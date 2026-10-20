#include <stdio.h>
#include <stdlib.h>


typedef struct PERSON {
    int ID;
    char meno[15];
    char priezvisko[15];
    char datum[11];
} PERSON;

typedef struct NODE {
    PERSON data;
    struct NODE *vlavo;
    struct NODE *vpravo;
    int hlbka;
} NODE;


int maximum(int a, int b) { return (a > b) ? a : b; };
NODE* Minimum(NODE* node);
NODE* novyNODE(PERSON osoba);
NODE* insert(NODE* node, PERSON osoba);
int hlbka(NODE *N);
void print_actual(PERSON osoba);
NODE* rot_vlavo(NODE *c);
NODE* rot_vpravo(NODE *d);
NODE* search(NODE* koren, int ID);
int balance(NODE *N);
NODE* deleteNode(NODE* koren, int ID);
void searchRange(NODE* koren, int start, int end, int *newline_counter);
void spravnePoradie(int *start, int *end);

int main()
{
    PERSON osoba;
    NODE *koren = NULL;
    char vstup;
    int ID, start, end, counter; 
    int newline_counter = 1;

    while(scanf(" %c", &vstup) != EOF) 
    { 
        switch(vstup) 
        {
            case 'i':  // Insert 
                scanf("%d %49s %49s %10s", &osoba.ID, osoba.meno, osoba.priezvisko, osoba.datum);
                koren = insert(koren, osoba);
                break;
            
            case 's':  // Search 
                counter = scanf("%d %d", &start, &end);
                if (counter == 2)
                { 
                    spravnePoradie(&start,&end);
                    searchRange(koren, start, end,&newline_counter);
                }
                else
                {
                    NODE* result = search(koren, start); 
                    if (result != NULL)
                    {
                        if(newline_counter != 1)
                        {
                            printf("\n");

                        }
                        print_actual(result->data);
                        newline_counter=0;
                    } 
                }
                break;
                
            case 'd':  // Delete 
                scanf("%d", &ID);
                koren = deleteNode(koren, ID);
                break;
            
            default:
                break;
        }
    }

    free(koren);


    return 0;
}

int hlbka(NODE *N)
{
    if(N==NULL)
    {
        return 0;
    }
    return N->hlbka;
}

NODE* novyNODE(PERSON osoba)
{
    NODE* node = (NODE *)malloc(sizeof(NODE));
    node->data=osoba;
    node->vlavo=NULL;
    node->vpravo=NULL;
    node->hlbka=1;
    return node;

}

NODE *rot_vlavo(NODE *pivotNode)
{
   NODE *newRoot = pivotNode->vpravo;
   NODE *child = newRoot->vlavo;

   newRoot->vlavo = pivotNode;
   pivotNode->vpravo = child;

   pivotNode->hlbka = maximum(hlbka(pivotNode->vlavo), hlbka(pivotNode->vpravo)) + 1;
   newRoot->hlbka = maximum(hlbka(newRoot->vlavo), hlbka(newRoot->vpravo)) + 1;

   return newRoot;
}

NODE *rot_vpravo(NODE *newRoot)
{
    NODE *pivotNode = newRoot->vlavo;
    NODE *child = pivotNode->vpravo;

    pivotNode->vpravo = newRoot;
    newRoot->vlavo = child;

    newRoot->hlbka = maximum(hlbka(newRoot->vlavo), hlbka(newRoot->vpravo)) + 1;
    pivotNode->hlbka = maximum(hlbka(pivotNode->vlavo), hlbka(pivotNode->vpravo)) + 1;

    return pivotNode;
}

int balance(NODE *N)
{
    if(N==NULL)
    {
        return 0;
    }
    return hlbka(N->vlavo)-hlbka(N->vpravo);
}

