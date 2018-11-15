#include "pch.h"
#include "QueueBTNode.h"


QueueBTNode::QueueBTNode(shared_ptr<BinaryTreeNode> &reference)
{
	this->reference = reference;
	next = nullptr;
}


QueueBTNode::~QueueBTNode()
{
}
