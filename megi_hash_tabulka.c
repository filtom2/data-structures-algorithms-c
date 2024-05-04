#include <stdio.h>
#include <stdlib.h>

typedef struct key {
    char krstne_meno[20];
    char priezvisko[20];
    char datum[12];
}KEY;

typedef struct osoba {
    KEY key;
    float zostatok;
    struct osoba *next;
}OSOBA;

typedef struct hash_table {
    OSOBA **hashItem; 
    int velkost;
}HASH_TABLE;


OSOBA *create_node(OSOBA data) {
    OSOBA *newNode = (OSOBA*)malloc(sizeof(OSOBA));
    newNode->key = data.key;
    newNode->zostatok = data.zostatok;
    newNode->next = NULL;
    return newNode;
}


HASH_TABLE *create_hash_table(int velkost) {
    HASH_TABLE *table = (HASH_TABLE*) malloc(sizeof(HASH_TABLE));
    if (table == 0){
        return NULL;
    }
    table->velkost = velkost;
    table->hashItem = (OSOBA **)malloc(sizeof(OSOBA*) * velkost);
    if (!table->hashItem){
        free(table);
        return NULL;
    }
    for (int i=0; i < velkost; i++) {
        table->hashItem[i] = NULL;
    }
    return table;
}

unsigned int hashovanie(KEY key, int velkostTabulky) {
    unsigned int hash_value = 6173;
    int totalLength = sizeof(key.krstne_meno) + sizeof(key.priezvisko) + sizeof(key.datum);
    char *combined = (char*)malloc(totalLength + 1);
    if (!combined) {
        return 0;
    }
    char *temp = combined;
    for(int i = 0; i < sizeof(key.krstne_meno) && key.krstne_meno[i] != '\0'; i++, temp++) {
        *temp = key.krstne_meno[i];
    }
    for(int i = 0; i < sizeof(key.priezvisko) && key.priezvisko[i] != '\0'; i++, temp++) {
        *temp = key.priezvisko[i];
    }
    for(int i = 0; i < sizeof(key.datum) && key.datum[i] != '\0'; i++, temp++) {
        *temp = key.datum[i];
    }
    for(char *str = combined; str < temp; str++) {
        hash_value = ((hash_value << 5) - hash_value) + *str;
    }
    free(combined);
    return hash_value % velkostTabulky;
}

int porovnajKluc(KEY kluc1, KEY kluc2) {
    for (int i = 0; i < sizeof(kluc1.krstne_meno); i++) {
        if (kluc1.krstne_meno[i] != kluc2.krstne_meno[i]) {
            return 1;
        }
        if (kluc1.krstne_meno[i] == '\0') break;
    }
    for (int i = 0; i < sizeof(kluc1.priezvisko); i++) {
        if (kluc1.priezvisko[i] != kluc2.priezvisko[i]) {
            return 1;
        }
        if (kluc1.priezvisko[i] == '\0') break;
    }
    for (int i = 0; i < sizeof(kluc1.datum); i++) {
        if (kluc1.datum[i] != kluc2.datum[i]) {
            return 1;
        }
        if (kluc1.datum[i] == '\0') break;
    }
    return 0;
}


float insert(HASH_TABLE *hash_table, OSOBA data) {
    OSOBA *newNode = create_node(data); 
    unsigned int index = hashovanie(data.key, hash_table->velkost); 

    OSOBA **current = &(hash_table->hashItem[index]);
    while (*current != NULL) {
        if (porovnajKluc((*current)->key, newNode->key) == 0) {
            free(newNode); 
            return 1; 
        }
        current = &((*current)->next);
    }
    *current = newNode;
     return 0; 
}


OSOBA *search(HASH_TABLE *hash_table, KEY key) {
    unsigned int index = hashovanie(key, hash_table->velkost); 
    OSOBA *current = hash_table->hashItem[index];

    while (current != NULL) {
        if (porovnajKluc(current->key, key) == 0) {
            return current; 
        }
        current = current->next; 
    }
    return NULL; 
}


