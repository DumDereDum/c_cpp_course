#include <stdio.h>

int main()
{
    char* c[]    = {
        "ENTER", 
		"NEP", 
		"POINT", 
		"FIRST"
    };
    char **cp[]  = {c+3, c+2, c+1, c};
    char *** cpp = cp;
        
    printf("%s", * * ++ cpp);
    printf("%s ", * -- * ++ cpp + 3);
    printf("%s", *cpp[ -2 ] + 3);
    printf("%s\n", cpp[ -1 ][ -1 ] + 1);
    return 0;
}