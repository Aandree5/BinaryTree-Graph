#include "pch.h"
#include "UnweightedGraph.h"

UnweightedGraph::UnweightedGraph()
{
	root = nullptr;
}

shared_ptr<UnweightedGraphNode> UnweightedGraph::addNode(size_t value)
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

size_t UnweightedGraph::addEdge(size_t nodeA, size_t nodeB, size_t weight)
{
	shared_ptr<UnweightedGraphNode> nA = findNode(nodeA);
	shared_ptr<UnweightedGraphNode> nB = findNode(nodeB);

	if (nA && nB)
		return addEdge(nA, nB, weight);
	else
	{
		printC("### Node: " + to_string(!nA ? nodeA : nodeB) + " wasn't found ###", C_RED);
		cout << endl << endl;
	}

	return 0;
}

size_t UnweightedGraph::addEdge(shared_ptr<UnweightedGraphNode> nodeA, shared_ptr<UnweightedGraphNode> nodeB, size_t weight)
{
	if (!nodeA || !nodeB || nodeA == nodeB)
		throw invalid_argument("'nodeA' and 'nodeB' can't be null nor the same.");

		return nodeA->addEdge(nodeB, weight);
}

size_t UnweightedGraph::countNodes()
{
	if (!root)
		return 0;

	shared_ptr<UnweightedGraphNode> current = root;
	size_t nrNodes = 0;

	do
	{
		nrNodes++;
	} while (current = current->next);

	return nrNodes;
}

bool UnweightedGraph::isPath(size_t nodeA, size_t nodeB)
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
	if (!nodeA || !nodeB || nodeA == nodeB)
		throw invalid_argument("'nodeA' and 'nodeB' can't be null nor the same.");

	ofstream file("Graph.txt");
	bool found = false;

	printC("#(" + to_string(nodeA->value) + ") <- ", C_CYAN);
	file << "#(" << to_string(nodeA->value) << ") <- ";

	QueueSingly<UnweightedGraphNode> queue;
	map<shared_ptr<UnweightedGraphNode>, shared_ptr<UnweightedGraphNode>> visited;

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

			if (!visited[node])
			{
				queue.push_back(node);
				visited[node] = current;
			}

			edge = edge->next;
		}
	}

	queue.clear();

	if (found)
	{
		shared_ptr<UnweightedGraphNode> current = nodeB;
		StackSingly<UnweightedGraphNode> path;

		while (visited[current] != nodeA)
		{
			path.push(visited[current]);
			current = visited[current];
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

shared_ptr<UnweightedGraphNode> UnweightedGraph::findNode(size_t value)
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

	bool connected = countNodes() == visited.size();

	if (connected)
		cout << "yes" << endl;

	else
		cout << "no" << endl;

	cout << endl;

	return connected;
}

bool UnweightedGraph::dijkstraPath(size_t nodeA, size_t nodeB)
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

bool UnweightedGraph::dijkstraPath(shared_ptr<UnweightedGraphNode> nodeA, shared_ptr<UnweightedGraphNode> nodeB)
{
	if (!nodeA || !nodeB || nodeA == nodeB)
		throw invalid_argument("'nodeA' and 'nodeB' can't be null nor the same.");

	map<shared_ptr<UnweightedGraphNode>, DijkstraItem> nodes;
	bool found = false;

	printC("$(" + to_string(nodeA->value) + ") <- ", C_CYAN);

	shared_ptr<UnweightedGraphNode> temp = root;
	do {
		nodes[temp] = DijkstraItem();
	} while (temp = temp->next);

	shared_ptr<UnweightedGraphNode> current = nodeA;
	nodes[current].cost = 0;

	if (current->edges.front())
	{
		while (current != nodeB)
		{
			nodes[current].visited = true;

			shared_ptr<SinglyItem<UnweightedGraphEdge>> edge = current->edges.front();
			while (edge)
			{
				shared_ptr<UnweightedGraphNode> toNode = edge->reference->getToNode(current);
				if (edge->reference->weight + nodes[current].cost < nodes[toNode].cost)
				{
					nodes[toNode].cost = edge->reference->weight + nodes[current].cost;
					nodes[toNode].fromRef = current;
				}

				edge = edge->next;
			}

			// Check when all the nodes have been visited and there's nowhere else to go
			bool allVisited = true;

			for (pair<shared_ptr<UnweightedGraphNode>, DijkstraItem> n : nodes)
			{
				if (n.second.cost < nodes[current].cost && !n.second.visited || nodes[current].visited)
					current = n.first;

				if (!n.second.visited)
					allVisited = false;
			}

			if (allVisited)
				break;

			if (current == nodeB && nodes[current].fromRef.lock())
				found = true;
		}
	}

	if (found)
	{
		StackSingly<UnweightedGraphNode> stack;
		shared_ptr<UnweightedGraphNode> nodeToFind = nodes[nodeB].fromRef.lock();

		while (nodeToFind != nodeA)
		{
			stack.push(nodeToFind);

			nodeToFind = nodes[nodeToFind].fromRef.lock();
		}

		while(!stack.isEmpty())
		{
			shared_ptr<UnweightedGraphNode> nodeToPrint = stack.pop();

			cout << to_string(nodeToPrint->value);
			
			if (!stack.isEmpty())
				cout << " - ";
		}


		printC(" -> (" + to_string(nodeB->value) + ")", C_CYAN);
		printC(" [" + to_string(nodes[nodeB].cost) + "]", C_BROWN);
	}
	else
	{
		printC("### No path ###", C_RED);
		printC(" -> (" + to_string(nodeB->value) + ")", C_CYAN);
	}

	cout << endl << endl;

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

	size_t nrNodes = countNodes();
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

	size_t nrNodes = countNodes();
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
		cout << to_string(current->value) << " -> ";

		shared_ptr<SinglyItem<UnweightedGraphEdge>> edge = current->edges.front();
		while (edge)
		{
			cout << to_string(edge->reference->getToNode(current)->value);
			printC(" '" + to_string(edge->reference->weight), C_DARKGREY);

			if (edge = edge->next)
				cout << ", ";
		}

		cout << endl;

	} while (current = current->next);
}