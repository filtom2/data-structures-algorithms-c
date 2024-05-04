
// // // int main() {
// // //     HASHTABLE* tabulka = vytvorTabulku(1000); // Zvýšenie veľkosti tabuľky pre lepšiu efektivitu
// // //     if (!tabulka) {
// // //         printf("Failed to create hash table\n");
// // //         return 1;
// // //     }

// // //     char operacia;
// // //     OSOBA* novaOsoba;
// // //     DATUM narodenie;
// // //     double zmenaZostatku;

// // //     while (scanf(" %c", &operacia) != EOF) {
// // //         switch (operacia) {
// // //             case 'i':
// // //                 novaOsoba = (OSOBA*)malloc(sizeof(OSOBA));
// // //                 if (scanf("%s %s %d.%d.%d %lf", novaOsoba->krstneMeno, novaOsoba->priezvisko, &narodenie.den, &narodenie.mesiac, &narodenie.rok, &novaOsoba->zostatok) == 6) {
// // //                     novaOsoba->narodenie = narodenie;
// // //                     novaOsoba->zostatok *= 100; // Konverzia na centy
// // //                     insert(tabulka, novaOsoba);
// // //                 } else {
// // //                     free(novaOsoba); // Uvoľnenie pamäte pri chybnom vstupe
// // //                     printf("insert failed\n");
// // //                 }
// // //                 break;
// // //             case 's':
// // //                 if (scanf("%s %s %d.%d.%d", narodenie.krstneMeno, narodenie.priezvisko, &narodenie.den, &narodenie.mesiac, &narodenie.rok) == 5) {
// // //                     search(tabulka, narodenie.krstneMeno, narodenie.priezvisko, narodenie);
// // //                 } else {
// // //                     printf("search failed\n");
// // //                 }
// // //                 break;
// // //             case 'u':
// // //                 if (scanf("%s %s %d.%d.%d %lf", narodenie.krstneMeno, narodenie.priezvisko, &narodenie.den, &narodenie.mesiac, &narodenie.rok, &zmenaZostatku) == 6) {
// // //                     update(tabulka, narodenie.krstneMeno, narodenie.priezvisko, narodenie, zmenaZostatku * 100); // Konverzia na centy
// // //                 } else {
// // //                     printf("update failed\n");
// // //                 }
// // //                 break;
// // //             case 'd':
// // //                 if (scanf("%s %s %d.%d.%d", narodenie.krstneMeno, narodenie.priezvisko, &narodenie.den, &narodenie.mesiac, &narodenie.rok) == 5) {
// // //                     delete(tabulka, narodenie.krstneMeno, narodenie.priezvisko, narodenie);
// // //                 } else {
// // //                     printf("delete failed\n");
// // //                 }
// // //                 break;
// // //             default:
// // //                 printf("%c failed\n", operacia); // V prípade neznámej operácie
// // //                 break;
// // //         }
// // //     }
// // //     uvolniTabulku(tabulka);
// // //     return 0;
// // // }





















// // // int main() {
// // //     HASHTABLE* tabulka = vytvorTabulku(100);
// // //     if (!tabulka) {
// // //         printf("Error creating hash table\n");
// // //         return 1;
// // //     }

// // //     char operacia;
// // //     char inputBuffer[1024]; // Adjust size as needed
// // //     int firstLinePrinted = 0;

// // //     while (scanf(" %c", &operacia) != EOF) {
// // //         fgets(inputBuffer, sizeof(inputBuffer), stdin);

// // //         // Replace comma with dot for atof conversion, if necessary
// // //         for (int i = 0; inputBuffer[i] != '\0' && i < sizeof(inputBuffer); i++) {
// // //             if (inputBuffer[i] == ',') {
// // //                 inputBuffer[i] = '.';
// // //             }
// // //         }

