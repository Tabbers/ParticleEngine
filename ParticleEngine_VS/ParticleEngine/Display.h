#pragma once
#include "SFML\Graphics.hpp"
#include <string>

class Display
{
public:
	Display(sf::RenderWindow* window);
	~Display();
	
	void Init();
	void Render();

	inline  void SetFpsCounter(std::string fps) { this->fps.setString(fps); };

private:
	sf::RenderWindow* window;

	sf::Text fps;
	sf::Font font;
};

