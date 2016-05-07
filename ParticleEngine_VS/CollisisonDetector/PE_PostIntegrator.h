#pragma once
#include "PE_Types.h"
#include "PE_Collision.h"

namespace pe
{
	namespace postIntegration
	{
		static bool CollissionSolver(Particle* particle, std::vector<Surface*> &surfaces, float deltatime)
		{
			bool collision = false;
			if (particle->forceGenKey & pe::Keys::COLLISION_REFLEXION)
			{
				collision = pe::collision::SurfaceCollissionSolver(particle, surfaces, deltatime);
			}
			return collision;
		}
		static bool EmitterUpdateTimer(Particle* particle, float deltatime)
		{
			Emitter* p = static_cast<Emitter*>(particle);
			p->currenttime += deltatime;
			if (p->currenttime > p->timer)
			{
				return true;
			}
			return false;
		}
		static void Emit(int index, std::vector<Particle*> &particles)
		{
			pe::Emitter* p = static_cast<pe::Emitter*>(particles[index]);
			float desiredForce = 100000.0f;
			particles.reserve(particles.size() + p->NumberOfParticles);
			for (unsigned int i = 0; i < p->NumberOfParticles; ++i)
			{
				pe::Particle* newp = new pe::Particle();
				newp->pos = p->pos;
				newp->velocity = p->velocity;
				newp->massfactor = p->massfactor;
				Vector2 f;
				f = Vector2(desiredForce, 0).rotate(Randomizer::GetRandom(0.0f,360.0f));
				newp->forceGenKey =
					pe::Keys::IMPULSE |
					pe::Keys::GRAVITY|
					pe::Keys::DRAG|
					pe::Keys::COLLISION_REFLEXION;
				newp->force = f;
				particles.push_back(newp);
			}
			std::swap(particles[index], particles[particles.size() - 1]);
			delete particles[particles.size() - 1];
			particles.resize(particles.size() - 1);
		}
	}
}