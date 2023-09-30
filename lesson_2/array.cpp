#include <stdio.h>
#include <string>

using namespace std;

int array[9] = {
    1,  2,  3,  4,  5, 31, 32, 48, 195
// 01, 02, 03, 04, 05, 1F, 20, 30,  C3
};

float array2[3] = {
    1.0,   // 0 x 3f 80 00 00 find 803f in binary
    4.5,   // 0 x 40 90 00 00 find 9040 in binary
    7.125, // 0 x 40 e4 00 00 find e440 in binary
};

string str = "1234567890"; // find 313233 in binary

int main(void)
{
    for(int i = 0; i < 9; i++)
    {
        void* address = array + i;
        int value = *(array + i);
        printf("array[%d]: address=%p \t value=%d \n", i, address, value);
    }

    for(int i = 0; i < 3; i++)
    {
        void* address = array2 + i;
        float value = *(array2 + i);
        printf("array[%d]: address=%p \t value=%f \n", i, address, value);
    }

    void* address = &(*str.begin());
    printf("str_address=%p \n",address);
    address = &(*str.end());
    printf("str_address=%p \n",address);
    
    return 0;
}