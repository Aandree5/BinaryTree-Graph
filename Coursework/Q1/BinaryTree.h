#pragma once
#include <string>
#include <iostream>
#include <memory>
#include "BinaryTreeNode.h"

using namespace std;

class BinaryTree
{
public:
	shared_ptr<BinaryTreeNode> root;

	BinaryTree();
	~BinaryTree();

	shared_ptr<BinaryTreeNode> insert(string value);
	shared_ptr<BinaryTreeNode> insert(string value, shared_ptr<BinaryTreeNode> &node);

	void printInOrder(shared_ptr<BinaryTreeNode> node = nullptr);
	void printPostOrder(shared_ptr<BinaryTreeNode> node = nullptr);
};