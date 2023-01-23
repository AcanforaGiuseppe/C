#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <stdio.h>

int main() 
{
    const char* file_name = "red16x16.png";
    int width, height, channels;

    unsigned char* data = stbi_load(file_name, &width, &height, &channels, 0);

    printf("Width: %d, Height: %d, Channels: %d\n", width, height, channels);
    int size = width * height * channels;
    printf("Size: %d\n", size);

    //stbi_image_free(data);

    stbi_write_png("newfile16x16", width, height, channels, data, 0);

    return 0;
}