#include <stdlib.h>
#include <stdio.h>
#include "chinese_postman.h"

#include <limits.h>

// Fonction pour trouver les sommets de degré impair
int *find_odd_degree_vertices(graph_t *g, int *odd_count) {
    int *odd_vertices = malloc(g->num_nodes * sizeof(int));
    *odd_count = 0;

    for (int i = 0; i < g->num_nodes; i++) {
        int degree = 0;
        for (int j = 0; j < g->num_nodes; j++) {
            if (g->matrix[i][j] > 0 && g->matrix[i][j] != INT_MAX) {
                degree++;
            }
        }
        if (degree % 2 != 0) {
            odd_vertices[(*odd_count)++] = i;
        }
    }

    for (int i = 0; i < g->num_nodes; i++) {
        printf("odd_vertices[%d] = %d\n", i, odd_vertices[i]);
    }
    return odd_vertices;
}


// Trouver un couplage parfait minimal
void find_minimum_weight_matching(int *odd_vertices, int odd_count, int** dist) {
    int min_weight;
    int pair_u, pair_v;
    int used[MAX_NODES] = {0};

    while (odd_count > 0) {
        min_weight = INT_MAX;
        pair_u = -1;
        pair_v = -1;

        // Trouver la paire de sommets impairs avec la distance minimale
        for (int i = 0; i < odd_count; i++) {
            if (used[odd_vertices[i]]) continue;
            for (int j = i + 1; j < odd_count; j++) {
                if (used[odd_vertices[j]]) continue;

                if (dist[odd_vertices[i]][odd_vertices[j]] < min_weight) {
                    min_weight = dist[odd_vertices[i]][odd_vertices[j]];
                    printf("odd_vertices = %d, odd_vertices = %d, min_cost = %d \n", odd_vertices[i], odd_vertices[j], min_weight);
                    pair_u = odd_vertices[i];
                    pair_v = odd_vertices[j];
                }
            }
        }

        // Ajouter l'arête pour le couplage parfait minimal
        if (pair_u != -1 && pair_v != -1) {
            printf("Adding edge between %d and %d with weight %d\n", pair_u, pair_v, min_weight);
            used[pair_u] = 1;
            used[pair_v] = 1;
        }

        odd_count -= 2;
    }
}

// Augmenter le graphe en ajoutant les arêtes du couplage parfait
void augment_graph(graph_t *g, int *odd_vertices, int odd_count, int **dist) {
    for (int i = 0; i < odd_count; i += 2) {
        int u = odd_vertices[i];
        int v = odd_vertices[i + 1];

        if (g->matrix[u][v] == 0 || g->matrix[u][v] == INT_MAX) {
            // Ajouter une nouvelle arête entre u et v avec la distance minimale
            printf("Adding new edge between %d and %d with weight %d\n", u, v, dist[u][v]);
            g->matrix[u][v] = dist[u][v];
            g->matrix[v][u] = dist[u][v];
        } else {
            // Si l'arête existe déjà, ajouter une copie en parallèle (simuler un nouveau passage)
            printf("Duplicating edge between %d and %d with weight %d\n", u, v, dist[u][v]);
            g->matrix[u][v] += dist[u][v];  // Ajouter une deuxième arête fictive
            g->matrix[v][u] += dist[u][v];
        }
    }
}


