#ifndef CHINESE_POSTMAN_H
#define CHINESE_POSTMAN_H

#include "../utils/graph.h"
#include <stdio.h>
#include "chinese_postman.h"

// Function to find vertices with odd degree
int *find_odd_degree_vertices(graph_t *g, int *count);
// Function to compute shortest distances using Floyd-Warshall algorithm
void floyd_warshall(graph_t *g, int** dist);
// Function to find minimum weight perfect matching (simplified example)
void find_minimum_weight_matching(int *odd_vertices, int count, int** dist);
// Function to add duplicate edges to create an Eulerian graph
void augment_graph(graph_t *g, int *odd_vertices, int count, int** dist);
// Function to find Eulerian circuit using Fleury's algorithm
int *fleury_algorithm(graph_t *g);
int *solve_chinese_postman(graph_t *g);

#endif //CHINESE_POSTMAN_H