#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stat-time.h>
#include <sys/types.h>
#include <time.h>

int open_file(char file_name[100]) {
  FILE *backup;
  char file_backup[100];

  strcpy(file_backup, file_name);
  strcat(file_backup, ".bkp");

  // Todo - cp file file metadata
  backup = fopen(file_backup, "a");
  if (backup == NULL) {
    printf("Não foi possível criar o arquivo de backup\n");
    return 0;
  }

  struct stat file_metadata;
  if (stat(file_name, &file_metadata) >= 0) {
    // Converting time
    char mtime[80];
    char atime[80];
    time_t t_mtime = file_metadata.st_mtime;
    time_t t_atime = file_metadata.st_atime;
    struct tm lt;
    struct tm lt2;

    localtime_r(&t_mtime, &lt);
    localtime_r(&t_atime, &lt2);

    strftime(mtime, sizeof mtime, "%a, %d %b %Y %T", &lt);
    strftime(atime, sizeof atime, "%a, %d %b %Y %T", &lt2);

    // Printing file metadata
    printf("File Size: \t\t%d bytes\n",file_metadata.st_size);
    printf("Number of Links: \t%d\n",file_metadata.st_nlink);
    printf("File inode: \t\t%d\n",file_metadata.st_ino);
    printf("Horário de acesso do arquivo: %s\n", atime);
    printf("Horário de modificação do arquivo: %s\n", mtime);
    printf("Horário de criação do arquivo: %s\n", mtime);
  }



  //  Imprimir metadados horário de:
     // criação,
      // modificação
      // acesso do arquivo alvo.


  fclose(backup);
}

int main(int argc, char const *argv[])
{

  if (argc != 3) {
    puts("Número de argumentos inválidos, por favor, tente novamente!");
    return 0;
  }

  // Input data
  char file_name[100];
  char date[15];
  strcpy(file_name, argv[1]);
  strcpy(date, argv[2]);

  printf("File name: %s\n", file_name);
  printf("Date: %s\n", date);

  open_file(file_name);


  return 0;
}
