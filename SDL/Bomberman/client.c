#ifdef _WIN32
	#include <WinSock2.h>
	#include <ws2tcpip.h>
#else
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
#endif

#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

int inputCoordinates();
int checkInput(const char* raw);

int inputCoordinates()
{
	const char* str[4096];
	scanf("%s", str);

	return checkInput(str);
}

int checkInput(const char* raw)
{
	char* lastPointer;
	int end = strtol(raw, NULL, 10);

	if (lastPointer == raw || errno == ERANGE)
	{
		printf("Invalid Input Error");
		return -1;
	}
	return end;
}

int main(int argc, char** argv)
{
#ifdef _WIN32
	WSADATA wsa_data;
	if (WSAStartup(0x0202, &wsa_data))
	{
		printf("Unable to initialize winsock2 \n");
		return -1;
	}
#endif

	int pos_x;
	int pos_y;
	int s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (s < 0)
	{
		printf("Unable to initialize UDP socket \n");
		return -1;
	}

	printf("Socket %d created \n", s);

	struct sockaddr_in sin;
	inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(9999);

	// Client loop
	int running = 1;

	while(running)
	{
		puts("\nExpected new input coordinates");
		printf("Insert X Coordinates: ");
		pos_x = inputCoordinates();
		if (pos_x < 0)
		{
			puts("Invalid X Position");
			return 1;
		}

		printf("Insert Y Coordinates: ");
		pos_y = inputCoordinates();
		if (pos_y < 0)
		{
			puts("Invalid Y Position");
			return 1;
		}

		int max_len = 8;
		char* buffer = malloc(4096);
		snprintf(buffer, max_len, "%d%s%d", pos_x, ",", pos_y);
		printf("Sending buffer: %s\n", buffer);
		int sent_bytes = sendto(s, buffer, max_len, 0, (struct sockaddr*)&sin, sizeof(sin));
		printf("Sent %d bytes via UDP \n", sent_bytes);
	}

	return 0;
}