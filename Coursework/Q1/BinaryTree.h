#pragma once
#include <memory>
#include <string>
#include <iostream>

using namespace std;

class Node
{
public:
	string value;
	shared_ptr<Node> prev;
	shared_ptr<Node> next;

	Node(string value);
	~Node();
};

class LinkedList
{
public:
	shared_ptr<Node> head;
	shared_ptr<Node> tail;

	LinkedList();
	~LinkedList();

	void push_back(string value);
};

class BinaryTree
{
public:
	unique_ptr<LinkedList> list;

	BinaryTree();
	~BinaryTree();
};