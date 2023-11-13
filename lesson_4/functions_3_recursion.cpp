#include <iostream>

int count = 0;

unsigned long fib (unsigned long n)
{
    count++;
    if(n == 1 || n == 2)
        return 1;
    return fib (n-1) + fib (n-2);
}

int main()
{
    
    printf("counter: %d\t\tres: %ld\n", count, fib(10) );
    count = 0;
    printf("counter: %d\t\tres: %ld\n", count, fib(20) );
    count = 0;
    printf("counter: %d\tres: %ld\n", count, fib(30) );

    return 0;
}