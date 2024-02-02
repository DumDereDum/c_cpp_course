#include <stdio.h>

int main(void)
{

    printf("\n");
    {
        float a = 5.6;
        int   b = 34;
        printf("!a = %d\n", !a);
        printf("!(b-b) = %d\n", !(b-b));
        
        // !((b-b)*a) -> !((0)*a) -> !(0) -> 1
        printf("!((b-b)*a) = %d\n", !((b-b)*a));

        // !(b-b)*a -> !(0)*a -> 1*a -> a
        printf("!(b-b)*a %f\n", !(b-b)*a);
    }

    printf("\n");
    {
        float a = 5.6, b = 3.4, c = 0;
        int d = 3, e = 7, f = 0;

        // lazy operation
        // it stops calculation after (a-a)=0
        // so c = b was not run
        (a - a) && (c = b);
        printf("c = %f\n", c );
        // so c = b was run firstly
        (c = b) && (a - a);
        printf("c = %f\n", c );

        // (e * f) = 0, so (f = d) was NOT run
        (e * f) && (f = d);
        printf("f = %d\n", f );

        // (f = d) = f != 0, so (d = e * f) was run
        (f = d) && (d = e * f);
        printf("f1 = %d\n", f );
        printf("d1 = %d\n", d );
        
        d = 45;
        // (f = 0) = f == 0, so (d = e * f) was NOT run
        (f = 0) && (d = e * f);
        printf("f2 = %d\n", f );
        printf("d2 = %d\n", d );
    }
    
    printf("\n");
    {
        float a = 5.6, b = 3.4, c = 0;
        int d = 3, e = 7, f = 0;

        // lazy operation
        // it stops calculation after (a)!=0
        // so c = b was NOT run
        (a) || (c = b);
        printf("c = %f\n", c );

        (a-a) || (c = b);
        printf("c = %f\n", c );

        // f = d != 0, so (d = e * f) was NOT run
        (f = d) || (d = e * f);
        printf("f1 = %d\n", f );
        printf("d1 = %d\n", d );
        printf("e*f = %d\n", e*f );
        
        // f = 0 == 0, so (d = e * f) was run
        (f = 0) || (d = e * f);
        printf("f2 = %d\n", f );
        printf("d2 = %d\n", d );
    }

    printf("\n");
    {
        float a = 5.6, b = 3.4, c = 0;
        int d = 3, e = 7, f = 0;
        
        // d != 0, so (f = e && a) was NOT run
        d || (f = e && a);
        printf("f = %d\n", f );

        // (f = e && a) ->  (f = 3.4) -> !=0
        // so (c=b), was NOT run
        (f = e && a) || (c = b);
        printf("f1 = %d\n", f );
        printf("c1 = %f\n", c );

        // ((f = e) && a) -> ((f = 7) && a) -> (7 && 5.6) -> (3.4) -> !=0
        // so (c=b), was NOT run
        ((f = e) && a) || (c = b);
        printf("f2 = %d\n", f );
        printf("c2 = %f\n", c );

        // (f && (a-a)) -> (f && 0) -> 0
        // so (c=b) was run
        (f && (a-a)) || (c = b);
        printf("c3 = %f\n", c );
    }

}