#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>

/*
    Prints out an array of strings
*/
void print_string_arr( char ** arr);

/*
    Stores a line of input into an array of strings, separated by ;
*/
char ** get_cmd_line( char * line );

char ** get_cmd_args(char * cmd);
//command num

//command separators