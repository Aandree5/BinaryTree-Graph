#pragma once
#include <memory>
#include <stdexcept> 

using namespace std;

class UnweightedGraphNode;

class UnweightedGraphEdge
{
public:
	weak_ptr<UnweightedGraphNode> nodeA;
	weak_ptr<UnweightedGraphNode> nodeB;
	size_t weight;

	///<summary>Creates a graph edge between the given nodes and with the given weight.</summary>
	///<remark>BigO notation for worst case is O(1).</remark>
	///<param name="nodeA">Pointer to the first to create an edge.</param>
	///<param name="nodeB">Pointer to the second to create an edge.</param>
	///<param name="weight">Positive weight for the edge.</param>
	UnweightedGraphEdge(shared_ptr<UnweightedGraphNode> nodeA, shared_ptr<UnweightedGraphNode> nodeB, size_t weight);

	///<summary>Retreives the node to wich the given node is connected to.</summary>
	///<remark>BigO notation for worst case is O(1).</remark>
	///<param name="fromNode">Pointer to the node find to wich other is connected.</param>
	///<returns>A pointer to the connected node.</returns>
	shared_ptr<UnweightedGraphNode> getToNode(shared_ptr<UnweightedGraphNode> fromNode);
};

