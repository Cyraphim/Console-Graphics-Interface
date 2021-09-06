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
	}
}