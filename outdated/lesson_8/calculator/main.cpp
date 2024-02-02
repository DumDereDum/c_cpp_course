// g++ -DDEBUG_MODE main.cpp calculator.cpp calculator.hpp  my_types.hpp -o main
// g++ main.cpp calculator.cpp calculator.hpp  my_types.hpp -o main

#include <iostream>
#include "calculator.hpp"

using namespace std;

int main()
{
    FuncPtr* menu = createMenu();

    int op;
    int a, b;
    printf("enter a: ");
    scanf("%d", &a);
    printf("enter b: ");
    scanf("%d", &b);
    printf("enter operation [0 - add, 1 - sub, 2 - mul, 3 - div]: ");
    scanf("%d", &op);

    #ifdef DEBUG_MODE
    #include <iostream>
    debugLog(a, b, op);
    #endif

    if (op >= 0 && op < 4)
    {
        printf("%d\n", menu[op](a, b));
    }
    return 0;
}