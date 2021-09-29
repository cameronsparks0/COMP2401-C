myExec: main.o person.o mystat.o
	gcc -o myExec main.o person.o mystat.o

person.o: person.c person.h mystat.h
	gcc -c person.c

mystat.o: mystat.c mystat.h
	gcc -c mystat.c

main.o: main.c person.h
	gcc -c main.c

clean:
	rm -f *.o