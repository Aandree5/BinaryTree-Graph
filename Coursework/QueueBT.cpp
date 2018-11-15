#include "pch.h"
#include "QueueBT.h"


QueueBT::QueueBT()
{
	head = nullptr;
	tail = nullptr;
}


QueueBT::~QueueBT()
{
}

void QueueBT::push_back(shared_ptr<BinaryTreeNode> &reference)
{
	if (!head)
	{
		head = make_shared<QueueBTNode>(reference);
		tail = head;
	}
	else
	{
		shared_ptr<QueueBTNode> temp = make_shared<QueueBTNode>(reference);
		tail->next = temp;
		tail = temp;
	}
}

shared_ptr<BinaryTreeNode> QueueBT::pop()
{
	shared_ptr<BinaryTreeNode> node = nullptr;

	if (head)
	{
		node = head->reference;
		
		if (head != tail)
			head = head->next;

		else
		{
			head = nullptr;
			tail = nullptr;
		}
	}

	return node;
}

bool QueueBT::isEmpty()
{
	return head == nullptr;
}

int QueueBT::size()
{
	if (!head)
		return 0;

	if (head == tail)
		return 1;

	int size = 1;
	shared_ptr<QueueBTNode> temp = head;

	while ((temp = temp->next) != nullptr)
		size++;

	return size;
}
