#include "pch.h"
#include "UnweightedGraphEdge.h"
#include "UnweightedGraphNode.h"


UnweightedGraphEdge::UnweightedGraphEdge(shared_ptr<UnweightedGraphNode> nodeA, shared_ptr<UnweightedGraphNode> nodeB, size_t weight)
{
	this->nodeA = nodeA;
	this->nodeB = nodeB;
	this->weight = weight;
}

shared_ptr<UnweightedGraphNode> UnweightedGraphEdge::getToNode(shared_ptr<UnweightedGraphNode> fromNode)
{
	shared_ptr<UnweightedGraphNode> nA = nodeA.lock();
	shared_ptr<UnweightedGraphNode> nB = nodeB.lock();

	return nA == fromNode ? nB : nA;
}
