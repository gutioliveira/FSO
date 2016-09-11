#include <stdio.h>
#include <string.h>

int main(){

	double number1 = 7.3, number2;
	char s1[100], s2[100];

	double *dPtr;

	dPtr = &number1;

	printf("valor do dPtr = %lf\n", *dPtr);

	number2 = *dPtr;

	printf("valor de number2 = %lf\n", number2);

	printf("endereço de number1 = %p\n", &number1);

	printf("endereço do dPtr = %p\n", dPtr);

	scanf("%s", s1);

	strcpy(s2, s1);

	printf("As strings s1 e s2 são iguais? %s , \n%s == %s \n",
		strcmp(s1, s2) == 0 ? "Sim" : "Nao", s1, s2);

	strcat(s1,s2);

	printf("A string s2 concatenada em s1 = \n%s\n", s1);

	printf("Tamanho de s1 = %zd\n", strlen(s1));

	return 0;
}