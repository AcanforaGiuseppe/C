#define CLOVE_SUITE_NAME FillerImageTest
#include "clove-unit.h"
#include "filler.h"
#include <string.h>
#include <stdlib.h>

char* concat_path(const char* path1, const char* path2) 
{
    int dest_size = strlen(path1) + strlen(path2) + 1;
    char* dest = (char*)malloc(dest_size);
    dest[0] = '\0';
    strcat(dest, path1);
    strcat(dest, path2);
    return dest;
}

CLOVE_TEST(FillOnePixelImageWithSuccess) 
{   
    const char* base_test_path = CLOVE_EXEC_BASE_PATH();
    const char* source_path = concat_path(base_test_path, "\\resources\\red_1x1.png");
    const char* dest_path = concat_path(base_test_path,   "\\resources\\red_1x1_filled_green.png");
    
    filler_color_t green = {0, 255, 0};
    
    filler_image(source_path, dest_path, 0, 0, green);
}