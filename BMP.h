#pragma pack(push, 1)


/* COLOR MACROS */
#define MAX_COLOR_24    255
#define MAX_COLOR_16    31

/* RGB555 */
#define RGB555_MASK             0x1f  // (0.000)(00.00)(000.1)(1111) ; dots 5 bits set; () 4 bit set  
#define RGB555_MASK_RED(x)      ((x & RGB555_MASK) << 10)
#define RGB555_MASK_GREEN(x)    ((x & RGB555_MASK) << 5)
#define RGB555_MASK_BLUE(x)     ((x & RGB555_MASK))

/* RGB888 */
#define RGB888_MASK             0xff
#define RGB888_MASK_RED(x)      ((x & RGB888_MASK) << 16)
#define RGB888_MASK_GREEN(x)    ((x & RGB888_MASK) << 8)
#define RGB888_MASK_BLUE(x)     ((x & RGB888_MASK))

struct Color {
    uint32_t blue;
    uint32_t green;
    uint32_t red;
};


/* BMP structure */
#define BMP_SIGNATURE               0x4d42
#define BMP_FILEHEADER_SIZE         14

#define DIB_BITMAPINFOHEADER_SIZE   40
#define DIB_BITMAPV5HEADER_SIZE     124

#define DEFAULT_COLOR_DEPTH         24
#define DEFAULT_COLOR_PLANE         1

enum DIB_TYPES {
    DIB_BITMAPINFOHEADER,
    DIB_BITMAPV5HEADER
};

struct BMP {
    struct FILEHEADER * fh;
    void * ih;                  // DIB it's determinate in creation 
    unsigned char * pixel_data;
    enum DIB_TYPES dib_type;    // that's why we have a tracker
};


struct FILEHEADER {
    uint16_t signature; 
    uint32_t file_size; 
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;    // where pixel_data begins (fileheader + infoheader)
};

struct BITMAPINFOHEADER {
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

struct BITMAPV5HEADER {
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

// SETTERS AND GETTERS - DECLARATIONS
int32_t BMP_get_width_in_bytes(struct BMP *);

void BMP_set_info_header_size(struct BMP * image);
uint32_t BMP_get_info_header_size(struct BMP * image); 

void BMP_set_width(struct BMP * image, uint32_t width);
int32_t BMP_get_width(struct BMP * image);

void BMP_set_height(struct BMP * image, uint32_t height);
int32_t BMP_get_height(struct BMP * image);

void BMP_set_color_planes(struct BMP * image, uint16_t color_planes);
uint16_t BMP_get_color_planes(struct BMP * image);

void BMP_set_color_depth(struct BMP * image, uint16_t color_depth);
uint16_t BMP_get_color_depth(struct BMP * image);

void BMP_set_compression_method(struct BMP * image, uint32_t compression_method);
int32_t BMP_get_compression_method(struct BMP * image);

void BMP_set_image_size(struct BMP * image, uint32_t image_size);
int32_t BMP_get_image_size(struct BMP * image);

void BMP_set_horizontal_resolution(struct BMP * image, uint32_t horizontal_resolution);
int32_t BMP_get_horizontal_resolution(struct BMP * image);

void BMP_set_vertical_resolution(struct BMP * image, uint32_t vertical_resolution);
int32_t BMP_get_vertical_resolution(struct BMP * image);

void BMP_set_ncolors(struct BMP * image, uint32_t ncolors);
uint32_t BMP_get_ncolors(struct BMP * image);

void BMP_set_important_colors(struct BMP * image, uint32_t important_colors);
uint32_t BMP_get_important_colors(struct BMP * image);

// SETTERS AND GETTERS - IMPLEMENTATION
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
