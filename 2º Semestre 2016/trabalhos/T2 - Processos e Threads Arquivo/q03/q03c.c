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

void* fill_matrix(void *index){

	struct pair *p = (struct pair*) index;

	int iaux = (*p).i;
	int jaux = (*p).j;

	int teste = 0;

	int kteste;

	for ( kteste = 0; kteste < row2; kteste++ ){

		teste += x[iaux][kteste] * y[kteste][jaux];
	}

	int teste2 = 1000000;

	// while(teste2--);

	// w[iaux][jaux] = teste;
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

	int iaux = 0;
	int jaux = 0;
	int number_threads = 0;

	pthread_t thread_id[4];

	int aux = 0;

	struct pair *pair = (struct pair*) malloc ( sizeof(struct pair) * row1 * column2 );

	for ( i = 0; i < row1; i++ )
		for ( j = 0; j < column2; j++, number_threads++ ){

			pair[aux] = create_pair(i,j);

			pthread_create(&(thread_id[number_threads]), NULL, 
			&fill_matrix, &pair[aux]);

			aux++;

			if ( number_threads == (4 - 1) ){ // Solução em software para limitar o número
											  // de threads concorrentes.

				int index;

				number_threads = 0;

				for ( index = 0; index < 4; index++ )
					pthread_join(thread_id[index], NULL);

			}
		}

	int index;

	if ( number_threads != 0 ) // Caso sobre threads.
		for ( index = number_threads; index < 4; index++ )
			pthread_join(thread_id[index], NULL);

	printf("Result:\n");

	for ( i = 0; i < row1; i++ ){
		for ( j = 0; j < column2; j++ ){

			printf(" %d", w[i][j]);
		}

		printf("\n");
	}
		
	return 0;
}