#include <stdio.h>      // FILE
#include <stdlib.h>     // malloc, free
#include <string.h>     // strndup
#include <stdint.h>     // Exact size integers


#include "BMP_structure.h"  // struct BMP
#include "BMP_error.h"      // BMP_perror


struct BMP * BMP_create(int32_t width, int32_t height, uint16_t color_depth) {
    struct BMP * image = malloc(sizeof(struct BMP));

    if (!image) 
    {
        BMP_perror("Cannot create image");
    }

    image -> infoheader.size = 40;
    
    image -> infoheader.color_planes = 1;
    
    image -> infoheader.width = width;
    image -> infoheader.height = height;
    image -> infoheader.color_depth = color_depth; 
    
    int32_t wiB = ((image -> infoheader.width * image -> infoheader.color_depth+31)/32)*4;
    image -> infoheader.image_size = wiB * image -> infoheader.height;
    
    image -> fileheader.type = 0x4d42;
    image -> fileheader.size = 54 + image -> infoheader.image_size;
    image -> fileheader.offset = 54;

    image -> pixel_data = malloc(image -> infoheader.image_size);

    if (!image -> pixel_data) 
    {
        BMP_perror("Cannot create pixel data");    
    }
   
    return image;
}

void BMP_save_without_free(struct BMP * image, const char * filename) {
    FILE *output = fopen(filename, "wb");

    if (!output)
    {
        BMP_perror("Cannot create file");
    }

    fwrite(&image -> fileheader, sizeof(image -> fileheader), 1, output);
    fwrite(&image -> infoheader, sizeof(image -> infoheader), 1, output);
    fwrite((char *) image -> pixel_data, image -> infoheader.image_size, 1, output);

    fclose(output);
}


void BMP_save(struct BMP * image, char * filename) {
    BMP_save_without_free(image, filename);
    free(image -> pixel_data);
    free(image);
}

void BMP_set_pixel(struct BMP * image, int row, int col, const char * color)
{
    int32_t wiB = ((image -> infoheader.width * image -> infoheader.color_depth+31)/32)*4;
    uint16_t depth = (image -> infoheader.color_depth + 7) / 8;
    
    for (int d = 0; d < depth; d++) 
        image -> pixel_data[row * wiB + col * depth + d] = color[d];
}
