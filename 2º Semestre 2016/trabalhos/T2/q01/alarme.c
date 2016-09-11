#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int mysignal){

	printf("Signal received. %d\n", mysignal); // Emite uma mensagem com o código do sinal.
}

int main(int argc, char *argv[]){

	pid_t child_pid = fork(); // Faz uma cópia do processo.

	if ( child_pid == 0 ){ // Processo filho.

		printf("Child process %d\n", getpid()); // Printa na tela o valor PID do processo filho.

		sleep(5); // Faz o processo filho dormir por 5 segundos.

		kill(getppid(), SIGALRM); // Envia um sinal do tipo SIGALRM para o processo pai
					  // através da função getppid(), no qual retorna o valor PID
					  // do processo pai.

	}else if ( child_pid > 0 ){ // Processo pai.

		signal(SIGALRM, signal_handler); // Trata o recebimento de um sinal.

		pause(); // Deixa o processo pai rodando até receber um sinal.
	}else{
		
		printf("Fork failed!\n");
		return 1;
	}

	return 0;
}
