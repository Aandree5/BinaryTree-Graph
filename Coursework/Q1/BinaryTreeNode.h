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
	int frequency;

	BinaryTreeNode(string value);
	~BinaryTreeNode();

	int increaseFrequency();
	int decreaseFrequency();
	bool isLeaf();
	bool hasOnlyOnechild();
};