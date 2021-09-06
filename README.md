# Changes:
* Tanuj Shrivastava
	- (31/08/2021) [Basic I/O functionality]

# Contents:
* About
* How to use
* Future Plans
* Documentation

# About:
CGI (Console Graphics Interface) is a Windows only c++ library 
that allows for a wide array of features. The library has a 
wide variety of features to cover the redundancies between 
projects. 

If you come up with ideas/implementations to update here, be
sure to add your name to the credits using the same format 
before pushing :)

# How to use:
Setup should be simple enough, Just add this project to the
project that youre working on, then right click on your 
project and go to Add -> Reference -> Select CGI

Alternatively, you can build the library separately and then
move cgi.lib to the same directory as your solution

All functionality will be part of the cgi namespace so
that the code is more organized.

Dont forget to add the lib file next to the EXE if running
outside of visual studio.

# Future plans:

These are mostly ideas/suggestions, *might* get implemented:
* STL Helper functions (Shuffling, random selection, etc.)
* Game Class that draws asynchronously
* Console buffer with console sprites and graphics
* Simple Entity Component System for gameobjects

# Documenation:
    
## cgi.h Enumerations:
* EColor:
	- BLACK
	    - RED
	    - GREEN
	    - YELLOW
	    - BLUE
	    - MAGENTA
	    - CYAN
	    - WHITE

## cgi.h Functions:
* void ClearScreen():
    - Clears the Console Buffer

* char GetCharInput():
    - Gets the next keyboard input from the player without
    waiting for an Return keypress

*  template \<class T\> void GetInput(T& ref):
    - gets input via std::cin and puts it into ref

* void PrintText(EColor color, std::string format, ...):
    - Prints the text in a printf() style with the added 
    option to choose what color we want to print with.

* void NewLine()
    - Moves the cursor to the next line  

## cgi/Cards.h Ennumerations:
*ECardType:
    - CLUBS
    - SPADES
    - HEARTS
    - DIAMONDS

## cgi/Cards.h Classes:
* CCard:
	-Copy and Default Constructor Destoryed
	For safety, use CCard via pointers
    -private:
	- ECardType m_type
	- unsigned int m_number
    -public:
	- CCard(ECardType type, unsigned int number)
	- std::string GetNumberString()
	- unsigned int GetNumber()
	- std::string GetTypeString()
	- ECardType GetType()
	- void Draw(EColor color, int row)
	    - Draws one row of the card

## cgi/Cards.h Functions:
* void DrawCard(EColor color, CCard& card)
    - prints a full card on to the console

* template \<class SetHolder\>
 void DrawCards(EColor color, SetHolder& set)
    - prints a list of cards horizontally when provided
    with an iterable data structure (uses foreach loop)
