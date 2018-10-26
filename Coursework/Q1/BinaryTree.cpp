
#include "stdafx.h"
#include "BinaryTree.h"

Node::Node(string value)
{
	this->value = value;
	prev = nullptr;
	next = nullptr;

	cout << "Node Created" << endl;
}

Node::~Node()
{
	cout << "Node Deleted: " << value << endl;
}


LinkedList::LinkedList()
{
	head = nullptr;
	tail = nullptr;

	cout << "Linked List Created" << endl;
}

LinkedList::~LinkedList()
{
	cout << "Linked List Deleted" << endl;
}	

void LinkedList::push_back(string value)
{
	if (head == nullptr)
	{
		head = make_shared<Node>(value);
		tail = head;
	}
}

BinaryTree::BinaryTree()
{
	list = make_unique<LinkedList>();
	list->push_back("Test");

	cout << "Binary Tree Created" << endl;
}

BinaryTree::~BinaryTree()
{
	cout << "Binary Tree Deleted" << endl;
}