// // //         if (operacia == 'i') {
// // //             OSOBA novaOsoba;
// // //             // Assuming format: "FirstName LastName DD.MM.YYYY Balance"
// // //             if (sscanf(inputBuffer, "%19s %19s %d.%d.%d %lf", novaOsoba.krstneMeno, novaOsoba.priezvisko, &novaOsoba.narodenie.den, &novaOsoba.narodenie.mesiac, &novaOsoba.narodenie.rok, &novaOsoba.zostatok) == 6) {
// // //                 // Perform the insertion
// // //                 int outcome = insert(tabulka, &novaOsoba);
// // //                 if (outcome != 0) { // Assuming insert returns non-zero on failure
// // //                     if (firstLinePrinted) printf("\n");
// // //                     printf("insert failed");
// // //                     firstLinePrinted = 1;
// // //                 }
// // //             } else {
// // //                 if (firstLinePrinted) printf("\n");
// // //                 printf("insert failed");
// // //                 firstLinePrinted = 1;
// // //             }
// // //         } else if (operacia == 's') {
// // //             char krstneMeno[20], priezvisko[20];
// // //             DATUM narodenie;
// // //             // Assuming format: "FirstName LastName DD.MM.YYYY"
// // //             if (sscanf(inputBuffer, "%19s %19s %d.%d.%d", krstneMeno, priezvisko, &narodenie.den, &narodenie.mesiac, &narodenie.rok) == 5) {
// // //                 OSOBA* found = search(tabulka, krstneMeno, priezvisko, narodenie);
// // //                 if (found != NULL) {
// // //                     if (firstLinePrinted) printf("\n");
// // //                     // Assuming balance is stored as a double, convert back to comma for output
// // //                     printf("%.2lf", found->zostatok); // Modify to format output as needed
// // //                     firstLinePrinted = 1;
// // //                 } else {
// // //                     if (firstLinePrinted) printf("\n");
// // //                     printf("search failed");
// // //                     firstLinePrinted = 1;
// // //                 }
// // //             } else {
// // //                 if (firstLinePrinted) printf("\n");
// // //                 printf("search failed");
// // //                 firstLinePrinted = 1;
// // //             }
// // //         } else if (operacia == 'u') {
// // //             char krstneMeno[20], priezvisko[20];
// // //             DATUM narodenie;
// // //             double zmenaZostatku;
// // //             // Assuming format: "FirstName LastName DD.MM.YYYY BalanceChange"
// // //             if (sscanf(inputBuffer, "%19s %19s %d.%d.%d %lf", krstneMeno, priezvisko, &narodenie.den, &narodenie.mesiac, &narodenie.rok, &zmenaZostatku) == 6) {
// // //                 int outcome = update(tabulka, krstneMeno, priezvisko, narodenie, zmenaZostatku);
// // //                 if (outcome != 0) { // Assuming update returns non-zero on failure
// // //                     if (firstLinePrinted) printf("\n");
// // //                     printf("update failed");
// // //                     firstLinePrinted = 1;
// // //                 }
// // //             } else {
// // //                 if (firstLinePrinted) printf("\n");
// // //                 printf("update failed");
// // //                 firstLinePrinted = 1;
// // //             }
// // //         } else if (operacia == 'd') {
// // //             char krstneMeno[20], priezvisko[20];
// // //             DATUM narodenie;
// // //             // Assuming format: "FirstName LastName DD.MM.YYYY"
// // //             if (sscanf(inputBuffer, "%19s %19s %d.%d.%d", krstneMeno, priezvisko, &narodenie.den, &narodenie.mesiac, &narodenie.rok) == 5) {
// // //                 int outcome = delete(tabulka, krstneMeno, priezvisko, narodenie);
// // //                 if (outcome != 0) { // Assuming delete returns non-zero on failure
// // //                     if (firstLinePrinted) printf("\n");
// // //                     printf("delete failed");
// // //                     firstLinePrinted = 1;
// // //                 }
// // //             } else {
// // //                 if (firstLinePrinted) printf("\n");
// // //                 printf("delete failed");
// // //                 firstLinePrinted = 1;
// // //             }
// // //         }
// // //     }

// // //     // Free the hash table and its contents at the end, if applicable
// // //     // uvolniTabulku(tabulka);

// // //     return 0;
// // // }




































// #include <stdlib.h>
// #include <stdio.h>

// typedef struct datum {
//     int den;
//     int mesiac;
//     int rok;
// } DATUM;

