#include "CGI.h"

#include <iostream>

#if _WIN32
#include <Windows.h>
#include <conio.h>
#endif

namespace cgi
{
	void ClearScreen()
	{
		HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (GetConsoleScreenBufferInfo(hConsoleOutput, &csbi))
		{
			CHAR_INFO fi = { ' ', csbi.wAttributes };
			csbi.srWindow.Left = 0;
			csbi.srWindow.Top = 0;
			csbi.srWindow.Right = csbi.dwSize.X - 1;
			csbi.srWindow.Bottom = csbi.dwSize.Y - 1;
			ScrollConsoleScreenBufferW(hConsoleOutput, &csbi.srWindow, 0, csbi.dwSize, &fi);
		}
	}

	void Pause()
	{
		system("pause");
	}

	char GetCharInput()
	{
		return _getch();
	}

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

		std::printf("\x1b[38;2;%d;%d;%dm", color.r, color.g, color.b);

		// Get the variadic list and printf to allow formatting
		va_list argptr;
		va_start(argptr, format);
			std::vprintf(format, argptr);
		va_end(argptr);

		std::cout << "\033[0m";

	}

	void PrintText(int r, int g, int b, const char* format, ...)
	{
		std::printf("\x1b[38;2;%d;%d;%dm", r, g, b);
		// Get the variadic list and printf to allow formatting
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