// Implémentation de l'algorithme de Dijkstra pour trouver les plus courts chemins
void dijkstra(graph_t *g, int src, int dist[MAX_NODES]) {
    int visited[MAX_NODES] = {0};

    // Initialisation des distances
    for (int i = 0; i < g->num_nodes; i++) {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;

    for (int count = 0; count < g->num_nodes - 1; count++) {
        int min_dist = INT_MAX, u = -1;

        // Trouver le sommet non visité avec la distance minimale
        for (int v = 0; v < g->num_nodes; v++) {
            if (!visited[v] && dist[v] < min_dist) {
                min_dist = dist[v];
                u = v;
            }
        }

        // Marquer le sommet comme visité
        if (u == -1) break; // Tous les sommets accessibles ont été visités
        visited[u] = 1;

        // Mise à jour des distances des sommets adjacents
        for (int v = 0; v < g->num_nodes; v++) {
            if (!visited[v] && g->matrix[u][v] > 0 && g->matrix[u][v] != INT_MAX) {
                if (dist[u] + g->matrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + g->matrix[u][v];
                }
            }
        }
    }
}

// Trouver la matrice des distances minimales pour les sommets impairs
void compute_all_pairs_shortest_paths(graph_t *g, int **dist, int *odd_vertices, int odd_count) {
    for (int i = 0; i < odd_count; i++) {
        dijkstra(g, odd_vertices[i], dist[odd_vertices[i]]);
    }
}

// Algorithme de Fleury pour trouver un cycle eulérien
int *fleury_algorithm(graph_t *g) {
    static int tour[MAX_NODES];
    int tour_index = 0;
    int visited[MAX_NODES];
    for (int i = 0; i < g->num_nodes; i++) {
        visited[i] = 0;
    }
    int stack[MAX_NODES];
    int top = 0;

    stack[top++] = 0;

    while (top > 0) {
        // printf("stack[top-1] = %d\n", stack[top-1]);
        int u = stack[--top];
        for (int v = 0; v < g->num_nodes; v++){
            if (g->matrix[u][v] > 0 && g->matrix[u][v] != INT_MAX) {
                printf("Matrix[%d][%d] = %d\n", u, v, g->matrix[u][v]);
                visited[u] = 1;
                stack[top++] = v;
                g->matrix[u][v]-=g->matrix[u][v];
                g->matrix[v][u]-=g->matrix[v][u];
                u = v;
                break;
            }
        }
        tour[tour_index++] = u;
    }

    printf("Circuit : \n", tour);
    for (int i = 0; i < g->num_nodes; i++) {
        printf("circuit[%d] = %d\n", i, tour[i]);
    }
    return tour;
}

int *solve_chinese_postman(graph_t *g) {
    // Trouver l'ensemble T de sommets de G de degré impair
    int odd_count;
    int* circuit = malloc(g->num_nodes * sizeof(int));
    int *odd_vertices = find_odd_degree_vertices(g, &odd_count);

    if (odd_count == 0) {
        // Trouver un cycle eulérien dans G' en utilisant l'algorithme de Fleury
        printf("Attempt to find an eulerian cycle in G... \n");
        circuit = fleury_algorithm(g);
    } else {
        // Pour tous u,v appartenant à T, trouver la distance de u à v dans G
        int ** dist = malloc(sizeof(int*) * g->num_nodes);
        for (int i = 0; i < g->num_nodes; i++) {
            dist[i] = malloc(sizeof(int) * g->num_nodes);
        }
        // Calculer les distances entre les sommets impairs
        compute_all_pairs_shortest_paths(g, dist, odd_vertices, odd_count);

        // Vérification des distances calculées
        for (int i = 0; i < odd_count; i++) {
            for (int j = 0; j < odd_count; j++) {
                printf("dist[%d][%d] = %d\n", odd_vertices[i], odd_vertices[j], dist[odd_vertices[i]][odd_vertices[j]]);
            }
        }

        // Construire le graphe complet pondéré H avec l'ensemble de sommets de T
        // Trouver un couplage parfait M dans H de poids minimum
        find_minimum_weight_matching(odd_vertices, odd_count, dist);
        augment_graph(g, odd_vertices, odd_count, dist);

        // Trouver un cycle eulérien dans G' en utilisant l'algorithme de Fleury
        printf("Attempt to find an eulerian cycle in G'... \n");
        circuit = fleury_algorithm(g);
        free(odd_vertices);
    }

    return circuit;
}

