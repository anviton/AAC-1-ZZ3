#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>
#include <limits>

using namespace std;

// Constant representing infinity
const int INF = numeric_limits<int>::max();

/**
 * @class Graph
 * @brief Represents a weighted undirected graph.
 */
class Graph {
public:
    int V;  ///< Number of vertices in the graph
    vector<vector<pair<int, int>>> adj;  ///< Adjacency list representation of the graph

    /**
     * @brief Constructs a graph with a given number of vertices.
     * @param V Number of vertices
     */
    Graph(int V);

    /**
     * @brief Adds an edge between two vertices with a specified weight.
     * @param u Source vertex
     * @param v Destination vertex
     * @param weight Weight of the edge
     */
    void add_edge(int u, int v, int weight);

    /**
     * @brief Finds vertices with an odd degree.
     * @return A vector containing the odd-degree vertices
     */
    vector<int> find_odd_degree_vertices() const;

    /**
     * @brief Computes all-pairs shortest paths using the Floyd-Warshall algorithm.
     * @return A matrix of shortest path distances between all pairs of vertices
     */
    vector<vector<int>> floyd_warshall();

    /**
     * @brief Finds a minimum weight perfect matching among the given odd-degree vertices.
     * @param odd_vertices Vector of odd-degree vertices
     * @param dist Distance matrix computed by floyd_warshall
     * @return A vector of paired vertices forming the minimum weight matching
     */
    static vector<pair<int, int>> min_weight_perfect_matching(const vector<int>& odd_vertices, const vector<vector<int>>& dist);

    /**
     * @brief Adds matching edges to the graph to make it Eulerian.
     * @param matching Pairs of vertices to be connected
     * @param dist Distance matrix computed by floyd_warshall
     */
    void add_matching_edges(const vector<pair<int, int>>& matching, const vector<vector<int>>& dist);

    /**
     * @brief Prints the adjacency list representation of the graph.
     */
    void print() const;

    /**
     * @brief Finds an Eulerian cycle in the graph.
     * @return A vector representing the Eulerian cycle
     */
    vector<int> find_eulerian_cycle();

    /**
     * @brief Computes the total cost of an Eulerian cycle.
     * @param eulerian_cycle A vector representing the Eulerian cycle
     * @return The total cost of the cycle
     */
    int total_cost(const vector<int>& eulerian_cycle);

    /**
     * @brief Checks if the found solution is optimal.
     */
    void check_solution_is_optimal();

private:
    /**
     * @brief Helper function to recursively find an Eulerian cycle.
     * @param v Current vertex
     * @param temp Temporary adjacency list to track remaining edges
     * @param path Stores the Eulerian path
     */
    void eulerian_cycle(int v, vector<vector<pair<int, int>>>& temp, vector<int>& path);
};

#endif  // GRAPH_H
