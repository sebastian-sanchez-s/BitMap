#include "BMP_color.h"
#include "BMP_lib.h"

struct Color * add_colors(struct Color a, struct Color b) {
    struct Color * ab = BMP_malloc(sizeof(struct Color), "Cannot add colors\n");

    ab->red = a.red + b.red;
    ab->blue = a.blue + b.blue;
    ab->green = a.green + b.green;
    
    return ab;
}
