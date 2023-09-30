#include <stdio.h>

int main(void)
{

    printf(" ++i \n");
    {
        int i = 5;
        // got old incremented variadble
        printf("%d\n", ++i);
    }

    printf("\n i++ \n");
    {
        int i = 5;
        // got copy of old not incremented value
        // but original variable was incremented
        printf("%d\n", i++);
        // print original variable
        printf("%d\n", i);
    }
    printf("\n ( ++i = i++ ) \n");
    {
        int i = 5;
        // ++i return original incremented i variable
        // i++ return copy of original not incremented i variable
        // i (6, orig) = i (5, copy)
        // i = 5
        printf("%d\n", ( ++i = i++ ) );
        printf("%d\n", i);
    }
    printf("\n ( ++i + i++ ) \n");
    {
        int i = 5;
        // ++i return original incremented i variable
        // now i = 6
        // i++ return copy of original not incremented i variable
        // but i was incremented and i = 7
        // so we have
        // i (7, orig) + i (6, copy) = 13
        printf("%d\n", ( ++i + i++ ) );
        printf("%d\n", i);
    }

    printf("\n (++i + ++i) \n");
    {
        int i = 5;
        // ++i return original incremented i variable
        // now i = 6
        // second ++i return original incremented i variable, too
        // now i = 7
        // so we have
        // i (7, orig) + i (7, orig) = 14
        printf("%d\n", (++i + ++i) );
    }

    printf("\n adresses \n");
    {
        int i = 5;
        printf("  i adress: %p\n", &i);
        printf("++i adress: %p\n", &(++i));
        // ERROR: expression must be an lvalue or a function designatorC/C++(158)
        // printf("i++ adress: %p\n", &(i++));
    }
}