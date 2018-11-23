// Coursework.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "BinaryTree.h"
#include "ConsoleHelpers.h"
#include "UnweightedGraph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <sstream>

using namespace std;

void Tree()
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
		cout << endl;
		tree.print();

		printTitle("Command");
		cout << endl << ">";
		cyan;
		cin >> input;
		grey;

		clearScreen();

		if (input[0] == '?')
			tree.find(input.substr(1, input.size() - 1));

		else if (input[0] == '!')
			tree.remove(input.substr(1, input.size() - 1));

		else if (input[0] == 'I')
			tree.printInOrder();

		else if (input[0] == 'P')
			tree.printPostOrder();

		else
			tree.insert(input);
	}
}

void Graph()
{
	UnweightedGraph graph = UnweightedGraph();

	shared_ptr<UnweightedGraphNode> a = graph.addNode(1);
	shared_ptr<UnweightedGraphNode> b = graph.addNode(3);
	shared_ptr<UnweightedGraphNode> c = graph.addNode(4);
	shared_ptr<UnweightedGraphNode> d = graph.addNode(5);
	shared_ptr<UnweightedGraphNode> g = graph.addNode(6);
	shared_ptr<UnweightedGraphNode> h = graph.addNode(75);
	shared_ptr<UnweightedGraphNode> j = graph.addNode(58);
	shared_ptr<UnweightedGraphNode> k = graph.addNode(8);
	shared_ptr<UnweightedGraphNode> n = graph.addNode(9);

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
		cout << endl;
		graph.print();


		printTitle("Command");
		cout << endl << ">";
		cyan;
		cin >> input;
		grey;

		char choice = input[0];

		if ((choice == '#' || choice == '$' || choice == '&') && isdigit(input[1]))
		{
			stringstream ss;
			size_t n1;
			size_t n2;

			ss << input.substr(1, input.size());
			ss >> n1;

			ss.str(string());
			ss.clear();

			grey;
			printTitle("Find shortest path (without weights)");
			cout << endl << "First node: ";
			printC(to_string(n1), C_CYAN);
			cout << endl << "Second node: ";
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

				printC(to_string(n2), C_CYAN);

				ss.str(string());
				ss.clear();


				grey;
				cout << endl << "Path weight: ";
				cyan;
				cin >> input;

				ss << input;
				ss >> w;

				clearScreen();

				graph.addEdge(n1, n2, w);
			}
		}
		
		else if (input[0] == '@')
		{
			clearScreen();
			graph.isConnected();
		}
		else if (input[0] == 'B')
		{
			clearScreen();
			graph.traversalBFS();
		}
		else if (input[0] == 'D')
		{
			clearScreen();
			graph.traversalDFS();
		}
		else if (isdigit(input[0]))
		{
			stringstream ss;
			size_t v1;

			ss << input;
			ss >> v1;

			clearScreen();

			graph.addNode(v1);
		}
		else
			clearScreen();


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
		Tree();
	else
		Graph();

	return 0;
}
