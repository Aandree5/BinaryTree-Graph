#pragma once
#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "SinglyItems.h"
#include "QueueSingly.h"
#include "StackSingly.h"
#include "ListSingly.h"
#include "ConsoleHelpers.h"
#include "UnweightedGraphNode.h"
#include "UnweightedGraphEdge.h"
#include <stdexcept> 

using namespace std;
using namespace ConsoleHelpers;

///<summary>Data structure used by Dijkstra algorithm.</summary>
struct DijkstraItem
{
	weak_ptr<UnweightedGraphNode> fromRef;
	size_t cost;
	bool visited;

	///<summary>Creates a new item, with cost 0 and visited set to false.</summary>
	DijkstraItem()
	{
		this->cost = UINT64_MAX;
		visited = false;
	}

	///<summary>Creates a new item, with the given properties.</summary>
	///<param name="fromRef">Pointer to the node from where this was found.</param>
	///<param name="cost">Cost to get from the starting node to this one, throught the 'fromRef'.</param>
	DijkstraItem(shared_ptr<UnweightedGraphNode> fromRef, size_t cost)
	{
		if (!fromRef)
			throw invalid_argument("'fomrRef' can't be null.");

		this->fromRef = fromRef;
		this->cost = cost;
		visited = false;
	}
};

class UnweightedGraph
{
	shared_ptr<UnweightedGraphNode> root;

public:
	UnweightedGraph();

	///<summary>Add a node with the given value to the graph.</summary>
	///<param name="value">Value of the node to be added.</param>
	///<returns>A pointer to the added node, nullptr if has failed or already exits.</returns>
	shared_ptr<UnweightedGraphNode> addNode(size_t value);

	///<summary>Add an edge between two nodes.</summary>
	///<param name="nodeA">Value of node A to add the edge.</param>
	///<param name="nodeB">Value of node B to add the edge.</param>
	///<param name="weight">Value of the weight of the edge.</param>
	///<returns>Number of edges of node A, 0 if an error occours.</returns>
	size_t addEdge(size_t nodeA, size_t nodeB, size_t weight);

	///<summary>Add an edge between two nodes.</summary>
	///<param name="nodeA">Pointer of node A to add the edge.</param>
	///<param name="nodeB">Pointer of node B to add the edge.</param>
	///<param name="weight">Value of the weight of the edge.</param>
	///<returns>Number of edges of node A, 0 if an error occours.</returns>
	size_t addEdge(shared_ptr<UnweightedGraphNode> nodeA, shared_ptr<UnweightedGraphNode> nodeB, size_t weight);

	///<summary>Counts the number of nodes in the graph.</summary>
	///<returns>The number of counted nodes.</returns>
	size_t countNodes();

	///<summary>Checks if there is a path between two nodes (Prints the shortest possible path and saves into a file, BFS).</summary>
	///<param name="nodeA">Value of node A.</param>
	///<param name="nodeB">Value of node B.</param>
	///<returns>True if there was a path found, false otherwise.</returns>
	bool isPath(size_t nodeA, size_t nodeB);

	///<summary>Checks if there is a path between two nodes (Prints the shortest possible path and saves into a file, BFS).</summary>
	///<param name="nodeA">Pointer of node A.</param>
	///<param name="nodeB">Pointer of node B.</param>
	///<returns>True if there was a path found, false otherwise.</returns>
	bool isPath(shared_ptr<UnweightedGraphNode> nodeA, shared_ptr<UnweightedGraphNode> nodeB);

	///<summary>Finds the node on the graph with the given value.</summary>
	///<param name="value">Value to look for.</param>
	///<returns>A pointer to the node if found, false otherwise.</returns>
	shared_ptr<UnweightedGraphNode> findNode(size_t value);

	///<summary>Checks if the graph is strongly connected (DFS).</summary>
	///<returns>True if is strongly connected, false otherwise.</returns>
	bool isConnected();

	///<summary>Finds the least wheighted path between two ndoes (Prints the path, Dijkstra).</summary>
	///<param name="nodeA">Value of node A.</param>
	///<param name="nodeB">Value of node B.</param>
	///<returns>True if there was a path found, false otherwise.</returns>
	bool dijkstraPath(size_t nodeA, size_t nodeB);

	///<summary>Finds the least wheighted path between two ndoes (Prints the path, Dijkstra).</summary>
	///<param name="nodeA">Pointer of node A.</param>
	///<param name="nodeB">Pointer of node B.</param>
	///<returns>True if there was a path found, false otherwise.</returns>
	bool dijkstraPath(shared_ptr<UnweightedGraphNode> nodeA, shared_ptr<UnweightedGraphNode> nodeB);

	///<summary>BFS (Breath Frist Search) traversal of the graph, prints the path to sceen and saves it on a file.</summary>
	void traversalBFS();

	///<summary>DFS (Depth Frist Search) traversal of the graph, prints the path to sceen and saves it on a file.</summary>
	void traversalDFS();

	///<summary>Prints graph to the screen, showing existing nodes, it's edges and their weights.</summary>
	void print();
};

