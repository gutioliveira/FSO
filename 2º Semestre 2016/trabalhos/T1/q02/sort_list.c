#include "sort_list.h"

int compare_less(const void *a, const void *b){

	return ( *(int*)a - *(int*)b );
}

int compare_greater(const void *a, const void *b){
	
	return ( *(int*)b - *(int*)a );
}

int * sort_list(int list_size, int *list){

	qsort(list, list_size, sizeof(int), compare_less);

	return list;
}

int *sort_list_decreasing(int list_size, int *list){

	qsort(list, list_size, sizeof(int), compare_greater);

	return list;
}