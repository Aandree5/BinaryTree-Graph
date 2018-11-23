#include "pch.h"
#include "UnweightedGraph.h"

UnweightedGraph::UnweightedGraph()
{
	root = nullptr;
}

shared_ptr<UnweightedGraphNode> UnweightedGraph::addNode(int value)
{
	if (!root)
	{
		root = make_shared<UnweightedGraphNode>(value);

		return root;
	}
	else
	{
		shared_ptr<UnweightedGraphNode> current = root;

		if (current->value == value)
			return nullptr;

		while (current->next)
		{
			if (current->next->value == value)
				return nullptr;

			current = current->next;
		}

		current->next = make_shared<UnweightedGraphNode>(value);

		return current->next;
	}
}

bool UnweightedGraph::addEdge(int nodeA, int nodeB, size_t weight)
{
	return addEdge(findNode(nodeA), findNode(nodeB), weight);
}

bool UnweightedGraph::addEdge(shared_ptr<UnweightedGraphNode> nodeA, shared_ptr<UnweightedGraphNode> nodeB, size_t weight)
{
	if (nodeA && nodeB)
	{
		nodeA->addEdge(nodeB, weight);

		return true;
	}

	return false;
}

bool UnweightedGraph::isPath(int nodeA, int nodeB)
{
	shared_ptr<UnweightedGraphNode> nA = findNode(nodeA);
	shared_ptr<UnweightedGraphNode> nB = findNode(nodeB);

	if (nA && nB)
		return isPath(nA, nB);
	else
	{
		printC("### Node: " + to_string(!nA ? nodeA : nodeB) + " wasn't found ###", C_RED);
		cout << endl << endl;
	}

	return false;
}

