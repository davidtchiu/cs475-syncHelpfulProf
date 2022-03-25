all: main.o actors.o
	gcc -o helpfulprof main.c actors.o -lpthread

actors.o: actors.c actors.h
	gcc -c actors.c

clean:
	rm -Rf *.o helpfulprof
