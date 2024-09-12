# Массивы

```
#include <stdio.h>
/* подcчет цифр, cимволов-разделителей и прочих cимволов */ 
int main()
{
    int c, i, nwhite, nother;
    int ndigit[10];
    nwhite = nother = 0;
    for (i = 0; i < 10; ++i)
        ndigit[i]= 0;
    while ((c = getchar()) != EOF)
        if (c >= '0' && c <= '9' )
            ++ndigit[c - '0' ];
        else if (c == ' ' || c == '\n' || c == '\t')
            ++nwhite;
        else
            ++nother;
    printf ("цифры =");
    for (i=0; i < 10; ++i)
        printf(" %d", ndigit[i]);
    printf (", cимволы-разделители = %d, прочие = %d\n", nwhite, nother);
}
```

**Упражнение 1:** добавить подсчет букв
**Упражнение 2:** считать все буквы как строчные, т.е. 'а' и 'А' считаются одинаковыми

