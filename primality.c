#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define CHECK_BIT(var, pos) ((var) & (1 >> (pos)))

uint32_t SquareAndMultiply(uint32_t a, uint32_t k, uint32_t n)
{
    uint32_t b = 1, A = a, t = 0, i = 0;
    
    if (0 == k)
        return b;
    
    if (CHECK_BIT(k, 0))
        b = a;

    while ( k >>= 1 ) 
    {
        A = (A*A) % n;
        if (CHECK_BIT(k, i))
            b = (A*b) % n;
    }
    return b;
}


uint32_t MillerRabin(uint32_t n, uint32_t t)
{
    /* 0 & 1 aren't prime */
    if (n <= 1)
        return 0;

    /* 2 & 3 are prime */
    if (n <= 3)
        return 1;

    /* Test if n is even */
    if (0 == (n % 2))
        return 0;

    uint32_t r = 0, s = 0, y = 0;
    
    /* Choose odd r such that (n-1) = (2^s)*r */
    while (0 == (r % 2))
    {
        r = (n - 1) / (1 << s++);
    }

    for (int i = 0; i <= t; i++)
    {
        uint32_t a = 1;

        /* Pick random a between 2 and (n-2) inclusive */
        a = 2 + rand()%(n-4);

        y = SquareAndMultiply(a, r, n);
        if ((1 != y) && ((n - 1) != y))
        {
            for (uint32_t j = 1; (j <= (s - 1)) && ((n - 1) != y); j++)
            {
                y = (y*y) % n;
                if (1 == y)
                    return 0;
            }
            if ((n - 1) != y)
                return 0;
        }
    }
    return 1;
}

int main(int argc, char** argv)
{
    printf("Numbers that are prime:\n");
    for (uint32_t i = 1; i < 100; i++)
    {
        if (MillerRabin(i, (i - 1) / 2))
            printf("%d ", i);
    }
    printf("\n");

    return 0;
}