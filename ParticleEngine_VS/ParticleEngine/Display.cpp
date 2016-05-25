#include "display.h"


Display::Display(sf::RenderWindow* window):window(window)
{
	font.loadFromFile("font/font.otf");
	fps.setFont(font);

	fps.setCharacterSize(24);
	fps.setPosition(20, 48);
	fps.setColor(sf::Color::White);

	lineColor = sf::Color::White;
	particleColor = sf::Color::Red;

	points.setPrimitiveType(sf::Points);
	lines.setPrimitiveType(sf::Lines);
}


Display::~Display()
{
}

void Display::Init()
{

}

void Display::Render()
{
	window->draw(lines);
	window->draw(points);
	window->draw(fps);
}

void Display::UpdateVertexArrays(std::vector<pe::Particle*> &particles)
{
	points.resize(particles.size());
	for (unsigned int i = 0; i < particles.size(); ++i)
	{
		points[i].color = particleColor;
		points[i].position = particles[i]->pos.toVector2f();
		points[i].color = particleColor;
	}
}

void Display::CreateVertexArrays(std::vector<pe::Particle*> &particles, std::vector<pe::Surface*> &surfaces)
{
	sf::Vertex vert;
	points.resize(particles.size());
	for (unsigned int i = 0; i < surfaces.size(); ++i)
	{
		vert.position = surfaces[i]->point1.toVector2f();
		vert.color = lineColor;
		lines.append(vert);

		vert.position = surfaces[i]->point2.toVector2f();
		vert.color = lineColor;
		lines.append(vert);
	}

	for (unsigned int i = 0; i < particles.size(); ++i)
	{
		vert.position = particles[i]->pos.toVector2f();
		vert.color = particleColor;
		points.append(vert);
	}

}
 
