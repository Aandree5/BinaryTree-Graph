// Q1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BinaryTree.h"
#include <memory>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	unique_ptr<BinaryTree> bTree = make_unique<BinaryTree>();

	ifstream file("..\\text.txt");
	string charsToRemove = " ,./\<>(){}*-"
	// REMOVE PUNCTUATION FROM WORDS, PREFERABLY WITHOUT THREE LOOPS!
	string line;
	while (getline(file, line))
	{
		int pos = 0;
		while ((pos = line.find(" ")) != string::npos) {
			string word = line.substr(0, pos);

			cout << line.substr(0, pos) << endl;
			line.erase(0, pos + 1);
		}
	}


	file.close();


	bTree.get()->insert("bz");
	bTree.get()->insert("hi");
	bTree.get()->insert("ai");
	bTree.get()->insert("sdasdasd");
	bTree.get()->insert("by");
	bTree.get()->insert("ba");

	bTree.get()->printInOrder();
	cin.get();

	bTree.reset();

	cin.get();
    return 0;
}

