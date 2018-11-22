#pragma once
#include <memory>

using namespace std;

template<class T>
struct SinglyRefItem
{
	weak_ptr<T> reference;
	shared_ptr<SinglyRefItem<T>> next;

	SinglyRefItem(shared_ptr<T> reference)
	{
		this->reference = reference;
		next = nullptr;
	};
};
