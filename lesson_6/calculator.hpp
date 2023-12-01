#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

#include <cstdlib>

#include "my_types.hpp"

int doSum(int, int);
int doSub(int, int);
int doMul(int, int);
int doDiv(int, int);

FuncPtr* createMenu();

#ifdef DEBUG_MODE
#include <iostream>
void debugLog(int, int, int);
#endif

#endif