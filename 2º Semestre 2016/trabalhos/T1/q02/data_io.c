#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void print_list_integers(int size_of_list, int *list){

	int i;

	printf("list sorted\n");

	for ( i = 0; i < size_of_list; i++ )
		printf("%d\n", list[i]);

	free(list);
}

int *read_list(int *list_size, int argc, char **argv){

	int *list, i, j;

	assert(argc > 1);

	if ( strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "-r") == 0 ){

		*list_size = argc - 2;

		list = (int*) malloc (sizeof(int) * ( (*list_size) ) );

		for ( i = 2, j = 0; i < argc; i++, j++ )
			list[j] = atoi(argv[i]);

		list = strcmp(argv[1], "-d") == 0 ? sort_list(*list_size, list) : sort_list_decreasing(*list_size, list);

	}else{

		*list_size = argc - 1;
		list = (int*) malloc (sizeof(int) * ( (*list_size) ) );

		for ( i = 1, j = 0; i < argc; i++, j++ )
			list[j] = atoi(argv[i]);

		list = sort_list(*list_size, list);
	}

	return list;
}
