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
#define white cout << "\033[1;37m"
#define grey cout << "\033[1;37m"
#endif // __linux__

enum Color
{
	C_RED,
	C_BLUE,
	C_GREEN,
	C_YELLOW,
	C_CYAN,
	C_WHITE,
	C_DEFAULT
};

namespace ConsoleHelpers
{


	bool static changeColour(Color colour)
	{
		switch (colour)
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

		default:
			grey;
			return false;
		}

		return true;
	}

	void static printC(std::string text, Color color)
	{
		bool needsReset = changeColour(color);
		
		std::cout << text.c_str();


		std::cout << std::flush;

		// Return color to default
		if (needsReset)
			grey;
	}
};
