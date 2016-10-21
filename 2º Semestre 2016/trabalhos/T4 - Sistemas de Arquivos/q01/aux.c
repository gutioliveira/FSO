#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

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
            // printf("%s\n", creation_date);
            break;
        }
    }

    fclose(fp);

    return creation_date;
}

void print_metadados(char *partition, char *file_number, const char *file_name){

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

        char buffer[1000];
        sprintf(buffer, "cp %s %s.bkp", file_name, file_name);
        system(buffer);

        printf("Horário de criação do arquivo: %s\n", 
            get_creation_date(partition, file_number));
    }
}

int open_file(char *partition, char *file_number, const char *file_name) {

    struct stat file_metadata;

    // char buffer[1000];

    // sprintf(buffer, "cp %s %s.bkp 2> erros", file_name, file_name);

    // printf("%s\n", buffer);

    // system(buffer);

    // FILE *erro = fopen("erros", "r");

    // if ( fgetc(erro) == EOF ){

    print_metadados(partition, file_number, file_name);

    return 1;
}

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

void change_metadados(const char **argv,const char *file_name){

    char buffer_time[50];

    sprintf(buffer_time, "timedatectl set-time '%c%c%c%c-%c%c-%c%c %c%c:%c%c:00'"
        ,argv[1][0],argv[1][1],argv[1][2],argv[1][3],argv[1][4],argv[1][5],argv[1][6]
        ,argv[1][7],argv[1][8],argv[1][9],argv[1][10],argv[1][11]);

    printf("%s\n", buffer_time);

    system("date +\"%F %T\" > time");

    FILE *fp_time = fopen("time", "r");
    // Fri Dec 24 08:15:42 BRST 2010

    char date[20];
    char hour[20];

    fscanf(fp_time, "%s %s", date, hour);

    fclose(fp_time);

    system(buffer_time);

    sprintf(buffer_time, "timedatectl set-time '%s %s'", date, hour);

    char buffer_file[100];

    sprintf(buffer_file, "cp %s %s2", file_name, file_name);

    system(buffer_file);

    sprintf(buffer_file, "rm %s", file_name);

    system(buffer_file);

    sprintf(buffer_file, "mv %s2 %s", file_name, file_name);

    system(buffer_file);

    FILE *fp_file = fopen(file_name, "r");

    fclose(fp_file);

printf("teste %s\n", buffer_time);

    system(buffer_time);
}

int main(int argc, char const *argv[])
{

    printf("%s\n", argv[1]);

    char *partition = get_partition();

    char *file_number = get_file_number(argv[2]);

    if ( open_file(partition, file_number, argv[2]) ){

        change_metadados(argv, argv[2]);
    }   
    // system("df -h . > out");

    // Input data sudo debugfs -R 'stat <14156272>' /dev/sda8
    // system("sudo debugfs -R 'stat <14156272>' /dev/sda8 > out");



    return 0;
}
