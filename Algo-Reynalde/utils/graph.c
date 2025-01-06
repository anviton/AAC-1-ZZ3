#include <stdio.h>

#include "graph.h"

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

void add_edges(graph_t * g, int u, int v, int weight)
{
    g->matrix[u][v] = weight;
    g->matrix[v][u] = weight;
}

