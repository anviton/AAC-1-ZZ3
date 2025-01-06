#include <stdio.h>
#include <stdbool.h>
#include "chinese_postman.h"
#include "graph.h"

void find_eulerian_circuit(graph_t * g)
{
    int stack[MAX_NODES];
    int circuit[MAX_NODES];
    int ssize = 0;
    int csize = 0;

    graph_t * temp = *g;

    int curr = -1;

    // Trouver un sommet de départ ayant des arêtes
    for (int i = 0; i < temp.num_nodes; i++)
    {
        for (int j = 0; j < temp.num_nodes; j++)
        {
            if (temp.matrix[i][j] > 0)
            {
                curr = i;
                break;
            }

        }
        if (curr != -1) break;
    } 

    if (curr == -1) {
        printf("Graph has not edges. \n");
        return;
    }   

    stack[ssize++] = curr;
    while (ssize > 0)
    {
        curr = stack[ssize - 1];

        // Chercher une arête non visitée
        int next = -1;
        for (int i = 0; i < temp.num_nodes; i++)
        {
            if (temp.matrix[current][i] > 0)
            {
                next = i;
                break;
            }
        }

        if (next == -1)
        {
            // Pas d'arêtes disponibles, ajouter au circuit
            circuit[csize++] = curr;
            ssize--;
        } else {
            // Ajouter au chemin temporaire et "enlever" l'arête
            stack[ssize] = next;
            temp.matrix[curr][next]--;
            temp.matrix[next][curr]--;
        }
    }
}


void solve_chinese_postman(const graph_t * g)
{
    int odd_nodes[MAX_NODES];
    int odd_count = 0;

    for (int i = 0; i < g->num_nodes; i++)
    {
        int deg = 0;
        for (int j = 0; j < g->num_nodes; j++)
        {
            if (g->matrix[i][j] != INF && g->matrix[i][j] != 0)
            {
                deg++;
            }

            if (deg % 2 != 0)
            {
                odd_nodes[odd_count++] = i;
            }
        }

        if (odd_count == 0)
        {
            find_eulerian_circuit(g);
        }
    }
}