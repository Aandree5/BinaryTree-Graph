#pragma once
#include <memory>

using namespace std;

template<class T>
struct SinglyItem
{
	shared_ptr<T> reference;
	shared_ptr<SinglyItem<T>> next;

	SinglyItem(shared_ptr<T> reference)
	{
		this->reference = reference;
		next = nullptr;
	};
};
