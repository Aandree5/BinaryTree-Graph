#pragma once
#include "pch.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#include <stdlib.h>
#define clearScreen() system("cls")
#define red SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12)
#define blue SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9)
#define green SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10)
#define yellow SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14)
#define cyan SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11)
#define white SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15)
#define grey SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7)
#define brown SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6)
#define darkgrey SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8)
#define darkred SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4)
#define getCursorPosition(x) CONSOLE_SCREEN_BUFFER_INFO cbsi;GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi);x=cbsi.dwCursorPosition.X
#endif // _WIN32

#ifdef __linux__
#include <sstream>
#include <chrono>
#include <thread>
#define clearScreen() cout << "\033[2J\033[1;1H"
#define red cout << "\033[1;31m"
#define blue cout << "\033[1;34m"
#define green cout << "\033[1;32m"
#define yellow cout << "\033[1;33m"
#define cyan cout << "\033[1;36m"
#define white cout << "\033[1;97m"
#define grey cout << "\033[1;37m"
#define brown cout << "\033[1;91m"
#define darkgrey cout << "\033[1;90m"
#define darkred cout << "\033[0;31m"
#define getCursorPosition(x) x=0
#endif // __linux__

enum Color
{
	C_RED,
	C_BLUE,
	C_GREEN,
	C_YELLOW,
	C_CYAN,
	C_WHITE,
	C_BROWN,
	C_DARKGREY,
	C_DARKRED,
	C_DEFAULT
};

namespace ConsoleHelpers
{
	///<summary>Prints the given string to the console in the given color.</summary>
	///<remark>BigO notation for worst case is O(1).</remark>
	///<param name="text">Text to print to console.</param>
	///<param name="color">Color in wich to show the given text.</param>
	void static printC(std::string text, Color color)
	{
		bool reset = true;
		switch (color)
		{
		case C_BLUE:
			blue;
			break;

		case C_GREEN:
			green;
			break;

		case C_CYAN:
			cyan;
			break;

		case C_RED:
			red;
			break;

		case C_YELLOW:
			yellow;
			break;

		case C_WHITE:
			white;
			break;

		case C_BROWN:
			brown;
			break;

		case C_DARKGREY:
			darkgrey;
			break;

		case C_DARKRED:
			darkred;
			break;

		default:
			grey;
			reset = false;
		}

		std::cout << text.c_str() << std::flush;

		// Return color to default
		if (reset)
			grey;
	}

	///<summary>Prints the given text as a title.</summary>
	///<remark>BigO notation for worst case is O(1).</remark>
	///<param name="text">Text to print as a title.</param>
	void static printTitle(string title)
	{
		cout << endl;

		printC("</ ", C_RED);
		printC(title, C_WHITE);
		printC(" >", C_RED);

		cout << endl;
	}

	///<summary>Prints the given text as detailed information.</summary>
	///<remark>BigO notation for worst case is O(1).</remark>
	///<param name="text">Text to print as detailed information.</param>
	void static printInfo(string info)
	{
		printC("// " + info, C_DARKGREY);
		cout << endl;
	}
};
