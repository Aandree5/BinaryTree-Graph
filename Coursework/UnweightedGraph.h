#pragma once
#include <memory>
#include <cstdarg>
#include <iostream>
#include "Queue.h"
#include "Stack.h"

using namespace std;

struct UnweightedGraphNode
{
	unsigned value;
	Stack<UnweightedGraphNode> edges;

	UnweightedGraphNode(int value)
	{
		this->value = value;

		cout << "Node Created" << endl;
	}

	UnweightedGraphNode(int value, shared_ptr<UnweightedGraphNode> connectedNodes...)
	{
		this->value = value;

		va_list args;
		va_start(args, connectedNodes);

		for (int i = 0; i < connectedNodes; i++)
		{
			val = va_arg(vl, double);
			printf(" [%.2f]", val);
		}

		while (connectedNodes)
		{
			edges.push(connectedNodes);

			connectedNodes = va_arg(connectedNodes);
		}

		va_end(args);


		cout << "Node Created" << endl;
	}

	~UnweightedGraphNode()
	{
		cout << "Node Deleted" << endl;
	}
};

class UnweightedGraph
{
	Queue<UnweightedGraphNode> nodes;

public:
	UnweightedGraph();
	~UnweightedGraph();

	shared_ptr<UnweightedGraphNode> add(int value);
	shared_ptr<UnweightedGraphNode> add(int value, shared_ptr<UnweightedGraphNode> connectedNodes...);

	void print();
};

