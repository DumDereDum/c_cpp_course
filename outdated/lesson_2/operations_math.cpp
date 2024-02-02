#include <stdio.h>

int main(void)
{

    printf("\n");
    {
        int a_i = 5, b_i = 6;
        printf("int 5 * 6 = %d\n", a_i * b_i );

        float a_f = 5.5, b_f = 3.2;
        printf("float 5.5 * 3.2 = %f\n", a_f * b_f );
        
        // chars are equivalent to int
        // 'a' = 97
        // 'b' = 98
        char a_c = 'a', b_c = 'b';
        printf("char 'a' * 'b' = %d\n", a_c * b_c );
    }

    printf("\n");
    {
        int a_i = 30, b_i = 6, c_i = 4;
        printf("int: 30 / 6 = %d\n", a_i / b_i );
        // NB!: resut will be 7, not 7.5
        printf("int: 30 / 4 = %d\n", a_i / c_i );

        float a_f = 5.5, b_f = 3.2;
        printf("float 5.5 / 3.2 = %f\n", a_f / b_f );

        // division by zero (expect warning in console)
        printf("float  5.5 / 0 = %f\n",  a_f / 0 );
        printf("float -5.5 / 0 = %f\n", -a_f / 0 );

        // type convertion of operaion
        printf("int(operation)-->float 30 / 4 = %f\n", (float) a_i / c_i);
        
        // type convertion of result of operaion
        printf("int(result)-->float    30 / 4 = %f\n", float(a_i / c_i));
    }

    printf("\n");
    {
        int a = 30, b = 7;
        // use %% instest of %
        // printf interpreting % as functional symbol
        printf("int  30 %%  7 =  %d\n",  a %  b );
        printf("int -30 %%  7 = %d\n", -a %  b );
        printf("int  30 %% -7 =  %d\n",  a % -b );
        printf("int -30 %% -7 = %d\n", -a % -b );
    }
}