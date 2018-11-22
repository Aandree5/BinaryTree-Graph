#pragma once
#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "SinglyItems.h"
#include "QueueSinglyRef.h"
#include "StackSinglyRef.h"
#include "ListSinglyRef.h"
#include "ConsoleHelpers.h"
#include "UnweightedGraphNode.h"
#include "UnweightedGraphEdge.h"

using namespace std;
using namespace ConsoleHelpers;

struct VisitedNode
{
	weak_ptr<UnweightedGraphNode> reference;
	weak_ptr<UnweightedGraphNode> fromRef;

	VisitedNode(shared_ptr<UnweightedGraphNode> reference, shared_ptr<UnweightedGraphNode> fromRef)
	{
		this->reference = reference;
		this->fromRef = fromRef;
	}
};

class UnweightedGraph
{
	shared_ptr<UnweightedGraphNode> root;

public:
	UnweightedGraph();

	shared_ptr<UnweightedGraphNode> addNode(int value);

	bool addEdge(int nodeA, int nodeB, size_t weight);
	bool addEdge(shared_ptr<UnweightedGraphNode> nodeA, shared_ptr<UnweightedGraphNode> nodeB, size_t weight);

	bool isPath(int nodeA, int nodeB);
	bool isPath(shared_ptr<UnweightedGraphNode> nodeA, shared_ptr<UnweightedGraphNode> nodeB);

	shared_ptr<UnweightedGraphNode> findNode(int value);

	bool isConnected();

	void traversalBFS();

	void traversalDFS();

	void print();
};