float deletovanie(HASH_TABLE *hash_table, KEY key) {
    unsigned int index = hashovanie(key, hash_table->velkost);
    OSOBA **current = &(hash_table->hashItem[index]);
    OSOBA *vymazat = NULL;

    while (*current) {
        if (porovnajKluc((*current)->key, key) == 0) {
            vymazat = *current;
            *current = (*current)->next;
            free(vymazat);
            return 0; 
        }
        current = &((*current)->next);
    }

    return 1; 
}


float updatovanie(HASH_TABLE *hash_table, KEY key, float update) {
    OSOBA *result = search(hash_table, key);
    if (result != NULL) {
        float suma = result->zostatok + update;
        if (suma >= 0) {
            result->zostatok = suma;
        } else {
            return -1;
        }
        return result->zostatok;
    } else {
        return -1;
    }
}


void printovanie(int *firstLinePrinted, const char* operation, float vysledok) {
    if (vysledok != 0) { 
        if (*firstLinePrinted) {
            printf("\n");
        } else {
            *firstLinePrinted = 1; 
        }
        printf("%s failed", operation);
    }
}


void freeHashTable(HASH_TABLE *hash_table) {
    for (int i = 0; i < hash_table->velkost; i++) {
        OSOBA *current = hash_table->hashItem[i];
        while (current != NULL) {
            OSOBA *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(hash_table->hashItem);
    free(hash_table);
}


void replaceChar(char *str, char find, char vymenit){
    for(int i = 0; str[i] != '\0'; i++){
        if (str[i] == find){
            str[i] = vymenit;
        }
    }
}


int main() {
    char znak, str[45];
    float update, vysledok, withoutcomma;
    int first_line = 0;
    int hashSize = 10000;
    OSOBA OSOBA_data, *result;
    HASH_TABLE *hash_table = create_hash_table(hashSize);;
    char bodka = '.', ciarka = ',';

    while (scanf(" %c", &znak) != EOF) {
        if(znak == 'i'){
            fgets(str, sizeof(str), stdin);
            replaceChar(str, ciarka, bodka);
            sscanf(str, "%s %s %s %f", OSOBA_data.key.krstne_meno, OSOBA_data.key.priezvisko, OSOBA_data.key.datum, &OSOBA_data.zostatok);
            vysledok = insert(hash_table, OSOBA_data);
            printovanie(&first_line, "insert", vysledok);
        }
        else if(znak == 's'){
            scanf("%s %s %s", OSOBA_data.key.krstne_meno, OSOBA_data.key.priezvisko, OSOBA_data.key.datum);
            result = search(hash_table, OSOBA_data.key);

            if (result != NULL) {
                withoutcomma = result->zostatok;
                char bezCiarky[20];
                sprintf(bezCiarky, "%.2f", withoutcomma);
                replaceChar(bezCiarky,bodka,ciarka);

                if (first_line != 0) {
                    printf("\n");
                } else           {
                    first_line = 1;
                }
                printf("%s", bezCiarky);
            } else {
                printovanie(&first_line, "search", 1); 
            }
        } else if(znak == 'd'){    
            scanf("%s %s %s", OSOBA_data.key.krstne_meno, OSOBA_data.key.priezvisko, OSOBA_data.key.datum);
            vysledok = deletovanie(hash_table, OSOBA_data.key);
            if (vysledok == 1) {
                printovanie(&first_line, "delete", vysledok);
            }
        } else if (znak == 'u'){
            fgets(str, sizeof(str), stdin);
            replaceChar(str, ciarka, bodka);
            sscanf(str, "%s %s %s %f", OSOBA_data.key.krstne_meno, OSOBA_data.key.priezvisko, OSOBA_data.key.datum, &update);
            vysledok = updatovanie(hash_table, OSOBA_data.key, update);
            if (vysledok < 0) {
                printovanie(&first_line, "update", vysledok);
            }
        }
    }
    return 0;
}