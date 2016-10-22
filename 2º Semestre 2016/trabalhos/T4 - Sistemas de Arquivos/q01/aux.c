#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <assert.h>

char *get_creation_date(char *partition, char *file_number){

    char buffer[1024];

    sprintf(buffer, "sudo debugfs -R 'stat <%s>' %s > out", file_number, partition);

    system(buffer);

    FILE *fp = fopen("out", "r");

    char aux[1024];

    char *creation_date = malloc(1000);

    while ( fscanf(fp, "%s", aux) != EOF ){

        if ( strcmp(aux, "crtime:") == 0 ){

            char day[10];
            char month[10];
            char day_n[10];
            char hour[50];
            char year[10];

            fscanf(fp, "%*s %*s %s %s %s %s %s", day, month, day_n, hour, year);
            sprintf(creation_date, "%s %s %s %s %s", day, month, day_n, hour, year);
            break;
        }
    }

    fclose(fp);

    assert(!strlen(creation_date) == 0);

    return creation_date;
}

void print_metadados(char *partition, char *file_number, char *file_name){

    struct stat file_metadata;

    if (stat(file_name, &file_metadata) >= 0) {
        // Converting time
        char mtime[1024];
        char atime[1024];
        time_t t_mtime = file_metadata.st_mtime;
        time_t t_atime = file_metadata.st_atime;
        struct tm lt;
        struct tm lt2;

        localtime_r(&t_mtime, &lt);
        localtime_r(&t_atime, &lt2);

        strftime(mtime, sizeof mtime, "%a, %d %b %Y %T", &lt);
        strftime(atime, sizeof atime, "%a, %d %b %Y %T", &lt2);

        // Printing file metadata
        printf("Horário de acesso do arquivo: %s\n", atime);
        printf("Horário de modificação do arquivo: %s\n", mtime);

        char buffer[1024];
        sprintf(buffer, "cp %s %s.bkp", file_name, file_name);
        system(buffer);

        printf("Horário de criação do arquivo: %s\n", 
            get_creation_date(partition, file_number));
    }
}

int open_file(char *partition, char *file_number, char *file_name) {

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

char *get_file_number(char *file_name){

    char buffer[1024];

    sprintf(buffer, "ls -i %s > out", file_name);

    system(buffer);

    FILE *fp = fopen("out", "r");

    char *file_number = malloc(100);

    fscanf(fp, "%s %s", file_number, buffer);

    fclose(fp);

    return file_number;
}

void change_metadados(char **argv, char *file_name){

    char buffer_time[1024];

    sprintf(buffer_time, "timedatectl set-time '%c%c%c%c-%c%c-%c%c %c%c:%c%c:00'"
        ,argv[2][0],argv[2][1],argv[2][2],argv[2][3],argv[2][4],argv[2][5],argv[2][6]
        ,argv[2][7],argv[2][8],argv[2][9],argv[2][10],argv[2][11]);

    system("date +\"%F %T\" > time");

    FILE *fp_time = fopen("time", "r");

    char date[1024];
    char hour[1024];

    fscanf(fp_time, "%s %s", date, hour);

    fclose(fp_time);

    system(buffer_time);

    sprintf(buffer_time, "timedatectl set-time '%s %s'", date, hour);

    char buffer_file[1024];

    sprintf(buffer_file, "cp %s %s2", file_name, file_name);

    system(buffer_file);

    sprintf(buffer_file, "rm %s", file_name);

    system(buffer_file);

    sprintf(buffer_file, "mv %s2 %s", file_name, file_name);

    system(buffer_file);

    FILE *fp_file = fopen(file_name, "r");

    fclose(fp_file);

    system(buffer_time);
}

int main(int argc, char *argv[]){

    char *partition;

    if ( argc == 4 )
        partition = argv[3];
    else
        partition = get_partition();

    char *file_number = get_file_number(argv[1]);

    if ( open_file(partition, file_number, argv[1]) ){

        change_metadados(argv, argv[1]);
    }   

    return 0;
}