// typedef struct osoba {
//     char krstneMeno[20];
//     char priezvisko[20];
//     DATUM narodenie; 
//     double zostatok;
// } OSOBA;

// typedef struct hashItem {
//     OSOBA* osoba;                  
//     struct hashItem* next;   
// } HASHITEM;


// typedef struct hashTable {
//     HASHITEM** polozky; 
//     int velkost;               
// } HASHTABLE;


// HASHTABLE* vytvorTabulku(int velkost){
//     HASHTABLE* tabulka = (HASHTABLE*)malloc(sizeof(HASHTABLE));
//     tabulka->velkost = velkost;
//     tabulka->polozky = (HASHITEM**)malloc(sizeof(HASHITEM*) * velkost);
    
//     for (int i = 0; i < velkost; i++) {
//         tabulka->polozky[i] = NULL;
//     }
    
//     return tabulka;

// }


// unsigned long hashovanie(HASHTABLE* tabulka, char* krstneMeno, char* priezvisko, int den, int mesiac, int rok) {
//     unsigned long hash = 0;
//     int docasna = 0; 

//     while ((docasna = *krstneMeno++) != '\0') { 
//         hash = hash * 31 + docasna;
//     }
//     while ((docasna = *priezvisko++) != '\0') {
//          hash = hash * 31 + docasna;
//     }
//     hash += den + 31 * (mesiac + 31 * rok);
//     return hash % tabulka->velkost;
// }



// int porovnajRetazce(const char* s1, const char* s2) {
//     while (*s1 && (*s1 == *s2)) {
//         s1++;
//         s2++;
//     }
//     return *(const unsigned char*)s1 - *(const unsigned char*)s2;
// }

// HASHITEM* najdi(HASHTABLE* tabulka, char* krstneMeno, char* priezvisko, DATUM narodenie) {
//     unsigned long index = hashovanie(tabulka, krstneMeno, priezvisko, narodenie.den, narodenie.mesiac, narodenie.rok);

    
//     for (HASHITEM* item = tabulka->polozky[index]; item != NULL; item = item->next) {
//         if (porovnajRetazce(item->osoba->krstneMeno, krstneMeno) == 0 &&
//             porovnajRetazce(item->osoba->priezvisko, priezvisko) == 0 &&
//             item->osoba->narodenie.den == narodenie.den &&
//             item->osoba->narodenie.mesiac == narodenie.mesiac &&
//             item->osoba->narodenie.rok == narodenie.rok) {
//             return item; 
//         }
//     }
//     return NULL; 
// }



// void insert(HASHTABLE* tabulka, OSOBA* novaOsoba) {
    
//     if (najdi(tabulka, novaOsoba->krstneMeno, novaOsoba->priezvisko, novaOsoba->narodenie) != NULL) {
//         printf("insert failed\n"); 
//         return;
//     }

    
//     unsigned long index = hashovanie(tabulka, novaOsoba->krstneMeno, novaOsoba->priezvisko, novaOsoba->narodenie.den, novaOsoba->narodenie.mesiac, novaOsoba->narodenie.rok);
//     HASHITEM* novaPolozka = (HASHITEM*)malloc(sizeof(HASHITEM));
//     if (!novaPolozka) {
//         printf("Insert failed\n"); 
//         return;
//     }

//     novaPolozka->osoba = novaOsoba;
//     novaPolozka->next = NULL;

   
//     if (!tabulka->polozky[index]) {
//         tabulka->polozky[index] = novaPolozka;
//     } else {
//         HASHITEM* aktualna = tabulka->polozky[index];
//         while (aktualna->next) {
//             aktualna = aktualna->next;
//         }
//         aktualna->next = novaPolozka;
//     }
// }


// void delete(HASHTABLE* tabulka, char* krstneMeno, char* priezvisko, DATUM narodenie) {
//     unsigned long index = hashovanie(tabulka, krstneMeno, priezvisko, narodenie.den, narodenie.mesiac, narodenie.rok);
//     HASHITEM* item = tabulka->polozky[index];
//     HASHITEM* predchadzajuci = NULL;

