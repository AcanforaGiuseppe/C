#include "filler.h"

void filler_image(const char* source_path, const char* dest_path, int x, int y, filler_color_t color) 
{ }

static void filler_algo_recurive(uint8_t* source_data, int width, int height, int channels, int x, int y, filler_color_t final_color, filler_color_t sampled_color) 
{
    if (x < 0 || x >= width)
    return;

    if (y < 0 || y >= height)
    return;

    int current_pixel = (y * width + x) * channels;
    filler_color_t* pixel_color = (filler_color_t*)(&source_data[current_pixel]); 

    if (pixel_color->r != sampled_color.r)
    return;

    if (pixel_color->g != sampled_color.g)
    return;

    if (pixel_color->b != sampled_color.b)
    return;

    pixel_color->r = final_color.r;
    pixel_color->g = final_color.g;
    pixel_color->b = final_color.b;

    filler_algo_recurive(source_data, width, height, channels, x-1, y+0, final_color, sampled_color);
    filler_algo_recurive(source_data, width, height, channels, x+1, y+0, final_color, sampled_color);
    filler_algo_recurive(source_data, width, height, channels, x+0, y-1, final_color, sampled_color);
    filler_algo_recurive(source_data, width, height, channels, x+0, y+1, final_color, sampled_color);
}

uint8_t* filler_execute(uint8_t* source_data, int width, int height, int channels, int x, int y, filler_color_t final_color) 
{
    if (x < 0 || x >= width)
    return NULL;

    if (y < 0 || y >= height)
    return NULL;

    int current_pixel = (y * width + x) * channels;
    filler_color_t sampled_color;
    sampled_color.r = source_data[current_pixel + 0];
    sampled_color.g = source_data[current_pixel + 1];
    sampled_color.b = source_data[current_pixel + 2];

    filler_algo_recurive(source_data, width, height, channels, x, y, final_color, sampled_color);

    return source_data;
}