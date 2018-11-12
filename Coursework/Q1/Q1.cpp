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
	string line;
	while (getline(file, line))
	{
		string word = "";
		for (size_t i = 0; i < line.size(); i++)
		{
			if (iswalpha(line[i]) || (line[i] == '-' && iswalpha(line[i + 1])))
				word += line[i];
			else if (word != "")
			{
				bTree.get()->insert(word);
				word = "";
			}
		}
	}

	file.close();

	bTree.get()->print();
	cin.get();

	bTree->remove("prog");

	bTree.get()->print();
	cin.get();

	bTree->remove("quiz");

	bTree.get()->print();
	cin.get();

	bTree->remove("fox");

	bTree.get()->print();
	cin.get();

	bTree.get()->find("wax");
	cin.get();

	bTree.reset();

	cin.get();
    return 0;
}

