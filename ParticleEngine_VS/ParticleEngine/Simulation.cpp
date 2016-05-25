#include "Simulation.h"
#include "../CollisisonDetector/PE_Integrator.h"
#include "../CollisisonDetector/PE_ForceGenerator.h"
#include "../CollisisonDetector/PE_Collision.h"
#include "../CollisisonDetector/PE_Events.h"
#include <iostream>

Simulation::Simulation()
{
	particles.reserve(10000000);
	collisions.reserve(particles.capacity());
	surfaces.reserve(100);
}


Simulation::~Simulation()
{
	for (unsigned int i = 0; i < particles.size(); ++i)
	{
		delete particles[i];
	}
	for (unsigned int i = 0; i < surfaces.size(); ++i)
	{
		delete surfaces[i];
	}
	for (unsigned int i = 0; i < collisions.size(); ++i)
	{
		delete collisions[i];
	}
}

void Simulation::Init(Vector2 bounds)
{
	m_SimulationBounds = bounds;

	pe::Surface* surfaceFloor = new pe::Surface();
	surfaceFloor->point1 = Vector2(0,bounds.y-10);
	surfaceFloor->point2 = Vector2(bounds.x, bounds.y-10);
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

	pe::Surface* surface3 = new pe::Surface();
	surface3->point1 = Vector2(300, 400);
	surface3->point2 = Vector2(500, 250);
	surface3->CalculateLeftNormal();
	surfaces.push_back(surface3);

	pe::Surface* surface4 = new pe::Surface();
	surface4->point1 = Vector2(500, 250);
	surface4->point2 = Vector2(600, 400);
	surface4->CalculateLeftNormal();
	surfaces.push_back(surface4);

	pe::Surface* surface5 = new pe::Surface();
	surface5->point1 = Vector2(20, 200);
	surface5->point2 = Vector2(200, 210);
	surface5->CalculateLeftNormal();
	surfaces.push_back(surface5);

}

void Simulation::Update(float deltatime, Vector2 mousePos)
{
	for (unsigned int i = 0; i < particles.size(); ++i)
	{
		if (particles[i]->forceGenKey & pe::Keys::EMITTER)
		{
			if (pe::events::EmitterUpdateTimer(particles[i], deltatime))
			{
				pe::events::Emit(i, particles);
			}
		}
	}
	for (unsigned int i = 0; i < particles.size(); ++i)
	{
		if (particles[i]->active)
		{
			Vector2 forcePerParticle;
			Vector2 futurepos = particles[i]->pos;
			forcePerParticle = pe::forceSolver::ForceSolver(particles[i], deltatime);
			futurepos = pe::integrator::Integrator(forcePerParticle, particles[i], deltatime);
			pe::collision::CollissionSolver(particles[i], surfaces, futurepos, deltatime);
		}
	}
}


void Simulation::AddNewParticle(Vector2 mousePosition)
{
	for (unsigned int i = 0; i < 1; ++i)
	{
		pe::Particle* p = new pe::Particle();
		p->pos = mousePosition;
		p->forceGenKey =
			pe::Keys::GRAVITY |
			pe::Keys::WIND |
			pe::Keys::DRAG |
			pe::Keys::COLLISION_REFLEXION |
			pe::Keys::COLLISION_FRICTION;
		p->massfactor = 1;

		Vector2 force;
		p->force = force;

		particles.push_back(p);
	}
}

void Simulation::EmitteFromMouse(Vector2 mousePosition)
{
	Vector2 offset(-30, 10);
	pe::Emitter* emitter = new pe::Emitter();
	emitter->pos = mousePosition;
	emitter->forceGenKey =
		pe::Keys::EMITTER |
		pe::Keys::WIND |
		pe::Keys::IMPULSE |
		pe::Keys::GRAVITY |
		pe::Keys::DRAG |
		pe::Keys::COLLISION_REFLEXION |
		pe::Keys::COLLISION_FRICTION;
	emitter->massfactor = 1;
	emitter->currenttime =0.5;
	emitter->NumberOfParticles = 5;
	emitter->stage = 2;
	Vector2 f;
	f = Vector2(10000.0f, 0).rotate(-120.0f);

	emitter->force = f;

	particles.push_back(emitter);
}
