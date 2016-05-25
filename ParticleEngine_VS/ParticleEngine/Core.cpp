#include "Core.h"
#include "Display.h"
#include "Simulation.h"
#include <iostream>
#include <string.h>

Core::Core()
{
}


Core::~Core()
{
}

void Core::Init()
{
	context.antialiasingLevel = 0;
	window = new sf::RenderWindow(sf::VideoMode(700, 700), "Collision Detection", sf::Style::Default, context);
	window->setFramerateLimit(60u);

	Vector2 windowsize;
	windowsize.x = window->getSize().x;
	windowsize.y = window->getSize().y;

	sim = new Simulation();
	sim->Init(windowsize);

	disp = new Display(window);
	disp->Init();
	disp->CreateVertexArrays(sim->GetParticles(), sim->GetSurfaces());
	srand(std::time(0));
}

void Core::Run()
{

	bool step = false;
	bool add = false;
	float zoomlevel = 1;

	sf::Vector2i position;
	sf::Time delta;

	Vector2 mousePosition;
	delta = clock.restart();
	bool firstFrame = true;
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window->close();
			if (event.type == sf::Event::KeyPressed)
			{
				
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{

				position = sf::Mouse::getPosition(*window);
				mousePosition.x = window->mapPixelToCoords(position).x;
				mousePosition.y = window->mapPixelToCoords(position).y;
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					sim->AddNewParticle(mousePosition);
				}
				else if (event.mouseButton.button == sf::Mouse::Left)
				{
					sim->EmitteFromMouse(mousePosition);
				}
			}
			
		}

		window->clear(sf::Color(40,40,40,255));
		
		if (!firstFrame)
		{
			sim->Update(delta.asSeconds(), mousePosition);
		}

		disp->UpdateVertexArrays(sim->GetParticles());
		disp->SetFpsCounter(std::to_string(delta.asSeconds()));
		disp->Render();
		step = false;
		firstFrame = false;
		window->display();
		delta = clock.restart();
	}
}
