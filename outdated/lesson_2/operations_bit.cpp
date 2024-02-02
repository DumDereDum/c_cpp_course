#include <stdio.h>

// macro from internet do not pay attection to it
#define print_bits(x)                                            \
  do {                                                           \
    unsigned long long a__ = (x);                                \
    size_t bits__ = sizeof(x) * 8;                               \
    printf(#x ": ");                                             \
    while (bits__--) putchar(a__ &(1ULL << bits__) ? '1' : '0'); \
    putchar('\n');                                               \
  } while (0)

int main(void)
{

    printf("\n & \n");
    {
        char a = 10, b = 7;
        char c = a & b;
        print_bits(a);
        print_bits(b);
        print_bits(c);
    }

    printf("\n | \n");
    {
        char a = 10, b = 7;
        char c = a | b;
        print_bits(a);
        print_bits(b);
        print_bits(c);
    }

    printf("\n ^ \n");
    {
        char a = 10, b = 7;
        char c = a ^ b;
        print_bits(a);
        print_bits(b);
        print_bits(c);
    }
    
    printf("\n ~ \n");
    {
        char a = 10, b = 7;
        // '~' converts number to 32 bit representation
        // so we use (char) for going back to 8 bits
        print_bits((char) a);
        print_bits((char)~a);
        print_bits((char) b);
        print_bits((char)~b);
    }

    printf("\n << \n");
    {
        int a = 7;
        print_bits(a);
        printf("a << 1 %d\n", a << 1);
        print_bits(a << 1);
        printf("a << 2 %d\n", a << 2);
        print_bits(a << 2);
        printf("a << 3 %d\n", a << 3);
        print_bits(a << 3);
    }
    
    printf("\n >> \n");
    {
        int a = 7;
        print_bits(a);
        printf("a >> 1 %d\n", a >> 1);
        print_bits(a >> 1);
        printf("a >> 2 %d\n", a >> 2);
        print_bits(a >> 2);
        printf("a >> 3 %d\n", a >> 3);
        print_bits(a >> 3);
    }
}