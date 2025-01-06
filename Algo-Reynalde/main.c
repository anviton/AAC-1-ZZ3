#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils/graph.h"
#include "src/chinese_postman.h"

void read_graph_from_file(graph_t *g, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int u, v, weight = 1; 
        if (strchr(line, ':')) 
        {
            // i->j:weight
            sscanf(line, "%d->%d:%d", &u, &v, &weight);
        } else {
            // i->j:1 (wieght is 1 by default)
            sscanf(line, "%d->%d", &u, &v);
        }
        add_edges_to_graph(g, u, v, weight);
    }

    fclose(file);
}


void export_to_dot(const graph_t *g, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Erreur : Impossible de créer le fichier %s\n", filename);
        return;
    }

    fprintf(file, "digraph G {\n");

    for (int i = 0; i < g->num_nodes; i++) {
        for (int j = 0; j < g->num_nodes; j++) {
            if (g->matrix[i][j] != 0 && g->matrix[i][j] != INF) {
                fprintf(file, "    %d -> %d [label=\"%d\"];\n", i, j, g->matrix[i][j]);
            }
        }
    }

    fprintf(file, "}\n");

    fclose(file);
    printf("Graphe exporté dans le fichier DOT : %s\n", filename);
}

int main() {
    const char *input_file = "examples/graph-1.txt";
    const char *output_file = "graph.dot";

    graph_t g;
    init_graph(&g, MAX_NODES);


    read_graph_from_file(&g, input_file);

    export_to_dot(&g, output_file);

    printf("Utilisez la commande suivante pour générer une image DOT :\n");
    printf("dot -Tpng %s -o examples/graph-1.png\n", output_file);

    return 0;
}
