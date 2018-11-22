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

bool UnweightedGraph::addEdge(int nodeA, int nodeB)
{
	return addEdge(findNode(nodeA), findNode(nodeB));
}

bool UnweightedGraph::addEdge(shared_ptr<UnweightedGraphNode> nodeA, shared_ptr<UnweightedGraphNode> nodeB)
{
	if (nodeA && nodeB)
	{
		nodeA->addEdge(nodeB);

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
	else if (!nA)
		cout << "Node: " << to_string(nodeA) << " wasn't found." << endl;
	else
		cout << "Node: " << to_string(nodeB) << " wasn't found." << endl;
}

bool UnweightedGraph::isPath(shared_ptr<UnweightedGraphNode> nodeA, shared_ptr<UnweightedGraphNode> nodeB)
{
	if (!nodeA || !nodeB)
		throw invalid_argument("'nodeA' and 'nodeB' can't be null.");

	ofstream file("Graph.txt");
	bool found = false;

	printC("#(" + to_string(nodeA->value) + ") <- ", C_CYAN);
	file << "#(" << to_string(nodeA->value) << ") <- ";

	QueueSinglyRef<UnweightedGraphNode> queue;
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

	queue.clear();

	if (found)
	{
		shared_ptr<UnweightedGraphNode> current = nodeB;
		StackSinglyRef<UnweightedGraphNode> path;

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
	StackSinglyRef<UnweightedGraphNode> stack;
	ListSinglyRef<UnweightedGraphNode> visited;

	stack.push(root);

	while (!stack.isEmpty())
	{
		shared_ptr<UnweightedGraphNode> current = stack.pop();

		if (!visited.contains(current))
		{
			visited.push(current);

			shared_ptr<SinglyRefItem<UnweightedGraphNode>> edge = current->edges.front();
			while (edge)
			{
				stack.push(edge->reference.lock());

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

void UnweightedGraph::traversalBFS()
{
	ofstream file("Graph.txt");

	printC("#(" + to_string(root->value) + ") -> ", C_CYAN);
	file << "#(" << to_string(root->value) << ") -> ";

	QueueSinglyRef<UnweightedGraphNode> queue;
	ListSinglyRef<UnweightedGraphNode> visited;

	queue.push_back(root);

	while (!queue.isEmpty())
	{
		shared_ptr<UnweightedGraphNode> current = queue.pop();

		if (!visited.contains(current))
		{
			visited.push(current);

			shared_ptr<SinglyRefItem<UnweightedGraphNode>> edge = current->edges.front();
			while (edge)
			{
				queue.push_back(edge->reference.lock());

				edge = edge->next;
			}

			if (current != root)
			{
				cout << to_string(current->value);
				file << to_string(current->value);

				if (!queue.isEmpty())
				{
					cout << " - ";
					file << " - ";
				}
			}
		}		
	}

	shared_ptr<UnweightedGraphNode> current = root;
	int nrNodes = 0;

	while (current = current->next)
		nrNodes++;

	size_t s = visited.size();

	if (nrNodes > s)
	{
		printC(to_string(nrNodes - s) + " missing", C_RED);
		file << to_string(nrNodes - s) << " missing";
	}

	cout << endl << endl;
	file << endl << endl;

	file.close();
}

void UnweightedGraph::traversalDFS()
{
	ofstream file("Graph.txt");

	printC("#(" + to_string(root->value) + ") -> ", C_CYAN);
	file << "#(" << to_string(root->value) << ") -> ";

	StackSinglyRef<UnweightedGraphNode> stack;
	ListSinglyRef<UnweightedGraphNode> visited;

	stack.push(root);

	while (!stack.isEmpty())
	{
		shared_ptr<UnweightedGraphNode> current = stack.pop();

		if (!visited.contains(current))
		{
			visited.push(current);

			shared_ptr<SinglyRefItem<UnweightedGraphNode>> edge = current->edges.front();
			while (edge)
			{
				stack.push(edge->reference.lock());

				edge = edge->next;
			}

			if (current != root)
			{
				cout << to_string(current->value);
				file << to_string(current->value);

				if (!stack.isEmpty())
				{
					cout << " - ";
					file << " - ";
				}
			}
		}
	}

	shared_ptr<UnweightedGraphNode> current = root;
	int nrNodes = 0;

	while (current = current->next)
		nrNodes++;

	size_t s = visited.size();

	if (nrNodes > s)
	{
		printC(to_string(nrNodes - s) + " missing", C_RED);
		file << to_string(nrNodes - s) << " missing";
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

		shared_ptr<SinglyRefItem<UnweightedGraphNode>> edge = current->edges.front();
		while (edge)
		{
			cout << edge->reference.lock()->value;

			if (edge = edge->next)
				cout << ", ";
		}

		cout << endl;

	} while (current = current->next);
}