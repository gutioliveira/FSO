main: geometric_operations.o data_io.o main.o
	gcc -o main main.o data_io.o geometric_operations.o -lm

geometric_operations.o:
	gcc -c geometric_operations.c -lm

data_io.o:
	gcc -c data_io.c

main.o:
	gcc -c main.c -std=gnu99

clean:
	rm -f *.o main