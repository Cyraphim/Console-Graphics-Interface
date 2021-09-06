#pragma once
#include "../cgi.h"

#include <string>
#include <vector>

namespace cgi
{
	namespace graphics
	{
		void GoToXY(int column, int line);
		char GetFromXY(int x, int y);

		class CSprite
		{
			private:
				int width;
				int height;
				std::vector<cgi::SColor> imageData;
			public:
				CSprite() = delete;
				CSprite(CSprite&) = delete;
				CSprite(std::string filepath);

				unsigned int GetHeight()
				{
					return this->height;
				}
				unsigned int GetWidth()
				{
					return this->width;
				}

				SColor GetPixel(int x, int y)
				{

						return imageData.at(width * y + x);

				}
		};

		void DrawImage(CSprite& sprite, int x, int y);
	}
}