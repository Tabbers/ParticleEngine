#include "Simulation.h"
#include "../CollisisonDetector/PE_Integrator.h"
#include "../CollisisonDetector/PE_ForceGenerator.h"
#include "../CollisisonDetector/PE_Collision.h"
#include "../CollisisonDetector/PE_PostIntegrator.h"
#include <iostream>

Simulation::Simulation()
{
	particles.reserve(10000000);
	surfaces.reserve(100);
}


Simulation::~Simulation()
{
	for (unsigned int i = 0; i < particles.size(); ++i)
	{
		delete particles[i];
	}
}

void Simulation::Init(Vector2 bounds)
{
	m_SimulationBounds = bounds;
	Vector2 offset(-30, 10);
	pe::Emitter* emitter = new pe::Emitter();
	emitter->pos = m_SimulationBounds - offset;
	emitter->forceGenKey =
		pe::Keys::EMITTER |
		pe::Keys::IMPULSE |
		pe::Keys::GRAVITY |
		pe::Keys::DRAG |
		pe::Keys::COLLISION_REFLEXION;
	emitter->massfactor = 1;
	emitter->currenttime= 0;
	emitter->timer = 2;
	emitter->NumberOfParticles = 500;
	
	Vector2 f;
	f = Vector2(5000.0f,0).rotate(-120.0f);
	
	emitter->force = f;

	//particles.push_back(emitter);

	pe::Surface* surfaceFloor = new pe::Surface();
	surfaceFloor->point1 = Vector2(0,bounds.y);
	surfaceFloor->point2 = Vector2(bounds.x, bounds.y);
	surfaceFloor->CalculateLeftNormal();

	surfaces.push_back(surfaceFloor);

	pe::Surface* surface1 = new pe::Surface();
	surface1->point1 = Vector2(20, 600);
	surface1->point2 = Vector2(200, 500);
	surface1->CalculateLeftNormal();
	surfaces.push_back(surface1);
	
	pe::Surface* surface2 = new pe::Surface();
	surface2->point1 = Vector2(200, 500);
	surface2->point2 = Vector2(380, 600);
	surface2->CalculateLeftNormal();
	surfaces.push_back(surface2);
}

void Simulation::Update(float deltatime, Vector2 mousePos)
{
	for (unsigned int i = 0; i < particles.size(); ++i)
	{
		if (particles[i]->forceGenKey & pe::Keys::EMITTER)
		{
			if (pe::postIntegration::EmitterUpdateTimer(particles[i], deltatime))
			{
				pe::postIntegration::Emit(i, particles);
			}
		}
	}
	for (unsigned int i = 0; i < particles.size(); ++i)
	{
		Vector2 forcePerParticle;
		forcePerParticle = pe::forceSolver::ApplyForces(particles[i]);
		std::cout << forcePerParticle.Length() << std::endl;
		Vector2 futurePosition = pe::integrator::Integrator(forcePerParticle, particles[i], deltatime);
		if (!pe::postIntegration::CollissionSolver(particles[i], surfaces, deltatime))
		{
			particles[i]->pos = futurePosition;
		}
	}


}


void Simulation::AddNewParticle(Vector2 mousePosition)
{
	for (unsigned int i = 0; i < 3; ++i)
	{
		pe::Emitter* p = new pe::Emitter();
		p->pos = mousePosition;
		p->forceGenKey =
			pe::Keys::EMITTER |
			pe::Keys::GRAVITY |
			pe::Keys::DRAG |
			pe::Keys::IMPULSE |
			pe::Keys::COLLISION_REFLEXION;
		p->massfactor = 1;
		p->currenttime = 0;
		p->timer = 1+i;
		p->NumberOfParticles = 100;

		Vector2 force;
		p->force = force;

		particles.push_back(p);
	}
}
