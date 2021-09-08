#include "graphics.h"


#define NOMINMAX
#include <Windows.h>
#include "../cgi.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <thread>
#include <mutex>

namespace cgi
{
    namespace graphics
    {
        // Singleton init
        CConsoleBuffer* CConsoleBuffer::m_instance = NULL;

        void GoToXY(int x, int y)
        {
            static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
            std::cout.flush();
            COORD coord = { (SHORT)x, (SHORT)y };
            SetConsoleCursorPosition(hOut, coord);
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
            // As many threads as there are rows on the console
            std::vector<std::thread> threads;

            auto imgHeight = sprite.GetHeight();
            auto imgWidth = sprite.GetWidth();

            auto maxHeight = CConsoleBuffer::Instance()->GetHeight();
            auto maxWidth = CConsoleBuffer::Instance()->GetWidth();

            for(size_t imgY = 0; imgY < imgHeight && imgY < maxHeight; imgY++)
            {
                // if our row is negative then we dont need to draw it at all
                if(y + imgY >= 0)
                {
                    // Multithreading the actual placement
                    // NOTE: Would it be faster if the entire function was asynchronous?
                    auto xLoop = [ &sprite, &x, &y, &imgWidth, &maxWidth, imgY] ()
                    {
                        for(size_t imgX = 0; imgX < maxWidth && imgX < imgWidth; imgX++)
                        {
                            // If the pixel is black then why bother copying it at all
                            auto col = sprite.GetPixel(imgX, imgY);
                            if(col != SColor::BLACK)
                            {
                                CConsoleBuffer::Instance()->PutPixel(col, x + imgX, y + imgY);
                            }
                        }
                    };
                    // Add to our thread references
                    threads.push_back(std::thread(xLoop));
                }
            }

            // Wait for it all to end before ending the function
            for(auto& t : threads)
            {
                t.join();
            }
        }

        CSprite::CSprite(std::string filepath)
        {
                this->width = 0;
                this->height = 0;
                int channels;
                // Using STB to load image into memory regardless of extension
                unsigned char* data = stbi_load(filepath.c_str(), (int*)&this->width, (int*)&this->height, &channels, 3);

                for (int i = 0; i < this->width * this->height * 3; i += 3)
                {
                    imageData.push_back(SColor(data[i], data[i + 1], data[i + 2]));
                }
                stbi_image_free(data);           
        }

        CConsoleBuffer::CConsoleBuffer()
        {
            // Get the console width and height and create a buffer
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
            m_screenWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            m_screenHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

            m_consoleBuffer.insert(m_consoleBuffer.end(), m_screenWidth * m_screenHeight, SColor(0, 0, 0));
        }
        void CConsoleBuffer::ClearBuffer()
        {
            // Set everything to black
            for(auto& color: m_consoleBuffer)
            {
                color = SColor(0, 0, 0);
            }
        }

        void CConsoleBuffer::SwapBuffer()
        {
            // Clear the screen before drawing our new buffer
            cgi::ClearScreen();

            std::mutex mtx;
            std::vector<std::thread> threads;

            for (size_t imgY = 0; imgY < m_screenHeight; imgY++)
            {
                auto xLoop = [this, &mtx, imgY]()
                {
                    bool printRow = false;

                    SColor col = this->GetPixel(0, imgY);
                    std::string toPrint = col.toString();
                    SColor prevcol = col;

                    for (size_t imgX = 0; imgX < m_screenWidth; imgX++)
                    {
                        col = this->GetPixel(imgX, imgY);
                        if (col != SColor::BLACK)
                        {
                            if(col != prevcol)
                            {
                                toPrint.append(col.toString());
                                prevcol = col;
                            }
                            toPrint.append("#");
                            printRow = true;
                        }
                        else
                        {
                            toPrint.append(" ");
                        }
                    }

                    if(printRow)
                    {
                        mtx.lock();

                        GoToXY(0, imgY);
                        cgi::PrintText(toPrint.append("\033[0m").c_str());

                        mtx.unlock();
                    }
                };
                threads.push_back(std::thread(xLoop));
            }

            for (auto& t : threads)
            {
                t.join();
            }
        }
    }
}