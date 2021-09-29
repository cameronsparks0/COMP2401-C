all: main util
	gcc -pthread -o assignment3 assignment3.o assignment3functions.o
main: assignment3.c pokemon.h
	gcc -c assignment3.c
util: assignment3functions.c pokemon.h
	gcc -c assignment3functions.c