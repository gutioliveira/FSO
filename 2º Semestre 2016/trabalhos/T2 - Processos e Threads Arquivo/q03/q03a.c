#include <stdio.h>
#include <assert.h>

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


	for ( i = 0; i < row1; i++ )
		for ( j = 0; j < column2; j++ ){

			struct pair pair = create_pair(i,j);

			fill_matrix(&pair);
		}

	printf("Result:\n");

	for ( i = 0; i < row1; i++ ){
		for ( j = 0; j < column2; j++ ){

			printf(" %d", w[i][j]);
		}

		printf("\n");
	}
		
	return 0;
}