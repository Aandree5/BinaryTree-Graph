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

using namespace std;
using namespace ConsoleHelpers;

struct UnweightedGraphNode : public enable_shared_from_this<UnweightedGraphNode>
{
	unsigned value;
	ListSinglyRef<UnweightedGraphNode> edges;
	shared_ptr<UnweightedGraphNode> next;

	UnweightedGraphNode(int value)
	{
		this->value = value;
	}

	int addEdge(shared_ptr<UnweightedGraphNode> toNode)
	{
		if (!edges.contains(toNode))
		{
			edges.push(toNode);

			toNode->edges.push(shared_from_this());
		}

		return edges.size();
	}
};

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
	bool addEdge(int nodeA, int nodeB);
	bool addEdge(shared_ptr<UnweightedGraphNode> nodeA, shared_ptr<UnweightedGraphNode> nodeB);
	bool isPath(int nodeA, int nodeB);
	bool isPath(shared_ptr<UnweightedGraphNode> nodeA, shared_ptr<UnweightedGraphNode> nodeB);
	shared_ptr<UnweightedGraphNode> findNode(int value);

	bool isConnected();

	void print();
};

