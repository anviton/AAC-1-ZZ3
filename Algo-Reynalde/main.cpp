#include "graph.h"
#include "file_reader.h"

#define FILENAME "graphe.txt"

int main() {
    Graph g = read_graph_from_file(FILENAME);
    g.print();

    vector<int> oddVertices = g.find_odd_degree_vertices();

    if (oddVertices.empty()) {
        cout << "The graph is already Eulerian.\n";
    } else {
        vector<vector<int>> dist = g.floyd_warshall();
        vector<pair<int, int>> matching = g.min_weight_perfect_matching(oddVertices, dist);
        g.add_matching_edges(matching, dist);
        cout << "Updated graph" << endl;
        g.print();
    }

    vector<int> eulerian_cycle = g.find_eulerian_cycle();
    cout << "The Eulerian cycle is: ";
    for (int v : eulerian_cycle) {
        cout << v << " ";
    }
    cout << endl;

    g.check_solution_is_optimal();
    g.total_cost(eulerian_cycle);
    return 0;
}
