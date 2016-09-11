#include <stdio.h>
#include <string.h>
#include "data_io.h"

int main(int argc, char **argv){

	int list_size = 0;

	print_list_integers(list_size, read_list(&list_size, argc, argv));

	return 0;
}