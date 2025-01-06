#ifndef GRAPH_H
#define GRAPH_H

#define MAX_NODES 1000
#define INF 999999

typedef struct {
    int num_nodes;
    int matrix[MAX_NODES][MAX_NODES];
} graph_t;

void init_graph(graph_t * g, int num_nodes);
void add_edges_to_graph(graph_t * g, int u, int v, int weight);
void print(const graph_t * g);

#endif // GRAPH_H