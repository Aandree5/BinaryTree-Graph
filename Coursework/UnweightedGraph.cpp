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

shared_ptr<UnweightedGraphNode> UnweightedGraph::addNode(int value)
{
	shared_ptr<UnweightedGraphNode> node = nullptr;

	if (!contains(value))
	{
		node = make_shared<UnweightedGraphNode>(value);
		nodes.push_back(node);
	}

	return node;
}

bool UnweightedGraph::contains(int value)
{
	shared_ptr<SinglyItem<UnweightedGraphNode>> current = nodes.front();
	bool found = false;

	while (current)
	{
		if (current->item->value == value)
		{
			found = true;
			break;
		}

		current = current->next;
	}

	return found;
}

bool UnweightedGraph::isPath(shared_ptr<UnweightedGraphNode> fromNode, shared_ptr<UnweightedGraphNode> toNode)
{
	bool found = false;

	cout << "#(" << to_string(fromNode->value) << ") <- " ;

	QueueSingly<UnweightedGraphNode> queue;
	vector<VisitedNode> visited;

	queue.push_back(fromNode);

	while (!queue.isEmpty())
	{
		shared_ptr<UnweightedGraphNode> current = queue.pop();

		if (current == toNode)
		{
			found = true;

			break;
		}
		else
		{
			shared_ptr<SinglyRefItem<UnweightedGraphNode>> edge = current->edges.front();

			while (edge)
			{
				shared_ptr<UnweightedGraphNode> node = edge->reference.lock();

				bool exits = false;
				for (VisitedNode vNode : visited)
					if (vNode.reference.lock() == node)
					{
						exits = true;
						break;
					}

				if (!exits)
				{
					queue.push_back(node);
					visited.push_back(VisitedNode(node, current));
				}

				edge = edge->next;
			}
		}
	}

	queue.clear();

	if (found)
	{
		shared_ptr<UnweightedGraphNode> current = toNode;
		StackSinglyRef<UnweightedGraphNode> path;

		while (current != fromNode)
		{
			for (VisitedNode vNode : visited)
				if (vNode.reference.lock() == current)
				{
					if (current != toNode)
						path.push(current);

					current = vNode.fromRef.lock();

					break;
				}
		}

		while (!path.isEmpty())
		{
			shared_ptr<UnweightedGraphNode> node = path.pop();
			cout << to_string(node->value);

			if (!path.isEmpty())
				cout << " - ";
		}

		cout << " -> (" << toNode->value << ")" << endl;
	}
	else
		cout << "### No path ###" << endl;


	return found;
}

void UnweightedGraph::print()
{
	if (!nodes.isEmpty())
	{
		shared_ptr<SinglyItem<UnweightedGraphNode>> current = nodes.front();

		while (current)
		{
			cout << current->item->value << " -> ";

			shared_ptr<SinglyRefItem<UnweightedGraphNode>> edge = current->item->edges.front();
			while (edge)
			{
				cout << edge->reference.lock()->value << ", ";
				
				edge = edge->next;
			}

			cout << endl;

			current = current->next;
		}
	}
}