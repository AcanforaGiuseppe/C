#include "bomberman.h"
#define SDL_MAIN_HANDLED

#ifdef _WIN32
	#include <WinSock2.h>
	#include <ws2tcpip.h>
#else
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
#endif

#include <SDL.h>
#include <stdbool.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#pragma comment(lib, "ws2_32.lib")

static void bomberman_game_mode_init(game_mode_t* game_mode)
{
	game_mode->timer = 60;
}

static void bomberman_map_init(cell_t* map)
{ }

static void bomberman_player_init(player_t* player)
{
	player->position.x = 0;
	player->position.y = 0;
	player->number_of_lifes = 1;
	player->number_of_bombs = 1;
	player->score = 0;
	player->speed = 1;
}

int bomberman_graphics_init(SDL_Window** window, SDL_Renderer** renderer, SDL_Texture** texture)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return -1;
	}

	*window = SDL_CreateWindow("SDL is active!", 100, 100, 512, 512, 0);
	if (!*window)
	{
		SDL_Log("Unable to create window: %s", SDL_GetError());
		SDL_Quit();
		return -1;
	}

	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!*renderer)
	{
		SDL_Log("Unable to create renderer: %s", SDL_GetError());
		SDL_DestroyWindow(*window);
		SDL_Quit();
		return -1;
	}

	int width;
	int height;
	int channels;
	unsigned char* pixels = stbi_load("emoji.png", &width, &height, &channels, 4);

	if (!pixels)
	{
		SDL_Log("Unable to open image");
		SDL_DestroyRenderer(*renderer);
		SDL_DestroyWindow(*window);
		SDL_Quit();
		return -1;
	}

	SDL_Log("Image width: %d height: %d channels: %d", width, height, channels);

	*texture = SDL_CreateTexture(*renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, width, height);

	if (!*texture)
	{
		SDL_Log("Unable to create texture: %s", SDL_GetError());
		free(pixels);
		SDL_DestroyRenderer(*renderer);
		SDL_DestroyWindow(*window);
		SDL_Quit();
		return -1;
	}

	SDL_UpdateTexture(*texture, NULL, pixels, width * 4);
	SDL_SetTextureAlphaMod(*texture, 255);
	SDL_SetTextureBlendMode(*texture, SDL_BLENDMODE_BLEND);
	free(pixels);

	return 0;
}

int server_init(int bm_socket)
{
	if (bm_socket < 0)
	{
		printf("Unable to initialize the UDP socket \n");
		return -1;
	}

	printf("Socket %d created \n", bm_socket);
	struct sockaddr_in sin;
	inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(9999);

	if (bind(bm_socket, (struct sockaddr*)&sin, sizeof(sin)))
	{
		printf("Unable to bind the UDP socket \n");
		return -1;
	}

	return 0;
}

int set_nb(int s)
{
#ifdef _WIN32
	unsigned long nb_mode = 1;
	return ioctlsocket(s, FIONBIO, &nb_mode);
#else
	int flags = fcntl(s, F_GETFL, 0);

	if (flags < 0)
		return flags;

	flags |= O_NONBLOCK;
	return fcntl(s, F_SETFL, flags);
#endif
}

int bomberman_get_socket_infos(int s, char* info)
{
	char buffer[4096];
	struct sockaddr_in sender_in;
	int sender_in_size = sizeof(sender_in);
	int len = recvfrom(s, buffer, 4096, 0, (struct sockaddr*)&sender_in, &sender_in_size);

	if (len > 0)
	{
		char addr_as_string[64];
		inet_ntop(AF_INET, &sender_in.sin_addr, addr_as_string, 64);
		printf("Received %d bytes from %s:%d\n", len, addr_as_string, ntohs(sender_in.sin_port));
		printf("Buffer: %s\n", buffer);
		strcpy(info, buffer);
		return 0;
	}
	else
	{
		strcpy(info, "Invalid");
		return -1;
	}
}

void bm_tp_player(player_t* player, int x, int y)
{
	player->position.x = x;
	player->position.y = y;
}

int main(int argc, char** argv)
{
	game_mode_t game_mode;
	cell_t map[64 * 64];
	player_t player;

	// DeltaTime
	double deltaT = 0;
	Uint64 lastFrameT;
	Uint64 currFrameT = 0;

	// - Debug only -
	bool showDebug = true;
	float clockTime = 1;
	float clockCounter = clockTime;

	// Player Movements
	int windowMultiplier = 100;
	double deltaMovement = 0;
	char* coords[4096];
	int x = -10;
	int y = -10;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;

	bomberman_game_mode_init(&game_mode);
	bomberman_map_init(map);
	bomberman_player_init(&player);

#ifdef _WIN32
	WSADATA wsa_data;
	if (WSAStartup(0x0202, &wsa_data))
	{
		printf("Unable to initialize winsock2 \n");
		return -1;
	}
#endif

	int bm_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	printf("Socket is %d\n", bm_socket);
	if (server_init(bm_socket) != 0)
	{
		puts("Unable to create socket");
		return -1;
	}
	set_nb(bm_socket);

	if (bomberman_graphics_init(&window, &renderer, &texture))
		return -1;

	// Game loop
	int running = 1;

	while (running)
	{
		lastFrameT = currFrameT;
		currFrameT = SDL_GetTicks64();
		deltaT = (double)(currFrameT - lastFrameT) * 0.001;

		if (showDebug)
		{
			clockCounter -= deltaT;
			if (clockCounter <= 0)
			{
				clockCounter = clockTime;
				printf("FPS: %f\n", 1 / deltaT);
			}
		}

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				running = 0;
		}

		SDL_PumpEvents();
		const Uint8* keys = SDL_GetKeyboardState(NULL);
		deltaMovement = player.speed * windowMultiplier * deltaT;
		player.position.x += (keys[SDL_SCANCODE_RIGHT] | keys[SDL_SCANCODE_D]) * (int)deltaMovement;
		player.position.x -= (keys[SDL_SCANCODE_LEFT] | keys[SDL_SCANCODE_A]) * (int)deltaMovement;
		player.position.y += (keys[SDL_SCANCODE_DOWN] | keys[SDL_SCANCODE_S]) * (int)deltaMovement;
		player.position.y -= (keys[SDL_SCANCODE_UP] | keys[SDL_SCANCODE_W]) * (int)deltaMovement;

		bomberman_get_socket_infos(bm_socket, coords);
		if (strcmp(coords, "Invalid") != 0)
		{
			char* token = strtok(coords, ",");
			x = strtol(token, NULL, 10);
			token = strtok(NULL, ",");
			y = strtol(token, NULL, 10);
			bm_tp_player(&player, x, y);
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_Rect target_rect = { player.position.x, player.position.y, 32, 32 };
		SDL_RenderCopy(renderer, texture, NULL, &target_rect);
		SDL_RenderPresent(renderer);
	}

	return 0;
}
