#pragma once
#include <memory>

using namespace std;

template<class T>
class ListSinglyRef
{
	shared_ptr<SinglyRefItem<T>> head;

public:
	ListSinglyRef()
	{
		head = nullptr;
	};

	void push(shared_ptr<T> reference)
	{
		if (!head)
			head = make_shared<SinglyRefItem<T>>(reference);

		else
		{
			shared_ptr<SinglyRefItem<T>> temp = make_shared<SinglyRefItem<T>>(reference);
			temp->next = head;
			head = temp;
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

			head = head->next;
		}

		return node;
	};

	shared_ptr<T> remove(shared_ptr<T> reference)
	{
		if (head->reference.lock() == reference)
			head = head->next;

		else
		{
			shared_ptr<SinglyRefItem<T>> current = head;

			while (current->next)
			{
				if (current->next->reference.lock() == reference)
					break;

				else
					current = current->next;
			}

			if (current->next->reference.lock() == reference)
				current->next = current->next->next;

			else
				return nullptr;
		}

		return reference;
	}

	bool isEmpty()
	{
		return head == nullptr;
	};

	int size()
	{
		int size = 0;

		if (head)
		{
			shared_ptr<SinglyRefItem<T>> temp = head;

			while ((temp = temp->next) != nullptr)
				size++;
		}

		return size;
	};

	bool contains(shared_ptr<T> reference)
	{
		shared_ptr<SinglyRefItem<T>> current = head;

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
		head = nullptr;
	}
};

