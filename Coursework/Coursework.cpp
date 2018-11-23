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

		printC("#> Tree", C_DARKGREY);
		cout << endl;
		tree.print();

		cout << endl;
		printC("#> Command", C_DARKGREY);
		cout << endl << ">";
		cyan;
		cin >> input;
		grey;

		clearScreen();

		if (input[0] == '?')
			tree.find(input.substr(1, input.size() - 1));

		else if (input[0] == '!')
			tree.remove(input.substr(1, input.size() - 1));

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

		printC("#> Graph", C_DARKGREY);
		cout << endl;
		graph.print();

		cout << endl;
		printC("#> Command", C_DARKGREY);
		cout << endl << ">";
		cyan;
		cin >> input;
		grey;

		if (input[0] == '#')
		{
			stringstream ss;
			size_t n1;
			size_t n2;

			ss << input.substr(1, input.size());
			ss >> n1;

			ss.str(string());
			ss.clear();

			grey;
			printC("</ ", C_BLUE); 
			printC("Find shortest path (without weights)", C_WHITE);
			printC(" >", C_BLUE);
			cout << endl << "First node: ";
			printC(to_string(n1), C_CYAN);
			cout << endl << "Second node: ";
			cyan;
			cin >> input;

			ss << input;
			ss >> n2;

			clearScreen();

			graph.isPath(n1, n2);
		}
		else if (input[0] == '&')
		{
			stringstream ss;
			size_t n1;
			size_t n2;
			size_t w;

			ss << input.substr(1, input.size());
			ss >> n1;

			ss.str(string());
			ss.clear();

			grey;
			printC("</ ", C_BLUE);
			printC("Add edge to nodes", C_WHITE);
			printC(" >", C_BLUE);
			cout << endl << "First node: ";
			printC(to_string(n1), C_CYAN);
			cout << endl << "Second node: ";
			cyan;
			cin >> input;

			ss << input;
			ss >> n2;

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
		else if (input[0] == '$')
		{
			stringstream ss;
			size_t n1;
			size_t n2;

			ss << input.substr(1, input.size());
			ss >> n1;

			ss.str(string());
			ss.clear();

			grey;
			printC("</ ", C_BLUE);
			printC("Find the lowest weight path", C_WHITE);
			printC(" >", C_BLUE);
			cout << endl << "First node: ";
			printC(to_string(n1), C_CYAN);
			cout << endl << "Second node: ";
			cyan;
			cin >> input;

			ss << input;
			ss >> n2;

			clearScreen();

			graph.dijkstraPath(n1, n2);
		}

		else if (isdigit(input[0]))
		{
			stringstream ss;
			int v1;

			ss << input;
			ss >> v1;

			clearScreen();

			graph.addNode(v1);
		}


		cin.clear();
		cin.ignore();

	}
}

int main()
{
	//Tree();
	Graph();

	return 0;
}
