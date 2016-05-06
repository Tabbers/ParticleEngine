#pragma once
#include "SFML\Graphics.hpp"
#include <string>
#include "../CollisisonDetector/PE_Types.h"
class Display
{
public:
	Display(sf::RenderWindow* window);
	~Display();
	
	void Init();
	void Render();

	inline  void SetFpsCounter(std::string fps) { this->fps.setString(fps); };
	void CreateVertexArrays(std::vector<pe::Particle*> &particles, std::vector<pe::Surface*> &surfaces);
	void UpdateVertexArrays(std::vector<pe::Particle*> &particles);
private:
	sf::RenderWindow* window;
	sf::VertexArray lines;
	sf::VertexArray points;
	sf::Color particleColor;
	sf::Color lineColor;
	sf::Text fps;
	sf::Font font;
};

