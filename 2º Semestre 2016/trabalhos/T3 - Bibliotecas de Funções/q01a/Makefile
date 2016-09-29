main:
	gcc -c libprimo.c 
	ar cr libprimo.a libprimo.o
	gcc -c main.c
	gcc -o main main.o -L. -lprimo

clean:
	rm *.o libprimo.a main
