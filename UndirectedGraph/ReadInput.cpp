#include <string>
#include <iostream>
#include <sstream>
#include "ReadInput.h"

using namespace std;
//If the input correctly gives the max number of nodes, then the zero-based indexing scheme should work
vector<vector<uint32_t>> readAdjacencyListFromStdin() {
	string line;
	size_t numNodes;
	std::getline(cin, line);
	stringstream toParse(line);
	toParse >> numNodes;
	vector<vector<uint32_t>> graph(numNodes);
	while (std::getline(cin, line)) {
		stringstream toParse(line);
		uint32_t node =0;
		toParse >> node;
		uint32_t childNode = 0;
		while (toParse >> childNode) {
			//Sweet! I don't have to care about the empty space! stringstream operator>> tokenizes it out during numerical conversion
			graph.at(node).push_back(childNode);
		}
	}
	return graph;
}
