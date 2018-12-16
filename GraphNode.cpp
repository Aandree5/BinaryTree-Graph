#include "pch.h"
#include "GraphNode.h"
#include "GraphEdge.h"

GraphNode::GraphNode(size_t value)
{
	this->value = value;
}

size_t GraphNode::addEdge(shared_ptr<GraphNode> toNode, size_t weight)
{
	if (!toNode)
		throw invalid_argument("'toNode' can't be null");

	shared_ptr<SinglyItem<GraphEdge>> edge = edges.front();
	bool found = false;

	while (edge)
	{
		if (edge->reference->nodeA.lock() == toNode || edge->reference->nodeB.lock() == toNode)
		{
			found = true;

			if (weight < edge->reference->weight)
				edge->reference->weight = weight;

			break;
		}

		edge = edge->next;
	}

	if (!found)
	{
		shared_ptr<GraphEdge> newEdge = make_shared<GraphEdge>(shared_from_this(), toNode, weight);

		edges.push(newEdge);

		toNode->edges.push(newEdge);
	}

	return edges.size();
}