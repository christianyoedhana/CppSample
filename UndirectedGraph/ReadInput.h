#pragma once
#include <vector>

///Read input from stdin, line by line. Each output entries represent the node index. Basically reads in the stdin stream as an adjacency list
std::vector<std::vector<std::uint32_t>> readAdjacencyListFromStdin();