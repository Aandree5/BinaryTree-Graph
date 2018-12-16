#pragma once
#include <memory>

using namespace std;

///<summary>Template for an item with a pointer to an object of the given class and a pointer to the next item of the list.</summary>
///<typeparam name="T">Class of objects on which to keep a reference.</typeparam>
template<class T>
struct SinglyItem
{
	shared_ptr<T> reference;
	shared_ptr<SinglyItem<T>> next;

	///<summary>Creates an item with a pointer to the given object.</summary>
	///<remark>BigO notation for worst case is O(1).</remark>
	///<param name="reference">Pointer to an object to keep a reference of it.</param>
	SinglyItem(shared_ptr<T> reference)
	{
		this->reference = reference;
		next = nullptr;
	};
};
