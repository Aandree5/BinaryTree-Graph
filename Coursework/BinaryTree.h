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
	///<returns>If exists, the value of the removed node, as a string, if not found, an empty string.</returns>
	string remove(string value);

	///<summary>Remove the given node from the tree.</summary>
	///<param name="node">Reference of the pointer to the node to be removed.</param>
	///<returns>If exists, the value of the removed node, as a string, if not found, an empty string.</returns>
	string remove(shared_ptr<BinaryTreeNode> &node);

	///<summary>Check the given node's balance, if balenced, leaft heavy or right heavy.</summary>
	///<param name="node">Node to check the childs balance.</param>
	///<returns>0 for balanced trees, -# for left heavy and +# for right heavy (where # is the difference of nodes), as an integer.</returns>
	int checkBalance(shared_ptr<BinaryTreeNode> node); 

	///<summary>Get the correct depth number for the given node.</summary>
	///<param name="node">Node to compute the correct depth.</param>
	///<returns>The correct depth for the fiven node, as an intger.</returns>
	int getCorrectDepth(shared_ptr<BinaryTreeNode> node);

	///<summary>Balance the tree from the given node up.</summary>
	///<param name="node">Reference of the node to balance.</param>
	void balanceTree(shared_ptr<BinaryTreeNode> &node);

	///<summary>Find the maximum value node from the given node.</summary>
	///<param name="node">Node to find it's biggest value.</param>
	///<returns>A pair of a pointer to the maximum value node and the number of nodes it went through to find it.</returns>
	pair<shared_ptr<BinaryTreeNode>, int> findMax(shared_ptr<BinaryTreeNode> node);

	///<summary>Find the minimum value node from the given node.</summary>
	///<param name="node">Node to find it's smallest value.</param>
	///<returns>A pair of a pointer to the minimum value node and the number of nodes it went through to find it.</returns>
	pair<shared_ptr<BinaryTreeNode>, int> findMin(shared_ptr<BinaryTreeNode> node);
	shared_ptr<BinaryTreeNode> getFurthestReplacerNode(shared_ptr<BinaryTreeNode> node);

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