#pragma once
#include <memory>
#include "SinglyItems.h"

using namespace std;

template<class T>
class StackSingly
{
	shared_ptr<SinglyItem<T>> stackTop;

public:
	StackSingly()
	{
		stackTop = nullptr;
	};

	void push(shared_ptr<T> reference)
	{
		if (!stackTop)
			stackTop = make_shared<SinglyItem<T>>(reference);

		else
		{
			shared_ptr<SinglyItem<T>> temp = make_shared<SinglyItem<T>>(reference);
			temp->next = stackTop;
			stackTop = temp;
		}
	};

	shared_ptr<SinglyItem<T>> top()
	{
		return stackTop;
	}

	shared_ptr<T> pop()
	{
		shared_ptr<T> node = nullptr;

		if (stackTop)
		{
			node = stackTop->reference;

			stackTop = stackTop->next;
		}

		return node;
	};

	bool isEmpty()
	{
		return stackTop == nullptr;
	};

	int size()
	{
		int size = 0;

		if (stackTop)
		{
			shared_ptr<SinglyItem<T>> temp = stackTop;

			while ((temp = temp->next) != nullptr)
				size++;
		}

		return size;
	};

	bool contains(shared_ptr<T> reference)
	{
		shared_ptr<SinglyItem<T>> current = stackTop;

		while (current)
		{
			if (current->reference.lock() == reference)
				break;

			current = current->next;
		}

		return (bool)current;
	}
	
	void clear()
	{
		stackTop = nullptr;
	}
};

