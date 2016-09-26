#include <stdio.h>

int main(){

	int opcao;
	int suposto_primo;

	while(1){

		printf("1) Gerar primo.\n");
		printf("2) Testar primo.\n");
		printf("0) Sair.\n");

		scanf("%d", &opcao);

		if ( opcao == 1 )
			printf("%d\n", gera_primo());
		else if ( opcao == 2 ){

			printf("Escreva o suposto primo\n");
			scanf("%d", &suposto_primo);

			if ( testa_primo(suposto_primo) )
				printf("%d é primo.\n", suposto_primo);
			else
				printf("%d não é primo.\n", suposto_primo);
		}else
			return 0;
	}
}