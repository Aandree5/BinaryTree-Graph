#include "pch.h"
#include "UnweightedGraphNode.h"
#include "UnweightedGraphEdge.h"

UnweightedGraphNode::UnweightedGraphNode(int value)
{
	this->value = value;
}

int UnweightedGraphNode::addEdge(shared_ptr<UnweightedGraphNode> toNode, size_t weight)
{
	shared_ptr<SinglyItem<UnweightedGraphEdge>> edge = edges.front();
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
		shared_ptr<UnweightedGraphEdge> newEdge = make_shared<UnweightedGraphEdge>(shared_from_this(), toNode, weight);

		edges.push(newEdge);

		toNode->edges.push(newEdge);
	}

	return edges.size();
}