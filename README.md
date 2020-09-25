# BitMap
A simple library to create bmp images. Aimed to my learning process of image processing.

### Use
Compiled with gcc on Ubuntu 20.04LTS - WSL2 using:
```shell
    gcc name_of_the_script.c -o executable
```
If some flags are use they are specified at the top comment in that file.

### Conventions
||Format|
|---|---|
|struct|PascalCase|
|enum|SNAKE_CASE|
|constants|SNAKE_CASE|
|'public' functions|BMP_snake_case|
|'private' functions|_snake_case|

> public functions are those meant to be call by the user.
  on the other hand, private functions are meant to be call
  by the public functions.

### Examples
#### RBG Color Square in 16 and 24 bit
![Four color square 16 bit depth](examples/colors16.bmp)
![Four color square 24 bit depth](examples/colors24.bmp)


### Currently Supported
* BITMAPINFOHEADER with color depth of 16 bit and 24 bit.

### Todo:
* Support for BITMAPV5HEADER (gimp).
* A way to store and read color palettes for color depth <= 8.
* Give the option to override or concatenated (ncopy) 
  at the end of the filename.