bool UnweightedGraph::isPath(shared_ptr<UnweightedGraphNode> nodeA, shared_ptr<UnweightedGraphNode> nodeB)
{
	if (!nodeA || !nodeB)
		throw invalid_argument("'nodeA' and 'nodeB' can't be null.");

	ofstream file("Graph.txt");
	bool found = false;

	printC("#(" + to_string(nodeA->value) + ") <- ", C_CYAN);
	file << "#(" << to_string(nodeA->value) << ") <- ";

	QueueSingly<UnweightedGraphNode> queue;
	vector<VisitedNode> visited;

	queue.push_back(nodeA);

	while (!queue.isEmpty())
	{
		shared_ptr<UnweightedGraphNode> current = queue.pop();

		if (current == nodeB)
		{
			found = true;

			break;
		}

		shared_ptr<SinglyItem<UnweightedGraphEdge>> edge = current->edges.front();
		while (edge)
		{
			shared_ptr<UnweightedGraphNode> node = edge->reference->getToNode(current);

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

	queue.clear();

	if (found)
	{
		shared_ptr<UnweightedGraphNode> current = nodeB;
		StackSingly<UnweightedGraphNode> path;

		while (current != nodeA)
		{
			for (VisitedNode vNode : visited)
				if (vNode.reference.lock() == current)
				{
					if (current != nodeB)
						path.push(current);

					current = vNode.fromRef.lock();

					break;
				}
		}

		while (!path.isEmpty())
		{
			shared_ptr<UnweightedGraphNode> node = path.pop();
			cout << to_string(node->value);
			file << to_string(node->value);

			if (!path.isEmpty())
			{
				cout << " - ";
				file << " - ";
			}
		}
	}
	else
	{
		printC("### No path ###", C_RED);
		file << "### No path ###" ;
	}

	printC(" -> (" + to_string(nodeB->value) + ")", C_CYAN);
	cout << endl << endl;
	file << " -> (" << nodeB->value << ")" << endl << endl;

	file.close();

	return found;
}

shared_ptr<UnweightedGraphNode> UnweightedGraph::findNode(int value)
{
	if (root)
	{
		shared_ptr<UnweightedGraphNode> current = root;

		do {
			if (current->value == value)
				return current;

		} while (current = current->next);
	}

	return nullptr;
}

bool UnweightedGraph::isConnected()
{
	StackSingly<UnweightedGraphNode> stack;
	ListSingly<UnweightedGraphNode> visited;

	stack.push(root);

	while (!stack.isEmpty())
	{
		shared_ptr<UnweightedGraphNode> current = stack.pop();

		if (!visited.contains(current))
		{
			visited.push(current);

			shared_ptr<SinglyItem<UnweightedGraphEdge>> edge = current->edges.front();
			while (edge)
			{
				stack.push(edge->reference->getToNode(current));

				edge = edge->next;
			}
		}
	}

	shared_ptr<UnweightedGraphNode> current = root;
	int nrNodes = 0;

	while (current = current->next)
		nrNodes++;

	bool connected = nrNodes == visited.size();

	if (connected)
		cout << "yes" << endl;

	else
		cout << "no" << endl;

	cout << endl;

	return connected;
}

bool UnweightedGraph::dijkstraPath(int nodeA, int nodeB)
{
	shared_ptr<UnweightedGraphNode> nA = findNode(nodeA);
	shared_ptr<UnweightedGraphNode> nB = findNode(nodeB);

	if (nA && nB)
		return dijkstraPath(nA, nB);
	else
	{
		printC("### Node: " + to_string(!nA ? nodeA : nodeB) + " wasn't found ###", C_RED);
		cout << endl << endl;
	}

	return false;
}

struct DijkstraItem
{
	weak_ptr<UnweightedGraphNode> reference;
	weak_ptr<UnweightedGraphNode> fromRef;
	size_t cost;

	DijkstraItem(shared_ptr<UnweightedGraphNode> reference, shared_ptr<UnweightedGraphNode> fromRef, size_t cost)
	{
		this->reference = reference;
		this->fromRef = fromRef;
		this->cost = cost;
	}
};

bool UnweightedGraph::dijkstraPath(shared_ptr<UnweightedGraphNode> nodeA, shared_ptr<UnweightedGraphNode> nodeB)
{
	ListSingly<DijkstraItem> nodes;
	bool found = false;

	shared_ptr<UnweightedGraphNode> temp = root;
	do {
		nodes.push(make_shared<DijkstraItem>(temp, nullptr, UINT64_MAX));
	} while (temp = temp->next);

	shared_ptr<SinglyItem<DijkstraItem>> current = nodes.front();
	shared_ptr<SinglyItem<DijkstraItem>> c = current->next;
	do
	{
		if (c->reference->reference.lock() == nodeA)
		{
			current = c;
			break;
		}
	} while (c = c->next);

	while (current->reference->reference.lock() != nodeB)
	{
		shared_ptr<SinglyItem<UnweightedGraphEdge>> edge = current->reference->reference.lock()->edges.front();
		do
		{
			shared_ptr<SinglyItem<DijkstraItem>> n = nodes.front();
			do
			{
				if (n->reference->reference.lock() == edge->reference->getToNode(current->reference->reference.lock()))
				{
					if (edge->reference->weight + current->reference->cost < n->reference->cost)
						n->reference->cost = edge->reference->weight + current->reference->cost;

					break;
				}
			} while (n = n->next);
		} while (edge = edge->next);

		current = nodes.front();
		shared_ptr<SinglyItem<DijkstraItem>> n = current->next;
		do
		{
			if (n->reference->cost < current->reference->cost)
				current = n;
		} while (n = n->next);

		if (current->reference->reference.lock() == nodeB)
			found = true;
	}

	if (found) 
	{
		cout << "found" << endl << endl;
	}

	return found;
}

void UnweightedGraph::traversalBFS()
{
	ofstream file("Graph.txt");
	bool isFirst = true;

	printC("#(" + to_string(root->value) + ") -> ", C_CYAN);
	file << "#(" << to_string(root->value) << ") -> ";

	QueueSingly<UnweightedGraphNode> queue;
	ListSingly<UnweightedGraphNode> visited;

	queue.push_back(root);

	while (!queue.isEmpty())
	{
		shared_ptr<UnweightedGraphNode> current = queue.pop();

		if (!visited.contains(current))
		{
			visited.push(current);

			shared_ptr<SinglyItem<UnweightedGraphEdge>> edge = current->edges.front();
			while (edge)
			{
				queue.push_back(edge->reference->getToNode(current));

				edge = edge->next;
			}

			if (current != root)
			{
				if (!isFirst)
				{
					cout << " - ";
					file << " - ";
				}
				isFirst = false;

				cout << to_string(current->value);
				file << to_string(current->value);
			}
		}		
	}

	shared_ptr<UnweightedGraphNode> current = root;
	int nrNodes = 0;

	while (current = current->next)
		nrNodes++;

	size_t vSize = visited.size();

	if (nrNodes > vSize)
	{
		cout << " ";
		printC(to_string(nrNodes - vSize) + " not connected", C_RED);
		file << " " << to_string(nrNodes - vSize) << " not connected";
	}

	cout << endl << endl;
	file << endl << endl;

	file.close();
}

void UnweightedGraph::traversalDFS()
{
	ofstream file("Graph.txt");
	bool isFirst = true;

	printC("#(" + to_string(root->value) + ") -> ", C_CYAN);
	file << "#(" << to_string(root->value) << ") -> ";

	StackSingly<UnweightedGraphNode> stack;
	ListSingly<UnweightedGraphNode> visited;

	stack.push(root);

	while (!stack.isEmpty())
	{
		shared_ptr<UnweightedGraphNode> current = stack.pop();

		if (!visited.contains(current))
		{
			visited.push(current);

			shared_ptr<SinglyItem<UnweightedGraphEdge>> edge = current->edges.front();
			while (edge)
			{
				stack.push(edge->reference->getToNode(current));

				edge = edge->next;
			}

			if (current != root)
			{
				if (!isFirst)
				{
					cout << " - ";
					file << " - ";
				}
				isFirst = false;

				cout << to_string(current->value);
				file << to_string(current->value);
			}
		}
	}

	shared_ptr<UnweightedGraphNode> current = root;
	int nrNodes = 0;

	while (current = current->next)
		nrNodes++;

	size_t vSize = visited.size();

	if (nrNodes > vSize)
	{
		cout << " ";
		printC(to_string(nrNodes - vSize) + " not connected", C_RED);
		file << " " << to_string(nrNodes - vSize) << " not connected";
	}

	cout << endl << endl;
	file << endl << endl;

	file.close();
}

void UnweightedGraph::print()
{
	shared_ptr<UnweightedGraphNode> current = root;

	do {
		cout << current->value << " -> ";

		shared_ptr<SinglyItem<UnweightedGraphEdge>> edge = current->edges.front();
		while (edge)
		{
			cout << edge->reference->getToNode(current)->value << " '" << to_string(edge->reference->weight);

			if (edge = edge->next)
				cout << ", ";
		}

		cout << endl;

	} while (current = current->next);
}