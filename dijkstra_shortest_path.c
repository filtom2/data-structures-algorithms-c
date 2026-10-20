/*
10 2
(1, 2, 10)
(2, 3, 100)
i 1 5 10
i 5 3 100
s 1 3
s 3 1 

vystup:
110: [1, 5, 3]
110: [3, 5, 1]
*/

#include <stdio.h>
#include <stdlib.h>

#define INT_MAX 2147483647 // max positive 32b integer

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
    int velkost_grafu;
} GRAPH;


typedef struct heap_node{
    int vertex; 
    int distance; 
} HEAPNODE;

typedef struct min_heap{
    HEAPNODE *nodes;
    int velkost;
    int kapacita;
    int *pozicia; 
} MINHEAP;


GRAPH* create_graph(int pocet_vrcholov);
int hrana_exist(GRAPH* hl_graf, int v1, int v2);
MINHEAP* create_min_heap(int kapacita);
void swap_heap_nodes(HEAPNODE *a, HEAPNODE *b);
void uprav_min_heap(MINHEAP *heap, int index);
HEAPNODE extract_min(MINHEAP *heap);
void decrease_key(MINHEAP *heap, int vertex_index, int vzdialenost);
int is_in_min_heap(MINHEAP *heap, int index_vrcholu);
int delete_edge(GRAPH* hl_graf, int v1, int v2);
int add_edge_to_graph(GRAPH* hl_graf, int zdroj, int ciel, int weight);
int insert_edge(GRAPH* hl_graf, int v1, int v2, int vaha);
void print_path(int parent[], int vrchol_cesty);
void print_results(int *first_line_printed, const char *message);
int print_path_to_string(int parent[], int vrchol_cesty, char *output);
void search(GRAPH* hl_graf, int zdroj, int ciel, int *first_line_printed);
int update_edge(GRAPH* hl_graf, int v1, int v2, int zmena_vahy);
void free_graph(GRAPH* hl_graf);


int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    char option;
    int zdroj, ciel;
    int zmena_vahy;
    GRAPH* hl_graf = create_graph(N);
    if (hl_graf == NULL) 
    {
        return 1;
    }

    int v1, v2, vaha, first_line_printed = 0;
    char parent1, parent2, comma1, comma2;
    for (int i = 0; i < M; i++) 
    {
        scanf(" %c%d%c%d%c%d%c", &parent1, &v1, &comma1, &v2, &comma2, &vaha, &parent2);
        if (insert_edge(hl_graf, v1, v2, vaha) == 1) {
            // char vypis_chyby[50];
            char *vypis_chyby = (char*)malloc(64 * sizeof(char));
                sprintf(vypis_chyby, "insert %d %d failed", v1, v2);
                print_results(&first_line_printed, vypis_chyby);
        }
    }

    while (scanf(" %c", &option) != EOF) {
        switch (option) {
        case 'u':
            scanf("%d %d %d", &v1, &v2, &zmena_vahy);
            if (update_edge(hl_graf, v1, v2, zmena_vahy) != 0) {
                char vypis_chyby[50];
                sprintf(vypis_chyby, "update %d %d failed", v1, v2);
                print_results(&first_line_printed, vypis_chyby);
            }
            break;

        case 's':
            scanf("%d %d", &zdroj, &ciel);
            search(hl_graf, zdroj, ciel, &first_line_printed);
            break;

        case 'd':
            scanf("%d %d", &v1, &v2);
            if (delete_edge(hl_graf, v1, v2) == 0) {
                char vypis_chyby[50];
                sprintf(vypis_chyby, "delete %d %d failed", v1, v2);
                print_results(&first_line_printed, vypis_chyby);
            }
            break;

        case 'i':
            scanf(" %d%c%d%c%d", &v1, &comma1, &v2, &comma2, &vaha);
            if (insert_edge(hl_graf, v1, v2, vaha) == 1) {
                char vypis_chyby[50];
                sprintf(vypis_chyby, "insert %d %d failed", v1, v2);
                print_results(&first_line_printed, vypis_chyby);
            }
            break;
        }
    }
    free_graph(hl_graf);
    return 0;
}


GRAPH* create_graph(int pocet_vrcholov) {
    GRAPH* hl_graf = (GRAPH*)malloc(sizeof(GRAPH));
    if (!hl_graf) {
        return NULL;
    }
    hl_graf->velkost_grafu = pocet_vrcholov;
    hl_graf->vertices = (VERTEX*)malloc(pocet_vrcholov * sizeof(VERTEX));
    if (!hl_graf->vertices) { 
        free(hl_graf);
        return NULL;
    }
    for (int i = 0; i < pocet_vrcholov; i++) {
        hl_graf->vertices[i].head = NULL;
    }
    return hl_graf;
}

