#include <stdio.h>      // FILE
#include <string.h>     // memset, memcpy

#include "BMP.h"        // struct BMP, enum DIB_TYPES, getter declarations
#include "BMP_lib.h"    // BMP_malloc

int DEBUG = 1;

struct BMP * BMP_create(int32_t width, int32_t height, uint16_t color_depth, enum DIB_TYPES dib_type) {
    struct BMP * image = BMP_malloc(sizeof(struct BMP), "Cannot create image");

    setup_infoheader(image, width, height, color_depth, dib_type);
    setup_fileheader(image);

    image -> pixel_data = BMP_malloc(BMP_get_image_size(image), "Cannot create pixel data");
    memset(image -> pixel_data, 0, BMP_get_image_size(image));
   
    if (DEBUG){
        printf("Image header data in Hex");
        printf("\nFileheader");
        printf("\n Signature: 0x%x", BMP_SIGNATURE);
        printf("\n Fileheader size: 0x%x", BMP_FILEHEADER_SIZE);
        printf("\n Infoheader size: 0x%x", BMP_get_info_header_size(image));
        printf("\n Imagesize: 0x%x", BMP_get_image_size(image));
        printf("\nInfoheader");
        printf("\n Size: 0x%x", BMP_get_info_header_size(image));
        printf("\n Width: 0x%x", BMP_get_width(image));
        printf("\n Height: 0x%x", BMP_get_height(image));
        printf("\n Planes: 0x%x", BMP_get_color_planes(image));
        printf("\n Compression: 0x%x", BMP_get_compression_method(image));
        printf("\n ImageSize: 0x%x", BMP_get_image_size(image));
        printf("\n Horizontal resolution: 0x%x", BMP_get_horizontal_resolution(image));
        printf("\n Vertica resolution: 0x%x", BMP_get_vertical_resolution(image));
        printf("\n Ncolors: 0x%x", BMP_get_ncolors(image));
        printf("\n Important colors: 0x%x\n", BMP_get_important_colors(image));
    }
    return image;
}

void * init_infoheader(enum DIB_TYPES dib_type) {
    switch (dib_type) {
        default:
        case DIB_BITMAPINFOHEADER:
            return BMP_malloc(sizeof(struct BITMAPINFOHEADER), "Cannot create infoheader");
            break;

        case DIB_BITMAPV5HEADER:
            return BMP_malloc(sizeof(struct BITMAPV5HEADER), "Cannot create infoheader");
            break;
    }
}

void setup_infoheader(struct BMP * image, int32_t width, int32_t height, uint16_t color_depth, enum DIB_TYPES dib_type) {
    image -> ih  = init_infoheader(dib_type);

    BMP_set_info_header_size(image);
    BMP_set_color_planes(image, DEFAULT_COLOR_PLANE);
    BMP_set_width(image, width);
    BMP_set_height(image, height);
    BMP_set_color_depth(image, color_depth);
    BMP_set_image_size(image, BMP_get_width_in_bytes(image)*height);
}

void setup_fileheader(struct BMP * image) {
    image -> fh = BMP_malloc(sizeof(struct FILEHEADER), "Cannot create fileheader");
    image -> fh -> signature = BMP_SIGNATURE;
    image -> fh -> file_size = BMP_FILEHEADER_SIZE + BMP_get_info_header_size(image) + BMP_get_image_size(image);
    image -> fh -> offset = BMP_FILEHEADER_SIZE + BMP_get_info_header_size(image);
}


void BMP_save_without_free(struct BMP * image, const char * filename) {
    FILE * output = fopen(filename, "wb");

    if (!output)
    {
        BMP_perror("Cannot create file");
    }

    fwrite(image -> fh, BMP_FILEHEADER_SIZE, 1, output);
    fwrite(image -> ih, BMP_get_info_header_size(image), 1, output);
    fwrite(image -> pixel_data, BMP_get_image_size(image), 1, output);

    fclose(output);
}


void BMP_save(struct BMP * image, char * filename) {
    BMP_save_without_free(image, filename);
    free(image -> fh);
    free(image -> ih);
    free(image -> pixel_data);
    free(image);
}

void BMP_set_pixel(struct BMP * image, int row, int col, void * color)
{
    int32_t wiB = BMP_get_width_in_bytes(image);
    uint16_t depth = (BMP_get_color_depth(image) + 7) / 8;
    
    memcpy(image -> pixel_data + row * wiB + col * depth, color, depth);
}


/************** SETTERS & GETTERS ********************/ 
int32_t BMP_get_width_in_bytes(struct BMP * image) {
    return ((BMP_get_width(image) * BMP_get_color_depth(image) + 31)/32)*4;
}

void BMP_set_info_header_size(struct BMP * image) {
    switch (image -> dib_type) {
        case DIB_BITMAPINFOHEADER:
           ((struct BITMAPINFOHEADER *) image -> ih) -> header_size = DIB_BITMAPINFOHEADER_SIZE;
           break;
        case DIB_BITMAPV5HEADER:
           ((struct BITMAPV5HEADER *)image -> ih) -> header_size = DIB_BITMAPV5HEADER_SIZE;
           break;
        default:
           break;
    }
}

