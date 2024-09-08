#include <stdio.h>
#define LOWER 0 /* нижняя граница таблицы */
#define UPPER 300 /* верхняя граница */
#define STEP 20 /* размер шага */

/* печать таблицы температур по Фаренгейту и Цельсию */
main ()
{
    int fahr;
    for (fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP)
        printf ("Translation F: %3d ~ C: %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
}