int hrana_exist(GRAPH* hl_graf, int v1, int v2) {
    EDGE* current1 = hl_graf->vertices[v1].head;
    while (current1 != NULL) {
        if (current1->vrchol2 == v2) {
            return 1;
        }
        current1 = current1->next;
    }
    EDGE* current2 = hl_graf->vertices[v2].head;
    while (current2 != NULL) {
        if (current2->vrchol2 == v1) {
            return 1;
        }
        current2 = current2->next;
    }
    return 0;
}

MINHEAP* create_min_heap(int kapacita) {
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

void swap_heap_nodes(HEAPNODE *a, HEAPNODE *b) {
    HEAPNODE temp = *a;
    *a = *b;
    *b = temp;
}

void uprav_min_heap(MINHEAP *heap, int index) {
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
        swap_heap_nodes(&heap->nodes[smallest], &heap->nodes[index]);
        uprav_min_heap(heap, smallest);
    }
}

HEAPNODE extract_min(MINHEAP *heap) {
   if (heap->velkost <= 0) {
        return (HEAPNODE){-1, 0}; 
    }

    HEAPNODE root = heap->nodes[0];
    HEAPNODE lastNode = heap->nodes[heap->velkost - 1];
    heap->nodes[0] = lastNode;
    heap->pozicia[root.vertex] = heap->velkost - 1;
    heap->pozicia[lastNode.vertex] = 0;
    heap->velkost--;
    uprav_min_heap(heap, 0);
    return root;
}

void decrease_key(MINHEAP *heap, int vertex_index, int vzdialenost) {
    int x = heap->pozicia[vertex_index];
    heap->nodes[x].distance = vzdialenost;
    while (x != 0 && heap->nodes[x].distance < heap->nodes[(x - 1) / 2].distance) {
        heap->pozicia[heap->nodes[x].vertex] = (x - 1) / 2;
        heap->pozicia[heap->nodes[(x - 1) / 2].vertex] = x;
        swap_heap_nodes(&heap->nodes[x], &heap->nodes[(x - 1) / 2]);
        x = (x - 1) / 2;
    }
}

int is_in_min_heap(MINHEAP *heap, int index_vrcholu) {
    return heap->pozicia[index_vrcholu] < heap->velkost ? 1 : 0;
}

int delete_edge(GRAPH* hl_graf, int v1, int v2) {
    int zhoda = 0;
    int uvolnenie = 0;
    
    EDGE **current = &(hl_graf->vertices[v1].head);
    while (*current != NULL) {
        EDGE *entry = *current;
        if (entry->vrchol2 == v2) {
            *current = entry->next;
            if(!uvolnenie){
                free(entry); 
                uvolnenie = 1;
            }
            zhoda = 1;
            break; 
        }
        current = &((*current)->next);
    }
    current = &(hl_graf->vertices[v2].head);
    while (*current != NULL) {
        EDGE *entry = *current;
        if (entry->vrchol2 == v1) {
            *current = entry->next;
            if(!uvolnenie){
                free(entry); 
                uvolnenie = 1;
            }
            zhoda = 1;
            break; 
        }
        current = &((*current)->next);
    }
    return zhoda;
}

int add_edge_to_graph(GRAPH* hl_graf, int zdroj, int ciel, int weight) {
    EDGE* new_edge = (EDGE*) malloc(sizeof(EDGE));
    if (!new_edge) {
        return 0; 
    }
    new_edge->vrchol1 = zdroj;
    new_edge->vrchol2 = ciel;
    new_edge->vaha = weight;
    new_edge->next = hl_graf->vertices[zdroj].head;
    hl_graf->vertices[zdroj].head = new_edge;
    return 1;
}

int insert_edge(GRAPH* hl_graf, int v1, int v2, int vaha) {
    if (v1 < 0 || v2 < 0 || v1 >= hl_graf->velkost_grafu || v2 >= hl_graf->velkost_grafu) {       
        return 1; 
    }
    if (v1 == v2) {
        return 1;
    }
    if (hrana_exist(hl_graf, v1, v2)) {
        return 1;
    }
    if (!add_edge_to_graph(hl_graf, v1, v2, vaha) || !add_edge_to_graph(hl_graf, v2, v1, vaha)) {
        delete_edge(hl_graf, v1, v2); 
        return 1;
    }
    return 0;
}

