#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "ReadInput.h"

using namespace std;

int main() {
	vector<vector<uint32_t>> adjacencyList{ readAdjacencyListFromStdin() };
	for_each(adjacencyList.cbegin(), adjacencyList.cend(),
		[node = 0](const auto& conn) mutable {
		cout << node++ << " : ";
		for_each(conn.cbegin(), conn.cend(),
			[](auto nodeId) {
				cout << nodeId << " ";
			});
		cout << endl;
	});

	//by now cin's eofbit should have been raised
	return 0;
}