#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>

#define MAX 4955 // Número máximo de threads possíveis.

int w[100];
int x[100];

struct pair{

	int i;
	int j;
};

void* fill_array(void *index);

void* compare(void *pair);

struct pair create_pair(int i, int j);

void* print_biggest(void *index);

int main(int argc, char **argv){

	int n = atoi(argv[1]);
	int i,j; 

	assert( n <= 100 ); assert( n > 0 ); // Programação defensiva.

	pthread_t thread_id[MAX];
	struct pair pair[MAX];

	int vector_aux[100]; // Utilizado para preencher o vetor w.
	
	for ( i = 0; i < n; i++ ){

		vector_aux[i] = i;

		pthread_create(&thread_id[i], NULL, 
			&fill_array, &vector_aux[i]);// Faz a thread executar a função fill_array.

		assert(argv[i+2] != NULL); // Programação defensiva.

		x[i] = atoi(argv[i+2]); // Preenche o array x[i], optei pela não 
								// utilização de threads pois o enúnciado
								// do problema não diz nada a respeito.
	}

	for ( i = 0; i < n; i++ ) // Processo principal espera as threads finalizarem.
		pthread_join(thread_id[i], NULL);

	// Optei por não usar threads na hora de printar os valores de x e w.
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

	int aux = 0;

	for ( i = 0; i < n; i++ )
		for ( j = i + 1; j < n; j++ , aux++ ){

			pair[aux] = create_pair(i,j);
			pthread_create(&thread_id[aux], NULL, &compare, &pair[aux]);
		}

	for ( i = 0; i < aux; i++ ) // Processo principal espera as threads finalizarem.
		pthread_join(thread_id[i], NULL);

	// ==================================================================
	printf("After Step 2\n");
	printf("w =");

	for ( i = 0; i < n; i++ )
		printf(" %d", w[i]);

	printf("\n");

	// Etapa 3.
	for ( i = 0; i < n; i++ ){

		pthread_create(&thread_id[i], NULL, &print_biggest, &vector_aux[i]);
	}

	for ( i = 0; i < n; i++ )
		pthread_join(thread_id[i], NULL);

	return 0;
}

void* fill_array(void *index){

	w[*((int*) index)] = 1;
}

void* compare(void *pair){

	int i = (*((struct pair*) pair)).i;
	int j = (*((struct pair*) pair)).j;

	if ( x[i] < x[j] ){

		printf("Thread T(%d,%d) compares x[%d] = %d and x[%d] = %d, and writes 0 into w[%d]\n", i,j,i,x[i],j,x[j],i);

		w[i] = 0;
	}else{

		printf("Thread T(%d,%d) compares x[%d] = %d and x[%d] = %d, and writes 0 into w[%d]\n", i,j,i,x[i],j,x[j],j);

		w[j] = 0;
	}

	// int teste = 100000;
	// while(teste--);
}

struct pair create_pair(int i, int j){

	return (struct pair) {.i = i, .j = j};
}

void* print_biggest(void *index){

	if ( w[*((int*) index)] == 1 ){
		printf("Maximum = %d\n", x[*((int*) index)]);
		printf("Location = %d\n", *((int*) index));
	}else
		return NULL;
}