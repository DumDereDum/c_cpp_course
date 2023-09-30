#include <stdio.h>

int main(void)
{

    printf("\n");
    for(int i = 0; i<=16; i++)
    {
        printf("%d ", i);
    }

    printf("\n");
    for(int i = 0; i<=16; i++)
    {
        // got incremented variables
        printf("%d ", ++i);
    }

    printf("\n");
    for(int i = 0; i<=16; i++)
    {
        // got copy of not incremented variables
        printf("%d ", i++);
    }

    printf("\n");
    printf("\n");
    {
        int i = 0;
        for(;;)
        {
            i++;
            if (i % 2 == 0)
            {
                printf("%d ", i);
            }
            if (i > 20)
            {
                break;
            }
        }
    }

    printf("\n");
    printf("\n");
    {
        int i = 0;
        for(;;)
        {
            i++;
            if (i % 2 == 0)
            {
                continue;
            }
            else
            {
                printf("%d ", i);
            }
            if (i > 20)
            {
                break;
            }
        }
    }
    printf("\n");

}