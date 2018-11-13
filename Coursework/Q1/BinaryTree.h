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

	shared_ptr<BinaryTreeNode> find(string value);
	shared_ptr<BinaryTreeNode> find(string value, shared_ptr<BinaryTreeNode> &node);

	string remove(string value);
	string remove(shared_ptr<BinaryTreeNode> &node);

	int checkBalance(shared_ptr<BinaryTreeNode> &node);
	void balanceTree(shared_ptr<BinaryTreeNode> &node);

	pair<shared_ptr<BinaryTreeNode>, int> findMax(shared_ptr<BinaryTreeNode> &node, int nodesCounted = 1);
	pair<shared_ptr<BinaryTreeNode>, int> findMin(shared_ptr<BinaryTreeNode> &node, int nodesCounted = 1);
	shared_ptr<BinaryTreeNode> getBiggestSubTreeNode(shared_ptr<BinaryTreeNode> &node);

	void printInOrder(shared_ptr<BinaryTreeNode> node = nullptr);
	void printPostOrder(shared_ptr<BinaryTreeNode> node = nullptr);
	void print(shared_ptr<BinaryTreeNode> node = nullptr);
};