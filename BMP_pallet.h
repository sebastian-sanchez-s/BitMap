#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "BMP_error.h"


int char2hex(char);


unsigned char * read_pallet_from_file(uint32_t color_depth, const char * filename)
{
    FILE * fd = fopen(filename, "rb");

    if (!fd)
    {
        BMP_perror("Cannot read pallet");
    }

    size_t bytes_to_read = (1 << color_depth); 

    char buffer[bytes_to_read];
    memset(buffer, 0, bytes_to_read);

    fread(buffer, sizeof(char), bytes_to_read, fd); 
    fclose(fd);

    unsigned char * color_pallet = malloc(strlen(buffer));

    for (int byte = 0; byte < strlen(buffer); byte++)
    {
        color_pallet[byte] = char2hex(buffer[byte]);
    }
    
    return color_pallet;
}


int char2hex(char c)
{
    switch (c)
    {
        case '0': return 0x0; break;
        case '1': return 0x1; break;
        case '2': return 0x2; break;
        case '3': return 0x3; break;
        case '4': return 0x4; break;
        case '5': return 0x5; break;
        case '6': return 0x6; break;
        case '7': return 0x7; break;
        case '8': return 0x0; break;
        case '9': return 0x1; break;
        case 'a':
        case 'A': return 0xa; break;
        case 'b':
        case 'B': return 0xb; break;
        case 'c':
        case 'C': return 0xc; break;
        case 'd':
        case 'D': return 0xd; break;
        case 'e': 
        case 'E': return 0xe; break;
        case 'f': 
        case 'F': return 0xf; break;
        default: return 0x0; break;
    }
}


