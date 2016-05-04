#include "Simulation.h"
#include "../CollisisonDetector/PE_Integrator.h"
#include "../CollisisonDetector/PE_ForceGenerator.h"

Simulation::Simulation()
{
}


Simulation::~Simulation()
{
	for (unsigned int i = 0; i < particles.size(); ++i)
	{
		delete particles[i];
	}
}

void Simulation::Init(Vector2 Simulationbounds)
{
	pe::EmitterParticle* emitter = new pe::EmitterParticle();
}

void Simulation::Update(float deltatime, Vector2 mousePos)
{
	Vector2 forcePerParticle;
	for (unsigned int i = 0; i < particles.size(); ++i)
	{
		forcePerParticle = pe::forceSolver::ApplyForces(particles[i]);
		pe::integrator::Integrator(forcePerParticle, particles[i], deltatime);
	}
}
