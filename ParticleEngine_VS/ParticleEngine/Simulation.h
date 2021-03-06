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

	inline std::vector<pe::Particle*> GetParticles() { return particles; }
	inline std::vector<pe::Surface*> GetSurfaces() { return surfaces; }

	void AddNewParticle(Vector2);
	void EmitteFromMouse(Vector2 mousePosition);
private:
	Vector2 m_SimulationBounds;
	std::vector<pe::Particle*> particles;
	std::vector<pe::Surface*> surfaces;
	std::vector<pe::CollisionData*> collisions;
};

