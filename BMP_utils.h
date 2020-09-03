#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BMP_structure.h"

struct BMP * BMP_create(int w, int h, int d) {
    struct BMP * image = malloc(sizeof(struct BMP));

    if (!image) 
    {
        // some error msg
        return NULL;
    }

    image -> infoheader.size = 40;
    
    image -> infoheader.color_planes = 1;
    
    image -> infoheader.width = w;
    image -> infoheader.height = h;
    image -> infoheader.bits_per_pixel = d; 
    
    int wiB = ((image -> infoheader.width * image -> infoheader.bits_per_pixel+31)/32)*4;
    image -> infoheader.image_size = wiB * image -> infoheader.height;
    
    image -> fileheader.type = 0x4d42;
    image -> fileheader.size = 54 + image -> infoheader.image_size;
    image -> fileheader.offset = 54;

    image -> pixel_data = malloc(image -> infoheader.image_size);

    if (!image -> pixel_data) 
    {
        // some errror
        return NULL;
    }
   
    return image;
}

void BMP_save_without_free(struct BMP * image, char * filename) {
    FILE *output = fopen(filename, "wb");

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
