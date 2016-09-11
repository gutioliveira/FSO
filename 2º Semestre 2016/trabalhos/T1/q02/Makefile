main: data_io.o sort_list.o main.o
	gcc -o main main.o sort_list.o data_io.o

sort_list.o:
	gcc -c sort_list.c

main.o:
	gcc -c main.c

data_io.o:
	gcc -c data_io.c

clean:
	rm -f *.o main