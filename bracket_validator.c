#include <stdlib.h>
#include <stdio.h>

int pocet_chyb(char *pole)
{
    int chyba = 0;
    int pridany_znak = -1;
    int dlzka = 0;
    while(pole[dlzka] != '\0')
    {
        dlzka++;
    }
    char *zasobnik = (char*)malloc(dlzka * sizeof(char));

    for(int i = 0; pole[i] != '\0'; i++)
    {
        char znak = pole[i];
        if(znak == '(' || znak == '{' || znak == '[' || znak == '<') 
        {
            zasobnik[++pridany_znak] = znak;
        } 
        else 
        {
            if(pridany_znak == -1) 
            {
                chyba++;
            } 
            else 
            {
                char posledny_otvoreny = zasobnik[pridany_znak--];
                if(posledny_otvoreny == '(' && znak != ')') 
                {
                    chyba++;
                } 
                else if(posledny_otvoreny == '[' && znak != ']') 
                {
                    chyba++;
                } 
                else if(posledny_otvoreny == '{' && znak != '}') 
                {
                    chyba++;
                } 
                else if(posledny_otvoreny == '<' && znak != '>') 
                {
                    chyba++;
                }
            }
        }
    }
    chyba += (pridany_znak + 1);
    free(zasobnik);
    return chyba;
}

int main()
{
    int pocet;
    scanf("%d", &pocet);
    if (pocet < 1 || pocet > 200) 
    {
        return 1;
    }

    int max_velkost = 100001;
    char *pole = (char*)malloc(max_velkost * sizeof(char));
    for(int i = 0; i < pocet; i++) 
    {
        scanf("%s", pole);
        printf("%d", pocet_chyb(pole));
        if(i < pocet-1) 
        {
            printf("\n");
        }
    }
    free(pole);
    return 0;
}
