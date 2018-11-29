#include "pch.h"
#include "GraphEdge.h"
#include "GraphNode.h"


GraphEdge::GraphEdge(shared_ptr<GraphNode> nodeA, shared_ptr<GraphNode> nodeB, size_t weight)
{
	if (!nodeA || !nodeB)
		throw invalid_argument("Input can't be nullptr");

	this->nodeA = nodeA;
	this->nodeB = nodeB;
	this->weight = weight;
}

shared_ptr<GraphNode> GraphEdge::getToNode(shared_ptr<GraphNode> fromNode)
{
	shared_ptr<GraphNode> nA = nodeA.lock();
	shared_ptr<GraphNode> nB = nodeB.lock();

	return nA == fromNode ? nB : nA;
}
