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
    Prints out an array of strings, given an array of strings
*/
void print_string_arr( char ** arr);

/*
    Parses a line of input (a string) for ';' and returns an array of strings 
*/
char ** get_cmd_line( char * line );

/*
    Parses a line of input (a string) for ' ' and returns an array of strings 
*/
char ** get_cmd_args(char * cmd);
//command num

//command separators