#include "graphics.h"


#define NOMINMAX
#include <Windows.h>
#include "../cgi.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace cgi
{
    namespace graphics
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

        char GetFromXY(int x, int y)
        {
            GoToXY(x, y);
            CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            GetConsoleScreenBufferInfo(hConsole, &csbiInfo);
            COORD pos = csbiInfo.dwCursorPosition; //set pos to current cursor location
            TCHAR strFromConsole[1];    //need space to only one char
            DWORD dwChars;
            ReadConsoleOutputCharacter(
                hConsole,
                strFromConsole, // Buffer where store symbols
                1, // Read 1 char to strFormConsole
                pos, // Read from current cursor position
                &dwChars); // How many symbols stored
            return strFromConsole[0];
        }

        void DrawImage(CSprite& sprite, size_t x, size_t y)
        {
            for(size_t imgY = 0; imgY < sprite.GetHeight(); imgY++)
            {
                for(size_t imgX = 0; imgX < sprite.GetWidth(); imgX++)
                {
                    GoToXY(x + imgX, y + imgY);

                    auto col = sprite.GetPixel(imgX, imgY);
                    
                    if(col.r == 0 && col.g == 0 && col.b == 0)
                    {
                        // Dont do anything
                    }
                    else
                    {
                        cgi::PrintText(col, "#");
                    }
                }
                cgi::NewLine();
            }
        }

        CSprite::CSprite(std::string filepath)
        {
                this->width = 0;
                this->height = 0;
                int channels;
                unsigned char* data = stbi_load(filepath.c_str(), (int*)&this->width, (int*)&this->height, &channels, 3);

                for (int i = 0; i < this->width * this->height * 3; i += 3)
                {
                    imageData.push_back(SColor(data[i], data[i + 1], data[i + 2]));
                }
                

                stbi_image_free(data);
            
        }
    }
}