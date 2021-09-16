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

            for (size_t imgY = 0; imgY < imgHeight && imgY < maxHeight; imgY++)
            {
                // if our row is negative then we dont need to draw it at all
                if (y + imgY >= 0)
                {
                    // Multithreading the actual placement
                    // NOTE: Would it be faster if the entire function was asynchronous?
                    auto xLoop = [&sprite, &x, &y, &imgWidth, &maxWidth, imgY]()
                    {
                        for (size_t imgX = 0; imgX < maxWidth && imgX < imgWidth; imgX++)
                        {
                            // If the pixel is black then why bother copying it at all
                            auto col = sprite.GetPixel(imgX, imgY);
                            if (col != SColor::BLACK)
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
            for (auto& t : threads)
            {
                t.join();
            }
        }

        void DrawImage(CSprite& sprite, SVec2 position)
        {
            DrawImage(sprite, (int) position.x, (int) position.y);
        }

        CSprite::CSprite(std::string filepath)
        {
            this->m_width = 0;
            this->m_height = 0;
            int channels;
            // Using STB to load image into memory regardless of extension
            unsigned char* data = stbi_load(filepath.c_str(), (int*)&this->m_width, (int*)&this->m_height, &channels, 3);

            for (int i = 0; i < this->m_width * this->m_height * 3; i += 3)
            {
                m_imageData.push_back(SColor(data[i], data[i + 1], data[i + 2]));
            }
            stbi_image_free(data);
        }

        CConsoleBuffer::CConsoleBuffer()
        {
            ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

            DWORD l_mode;
            HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
            GetConsoleMode(hStdout, &l_mode);
            SetConsoleMode(hStdout, l_mode |
                ENABLE_VIRTUAL_TERMINAL_PROCESSING |
                DISABLE_NEWLINE_AUTO_RETURN);

            SetConsoleOutputCP(65001);
            // Get the console width and height and create a buffer
            COORD size;
            SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), {m_screenWidth, m_screenHeight});

            m_consoleBuffer.insert(m_consoleBuffer.end(), m_screenWidth * m_screenHeight, SColor(0, 0, 0));

            m_drawChar = u8"█";
        }
        void CConsoleBuffer::ClearBuffer()
        {
            // Set everything to black
            for (auto& color : m_consoleBuffer)
            {
                color = SColor(0, 0, 0);
            }
        }

        void CConsoleBuffer::SwapBuffer()
        {
            //NOTE:
            // We currently use multithreading to append everything to a buffer string
            // Then we attach all these strings together to create a final buffer
            // and then we print that
            //
            // In a hypthothetical optimization I would try to get rid of the 
            // intermediate buffer and append directly

            std::vector<std::thread> threads;
            std::vector<std::string> buffer(m_screenHeight, "");
            for (size_t imgY = 0; imgY < m_screenHeight; imgY++)
            {
                auto xLoop = [&buffer, this, imgY]()
                {
                    SColor col = this->GetPixel(0, imgY);
                    buffer[imgY].append(col.toString());
                    SColor prevcol = col;

                    for (size_t imgX = 0; imgX < m_screenWidth; imgX++)
                    {
                        col = this->GetPixel(imgX, imgY);
                        if (col != SColor::BLACK)
                        {
                            if (col != prevcol)
                            {
                                buffer[imgY].append(col.toString());
                                prevcol = col;
                            }
                            buffer[imgY].append(m_drawChar);
                        }
                        else
                        {
                            buffer[imgY].push_back(' ');
                        }
                    }

                    buffer[imgY].append("\033[0m\n");

                };
                threads.push_back(std::thread(xLoop));
            }

            for (auto& t : threads)
            {
                t.join();
            }

            std::string finalBuffer = "";
            for (auto s : buffer)
                finalBuffer += s;
            GoToXY(0, 0);
            
            cgi::PrintText(finalBuffer.c_str());
        }
    }
}