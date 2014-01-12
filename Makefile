CC = gcc
CFLAGS = -Wall -pedantic -g

memory: main.c game.o ui.o
	gcc main.c game.o ui.o `sdl-config --libs` -lSDL_image -o memory

clean:
	rm -f *.o
