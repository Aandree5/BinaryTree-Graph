#pragma once
#include <memory>
#include "QueueBTNode.h"

using namespace std;

//TODO: Make a varied type class T, not just BinaryTree
class QueueBT
{
	shared_ptr<QueueBTNode> head;
	shared_ptr<QueueBTNode> tail;

public:
	QueueBT();
	~QueueBT();

	void push_back(shared_ptr<BinaryTreeNode> &reference);
	shared_ptr<BinaryTreeNode> pop();
	bool isEmpty();
	int size();
};

