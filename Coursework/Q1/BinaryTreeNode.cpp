#include "stdafx.h"
#include "BinaryTreeNode.h"

BinaryTreeNode::BinaryTreeNode(string value)
{
	this->value = value;
	left = nullptr;
	right = nullptr;

	cout << "Node Created" << endl;
}

BinaryTreeNode::~BinaryTreeNode()
{
	cout << "Node Deleted: " << value << endl;
}