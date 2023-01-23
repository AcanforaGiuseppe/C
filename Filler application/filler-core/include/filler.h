#pragma once
#include <stdint.h>

//void* fillImage(srcImageData, color, pointXY)
//void filler(destPath, sourcePath, color, pointXY)

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} filler_color_t; 

uint8_t* filler_execute(uint8_t* source_data, int width, int height, int channels, int x, int y, filler_color_t color);

void filler_image(const char* source_path, const char* dest_path, int x, int y, filler_color_t color);