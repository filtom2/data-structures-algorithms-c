#include <stdio.h>
#include <stdlib.h>

#define NEKONECNO 999999999   //QUICKSORT

typedef struct Hrana {
    int ciel;
    int vaha;
    struct Hrana* dalsi;
} Hrana;

typedef struct {
    int from;
    int to;
    int weight;
} Edge;


typedef struct { //Adjacency list
    Hrana** zoznamSusednosti;
    int pocetVrcholov;
} Graf;

/*typedef struct {
    int vrchol;
    int distance;
    int vaha;
} Node;*/

/*typedef struct {
    Edge* array;    
    int capacity;   
    int size;      
} MinHeap;*/

Graf* vytvorGraf(int pocetVrcholov) {
    Graf* graf = (Graf*)malloc(sizeof(Graf));
    graf->pocetVrcholov = pocetVrcholov;
    graf->zoznamSusednosti = (Hrana**)malloc(pocetVrcholov * sizeof(Hrana*));
    for (int i = 0; i < pocetVrcholov; i++) { //<
        graf->zoznamSusednosti[i] = NULL;
    }
    return graf;
}

/*MinHeap* vytvorMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!minHeap) {
        return NULL;
    }
    minHeap->capacity = capacity;
    minHeap->size = 0;
    minHeap->array = (Edge*)malloc(capacity * sizeof(Edge));
    if (!minHeap->array) {
        free(minHeap);
        return NULL;
    }
    return minHeap;
}*/
typedef struct {
    Edge* array;
    int capacity;
    int size;
    int *pos;  // Position map to track positions of vertices in the heap
} MinHeap;


MinHeap* vytvorMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->capacity = capacity;
    minHeap->size = 0;
    minHeap->array = (Edge*)malloc(capacity * sizeof(Edge));
    minHeap->pos = (int*)malloc(capacity * sizeof(int));  
    return minHeap;
}

void freeMinHeap(MinHeap* minHeap) {
    free(minHeap->array);
    free(minHeap->pos);
    free(minHeap);
}



/*void insertMinHeap(MinHeap* minHeap, Edge edge) {
    if (minHeap->size == minHeap->capacity) {
        return; // Heap is full, optionally resize the heap here
    }
    // Insert at the end and sift up
    minHeap->array[minHeap->size] = edge;
    int current = minHeap->size;
    minHeap->size++;
    while (current != 0 && minHeap->array[current].weight < minHeap->array[(current - 1) / 2].weight) {
        Edge temp = minHeap->array[current];
        minHeap->array[current] = minHeap->array[(current - 1) / 2];
        minHeap->array[(current - 1) / 2] = temp;
        current = (current - 1) / 2;
    }
}*/
void swapEdge(Edge* a, Edge* b) {
    Edge t = *a;
    *a = *b;
    *b = t;
}

void decreaseKey(MinHeap* minHeap, int v, int weight) {
    int i = minHeap->pos[v];
    minHeap->array[i].weight = weight;
    while (i != 0 && minHeap->array[i].weight < minHeap->array[(i - 1) / 2].weight) {
        minHeap->pos[minHeap->array[i].to] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2].to] = i;
        swapEdge(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void insertMinHeap(MinHeap* minHeap, Edge edge) {
    if (minHeap->size == minHeap->capacity) {
        return; // Optionally resize the heap here
    }
    int i = minHeap->size;
    minHeap->size++;
    minHeap->array[i] = edge;
    minHeap->pos[edge.to] = i;

    // Fix the min heap property if it is violated
    decreaseKey(minHeap, edge.to, edge.weight);
}



int prazdne(MinHeap* minHeap) {
    return minHeap->size == 0;
}

/*Node extractMin(MinHeap* minHeap) {
    if (prazdne(minHeap))
        return (Node){-1, -1};
    Node root = minHeap->array[0];
    Node lastNode = minHeap->array[minHeap->velkost - 1];
    minHeap->array[0] = lastNode;
    minHeap->pozicia[root.vrchol] = minHeap->velkost - 1;
    minHeap->pozicia[lastNode.vrchol] = 0;
    --minHeap->velkost;
    minHeapify(minHeap, 0);

    return root;
}*/
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left].weight < minHeap->array[smallest].weight)
        smallest = left;
    if (right < minHeap->size && minHeap->array[right].weight < minHeap->array[smallest].weight)
        smallest = right;

    if (smallest != idx) {
        Edge temp = minHeap->array[idx];
        minHeap->array[idx] = minHeap->array[smallest];
        minHeap->array[smallest] = temp;
        minHeapify(minHeap, smallest);
    }
}


Edge extractMin(MinHeap* minHeap) {
    if (minHeap->size <= 0)
        return (Edge){-1, -1, 0};
    if (minHeap->size == 1) {
        minHeap->size--;
        return minHeap->array[0];
    }

    // Move the last element to root and heapify down from root
    Edge root = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);
    return root;
}


