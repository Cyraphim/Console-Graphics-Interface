#pragma once

#include <iostream>
#include <string>

namespace cgi
{
	// DEPRECATED, USE SColor INSTEAD
	enum class EColor
	{
		BLACK,
			RED,
			GREEN,
			YELLOW,
			BLUE,
			MAGENTA,
			CYAN,
			WHITE
	};

	// Color code for Console Outputenum class EColor
	struct SColor
	{
		unsigned int r = 0;
		unsigned int g = 0;
		unsigned int b = 0;

		SColor(unsigned int r, unsigned int g, unsigned int b):r(r), g(g), b(b){}
	};

	// Clears the Console Buffer
	void ClearScreen();

	// Gets the next keyboard input from the player without
	// waiting for an Return keypress
	char GetCharInput(); 

	// Get input using std::cin
	// If input is invalid, clear the input stream, warn the user, and try again
	//
	// Needed to declare it here and not in cpp
	// For some reason it couldn't find the body in cgi.cpp
	// Will try to figure this out later
	template<class Type>
	void GetInput(Type* ref)
	{
		std::cin >> *ref;

		while (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "INVALID VALUE ENTERED, PLEASE INPUT A/AN '" << typeid(Type).name() << "' VALUE ONLY\n";
			std::cin >> *ref;
		}
	}

	// Calls the Pause function as per the running OS
	void Pause();

	// Prints the text in a printf() style with the added
	// option to choose what color we want to print with.
	void PrintText(EColor color, const char* format, ...);
	void PrintText(SColor color, const char* format, ...);
	void PrintText(int r, int g, int b, const char* format, ...);

	// Moves the cursor to the next line
	void NewLine();
}