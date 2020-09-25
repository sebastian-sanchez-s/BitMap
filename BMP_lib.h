void * BMP_malloc(size_t size, const char * msg_failed) {
    void * bodyguard = malloc(size);

    if (!bodyguard) {
        BMP_perror(msg_failed);
    }

    return bodyguard;
}

void * BMP_open(const char * filename, const char * mode)
{
    FILE * file = fopen(filename, mode);

    if (!file)
    {
        BMP_perror("Coudn't create file");
    }

    return file;
}
