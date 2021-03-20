CC=gcc
CFLAGS=-c -Werror -Ilib

all: libbmp.a

libbmp.a:	BMP.o BMP_color.o BMP_error.o BMP_lib.o BMP_infoheader.o
	ar -rcs $@ $^

%.o: src/%.c
	$(CC) $(CFLAGS) $^

clean:
	rm *.gch *.o libbmp.a
