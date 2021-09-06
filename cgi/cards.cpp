#include "cards.h"
#include "../cgi.h"

namespace cgi
{
	namespace cards
	{
		CCard::CCard(ECardType type, unsigned int number)
			: m_type(type), m_number(number)
		{
		
		}
		std::string CCard::GetNumberString()
		{
			switch(this->m_number)
			{
			case 1:
				return "Ace";
			case 11:
				return "Jack";
			case 12:
				return "Queen";
			case 13:
				return "King";
			default:
				return std::to_string(this->m_number);
			}
		}
		unsigned int CCard::GetNumber()
		{
			return this->m_number;
		}
		std::string CCard::GetTypeString()
		{
			switch(this->m_type)
			{
				case ECardType::CLUBS:
					return "Clubs";
				case ECardType::HEARTS:
					return "Hearts";
				case ECardType::SPADES:
					return "Spades";
				case ECardType::DIAMONDS:
					return "Diamonds";
				default:
					return "\0";
			}
		}
		ECardType CCard::GetType()
		{
			return this->m_type;
		}

		void CCard::Draw(cgi::EColor color, int row)
		{
			//
			// ************
			// * Queen    *
			// *          *
			// *          *
			// *          *
			// * Diamonds *
			// *          *
			// *          *
			// *          *
			// *    Queen *       
			// ************
			//
			int padlen = 0;
			switch (row % 11)
			{
			case 0:
			case 10:
				cgi::PrintText(color, "************");
				break;
			case 1:
				cgi::PrintText(color, "* %-5s    *", this->GetNumberString().c_str());
				break;
			case 2:
			case 3:
			case 4:
			case 6:
			case 7:
			case 8:
				cgi::PrintText(color, "*          *");
				break;
			case 5:
				padlen = (5 - this->GetNumberString().length()) / 2;
				cgi::PrintText(color, "* %-8s *", this->GetTypeString().c_str());
				break;
			case 9:
				cgi::PrintText(color, "*    %5s *", this->GetNumberString().c_str());
				break;
			}
		
		}

		void DrawCard(EColor color, CCard& card)
		{
			for(int row = 0; row < 11; row++)
			{
				card.Draw(color, row);
				cgi::NewLine();
			}
		}
	}
}