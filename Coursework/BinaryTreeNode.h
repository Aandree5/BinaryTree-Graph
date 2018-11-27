#pragma once
#include <memory>
#include <iostream>
#include <string>

using namespace std;

class BinaryTreeNode
{
public:
	string value;
	weak_ptr<BinaryTreeNode> parent;
	shared_ptr<BinaryTreeNode> left;
	shared_ptr<BinaryTreeNode> right;

	///<summary>Number of times this node's <paramref name="value"/> was added to the tree.</summary>
	int frequency;

	///<summary>Depth of the node, starting at the farthest leaf (1 indexed).</summary>
	int depth;

	///<summary>Creates a binary tree node with the given value.</summary>
	///<param name="value">Value for the new node.</param>
	BinaryTreeNode(string value);

	///<summary>Checks if node has childs.</summary>
	///<returns>True if node is leaf(has no childs), false otherwise.</returns>
	bool isLeaf();

	///<summary>Checks if node has only one child.</summary>
	///<returns>A pointer to the child node if true, null pointer otherwise.</returns>
	shared_ptr<BinaryTreeNode> hasOnlyOnechild();


	// ### Operators ###
	operator string() const
	{
		return value;
	}

	friend ostream &operator<<(ostream &os, const BinaryTreeNode &node)
	{
		os << node.value;

		return os;
	}

	friend wostream &operator<<(wostream &wos, const BinaryTreeNode &node)
	{
		wos << node.value.c_str();

		return wos;
	}
};