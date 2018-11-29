#pragma once
#include <memory>
#include "ListSingly.h"
#include "SinglyItem.h"
#include <stdexcept> 
#include <string>

using namespace std;

class GraphEdge;

class GraphNode : public enable_shared_from_this<GraphNode>
{
public:
	size_t value;
	ListSingly<GraphEdge> edges;
	shared_ptr<GraphNode> next;

	///<summary>Creates a graph node with the given value.</summary>
	///<remark>BigO notation for worst case is O(1).</remark>
	///<param name="value">Value for the node.</param>
	GraphNode(size_t value);

	///<summary>Creates a graph edge between this node and the given one, with the given weight.</summary>
	///<remark>BigO notation for worst case is O(n).</remark>
	///<param name="toNode">Pointer to the node to connect to.</param>
	///<param name="weight">Positive value for the edge weight.</param>
	///<returns>The number of edges of this node.</returns>
	size_t addEdge(shared_ptr<GraphNode> toNode, size_t weight);


	// ### Operators ###
	operator string() const
	{
		return to_string(value);
	}

	friend ostream &operator<<(ostream &os, const GraphNode &node)
	{
		os << to_string(node.value);

		return os;
	}

	friend wostream &operator<<(wostream &wos, const GraphNode &node)
	{
		wos << to_string(node.value).c_str();

		return wos;
	}
};

