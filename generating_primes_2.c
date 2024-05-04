// Generovanie prvocisiel 
#include <stdio.h>

int check_prime(long num);

int main(void) 
{
    long range_start, range_end;
    int first_prime = 1;

    do
    {
        scanf("%li %li", &range_start, &range_end);
        
    } while ((range_end <= range_start) || (range_start < 0 || range_end > 1000000));

    for (long i = range_start; i <= range_end; i++)
    {
        if (check_prime(i)) // if true
        {
            if (first_prime)
            {
                printf("%li", i);
                first_prime = 0;
            }
            else
            {
                printf(", %li", i);
            }
        }
    }

    
    return 0;
}


int check_prime(long num)
{
    // 0 / 1 -> not prime
    if (num < 2)
    {
        return 0;
    }
    // 2 -> is prime
    if (num == 2)
    {
        return 1;
    }

    // even number -> not prime
    if (num % 2 == 0)
    {
        return 0;
    }

    for (long i = 3; i * i <= num; i += 2)
    {
        if (num % i == 0)
        {
            return 0;
        }
    }

    return 1;
}