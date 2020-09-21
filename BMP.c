#include <stdio.h>      // FILE
#include <string.h>     // menset

#include "BMP.h"        // struct _BMP, enum DIB_TYPES, getter declarations
#include "BMP_lib.h"    // BMP_malloc

int DEBUG = 1;

struct _BMP * BMP_create(int32_t width, int32_t height, uint16_t color_depth, enum DIB_TYPES dib_type) {
    struct _BMP * image = BMP_malloc(sizeof(struct _BMP), "Cannot create image");

    setup_infoheader(image, width, height, color_depth, dib_type);
    setup_fileheader(image);

    image -> pixel_data = BMP_malloc(get_image_size(image), "Cannot create pixel data");
    memset(image -> pixel_data, 0, get_image_size(image));
   
    if (DEBUG){
        printf("Image header data in Hex");
        printf("\nFileheader");
        printf("\n Signature: 0x%x", BMP_SIGNATURE);
        printf("\n Fileheader size: 0x%x", FILEHEADER_SIZE);
        printf("\n Infoheader size: 0x%x", get_info_header_size(image));
        printf("\n Imagesize: 0x%x", get_image_size(image));
        printf("\nInfoheader");
        printf("\n Size: 0x%x", get_info_header_size(image));
        printf("\n Width: 0x%x", get_width(image));
        printf("\n Height: 0x%x", get_height(image));
        printf("\n Planes: 0x%x", get_color_planes(image));
        printf("\n Compression: 0x%x", get_compression_method(image));
        printf("\n ImageSize: 0x%x", get_image_size(image));
        printf("\n Horizontal resolution: 0x%x", get_horizontal_resolution(image));
        printf("\n Vertica resolution: 0x%x", get_vertical_resolution(image));
        printf("\n Ncolors: 0x%x", get_ncolors(image));
        printf("\n Important colors: 0x%x", get_important_colors(image));
    }
    return image;
}

void * init_infoheader(enum DIB_TYPES dib_type) {
    switch (dib_type) {
        default:
        case BITMAPINFOHEADER:
            return BMP_malloc(sizeof(struct _BITMAPINFOHEADER), "Cannot create infoheader");
            break;

        case BITMAPV5HEADER:
            return BMP_malloc(sizeof(struct _BITMAPV5HEADER), "Cannot create infoheader");
            break;
    }
}

void setup_infoheader(struct _BMP * image, int32_t width, int32_t height, uint16_t color_depth, enum DIB_TYPES dib_type) {
    image -> ih  = init_infoheader(dib_type);

    set_info_header_size(image);
    set_color_planes(image, DEFAULT_COLOR_PLANE);
    set_width(image, width);
    set_height(image, height);
    set_color_depth(image, color_depth);
    set_image_size(image, get_width_in_bytes(image)*height);
}

void setup_fileheader(struct _BMP * image) {
    image -> fh = BMP_malloc(sizeof(struct _FILEHEADER), "Cannot create fileheader");
    image -> fh -> signature = BMP_SIGNATURE;
    image -> fh -> file_size = FILEHEADER_SIZE + get_info_header_size(image) + get_image_size(image);
    image -> fh -> offset = FILEHEADER_SIZE + get_info_header_size(image);
}


void BMP_save_without_free(struct _BMP * image, const char * filename) {
    FILE * output = fopen(filename, "wb");

    if (!output)
    {
        BMP_perror("Cannot create file");
    }

    fwrite(image -> fh, FILEHEADER_SIZE, 1, output);
    fwrite(image -> ih, get_info_header_size(image), 1, output);
    fwrite(image -> pixel_data, get_image_size(image), 1, output);

    fclose(output);
}


void BMP_save(struct _BMP * image, char * filename) {
    BMP_save_without_free(image, filename);
    free(image -> fh);
    free(image -> ih);
    free(image -> pixel_data);
    free(image);
}

void BMP_set_pixel(struct _BMP * image, int row, int col, const char * color)
{
    int32_t wiB = get_width_in_bytes(image);
    uint16_t depth = (get_color_depth(image) + 7) / 8;
    
    for (int d = 0; d < depth; d++) { 
        image -> pixel_data[row * wiB + col * depth + d] = color[d];

    }
}


/************** SETTERS & GETTERS ********************/ 
int32_t get_width_in_bytes(struct _BMP * image) {
    return ((get_width(image) * get_color_depth(image) + 31)/32)*4;
}

int32_t get_file_header_size() {
    return FILEHEADER_SIZE;
}

