#pragma once
#include <memory>

using namespace std;

template<class T>
class QueueSingly
{
	shared_ptr<SinglyItem<T>> head;
	shared_ptr<SinglyItem<T>> tail;

public:
	QueueSingly()
	{
		head = nullptr;
		tail = nullptr;
	};

	void push_back(shared_ptr<T> item)
	{
		if (!head)
		{
			head = make_shared<SinglyItem<T>>(item);
			tail = head;
		}
		else
		{
			shared_ptr<SinglyItem<T>> temp = make_shared<SinglyItem<T>>(item);
			tail->next = temp;
			tail = temp;
		}
	};

	shared_ptr<SinglyItem<T>> front()
	{
		return head;
	}

	shared_ptr<T> pop()
	{
		shared_ptr<T> node = nullptr;

		if (head)
		{
			node = head->item;

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
		shared_ptr<SinglyItem<T>> temp = head;

		while ((temp = temp->next) != nullptr)
			size++;

		return size;
	};

	bool contains(shared_ptr<T> item)
	{
		shared_ptr<SinglyItem<T>> current = head;

		while (current)
		{
			if (current->item == item)
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

