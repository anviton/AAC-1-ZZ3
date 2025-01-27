#ifndef FILE_READER_H
#define FILE_READER_H

#include "graph.h"
#include <string>

/**
 * @brief Reads a graph from a given file.
 *
 * This function takes a filename as input and constructs a graph
 * by reading data from the file.
 *
 * @param filename The name of the file containing graph data
 * @return A graph object populated with data from the file
 */
Graph read_graph_from_file(const std::string& filename);

#endif  // FILE_READER_H
