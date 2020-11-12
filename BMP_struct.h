#define BMP_SIGNATURE               0x4d42
#define BMP_FILEHEADER_SIZE         14

#pragma pack(push, 1)

struct FILEHEADER {
    uint16_t signature; 
    uint32_t file_size; 
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;                      // where pixel_data begins (fileheader + infoheader)
};

struct BMP {
    struct FILEHEADER * fileheader;
    void * infoheader;                   // DIB it's determinate on creation 
    unsigned char * pixel_data;               
    enum DIB_TYPES dib_type;             // that's why we have a tracker
};

#pragma pack(pop)


