// Q1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BinaryTree.h"

int main()
{
	unique_ptr<BinaryTree> bTree = make_unique<BinaryTree>();

	string a;
	cin >> a;

	bTree.reset();

	cin >> a;

    return 0;
}