//     while (item != NULL) {
//         if (porovnajRetazce(item->osoba->krstneMeno, krstneMeno) == 0 &&
//             porovnajRetazce(item->osoba->priezvisko, priezvisko) == 0 &&
//             item->osoba->narodenie.den == narodenie.den &&
//             item->osoba->narodenie.mesiac == narodenie.mesiac &&
//             item->osoba->narodenie.rok == narodenie.rok) {
            
//             if (predchadzajuci == NULL) {
//                 tabulka->polozky[index] = item->next;
//             } else {
//                 predchadzajuci->next = item->next;
//             }
//             free(item->osoba); 
//             free(item); 
//             return;
//         }
//         predchadzajuci = item;
//         item = item->next;
//     }

//     printf("delete failed\n"); 
// }


// void search(HASHTABLE* tabulka, char* krstneMeno, char* priezvisko, DATUM narodenie) {
//     unsigned long index = hashovanie(tabulka, krstneMeno, priezvisko, narodenie.den, narodenie.mesiac, narodenie.rok);
//     HASHITEM* item = tabulka->polozky[index];

//     while (item != NULL) {
//         if (porovnajRetazce(item->osoba->krstneMeno, krstneMeno) == 0 &&
//             porovnajRetazce(item->osoba->priezvisko, priezvisko) == 0 &&
//             item->osoba->narodenie.den == narodenie.den &&
//             item->osoba->narodenie.mesiac == narodenie.mesiac &&
//             item->osoba->narodenie.rok == narodenie.rok) {
            
//             printf("Osoba: %s %s, Narodenie: %d.%d.%d, Zostatok: %.2f\n",
//                    item->osoba->krstneMeno, item->osoba->priezvisko,
//                    item->osoba->narodenie.den, item->osoba->narodenie.mesiac, item->osoba->narodenie.rok,
//                    item->osoba->zostatok / 100.0); 
//             return;
//         }
//         item = item->next;
//     }

    
//     printf("search failed\n");
// }

// void update(HASHTABLE* tabulka, char* krstneMeno, char* priezvisko, DATUM narodenie, long long zmenaZostatku) {
//     unsigned long index = hashovanie(tabulka, krstneMeno, priezvisko, narodenie.den, narodenie.mesiac, narodenie.rok);
//     HASHITEM* item = tabulka->polozky[index];

//     while (item != NULL) {
//         if (porovnajRetazce(item->osoba->krstneMeno, krstneMeno) == 0 &&
//             porovnajRetazce(item->osoba->priezvisko, priezvisko) == 0 &&
//             item->osoba->narodenie.den == narodenie.den &&
//             item->osoba->narodenie.mesiac == narodenie.mesiac &&
//             item->osoba->narodenie.rok == narodenie.rok) {
            
//             double novyZostatok = item->osoba->zostatok + zmenaZostatku;
//             if (novyZostatok < 0) {
//                 printf("update failed\n");
//                 return;
//             }
//             item->osoba->zostatok = novyZostatok;
//             return;
//         }
//         item = item->next;
//     }

   
//     printf("update failed\n");
// }


// void uvolniTabulku(HASHTABLE* tabulka) {
//     for (int i = 0; i < tabulka->velkost; i++) {
//         HASHITEM* item = tabulka->polozky[i];
//         while (item != NULL) {
//             HASHITEM* temp = item;
//             item = item->next;
//             free(temp->osoba);
//             free(temp);
//         }
//     }
//     free(tabulka->polozky);
//     free(tabulka);
// }





// int main() {
//     HASHTABLE* tabulka = vytvorTabulku(100); 
//     if (!tabulka) {
//         printf("Error creating hash table\n");
//         return 1;
//     }

//     char operacia;
//     char vstup[1024]; 
//     int firstLinePrinted = 0;

//     while (scanf(" %c", &operacia) != EOF) {
//         fgets(vstup, sizeof(vstup), stdin);

        
//         for (int i = 0; vstup[i] != '\0' && i < sizeof(vstup); i++) {
//             if (vstup[i] == ',') {
//                 vstup[i] = '.';
//             }
//         }

