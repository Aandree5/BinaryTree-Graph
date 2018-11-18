#include "pch.h"
#include "BinaryTree.h"
#include "BinaryTreeNode.h"
#include "QueueBT.h"

BinaryTree::BinaryTree()
{
	root = nullptr;
}

BinaryTree::~BinaryTree()
{
}

shared_ptr<BinaryTreeNode> BinaryTree::insert(string value)
{
	shared_ptr<BinaryTreeNode> nodeToReturn;

	if (!root)
	{
		root = make_shared<BinaryTreeNode>(value);

		nodeToReturn = root;
	}
	else
	{
		shared_ptr<BinaryTreeNode> current = root;

		while (!nodeToReturn)
		{
			if (current->value == value)
			{
				current->frequency++;

				nodeToReturn = current;
			}
			else
			{
				shared_ptr<BinaryTreeNode> &childReference = (value < current->value ? current->left : current->right);

				if (!childReference)
				{
					nodeToReturn = make_shared<BinaryTreeNode>(value);
					nodeToReturn->parent = current;
					childReference = nodeToReturn;

					balanceTree(nodeToReturn);
				}
				else
					current = childReference;
			}
		}
	}

	return nodeToReturn;
}

shared_ptr<BinaryTreeNode> BinaryTree::find(string value)
{
	if (value == "")
		throw invalid_argument("'value' can't be empty.");

	shared_ptr<BinaryTreeNode> current = root;

	cout << "?(" << value << "): ";

	do
	{
		if (!current)
			cout << " ### NO ###" << endl;

		else if (current->value == value)
		{
			cout << current->value << " ### YES ###" << endl;

			break;
		}
		else
		{
			cout << current->value << " > ";

			current = (value < current->value ? current->left : current->right);
		}
	} while (current);

	return current;
}

shared_ptr<BinaryTreeNode> BinaryTree::remove(string value)
{
	if (value == "")
		throw invalid_argument("'value' can't be empty.");

	shared_ptr<BinaryTreeNode> node = find(value);

	return (node ? remove(node) : nullptr);
}