uint32_t BMP_get_info_header_size(struct BMP * image) {
    switch (image -> dib_type) {
        case DIB_BITMAPINFOHEADER:
           return ((struct BITMAPINFOHEADER *) image -> ih) -> header_size;
           break;
        case DIB_BITMAPV5HEADER:
           return ((struct BITMAPV5HEADER *) image -> ih) -> header_size;
           break;
        default:
           break;
    }
}


void BMP_set_width(struct BMP * image, uint32_t width) {
    switch (image -> dib_type) {
        case DIB_BITMAPINFOHEADER:
           ((struct BITMAPINFOHEADER *)image -> ih) -> width = width;
           break;
        case DIB_BITMAPV5HEADER:
           ((struct BITMAPV5HEADER *)image -> ih) -> width = width;
           break;
        default:
           break;
    }
}

int32_t BMP_get_width(struct BMP * image) {
    switch (image -> dib_type) {
        case DIB_BITMAPINFOHEADER:
           return ((struct BITMAPINFOHEADER *)image -> ih) -> width;
           break;
        case DIB_BITMAPV5HEADER:
           return ((struct BITMAPV5HEADER *)image -> ih) -> width;
           break;
        default:
           break;
    }
}


void BMP_set_height(struct BMP * image, uint32_t height) {
    switch (image -> dib_type) {
        case DIB_BITMAPINFOHEADER:
           ((struct BITMAPINFOHEADER *)image -> ih) -> height = height;
           break;
        case DIB_BITMAPV5HEADER:
           ((struct BITMAPV5HEADER *)image -> ih) -> height = height;
           break;
        default:
           break;
    }
}

int32_t BMP_get_height(struct BMP * image) {
    switch (image -> dib_type) {
        case DIB_BITMAPINFOHEADER:
           return ((struct BITMAPINFOHEADER *)image -> ih) -> height;
           break;
        case DIB_BITMAPV5HEADER:
           return ((struct BITMAPV5HEADER *)image -> ih) -> height;
           break;
        default:
           break;
    }
}

void BMP_set_color_planes(struct BMP * image, uint16_t color_planes) {
    switch (image -> dib_type) {
        case DIB_BITMAPINFOHEADER:
           ((struct BITMAPINFOHEADER *)image -> ih) -> color_planes = color_planes;
           break;
        case DIB_BITMAPV5HEADER:
           ((struct BITMAPV5HEADER *)image -> ih) -> color_planes = color_planes;
           break;
        default:
           break;
    }
}
uint16_t BMP_get_color_planes(struct BMP * image) {
    switch (image -> dib_type) {
        case DIB_BITMAPINFOHEADER:
           return ((struct BITMAPINFOHEADER *)image -> ih) -> color_planes;
           break;
        case DIB_BITMAPV5HEADER:
           return ((struct BITMAPV5HEADER *)image -> ih) -> color_planes;
           break;
        default:
           break;
    }
}
void BMP_set_color_depth(struct BMP * image, uint16_t color_depth) {
    switch (image -> dib_type) {
        case DIB_BITMAPINFOHEADER:
           ((struct BITMAPINFOHEADER *)image -> ih) -> color_depth = color_depth;
           break;
        case DIB_BITMAPV5HEADER:
           ((struct BITMAPV5HEADER *)image -> ih) -> color_depth = color_depth;
           break;
        default:
           break;
    }
}
uint16_t BMP_get_color_depth(struct BMP * image) {
    switch (image -> dib_type) {
        case DIB_BITMAPINFOHEADER:
           return ((struct BITMAPINFOHEADER *)image -> ih) -> color_depth;
           break;
        case DIB_BITMAPV5HEADER:
           return ((struct BITMAPV5HEADER *)image -> ih) -> color_depth;
           break;
        default:
           break;
    }
}

void BMP_set_compression_method(struct BMP * image, uint32_t compression_method) {
    switch (image -> dib_type) {
        case DIB_BITMAPINFOHEADER:
           ((struct BITMAPINFOHEADER *)image -> ih) -> compression_method = compression_method;
           break;
        case DIB_BITMAPV5HEADER:
           ((struct BITMAPV5HEADER *)image -> ih) -> compression_method = compression_method;
           break;
        default:
           break;
    }
}

int32_t BMP_get_compression_method(struct BMP * image) {
    switch (image -> dib_type) {
        case DIB_BITMAPINFOHEADER:
           return ((struct BITMAPINFOHEADER *)image -> ih) -> compression_method;
           break;
        case DIB_BITMAPV5HEADER:
           return ((struct BITMAPV5HEADER *)image -> ih) -> compression_method;
           break;
        default:
           break;
    }
}


