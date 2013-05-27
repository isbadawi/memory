CC = gcc
CFLAGS = -Wall -pedantic -g

memory: main.c game.o icons.o
	gcc main.c game.o icons.o `sdl-config --libs` -lSDL_image -o memory

clean:
	rm *.o
