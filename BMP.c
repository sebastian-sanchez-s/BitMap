
#include <stdio.h>          // FILE, fprintf family
#include <stdint.h>         // intXX
#include <stdlib.h>         // free

#include "BMP.h"
#include "BMP_error.h"      // BMP_perror
#include "BMP_lib.h"        // BMP_malloc, BMP_open
#include "BMP_infoheader.c"


#define DEBUG 1
#define DEBUG_PRINT(x) if (DEBUG) {printf("%s\n", x);}


uint32_t width_in_bytes(struct BMP * image)
{
    return ((BMP_get_width(image) * BMP_get_color_depth(image) + 31)/32) * 4;
}


void setup_fileheader(struct BMP * image)
{
    DEBUG_PRINT("Setup fileheader...")

    image -> fileheader = BMP_malloc(sizeof(struct FILEHEADER), "Cannot create fileheader");

    image -> fileheader -> signature = BMP_SIGNATURE;
    image -> fileheader -> file_size = BMP_FILEHEADER_SIZE + BMP_get_infoheader_size(image) + BMP_get_image_size(image);
    image -> fileheader -> offset = BMP_FILEHEADER_SIZE + BMP_get_infoheader_size(image);

    DEBUG_PRINT("Fileheader created.")
}


void setup_infoheader(struct BMP * image, int32_t width, int32_t height, uint16_t color_depth)
{
    DEBUG_PRINT("Setup infoheader...")

    image -> infoheader = (*init_infoheader[image->dib_type])();

    BMP_set_color_planes(image, 1);
    BMP_set_width(image, width);
    BMP_set_height(image, height);
    BMP_set_color_depth(image, color_depth);
    BMP_set_image_size(image, width_in_bytes(image) * abs(height));

    DEBUG_PRINT("Infoheader created.")
}


struct BMP * BMP_create(int32_t width, int32_t height, uint16_t color_depth, enum DIB_TYPES dib_type)
{
    DEBUG_PRINT("Creating image")

    struct BMP * image = BMP_malloc(sizeof(struct BMP), "Cannot create image");

    image -> dib_type = dib_type;

    setup_infoheader(image, width, height, color_depth);
    setup_fileheader(image);

    image -> pixel_data = BMP_malloc(BMP_get_image_size(image), "Cannot create pixel data");

    memset(image -> pixel_data, 0, BMP_get_image_size(image));

    DEBUG_PRINT("Image created.")
    
    printf("Fileheader\n");
    printf("\tsignature: %x\n", image -> fileheader -> signature);
    printf("\tfile size: %i\n", image -> fileheader -> file_size);
    printf("\toffset   : %i\n", image -> fileheader -> offset);

    printf("Infoheader\n");
    printf("\theader size : %i\n", BMP_get_infoheader_size(image));
    printf("\tcolor planes: %i\n", BMP_get_color_planes(image));
    printf("\timage size  : %i\n", BMP_get_image_size(image));
    printf("\tcolor depth : %i\n", BMP_get_color_depth(image));

    return image;
}


void BMP_save_without_free(struct BMP * image, const char * filename)
{
    DEBUG_PRINT("Saving image...")

    FILE * output = BMP_open(filename, "wb");

    fwrite(image -> fileheader, BMP_FILEHEADER_SIZE, 1, output);
    fwrite(image -> infoheader, BMP_get_infoheader_size(image), 1, output);
    fwrite(image -> pixel_data, BMP_get_image_size(image), 1, output);

    fclose(output);

    DEBUG_PRINT("Image saved.")
}


void BMP_save(struct BMP * image, const char * filename)
{
    BMP_save_without_free(image, filename);

    DEBUG_PRINT("Freeing memory...")

    free(image -> fileheader);
    free(image -> infoheader);
    free(image -> pixel_data);
    free(image);

    DEBUG_PRINT("Memory freed.")
}


void BMP_set_pixel(struct BMP * image, int row, int col, struct Color color)
{
    uint16_t depth_in_bits = BMP_get_color_depth(image);
    uint16_t depth_in_bytes = (depth_in_bits+7)/8;
    int32_t offset = row * width_in_bytes(image) + col * depth_in_bytes; // pixel[row][col]

    /* Sanity check*/
    if (offset > BMP_get_image_size(image) || offset < 0)
    {
        BMP_perror("Pixel position out of range");
    }

    uint32_t true_color;
    /* The actual write */
    if (depth_in_bits == 32) {
        true_color = RGB888_MASK_RED(color.red) | RGB888_MASK_GREEN(color.green) | (RGB888_MASK_BLUE(color.blue)) | (RGB888_MASK_ALPHA(color.alpha));
    } else if (depth_in_bits == 24) {
        true_color = RGB888_MASK_RED(color.red) | RGB888_MASK_GREEN(color.green) | (RGB888_MASK_BLUE(color.blue));
    } else if (depth_in_bits == 16) {
        true_color = RGB555_MASK_RED(color.red) | RGB555_MASK_GREEN(color.green) | RGB555_MASK_BLUE(color.blue);
    }

    memcpy(image -> pixel_data + offset, &true_color, depth_in_bytes);
}


void BMP_set_background(struct BMP * image, struct Color color)
{
    int height = BMP_get_height(image);
    int width = BMP_get_width(image);

    for (int row = height - 1; row >= 0; row--)
    {
        for (int col = 0; col < width; col++)
        {
            BMP_set_pixel(image, row, col, color);
        }
    }
}


/***************************************************************
 *************** SETTERS AND GETTERS ***************************
 ***************************************************************/

int32_t BMP_get_infoheader_size(struct BMP * image)
{
    return (_get_header_size[image->dib_type])(image->infoheader);
}

void BMP_set_width(struct BMP * image, int32_t width)
{
    (_set_width[image->dib_type])(image->infoheader, width);
}

uint32_t BMP_get_width(struct BMP * image)
{
    return (_get_width[image->dib_type])(image->infoheader);
}

void BMP_set_height(struct BMP * image, int32_t height)
{
    (_set_height[image->dib_type])(image->infoheader, height);
}

uint32_t BMP_get_height(struct BMP * image)
{
    return (_get_height[image->dib_type])(image->infoheader);
}

void BMP_set_color_planes(struct BMP * image, uint16_t planes)
{
    (_set_color_planes[image->dib_type])(image->infoheader, planes);
}

uint16_t BMP_get_color_planes(struct BMP * image)
{
    return (_get_color_planes[image->dib_type])(image->infoheader);
}


void BMP_set_color_depth(struct BMP * image, uint16_t depth)
{
    (_set_color_depth[image->dib_type])(image->infoheader, depth);
}

uint16_t BMP_get_color_depth(struct BMP * image)
{
    return (_get_color_depth[image->dib_type])(image->infoheader);
}

void BMP_set_image_size(struct BMP * image, uint32_t size)
{
    (_set_image_size[image->dib_type])(image->infoheader, size);
}

uint32_t BMP_get_image_size(struct BMP * image)
{
    return (_get_image_size[image->dib_type])(image->infoheader);
}
