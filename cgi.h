#pragma once

#include <iostream>
#include <string>
#include <sstream>

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

		static SColor const BLACK;
		unsigned int r = 0;
		unsigned int g = 0;
		unsigned int b = 0;

		SColor(unsigned int r = 0, unsigned int g = 0, unsigned int b = 0):r(r), g(g), b(b){}

		bool operator==(SColor const &other)
		{
			return (this->r == other.r && this->g == other.g && this->b == other.b);
		}

		bool operator!=(SColor const& other)
		{
			return (this->r != other.r || this->g != other.g || this->b != other.b);
		}

		// Convert a value to string
		std::string toString()
		{
			std::ostringstream strout;
			strout << "\x1b[38;2;" << r << ";" << g << ";" << b << "m";
			return strout.str();
		}
	}; 

	struct SVec2
	{
		double x;
		double y;

		SVec2(double x = 0, double y = 0) : x(x), y(y) {}
		SVec2(int x, int y) : x(x), y(y) {}

		bool operator==(SVec2 const& other)
		{
			return (this->x == other.x && this->y == other.y);
		}

		bool operator!=(SVec2 const& other)
		{
			return (this->x != other.x || this->y != other.y);
		}

		SVec2 operator-(SVec2 const& other)
		{
			return SVec2(this->x - other.x, this->y - other.y);
		}

		SVec2 operator+(SVec2 const& other)
		{
			return SVec2(this->x + other.x, this->y + other.y);
		}

		SVec2 operator*(int const& other)
		{
			return SVec2(this->x + other, this->y + other);
		}

		SVec2 operator+=(SVec2 const& other)
		{
			return SVec2(this->x += other.x, this->y += other.y);
		}

		SVec2 operator-=(SVec2 const& other)
		{
			return SVec2(this->x -= other.x, this->y -= other.y);
		}

		double Magnitude()
		{
			return std::sqrt(x * x + y * y);
		}

		double Distance(SVec2 const& other)
		{
			return (*this - other).Magnitude();
		}
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

	void PutChar(SColor color, char c);
	// Prints the text in a printf() style with the added
	// option to choose what color we want to print with.
	void PrintText(const char* format, ...);
	void PrintText(EColor color, const char* format, ...);
	void PrintText(SColor color, const char* format, ...);
	void PrintText(int r, int g, int b, const char* format, ...);

	// Moves the cursor to the next line
	void NewLine();

	template <class T>
	void Increment(T& value, T min, T max)
	{
		value++;
		max++;
		value = (int) value % max;
	}

	template <class T>
	void Decrement(T& value, T min, T max)
	{
		value--;
		max++;
		// % loops around for positive change
		// this formula loops around for both positive and negative values
		value = (((int)value - min) % (max - min) + max - min) % (max - min) + min;
	}
}