#pragma once
#include <string>
#include <iostream>
#include <memory>

using namespace std;

class BinaryTreeNode;

class BinaryTree
{
public:
	shared_ptr<BinaryTreeNode> root;

	BinaryTree();
	~BinaryTree();

	///<summary>Add a new value into the tree.</summary>
	///<param name="value">Value of the new node to add.</param>
	///<returns>A pointer to the new created node.</returns>
	shared_ptr<BinaryTreeNode> insert(string value);

	///<summary>Look for the node with a specified value, prints the path to find it and if it was found or not.</summary>
	///<param name="value">Value to look for.</param>
	///<returns>If found, a pointer to the with the value, if not found, a null pointer.</returns>
	shared_ptr<BinaryTreeNode> find(string value);

	///<summary>Look for the node with the specified value and remove it.</summary>
	///<param name="value">Value of the node to remove.</param>
	///<returns>If exists, the value of the removed node, if not found, an empty string.</returns>
	string remove(string value);

	///<summary>Remove the given node from the tree.</summary>
	///<param name="&node">Reference of the pointer to the node to be removed.</param>
	///<returns>If exists, the value of the removed node, if not found, an empty string.</returns>
	string remove(shared_ptr<BinaryTreeNode> &node);

	int checkBalance(shared_ptr<BinaryTreeNode> &node);
	void balanceTree(shared_ptr<BinaryTreeNode> &node);

	pair<shared_ptr<BinaryTreeNode>, int> findMax(shared_ptr<BinaryTreeNode> &node, int nodesCounted = 1);
	pair<shared_ptr<BinaryTreeNode>, int> findMin(shared_ptr<BinaryTreeNode> &node, int nodesCounted = 1);
	shared_ptr<BinaryTreeNode> getBiggestSubTreeNode(shared_ptr<BinaryTreeNode> &node);

	///<summary>Print a list of all the node values, in order.</summary>
	///<param name="node">Pointer to the starting node, if null, starts at root.</param>
	void printInOrder(shared_ptr<BinaryTreeNode> node = nullptr);

	///<summary>Print a list of all the node values, in post order.</summary>
	///<param name="node">Pointer to the starting node, if null, starts at root.</param>
	void printPostOrder(shared_ptr<BinaryTreeNode> node = nullptr);

	///<summary>Print an horizontal tree of the node values.</summary>
	///<param name="node">Pointer to the starting node, if null, starts at root.</param>
	void print(shared_ptr<BinaryTreeNode> node = nullptr);

	// NOT WORKING
	void printTree();
};