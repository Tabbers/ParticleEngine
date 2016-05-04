#pragma once
#include "Vector2.h"
#include "../CollisisonDetector/PE_Types.h"
#include <vector>

class Simulation
{
public:
	Simulation();
	~Simulation();

	//GETTER

	void Init(Vector2);
	void Update(float, Vector2);

private:
	Vector2 m_SimulationBounds;
	std::vector<PE::Particle*> particles;
};

