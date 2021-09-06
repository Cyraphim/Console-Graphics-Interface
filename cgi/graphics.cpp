#include "graphics.h"

#include <Windows.h>
#include "../cgi.h"

namespace cgi
{

    void GoToXY(int column, int line)
    {
        COORD coord;
        coord.X = column;
        coord.Y = line;

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        if (!SetConsoleCursorPosition(hConsole, coord))
        {
            PrintText(EColor::RED, "ERROR: Could not set position\n Please Fix for coordinates: %d, %d", column, line);
        }
    }
}