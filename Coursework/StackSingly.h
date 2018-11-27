#pragma once
#include <memory>
#include "SinglyItems.h"

using namespace std;

///<summary>Template for a stack of singly list items with pointer to objects of the given class.</summary>
///<typeparam name="T">Class of objects on which to keep a reference.</typeparam>
template<class T>
class StackSingly
{
	shared_ptr<SinglyItem<T>> stackTop;

public:
	///<summary>Creates a new empty stack.</summary>
	StackSingly()
	{
		stackTop = nullptr;
	};

	///<summary>Adds a reference to the given object to the stack.</summary>
	///<param name="reference">Pointer to an object to keep a reference of it.</param>
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

	///<summary>Gets the item on the top of the stack.</summary>
	///<returns>A pointer to the item on the top of the stack.</returns>
	shared_ptr<SinglyItem<T>> top()
	{
		return stackTop;
	}

	///<summary>Removes the top item from the stack and return the reference it's was keeping.</summary>
	///<returns>A pointer to the object referenced by the top item in the stack.</returns>
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

	///<summary>Checks if there's any items in the stack.</summary>
	///<returns>True if at least one item is found, false if not.</returns>
	bool isEmpty()
	{
		return stackTop == nullptr;
	};

	///<summary>Counts the number of items in the stack.</summary>
	///<returns>The number of items in the stack.</returns>
	int size()
	{
		int size = 0;

		if (stackTop)
		{
			shared_ptr<SinglyItem<T>> temp = stackTop;

			do
			{
				size++;
			} while (temp = temp->next);
		}

		return size;
	};

	///<summary>Check if the stack has the given reference.</summary>
	///<param name="reference">Pointer to the reference to search the stack.</param>
	///<returns>True if the reference was found, false otherwise.</returns>
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

	///<summary>Removes all the items from the stack.</summary>
	void clear()
	{
		stackTop = nullptr;
	}
};

