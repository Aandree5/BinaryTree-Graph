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
	int depth;

	BinaryTreeNode(string value);
	~BinaryTreeNode();

	bool isLeaf();
	shared_ptr<BinaryTreeNode> hasOnlyOnechild();
};