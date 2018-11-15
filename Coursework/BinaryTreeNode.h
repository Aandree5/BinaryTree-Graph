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

	///<summary>Distance from this node to the farthest leaf.</summary>
	int depth;

	BinaryTreeNode(string value);
	~BinaryTreeNode();

	///<summary>Checks if node has childs.</summary>
	///<returns>True if node is leaf(has no childs), false otherwise.</returns>
	bool isLeaf();

	///<summary>Checks if node has only one child.</summary>
	///<returns>A pointer to the child node if true, null pointer otherwise.</returns>
	shared_ptr<BinaryTreeNode> hasOnlyOnechild();
};