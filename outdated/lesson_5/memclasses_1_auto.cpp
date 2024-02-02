#include <iostream>

using namespace std;

int main()
{
    int n = 10;
    {
        int n = 5;
        printf("%d\n", n);
    }
    {
        auto n = 5;
        printf("%d\n", n);
    }
    {
        auto n = 5.0;
        printf("%d\n", n);
    }
    printf("%d\n", n);
    return 0;
}