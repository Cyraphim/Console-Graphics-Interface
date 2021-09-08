#pragma once
#include "../cgi.h"
#include "graphics.h"

#include <string>
#include <vector>


namespace cgi
{
	namespace graphics
	{

		// Goes to the required position
		void GoToXY(int column, int line);
		// returns the character at the given position
		char GetFromXY(int x, int y);

		// Holds image data and is used to print to the screen
		class CSprite
		{
			private:
				size_t width;
				size_t height;
				std::vector<cgi::SColor> imageData;
			public:
				CSprite() = delete;
				CSprite(CSprite&) = delete;
				CSprite(std::string filepath);

				size_t GetHeight()
				{
					return this->height;
				}
				size_t GetWidth()
				{
					return this->width;
				}

				SColor GetPixel(size_t x, size_t y)
				{
					return imageData.at(width * y + x);
				}
		};

		// Draws the sprite at the given position
		void DrawImage(CSprite& sprite, size_t x, size_t y);

		// A double buffer used to draw onto the screen
		// We use a singleton structure here because it works better that way
        class CConsoleBuffer
        {
        private:
            static CConsoleBuffer* m_instance;

            std::vector<SColor> m_consoleBuffer;
            size_t m_screenWidth;
            size_t m_screenHeight;

        private:
            CConsoleBuffer();
            
        public:
			// Use this to get access to the console initializes when used
            static CConsoleBuffer* Instance()
            {
                if (m_instance == NULL)
                {
                    m_instance = new CConsoleBuffer();
                }
                return m_instance;
            }
			// Clears the console screen
			void ClearBuffer();

			// Shows what is on the buffer onto the console
            void SwapBuffer();

			// puts a pixel on the buffer at the position provided
            void PutPixel(SColor color, int x, int y)
            {
				auto pos = m_screenWidth * y + x;
				if(pos >= 0 && pos < m_consoleBuffer.size() - 1 && x >= 0)
					m_consoleBuffer[m_screenWidth * y + x] = color;
            }

			// Gets the color at the given position
			SColor GetPixel(int x, int y)
			{
				return this->m_consoleBuffer.at(y * m_screenWidth + x);
			}

			size_t GetWidth()
			{
				return m_screenWidth;
			}

			size_t GetHeight()
			{
				return m_screenHeight;
			}


        };
	}
}