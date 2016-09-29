main:
	gcc -c libprimo.c
	ar cr libprimo.a libprimo.o
	gcc -c main.c
	gcc -o gera_primo main.o -L. -lprimo

clean:
	rm *.o libprimo.a gera_primo
