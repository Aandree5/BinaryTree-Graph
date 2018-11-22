#pragma once
#include <memory>

using namespace std;

class UnweightedGraphNode;

class UnweightedGraphEdge
{
public:
	weak_ptr<UnweightedGraphNode> nodeA;
	weak_ptr<UnweightedGraphNode> nodeB;
	size_t weight;

	UnweightedGraphEdge(shared_ptr<UnweightedGraphNode> nodeA, shared_ptr<UnweightedGraphNode> nodeB, size_t weight);

	shared_ptr<UnweightedGraphNode> getToNode(shared_ptr<UnweightedGraphNode> fromNode);
};

