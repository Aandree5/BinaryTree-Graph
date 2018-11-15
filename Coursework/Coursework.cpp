// Coursework.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "BinaryTree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <memory>

using namespace std;

int main()
{
	unique_ptr<BinaryTree> bTree = make_unique<BinaryTree>();

	// TODO: Fail when file not found
	ifstream file("text.txt");

	if (!file.is_open())
		throw runtime_error("File not found!");

	string line;
	while (getline(file, line))
	{
		string word = "";
		for (unsigned i = 0; i < line.size(); i++)
		{
			if (iswalpha(line[i]) || (line[i] == '-' && iswalpha(line[i + 1])))
				word += line[i];
			else if (word != "")
			{
				bTree->insert(word);
				word = "";
			}
		}
	}

	file.close();

	bTree->print();
	cin.get();

	bTree->remove("prog");

	bTree->print();
	cin.get();

	bTree->remove("quiz");

	bTree->print();
	cin.get();

	bTree->remove("fox");

	bTree->print();
	cin.get();

	bTree->find("wax");
	cin.get();

	bTree.reset();

	cin.get();
	return 0;
}

