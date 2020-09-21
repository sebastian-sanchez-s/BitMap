#include <stdint.h>

#pragma pack(push, 1)

// Definitions
enum DIB_TYPES {
    BITMAPINFOHEADER,
    BITMAPV5HEADER
};

/* Colors LIMITS */

#define MAX_COLOR16 31
struct Color16 {
    unsigned int red:5;
    unsigned int green:5;
    unsigned int blue:5;
    unsigned int alpha:1;
};

#define MAX_COLOR24 255
struct Color24 {
    unsigned int red:8;
    unsigned int green:8;
    unsigned int blue:8;
    unsigned int alpha:8;
};


/* BMP structure itself */
#define BMP_SIGNATURE           0x4d42
#define FILEHEADER_SIZE         14

#define BITMAPINFOHEADER_SIZE   40
#define BITMAPV5HEADER_SIZE     124

#define DEFAULT_COLOR_DEPTH     24
#define DEFAULT_COLOR_PLANE     1

struct _BMP {
    struct _FILEHEADER * fh;
    void * ih;                  // DIB it's determinate in creation 
    unsigned char * pixel_data;
    enum DIB_TYPES dib_type;    // that's why we have a tracker
};


struct _FILEHEADER {
    uint16_t signature; 
    uint32_t file_size; 
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;    // where pixel_data begins (fileheader + infoheader)
};

struct _BITMAPINFOHEADER {
    uint32_t header_size;
    int32_t  width;
    int32_t  height;
    uint16_t color_planes;
    uint16_t color_depth;
    uint32_t compression_method;
    uint32_t image_size;
    int32_t  horizontal_resolution;
    int32_t  vertical_resolution;
    uint32_t ncolors;
    uint32_t important_colors;
};

struct _BITMAPV5HEADER {
    uint32_t header_size;
    int32_t  width;
    int32_t  height;
    uint16_t color_planes;
    uint16_t color_depth;
    uint32_t compression_method;
    uint32_t image_size;
    int32_t  horizontal_resolution;
    int32_t  vertical_resolution;
    uint32_t ncolors;
    uint32_t important_colors;
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
}; 
#pragma pack(pop)

// Functions prototype
struct _BMP * BMP_create(int32_t, int32_t, uint16_t, enum DIB_TYPES);
void * init_infoheader(enum DIB_TYPES); 
void setup_infoheader(struct _BMP *, int32_t, int32_t, uint16_t, enum DIB_TYPES); 
void setup_fileheader(struct _BMP *);

// Setters and Getters
int32_t get_width_in_bytes(struct _BMP *);

void set_info_header_size(struct _BMP * image);
uint32_t get_info_header_size(struct _BMP * image); 

void set_width(struct _BMP * image, uint32_t width);
int32_t get_width(struct _BMP * image);

void set_height(struct _BMP * image, uint32_t height);
int32_t get_height(struct _BMP * image);

void set_color_planes(struct _BMP * image, uint16_t color_planes);
uint16_t get_color_planes(struct _BMP * image);

void set_color_depth(struct _BMP * image, uint16_t color_depth);
uint16_t get_color_depth(struct _BMP * image);

void set_compression_method(struct _BMP * image, uint32_t compression_method);
int32_t get_compression_method(struct _BMP * image);

void set_image_size(struct _BMP * image, uint32_t image_size);
int32_t get_image_size(struct _BMP * image);

void set_horizontal_resolution(struct _BMP * image, uint32_t horizontal_resolution);
int32_t get_horizontal_resolution(struct _BMP * image);

void set_vertical_resolution(struct _BMP * image, uint32_t vertical_resolution);
int32_t get_vertical_resolution(struct _BMP * image);

void set_ncolors(struct _BMP * image, uint32_t ncolors);
uint32_t get_ncolors(struct _BMP * image);

void set_important_colors(struct _BMP * image, uint32_t important_colors);
uint32_t get_important_colors(struct _BMP * image);
