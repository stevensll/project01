#include "shell.h"

char ** get_cmd_line( char * line ) {
    char *pos;
    if ((pos=strchr(line, '\n')) != NULL)
        *pos = '\0';
    char ** values = calloc(sizeof(line)/sizeof(char), sizeof(char *));
    char * curr = line;
    int i = 0;
    while (curr) {
        values[i] = strsep(&curr, ";");
        i++;
    }
    return values;
}

char ** get_cmd_args(char * cmd){
    char ** parts = calloc(sizeof(cmd)/sizeof(char), sizeof(char *));
    char * curr = cmd;
    int i = 0;
    while (curr){
        parts[i] = strsep(&curr, " ");
        i++;
    }
    parts[i] = NULL;
    return parts;
}


void print_string_arr( char ** arr){
    int i = 0;
    while(arr[i]){
        printf("%s\n", arr[i]);
        i++;
    }
    printf("\n");
}
