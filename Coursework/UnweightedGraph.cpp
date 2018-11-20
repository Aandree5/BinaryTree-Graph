#include "pch.h"
#include "UnweightedGraph.h"

UnweightedGraph::UnweightedGraph()
{
	cout << "Graph Created" << endl;
}


UnweightedGraph::~UnweightedGraph()
{
	cout << "Graph Deleted" << endl;
}

shared_ptr<UnweightedGraphNode> UnweightedGraph::add(int value)
{
	shared_ptr<UnweightedGraphNode> node = make_shared<UnweightedGraphNode>(value);

	nodes.push_back(node);

	return node;
}

shared_ptr<UnweightedGraphNode> UnweightedGraph::add(int value, shared_ptr<UnweightedGraphNode> connectedNodes...)
{
	shared_ptr<UnweightedGraphNode> node = make_shared<UnweightedGraphNode>(value, connectedNodes);

	nodes.push_back(node);

	return node;
}

void UnweightedGraph::print()
{
	if (!nodes.isEmpty())
	{
		shared_ptr<QueueItem<UnweightedGraphNode>> current = nodes.front();

		while (current)
		{
			cout << current->reference->value << " -> ";

			shared_ptr<StackItem<UnweightedGraphNode>> edge = current->reference->edges.top();
			while (edge)
			{
				cout << edge->reference->value << ", ";
				
				edge = edge->next;
			}

			cout << endl;

			current = current->next;
		}
	}
}