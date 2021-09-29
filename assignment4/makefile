all: main util
	gcc -o pps server.o serverFunctions.o
	gcc -pthread -o pqc client.o clientFunctions.o
main: server.c client.c client.h server.h
	gcc -c server.c
	gcc -c client.c
util: serverFunctions.c clientFunctions.c client.h server.h
	gcc -c serverFunctions.c
	gcc -c clientFunctions.c