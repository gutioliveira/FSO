main:
	gcc -fPIC -c *.c
	gcc -shared -o libprimo.so  *.o
	gcc -L. -Wl,-rpath=. main.c -o gera_primo -lprimo

clean:
	rm -rf *.o gera_primo libprimo.so
