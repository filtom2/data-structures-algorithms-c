#include <stdio.h>
#include <stdlib.h>

#define INT_MAX 2147483647

typedef struct edge {
    int vrchol1;
    int vrchol2;
    int vaha;
    struct edge* next;
} EDGE;


typedef struct vertex{
    EDGE* head;  
} VERTEX;


typedef struct graph{
    VERTEX* vertices;
    int velkostGrafu;
} GRAPH;


typedef struct heapNode{
    int vertex; 
    int distance; 
} HEAPNODE;

typedef struct minHeap{
    HEAPNODE *nodes;
    int velkost;
    int kapacita;
    int *pozicia; 
} MINHEAP;


GRAPH* createGraph(int pocetVrcholov) {
    GRAPH* grafik = (GRAPH*)malloc(sizeof(GRAPH));
    if (!grafik) {
        return NULL;
    }
    grafik->velkostGrafu = pocetVrcholov;
    grafik->vertices = (VERTEX*)malloc(pocetVrcholov * sizeof(VERTEX));
    if (!grafik->vertices) { 
        free(grafik);
        return NULL;
    }
    for (int i = 0; i < pocetVrcholov; i++) {
        grafik->vertices[i].head = NULL;
    }
    return grafik;
}



int hranaExist(GRAPH* grafik, int v1, int v2) {
    EDGE* current1 = grafik->vertices[v1].head;
    while (current1 != NULL) {
        if (current1->vrchol2 == v2) {
            return 1;
        }
        current1 = current1->next;
    }
    EDGE* current2 = grafik->vertices[v2].head;
    while (current2 != NULL) {
        if (current2->vrchol2 == v1) {
            return 1;
        }
        current2 = current2->next;
    }
    return 0;
}


MINHEAP* createMinHeap(int kapacita) {
    MINHEAP *heap = (MINHEAP *)malloc(sizeof(MINHEAP));
    if (!heap) return NULL;
    heap->nodes = (HEAPNODE *)malloc(kapacita * sizeof(HEAPNODE));
    heap->pozicia = (int *)malloc(kapacita * sizeof(int));
    heap->kapacita = kapacita;
    heap->velkost = 0;
    if (!heap->nodes || !heap->pozicia) {
        free(heap->nodes);
        free(heap->pozicia);
        free(heap);
        return NULL;
    }
    for (int i = 0; i < kapacita; i++) {
        heap->nodes[i] = (HEAPNODE){i, INT_MAX};
        heap->pozicia[i] = i;
    }
    return heap;
}


void swapHeapNodes(HEAPNODE *a, HEAPNODE *b) {
    HEAPNODE temp = *a;
    *a = *b;
    *b = temp;
}


void upravMinHeap(MINHEAP *heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->velkost && heap->nodes[left].distance < heap->nodes[smallest].distance) {
        smallest = left;
    }
    if (right < heap->velkost && heap->nodes[right].distance < heap->nodes[smallest].distance) {
        smallest = right;
    }
    if (smallest != index) {
        heap->pozicia[heap->nodes[smallest].vertex] = index;
        heap->pozicia[heap->nodes[index].vertex] = smallest;
        swapHeapNodes(&heap->nodes[smallest], &heap->nodes[index]);
        upravMinHeap(heap, smallest);
    }
}


HEAPNODE extractMin(MINHEAP *heap) {
   if (heap->velkost <= 0) {
        return (HEAPNODE){-1, 0}; 
    }

    HEAPNODE root = heap->nodes[0];
    HEAPNODE lastNode = heap->nodes[heap->velkost - 1];
    heap->nodes[0] = lastNode;
    heap->pozicia[root.vertex] = heap->velkost - 1;
    heap->pozicia[lastNode.vertex] = 0;
    heap->velkost--;
    upravMinHeap(heap, 0);
    return root;
}

void decreaseKey(MINHEAP *heap, int vertexIndex, int vzdialenost) {
    int x = heap->pozicia[vertexIndex];
    heap->nodes[x].distance = vzdialenost;
    while (x != 0 && heap->nodes[x].distance < heap->nodes[(x - 1) / 2].distance) {
        heap->pozicia[heap->nodes[x].vertex] = (x - 1) / 2;
        heap->pozicia[heap->nodes[(x - 1) / 2].vertex] = x;
        swapHeapNodes(&heap->nodes[x], &heap->nodes[(x - 1) / 2]);
        x = (x - 1) / 2;
    }
}


int isInMinHeap(MINHEAP *heap, int IndexVrcholu) {
    return heap->pozicia[IndexVrcholu] < heap->velkost ? 1 : 0;
}



