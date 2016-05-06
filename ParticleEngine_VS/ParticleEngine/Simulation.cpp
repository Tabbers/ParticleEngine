#include "Simulation.h"
#include "../CollisisonDetector/PE_Integrator.h"
#include "../CollisisonDetector/PE_ForceGenerator.h"
#include "../CollisisonDetector/PE_Collision.h"
#include "../CollisisonDetector/PE_PostIntegrator.h"

Simulation::Simulation()
{
	particles.reserve(1000000);
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
	Vector2 offset(-30, 0);
	pe::Emitter* emitter = new pe::Emitter();
	emitter->pos = m_SimulationBounds - offset;
	emitter->forceGenKey =
		pe::Keys::DELAYEDIMPULSE |
		pe::Keys::IMPULSE |
		pe::Keys::GRAVITY |
		pe::Keys::DRAG;
	emitter->mass = 1;
	emitter->currenttime= 0;
	emitter->timer = 2;
	emitter->NumberOfParticles = 500;
	
	pe::Force f;
	f.amount = 70;
	f.direction= Vector2(1,0).rotate(-100);
	
	emitter->f = f;

	particles.push_back(emitter);

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
	Vector2 forcePerParticle;
	for (unsigned int i = 0; i < particles.size(); ++i)
	{
		forcePerParticle = pe::forceSolver::ApplyForces(particles[i], surfaces,deltatime);
		Vector2 futurePosition = pe::integrator::Integrator(forcePerParticle, particles[i], deltatime);
		if (forcePerParticle == pe::EMITNEW)
		{
			pe::postIntegration::Emit(particles[i],particles);
		}
		if (!pe::postIntegration::CollissionSolver(particles[i], surfaces, deltatime))
		{
			particles[i]->pos = futurePosition;
		}
	}
}

void Simulation::AddNewParticle(Vector2 mousePosition)
{
	pe::Particle* p = new pe::Particle();
	p->pos = mousePosition;
	p->forceGenKey =
		pe::Keys::GRAVITY |
		pe::Keys::DRAG |
		pe::Keys::IMPULSE;
	p->mass = 1;

	pe::Force f;
	f.amount = 1000;
	f.direction = Vector2(0.5, -0.5);

	p->f = f;

	particles.push_back(p);
}
