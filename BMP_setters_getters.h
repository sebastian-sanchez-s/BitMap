// INFOHEADER
int32_t BMP_get_infoheader_size(struct BMP * image)
{
    return (_get_header_size[image->dib_type])(image->infoheader);
}

// WIDTH
void BMP_set_width(struct BMP * image, int32_t width)
{
    (_set_width[image->dib_type])(image->infoheader, width);
}

uint32_t BMP_get_width(struct BMP * image)
{
    return (_get_width[image->dib_type])(image->infoheader);
}

// HEIGHT
void BMP_set_height(struct BMP * image, int32_t height)
{
    (_set_height[image->dib_type])(image->infoheader, height);
}

uint32_t BMP_get_height(struct BMP * image)
{
    return (_get_height[image->dib_type])(image->infoheader);
}

// COLOR PLANES
void BMP_set_color_planes(struct BMP * image, uint16_t planes)
{
    (_set_color_planes[image->dib_type])(image->infoheader, planes);
}

uint16_t BMP_get_color_planes(struct BMP * image)
{
    return (_get_color_planes[image->dib_type])(image->infoheader);
}


// COLOR DEPTH
void BMP_set_color_depth(struct BMP * image, uint16_t depth)
{
    (_set_color_depth[image->dib_type])(image->infoheader, depth);
}

uint16_t BMP_get_color_depth(struct BMP * image)
{
    return (_get_color_depth[image->dib_type])(image->infoheader);
}

// IMAGE SIZE
void BMP_set_image_size(struct BMP * image, uint32_t size)
{
    (_set_image_size[image->dib_type])(image->infoheader, size);
}

uint32_t BMP_get_image_size(struct BMP * image)
{
    return (_get_image_size[image->dib_type])(image->infoheader);
}
