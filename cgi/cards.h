#pragma once

#include <string>
#include "../cgi.h"

namespace cgi
{
	namespace cards
	{
		enum class ECardType
		{
			CLUBS,
			SPADES,
			HEARTS,
			DIAMONDS
		};

		// All possible cardtypes
		// Used for iterating
		static const ECardType AllCardTypes[] = 
		{
			ECardType::CLUBS, 
			ECardType::SPADES, 
			ECardType::HEARTS, 
			ECardType::DIAMONDS
		};

		// Copy and Default Constructor Destoryed 
		// For safety, use CCard via pointers
		class CCard
		{
			private:
				ECardType m_type;
				unsigned int m_number;
			public:
				CCard() = delete;
				CCard(CCard&) = delete;
				CCard(ECardType type, unsigned int number);

				std::string GetNumberString();
				unsigned int GetNumber();

				std::string GetTypeString();
				ECardType GetType();

				// Draws one row of the card
				void Draw(cgi::EColor color, int row);
		};

		// prints a full card on to the console
		void DrawCard(EColor color, CCard& card);


		// prints a list of cards horizontally when provided
		// with an iterable data structure(uses foreach loop)
		template <class SetHolder>
		void DrawCards(EColor color, SetHolder& set)
		{
			for (int row = 0; row < 11; row++)
			{
				for (auto card : set)
				{
					card->Draw(color, row);
					cgi::PrintText(EColor::BLACK, "  ");
				}
				cgi::NewLine();
			}
		}
	}
}