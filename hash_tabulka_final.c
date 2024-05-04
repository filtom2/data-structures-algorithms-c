#include <stdio.h>
#include <stdlib.h>

typedef struct id {
    char meno[16];
    char priezvisko[16];
    char datum[16];
} ID;

typedef struct ludia {
    ID kluc;
    int money_pred_ciarkou;
    int money_za_ciarkou;
} Ludia;

typedef struct prvok {
    Ludia data;
    struct prvok *next;
} Prvok;

typedef struct hash_tabulka {
    Prvok *dalsi[10000];
} Hash_tabulka;

unsigned int hash(ID kluc);
Prvok *novyPrvok(Ludia data);
int insert(Hash_tabulka *table, Ludia data);
void printIfNotEmpty(int *printed);
Prvok *find_item(Hash_tabulka *table, ID kluc);
int update(Hash_tabulka *table, ID kluc, int pred_item, int za_item);
int delete_item(Hash_tabulka *table, ID kluc);

int main() 
{
    char volba;
    Hash_tabulka table = {0};
    Ludia ludia;
    int insert_status, update_status, delete_status;
    int printed = 0;
    while (scanf(" %c", &volba) == 1) 
    {
        switch (volba) 
        {
            case 'i':
                scanf("%s %s %s %d,%d", ludia.kluc.meno, ludia.kluc.priezvisko, ludia.kluc.datum, &ludia.money_pred_ciarkou, &ludia.money_za_ciarkou);
                insert_status = insert(&table, ludia);
                if(insert_status != 0){
                    printIfNotEmpty(&printed);
                    printf("insert failed");
                };
                break;

            case 's':
                scanf("%s %s %s", ludia.kluc.meno, ludia.kluc.priezvisko, ludia.kluc.datum);
                Prvok *find_item_result = find_item(&table, ludia.kluc);
                if (find_item_result != NULL)
                {
                    printIfNotEmpty(&printed);
                    printf("%d,%.02d", find_item_result->data.money_pred_ciarkou, find_item_result->data.money_za_ciarkou);
                }
                else 
                {
                    printIfNotEmpty(&printed);
                    printf("find_item failed");
                }
                break;

            case 'u':
                scanf("%s %s %s %d,%d", ludia.kluc.meno, ludia.kluc.priezvisko, ludia.kluc.datum, &ludia.money_pred_ciarkou, &ludia.money_za_ciarkou);
                update_status = update(&table, ludia.kluc, ludia.money_pred_ciarkou, ludia.money_za_ciarkou);
                if(update_status == -1)
                {
                    printIfNotEmpty(&printed);
                    printf("update failed");
                }
                break;

            case 'd':
                scanf("%s %s %s", ludia.kluc.meno, ludia.kluc.priezvisko, ludia.kluc.datum);
                delete_status = delete_item(&table, ludia.kluc);
                if(delete_status == -1)
                {
                    printIfNotEmpty(&printed);
                    printf("delete_item failed");
                }
                break;

            default:
                break;
        }
    }

    return 0;
}


unsigned int hash(ID kluc) // djb2 hash
{
    unsigned int hash = 5381;
    char *retaz = kluc.meno;
    while (*retaz != '\0')
    {
        hash = ((hash << 5) + hash) + *retaz;
        retaz++;
    }
    
    retaz = kluc.priezvisko;
    while (*retaz != '\0')
    {
        hash = ((hash << 5) + hash) + *retaz;
        retaz++;
    }

    retaz = kluc.datum;
    while (*retaz != '\0')
    {
        hash = ((hash << 5) + hash) + *retaz;
        retaz++;
    }
    return hash % 10000;
}

Prvok *novyPrvok(Ludia data)
{
    Prvok *prvok = (Prvok *)malloc(sizeof(Prvok));
    if (prvok == NULL)
    {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 12; i++)
    {
        prvok->data.kluc.meno[i] = data.kluc.meno[i];
        prvok->data.kluc.priezvisko[i] = data.kluc.priezvisko[i];
        prvok->data.kluc.datum[i] = data.kluc.datum[i];
    }
    prvok->data.money_pred_ciarkou = data.money_pred_ciarkou;
    prvok->data.money_za_ciarkou = data.money_za_ciarkou;
    prvok->next = NULL;
    return prvok;
}

int insert(Hash_tabulka *table, Ludia data)
{
    unsigned int index = hash(data.kluc);
    Prvok *novy = novyPrvok(data);
    if (table->dalsi[index] == NULL)
    {
        table->dalsi[index] = novy;
    }
    else
    {
        Prvok *aktualny = table->dalsi[index];
        while (aktualny->next != NULL)
        {
            aktualny = aktualny->next;
        }
        aktualny->next = novy;
    }
    return 0;
}

void printIfNotEmpty(int *printed)
{
    if (*printed)
    {
        printf("\n");
    }
    else
    {
        *printed = 1;
    }
}

Prvok *find_item(Hash_tabulka *table, ID kluc)
{
    unsigned int index = hash(kluc);
    Prvok *aktualny = table->dalsi[index];
    while (aktualny != NULL)
    {
        if (aktualny->data.kluc.meno[0] == kluc.meno[0] && aktualny->data.kluc.priezvisko[0] == kluc.priezvisko[0] && aktualny->data.kluc.datum[0] == kluc.datum[0])
        {
            return aktualny;
        }
        aktualny = aktualny->next;
    }
    return NULL;
}

int update(Hash_tabulka *table, ID kluc, int pred_item, int za_item)
{
    Prvok *aktualny = find_item(table, kluc);
    if (aktualny != NULL)
    {
        int currentTotalCents = aktualny->data.money_pred_ciarkou * 100 + aktualny->data.money_za_ciarkou;
        int newTotalCents = currentTotalCents;
        if (pred_item < 0)
        {
            newTotalCents += (pred_item * 100 + za_item) - za_item - za_item;
        }
        else
        {
            newTotalCents += (pred_item * 100 + za_item);
        }
        if (newTotalCents < 0)
        {
            return -1;
        }
        aktualny->data.money_pred_ciarkou = newTotalCents / 100;
        aktualny->data.money_za_ciarkou = newTotalCents % 100;
        return 0;
    }
    else
    {
        return -1;
    }
}

int delete_item(Hash_tabulka *table, ID kluc)
{
    unsigned int index = hash(kluc);
    Prvok *aktualny = table->dalsi[index];
    Prvok *predchadzajuci = NULL;
    while (aktualny != NULL)
    {
        if (aktualny->data.kluc.meno[0] == kluc.meno[0] && aktualny->data.kluc.priezvisko[0] == kluc.priezvisko[0] && aktualny->data.kluc.datum[0] == kluc.datum[0])
        {
            if (predchadzajuci == NULL)
            {
                table->dalsi[index] = aktualny->next;
            }
            else
            {
                predchadzajuci->next = aktualny->next;
            }
            free(aktualny);
            return 0;
        }
        predchadzajuci = aktualny;
        aktualny = aktualny->next;
    }
    return -1;
}