main: sthreads nothreads

sthreads:
	gcc -o sthreads sequence.c -lpthread

nothreads:
	gcc -o nothreads sequence_without_threads.c 

clean:
	rm -f sthreads nothreads
