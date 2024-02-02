#include <cstdlib>

#include "calculator.hpp"

int doSum(int a, int b)
{
    return a + b;
}

int doSub(int a, int b)
{
    return a - b;
}

int doMul(int a, int b)
{
    return a * b;
}

int doDiv(int a, int b)
{
    if (b == 0)
        exit(-1);
    return a / b;
}

FuncPtr* createMenu() {
    FuncPtr* menu = (FuncPtr*)malloc(4 * sizeof(FuncPtr));
    if (menu != NULL) {
        menu[0] = doSum;
        menu[1] = doSub;
        menu[2] = doMul;
        menu[3] = doDiv;
    }
    return menu;
}

#ifdef DEBUG_MODE
#include <iostream>
void debugLog(int a, int b, int op)
{
    std::cout << "Debug Message:" << std::endl;
    std::cout << "\ta : " << a << std::endl;
    std::cout << "\tb : " << b << std::endl;
    std::cout << "\top: " << op << std::endl;
}
#endif