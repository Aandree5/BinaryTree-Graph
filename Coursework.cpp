// Coursework.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "BinaryTree.h"
#include "ConsoleHelpers.h"
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <sstream>

using namespace std;

void manageTree()
{
	BinaryTree tree = BinaryTree();

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
				tree.insert(word);
				word = "";
			}
		}
	}

	file.close();

	tree.lastChanged = "";
	tree.tempMarked.clear();

	while (true)
	{
		string input;

		printTitle("Tree");
		printInfo("'# - Frequency of each word.");
		cout << endl;
		tree.print();

		printTitle("Command");
		printInfo("? - Find text in the tree.");
		printInfo("! - Remove text from the tree.");
		printInfo("I - Print tree in order.");
		printInfo("P - Print tree post order.");
		printInfo("[text] - Add a new node to the tree.");
		cout << endl;

		cout << "> ";
		cyan;
		cin >> input;
		grey;

		char choice = input[0];

		if (choice == '?' || choice == '!')
		{
			if (input[1])
				input = input.substr(1, input.size());

			else
			{
				grey;
				if (choice == '?')
					printTitle("Look for a text in the tree");

				else if (choice == '!')
					printTitle("Remove a text from the tree");

				cout << endl << "Text: ";

				cyan;
				cin >> input;
			}

			clearScreen();

			if (choice == '?')
				tree.find(input);

			else if (choice == '!')
				tree.remove(input);
		}
		else
		{
			clearScreen();

			if (choice == 'I')
				tree.printInOrder();

			else if (choice == 'P')
				tree.printPostOrder();

			else
				tree.insert(input);
		}
	}
}

void manageGraph()
{
	Graph graph = Graph();

	shared_ptr<GraphNode> a = graph.addNode(1);
	shared_ptr<GraphNode> b = graph.addNode(3);
	shared_ptr<GraphNode> c = graph.addNode(4);
	shared_ptr<GraphNode> d = graph.addNode(5);
	shared_ptr<GraphNode> g = graph.addNode(6);
	shared_ptr<GraphNode> h = graph.addNode(75);
	shared_ptr<GraphNode> j = graph.addNode(58);
	shared_ptr<GraphNode> k = graph.addNode(8);
	shared_ptr<GraphNode> n = graph.addNode(9);

	c->addEdge(a, 2);
	d->addEdge(c, 3);
	d->addEdge(a, 4);
	k->addEdge(j, 5);
	j->addEdge(h, 7);
	h->addEdge(g, 7);
	g->addEdge(d, 8);
	c->addEdge(b, 1);

	while (true)
	{
		string input;

		printTitle("Graph");
		printInfo("'# - Weight of each edge.");
		cout << endl;
		graph.print();

		printTitle("Command");
		printInfo("# - Find the smallest path between two nodes.");
		printInfo("$ - Find the least weight path between two nodes (Dijkstra).");
		printInfo("& - Create weighted edge between two nodes.");
		printInfo("@ - Check if the graph is connected.");
		printInfo("B - BFS traversal of the graph.");
		printInfo("D - DFS traversal of the graph.");
		printInfo("[digit] - Add a new node to the graph.");
		cout << endl;

		cout << "> ";
		cyan;
		cin >> input;
		grey;

		char choice = input[0];

		if (choice == '#' || choice == '$' || choice == '&')
		{
			stringstream ss;
			size_t n1;
			size_t n2;
			bool shouldPrint = true;

			input = input.substr(1, input.size());

			grey;
			if (choice == '#')
				printTitle("Find shortest path (without weights)");

			else if (choice == '$')
				printTitle("Find the least weighted path (Dijkstra)");

			else if (choice == '&')
				printTitle("Create edge between nodes.");

			cout << endl << "First node: ";

			if (!isdigit(input[0]))
			{
				cyan;
				cin >> input;
				grey;

				shouldPrint = false;
			}

			ss << input;
			ss >> n1;

			ss.str(string());
			ss.clear();

			if (shouldPrint)
			{
				printC(to_string(n1), C_CYAN);
				cout << endl;
			}

			cout << "Second node: ";
			cyan;
			cin >> input;

			ss << input;
			ss >> n2;


			if (choice == '#')
			{
				clearScreen();
				graph.isPath(n1, n2);
			}
			else if (choice == '$')
			{
				clearScreen();
				graph.dijkstraPath(n1, n2);
			}
			else if (choice == '&')
			{
				size_t w;
				int cursorPOSX;

				getCursorPosition(cursorPOSX);

				if (cursorPOSX != 0)
				{
					printC(to_string(n2), C_CYAN);
					cout << endl;
				}

				ss.str(string());
				ss.clear();


				grey;
				cout << "Path weight: ";
				cyan;
				cin >> input;

				ss << input;
				ss >> w;

				clearScreen();

				graph.addEdge(n1, n2, w);
			}
		}
		else
		{
			clearScreen(); 
			
			if (choice == '@')
				graph.isConnected();

			else if (choice == 'B')
				graph.traversalBFS();

			else if (choice  == 'D')
				graph.traversalDFS();

			else if (isdigit(input[0]))
			{
				stringstream ss;
				size_t v1;

				ss << input;
				ss >> v1;

				graph.addNode(v1);
			}
		}


		cin.clear();
		cin.ignore();

	}
}

int main()
{
	int input;
	
	printTitle("210CT Programming, Algorithms and Data Structures");
	cout << endl << endl;

	cout << "1. BinaryTree" << endl;
	cout << "2. Graph" << endl;
	cout << endl << "> ";

	cyan;
	cin >> input;
	grey;

	clearScreen();

	if (input == 1)
		manageTree();
	else
		manageGraph();

	return 0;
}
