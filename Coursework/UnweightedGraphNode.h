#pragma once
#include <memory>
#include "ListSingly.h"
#include "SinglyItems.h"

using namespace std;

class UnweightedGraphEdge;

class UnweightedGraphNode : public enable_shared_from_this<UnweightedGraphNode>
{
public:
	size_t value;
	ListSingly<UnweightedGraphEdge> edges;
	shared_ptr<UnweightedGraphNode> next;

	UnweightedGraphNode(int value);

	int addEdge(shared_ptr<UnweightedGraphNode> toNode, size_t weight);
};

