#include "CGI.h"

#include <iostream>

#if _WIN32
#include <Windows.h>
#include <conio.h>
#endif

namespace cgi
{

	SColor const SColor::BLACK;
	SColor const SColor::WHITE(255, 255, 255);
	SColor const SColor::RED(255, 0, 0);
	SColor const SColor::BLUE(0, 0, 255);
	SColor const SColor::GREEN(0, 255, 0);
	SColor const SColor::YELLOW(255, 255, 0);
	SColor const SColor::TEAL(0, 255, 255);
	SColor const SColor::PURPLE(255, 0, 255);
	void ClearScreen()
	{
		// Get the Win32 handle representing standard output.
// This generally only has to be done once, so we make it static.
		static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		COORD topLeft = { 0, 0 };

		// std::cout uses a buffer to batch writes to the underlying console.
		// We need to flush that to the console because we're circumventing
		// std::cout entirely; after we clear the console, we don't want
		// stale buffered text to randomly be written out.
		std::cout.flush();

		// Figure out the current width and height of the console window
		if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
			// TODO: Handle failure!
			abort();
		}
		DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

		DWORD written;

		// Flood-fill the console with spaces to clear it
		FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

		// Reset the attributes of every character to the default.
		// This clears all background colour formatting, if any.
		FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

		// Move the cursor back to the top left for the next sequence of writes
		SetConsoleCursorPosition(hOut, topLeft);
	}

	void Pause()
	{
		system("pause");
	}

	char GetCharInput()
	{
		return _getch();
	}

	char GetAsyncCharInput()
	{
		if(_kbhit())
		{
			return _getch();
		}
		return -1;
	}

	void PrintText(const char* format, ...)
	{
		// Get the variadic list and printf to allow formatting
		va_list argptr;
		va_start(argptr, format);
			std::vprintf(format, argptr);
		va_end(argptr);
	}

	void PutChar(SColor color, char c)
	{
		std::printf("\x1b[38;2;%d;%d;%dm", color.r, color.g, color.b);
		std::putchar(c);
		std::cout << "\033[0m";
	}

	// DEPRECATED
	// Variadic functions yayyy
	void PrintText(EColor color, const char* format, ...)
	{
		// Print the formatting for the color
		// Not sure if it works on other OS
		switch (color)
		{
		case EColor::RED:
			std::cout << "\x1b[91m";
			break;
		case EColor::GREEN:
			std::cout << "\x1b[92m";
			break;
		case EColor::YELLOW:
			std::cout << "\x1b[93m";
			break;
		case EColor::BLUE:
			std::cout << "\x1b[94m";
			break;
		case EColor::MAGENTA:
			std::cout << "\x1b[95m";
			break;
		case EColor::CYAN:
			std::cout << "\x1b[96m";
			break;
		case EColor::WHITE:
			std::cout << "\x1b[97m";
			break;
		default:
			// Print black by default
			std::cout << "\x1b[30m";
			break;
		}

		// Get the variadic list and printf to allow formatting
		va_list argptr;
		va_start(argptr, format);
			std::vprintf(format, argptr);
		va_end(argptr);

		// Switch color back to white lest we forget
		std::cout << "\033[0m";
	}

	void PrintText(SColor color, const char* format, ...)
	{
		// Changes the console color
		std::printf("\x1b[38;2;%d;%d;%dm", color.r, color.g, color.b);

		va_list argptr;
		va_start(argptr, format);
			std::vprintf(format, argptr);
		va_end(argptr);

		std::cout << "\033[0m";

	}

	void PrintText(int r, int g, int b, const char* format, ...)
	{
		// Changes the console color
		std::printf("\x1b[38;2;%d;%d;%dm", r, g, b);
		va_list argptr;
		va_start(argptr, format);
			std::vprintf(format, argptr);
		va_end(argptr);

		std::cout << "\033[0m";
	}

	void NewLine()
	{
		std::cout << "\n";
	}
}