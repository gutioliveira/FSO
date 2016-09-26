main:
	gcc -fPIC -c *.c
	gcc -shared -o libprimo.so  *.o
	gcc -rdynamic -o gera_primo main.c -ldl

clean:
	rm -rf *.o gera_primo libprimo.so
