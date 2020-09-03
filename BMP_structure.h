#include <stdint.h>

#pragma pack(push, 1)
struct FileHeader {
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset; 
};

struct InfoHeader {
    uint32_t size;
    int32_t  width;
    int32_t  height;
    uint16_t color_planes;
    uint16_t bits_per_pixel;
    uint32_t compression_method;
    uint32_t image_size;
    int32_t  horizontal_resolution;
    int32_t  vertical_resolution;
    uint32_t colors;
    uint32_t important_colors;
};

struct BMP {
    struct FileHeader fileheader; 
    struct InfoHeader infoheader;
    unsigned char * pixel_data; 
};

#pragma pack(pop)
