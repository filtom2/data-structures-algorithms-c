#include <stdio.h>
#include <stdlib.h>

#define INT_MAX 2147483647 // max positive integer (32b)

typedef struct edge {
    int vertex_1;
    int vertex_2;
    int weight;
    struct edge* next;
} edge;

typedef struct vertex {
    edge* head;
} vertex;

typedef struct graph {
    vertex* vertices;
    int num_vertices;
} graph;

graph* create_graph(int num_vertices);
int edge_exists(graph* graph_data, int v1, int v2);
int delete_edge(graph* graph_data, int v1, int v2);
int add_edge_to_graph(graph* graph_data, int src, int dest, int weight);
int insert_edge(graph* graph_data, int v1, int v2, int weight);
int calc_min_dist(int distances[], int spt_set[], int n);
void print_path(int parent[], int j);
void print_results(int *first_line_printed, const char *message);
int print_path_to_string(int parent[], int j, char *output);
void search(graph* graph_data, int src, int dest, int *first_line_printed);
int update_edge(graph* graph_data, int v1, int v2, int weight_change);
void free_graph(graph* graph_data);

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    graph* graph_data = create_graph(n);

    int v1, v2, weight;
    char paren1, comma1, comma2, paren2;
    for (int i = 0; i < m; i++) {
        scanf(" %c%d%c%d%c%d%c", &paren1, &v1, &comma1, &v2, &comma2, &weight, &paren2);
        if (insert_edge(graph_data, v1, v2, weight) == 1) {
            printf("insert %d %d failed\n", v1, v2);
        }
    }

    char command;
    int src, dest;
    int weight_change, first_line_printed = 0;

    while (scanf(" %c", &command) != EOF) {
        switch (command) {
        case 'i':
            scanf(" %d%c%d%c%d", &v1, &comma1, &v2, &comma2, &weight);
            if (insert_edge(graph_data, v1, v2, weight) == 1) {
                printf("\ninsert %d %d failed", v1, v2);
            }
            break;
        case 'd':
            scanf("%d %d", &v1, &v2);
            if (delete_edge(graph_data, v1, v2) == 0) {
                printf("\ndelete %d %d failed", v1, v2);
            }
            break;
        case 's':
            scanf("%d %d", &src, &dest);
            search(graph_data, src, dest, &first_line_printed);
            break;
        case 'u':
            scanf("%d %d %d", &v1, &v2, &weight_change);
            if (update_edge(graph_data, v1, v2, weight_change) != 0) {
                printf("\nupdate %d %d failed", v1, v2);
            }
            break;
        }
    }

    free_graph(graph_data);
    return 0;
}

graph* create_graph(int num_vertices) {
    graph* graph_data = (graph*) malloc(sizeof(graph));
    graph_data->num_vertices = num_vertices;
    graph_data->vertices = (vertex*) malloc(num_vertices * sizeof(vertex));

    for (int i = 0; i < num_vertices; i++) {
        graph_data->vertices[i].head = NULL;
    }
    return graph_data;
}

int edge_exists(graph* graph_data, int v1, int v2) {
    edge* current1 = graph_data->vertices[v1].head;
    while (current1 != NULL) {
        if (current1->vertex_2 == v2) {
            return 1;
        }
        current1 = current1->next;
    }

    edge* current2 = graph_data->vertices[v2].head;
    while (current2 != NULL) {
        if (current2->vertex_2 == v1) {
            return 1;
        }
        current2 = current2->next;
    }
    return 0;
}

int delete_edge(graph* graph_data, int v1, int v2) {
    int match = 0;
    int freed = 0;

    edge **current = &(graph_data->vertices[v1].head);
    while (*current != NULL) {
        edge *entry = *current;
        if (entry->vertex_2 == v2) {
            *current = entry->next;
            if (!freed) {
                free(entry);
                freed = 1;
            }
            match = 1;
            break;
        }
        current = &((*current)->next);
    }

    current = &(graph_data->vertices[v2].head);
    while (*current != NULL) {
        edge *entry = *current;
        if (entry->vertex_2 == v1) {
            *current = entry->next;
            if (!freed) {
                free(entry);
                freed = 1;
            }
            match = 1;
            break;
        }
        current = &((*current)->next);
    }
    return match;
}

