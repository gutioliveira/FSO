#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void printdir(char *folder, char *dir_name, const char *substring, int *cont, const int N){
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;

    if( (dp = opendir(folder)) == NULL ) {

        fprintf(stderr,"Não foi possível abrir a pasta: %s\n", folder);
        return;
    }

    if ( *cont > N )
        return;

    char *directory = folder;

    chdir(folder);

    while((entry = readdir(dp)) != NULL) {

        lstat(entry->d_name,&statbuf);

        if(S_ISDIR(statbuf.st_mode)) {

            char buf_path[1000];

            if ( strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 )
                continue;
            
            sprintf(buf_path, "%s/%s", dir_name, entry->d_name);

            printdir(entry->d_name, buf_path, substring, cont, N);
        }else{

            if ( *cont > N )
                return;

            if ( strstr(entry->d_name, substring) != NULL ){

                printf("%d.%s/%s\n", *cont, dir_name, entry->d_name);
                *cont = *cont + 1;
            }
        }
    }
    chdir("..");
    closedir(dp);
}

int main(int argc, char **argv){

    char *path = argv[1];
    char *substring = argv[2];
    int N = atoi(argv[3]);

    int contador = 1;

    printf("\n\n\nResultado de %s -- \"buscador\" na pasta %s\n\n\n\n", substring, path);

    printdir(path, path, substring, &contador,N);

    return 0;
}