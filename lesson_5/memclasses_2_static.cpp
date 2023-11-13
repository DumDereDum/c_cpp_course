#include <iostream>

using namespace std;

void counter()
{
    static int count_1; //по умолчанию count = 0
    static int count_2 = 5;
    int count_3 = 0;
    ++count_1;
    ++count_2;
    ++count_3;
    printf("count_1:%d\tcount_2:%d\tcount_3:%d\t\n", count_1, count_2, count_3);
}

int main()
{
    for(int i=0; i<10; i++)
        counter();
    return 0;
}