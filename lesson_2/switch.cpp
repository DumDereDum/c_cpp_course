#include <stdio.h>

int main(void)
{
    // switch works during first break
    // this goes from JMP in assembler
    printf("\n");
    {
        int a = 2;
        switch (a)
        {
            case 1:
                printf("one\n");
            case 2:
                printf("two\n");
            case 3:
                printf("three\n");
            case 4:
                printf("four\n");
            case 5:
                printf("five\n");
            default:
                printf("other number\n");
        }
    }

    printf("\n");
    {
        int a = 2;
        switch (a)
        {
            case 1:
                printf("one\n");
                break;
            case 2:
                printf("two\n");
            case 3:
                printf("three\n");
            case 4:
                printf("four\n");
                break;
            case 5:
                printf("five\n");
                break;
            default:
                printf("other number\n");
                break;
        }
    }

    printf("\n");
    {
        int a = 2;
        switch (a)
        {
            case 1:
                printf("one\n");
                break;
            case 2:
                printf("two\n");
                break;
            case 3:
                printf("three\n");
                break;
            case 4:
                printf("four\n");
                break;
            case 5:
                printf("five\n");
                break;
            default:
                printf("other number\n");
                break;
        }
    }
}