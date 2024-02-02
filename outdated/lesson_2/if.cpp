#include <stdio.h>

int main(void)
{

    printf("\n");
    {
        int x = 2, y = 0;
        if (x > y)
            printf("if_1 %d\n", 1);
    }

    printf("\n");
    {
        int x = 2, y = 4;
        if (x > y)
            printf("if_2 %d\n", 1);
        else
            printf("if_2 %d\n", 0);
    }

    printf("\n");
    {
        int x = 2, y = 0;
        printf("if_3 %d\n", (x > y ? 1 : 0 ) );
        y = 4;
        printf("if_3 %d\n", (x > y ? 1 : 0 ) );
    }

    printf("\n");
    {
        int x = 2, y = 6, z = 5;
        if (x > y)
            printf("if_4 %d\n", 1);
        else if (x > z)
            printf("if_4 %d\n", 2);
        else if (y > z)
            printf("if_4 %d\n", 3);
        else
            printf("if_4 %d\n", 4);
    }

    printf("\n");
    {
        int x = 9, y = 8, z = 7;
        if (x > y)
        {
            if (x > z)
            {
                printf("if_5 %d\n", x);
            }
            else if (y > z)
            {
                printf("if_5 %d\n", y);
            }
            else
            {
                printf("if_5 %d\n", z);
            }
        }
    }
}