/*int isInMinHeap(MinHeap* minHeap, int vrchol) {
    if (minHeap->pozicia[vrchol] < minHeap->velkost){ //< minHeap->pozicia[vrchol] >= 0 &&
        return 1;
    }
    return -1;
}*/


void new_line() {
    static int first_line = 1;
    if (!first_line) {
        printf("\n");
    }
    first_line = 0;
}

Hrana* vytvorHranu(int ciel, int vaha) {
    Hrana* novaHrana = (Hrana*)malloc(sizeof(Hrana));
    novaHrana->ciel = ciel;
    novaHrana->vaha = vaha;
    novaHrana->dalsi = NULL;
    return novaHrana;
}




/*void quicksort(Edge* edges, int zac, int kon) {
    if (zac < kon) {
        int index = zac;
        Edge pivot = edges[kon];
        for (int i = zac; i < kon; i++) {
            // Sort edges based on first vertex, and then by second vertex if first vertices are the same
            if ((edges[i].from < pivot.from) || (edges[i].from == pivot.from && edges[i].to < pivot.to)) {
                Edge pom = edges[i];
                edges[i] = edges[index];
                edges[index] = pom;
                index++;
            }
        }
        Edge pom2 = edges[index];
        edges[index] = edges[kon];
        edges[kon] = pom2;
        quicksort(edges, zac, index - 1);
        quicksort(edges, index + 1, kon);
    }
}*/


void quicksort(Edge* edges, int zac, int kon) {
    if (zac < kon) {
        int index = zac;
        Edge pivot = edges[kon];
        for (int i = zac; i < kon; i++) {
            if ((edges[i].from < pivot.from) || (edges[i].from == pivot.from && edges[i].to < pivot.to)) {
                swapEdge(&edges[i], &edges[index]);  // Using swapEdge function
                index++;
            }
        }
        swapEdge(&edges[index], &edges[kon]);  // Using swapEdge function
        quicksort(edges, zac, index - 1);
        quicksort(edges, index + 1, kon);
    }
}





/*void primMST(Graf* graf, int startVertex) {
    if (startVertex < 0 || startVertex >= graf->pocetVrcholov || graf->zoznamSusednosti[startVertex] == NULL) {
        printf("search %d failed\n", startVertex);
        return;
    }

    int V = graf->pocetVrcholov;
    int parent[V], key[V];
    char mstSet[V]; // This array keeps track of vertices included in MST
    unsigned long long mst_weight = 0;

    for (int i = 0; i < V; i++) {
        key[i] = NEKONECNO;
        mstSet[i] = 0;
        parent[i] = -1;
    }

    MinHeap* minHeap = vytvorMinHeap(V);
    key[startVertex] = 0;
    insertMinHeap(minHeap, (Edge){-1, startVertex, 0});

    /*while (!prazdne(minHeap)) {
        Edge minEdge = extractMin(minHeap);
        int u = minEdge.to;

        if (!mstSet[u]) {
            mstSet[u] = 1; // Mark this vertex as included in MST
            mst_weight += minEdge.weight;

            // For each adjacent vertex v of u, check if v is in mstSet
            for (Hrana* crawler = graf->zoznamSusednosti[u]; crawler != NULL; crawler = crawler->dalsi) {
                int v = crawler->ciel;
                if (!mstSet[v] && crawler->vaha < key[v]) {
                    key[v] = crawler->vaha;
                    parent[v] = u;
                    insertMinHeap(minHeap, (Edge){u, v, crawler->vaha});
                }
            }
        }
    }

    // Collect all edges in the MST for sorting and output.
    Edge* edges = malloc((V - 1) * sizeof(Edge));
    int count = 0;
    for (int i = 0; i < V; i++) {
        if (parent[i] != -1) {
            if (i < parent[i])
                edges[count++] = (Edge){i, parent[i], key[i]};
            else
                edges[count++] = (Edge){parent[i], i, key[i]};
        }
    }

    // Quicksort the edges for consistent output.
    quicksort(edges, 0, count - 1);

    printf("%llu: [", mst_weight);
    for (int i = 0; i < count; i++) {
        printf("(%d, %d)", edges[i].from, edges[i].to);
        if (i < count - 1) printf(", ");
    }
    printf("]\n");

    free(edges);
    freeMinHeap(minHeap);
}
*/
void primMST(Graf* graf, int startVertex) {
    if (startVertex < 0 || startVertex >= graf->pocetVrcholov || graf->zoznamSusednosti[startVertex] == NULL) {
        printf("search %d failed\n", startVertex);
        return;
    }

    int V = graf->pocetVrcholov;
    int parent[V], key[V];
    char mstSet[V]; // This array keeps track of vertices included in MST
    unsigned long long mst_weight = 0;

    for (int i = 0; i < V; i++) {
        key[i] = NEKONECNO;
        mstSet[i] = 0;
        parent[i] = -1;
    }

    MinHeap* minHeap = vytvorMinHeap(V);
    for (int i = 0; i < V; i++) {
        minHeap->pos[i] = i;
        minHeap->array[i] = (Edge){-1, i, key[i]};
    }
    minHeap->size = V;
    decreaseKey(minHeap, startVertex, 0);

    while (!prazdne(minHeap)) {
        Edge minEdge = extractMin(minHeap);
        int u = minEdge.to;

        mstSet[u] = 1; // Mark this vertex as included in MST
        mst_weight += minEdge.weight;

        // For each adjacent vertex v of u, check if v is in mstSet
        for (Hrana* crawler = graf->zoznamSusednosti[u]; crawler != NULL; crawler = crawler->dalsi) {
            int v = crawler->ciel;
            if (!mstSet[v] && crawler->vaha < key[v]) {
                key[v] = crawler->vaha;
                parent[v] = u;
                decreaseKey(minHeap, v, crawler->vaha);
            }
        }
    }

    // Output edges and weight
    printf("%llu: [", mst_weight);
    for (int i = 0; i < V; i++) {
        if (parent[i] != -1) {
            printf("(%d, %d)", parent[i], i);
            if (i < V - 1) printf(", ");
        }
    }
    printf("]\n");

    //free(edges);
    freeMinHeap(minHeap);
}




