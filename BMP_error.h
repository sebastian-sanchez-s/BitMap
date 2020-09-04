#include <stdio.h>  // fprintf
#include <stdlib.h> // exit()

void BMP_perror(const char * errmsg)
{
    fprintf(stderr, "Error: %s\n", errmsg);
    exit(0);
}
