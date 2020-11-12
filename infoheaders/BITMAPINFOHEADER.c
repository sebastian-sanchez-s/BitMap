#define DIB_BITMAPINFOHEADER_SIZE   40

#pragma pack(push, 1)

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

#pragma pack(push, 1)

// INITIALIZER
void * BITMAPINFOHEADER_init()
{
    void * header = BMP_malloc(sizeof(struct BITMAPINFOHEADER), "Cannot init infoheader");
    
    memset(header, 0, DIB_BITMAPINFOHEADER_SIZE);

    ((struct BITMAPINFOHEADER *) header) -> header_size = DIB_BITMAPINFOHEADER_SIZE;

    return header;
}


// HEADER SIZE
uint32_t BITMAPINFOHEADER_get_header_size(void * f)
{
    return ((struct BITMAPINFOHEADER *) f) -> header_size;
}

// WIDTH
void BITMAPINFOHEADER_set_width(void * f, int32_t w)
{
    ((struct BITMAPINFOHEADER *) f) -> width = w;
}

int32_t BITMAPINFOHEADER_get_width(void * f)
{
    return ((struct BITMAPINFOHEADER *) f) -> width;
}

// HEIGHT
void BITMAPINFOHEADER_set_height(void * f, int32_t h)
{
    ((struct BITMAPINFOHEADER *) f) -> height = h;
}

int32_t BITMAPINFOHEADER_get_height(void * f)
{
    return ((struct BITMAPINFOHEADER *) f) -> height;
}

// COLOR PLANES
void BITMAPINFOHEADER_set_color_planes(void * f, uint16_t cp)
{
    ((struct BITMAPINFOHEADER *) f) -> color_planes = cp;
}

uint16_t BITMAPINFOHEADER_get_color_planes(void * f)
{
    return ((struct BITMAPINFOHEADER *) f) -> color_planes;
}

// COLOR DEPTH
void BITMAPINFOHEADER_set_color_depth(void * f, uint16_t cd)
{
    ((struct BITMAPINFOHEADER *) f) -> color_depth = cd;
}

uint16_t BITMAPINFOHEADER_get_color_depth(void * f)
{
    return ((struct BITMAPINFOHEADER *) f) -> color_depth;
}

// TODO: COMPRESSION METHOD

// IMAGE SIZE
void BITMAPINFOHEADER_set_image_size(void * f, uint32_t s)
{
    ((struct BITMAPINFOHEADER *) f) -> image_size = s;
}

uint32_t BITMAPINFOHEADER_get_image_size(void * f)
{
    return ((struct BITMAPINFOHEADER *) f) -> image_size;
}

// HORIZONTAL RESOLUTION
void BITMAPINFOHEADER_set_horizontal_resolution(void * f, int32_t hr)
{
    ((struct BITMAPINFOHEADER *) f) -> horizontal_resolution = hr;
}

int32_t BITMAPINFOHEADER_get_horizontal_resolution(void * f)
{
    return ((struct BITMAPINFOHEADER *) f) -> horizontal_resolution;
}

// VERTICAL RESOLUTION
void BITMAPINFOHEADER_set_vertical_resolution(void * f, int32_t vr)
{
    ((struct BITMAPINFOHEADER *) f) -> vertical_resolution = vr;
}

int32_t BITMAPINFOHEADER_get_vertical_resolution(void * f)
{
    return ((struct BITMAPINFOHEADER *) f) -> vertical_resolution;
}

// NUMBER OF COLORS
void BITMAPINFOHEADER_set_ncolors(void * f, uint32_t nc)
{
    ((struct BITMAPINFOHEADER *) f) -> ncolors = nc;
}

uint32_t BITMAPINFOHEADER_get_ncolors(void * f)
{
    return ((struct BITMAPINFOHEADER *) f) -> ncolors;
}

// TODO: IMPORTANT COLORS