int vlozHranu(Graf* graf, int zaciatok, int ciel, int vaha) {
    if (zaciatok < 0 || ciel < 0 || zaciatok >= graf->pocetVrcholov || ciel >= graf->pocetVrcholov || zaciatok == ciel) {
        //printf("Insert failed: Invalid indices or same vertex (%d, %d)\n", zaciatok, ciel);
        return 0;
    }

    
    Hrana* explorer_zaciatok = graf->zoznamSusednosti[zaciatok];
    while (explorer_zaciatok != NULL) {
        if (explorer_zaciatok->ciel == ciel) {
            //printf("Insert failed: Edge already exists (%d, %d)\n", zaciatok, ciel);
            return 0;
        }
        explorer_zaciatok = explorer_zaciatok->dalsi;
    }

    Hrana* explorer_ciel = graf->zoznamSusednosti[ciel];
    while (explorer_ciel != NULL) {
        if (explorer_ciel->ciel == zaciatok) {
            //printf("Insert failed: Edge already exists (%d, %d)\n", ciel, zaciatok);
            return 0;
        }
        explorer_ciel = explorer_ciel->dalsi;
    }

    // Add edge from zaciatok to ciel
    Hrana* newEdge = vytvorHranu(ciel, vaha);
    newEdge->dalsi = graf->zoznamSusednosti[zaciatok];
    graf->zoznamSusednosti[zaciatok] = newEdge;

    // Add edge from ciel to zaciatok
    newEdge = vytvorHranu(zaciatok, vaha);
    newEdge->dalsi = graf->zoznamSusednosti[ciel];
    graf->zoznamSusednosti[ciel] = newEdge;

    //printf("Edge successfully inserted: %d <-> %d with weight %d\n", zaciatok, ciel, vaha);
    return 1;
}



//delete
/*int odstranHranu(Graf* graf, int zaciatok, int ciel) {
    if (zaciatok < 0 || ciel < 0 || zaciatok >= graf->pocetVrcholov || ciel >= graf->pocetVrcholov) {
        new_line();
        printf("delete %d %d failed", zaciatok, ciel);
        return 0;
    }
    Hrana** curr = &graf->zoznamSusednosti[zaciatok];
    int removed = 0;
    while (*curr != NULL) {
        Hrana* entry = *curr;
        if (entry->ciel == ciel) {
            *curr = entry->dalsi;
            free(entry);
            removed = 1; 
            break;
        }
        curr = &entry->dalsi;
    }

    if (removed) {
        removed = 0; 
        curr = &graf->zoznamSusednosti[ciel];
        while (*curr != NULL) {
            Hrana* entry = *curr;
            if (entry->ciel == zaciatok) {
                *curr = entry->dalsi;
                free(entry);
                removed = 1; 
                break;
            }
            curr = &entry->dalsi;
        }
    }

    if (!removed) {
        new_line();
        printf("delete %d %d failed", zaciatok, ciel);
    }

    return removed; 
}*/


