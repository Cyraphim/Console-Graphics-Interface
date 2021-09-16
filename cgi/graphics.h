#pragma once
#include "../cgi.h"

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
				size_t m_width;
				size_t m_height;
				std::vector<cgi::SColor> m_imageData;
			public:
				CSprite() = delete;
				CSprite(CSprite&) = delete;
				CSprite(std::string filepath);

				~CSprite()
				{
					m_imageData.clear();
				}

				size_t GetHeight()
				{
					return this->m_height;
				}
				size_t GetWidth()
				{
					return this->m_width;
				}

				SColor GetPixel(size_t x, size_t y)
				{
					return m_imageData.at(m_width * y + x);
				}

				SColor GetPixel(SVec2 position)
				{
					return m_imageData.at(m_width * position.y + position.x);
				}
		};

		// Draws the sprite at the given position
		void DrawImage(CSprite& sprite, size_t x, size_t y);
		void DrawImage(CSprite& sprite, SVec2 position);

		// A double buffer used to draw onto the screen
		// We use a singleton structure here because it works better that way
        class CConsoleBuffer
        {
        private:
            static CConsoleBuffer* m_instance;

            std::vector<SColor> m_consoleBuffer;
            short const m_screenWidth = 128;
			short const m_screenHeight = 128;

			const char* m_drawChar;

        private:
            CConsoleBuffer();
            
        public:
			~CConsoleBuffer()
			{
				m_drawChar = NULL;
				m_instance = NULL;
				delete this;
			}

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
				if (pos >= 0 && pos < m_consoleBuffer.size() - 1 && x >= 0)
					m_consoleBuffer[m_screenWidth * y + x] = color;
			}

			void PutPixel(SColor color, SVec2 position)
			{
				auto pos = m_screenWidth * position.y + position.x;
				if (pos >= 0 && pos < m_consoleBuffer.size() - 1 && position.x >= 0)
					m_consoleBuffer[pos] = color;
			}

			// Gets the color at the given position
			SColor GetPixel(int x, int y)
			{
				return this->m_consoleBuffer.at(y * m_screenWidth + x);
			}

			// Gets the color at the given position
			SColor GetPixel(SVec2& position)
			{
				return this->m_consoleBuffer.at(position.y * m_screenWidth + position.x);
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