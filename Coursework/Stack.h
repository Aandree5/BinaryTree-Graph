#pragma once
#include <memory>

using namespace std;

template<class T>
struct StackItem
{
	shared_ptr<T> reference;
	shared_ptr<StackItem> next;

	StackItem(shared_ptr<T> reference)
	{
		this->reference = reference;
		next = nullptr;
	};
};

template<class T>
class Stack
{
	shared_ptr<StackItem<T>> top;

public:
	Stack()
	{
		top = nullptr;
	};

	void push(shared_ptr<T> reference)
	{
		if (!top)
			top = make_shared<StackItem<T>>(reference);

		else
		{
			shared_ptr<StackItem<T>> temp = make_shared<StackItem<T>>(reference);
			temp->next = top;
			top = temp;
		}
	};

	shared_ptr<T> pop()
	{
		shared_ptr<T> node = nullptr;

		if (top)
		{
			node = top->reference;

			top = top->next;
		}

		return node;
	};

	bool isEmpty()
	{
		return top == nullptr;
	};

	int size()
	{
		int size = 0;

		if (top)
		{
			shared_ptr<StackItem<T>> temp = top;

			while ((temp = temp->next) != nullptr)
				size++;
		}

		return size;
	};
};

