/* COLOR MACROS */
#define MAX_COLOR_24    255
#define MAX_COLOR_16    31

/* RGB555 */
#define RGB555_MASK             0x1f                        // (0.000)(00.00)(000.1)(1111) ; dots 5 bits set; () 4 bit set  
#define RGB555_MASK_RED(x)      ((x & RGB555_MASK) << 10)
#define RGB555_MASK_GREEN(x)    ((x & RGB555_MASK) << 5)
#define RGB555_MASK_BLUE(x)     ((x & RGB555_MASK))

/* RGB888 */
#define RGB888_MASK             0xff
#define RGB888_MASK_RED(x)      ((x & RGB888_MASK) << 16)
#define RGB888_MASK_GREEN(x)    ((x & RGB888_MASK) << 8)
#define RGB888_MASK_BLUE(x)     ((x & RGB888_MASK))

struct Color {
    uint32_t blue;
    uint32_t green;
    uint32_t red;
};