// void printPath(int parent[], int vrcholCesty) {
//     if (parent[vrcholCesty] == -1) {
//         printf("%d", vrcholCesty);
//         return;
//     }
//     printPath(parent, parent[vrcholCesty]);
//     printf(", %d", vrcholCesty);
// }


void printResults(int *firstLinePrinted, const char *message) {
    if (*firstLinePrinted) {
        printf("\n");
    }
    printf("%s failed", message);
    *firstLinePrinted = 1;
}



int printPathToString(int parent[], int vrcholCesty, char *output) {
    if (parent[vrcholCesty] == -1) {
        return sprintf(output, "%d", vrcholCesty);
    }
    int len = printPathToString(parent, parent[vrcholCesty], output);
    return len + sprintf(output + len, ", %d", vrcholCesty);
}




int deleteEdge(GRAPH* grafik, int v1, int v2) {
    int found = 0;
    EDGE **prev = &grafik->vertices[v1].head, *temp;
    while (*prev) {
        if ((*prev)->vrchol2 == v2) {
            temp = *prev;
            *prev = temp->next;
            free(temp);
            found = 1;
            break;
        }
        prev = &((*prev)->next);
    }

    prev = &grafik->vertices[v2].head;
    while (*prev) {
        if ((*prev)->vrchol2 == v1) {
            temp = *prev;
            *prev = temp->next;
            free(temp);
            found = 1;
            break;
        }
        prev = &((*prev)->next);
    }

    return found ? 0 : 1;  
}




int addEdgeToGraph(GRAPH* grafik, int zdroj, int ciel, int weight) {
    EDGE* newEdge = (EDGE*) malloc(sizeof(EDGE));
    if (!newEdge) {
        return 0; 
    }
    newEdge->vrchol1 = zdroj;
    newEdge->vrchol2 = ciel;
    newEdge->vaha = weight;
    newEdge->next = grafik->vertices[zdroj].head;
    grafik->vertices[zdroj].head = newEdge;
    return 1;
}


int insertEdge(GRAPH* grafik, int v1, int v2, int vaha) {
    if (v1 < 0 || v2 < 0 || v1 >= grafik->velkostGrafu || v2 >= grafik->velkostGrafu) {       
        return 1; 
    }
    if (v1 == v2) {
        return 1;
    }
    if (hranaExist(grafik, v1, v2)) {
        return 1;
    }
    if (!addEdgeToGraph(grafik, v1, v2, vaha) || !addEdgeToGraph(grafik, v2, v1, vaha)) {
        deleteEdge(grafik, v1, v2); 
        return 1;
    }
    return 0;
}



int updateEdge(GRAPH* grafik, int v1, int v2, int zmenaVahy) {
    int updated = 0;  
    if (!hranaExist(grafik, v1, v2)) return 1;

    for (EDGE* aktualnaHrana = grafik->vertices[v1].head; aktualnaHrana != NULL; aktualnaHrana = aktualnaHrana->next) {
        if (aktualnaHrana->vrchol2 == v2) {
            if (aktualnaHrana->vaha + zmenaVahy < 0) { 
                return -1; 
            }
            aktualnaHrana->vaha += zmenaVahy;
            updated = 1; 
            break; 
        }
    }

    for (EDGE* aktualnaHrana = grafik->vertices[v2].head; aktualnaHrana != NULL; aktualnaHrana = aktualnaHrana->next) {
        if (aktualnaHrana->vrchol2 == v1) {
            if (aktualnaHrana->vaha + zmenaVahy < 0) { 
                return -1;
            }
            aktualnaHrana->vaha += zmenaVahy;
            updated = 1;
            break;
        }
    }
    return updated ? 0 : -1;  
}



// int updateEdge(GRAPH* grafik, int v1, int v2, int zmenaVahy) {
//     if (!hranaExist(grafik, v1, v2)) return 1;  // Hrana neexistuje

//     int updated = 0;  
//     for (int i = 0; i < 2; i++) {
//         int src = i == 0 ? v1 : v2;  
//         int dst = i == 0 ? v2 : v1;  

//         for (EDGE* aktualnaHrana = grafik->vertices[src].head; aktualnaHrana != NULL; aktualnaHrana = aktualnaHrana->next) {
//             if (aktualnaHrana->vrchol2 == dst) {
//                 if (aktualnaHrana->vaha + zmenaVahy < 0) {  
//                     return 1;  
//                 }
//                 aktualnaHrana->vaha += zmenaVahy;
//                 updated = 1;
//                 break;
//             }
//         }
//     }

//     return updated ? 0 : 1;  
// }






