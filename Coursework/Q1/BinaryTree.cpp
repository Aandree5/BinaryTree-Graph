#include "stdafx.h"
#include "BinaryTree.h"

BinaryTree::BinaryTree()
{
	root = nullptr;

	cout << "Binary Tree Created" << endl;
}

BinaryTree::~BinaryTree()
{
	cout << "Binary Tree Deleted" << endl;
}

shared_ptr<BinaryTreeNode> BinaryTree::insert(string value)
{
	return insert(value, root);
}

shared_ptr<BinaryTreeNode> BinaryTree::insert(string value, shared_ptr<BinaryTreeNode> &node)
{
	if (!node) // For the root case
	{
		node = make_shared<BinaryTreeNode>(value);

		return node;
	}
	else if (value == node->value)
	{
		node->frequency++;

		return node;
	}
	else
	{
		shared_ptr<BinaryTreeNode> &child = (value < node->value ? node->left : node->right);

		if (!child)
		{
			if (node->isLeaf())
			{
				node->depth++;

				shared_ptr<BinaryTreeNode> parent = node->parent.lock();
				if (parent)
					balanceTree(parent);
			}

			child = make_shared<BinaryTreeNode>(value);
			child->parent = node;

			return child;
		}
		else
			return insert(value, child);
	}
}

int BinaryTree::checkBalance(shared_ptr<BinaryTreeNode> &node)
{
	int depthLeft = (node->left ? node->left->depth : 0);
	int depthRight = (node->right ? node->right->depth : 0);

	return depthRight - depthLeft;
}

void BinaryTree::balanceTree(shared_ptr<BinaryTreeNode> &node)
{
	int balance = checkBalance(node);

	// CHECK IS BALANCED
	if (balance < -1 || balance > 1)
	{

		// BALANCE TREE

		// FIX PARENT DEPTH
	}
}

shared_ptr<BinaryTreeNode> BinaryTree::find(string value)
{
	return find(value, root);
}

shared_ptr<BinaryTreeNode> BinaryTree::find(string value, shared_ptr<BinaryTreeNode> &node)
{
	if (!node)
	{
		cout << " ### NO ###" << endl;

		return nullptr;
	}

	if (value == node->value)
	{
		cout << node->value;

		cout << " ### YES ###" << endl;

		return node;
	}

	cout << node->value << " > ";

	return find(value, (value < node->value ? node->left : node->right));
}

string BinaryTree::remove(string value)
{
	shared_ptr<BinaryTreeNode> node = find(value);

	return (node ? remove(node) : nullptr);
}

string BinaryTree::remove(shared_ptr<BinaryTreeNode> &node)
{
	string removedValue =node->value;
	shared_ptr<BinaryTreeNode> parent = node->parent.lock();

	if (node->isLeaf())
	{
		if (parent)
		{
			(parent->left == node ? parent->left : parent->right) = nullptr;

			parent->depth--;
			balanceTree(parent);
		}
		else
			root = nullptr;
	}
	else if (shared_ptr<BinaryTreeNode> child = node->hasOnlyOnechild())
	{
		if (parent)
		{
			(parent->left == node ? parent->left : parent->right) = child;
			child->parent = parent;
		}
		else
			root = child;
	}

	else
	{
		shared_ptr<BinaryTreeNode> replacerNode = getBiggestSubTreeNode(node); // IT WILL BE BALANCED SO NO NEED FOR THIS FUNCTION
		string v = node->value;

		node->value = replacerNode->value;
		node->frequency = replacerNode->frequency;

		replacerNode->value = v;

		remove(replacerNode);
	}

	return removedValue;
}

pair<shared_ptr<BinaryTreeNode>, int> BinaryTree::findMax(shared_ptr<BinaryTreeNode> &node, int nodesCounted)
{
	if (!node->right)
		return pair<shared_ptr<BinaryTreeNode>, int>(node, nodesCounted);

	return findMax(node->right, nodesCounted++);
}

pair<shared_ptr<BinaryTreeNode>, int> BinaryTree::findMin(shared_ptr<BinaryTreeNode> &node, int nodesCounted)
{
	if (!node->left)
		return pair<shared_ptr<BinaryTreeNode>, int>(node, nodesCounted);

	return findMin(node->left, nodesCounted++);
}

shared_ptr<BinaryTreeNode> BinaryTree::getBiggestSubTreeNode(shared_ptr<BinaryTreeNode> &node)
{
	pair<shared_ptr<BinaryTreeNode>, int> min = findMin(node->right);
	pair<shared_ptr<BinaryTreeNode>, int> max = findMax(node->left);

	return (min.second > max.second ? min.first : max.first);
}

void BinaryTree::printInOrder(shared_ptr<BinaryTreeNode> node)
{
	if (!node)
		node = root;

	if (node->left)
		printInOrder(node->left);

	cout << to_string(node->frequency) << " " << node->value << endl;

	if (node->right)
		printInOrder(node->right);
}

void BinaryTree::printPostOrder(shared_ptr<BinaryTreeNode> node)
{
	if (!node)
		node = root;

	if (node->left)
		printInOrder(node->left);

	if (node->right)
		printInOrder(node->right);

	cout << to_string(node->frequency) << " " << node->value << endl;
}

void BinaryTree::print(shared_ptr<BinaryTreeNode> node)
{
	if (!node)
		node = root;


	shared_ptr<BinaryTreeNode> parent = node->parent.lock();

	while (parent)
	{
		cout << "|  ";

		parent = parent->parent.lock();
	}


	if (parent = node->parent.lock())
		cout << (node == parent->left ? "-" : "+") << "> ";

	cout << to_string(node->depth) << ") " << to_string(node->frequency) << " " << node->value << endl;

	if (node->left)
		print(node->left);
	if (node->right)
		print(node->right);
}