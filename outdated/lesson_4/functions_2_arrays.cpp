#include <iostream>

#define N 3
#define M 6

using namespace std;

void printArr1(int av[])
{
    for(int j = 0; j < M; j++)
        printf("%d\t", av[j]);
    printf("\n");
}

void printArr2(int *av)
{
    for(int j = 0; j < M; j++)
        printf("%d\t", av[j]);
    printf("\n");
}

void setTemp1(int (*t)[M])
{
    for(int i=0; i<N; i++)
        for(int j = 0; j<M; j++)
            t[i][j] = rand()%41-30;
}
void setTemp2(int t[][M])
{
    for(int i=0; i<N; i++)
        for(int j = 0; j<M; j++)
            t[i][j] = rand()%41-30;
}

int main()
{
    int average1[N][M];
    int average2[N][M];

    setTemp1(average1);
    setTemp2(average2);

    for(int i=0; i<N; i++)
        printArr1(average1[i]);

    for(int i=0; i<N; i++)
        printArr2(average1[i]);
}
