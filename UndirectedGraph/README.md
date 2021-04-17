Implemeting the following representations of unweighted undirected graph of unsigned int nodes:
Adjacency matrix using an vector of bool vectors
Adjacency list using a vector of bool vectors
Compact list using an uint vector

The sample program requires a stream of EOF-terminated text input. All 3 implementations will be demonstrated, as well as the output
of all BFS and DFS starting on every nodes. Assumes that the input represents a connected graph.

Sample run:
UndirectedGraph.exe < SampleGraph.txt

The format of the input is
<Number Of Nodes>
<Paths>::= <Paths> | <Node><Connections><EOL>
<EOF>

EOL is the OS-specific EOL
EOF is the OS-specific EOF