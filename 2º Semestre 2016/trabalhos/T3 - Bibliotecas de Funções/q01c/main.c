#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "libprimo.h"

int main() {

	int opcao;
	int suposto_primo;
	void *lib_handle;
	int (*resultado)();
	int (*primo)(int);
	char *error;

	lib_handle = dlopen("./libprimo.so", RTLD_LAZY);

	if (!lib_handle) {
	  fprintf(stderr, "%s\n", dlerror());
	  exit(1);
	}

	while(1){
		printf("1) Gerar primo.\n");
		printf("2) Testar primo.\n");
		printf("0) Sair.\n");
		scanf("%d", &opcao);

		if(opcao == 1) {

			resultado = dlsym(lib_handle, "gera_primo");
			if ((error = dlerror()) != NULL) {
				fprintf(stderr, "%s\n", error);
				exit(1);
			}

			printf("%d\n", (*resultado)());
		}
		else if(opcao == 2) {
			printf("Escreva o suposto primo\n");
			scanf("%d", &suposto_primo);

			primo = dlsym(lib_handle, "testa_primo");
			if ((error = dlerror()) != NULL) {
				fprintf(stderr, "%s\n", error);
				exit(1);
			}

			if ((*primo)(suposto_primo)) {
				printf("%d é primo.\n", suposto_primo);
			}
			else{
				printf("%d não é primo.\n", suposto_primo);
			}
		}
		else {
			return 0;
		}
	}

	dlclose(lib_handle);
	return 0;
}
