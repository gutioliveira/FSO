#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

int contador = 1;

void primeiros_30_bytes(const char *file_name){

    FILE *fp = fopen(file_name, "r");

    int cont = 0;

    int c;

    while( (c = fgetc(fp)) != EOF ){

        printf("%c", (char) c);
        cont++;

        if ( cont >= 30 )
            break;
    }

    printf("\n");
}

void percorre_diretorios(char *nome_diretorio, const char *substring, const int N){
    
    DIR *dp;
    struct dirent *entrada;
    struct stat estado;

    if( (dp = opendir(nome_diretorio)) == NULL ) {

        fprintf(stderr,"Não foi possível abrir a pasta: %s\n", nome_diretorio);
        return;
    }

    chdir(nome_diretorio);

    while((entrada = readdir(dp)) != NULL) {

        lstat(entrada->d_name,&estado);

        if(S_ISDIR(estado.st_mode)) {

            if ( strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0 )
                continue;

            percorre_diretorios(entrada->d_name, substring, N);
        }else{


            if ( strstr(entrada->d_name, substring) != NULL ){

                char buf[1024];
                getcwd(buf, sizeof(buf));

                if ( contador <= N ){

                    printf("%d.%s/%s\n", contador++, buf, entrada->d_name);
                    primeiros_30_bytes(entrada->d_name);
                }
            }
        }
    }
    chdir("..");
    closedir(dp);
}

int main(int argc, char **argv){

    char *caminho = argv[1];
    char *substring = argv[2];
    int N = atoi(argv[3]);

    printf("\n\n\nResultado de buscador -- \"%s\" na pasta %s\n\n\n\n", substring, caminho);

    percorre_diretorios(caminho, substring,N);

    return 0;
}