//         if (operacia == 'i') {
//             OSOBA novaOsoba;
//             if (sscanf(vstup, "%19s %19s %d.%d.%d %lf", novaOsoba.krstneMeno, novaOsoba.priezvisko, &novaOsoba.narodenie.den, &novaOsoba.narodenie.mesiac, &novaOsoba.narodenie.rok, &novaOsoba.zostatok) == 6) {
                
//                 insert(tabulka, &novaOsoba);
                
//             } else {
//                 if (firstLinePrinted) printf("\n");
//                 printf("insert failed");
//                 firstLinePrinted = 1;
//             }
//         } else if (operacia == 's') {
//             char krstneMeno[20], priezvisko[20];
//             DATUM narodenie;
//             if (sscanf(vstup, "%19s %19s %d.%d.%d", krstneMeno, priezvisko, &narodenie.den, &narodenie.mesiac, &narodenie.rok) == 5) {
                
//                 search(tabulka, krstneMeno, priezvisko, narodenie);
                
//             } else {
//                 if (firstLinePrinted) printf("\n");
//                 printf("search failed");
//                 firstLinePrinted = 1;
//             }
//         } else if (operacia == 'u') {
//             char krstneMeno[20], priezvisko[20];
//             DATUM narodenie;
//             double zmenaZostatku;
//             if (sscanf(vstup, "%19s %19s %d.%d.%d %lf", krstneMeno, priezvisko, &narodenie.den, &narodenie.mesiac, &narodenie.rok, &zmenaZostatku) == 6) {
                
//                 update(tabulka, krstneMeno, priezvisko, narodenie, zmenaZostatku);
                
//             } else {
//                 if (firstLinePrinted) printf("\n");
//                 printf("update failed");
//                 firstLinePrinted = 1;
//             }
//         } else if (operacia == 'd') {
//             char krstneMeno[20], priezvisko[20];
//             DATUM narodenie;
//             if (sscanf(vstup, "%19s %19s %d.%d.%d", krstneMeno, priezvisko, &narodenie.den, &narodenie.mesiac, &narodenie.rok) == 5) {
                
//                 delete(tabulka, krstneMeno, priezvisko, narodenie);
               
//             } else {
//                 if (firstLinePrinted) printf("\n");
//                 printf("delete failed");
//                 firstLinePrinted = 1;
//             }
//         }
//     }

  

//     return 0;
// }




























#include <stdlib.h>
#include <stdio.h>

typedef struct datum {
    int den;
    int mesiac;
    int rok;
} DATUM;

typedef struct osoba {
    char krstneMeno[20];
    char priezvisko[20];
    DATUM narodenie; 
    double zostatok;
} OSOBA;

typedef struct hashItem {
    OSOBA* osoba;                  
    struct hashItem* next;   
} HASHITEM;


typedef struct hashTable {
    HASHITEM** polozky; 
    int velkost;               
} HASHTABLE;


HASHTABLE* vytvorTabulku(int velkost){
    HASHTABLE* tabulka = (HASHTABLE*)malloc(sizeof(HASHTABLE));
    tabulka->velkost = velkost;
    tabulka->polozky = (HASHITEM**)malloc(sizeof(HASHITEM*) * velkost);
    
    for (int i = 0; i < velkost; i++) {
        tabulka->polozky[i] = NULL;
    }
    
    return tabulka;

}


unsigned long hashovanie(HASHTABLE* tabulka, char* krstneMeno, char* priezvisko, int den, int mesiac, int rok) {
    unsigned long hash = 0;
    int docasna = 0; 

    while ((docasna = *krstneMeno++) != '\0') { 
        hash = hash * 31 + docasna;
    }
    while ((docasna = *priezvisko++) != '\0') {
         hash = hash * 31 + docasna;
    }
    hash += den + 31 * (mesiac + 31 * rok);
    return hash % tabulka->velkost;
}



