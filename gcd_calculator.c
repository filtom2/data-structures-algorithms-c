// od 0 do 18446744073709551615 => 2^64 => unsigned long long

#include <stdio.h>

unsigned long long calculate_gcd(unsigned long long num1, unsigned long long num2);

int main(void) {
    unsigned long long num1, num2;
    int pocet_vstupov;

    do
    {
        scanf("%i", &pocet_vstupov);
    } while (pocet_vstupov < 1 || pocet_vstupov > 100000);

    unsigned long long gcd_zaznamy[pocet_vstupov]; 
    for (int i = pocet_vstupov, counter = 0; i != 0; i--, counter++) {
        scanf("%llu %llu", &num1, &num2);
        gcd_zaznamy[counter] = calculate_gcd(num1, num2);
    }

    // Prejdenie a vypisanie zoznamu
    for (int i = 0; i < pocet_vstupov; i++) {
        printf("%llu\n", gcd_zaznamy[i]);
    }


    return 0;
}

unsigned long long calculate_gcd(unsigned long long num1, unsigned long long num2) {
    unsigned long long gcd = 0;

    // if num2 is greater than num1 => we swap
    if (num2 > num1) {
    unsigned long long tmp = num2;
    num2 = num1;
    num1 = tmp;
    }

    // i starts from 1
    for (int i = 1; i <= num2; i++){
        if (num1 % i == 0 && num2 % i == 0)
        {
            gcd = i;
        }
    }

    return gcd;
}