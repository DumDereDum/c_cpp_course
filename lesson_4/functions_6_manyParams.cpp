#include <stdarg.h>
#include <stdio.h>

int test(char* first,...)
{
    va_list ap;
    va_start(ap, first);
    printf("%s\n", first);
    char* p = va_arg(ap, char*);
    while(p)
    {
        printf("%s\n", p);
        p = va_arg(ap, char*);
    }
    va_end(ap);
    return 0;
}

int main()
{
    test("Hello!",(char*)0);
    test("Hello", "world!", (char*)0);
    test("Just", "simple", "test",(char*)0);
    return 0;
}