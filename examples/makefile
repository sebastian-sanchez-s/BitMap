CC=gcc
CFLAGS=-I../includes -L../ -lbmp -lm
VIEW=viewnior

%: %.c
	$(CC) $< $(CFLAGS) -o app
	./app