int porovnajRetazce(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

HASHITEM* najdi(HASHTABLE* tabulka, char* krstneMeno, char* priezvisko, DATUM narodenie) {
    unsigned long index = hashovanie(tabulka, krstneMeno, priezvisko, narodenie.den, narodenie.mesiac, narodenie.rok);

    
    for (HASHITEM* item = tabulka->polozky[index]; item != NULL; item = item->next) {
        if (porovnajRetazce(item->osoba->krstneMeno, krstneMeno) == 0 &&
            porovnajRetazce(item->osoba->priezvisko, priezvisko) == 0 &&
            item->osoba->narodenie.den == narodenie.den &&
            item->osoba->narodenie.mesiac == narodenie.mesiac &&
            item->osoba->narodenie.rok == narodenie.rok) {
            return item; 
        }
    }
    return NULL; 
}



int insert(HASHTABLE* tabulka, OSOBA* novaOsoba) {
    if (najdi(tabulka, novaOsoba->krstneMeno, novaOsoba->priezvisko, novaOsoba->narodenie) != NULL) {
        
        return 0;
    }
    unsigned long index = hashovanie(tabulka, novaOsoba->krstneMeno, novaOsoba->priezvisko, novaOsoba->narodenie.den, novaOsoba->narodenie.mesiac, novaOsoba->narodenie.rok);
    HASHITEM* novaPolozka = (HASHITEM*)malloc(sizeof(HASHITEM));
    if (!novaPolozka) { 
        return 0;
    }

    // novaPolozka->osoba = novaOsoba;
    // novaPolozka->next = NULL;

    novaPolozka->osoba = novaOsoba;
    novaPolozka->next = tabulka->polozky[index];
    tabulka->polozky[index] = novaPolozka;
    return 1;

    // if (!tabulka->polozky[index]) {
    //     tabulka->polozky[index] = novaPolozka;
    // } else {
    //     HASHITEM* aktualna = tabulka->polozky[index];
    //     while (aktualna->next) {
    //         aktualna = aktualna->next;
    //     }
    //     aktualna->next = novaPolozka;
    // }
}



int delete(HASHTABLE* tabulka, char* krstneMeno, char* priezvisko, DATUM narodenie) {
    unsigned long index = hashovanie(tabulka, krstneMeno, priezvisko, narodenie.den, narodenie.mesiac, narodenie.rok);
    HASHITEM* item = tabulka->polozky[index];
    HASHITEM* predchadzajuci = NULL;
    while (item != NULL) {
        if (porovnajRetazce(item->osoba->krstneMeno, krstneMeno) == 0 &&
            porovnajRetazce(item->osoba->priezvisko, priezvisko) == 0 &&
            item->osoba->narodenie.den == narodenie.den &&
            item->osoba->narodenie.mesiac == narodenie.mesiac &&
            item->osoba->narodenie.rok == narodenie.rok) {
            if (predchadzajuci == NULL) {
                tabulka->polozky[index] = item->next;
            } else {
                predchadzajuci->next = item->next;
            }
            free(item->osoba);
            free(item);
            return 1; 
        }
        predchadzajuci = item;
        item = item->next;
    }
    return 0; 
}




// void search(HASHTABLE* tabulka, char* krstneMeno, char* priezvisko, DATUM narodenie) {
//     unsigned long index = hashovanie(tabulka, krstneMeno, priezvisko, narodenie.den, narodenie.mesiac, narodenie.rok);
//     HASHITEM* item = tabulka->polozky[index];

//     int naslo = 0; 

//     while (item != NULL) {
//         if (porovnajRetazce(item->osoba->krstneMeno, krstneMeno) == 0 &&
//             porovnajRetazce(item->osoba->priezvisko, priezvisko) == 0 &&
//             item->osoba->narodenie.den == narodenie.den &&
//             item->osoba->narodenie.mesiac == narodenie.mesiac &&
//             item->osoba->narodenie.rok == narodenie.rok) {
            
//             printf("Osoba: %s %s, Narodenie: %d.%d.%d, Zostatok: %.2f\n",
//                    item->osoba->krstneMeno, item->osoba->priezvisko,
//                    item->osoba->narodenie.den, item->osoba->narodenie.mesiac, item->osoba->narodenie.rok,
//                    item->osoba->zostatok / 100.0); 
//             naslo = 1; 
//             break; 
//         }
//         item = item->next;
//     }

//     if (!naslo) {
//         printf("search failed\n"); 
//     }
// }




int search(HASHTABLE* tabulka, char* krstneMeno, char* priezvisko, DATUM narodenie) {
    HASHITEM* item = najdi(tabulka, krstneMeno, priezvisko, narodenie);
    if (item == NULL) {
        return 0; 
    }
    
    printf("Osoba: %s %s, Narodenie: %d.%d.%d, Zostatok: %.2f\n",
           item->osoba->krstneMeno, item->osoba->priezvisko,
           item->osoba->narodenie.den, item->osoba->narodenie.mesiac, item->osoba->narodenie.rok,
           item->osoba->zostatok / 100.0);
    return 1; 
}





int update(HASHTABLE* tabulka, char* krstneMeno, char* priezvisko, DATUM narodenie, double zmenaZostatku) {
    unsigned long index = hashovanie(tabulka, krstneMeno, priezvisko, narodenie.den, narodenie.mesiac, narodenie.rok);
    for (HASHITEM* item = tabulka->polozky[index]; item != NULL; item = item->next) {
        if (porovnajRetazce(item->osoba->krstneMeno, krstneMeno) == 0 &&
            porovnajRetazce(item->osoba->priezvisko, priezvisko) == 0 &&
            item->osoba->narodenie.den == narodenie.den &&
            item->osoba->narodenie.mesiac == narodenie.mesiac &&
            item->osoba->narodenie.rok == narodenie.rok) {
            
            double novyZostatok = item->osoba->zostatok + zmenaZostatku;
            if (novyZostatok < 0) {
                printf("update failed\n"); 
                return 0;
            }
            item->osoba->zostatok = novyZostatok;
            return 1; 
        }
    }
    printf("update failed\n"); 
    return 0;
}


void uvolniTabulku(HASHTABLE* tabulka) {
    for (int i = 0; i < tabulka->velkost; i++) {
        HASHITEM* item = tabulka->polozky[i];
        while (item != NULL) {
            HASHITEM* temp = item;
            item = item->next;
            free(temp->osoba);
            free(temp);
        }
    }
    free(tabulka->polozky);
    free(tabulka);
}




#include <stdio.h>
#include <stdlib.h>

// Zadefinujte štruktúry a funkcie tu, podľa potreby...

int main() {
    HASHTABLE* tabulka = vytvorTabulku(100);
    if (!tabulka) {
        printf("Error creating hash table\n");
        return 1;
    }

    char operacia;
    char vstup[1024];
    int podarilo; 

    while (scanf(" %c", &operacia) != EOF) {
        fgets(vstup, sizeof(vstup), stdin);

        
        for (int i = 0; vstup[i] != '\0' && i < sizeof(vstup); i++) {
            if (vstup[i] == ',') {
                vstup[i] = '.';
            }
        }

        switch (operacia) {
            case 'i': {
                OSOBA novaOsoba;
                if (sscanf(vstup, "%19s %19s %d.%d.%d %lf", novaOsoba.krstneMeno, novaOsoba.priezvisko, &novaOsoba.narodenie.den, &novaOsoba.narodenie.mesiac, &novaOsoba.narodenie.rok, &novaOsoba.zostatok) == 6) {
                    podarilo = insert(tabulka, &novaOsoba);
                    if (!podarilo) printf("insert failed\n");
                } else {
                    printf("insert failed\n");
                }
                break;
            }
            case 's': {
                char krstneMeno[20], priezvisko[20];
                DATUM narodenie;
                if (sscanf(vstup, "%19s %19s %d.%d.%d", krstneMeno, priezvisko, &narodenie.den, &narodenie.mesiac, &narodenie.rok) == 5) {
                    podarilo = search(tabulka, krstneMeno, priezvisko, narodenie);
                    if (!podarilo) printf("search failed\n");
                } else {
                    printf("search failed\n");
                }
                break;
            }
            case 'u': {
                char krstneMeno[20], priezvisko[20];
                DATUM narodenie;
                double zmenaZostatku;
                if (sscanf(vstup, "%19s %19s %d.%d.%d %lf", krstneMeno, priezvisko, &narodenie.den, &narodenie.mesiac, &narodenie.rok, &zmenaZostatku) == 6) {
                    podarilo = update(tabulka, krstneMeno, priezvisko, narodenie, zmenaZostatku);
                    if (!podarilo) printf("update failed\n");
                } else {
                    printf("update failed\n");
                }
                break;
            }
            case 'd': {
                char krstneMeno[20], priezvisko[20];
                DATUM narodenie;
                if (sscanf(vstup, "%19s %19s %d.%d.%d", krstneMeno, priezvisko, &narodenie.den, &narodenie.mesiac, &narodenie.rok) == 5) {
                    podarilo = delete(tabulka, krstneMeno, priezvisko, narodenie);
                    if (!podarilo) printf("delete failed\n");
                } else {
                    printf("delete failed\n");
                }
                break;
            }
            default:
                printf("Unknown operation '%c'\n", operacia);
                break;
        }
    }

   
    uvolniTabulku(tabulka);

    return 0;
}





// int main() {
//     HASHTABLE* tabulka = vytvorTabulku(100); 
//     if (!tabulka) {
//         printf("Error creating hash table\n");
//         return 1;
//     }

//     char operacia;
//     char vstup[1024]; 
//     int firstLinePrinted = 0;
//     int podarilo;

//     while (scanf(" %c", &operacia) != EOF) {
//         fgets(vstup, sizeof(vstup), stdin);

        
//         for (int i = 0; vstup[i] != '\0' && i < sizeof(vstup); i++) {
//             if (vstup[i] == ',') {
//                 vstup[i] = '.';
//             }
//         }

//         if (operacia == 'i') {
//             OSOBA novaOsoba;
//             if (sscanf(vstup, "%19s %19s %d.%d.%d %lf", novaOsoba.krstneMeno, novaOsoba.priezvisko, &novaOsoba.narodenie.den, &novaOsoba.narodenie.mesiac, &novaOsoba.narodenie.rok, &novaOsoba.zostatok) == 6) {
//                 podarilo = insert(tabulka, &novaOsoba);
//                 if (!podarilo){

//                 }
                
//             } else {
//                 if (firstLinePrinted) printf("\n");
//                 printf("insert failed");
//                 firstLinePrinted = 1;
//             }
//         } else if (operacia == 's') {
//             char krstneMeno[20], priezvisko[20];
//             DATUM narodenie;
//             if (sscanf(vstup, "%19s %19s %d.%d.%d", krstneMeno, priezvisko, &narodenie.den, &narodenie.mesiac, &narodenie.rok) == 5) {
                
//                 search(tabulka, krstneMeno, priezvisko, narodenie);
                
//             } else {
//                 if (firstLinePrinted) printf("\n");
//                 printf("search failed");
//                 firstLinePrinted = 1;
//             }
//         } else if (operacia == 'u') {
//             char krstneMeno[20], priezvisko[20];
//             DATUM narodenie;
//             double zmenaZostatku;
//             if (sscanf(vstup, "%19s %19s %d.%d.%d %lf", krstneMeno, priezvisko, &narodenie.den, &narodenie.mesiac, &narodenie.rok, &zmenaZostatku) == 6) {
                
//                 update(tabulka, krstneMeno, priezvisko, narodenie, zmenaZostatku);
                
//             } else {
//                 if (firstLinePrinted) printf("\n");
//                 printf("update failed");
//                 firstLinePrinted = 1;
//             }
//         } else if (operacia == 'd') {
//             char krstneMeno[20], priezvisko[20];
//             DATUM narodenie;
//             if (sscanf(vstup, "%19s %19s %d.%d.%d", krstneMeno, priezvisko, &narodenie.den, &narodenie.mesiac, &narodenie.rok) == 5) {
                
//                 delete(tabulka, krstneMeno, priezvisko, narodenie);
               
//             } else {
//                 if (firstLinePrinted) printf("\n");
//                 printf("delete failed");
//                 firstLinePrinted = 1;
//             }
//         }
//     }

  

//     return 0;
// }












