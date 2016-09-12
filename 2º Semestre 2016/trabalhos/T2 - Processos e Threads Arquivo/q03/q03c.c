#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <assert.h>
#include <unistd.h>
#include <pthread.h>

#define MAX 1000

int row1, column1;
int row2, column2;
int i,j,k;
int aux = 0;
int x[MAX][MAX];
int y[MAX][MAX];
int w[MAX][MAX];

struct pair{

	int i, j;
};

// Faz a multiplicação na célula [i][j] passado como index.
void* fill_matrix(void *index){

	struct pair *p = (struct pair*) index;

	int iaux = (*p).i;
	int jaux = (*p).j;

	int value = 0;

	int kaux;

	for ( kaux = 0; kaux < row2; kaux++ ){

		value += x[iaux][kaux] * y[kaux][jaux];
	}

	// int teste2 = 1000000;

	// while(teste2--);

	w[iaux][jaux] = value;
}

struct pair create_pair(int i, int j){

	return (struct pair) {.i = i, .j = j};
}

int main(){

	printf("enter the number of rows and columns for the first matrix.\n");
	scanf("%d %d", &row1, &column1);
	printf("enter the number of rows and columns for the second matrix.\n");
	scanf("%d %d", &row2, &column2);

	assert( column1 == row2 );

	printf("enter the first matrix\n");
	for ( i = 0; i < row1; i++ )
		for ( j = 0; j < column1; j++ )
			scanf("%d", &x[i][j]);

	printf("enter the second matrix\n");
	for ( i = 0; i < row2; i++ )
		for ( j = 0; j < column2; j++ )
			scanf("%d", &y[i][j]);

	int number_threads = 0; // usado como auxliar para indicar qual das 4 threads utilizar.

	pthread_t thread_id[4];

	int aux = 0;

	struct pair *pair = (struct pair*) malloc ( sizeof(struct pair) * row1 * column2 );

	for ( i = 0; i < row1; i++ )
		for ( j = 0; j < column2; j++, number_threads++ ){

			pair[aux] = create_pair(i,j);

			pthread_create(&(thread_id[number_threads]), NULL, 
			&fill_matrix, &pair[aux]); // faz a thread executar a função full_matrix.

			aux++;

			// number_threads = 3 significa que é a quarta thread concorrente.
			if ( number_threads == 3 ){ // Solução em software para limitar o número
											  // de threads concorrentes.

				int index;

				number_threads = 0;

				for ( index = 0; index < 4; index++ )
					pthread_join(thread_id[index], NULL);

			}
		}

	int index;

	// Faz o processo esperar as threads que sobraram do for duplo anterior.
	if ( number_threads != 0 )
		for ( index = number_threads - 1; index < 4; index++ )
				pthread_join(thread_id[index], NULL);

	free(pair);

	printf("Result:\n");

	for ( i = 0; i < row1; i++ ){
		for ( j = 0; j < column2; j++ ){

			printf(" %d", w[i][j]);
		}

		printf("\n");
	}
		
	return 0;
}