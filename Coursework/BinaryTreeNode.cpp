#include "pch.h"
#include "BinaryTreeNode.h"

BinaryTreeNode::BinaryTreeNode(string value)
{
	this->value = value;
	left = nullptr;
	right = nullptr;
	frequency = 1;
	depth = 1;

	cout << "Node Created" << endl;
}

BinaryTreeNode::~BinaryTreeNode()
{
	cout << "Node Deleted: " << value << endl;
}

bool BinaryTreeNode::isLeaf()
{
	return (!left && !right);
}

shared_ptr<BinaryTreeNode> BinaryTreeNode::hasOnlyOnechild()
{
	if ((!left || !right) && (left != right))
		return (left ? left : right);

	else
		return nullptr;
}