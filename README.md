# Systems Project 01 - PeteSteveShell (PSHell)

  

[Basic implementation of a shell.](https://www.stuycs.org/systems-dw/2021/11/17/p01.html)

  

## Features

  
* run bash commands
* `exit` to close the shell
* `cd` to change directories
* run multiple commands in one line using `;`
* two argument piping using ` | `
* ~~basic redirection using `<` and `>`~~
 * `color` to display working directory with color of choosing 

## Usage

  For command inputs, please limit to one space before and after the `;`, `|`, `<`, `>`e.g
  ```c
  ls -a;echo hi   //works
  ls -a ; echo hi //works
  ls -a; echo hi  //works
  ls -a ;echo hi  //works
  ```
  
  You can edit the working directory color by using the custom command `color` using the arguments blue, green, or red.

  ```c
  color blue //changes directory color to blue
  color red //changes directory color to red
  color green //changes directory color to green
  color brown //Displays message "Invalid Color. Try 'blue', 'green', or 'red'."
  ```  

## Attempts

## Bugs

## Function Headers

```c

 /*

 Prints out an array of strings, given an array of strings

*/

void print_string_arr(char ** arr);

  

/*

 Parses a line of input (a string) for ';' and returns an array of strings

*/

char ** get_cmd_line( char * line );

  

/*

 Parses a line of input (a string) for ' ' and returns an array of strings

*/

char ** get_cmd_args(char * cmd);

  

/*

 Parses a pipe for '|', '>', or '<', and returns a two string array containing the piped or redirected commands

*/

char ** get_cmd_from_operator(char * line, char * operator);

  

/*

 Prints the current working directory in the given color

*/

void pwd(char * color);

```

