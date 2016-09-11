#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>

int w[100];
int x[100];

struct pair{

	int i;
	int j;
};

void fill_array(int index);

void* compare(struct pair pair);

struct pair create_pair(int i, int j);

void* print_biggest(int index);

/**
	Cópia do programa sequence.c, modificado para não utilização de threads.
*/

int main(int argc, char **argv){

	int n = atoi(argv[1]);
	int i,j;

	struct pair pair; 

	assert( n <= 100 ); assert( n > 0 ); // Programação defensiva.

	// Etapa 1.
	for ( i = 0; i < n; i++ ){

		fill_array(i);

		assert(argv[i+2] != NULL); // Programação defensiva.

		x[i] = atoi(argv[i+2]); // Preenche o array x[i], optei pela não 
								// utilização de threads pois o enúnciado
								// do problema não diz nada a respeito.
	}

	printf("Number of input values = %d\n", n);
	printf("Input values x =");

	for ( i = 0; i < n; i++ )
		printf(" %d", x[i]);

	printf("\nAfter inicialization w =");

	for ( i = 0; i < n; i++ )
		printf(" %d", w[i]);

	printf("\n");
	// ==================================================================

	// Etapa 2.
	for ( i = 0; i < n; i++ )
		for ( j = i + 1; j < n; j++ ){

			struct pair pair = create_pair(i, j);
			compare(pair);
		}
	// ==================================================================
	printf("After Step 2\n");
	printf("w =");

	for ( i = 0; i < n; i++ )
		printf(" %d", w[i]);

	printf("\n");

	// Etapa 3.
	for ( i = 0; i < n; i++ ){

		print_biggest(i);
	}

	return 0;
}

void fill_array(int index){

	w[index] = 1;
}

void* compare(struct pair pair){

	int i = pair.i;
	int j = pair.j;

	if ( x[i] < x[j] ){

		printf("Thread T(%d,%d) compares x[%d] = %d and x[%d] = %d, and writes 0 into w[%d]\n", i,j,i,x[i],j,x[j],i);

		w[i] = 0;
	}
	else{

		printf("Thread T(%d,%d) compares x[%d] = %d and x[%d] = %d, and writes 0 into w[%d]\n", i,j,i,x[i],j,x[j],j);

		w[j] = 0;
	}

	// int teste = 100000;
	// while(teste--);
}

struct pair create_pair(int i, int j){

	return (struct pair) {.i = i, .j = j};
}

void* print_biggest(int index){

	if ( w[index] == 1 ){
		printf("Maximum = %d\n", x[index]);
		printf("Location = %d\n", index);
	}
	else
		return NULL;
}