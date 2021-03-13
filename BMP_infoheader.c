#include <stdint.h>
#include <string.h>

#include "BMP_lib.h"

#include "infoheaders/BITMAPINFOHEADER.c"
#include "infoheaders/BITMAPV5HEADER.c"

// INIT INFOHEADER

void * (*init_infoheader[])() = {
	BITMAPINFOHEADER_init,
    BITMAPV5HEADER_init
};

// HEADER SIZE

uint32_t (*_get_header_size[])(void *) = {
    BITMAPINFOHEADER_get_header_size,
    BITMAPV5HEADER_get_header_size
};

// WIDTH
void (*_set_width[])(void *, int32_t) = {
    BITMAPINFOHEADER_set_width,
    BITMAPV5HEADER_set_width
};

int32_t (*_get_width[])(void *) = {
    BITMAPINFOHEADER_get_width,
    BITMAPV5HEADER_get_width
};

// HEIGHT
void (*_set_height[])(void *, int32_t) = {
    BITMAPINFOHEADER_set_height,
    BITMAPV5HEADER_set_height
};

int32_t (*_get_height[])(void *) = {
    BITMAPINFOHEADER_get_height,
    BITMAPV5HEADER_get_height
};

// COLOR PLANES
void (*_set_color_planes[])(void *, uint16_t) = {
    BITMAPINFOHEADER_set_color_planes,
    BITMAPV5HEADER_set_color_planes
};

uint16_t (*_get_color_planes[])(void *) = {
    BITMAPINFOHEADER_get_color_planes,
    BITMAPV5HEADER_get_color_planes
};

// COLOR DEPTH
void (*_set_color_depth[])(void *, uint16_t) = {
    BITMAPINFOHEADER_set_color_depth,
    BITMAPV5HEADER_set_color_depth
};

uint16_t (*_get_color_depth[])(void *f) = {
    BITMAPINFOHEADER_get_color_depth,
    BITMAPV5HEADER_get_color_depth
};

// IMAGE SIZE
void (*_set_image_size[])(void *, uint32_t) = {
    BITMAPINFOHEADER_set_image_size,
    BITMAPV5HEADER_set_image_size,
};

uint32_t (*_get_image_size[])(void *) = {
    BITMAPINFOHEADER_get_image_size,
    BITMAPV5HEADER_get_image_size,
};
