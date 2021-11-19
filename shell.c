char ** parse_args( char * line ) {
    char ** values = calloc(5, sizeof(char *));
    char * curr = line;
    char * arg;
    int i = 0;
    while (curr) {
        arg = strsep(&curr, " ");
        values[i] = arg;
        i++;
    }
    return values;
}