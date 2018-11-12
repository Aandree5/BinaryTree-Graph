// Q1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BinaryTree.h"
#include <memory>
#include <fstream>
#include <iostream>
#include <string>

#if _WIN64
#define FILE "..\\..\\text.txt"
#else
#define FILE "..\\text.txt"
#endif

using namespace std;

int main()
{
	unique_ptr<BinaryTree> bTree = make_unique<BinaryTree>();
	
	ifstream file(FILE);
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

