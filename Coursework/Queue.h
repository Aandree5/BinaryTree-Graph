#pragma once
#include <memory>

using namespace std;

template<class T>
struct QueueItem
{
	shared_ptr<T> reference;
	shared_ptr<QueueItem<T>> next;

	QueueItem(shared_ptr<T> reference)
	{
		this->reference = reference;
		next = nullptr;
	};
};

template<class T>
class Queue
{
	shared_ptr<QueueItem<T>> head;
	shared_ptr<QueueItem<T>> tail;

public:
	Queue()
	{
		head = nullptr;
		tail = nullptr;
	};

	void push_back(shared_ptr<T> reference)
	{
		if (!head)
		{
			head = make_shared<QueueItem<T>>(reference);
			tail = head;
		}
		else
		{
			shared_ptr<QueueItem<T>> temp = make_shared<QueueItem<T>>(reference);
			tail->next = temp;
			tail = temp;
		}
	};

	shared_ptr<QueueItem<T>> front()
	{
		return head;
	}

	shared_ptr<T> pop()
	{
		shared_ptr<T> node = nullptr;

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
		shared_ptr<QueueItem<T>> temp = head;

		while ((temp = temp->next) != nullptr)
			size++;

		return size;
	};
};

