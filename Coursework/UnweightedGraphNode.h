#pragma once
#include <memory>
#include "ListSingly.h"
#include "SinglyItems.h"
#include <stdexcept> 

using namespace std;

class UnweightedGraphEdge;

class UnweightedGraphNode : public enable_shared_from_this<UnweightedGraphNode>
{
public:
	size_t value;
	ListSingly<UnweightedGraphEdge> edges;
	shared_ptr<UnweightedGraphNode> next;

	///<summary>Creates a graph node with the given value.</summary>
	///<param name="value">Value for the node.</param>
	UnweightedGraphNode(size_t value);

	///<summary>Creates a graph edge between this node and the given one, with the given weight.</summary>
	///<param name="toNode">Pointer to the node to connect to.</param>
	///<param name="weight">Positive value for the edge weight.</param>
	///<returns>The number of edges of this node.</returns>
	size_t addEdge(shared_ptr<UnweightedGraphNode> toNode, size_t weight);
};