NODE* insert(NODE* node,PERSON osoba)
{
    if(node==NULL)
    {
        return novyNODE(osoba);
    }
    if(osoba.ID < node->data.ID)
    {
        node->vlavo=insert(node->vlavo,osoba);
    }
    else if(osoba.ID > node->data.ID)
    {
        node->vpravo=insert(node->vpravo,osoba);
    }
    else
    {
        return node;
    }

    node->hlbka= 1+ maximum(hlbka(node->vlavo),hlbka(node->vpravo));
    int balanc=balance(node);

    if (balanc > 1 && osoba.ID < node->vlavo->data.ID)
    {
        return rot_vpravo(node);
    }
    if (balanc < -1 && osoba.ID > node->vpravo->data.ID)
    {   
        return rot_vlavo(node);
    }
    if (balanc > 1 && osoba.ID > node->vlavo->data.ID)
    {
        node->vlavo = rot_vlavo(node->vlavo);
        return rot_vpravo(node);
    }
    if (balanc < -1 && osoba.ID < node->vpravo->data.ID)
    {
        node->vpravo = rot_vpravo(node->vpravo);
        return rot_vlavo(node);
    }

    return node;
}

void print_actual(PERSON osoba)
{
    printf("%d %s %s %s", osoba.ID, osoba.meno, osoba.priezvisko, osoba.datum);
}

NODE* search(NODE* koren, int ID)
{
    if (koren == NULL || koren->data.ID == ID)
    {
        return koren;
    }
    if (koren->data.ID < ID)
    {
        return search(koren->vpravo, ID);
    }
    
    return search(koren->vlavo, ID);
}



NODE* Minimum(NODE* node)
{
    NODE* actual = node;
    while (actual->vlavo != NULL)
    {
        actual = actual->vlavo;
    }
    return actual;
}


NODE* deleteNode(NODE* koren, int ID)
{
    if (koren == NULL)
    {
        return koren;
    }
    
    if ( ID < koren->data.ID )
    {
        koren->vlavo = deleteNode(koren->vlavo, ID);
    }
    else if( ID > koren->data.ID )
    {
        koren->vpravo = deleteNode(koren->vpravo, ID);
    }
    else 
    {
        if((koren->vlavo == NULL) || (koren->vpravo == NULL))
        {
            NODE *tmp = koren->vlavo ? koren->vlavo : koren->vpravo;

            if (tmp == NULL)
            {
                tmp = koren;
                koren = NULL;
            }
            else
            {
                *koren = *tmp; 
            }

            free(tmp);
        }
        else
        {
            NODE* tmp = Minimum(koren->vpravo);
            koren->data = tmp->data;
            koren->vpravo = deleteNode(koren->vpravo, tmp->data.ID);
        }
    }

    if (koren == NULL)
    {
      return koren;
    }
    
    koren->hlbka = 1 + maximum(hlbka(koren->vlavo), hlbka(koren->vpravo));
    int balanc = balance(koren);

    if (balanc > 1 && balance(koren->vlavo) >= 0)
    {
        return rot_vpravo(koren);
    }
    
    if (balanc > 1 && balance(koren->vlavo) < 0)
    {
        koren->vlavo = rot_vlavo(koren->vlavo);
        return rot_vpravo(koren);
    }

    if (balanc < -1 && balance(koren->vpravo) <= 0)
    {
        return rot_vlavo(koren);
    }
    
    if (balanc < -1 && balance(koren->vpravo) > 0)
    {
        koren->vpravo = rot_vpravo(koren->vpravo);
        return rot_vlavo(koren);
    }

    return koren;
}



void searchRange(NODE* koren, int start, int end,int *newline_counter)
{
    if (koren == NULL)
    {
        return;
    }

    if(koren->data.ID >= start)
    {
        searchRange(koren->vlavo, start, end,newline_counter);
    }
    if(koren->data.ID >= start && koren->data.ID <= end)
    {
        if(*newline_counter != 1)
        {
            printf("\n");
        }

        print_actual(koren->data);
        *newline_counter = 0;
    }

    if(koren->data.ID <= end)
    {
        searchRange(koren->vpravo, start, end,newline_counter);
    }
}


void spravnePoradie(int *start,int *end)
{
    if(*end < *start)
    {
        int tmp = *end;
        *end = *start;
        *start = tmp; 
    }
}