int odstranHranu(Graf* graf, int zaciatok, int ciel) {
    if (zaciatok < 0 || ciel < 0 || zaciatok >= graf->pocetVrcholov || ciel >= graf->pocetVrcholov) {
        new_line();
        //printf("delete %d %d failed", zaciatok, ciel);
        return 0;
    }

    // Remove edge from zaciatok to ciel
    Hrana** curr = &graf->zoznamSusednosti[zaciatok];
    int removed = 0;
    while (*curr != NULL) {
        Hrana* entry = *curr;
        if (entry->ciel == ciel) {
            *curr = entry->dalsi;
            free(entry);
            removed = 1; 
            break;
        }
        curr = &entry->dalsi;
    }

    if (!removed) {
        new_line();
        //printf("delete %d %d failed", zaciatok, ciel);
        return 0;
    }

    // Remove edge from ciel to zaciatok
    curr = &graf->zoznamSusednosti[ciel];
    while (*curr != NULL) {
        Hrana* entry = *curr;
        if (entry->ciel == zaciatok) {
            *curr = entry->dalsi;
            free(entry);
            break;
        }
        curr = &entry->dalsi;
    }

    return 1; 
}




//update
/*int aktualizujHranu(Graf* graf, int zaciatok, int ciel, int zmenaVahy) {
    int aktualizovane = 0;
    Hrana* ptr = graf->zoznamSusednosti[zaciatok];
    while (ptr != NULL) {
        if (ptr->ciel == ciel) {
            if (ptr->vaha + zmenaVahy >= 0) {
                ptr->vaha += zmenaVahy;
                aktualizovane = 1;
            } else {
                new_line();
                printf("update %d %d failed", zaciatok, ciel);
                return 0;
            }
            break;
        }
        ptr = ptr->dalsi;
    }

    ptr = graf->zoznamSusednosti[ciel];
    while (ptr != NULL && aktualizovane) {
        if (ptr->ciel == zaciatok) {
            ptr->vaha += zmenaVahy;
            break;
        }
        ptr = ptr->dalsi;
    }

    if (!aktualizovane) {
        new_line();
        printf("update %d %d failed", zaciatok, ciel);
        return 0;
    }

    return 1; // Success
}*/
int aktualizujHranu(Graf* graf, int zaciatok, int ciel, int zmenaVahy) {
    int aktualizovane = 0;
    Hrana* ptr = graf->zoznamSusednosti[zaciatok];
    while (ptr != NULL) {
        if (ptr->ciel == ciel) {
            if (ptr->vaha + zmenaVahy >= 0) {
                ptr->vaha += zmenaVahy;
                aktualizovane = 1;
            } else {
                new_line();
                printf("update %d %d failed: weight would be negative\n", zaciatok, ciel);
                return 0;
            }
            break;
        }
        ptr = ptr->dalsi;
    }

    if (aktualizovane) {
       
        ptr = graf->zoznamSusednosti[ciel];
        while (ptr != NULL) {
            if (ptr->ciel == zaciatok) {
                ptr->vaha += zmenaVahy;
                break;
            }
            ptr = ptr->dalsi;
        }
        return 1; // Success
    } else {
        new_line();
        printf("update %d %d failed: edge not found\n", zaciatok, ciel);
        return 0;
    }
}








void uvolniGraf(Graf* graf) {
    if (graf == NULL) return;
    
    for (int i = 0; i < graf->pocetVrcholov; i++) {
        Hrana* hrana = graf->zoznamSusednosti[i];
        while (hrana != NULL) {
            Hrana* temp = hrana;
            hrana = hrana->dalsi;
            free(temp);
        }
    }
    free(graf->zoznamSusednosti);
    free(graf);
}

int main() {
    int N;
    scanf("%d", &N);
    Graf* graf = vytvorGraf(N);

    for (int i = 0; i < N; i++) {
        int zaciatok, ciel;
        long long vaha;
        scanf(" (%d, %d, %lld)", &zaciatok, &ciel, &vaha);
        vlozHranu(graf, zaciatok, ciel, vaha);
    }

    char operacia;
    int zaciatok, ciel;
    long long vaha;

    while (scanf(" %c", &operacia) != EOF) {
        switch (operacia) {
            case 'i':
                if (scanf(" %d %d %lld", &zaciatok, &ciel, &vaha) == 3) {
                    //printf("Trying to insert edge between %d and %d with weight %d\n", zaciatok, ciel, vaha);
                    vlozHranu(graf, zaciatok, ciel, vaha);
                }
                break;
            case 'd':
                if (scanf(" %d %d", &zaciatok, &ciel) == 2) {
                    odstranHranu(graf, zaciatok, ciel);
                }
                break;
            case 'u':
                if (scanf(" %d %d %lld", &zaciatok, &ciel, &vaha) == 3) {
                    aktualizujHranu(graf, zaciatok, ciel, vaha);
                }
                break;
            case 's':
                if (scanf(" %d", &zaciatok) == 1) {
                    primMST(graf, zaciatok);
                }
                break;
        }
    }

    uvolniGraf(graf);
    return 0;
}