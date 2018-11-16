#include "pch.h"
#include "BinaryTreeNode.h"

BinaryTreeNode::BinaryTreeNode(string value)
{
	if (value == "")
		throw invalid_argument("Argument 'value' is empty. Can't create node.");

	this->value = value;
	left = nullptr;
	right = nullptr;
	frequency = 1;
	depth = 1;
}

BinaryTreeNode::~BinaryTreeNode()
{
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