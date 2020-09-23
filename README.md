# BitMap
A simple library to create bmp images. Aimed to my learning process of image processing.

## Examples
#### Red gradient in 24 bit and 16 bit.
![red_gradient_24bit_BITMAPINFOHEADER](playground/red_gradient24.bmp)
![red_gradient_16bit_BITMAPINFOHEADER](playground/red_gradient16.bmp)

> You can make them the same size, but that's going to be a 7905x7095 ~ 170 MB.

### Currently Supported
* BITMAPINFOHEADER with color depth of 16 bit and 24 bit.

### Todo:
* Support for BITMAPV5HEADER (gimp).
* A way to store and read color palettes for color depth <= 8.