shared_ptr<BinaryTreeNode> BinaryTree::remove(shared_ptr<BinaryTreeNode> node)
{
	if (!node)
		throw invalid_argument("'node' can't be null.");

	shared_ptr<BinaryTreeNode> parent = node->parent.lock();

	if (node->frequency > 1)
		node->frequency--;

	else if (node->isLeaf())
	{
		if (parent)
		{
			(parent->left == node ? parent->left : parent->right) = nullptr;

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
		else // Node parent is a weak pointer. no need to set null
			root = child;


		balanceTree(child);
	}
	else
	{
		shared_ptr<BinaryTreeNode> replacerNode = getFurthestReplacerNode(node);
		shared_ptr<BinaryTreeNode> balanceFrom = replacerNode->parent.lock();

		// When replacerNode is removed there's only two options, or is leaf or has only one child
		// Because getFurthestReplacerNode() will choose the min or max of either side, if it had two children the function would continue
		if (shared_ptr<BinaryTreeNode> child = replacerNode->hasOnlyOnechild())
		{
			child->parent = replacerNode;

			// No need to check if is root, replacernode will always be on top of every child, forcing this node to have a parent
			(balanceFrom->left == replacerNode ? balanceFrom->left : balanceFrom->right) = child;

			balanceFrom = child;
		}
		else
			(balanceFrom->left == replacerNode ? balanceFrom->left : balanceFrom->right) = nullptr;

		replacerNode->parent = node->parent;
		replacerNode->left = node->left;
		replacerNode->right = node->right;

		if (parent)
			(parent->left == node ? parent->left : parent->right) = replacerNode;

		else
			root = replacerNode;

		if (node->left)
			node->left->parent = replacerNode;

		if (node->right)
			node->right->parent = replacerNode;

		balanceTree(balanceFrom);
	}

	return node;
}

int BinaryTree::checkBalance(shared_ptr<BinaryTreeNode> node)
{
	if (!node)
		throw invalid_argument("'node' can't be null.");

	int depthLeft = (node->left ? node->left->depth : 0);
	int depthRight = (node->right ? node->right->depth : 0);

	return depthRight - depthLeft;
}

int BinaryTree::getCorrectDepth(shared_ptr<BinaryTreeNode> node)
{
	if (!node)
		throw invalid_argument("'node' can't be null.");

	if (node->isLeaf())
		return 1;

	else if (shared_ptr<BinaryTreeNode> child = node->hasOnlyOnechild())
		return child->depth + 1;

	else
		return (node->left->depth > node->right->depth ? node->left->depth : node->right->depth) + 1;
}

void BinaryTree::balanceTree(shared_ptr<BinaryTreeNode> node)
{
	if (!node)
		throw invalid_argument("'node' can't be null.");

	int balance = checkBalance(node);

	if (balance >= -1 && balance <= 1)
	{
		node->depth = getCorrectDepth(node);

		if (shared_ptr<BinaryTreeNode> parent = node->parent.lock())
			balanceTree(parent);
	}
	else
	{
		if (balance < -1) // Left Heavy
		{
			int childBalance = checkBalance(node->left);

			// Left Right Heavy
			/*		  T			->		R
					 /			->	   / \
					O			->	  O   T
					 \			->
					  R	 		->					*/
			if (childBalance > 0)
			{
				shared_ptr<BinaryTreeNode> tempLeftRight = node->left->right;

				if (tempLeftRight->left)
					tempLeftRight->left->parent = node->left;

				if (tempLeftRight->right)
					tempLeftRight->right->parent = node;

				node->left->right = tempLeftRight->left;
				tempLeftRight->left = node->left;

				node->left = tempLeftRight->right;
				tempLeftRight->right = node;

				if (shared_ptr<BinaryTreeNode> parent = node->parent.lock())
					(parent->left == node ? parent->left : parent->right) = tempLeftRight;
				else
					root = tempLeftRight;

				tempLeftRight->parent = node->parent;
				tempLeftRight->left->parent = tempLeftRight;
				node->parent = tempLeftRight;

				tempLeftRight->depth = getCorrectDepth(tempLeftRight);
				tempLeftRight->left->depth = getCorrectDepth(tempLeftRight->left);
			}

			// Left Left Heavy
			/*		  T			->		O
					 /			->	   / \
					O			->	  L   T
				   /			->
				  L	 			->					*/
			else
			{
				shared_ptr<BinaryTreeNode> tempRight = node->left->right;

				node->left->right = node;
				node->left->parent = node->parent;

				if (shared_ptr<BinaryTreeNode> parent = node->parent.lock())
					(parent->left == node ? parent->left : parent->right) = node->left;
				else
					root = node->left;

				node->parent = node->left;

				if (tempRight)
				{
					node->left = tempRight;

					tempRight->parent = node;
				}
				else
					node->left = nullptr;
			}
		}
		else if (balance > 1) // Right Heavy
		{
			int childBalance = checkBalance(node->right);

			// Right Left Heavy
			/*		  T			->		V
					   \		->	   / \
						X		->	  T   X
					   /		->
					  V			->					*/
			if (childBalance < 0)
			{
				shared_ptr<BinaryTreeNode> tempRightLeft = node->right->left;

				if (tempRightLeft->right)
					tempRightLeft->right->parent = node->right;

				if (tempRightLeft->left)
					tempRightLeft->left->parent = node;

				node->right->left = tempRightLeft->right;
				tempRightLeft->right = node->right;

				node->right = tempRightLeft->left;
				tempRightLeft->left = node;

				if (shared_ptr<BinaryTreeNode> parent = node->parent.lock())
					(parent->left == node ? parent->left : parent->right) = tempRightLeft;
				else
					root = tempRightLeft;

				tempRightLeft->parent = node->parent;
				tempRightLeft->right->parent = tempRightLeft;
				node->parent = tempRightLeft;

				tempRightLeft->depth = getCorrectDepth(tempRightLeft);
				tempRightLeft->right->depth = getCorrectDepth(tempRightLeft->right);
			}

			// Right Right Heavy
			/*		  T			->		X
					   \		->	   / \
						X		->	  T   Z
						 \ 		->
						  Z		->					*/
			else
			{
				shared_ptr<BinaryTreeNode> tempLeft = node->right->left;

				node->right->left = node;
				node->right->parent = node->parent;

				if (shared_ptr<BinaryTreeNode> parent = node->parent.lock())
					(parent->left == node ? parent->left : parent->right) = node->right;
				else
					root = node->right;

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

		node->depth = getCorrectDepth(node);

		if (shared_ptr<BinaryTreeNode> parent = node->parent.lock())
		{
			parent->depth = getCorrectDepth(parent);

			if (parent = parent->parent.lock())
				balanceTree(parent);
		}
	}
}

pair<shared_ptr<BinaryTreeNode>, int> BinaryTree::findMax(shared_ptr<BinaryTreeNode> node)
{
	int count = 1;

	while (node->right)
	{
		count++;

		node = node->right;
	}

	return pair<shared_ptr<BinaryTreeNode>, int>(node, count);
}

pair<shared_ptr<BinaryTreeNode>, int> BinaryTree::findMin(shared_ptr<BinaryTreeNode> node)
{
	int count = 1;

	while (node->left)
	{
		count++;

		node = node->left;
	}
	
	return pair<shared_ptr<BinaryTreeNode>, int>(node, count);
}

shared_ptr<BinaryTreeNode> BinaryTree::getFurthestReplacerNode(shared_ptr<BinaryTreeNode> node)
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

	cout << to_string(node->depth) << ". " << *node << endl;

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