#include "BMP_error.h"


void * BMP_malloc(size_t size, const char * msg_failed) {
    void * bodyguard = malloc(size);

    if (!bodyguard) {
        BMP_perror(msg_failed);
    }

    return bodyguard;
}