int compareEdges(const void *a, const void *b) {
    EDGE *edge1 = (EDGE *)a;
    EDGE *edge2 = (EDGE *)b;
    int minVertex1 = edge1->vrchol1 < edge1->vrchol2 ? edge1->vrchol1 : edge1->vrchol2;
    int maxVertex1 = edge1->vrchol1 > edge1->vrchol2 ? edge1->vrchol1 : edge1->vrchol2;
    int minVertex2 = edge2->vrchol1 < edge2->vrchol2 ? edge2->vrchol1 : edge2->vrchol2;
    int maxVertex2 = edge2->vrchol1 > edge2->vrchol2 ? edge2->vrchol1 : edge2->vrchol2;

    if (minVertex1 != minVertex2) return minVertex1 - minVertex2;
    return maxVertex1 - maxVertex2;
}


void printMSTResult(EDGE mstEdges[], int mstSize, int *firstLinePrinted) {
    if (*firstLinePrinted) {
        printf("\n");
    } else {
        *firstLinePrinted = 1;
    }
    int totalWeight = 0;
    for (int i = 0; i < mstSize; i++) {
        if (mstEdges[i].vrchol1 > mstEdges[i].vrchol2) {
            int temp = mstEdges[i].vrchol1;
            mstEdges[i].vrchol1 = mstEdges[i].vrchol2;
            mstEdges[i].vrchol2 = temp;
        }
        totalWeight += mstEdges[i].vaha;
    }
    qsort(mstEdges, mstSize, sizeof(EDGE), compareEdges);

    printf("%d: [", totalWeight);
    for (int i = 0; i < mstSize; i++) {
        printf("(%d, %d)", mstEdges[i].vrchol1, mstEdges[i].vrchol2);
        if (i < mstSize - 1) {
            printf(", ");
        }
    }
    printf("]");
}





void search(GRAPH *grafik, int src, int *firstLinePrinted) {
    int V = grafik->velkostGrafu;
    if (src < 0 || src >= V) { 
        if (*firstLinePrinted) printf("\n");
        printf("search %d failed", src);
        *firstLinePrinted = 1;
        return;
    }
    int parent[V], key[V], mstSet[V];
    EDGE mstEdges[V-1];

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
        parent[i] = -1;
    }

    key[src] = 0;
    parent[src] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = -1, min = INT_MAX;

        for (int v = 0; v < V; v++) {
            if (mstSet[v] == 0 && key[v] < min) {
                min = key[v], u = v;
            }
        }

        if (u == -1) break;  
        mstSet[u] = 1;

        for (EDGE* p = grafik->vertices[u].head; p != NULL; p = p->next) {
            int v = p->vrchol2;
            if (mstSet[v] == 0 && p->vaha < key[v]) {
                parent[v] = u, key[v] = p->vaha;
            }
        }
    }

    int mstSize = 0;
    for (int i = 1; i < V; i++) {
        if (parent[i] != -1) {
            mstEdges[mstSize++] = (EDGE){parent[i], i, key[i]};
        }
    }

    if (mstSize > 0) {
        printMSTResult(mstEdges, mstSize, firstLinePrinted);
    } else {
        if (*firstLinePrinted) {
        printf("\n");
        }
        printf("search %d failed", src);
        *firstLinePrinted = 1;
    }
}






void freeGraph(GRAPH* grafik) {
    for (int i = 0; i < grafik->velkostGrafu; i++) {
        EDGE* current = grafik->vertices[i].head;
        while (current != NULL) {
            EDGE* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(grafik->vertices);
    free(grafik);
}


int main() {
    int N, v1, v2, weight;
    int firstLinePrinted = 0;
    char command;
    scanf("%d", &N);
    GRAPH* graf = createGraph(N);
    if (!graf) return 1;

    while (scanf(" (%d, %d, %d)", &v1, &v2, &weight) == 3) {
        if (insertEdge(graf, v1, v2, weight) != 0) {
            printResults(&firstLinePrinted, "insert");
        }
    }

    while (scanf(" %c", &command) != EOF) {
        switch (command) {
            case 'i':
                if (scanf(" %d %d %d", &v1, &v2, &weight) == 3) {
                    if (insertEdge(graf, v1, v2, weight) != 0) {
                        printResults(&firstLinePrinted, "insert");
                    }
                }
                break;
            case 'd':
                if (scanf(" %d %d", &v1, &v2) == 2) {
                    if (deleteEdge(graf, v1, v2) != 0) {
                        printResults(&firstLinePrinted, "delete");
                    }
                }
                break;
            case 's':
                if (scanf(" %d", &v1) == 1) {
                    search(graf, v1, &firstLinePrinted);
                }
                break;
            case 'u':
                if (scanf(" %d %d %d", &v1, &v2, &weight) == 3) {
                    if (updateEdge(graf, v1, v2, weight) != 0) {
                        printResults(&firstLinePrinted, "update");
                    }
                }
                break;
        }
    }

    freeGraph(graf);
    return 0;
}
