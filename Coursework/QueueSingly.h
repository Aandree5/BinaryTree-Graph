#pragma once
#include <memory>
#include "SinglyItem.h"

using namespace std;

///<summary>Template for a queue of singly list items with pointer to objects of the given class.</summary>
///<typeparam name="T">Class of objects on which to keep a reference.</typeparam>
template<class T>
class QueueSingly
{
	shared_ptr<SinglyItem<T>> head;
	shared_ptr<SinglyItem<T>> tail;

public:
	///<summary>Creates a new empty queue.</summary>
	///<remark>BigO notation for worst case is O(1).</remark>
	QueueSingly()
	{
		head = nullptr;
		tail = nullptr;
	};

	///<summary>Adds a reference to the given object to the back of the queue.</summary>
	///<remark>BigO notation for worst case is O(1).</remark>
	///<param name="reference">Pointer to an object to keep a reference of it.</param>
	void push_back(shared_ptr<T> reference)
	{
		if (!head)
		{
			head = make_shared<SinglyItem<T>>(reference);
			tail = head;
		}
		else
		{
			shared_ptr<SinglyItem<T>> temp = make_shared<SinglyItem<T>>(reference);
			tail->next = temp;
			tail = temp;
		}
	};

	///<summary>Gets the item ionn the front of the queue.</summary>
	///<remark>BigO notation for worst case is O(1).</remark>
	///<returns>A pointer to the item on the front of the queue.</returns>
	shared_ptr<SinglyItem<T>> front()
	{
		return head;
	}

	///<summary>Removes the front item from the queue and return the reference it's was keeping.</summary>
	///<remark>BigO notation for worst case is O(1).</remark>
	///<returns>A pointer to the object referenced by the front item in the queue.</returns>
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

	///<summary>Checks if there's any items in the queue.</summary>
	///<remark>BigO notation for worst case is O(1).</remark>
	///<returns>True if at least one item is found, false if not.</returns>
	bool isEmpty()
	{
		return head == nullptr;
	};

	///<summary>Counts the number of items in the queue.</summary>
	///<remark>BigO notation for worst case is O(n).</remark>
	///<returns>The number of items in the queue.</returns>
	int size()
	{
		if (!head)
			return 0;

		if (head == tail)
			return 1;

		int size = 1;
		shared_ptr<SinglyItem<T>> temp = head;

		do
		{
			size++;
		} while (temp = temp->next);

		return size;
	};

	///<summary>Check if the queue has the given reference.</summary>
	///<remark>BigO notation for worst case is O(n).</remark>
	///<param name="reference">Pointer to the reference to search the queue.</param>
	///<returns>True if the reference was found, false otherwise.</returns>
	bool contains(shared_ptr<T> reference)
	{
		shared_ptr<SinglyItem<T>> current = head;

		while (current)
		{
			if (current->reference == reference)
				break;

			current = current->next;
		}

		return (bool)current;
	}

	///<summary>Removes all the items from the queue.</summary>
	///<remark>BigO notation for worst case is O(1).</remark>
	void clear()
	{
		head = nullptr;
		tail = nullptr;
	}
};

