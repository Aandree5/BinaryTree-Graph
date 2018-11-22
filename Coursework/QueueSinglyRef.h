#pragma once
#include <memory>
#include "SinglyItems.h"

using namespace std;

template<class T>
class QueueSinglyRef
{
	shared_ptr<SinglyRefItem<T>> head;
	shared_ptr<SinglyRefItem<T>> tail;

public:
	QueueSinglyRef()
	{
		head = nullptr;
		tail = nullptr;
	};

	void push_back(shared_ptr<T> reference)
	{
		if (!head)
		{
			head = make_shared<SinglyRefItem<T>>(reference);
			tail = head;
		}
		else
		{
			shared_ptr<SinglyRefItem<T>> temp = make_shared<SinglyRefItem<T>>(reference);
			tail->next = temp;
			tail = temp;
		}
	};

	shared_ptr<SinglyRefItem<T>> front()
	{
		return head;
	}

	shared_ptr<T> pop()
	{
		shared_ptr<T> node = nullptr;

		if (head)
		{
			node = head->reference.lock();

			if (head != tail)
				head = head->next;

			else
			{
				head = nullptr;
				tail = nullptr;
			}
		}

		return node;
	};

	bool isEmpty()
	{
		return head == nullptr;
	};

	int size()
	{
		if (!head)
			return 0;

		if (head == tail)
			return 1;

		int size = 1;
		shared_ptr<SinglyRefItem<T>> temp = head;

		while ((temp = temp->next) != nullptr)
			size++;

		return size;
	};

	bool contains(shared_ptr<T> reference)
	{
		shared_ptr<SinglyRefItem<T>> current = head;

		while (current)
		{
			if (current->reference == reference)
				break;

			current = current->next;
		}

		return (bool)current;
	}

	void clear()
	{
		head = nullptr;
		tail = nullptr;
	}
};

