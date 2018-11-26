#pragma once
#include <memory>
#include "SinglyItems.h"

using namespace std;

///<summary>Template for a list of singly list items with pointer to objects of the given class.</summary>
///<typeparam name="T">Class of objects on which to keep a reference.</typeparam>
template<class T>
class ListSingly
{
	shared_ptr<SinglyItem<T>> head;

public:
	///<summary>Creates a new empty list.</summary>
	ListSingly()
	{
		head = nullptr;
	};

	///<summary>Adds a reference to the given object to the list.</summary>
	///<param name="reference">Pointer to an object to keep a reference of it.</param>
	void push(shared_ptr<T> reference)
	{
		if (!head)
			head = make_shared<SinglyItem<T>>(reference);

		else
		{
			shared_ptr<SinglyItem<T>> temp = make_shared<SinglyItem<T>>(reference);
			temp->next = head;
			head = temp;
		}
	};

	///<summary>Gets the item on the front of the list.</summary>
	///<returns>A pointer to the item on the front of the list.</returns>
	shared_ptr<SinglyItem<T>> front()
	{
		return head;
	}

	///<summary>Removes the front item from the list and return the reference it's was keeping.</summary>
	///<returns>A pointer to the object referenced by the front item in the list.</returns>
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

	///<summary>Revoves the given item from anywhere in the list.</summary>
	///<param name="reference">Pointer to the reference to search the list.</param>
	///<returns>A pointer to the reference held by the removed item.</returns>
	shared_ptr<T> remove(shared_ptr<T> reference)
	{
		if (head->reference.lock() == reference)
			head = head->next;

		else
		{
			shared_ptr<SinglyItem<T>> current = head;

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

	///<summary>Checks if there's any items in the list.</summary>
	///<returns>True if at least one item is found, false if not.</returns>
	bool isEmpty()
	{
		return head == nullptr;
	};

	///<summary>Counts the number of items in the list.</summary>
	///<returns>The number of items in the list.</returns>
	int size()
	{
		int size = 0;

		if (head)
		{
			shared_ptr<SinglyItem<T>> temp = head;

			while (temp = temp->next)
				size++;
		}

		return size;
	};

	///<summary>Check if the list has the given reference.</summary>
	///<param name="reference">Pointer to the reference to search the list.</param>
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

	///<summary>Removes all the items from the list.</summary>
	void clear()
	{
		head = nullptr;
	}
};

