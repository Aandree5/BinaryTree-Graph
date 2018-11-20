#pragma once
#include <memory>

using namespace std;

template<class T>
struct StackItem
{
	shared_ptr<T> reference;
	shared_ptr<StackItem<T>> next;

	StackItem(shared_ptr<T> reference)
	{
		this->reference = reference;
		next = nullptr;
	};
};

template<class T>
class Stack
{
	shared_ptr<StackItem<T>> stackTop;

public:
	Stack()
	{
		stackTop = nullptr;
	};

	void push(shared_ptr<T> reference)
	{
		if (!stackTop)
			stackTop = make_shared<StackItem<T>>(reference);

		else
		{
			shared_ptr<StackItem<T>> temp = make_shared<StackItem<T>>(reference);
			temp->next = stackTop;
			stackTop = temp;
		}
	};

	shared_ptr<StackItem<T>> top()
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

	shared_ptr<T> remove(shared_ptr<T> reference)
	{
		if (stackTop->reference == reference)
			stackTop = stackTop->next;

		else
		{
			shared_ptr<StackItem<T>> current = stackTop;

			while (current->next)
			{
				if (current->next->reference == reference)
					break;

				else
					current = current->next;
			}

			if (current->next->reference == reference)
				current->next = current->next->next;

			else
				return nullptr;
		}

		return reference;
	}

	bool isEmpty()
	{
		return stackTop == nullptr;
	};

	int size()
	{
		int size = 0;

		if (stackTop)
		{
			shared_ptr<StackItem<T>> temp = stackTop;

			while ((temp = temp->next) != nullptr)
				size++;
		}

		return size;
	};
};

