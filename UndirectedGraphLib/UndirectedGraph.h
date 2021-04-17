#pragma once
/// <summary>
/// UndirectedGraph is the interface to the unweighted undirected graph implementation.
/// </summary>
#include <vector>
#include <string>

class UndirectedGraph {
public:
	UndirectedGraph() = default;
	explicit UndirectedGraph(const std::vector<std::vector<std::uint32_t>>& adjList);
	virtual ~UndirectedGraph() = default;
	/// <summary>
	/// Populates the implementing class with the 2-D vector of connections.
	/// The first element in the connection vector is always the node id.
	/// The rest of the elements are the node id connected to this node.
	/// A connection vector always have at least 2 elements: the node and one connection.
	/// Return true if the creation succeeded. False otherwise. Throws only std exceptions.
	/// </summary>
	/// <param name="connections">Adjacency list of the graph</param>
	/// <returns></returns>
	virtual bool create(const std::vector<std::vector<std::uint32_t>>& connections) = 0;
	/// <summary>
	/// Start a BFS traversal from every nodes. Return traversal result as a string of node ids separated by a space
	/// </summary>
	virtual std::vector<std::string> bfs() = 0;
	/// <summary>
	/// Performs a DFS traversal from every nodes
	/// </summary>
	/// <returns>String representation of the node traversal</returns>
	virtual std::vector<std::string> dfs() = 0;
private:
	/// <summary>
	/// Queries all node ids in the graph
	/// </summary>
	/// <returns>Returns a list of nodes from the implemetating class</returns>
	virtual std::vector<std::uint32_t> nodes() = 0;
	/// <summary>
	/// Queries the connected nodes of a given node id
	/// </summary>
	/// <param name="nodeId">Node id to query</param>
	/// <returns>Returns the node ids connected to a node</returns>
	virtual std::vector<std::uint32_t> connection(std::uint32_t nodeId) = 0;
};
