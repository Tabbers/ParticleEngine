#include "display.h"


Display::Display(sf::RenderWindow* window):window(window)
{
	font.loadFromFile("font/font.otf");
	fps.setFont(font);

	fps.setCharacterSize(24);
	fps.setPosition(20, 48);
	fps.setColor(sf::Color::White);
}


Display::~Display()
{
}

void Display::Init()
{

}

void Display::Render()
{
	window->draw(fps);
}
 
