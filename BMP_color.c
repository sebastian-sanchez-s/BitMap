#include <stdio.h>
#include "BMP_color.h"
#include "BMP_lib.h"

struct Color * BMP_color_add(struct Color * result, int nadding, struct Color add_1, ...) {
    va_list colors_add;

    result -> red = 0;
    result -> blue = 0;
    result -> green = 0;

    struct Color curr_color;
    
    va_start(colors_add, add_1);

    for (curr_color = add_1; nadding > 0; nadding--, curr_color = va_arg(colors_add, struct Color))
    {
        result -> red += curr_color.red;
        result -> green += curr_color.green;
        result -> blue += curr_color.blue;
    }

    va_end(colors_add);

    return result;
}

struct Color * BMP_color_complement(struct Color * result, struct Color color) {
    result -> red = ~color.red;
    result -> green = ~color.green;
    result -> blue = ~color.blue;

    return result;
}
