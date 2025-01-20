#include <stdio.h>

#include "graph.h"

#include <limits.h>

void init_graph(graph_t * g, int num_nodes)
{
    g->num_nodes = num_nodes;
    for (int i = 0; i < num_nodes; i++)
    {
        for (int j = 0; j < num_nodes; j++)
        {
            g->matrix[i][j] = (i == j) ? 0 : INF;
        }
    }
}

void add_edges_to_graph(graph_t * g, int u, int v, int weight)
{
    g->matrix[u][v] = weight;
    g->matrix[v][u] = weight;
}

void print_matrix(graph_t *g) {
    printf("Number of nodes: %d\n", g->num_nodes);

    // Print column headers
    printf("    ");
    for (int j = 0; j < g->num_nodes; j++) {
        printf("%4d \t", j);
    }
    printf("\n");

    // Print matrix values
    for (int i = 0; i < g->num_nodes; i++) {
        printf("%2d |", i);  // Row label
        for (int j = 0; j < g->num_nodes; j++) {
            if (g->matrix[i][j] == INT_MAX) {
                printf("  inf. \t");  // Print infinity symbol
            } else {
                printf("%4d \t", g->matrix[i][j]);  // Print weights with spacing
            }
        }
        printf("\n");
    }
}