void set_info_header_size(struct _BMP * image) {
    switch (image -> dib_type) {
        case BITMAPINFOHEADER:
           ((struct _BITMAPINFOHEADER *) image -> ih) -> header_size = BITMAPINFOHEADER_SIZE;
           break;
        case BITMAPV5HEADER:
           ((struct _BITMAPV5HEADER *)image -> ih) -> header_size = BITMAPV5HEADER_SIZE;
           break;
        default:
           break;
    }
}

uint32_t get_info_header_size(struct _BMP * image) {
    switch (image -> dib_type) {
        case BITMAPINFOHEADER:
           return ((struct _BITMAPINFOHEADER *) image -> ih) -> header_size;
           break;
        case BITMAPV5HEADER:
           return ((struct _BITMAPV5HEADER *) image -> ih) -> header_size;
           break;
        default:
           break;
    }
}


void set_width(struct _BMP * image, uint32_t width) {
    switch (image -> dib_type) {
        case BITMAPINFOHEADER:
           ((struct _BITMAPINFOHEADER *)image -> ih) -> width = width;
           break;
        case BITMAPV5HEADER:
           ((struct _BITMAPV5HEADER *)image -> ih) -> width = width;
           break;
        default:
           break;
    }
}

int32_t get_width(struct _BMP * image) {
    switch (image -> dib_type) {
        case BITMAPINFOHEADER:
           return ((struct _BITMAPINFOHEADER *)image -> ih) -> width;
           break;
        case BITMAPV5HEADER:
           return ((struct _BITMAPV5HEADER *)image -> ih) -> width;
           break;
        default:
           break;
    }
}


void set_height(struct _BMP * image, uint32_t height) {
    switch (image -> dib_type) {
        case BITMAPINFOHEADER:
           ((struct _BITMAPINFOHEADER *)image -> ih) -> height = height;
           break;
        case BITMAPV5HEADER:
           ((struct _BITMAPV5HEADER *)image -> ih) -> height = height;
           break;
        default:
           break;
    }
}

int32_t get_height(struct _BMP * image) {
    switch (image -> dib_type) {
        case BITMAPINFOHEADER:
           return ((struct _BITMAPINFOHEADER *)image -> ih) -> height;
           break;
        case BITMAPV5HEADER:
           return ((struct _BITMAPV5HEADER *)image -> ih) -> height;
           break;
        default:
           break;
    }
}

void set_color_planes(struct _BMP * image, uint16_t color_planes) {
    switch (image -> dib_type) {
        case BITMAPINFOHEADER:
           ((struct _BITMAPINFOHEADER *)image -> ih) -> color_planes = color_planes;
           break;
        case BITMAPV5HEADER:
           ((struct _BITMAPV5HEADER *)image -> ih) -> color_planes = color_planes;
           break;
        default:
           break;
    }
}
uint16_t get_color_planes(struct _BMP * image) {
    switch (image -> dib_type) {
        case BITMAPINFOHEADER:
           return ((struct _BITMAPINFOHEADER *)image -> ih) -> color_planes;
           break;
        case BITMAPV5HEADER:
           return ((struct _BITMAPV5HEADER *)image -> ih) -> color_planes;
           break;
        default:
           break;
    }
}
void set_color_depth(struct _BMP * image, uint16_t color_depth) {
    switch (image -> dib_type) {
        case BITMAPINFOHEADER:
           ((struct _BITMAPINFOHEADER *)image -> ih) -> color_depth = color_depth;
           break;
        case BITMAPV5HEADER:
           ((struct _BITMAPV5HEADER *)image -> ih) -> color_depth = color_depth;
           break;
        default:
           break;
    }
}
uint16_t get_color_depth(struct _BMP * image) {
    switch (image -> dib_type) {
        case BITMAPINFOHEADER:
           return ((struct _BITMAPINFOHEADER *)image -> ih) -> color_depth;
           break;
        case BITMAPV5HEADER:
           return ((struct _BITMAPV5HEADER *)image -> ih) -> color_depth;
           break;
        default:
           break;
    }
}

void set_compression_method(struct _BMP * image, uint32_t compression_method) {
    switch (image -> dib_type) {
        case BITMAPINFOHEADER:
           ((struct _BITMAPINFOHEADER *)image -> ih) -> compression_method = compression_method;
           break;
        case BITMAPV5HEADER:
           ((struct _BITMAPV5HEADER *)image -> ih) -> compression_method = compression_method;
           break;
        default:
           break;
    }
}

