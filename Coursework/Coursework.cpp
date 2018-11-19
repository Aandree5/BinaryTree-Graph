// Coursework.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "BinaryTree.h"
#include "ConsoleHelpers.h"
#include <iostream>
#include <fstream>
#include <string>
#include <memory>

using namespace std;

int main()
{
	unique_ptr<BinaryTree> bTree = make_unique<BinaryTree>();

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

	bTree->lastChanged = "";
	bTree->tempMarked.clear();

	while (true)
	{

		bTree->print();

		string input;

		cout << ">";

		cin >> input;

		clearScreen();

		if (input[0] == '?')
			bTree->find(input.substr(1, input.size() - 1));

		else if (input[0] == '!')
			bTree->remove(input.substr(1, input.size() - 1));

		else
			bTree->insert(input);
	}

	return 0;
}
