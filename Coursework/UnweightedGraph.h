#pragma once
#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include "SinglyItems.h"
#include "QueueSingly.h"
#include "StackSinglyRef.h"
#include "ListSinglyRef.h"

using namespace std;

struct UnweightedGraphNode : public enable_shared_from_this<UnweightedGraphNode>
{
	unsigned value;
	ListSinglyRef<UnweightedGraphNode> edges;

	UnweightedGraphNode(int value)
	{
		this->value = value;

		cout << "Node Created" << endl;
	}

	~UnweightedGraphNode()
	{
		cout << "Node Deleted" << endl;
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
	QueueSingly<UnweightedGraphNode> nodes;

public:
	UnweightedGraph();
	~UnweightedGraph();

	shared_ptr<UnweightedGraphNode> addNode(int value);
	bool contains(int value);
	bool isPath(shared_ptr<UnweightedGraphNode> fromNode, shared_ptr<UnweightedGraphNode> toNode);

	void print();
};

