#include "shell.h"

char ** parse_args( char * line ) {
    char ** values = calloc(100, sizeof(char *));
    char * curr = line;
    char * arg;
    int i = 0;
    while (curr) {
        arg = strsep(&curr, " ");
        values[i] = arg;
        i++;
    }
    //values[i] = '\0';
    return values;
}
void print_2d_arr( char ** arr){
    int i = 0;
    while(arr[i]){
        printf("%s\n", arr[i]);
        i++;
    }
}
