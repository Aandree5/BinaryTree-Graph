#include "pch.h"
#include "BinaryTree.h"
#include "BinaryTreeNode.h"
#include "QueueBT.h"

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
	if (!root)
	{
		root = make_shared<BinaryTreeNode>(value);

		return root;
	}

	shared_ptr<BinaryTreeNode> current = root;

	while (current)
	{
		if (current->value == value)
		{
			current->frequency++;

			break;
		}
		else
		{
			shared_ptr<BinaryTreeNode> &child = (value < current->value ? current->left : current->right);

			if (!child)
			{
				child = make_shared<BinaryTreeNode>(value);
				child->parent = current;

				balanceTree(child);

				return child;
			}
			else
				current = child;
		}
	}
	
	return current;
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

	if (balance >= -1 && balance <= 1)
	{
		shared_ptr<BinaryTreeNode> parent = node->parent.lock();
		if (parent)
		{
			parent->depth = node->depth + 1;
			balanceTree(parent);
		}
	}
	else if (balance < -1) // Left heavy
	{

		shared_ptr<BinaryTreeNode> tempRight = node->left->right;

		node->left->right = node;
		node->left->parent = node->parent;

		if (node->parent.lock())
			(node->parent.lock()->left == node ? node->parent.lock()->left : node->parent.lock()->right) = node->left;
		else
			root = node->left;

		node->depth = node->left->depth - 1;
		node->parent = node->left;

		if (tempRight)
		{
			node->left = tempRight;

			tempRight->parent = node;
		}
		else
			node->left = nullptr;
	}
	else if (balance > 1) // Right heavy
	{

		shared_ptr<BinaryTreeNode> tempLeft = node->right->left;

		node->right->left = node;
		node->right->parent = node->parent;

		if (node->parent.lock())
			(node->parent.lock()->left == node ? node->parent.lock()->left : node->parent.lock()->right) = node->right;
		else
			root = node->right;

		node->depth = node->right->depth - 1;
		node->parent = node->right;

		if (tempLeft)
		{
			node->right = tempLeft;

			tempLeft->parent = node;
		}
		else
			node->right = nullptr;
	}
}

shared_ptr<BinaryTreeNode> BinaryTree::find(string value)
{
	if (!root)
	{
		cout << "No nodes in the tree." << endl;

		return nullptr;
	}
	 
	cout << "?(" << value << "): ";

	shared_ptr<BinaryTreeNode> current = root;

	while (current && current->value != value)
	{
		cout << current->value << " > ";

		current = (value < current->value ? current->left : current->right);

		if (!current)
			cout << " ### NO ###" << endl;

		else if (current->value == value)
			cout << current->value << " ### YES ###" << endl;
	}

	return current;
}

string BinaryTree::remove(string value)
{
	shared_ptr<BinaryTreeNode> node = find(value);

	return (node ? remove(node) : "");
}

string BinaryTree::remove(shared_ptr<BinaryTreeNode> &node)
{
	string removedValue =node->value;
	shared_ptr<BinaryTreeNode> parent = node->parent.lock();

	if (node->isLeaf())
	{
		if (parent)
			(parent->left == node ? parent->left : parent->right) = nullptr;
		
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


	shared_ptr<BinaryTreeNode> current = root;

	while (current != node)
	{
		if (current->right == node || (current == node->parent.lock() && current->hasOnlyOnechild()))
		{
			cout << char(192) << char(196);
			break;
		}
		else if (current->left == node)
		{
			cout << char(195) << char(196);
			break;
		}
		else if (current->value > node->value  && !current->hasOnlyOnechild()) // Left child
		{
			cout << char(179) << "  ";

			if (!current->left)
				break;

			current = current->left;
		}
		else //Right child or just one child
		{
			cout << "   ";

			if (current->right)
				current = current->right;

			else if (current->hasOnlyOnechild())
				current = current->hasOnlyOnechild();

			else
				break;
		}
	}


	shared_ptr<BinaryTreeNode> parent = node->parent.lock();
	if (parent = node->parent.lock())
		cout << " " << (node == parent->left ? "-" : "+") << "> ";

	cout << to_string(node->depth) << ". " << node->value << " '" << to_string(node->frequency) << endl;

	if (node->left)
		print(node->left);
	if (node->right)
		print(node->right);
}

// TODO: FINISH PRINTING TREE
void BinaryTree::printTree()
{
	shared_ptr<QueueBT> queue = make_shared<QueueBT>();
	queue->push_back(root);
	int currDepth = root->depth + 1;
	int childs = 1;

	while (!queue->isEmpty())
	{
		shared_ptr<BinaryTreeNode> node = queue->pop();
		childs--;

		if (node->left)
			queue->push_back(node->left);

		if (node->right)
			queue->push_back(node->right);

		for (int i = (int)pow(2, root->depth - currDepth) * 4; i < currDepth*6; i++)
			cout << " ";

		cout << node->value;

		if (!childs)
		{
			childs = queue->size();
			currDepth--;
			cout << endl;
		}
	}

	cout << endl;
}