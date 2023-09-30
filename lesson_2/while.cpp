#include <stdio.h>

int main(void)
{

    printf("\n");
    {
        int i = 0;
        while (i < 20)
        {
            printf("%d ", ++i);
        }
    }

    printf("\n");
    {
        int i = 0;
        while (1)
        {
            if (i == 20)
            {
                break;
            }
            printf("%d ", ++i);
        }
    }
    printf("\n");

}