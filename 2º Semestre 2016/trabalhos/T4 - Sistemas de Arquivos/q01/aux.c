#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

// int open_file(char file_name[100]) {
//   FILE *backup;
//   char file_backup[100];

//   strcpy(file_backup, file_name);
//   strcat(file_backup, ".bkp");

//   // Todo - cp file file metadata
//   backup = fopen(file_backup, "a");
//   if (backup == NULL) {
//     printf("Não foi possível criar o arquivo de backup\n");
//     return 0;
//   }

//   struct stat file_metadata;
//   if (stat(file_name, &file_metadata) >= 0) {
//     // Converting time
//     char mtime[80];
//     char c_time[80];
//     char atime[80];
//     time_t t_mtime = file_metadata.st_mtime;
//     time_t t_atime = file_metadata.st_atime;
//     time_t t_ctime = file_metadata.st_ctime;
//     struct tm lt;
//     struct tm lt2;
//     struct tm lt3;

//     localtime_r(&t_mtime, &lt);
//     localtime_r(&t_atime, &lt2);
//     localtime_r(&t_ctime, &lt3);

//     strftime(mtime, sizeof mtime, "%a, %d %b %Y %T", &lt);
//     strftime(atime, sizeof atime, "%a, %d %b %Y %T", &lt2);
//     strftime(c_time, sizeof c_time, "%a, %d %b %Y %T", &lt3);

//     // Printing file metadata
//     printf("File Size: \t\t%d bytes\n",file_metadata.st_size);
//     printf("Number of Links: \t%d\n",file_metadata.st_nlink);
//     printf("File inode: \t\t%d\n",file_metadata.st_ino);
//     printf("Horário de acesso do arquivo: %s\n", atime);
//     printf("Horário de modificação do arquivo: %s\n", mtime);
//     printf("Horário de criação do arquivo: %s\n", c_time);
//   }


// //sudo debugfs -R 'stat /home/lu/Dropbox/Estudos.txt' /dev/sda5


//   //  Imprimir metadados horário de:
//      // criação,
//       // modificação
//       // acesso do arquivo alvo.


//   fclose(backup);
// }

char *get_partition(){

    char *partition = malloc(100); 

    system("df -h . > out");

    FILE *fp = fopen("out", "r");

    while ( fscanf(fp, "%s", partition) != EOF ){

        if ( partition[0] == '/' )
            break;
    }

    fclose(fp);

    return partition;
}

char *get_file_number(const char *file_name){

    char buffer[1024];

    sprintf(buffer, "ls -i %s > out", file_name);

    system(buffer);

    FILE *fp = fopen("out", "r");

    char *file_number = malloc(100);

    fscanf(fp, "%s %s", file_number, buffer);

    fclose(fp);

    return file_number;
}

char *get_creation_date(char *partition, char *file_number){

    char buffer[1024];

    sprintf(buffer, "sudo debugfs -R 'stat <%s>' %s > out", file_number, partition);

    system(buffer);

    FILE *fp = fopen("out", "r");

    char aux[1000];

    char *creation_date = malloc(1000);

    while ( fscanf(fp, "%s", aux) != EOF ){

        // printf("%s\n", aux);

        if ( strcmp(aux, "crtime:") == 0 ){

            char day[10];
            char month[10];
            char day_n[10];
            char hour[50];
            char year[10];

            fscanf(fp, "%*s %*s %s %s %s %s %s", day, month, day_n, hour, year);
            sprintf(creation_date, "%s %s %s %s %s", day, month, day_n, hour, year);
            printf("%s\n", creation_date);
            break;
        }
    }

    fclose(fp);

    return creation_date;
}

int main(int argc, char const *argv[])
{

    printf("%s\n", argv[1]);

    char *partition = get_partition();

    char *file_number = get_file_number(argv[2]);

    printf("%s\n",get_creation_date(partition, file_number));

    char buffer_time[50];



    // sprintf(buffer_time, "timedatectl set-time '%c%c%c%c-%c%c-%c%c %c%c:%c%c:00'"
    //     ,argv[1][0],argv[1][1],argv[1][2],argv[1][3],argv[1][4],argv[1][5],argv[1][6]
    //     ,argv[1][7],argv[1][8],argv[1][9],argv[1][10],argv[1][11]);

    // printf("%s\n", buffer_time);

    // system(buffer_time);

    // FILE *fp = fopen("PLSGOD2.txt", "a");

    // fclose(fp);

    int x = 1000000000;

    while(x--)
        ;

    // system("timedatectl set-ntp true");
    // system("df -h . > out");

    // Input data sudo debugfs -R 'stat <14156272>' /dev/sda8
    // system("sudo debugfs -R 'stat <14156272>' /dev/sda8 > out");



    return 0;
}