void BMP_set_image_size(struct BMP * image, uint32_t image_size) {
    switch (image -> dib_type) {
        case DIB_BITMAPINFOHEADER:
           ((struct BITMAPINFOHEADER *)image -> ih) -> image_size = image_size;
           break;
        case DIB_BITMAPV5HEADER:
           ((struct BITMAPV5HEADER *)image -> ih) -> image_size = image_size;
           break;
        default:
           break;
    }
}

int32_t BMP_get_image_size(struct BMP * image) {
    switch (image -> dib_type) {
        case DIB_BITMAPINFOHEADER:
           return ((struct BITMAPINFOHEADER *)image -> ih) -> image_size;
           break;
        case DIB_BITMAPV5HEADER:
           return ((struct BITMAPV5HEADER *)image -> ih) -> image_size;
           break;
        default:
           break;
    }
}


void BMP_set_horizontal_resolution(struct BMP * image, uint32_t horizontal_resolution) {
    switch (image -> dib_type) {
        case DIB_BITMAPINFOHEADER:
           ((struct BITMAPINFOHEADER *)image -> ih) -> horizontal_resolution = horizontal_resolution;
           break;
        case DIB_BITMAPV5HEADER:
           ((struct BITMAPV5HEADER *)image -> ih) -> horizontal_resolution = horizontal_resolution;
           break;
        default:
           break;
    }
}

int32_t BMP_get_horizontal_resolution(struct BMP * image) {
    switch (image -> dib_type) {
        case DIB_BITMAPINFOHEADER:
           return ((struct BITMAPINFOHEADER *)image -> ih) -> horizontal_resolution;
           break;
        case DIB_BITMAPV5HEADER:
           return ((struct BITMAPV5HEADER *)image -> ih) -> horizontal_resolution;
           break;
        default:
           break;
    }
}



void BMP_set_vertical_resolution(struct BMP * image, uint32_t vertical_resolution) {
    switch (image -> dib_type) {
        case DIB_BITMAPINFOHEADER:
           ((struct BITMAPINFOHEADER *)image -> ih) -> vertical_resolution = vertical_resolution;
           break;
        case DIB_BITMAPV5HEADER:
           ((struct BITMAPV5HEADER *)image -> ih) -> vertical_resolution = vertical_resolution;
           break;
        default:
           break;
    }
}

int32_t BMP_get_vertical_resolution(struct BMP * image) {
    switch (image -> dib_type) {
        case DIB_BITMAPINFOHEADER:
           return ((struct BITMAPINFOHEADER *)image -> ih) -> vertical_resolution;
           break;
        case DIB_BITMAPV5HEADER:
           return ((struct BITMAPV5HEADER *)image -> ih) -> vertical_resolution;
           break;
        default:
           break;
    }
}


void BMP_set_ncolors(struct BMP * image, uint32_t ncolors) {
    switch (image -> dib_type) {
        case DIB_BITMAPINFOHEADER:
           ((struct BITMAPINFOHEADER *)image -> ih) -> ncolors = ncolors;
           break;
        case DIB_BITMAPV5HEADER:
           ((struct BITMAPV5HEADER *)image -> ih) -> ncolors = ncolors;
           break;
        default:
           break;
    }
}

uint32_t BMP_get_ncolors(struct BMP * image) {
    switch (image -> dib_type) {
        case DIB_BITMAPINFOHEADER:
           return ((struct BITMAPINFOHEADER *)image -> ih) -> ncolors;
           break;
        case DIB_BITMAPV5HEADER:
           return ((struct BITMAPV5HEADER *)image -> ih) -> ncolors;
           break;
        default:
           break;
    }
}


void BMP_set_important_colors(struct BMP * image, uint32_t important_colors) {
    switch (image -> dib_type) {
        case DIB_BITMAPINFOHEADER:
           ((struct BITMAPINFOHEADER *)image -> ih) -> important_colors = important_colors;
           break;
        case DIB_BITMAPV5HEADER:
           ((struct BITMAPV5HEADER *)image -> ih) -> important_colors = important_colors;
           break;
        default:
           break;
    }
}

uint32_t BMP_get_important_colors(struct BMP * image) {
    switch (image -> dib_type) {
        case DIB_BITMAPINFOHEADER:
           return ((struct BITMAPINFOHEADER *)image -> ih) -> important_colors;
           break;
        case DIB_BITMAPV5HEADER:
           return ((struct BITMAPV5HEADER *)image -> ih) -> important_colors;
           break;
        default:
           break;
    }
}
/* TODO: setters and getters of these
uint32_t mask_red;
uint32_t mask_green;
uint32_t mask_blue;
uint32_t mask_alpha;
uint32_t color_space;
int32_t redx;
int32_t redy;
int32_t redz;
int32_t greenx;
int32_t greeny;
int32_t greenz;
int32_t bluex;
int32_t bluey;
int32_t bluez;
uint32_t gamma_red;
uint32_t gamma_green;
uint32_t gamma_blue;
uint32_t rendering_intent;
uint32_t profile_data_offset;
uint32_t profile_data_size;
uint32_t reserved;
*/
