#include "stdafx.h"
#include "BinaryTreeNode.h"

BinaryTreeNode::BinaryTreeNode(string value)
{
	this->value = value;
	left = nullptr;
	right = nullptr;
	frequency = 1;

	cout << "Node Created" << endl;
}

BinaryTreeNode::~BinaryTreeNode()
{
	cout << "Node Deleted: " << value << endl;
}

int BinaryTreeNode::increaseFrequency()
{
	return frequency++;
}

int BinaryTreeNode::decreaseFrequency()
{
	frequency--;
	if (frequency == 0)
	{
		//TODO: DELETE NODE IF FREQUENCY IS 0
	}

	return frequency;
}

bool BinaryTreeNode::isLeaf()
{
	return (!left && !right);
}

bool BinaryTreeNode::hasOnlyOnechild()
{
	return (!left || !right) && (left != right);
}