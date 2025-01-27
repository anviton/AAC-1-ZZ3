#include "graph.h"
#include <algorithm>

Graph::Graph(int V) : V(V) {
    adj.resize(V);
}

void Graph::add_edge(int u, int v, int weight) {
    adj[u].emplace_back(v, weight);
    adj[v].emplace_back(u, weight);
}

vector<int> Graph::find_odd_degree_vertices() const {
    vector<int> odd_vertices;
    for (int i = 0; i < V; ++i) {
        if (adj[i].size() % 2 != 0) {
            odd_vertices.push_back(i);
        }
    }
    return odd_vertices;
}

vector<vector<int>> Graph::floyd_warshall() {
    vector<vector<int>> dist(V, vector<int>(V, INF));
    for (int i = 0; i < V; ++i) {
        dist[i][i] = 0;
        for (auto &edge : adj[i]) {
            int v = edge.first, w = edge.second;
            dist[i][v] = w;
        }
    }

    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    return dist;
}

vector<pair<int, int>> Graph::min_weight_perfect_matching(const vector<int>& oddVertices, const vector<vector<int>>& dist) {
    vector<pair<int, int>> matching;
    vector<bool> used(oddVertices.size(), false);

    for (size_t i = 0; i < oddVertices.size(); ++i) {
        if (used[i]) continue;
        int match = -1, bestDist = INF;

        for (size_t j = i + 1; j < oddVertices.size(); ++j) {
            if (!used[j] && dist[oddVertices[i]][oddVertices[j]] < bestDist) {
                bestDist = dist[oddVertices[i]][oddVertices[j]];
                match = j;
            }
        }

        if (match != -1) {
            used[i] = used[match] = true;
            matching.emplace_back(oddVertices[i], oddVertices[match]);
        }
    }
    return matching;
}

void Graph::add_matching_edges(const vector<pair<int, int>>& matching, const vector<vector<int>>& dist) {
    for (const auto &pair : matching) {
        add_edge(pair.first, pair.second, dist[pair.first][pair.second]);
    }
}

void Graph::eulerian_cycle(int v, vector<vector<pair<int, int>>>& temp, vector<int>& path) {
    for (auto it = temp[v].begin(); it != temp[v].end();) {
        int u = it->first;
        int weight = it->second;

        temp[v].erase(it);

        for (auto jt = temp[u].begin(); jt != temp[u].end(); ++jt) {
            if (jt->first == v && jt->second == weight) {
                temp[u].erase(jt);
                break;
            }
        }
        eulerian_cycle(u, temp, path);
        it = temp[v].begin();
    }
    path.push_back(v);
}


void Graph::print() const {
    for (int u = 0; u < V; ++u) {
        std::cout << "Vertex " << u << " -> ";
        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;
            std::cout << "(" << v << ", " << weight << ") ";
        }
        std::cout << std::endl;
    }
}

vector<int> Graph::find_eulerian_cycle() {
    vector<vector<pair<int, int>>> temp = adj;
    vector<int> path;

    int start_vertex = -1;
    for (int i = 0; i < V; ++i) {
        if (!temp[i].empty()) {
            start_vertex = i;
            break;
        }
    }

    if (start_vertex == -1) {
        std::cerr << "! Error: no eulerian cycle possible (empty graph)\n";
        return {};
    }

    eulerian_cycle(start_vertex, temp, path);
    reverse(path.begin(), path.end());
    return path;
}


int Graph::total_cost(const vector<int>& eulerian_cycle) {
    int total_cost = 0;
    for (size_t i = 0; i < eulerian_cycle.size() - 1; ++i) {
        int u = eulerian_cycle[i];
        int v = eulerian_cycle[i + 1];

        for (const auto& edge : adj[u]) {
            if (edge.first == v) {
                total_cost += edge.second;
                break;
            }
        }
    }
    return total_cost;
}

void Graph::check_solution_is_optimal() {
    vector<int> eulerian_cycle = find_eulerian_cycle();
    int total_weight = total_cost(eulerian_cycle);

    cout << "The total cost of the Eulerian cycle is: " << total_weight << endl;

    int original_weight = 0;
    for (int i = 0; i < V; ++i) {
        for (const auto& edge : adj[i]) {
            original_weight += edge.second;
        }
    }
    original_weight /= 2;

    cout << "- Original graph weight: " << original_weight << endl;
    cout << "- Additional weight added for even degree: " << (total_weight - original_weight) << endl;

    if (total_weight == original_weight) {
        cout << "* Solution is optimal." << endl;
    } else {
        cout << "! Solution might not be optimal. Check additional edges." << endl;
    }
}
