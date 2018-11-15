#pragma once
#include <memory>
#include "BinaryTreeNode.h"

using namespace std;

class QueueBTNode
{
public:
	shared_ptr<BinaryTreeNode> reference;
	shared_ptr<QueueBTNode> next;

	QueueBTNode(shared_ptr<BinaryTreeNode> &reference);
	~QueueBTNode();
};

