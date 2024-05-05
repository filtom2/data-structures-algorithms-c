#include <stdio.h>
#include <stdlib.h>

#define NEKONECNO 999999999

typedef struct Hrana {
    int ciel;
    int vaha;
    struct Hrana* dalsi;
} Hrana;

typedef struct edge{
    int from;
    int to;
    int weight;
} Edge;


typedef struct {
    Hrana** zoznamSusednosti;
    int pocetVrcholov;
} Graf;


Graf* vytvorGraf(int pocetVrcholov) {
    Graf* graf = (Graf*)malloc(sizeof(Graf));
    graf->pocetVrcholov = pocetVrcholov;
    graf->zoznamSusednosti = (Hrana**)malloc(pocetVrcholov * sizeof(Hrana*));
    for (int i = 0; i < pocetVrcholov; i++) { //<
        graf->zoznamSusednosti[i] = NULL;
    }
    return graf;
}

typedef struct {
    Edge* array;
    int capacity;
    int size;
    int *pos;
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

    decreaseKey(minHeap, edge.to, edge.weight);
}



int prazdne(MinHeap* minHeap) {
    return minHeap->size == 0;
}

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

    Edge root = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);
    return root;
}

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


void sort_dvojice(Edge *edge) {
    if (edge->from > edge->to) {
        int temp = edge->from;
        edge->from = edge->to;
        edge->to = temp;
    }
}

int compareEdges(const void* a, const void* b) {
    Edge* edge1 = (Edge*)a;
    Edge* edge2 = (Edge*)b;

    if (edge1->from != edge2->from) {
        return (edge1->from - edge2->from);
    } else {
        return (edge1->to - edge2->to);
    }
}

int primMST(Graf* graf, int startVertex, int first_line) {
    if (startVertex < 0 || startVertex >= graf->pocetVrcholov || graf->zoznamSusednosti[startVertex] == NULL) {
        if (first_line != 0) {
            printf("\n");
        } else {
            first_line = 1;
        }
        printf("search %d failed", startVertex);
        return first_line;
    }

    int V = graf->pocetVrcholov;
    int parent[V], key[V];
    char mstSet[V];
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

        mstSet[u] = 1;
        mst_weight += minEdge.weight;

        for (Hrana* crawler = graf->zoznamSusednosti[u]; crawler != NULL; crawler = crawler->dalsi) {
            int v = crawler->ciel;
            if (!mstSet[v] && crawler->vaha < key[v]) {
                key[v] = crawler->vaha;
                parent[v] = u;
                decreaseKey(minHeap, v, crawler->vaha);
            }
        }
    }

    Edge edges[V-1];
    int edgeCount = 0;
    for (int i = 0; i < V; i++) {
        if (parent[i] != -1) {
            edges[edgeCount++] = (Edge){parent[i], i, key[i]};
        }
    }

    if(mst_weight == 0){
        if (first_line != 0) {
            printf("\n");
        }
        else {
            first_line = 1;
        }
        printf("search %d failed", startVertex);
        return first_line;
    }
    if (first_line != 0) {
        printf("\n");
    }
    else {
        first_line = 1;
    }

    for (int i = 0; i < edgeCount; i++) {
        sort_dvojice(&edges[i]);
    }
    qsort(edges, edgeCount, sizeof(Edge), compareEdges);

    printf("%llu: [", mst_weight);
    for (int i = 0; i < edgeCount; i++) {
        if (i > 0)
            printf(", ");
        printf("(%d, %d)", edges[i].from, edges[i].to);
    }
    printf("]");
    freeMinHeap(minHeap);
    return first_line;
}

int vlozHranu(Graf* graf, int zaciatok, int ciel, int vaha) {
    if (zaciatok < 0 || ciel < 0 || zaciatok >= graf->pocetVrcholov || ciel >= graf->pocetVrcholov || zaciatok == ciel) {
        return -1;
    }


    Hrana* explorer_zaciatok = graf->zoznamSusednosti[zaciatok];
    while (explorer_zaciatok != NULL) {
        if (explorer_zaciatok->ciel == ciel) {
            return -1;
        }
        explorer_zaciatok = explorer_zaciatok->dalsi;
    }

    Hrana* explorer_ciel = graf->zoznamSusednosti[ciel];
    while (explorer_ciel != NULL) {
        if (explorer_ciel->ciel == zaciatok) {
            return -1;
        }
        explorer_ciel = explorer_ciel->dalsi;
    }

    Hrana* newEdge = vytvorHranu(ciel, vaha);
    newEdge->dalsi = graf->zoznamSusednosti[zaciatok];
    graf->zoznamSusednosti[zaciatok] = newEdge;

    newEdge = vytvorHranu(zaciatok, vaha);
    newEdge->dalsi = graf->zoznamSusednosti[ciel];
    graf->zoznamSusednosti[ciel] = newEdge;
    return 0;
}




int odstranHranu(Graf* graf, int zaciatok, int ciel) {
    if (zaciatok < 0 || ciel < 0 || zaciatok >= graf->pocetVrcholov || ciel >= graf->pocetVrcholov) {
        return -1;
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

    if (!removed) {
        return -1;
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

    return 0;
}

int aktualizujHranu(Graf* graf, int zaciatok, int ciel, int zmenaVahy) {
    int aktualizovane = 0;
    Hrana* ptr = graf->zoznamSusednosti[zaciatok];
    while (ptr != NULL) {
        if (ptr->ciel == ciel) {
            if (ptr->vaha + zmenaVahy >= 0) {
                ptr->vaha += zmenaVahy;
                aktualizovane = 1;
            } else {
                return -1;
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
        return 0;
    } else {
        return -1;
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
    int N, first_line = 0, zaciatok, ciel;
    char operacia;
    long long vaha;
    scanf("%d", &N);
    Graf* graf = vytvorGraf(N+1);


    while (scanf(" %c", &operacia) != EOF) {
        switch (operacia) {
            case '(':
                scanf(" %d, %d, %lld)", &zaciatok, &ciel, &vaha);
                if(vlozHranu(graf, zaciatok, ciel, vaha) == -1) {
                    if (first_line != 0) {
                        printf("\n");
                    } else {
                        first_line = 1;
                    }
                    printf("insert %d %d failed", zaciatok, ciel);
                    }
                break;
            case 'i':
                scanf(" %d %d %lld", &zaciatok, &ciel, &vaha);
                if(vlozHranu(graf, zaciatok, ciel, vaha) == -1){
                    if (first_line != 0) {
                        printf("\n");
                    } else {
                        first_line = 1;
                    }
                    printf("insert %d %d failed", zaciatok, ciel);
                }
                break;
            case 'd':
                scanf(" %d %d", &zaciatok, &ciel);
                if(odstranHranu(graf, zaciatok, ciel) == -1){
                    if (first_line != 0) {
                        printf("\n");
                    } else {
                        first_line = 1;
                    }
                    printf("delete %d %d failed", zaciatok, ciel);
                    }
                break;
            case 'u':
                scanf(" %d %d %lld", &zaciatok, &ciel, &vaha) ;
                if(aktualizujHranu(graf, zaciatok, ciel, vaha)== -1){
                    if (first_line != 0) {
                        printf("\n");
                    } else {
                        first_line = 1;
                    }
                    printf("update %d %d failed", zaciatok, ciel);
                }
                break;
            case 's':
                scanf(" %d", &zaciatok);
                first_line = primMST(graf, zaciatok, first_line);
                break;
        }
    }

    uvolniGraf(graf);
    return 0;
}