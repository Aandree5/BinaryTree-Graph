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

using namespace std;
using namespace ConsoleHelpers;

struct DijkstraItem
{
	weak_ptr<UnweightedGraphNode> fromRef;
	size_t cost;
	bool visited;

	DijkstraItem()
	{
		this->cost = 0;
		visited = false;
	}

	DijkstraItem(shared_ptr<UnweightedGraphNode> fromRef, size_t cost)
	{
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

	shared_ptr<UnweightedGraphNode> addNode(size_t value);

	bool addEdge(size_t nodeA, size_t nodeB, size_t weight);
	bool addEdge(shared_ptr<UnweightedGraphNode> nodeA, shared_ptr<UnweightedGraphNode> nodeB, size_t weight);

	size_t countNodes();

	bool isPath(size_t nodeA, size_t nodeB);
	bool isPath(shared_ptr<UnweightedGraphNode> nodeA, shared_ptr<UnweightedGraphNode> nodeB);

	shared_ptr<UnweightedGraphNode> findNode(size_t value);

	bool isConnected();

	bool dijkstraPath(size_t nodeA, size_t nodeB);
	bool dijkstraPath(shared_ptr<UnweightedGraphNode> nodeA, shared_ptr<UnweightedGraphNode> nodeB);

	void traversalBFS();
	void traversalDFS();

	void print();
};

