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
	if (!node)
	{
		node = make_shared<BinaryTreeNode>(value);

		return node;
	}
	else
	{
		shared_ptr<BinaryTreeNode> &child = (value < node->value ? node->left : node->right);

		if (!child)
		{
			child = make_shared<BinaryTreeNode>(value);
			child->parent = node;
			return child;
		}
		else
			return insert(value, child);
	}
}

void BinaryTree::printInOrder(shared_ptr<BinaryTreeNode> node)
{
	if (!node)
		node = root;

	if (node->left)
		printInOrder(node->left);

	cout << node->value << endl;

	/* DEBUG
	cout << "Parent " << (node->parent.lock() ? node->parent.lock()->value : "NULL") << endl;
	cout << "Left " << (node->left ? node->left->value : "NULL") << endl;
	cout << "Right " << (node->right ? node->right->value : "NULL") << endl;
	cout << endl;
	*/

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

	cout << node->value << endl;
}