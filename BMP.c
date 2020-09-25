#include <stdio.h>      // FILE, fprintf family
#include <stdint.h>     // intXX, uintXX
#include <string.h>     // memset, memcpy, perror
#include <stdlib.h>     // malloc, exit
#include <errno.h>      // errno

#include "BMP.h"        // Format definitions (struct, enum, macros)
#include "BMP_error.h"  // BMP_perror
#include "BMP_lib.h"    // BMP_malloc, BMP_open

#define DEBUG 1
#define DEBUG_PRINT(x) if (DEBUG) {printf("%s\n", x);}

// *************************** DECLARATIONS ****************** 
// ---------------------------- Public -----------------------
struct BMP * BMP_create(int32_t, int32_t, uint16_t, enum DIB_TYPES);
void BMP_save_without_free(struct BMP *, const char *);
void BMP_save(struct BMP *, const char *);
void BMP_set_pixel(struct BMP *, int, int, void *);
void BMP_set_background(struct BMP *, void *);
// ---------------------------- Private ----------------------
static void * _init_infoheader(enum DIB_TYPES);
static void _setup_infoheader(struct BMP *, int32_t, int32_t, uint16_t, enum DIB_TYPES);
static void _setup_fileheader(struct BMP *);


// ************************* IMPLEMENTATIONS ************************
// --------------------------- Public --------------------------------------
struct BMP * BMP_create(int32_t width, int32_t height, uint16_t color_depth, enum DIB_TYPES dib_type) {
    DEBUG_PRINT("Creating image")

    struct BMP * image = BMP_malloc(sizeof(struct BMP), "Cannot create image");

    _setup_infoheader(image, width, height, color_depth, dib_type);
    _setup_fileheader(image);

    image -> pixel_data = BMP_malloc(BMP_get_image_size(image), "Cannot create pixel data");
    memset(image -> pixel_data, 0, BMP_get_image_size(image));

    return image;
}

void BMP_save_without_free(struct BMP * image, const char * filename) {
    DEBUG_PRINT("Saving image...")

    FILE * output = BMP_open(filename, "wb");

    fwrite(image -> fh, BMP_FILEHEADER_SIZE, 1, output);
    fwrite(image -> ih, BMP_get_info_header_size(image), 1, output);
    fwrite(image -> pixel_data, BMP_get_image_size(image), 1, output);

    fclose(output);
    
    DEBUG_PRINT("Done.")
}


void BMP_save(struct BMP * image, const char * filename) {
    BMP_save_without_free(image, filename);
    
    DEBUG_PRINT("Freeing memory...")

    free(image -> fh);
    free(image -> ih);
    free(image -> pixel_data);
    free(image);

    DEBUG_PRINT("Done.")
}

void BMP_set_pixel(struct BMP * image, int row, int col, void * color)
{
    int32_t wiB = BMP_get_width_in_bytes(image);
    uint16_t depth = (BMP_get_color_depth(image) + 7) / 8;
    
    memcpy(image -> pixel_data + row * wiB + col * depth, color, depth);
}

void BMP_set_background(struct BMP * image, void * color)
{
    memset(image -> pixel_data, *(int *) color, BMP_get_image_size(image));
}

// ---------------------------- Private ----------------------------------

static void * _init_infoheader(enum DIB_TYPES dib_type) {
    switch (dib_type) {
        default:
        case DIB_BITMAPINFOHEADER:
            DEBUG_PRINT("Detect BITMAPINFOHEADER")

            return BMP_malloc(sizeof(struct BITMAPINFOHEADER), "Cannot create infoheader");
            break;

        case DIB_BITMAPV5HEADER:
            DEBUG_PRINT("Detect BITMAPV5HEADER")

            return BMP_malloc(sizeof(struct BITMAPV5HEADER), "Cannot create infoheader");
            break;
    }
}

static void _setup_infoheader(struct BMP * image, int32_t width, int32_t height, uint16_t color_depth, enum DIB_TYPES dib_type) {
    DEBUG_PRINT("Setup infoheader...")

    image -> ih  = _init_infoheader(dib_type);

    BMP_set_info_header_size(image);
    BMP_set_color_planes(image, DEFAULT_COLOR_PLANE);
    BMP_set_width(image, width);
    BMP_set_height(image, height);
    BMP_set_color_depth(image, color_depth);
    BMP_set_image_size(image, BMP_get_width_in_bytes(image)*height);
    
    DEBUG_PRINT("Done.")
}

static void _setup_fileheader(struct BMP * image) {
    DEBUG_PRINT("Setup fileheader...")
        
    image -> fh = BMP_malloc(sizeof(struct FILEHEADER), "Cannot create fileheader");
    image -> fh -> signature = BMP_SIGNATURE;
    image -> fh -> file_size = BMP_FILEHEADER_SIZE + BMP_get_info_header_size(image) + BMP_get_image_size(image);
    image -> fh -> offset = BMP_FILEHEADER_SIZE + BMP_get_info_header_size(image);

    DEBUG_PRINT("Done.")
}

