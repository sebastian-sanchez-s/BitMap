#include <stdlib.h>
#include <stdint.h>

#include "BMP_error.h"


unsigned char * read_pallet_from_file(uint32_t color_depth, const char * filename)
{
    FILE * fd = fopen(filename, "rb");

    if (!fd)
    {
        BMP_perror("Cannot read pallet");
    }

    size_t bytes_to_read = (1 << color_depth); 

    char buffer[bytes_to_read];

    fread(buffer, sizeof(char), bytes_to_read, fd); 

    for (int byte = 0; byte < bytes_to_read; byte++)
    {
        printf("Byte %i -> %c\n", byte, buffer[byte]);
    }

    fclose(fd);
}
