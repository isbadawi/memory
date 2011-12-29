CC = gcc
CFLAGS = -Wall -pedantic -g

memory: main.c game.o icons.o
	gcc main.c game.o icons.o -lSDL -lSDL_image -o memory

clean:
	rm *.o