int32_t get_compression_method(struct _BMP * image) {
    switch (image -> dib_type) {
        case BITMAPINFOHEADER:
           return ((struct _BITMAPINFOHEADER *)image -> ih) -> compression_method;
           break;
        case BITMAPV5HEADER:
           return ((struct _BITMAPV5HEADER *)image -> ih) -> compression_method;
           break;
        default:
           break;
    }
}


void set_image_size(struct _BMP * image, uint32_t image_size) {
    switch (image -> dib_type) {
        case BITMAPINFOHEADER:
           ((struct _BITMAPINFOHEADER *)image -> ih) -> image_size = image_size;
           break;
        case BITMAPV5HEADER:
           ((struct _BITMAPV5HEADER *)image -> ih) -> image_size = image_size;
           break;
        default:
           break;
    }
}

int32_t get_image_size(struct _BMP * image) {
    switch (image -> dib_type) {
        case BITMAPINFOHEADER:
           return ((struct _BITMAPINFOHEADER *)image -> ih) -> image_size;
           break;
        case BITMAPV5HEADER:
           return ((struct _BITMAPV5HEADER *)image -> ih) -> image_size;
           break;
        default:
           break;
    }
}


void set_horizontal_resolution(struct _BMP * image, uint32_t horizontal_resolution) {
    switch (image -> dib_type) {
        case BITMAPINFOHEADER:
           ((struct _BITMAPINFOHEADER *)image -> ih) -> horizontal_resolution = horizontal_resolution;
           break;
        case BITMAPV5HEADER:
           ((struct _BITMAPV5HEADER *)image -> ih) -> horizontal_resolution = horizontal_resolution;
           break;
        default:
           break;
    }
}

int32_t get_horizontal_resolution(struct _BMP * image) {
    switch (image -> dib_type) {
        case BITMAPINFOHEADER:
           return ((struct _BITMAPINFOHEADER *)image -> ih) -> horizontal_resolution;
           break;
        case BITMAPV5HEADER:
           return ((struct _BITMAPV5HEADER *)image -> ih) -> horizontal_resolution;
           break;
        default:
           break;
    }
}



void set_vertical_resolution(struct _BMP * image, uint32_t vertical_resolution) {
    switch (image -> dib_type) {
        case BITMAPINFOHEADER:
           ((struct _BITMAPINFOHEADER *)image -> ih) -> vertical_resolution = vertical_resolution;
           break;
        case BITMAPV5HEADER:
           ((struct _BITMAPV5HEADER *)image -> ih) -> vertical_resolution = vertical_resolution;
           break;
        default:
           break;
    }
}

int32_t get_vertical_resolution(struct _BMP * image) {
    switch (image -> dib_type) {
        case BITMAPINFOHEADER:
           return ((struct _BITMAPINFOHEADER *)image -> ih) -> vertical_resolution;
           break;
        case BITMAPV5HEADER:
           return ((struct _BITMAPV5HEADER *)image -> ih) -> vertical_resolution;
           break;
        default:
           break;
    }
}


void set_ncolors(struct _BMP * image, uint32_t ncolors) {
    switch (image -> dib_type) {
        case BITMAPINFOHEADER:
           ((struct _BITMAPINFOHEADER *)image -> ih) -> ncolors = ncolors;
           break;
        case BITMAPV5HEADER:
           ((struct _BITMAPV5HEADER *)image -> ih) -> ncolors = ncolors;
           break;
        default:
           break;
    }
}

uint32_t get_ncolors(struct _BMP * image) {
    switch (image -> dib_type) {
        case BITMAPINFOHEADER:
           return ((struct _BITMAPINFOHEADER *)image -> ih) -> ncolors;
           break;
        case BITMAPV5HEADER:
           return ((struct _BITMAPV5HEADER *)image -> ih) -> ncolors;
           break;
        default:
           break;
    }
}


void set_important_colors(struct _BMP * image, uint32_t important_colors) {
    switch (image -> dib_type) {
        case BITMAPINFOHEADER:
           ((struct _BITMAPINFOHEADER *)image -> ih) -> important_colors = important_colors;
           break;
        case BITMAPV5HEADER:
           ((struct _BITMAPV5HEADER *)image -> ih) -> important_colors = important_colors;
           break;
        default:
           break;
    }
}

uint32_t get_important_colors(struct _BMP * image) {
    switch (image -> dib_type) {
        case BITMAPINFOHEADER:
           return ((struct _BITMAPINFOHEADER *)image -> ih) -> important_colors;
           break;
        case BITMAPV5HEADER:
           return ((struct _BITMAPV5HEADER *)image -> ih) -> important_colors;
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
