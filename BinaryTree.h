#pragma once
#include <string>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class BinaryTreeNode;
class QueueBT;

class BinaryTree
{
public:
	shared_ptr<BinaryTreeNode> root;
	string lastChanged;
	vector<string> tempMarked;


	///<summary>Creates a new binary tree.</summary>
	///<remark>BigO notation for worst case is O(1).</remark>
	BinaryTree();

	///<summary>Add a new value into the tree.</summary>
	///<remark>BigO notation for worst case is O(log(n)).</remark>
	///<param name="value">Value of the new node to add.</param>
	///<returns>A pointer to the new created node.</returns>
	shared_ptr<BinaryTreeNode> insert(string value);

	///<summary>Look for the node with a specified value, prints the path to find it and if it was found or not.</summary>
	///<remark>BigO notation for worst case is O(log(n)).</remark>
	///<param name="value">Value to look for.</param>
	///<returns>If found, a pointer to the with the value, if not found, a null pointer.</returns>
	shared_ptr<BinaryTreeNode> find(string value);

	///<summary>Look for the node with the specified value and remove it.</summary>
	///<remark>BigO notation for worst case is O(log(n)).</remark>
	///<param name="value">Value of the node to remove.</param>
	///<returns>If exists, a pointer for the removed node, if not found, a null pointer.</returns>
	shared_ptr<BinaryTreeNode> remove(string value);

	///<summary>Remove the given node from the tree.</summary>
	///<remark>BigO notation for worst case is O(log(n)).</remark>
	///<param name="node">Pointer to the node to be removed.</param>
	///<returns>If exists, a pointer for the removed node, if not found, a null pointer.</returns>
	shared_ptr<BinaryTreeNode> remove(shared_ptr<BinaryTreeNode> node);

	///<summary>Check the given node's balance, if balenced, leaft heavy or right heavy.</summary>
	///<remark>BigO notation for worst case is O(1).</remark>
	///<param name="node">Node to check the childs balance.</param>
	///<returns>0 for balanced trees, -# for left heavy and +# for right heavy (where # is the difference of nodes), as an integer.</returns>
	int checkBalance(shared_ptr<BinaryTreeNode> node); 

	///<summary>Get the correct depth number for the given node.</summary>
	///<remark>BigO notation for worst case is O(1).</remark>
	///<param name="node">Node to compute the correct depth.</param>
	///<returns>The correct depth for the fiven node, as an intger.</returns>
	int getCorrectDepth(shared_ptr<BinaryTreeNode> node);

	///<summary>Balance the tree from the given node up.</summary>
	///<remark>BigO notation for worst case is O(log(n)).</remark>
	///<param name="node">Pointer of the node to balance.</param>
	void balanceTree(shared_ptr<BinaryTreeNode> node);

	///<summary>Find the maximum value node from the given node.</summary>
	///<remark>BigO notation for worst case is O(log(n)).</remark>
	///<param name="node">Node to find it's biggest value.</param>
	///<returns>A pair of a pointer to the maximum value node and the number of nodes it went through to find it.</returns>
	pair<shared_ptr<BinaryTreeNode>, int> findMax(shared_ptr<BinaryTreeNode> node);

	///<summary>Find the minimum value node from the given node.</summary>
	///<remark>BigO notation for worst case is O(log(n)).</remark>
	///<param name="node">Node to find it's smallest value.</param>
	///<returns>A pair of a pointer to the minimum value node and the number of nodes it went through to find it.</returns>
	pair<shared_ptr<BinaryTreeNode>, int> findMin(shared_ptr<BinaryTreeNode> node);

	///<summary>Find a possible replacer node for the given one. 
	///<para>The furthest maximum node from the left child or the minimum node from the right, depending on wich is further away.</para></summary>
	///<remark>BigO notation for worst case is O(log(n)).</remark>
	///<param name="node">Node from wich to find it's furthest replacer.</param>
	///<returns>A pointer to the node found.</returns>
	shared_ptr<BinaryTreeNode> getFurthestReplacerNode(shared_ptr<BinaryTreeNode> node);

	///<summary>Print a list of all the node values, in order.</summary>
	///<remark>BigO notation for worst case is O(n).</remark>
	///<param name="node">Pointer to the starting node, if null, starts at root.</param>
	void printInOrder(shared_ptr<BinaryTreeNode> node = nullptr);

	///<summary>Print a list of all the node values, in post order.</summary>
	///<remark>BigO notation for worst case is O(n).</remark>
	///<param name="node">Pointer to the starting node, if null, starts at root.</param>
	void printPostOrder(shared_ptr<BinaryTreeNode> node = nullptr);

	///<summary>Print an horizontal tree of the node values.</summary>
	///<remark>BigO notation for worst case is O(n).</remark>
	void print();
};