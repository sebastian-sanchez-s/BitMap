#define DIB_BITMAPV5HEADER_SIZE     124

#pragma pack(push, 1)

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
	int32_t  redx;
	int32_t  redy;
	int32_t  redz;
	int32_t  greenx;
	int32_t  greeny;
	int32_t  greenz;
	int32_t  bluex;
	int32_t  bluey;
	int32_t  bluez;
	uint32_t gamma_red;
	uint32_t gamma_green;
  	uint32_t gamma_blue;
  	uint32_t rendering_intent;
  	uint32_t profile_data_offset;
  	uint32_t profile_data_size;
  	uint32_t reserved;
};


#pragma pack(push, 1)


// INITIALIZER
void * BITMAPV5HEADER_init()
{
    void * header = BMP_malloc(sizeof(struct BITMAPV5HEADER), "Cannot init infoheader");

    memset(header, 0, DIB_BITMAPV5HEADER_SIZE);

    ((struct BITMAPV5HEADER *) header) -> header_size = DIB_BITMAPV5HEADER_SIZE;

    return header;
}

// HEADER SIZE

uint32_t BITMAPV5HEADER_get_header_size(void * f)
{
    return ((struct BITMAPV5HEADER *) f) -> header_size;
}

// WIDTH
void BITMAPV5HEADER_set_width(void * f, int32_t w)
{
    ((struct BITMAPV5HEADER *) f) -> width = w;
}

int32_t BITMAPV5HEADER_get_width(void * f)
{
    return ((struct BITMAPV5HEADER *) f) -> width;
}

// HEIGHT
void BITMAPV5HEADER_set_height(void * f, int32_t h)
{
    ((struct BITMAPV5HEADER *) f) -> height = h;
}

int32_t BITMAPV5HEADER_get_height(void * f)
{
    return ((struct BITMAPV5HEADER *) f) -> height;
}

// COLOR PLANES
void BITMAPV5HEADER_set_color_planes(void * f, uint16_t cp)
{
    ((struct BITMAPV5HEADER *) f) -> color_planes = cp;
}

uint16_t BITMAPV5HEADER_get_color_planes(void * f)
{
    return ((struct BITMAPV5HEADER *) f) -> color_planes;
}

// COLOR DEPTH
void BITMAPV5HEADER_set_color_depth(void * f, uint16_t cd)
{
    ((struct BITMAPV5HEADER *) f) -> color_depth = cd;
}

uint16_t BITMAPV5HEADER_get_color_depth(void * f)
{
    return ((struct BITMAPV5HEADER *) f) -> color_depth;
}

// TODO: COMPRESSION METHOD

// IMAGE SIZE
void BITMAPV5HEADER_set_image_size(void * f, uint32_t s)
{
    ((struct BITMAPV5HEADER *) f) -> image_size = s;
}

uint32_t BITMAPV5HEADER_get_image_size(void * f)
{
    return ((struct BITMAPV5HEADER *) f) -> image_size;
}

// HORIZONTAL RESOLUTION
void BITMAPV5HEADER_set_horizontal_resolution(void * f, int32_t hr)
{
    ((struct BITMAPV5HEADER *) f) -> horizontal_resolution = hr;
}

int32_t BITMAPV5HEADER_get_horizontal_resolution(void * f)
{
    return ((struct BITMAPV5HEADER *) f) -> horizontal_resolution;
}

// VERTICAL RESOLUTION
void BITMAPV5HEADER_set_vertical_resolution(void * f, int32_t vr)
{
    ((struct BITMAPV5HEADER *) f) -> vertical_resolution = vr;
}

uint32_t BITMAPV5HEADER_get_vertical_resolution(void * f)
{
    return ((struct BITMAPV5HEADER *) f) -> vertical_resolution;
}

// NUMBER OF COLORS
void BITMAPV5HEADER_set_ncolors(void * f, uint32_t nc)
{
    ((struct BITMAPV5HEADER *) f) -> ncolors = nc;
}

uint32_t BITMAPV5HEADER_get_ncolors(void * f)
{
    return ((struct BITMAPV5HEADER *) f) -> ncolors;
}

// TODO: IMPORTANT COLORS
