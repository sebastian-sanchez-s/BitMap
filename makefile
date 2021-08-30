CC=gcc
CFLAGS=-c -Werror -Iincludes/
OBJS=BMP.o BMP_color.o BMP_error.o BMP_lib.o BMP_infoheader.o

all: libbmp.a

libbmp.a: $(OBJS)
	ar -rcs $@ $^
	rm *.o

%.o: src/%.c
	$(CC) $(CFLAGS) $^

clean:
	rm *.gch *.o libbmp.a
