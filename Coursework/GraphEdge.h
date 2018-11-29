#pragma once
#include <memory>
#include <stdexcept> 

using namespace std;

class GraphNode;

class GraphEdge
{
public:
	weak_ptr<GraphNode> nodeA;
	weak_ptr<GraphNode> nodeB;
	size_t weight;

	///<summary>Creates a graph edge between the given nodes and with the given weight.</summary>
	///<remark>BigO notation for worst case is O(1).</remark>
	///<param name="nodeA">Pointer to the first to create an edge.</param>
	///<param name="nodeB">Pointer to the second to create an edge.</param>
	///<param name="weight">Positive weight for the edge.</param>
	GraphEdge(shared_ptr<GraphNode> nodeA, shared_ptr<GraphNode> nodeB, size_t weight);

	///<summary>Retreives the node to wich the given node is connected to.</summary>
	///<remark>BigO notation for worst case is O(1).</remark>
	///<param name="fromNode">Pointer to the node find to wich other is connected.</param>
	///<returns>A pointer to the connected node.</returns>
	shared_ptr<GraphNode> getToNode(shared_ptr<GraphNode> fromNode);
};

