#include <iostream>

using namespace std;

void funNoPointer(short value)
{
    value++;
}
void funPointer(short *value)
{
    (*value)++;
}

int main()
{
    short value=14;
    
    funNoPointer(value);
    printf("funNoPointer: %d\n", value);
    
    funPointer(&value);
    printf("funPointer:   %d\n", value);

    return 0;
}