int add_edge_to_graph(graph* graph_data, int src, int dest, int weight) {
    edge* new_edge = (edge*) malloc(sizeof(edge));
    if (!new_edge) {
        return 0;
    }
    new_edge->vertex_1 = src;
    new_edge->vertex_2 = dest;
    new_edge->weight = weight;
    new_edge->next = graph_data->vertices[src].head;
    graph_data->vertices[src].head = new_edge;
    return 1;
}

int insert_edge(graph* graph_data, int v1, int v2, int weight) {
    if (v1 < 0 || v2 < 0 || v1 >= graph_data->num_vertices || v2 >= graph_data->num_vertices) {
        return 1;
    }
    if (v1 == v2) {
        return 1;
    }
    if (edge_exists(graph_data, v1, v2)) {
        return 1;
    }
    if (!add_edge_to_graph(graph_data, v1, v2, weight) || !add_edge_to_graph(graph_data, v2, v1, weight)) {
        delete_edge(graph_data, v1, v2);
        return 1;
    }
    return 0;
}

int calc_min_dist(int distances[], int spt_set[], int n) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < n; v++)
        if (!spt_set[v] && distances[v] <= min)
            min = distances[v], min_index = v;
    return min_index;
}

void print_path(int parent[], int j) {
    if (parent[j] == -1) {
        printf("%d", j);
        return;
    }
    print_path(parent, parent[j]);
    printf(", %d", j);
}

void print_results(int *first_line_printed, const char *message) {
    if (*first_line_printed) {
        printf("\n");
    } else {
        *first_line_printed = 1;
    }

    printf("%s", message);
}

int print_path_to_string(int parent[], int j, char *output) {
    if (parent[j] == -1) {
        return sprintf(output, "%d", j);
    }
    int len = print_path_to_string(parent, parent[j], output);
    return len + sprintf(output + len, ", %d", j);
}

void search(graph* graph_data, int src, int dest, int *first_line_printed) {
    if (src < 0 || dest < 0 || src >= graph_data->num_vertices || dest >= graph_data->num_vertices) {
        print_results(first_line_printed, "operation failed");
        return;
    }

    int n = graph_data->num_vertices;
    int distances[n], parent[n], spt_set[n];

    for (int i = 0; i < n; i++) {
        parent[i] = -1;
        distances[i] = INT_MAX;
        spt_set[i] = 0;
    }

    distances[src] = 0;

    for (int count = 0; count < n; count++) {
        int u = calc_min_dist(distances, spt_set, n);
        if (u == -1 || distances[u] == INT_MAX)
            break;
        spt_set[u] = 1;

        for (edge* e = graph_data->vertices[u].head; e != NULL; e = e->next) {
            int v = e->vertex_2;
            if (!spt_set[v] && (long long)distances[u] + e->weight < distances[v]) {
                parent[v] = u;
                distances[v] = distances[u] + e->weight;
            }
        }
    }

    if (distances[dest] == INT_MAX) {
        print_results(first_line_printed, "operation failed");
    } else {
        char output[1024] = {0};
        int pos = sprintf(output, "%d: [", distances[dest]);
        if (parent[dest] != -1) {
            pos += print_path_to_string(parent, dest, output + pos);
        }
        sprintf(output + pos, "]");
        print_results(first_line_printed, output);
    }
}

int update_edge(graph* graph_data, int v1, int v2, int weight_change) {
    int updated = 0;
    for (edge* e = graph_data->vertices[v1].head; e != NULL; e = e->next) {
        if (e->vertex_2 == v2) {
            if (e->weight + weight_change < 0) {
                return -1;
            }
            e->weight += weight_change;
            updated = 1;
            break;
        }
    }

    for (edge* e = graph_data->vertices[v2].head; e != NULL; e = e->next) {
        if (e->vertex_2 == v1) {
            if (e->weight + weight_change < 0) {
                return -1;
            }
            e->weight += weight_change;
            updated = 1;
            break;
        }
    }
    return updated ? 0 : -1;
}

void free_graph(graph* graph_data) {
    for (int i = 0; i < graph_data->num_vertices; i++) {
        edge* current = graph_data->vertices[i].head;
        while (current != NULL) {
            edge* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph_data->vertices);
    free(graph_data);
}
