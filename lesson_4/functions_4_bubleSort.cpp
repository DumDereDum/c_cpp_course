#include <iostream>

using namespace std;

int _less(int a, int b)
{
    return a < b;
}

int _greater(int a, int b)
{
    return a > b;
}

void bubbleSort(int * arr, int size, int(*pred)(int, int)) {
    for (int i = size-1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (pred(arr[j], arr[j + 1])) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

#define SIZE 10

int main()
{
    int arr[SIZE] = { 2,45,3,34,43,12,-5, 5,67,33 };

    for (int i = 0; i < SIZE; i++)
        printf("%d\t", arr[i]);
    printf("\n");

    bubbleSort(arr, SIZE, _less);
    for (int i = 0; i < SIZE; i++)
        printf("%d\t", arr[i]);
    printf("\n");

    bubbleSort(arr, SIZE, _greater);
    for (int i = 0; i < SIZE; i++)
        printf("%d\t", arr[i]);
    printf("\n");

    return 0;
}