void print_path(int parent[], int vrchol_cesty) {
    if (parent[vrchol_cesty] == -1) {
        printf("%d", vrchol_cesty);
        return;
    }
    print_path(parent, parent[vrchol_cesty]);
    printf(", %d", vrchol_cesty);
}

void print_results(int *first_line_printed, const char *message) {
    if (*first_line_printed) {
        printf("\n");
    } else {
        *first_line_printed = 1;
    }
    printf("%s", message);
}

int print_path_to_string(int parent[], int vrchol_cesty, char *output) {
    if (parent[vrchol_cesty] == -1) {
        return sprintf(output, "%d", vrchol_cesty);
    }
    int len = print_path_to_string(parent, parent[vrchol_cesty], output);
    return len + sprintf(output + len, ", %d", vrchol_cesty);
}

void search(GRAPH* hl_graf, int zdroj, int ciel, int *first_line_printed) {
    if (zdroj < 0 || ciel < 0 || zdroj >= hl_graf->velkost_grafu || ciel >= hl_graf->velkost_grafu) {
        print_results(first_line_printed, "search failed");
        return;
    }

    MINHEAP *min_heap = create_min_heap(hl_graf->velkost_grafu);
    if (!min_heap) {
        return;
    }
    int distances[hl_graf->velkost_grafu];
    int parent[hl_graf->velkost_grafu];

    for (int i = 0; i < hl_graf->velkost_grafu; i++) {
        parent[i] = -1;
        distances[i] = INT_MAX;
        min_heap->nodes[i] = (HEAPNODE){i, INT_MAX};
        min_heap->pozicia[i] = i;
    }

    distances[zdroj] = 0;
    decrease_key(min_heap, zdroj, distances[zdroj]);
    min_heap->velkost = hl_graf->velkost_grafu;

    while (min_heap->velkost > 0) {
        HEAPNODE min_heap_node = extract_min(min_heap);
        int current_vertex = min_heap_node.vertex;
        if (current_vertex == ciel) break;

        EDGE *curr_edge = hl_graf->vertices[current_vertex].head;
        while (curr_edge != NULL) {
            int adjacent_ver = curr_edge->vrchol2;
            if (is_in_min_heap(min_heap, adjacent_ver) && distances[current_vertex] != INT_MAX) {
                long long new_dist = (long long)distances[current_vertex] + curr_edge->vaha;
                if (new_dist < distances[adjacent_ver] && new_dist < INT_MAX) {
                    distances[adjacent_ver] = new_dist;
                    parent[adjacent_ver] = current_vertex;
                    decrease_key(min_heap, adjacent_ver, distances[adjacent_ver]);
                }
            }
            curr_edge = curr_edge->next;
        }
    }

    if (distances[ciel] == INT_MAX) {
        print_results(first_line_printed, "search failed");
    } else {
        char output[1024];
        int length = snprintf(output, sizeof(output), "%d: [", distances[ciel]);
        if (parent[ciel] != -1) {
            length += print_path_to_string(parent, ciel, output + length);
        }
        snprintf(output + length, sizeof(output) - length, "]");
        print_results(first_line_printed, output);
    }

    free(min_heap->nodes);
    free(min_heap->pozicia);
    free(min_heap);
}

int update_edge(GRAPH* hl_graf, int v1, int v2, int zmena_vahy) {
    int updated = 0;  
    for (EDGE* aktualna_hrana = hl_graf->vertices[v1].head; aktualna_hrana != NULL; aktualna_hrana = aktualna_hrana->next) {
        if (aktualna_hrana->vrchol2 == v2) {
            if (aktualna_hrana->vaha + zmena_vahy < 0) { 
                return -1; 
            }
            aktualna_hrana->vaha += zmena_vahy;
            updated = 1; 
            break; 
        }
    }

    for (EDGE* aktualna_hrana = hl_graf->vertices[v2].head; aktualna_hrana != NULL; aktualna_hrana = aktualna_hrana->next) {
        if (aktualna_hrana->vrchol2 == v1) {
            if (aktualna_hrana->vaha + zmena_vahy < 0) { 
                return -1;
            }
            aktualna_hrana->vaha += zmena_vahy;
            updated = 1;
            break;
        }
    }
    return updated ? 0 : -1;  
}

void free_graph(GRAPH* hl_graf) {
    for (int i = 0; i < hl_graf->velkost_grafu; i++) {
        EDGE* current = hl_graf->vertices[i].head;
        while (current != NULL) {
            EDGE* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(hl_graf->vertices);
    free(hl_graf);
}