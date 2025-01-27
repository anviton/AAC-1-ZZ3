#include "file_reader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <tuple>

Graph read_graph_from_file(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: unable to open file " << filename << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    int maxNode = -1;
    vector<tuple<int, int, int>> edges;

    while (getline(file, line)) {
        stringstream ss(line);
        int u, v, w;
        char dash, colon;
        ss >> u >> dash >> v >> colon >> w;
        edges.emplace_back(u, v, w);
        maxNode = std::max(maxNode, std::max(u, v));
    }

    file.close();
    Graph g(maxNode + 1);

    for (const auto& [u, v, w] : edges) {
        g.add_edge(u, v, w);
    }

    return g;
}
