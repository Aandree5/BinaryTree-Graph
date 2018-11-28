#pragma once
#include <memory>
#include "ListSingly.h"
#include "SinglyItems.h"
#include <stdexcept> 
#include <string>

using namespace std;

class UnweightedGraphEdge;

class UnweightedGraphNode : public enable_shared_from_this<UnweightedGraphNode>
{
public:
	size_t value;
	ListSingly<UnweightedGraphEdge> edges;
	shared_ptr<UnweightedGraphNode> next;

	///<summary>Creates a graph node with the given value.</summary>
	///<remark>BigO notation for worst case is O(1).</remark>
	///<param name="value">Value for the node.</param>
	UnweightedGraphNode(size_t value);

	///<summary>Creates a graph edge between this node and the given one, with the given weight.</summary>
	///<remark>BigO notation for worst case is O(n).</remark>
	///<param name="toNode">Pointer to the node to connect to.</param>
	///<param name="weight">Positive value for the edge weight.</param>
	///<returns>The number of edges of this node.</returns>
	size_t addEdge(shared_ptr<UnweightedGraphNode> toNode, size_t weight);


	// ### Operators ###
	operator string() const
	{
		return to_string(value);
	}

	friend ostream &operator<<(ostream &os, const UnweightedGraphNode &node)
	{
		os << to_string(node.value);

		return os;
	}

	friend wostream &operator<<(wostream &wos, const UnweightedGraphNode &node)
	{
		wos << to_string(node.value).c_str();

		return wos;
	}
};

