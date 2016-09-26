#include "libprimo.h"

int gera_primo(){

	int p = rand();
	srand (time(NULL));

	while ( !testa_primo(p) ){

		p = rand();
	}

	return p;
}

int testa_primo(int primo){

	if ( primo == 2 )
		return 1;
	if ( primo == 3 )
		return 1;
	if ( primo % 2 == 0 )
		return 0;
	if ( primo % 3 == 0 )
		return 0;

	int i = 5;
	int j = 2;

	while ( i * i <= primo ){

		if ( primo % i == 0 )
			return 0;

		i += j;
		j = 6 - j;
	}

	return 1;
}