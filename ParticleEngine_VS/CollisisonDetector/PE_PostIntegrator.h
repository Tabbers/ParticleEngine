#pragma once
#include "PE_Types.h"
#include "PE_Collision.h"

namespace pe
{
	namespace postIntegration
	{
		bool CollissionSolver(Particle* particle, std::vector<Surface*> &surfaces, float deltatime)
		{
			bool collision = false;
			if (particle->forceGenKey & pe::Keys::COLLISION_REFLEXION)
			{
				collision = pe::collision::SurfaceCollissionSolver(particle, surfaces, deltatime);
			}
			return collision;
		}
		void Emit(Particle* particle, std::vector<Particle*> &particles)
		{
			Emitter* p = reinterpret_cast<Emitter*>(particle);
			Particle* newp;
			Force f;
			for (unsigned int i = 0; i < p->NumberOfParticles; ++i)
			{
				newp = p;
				f.amount = Randomizer::GetRandom(0.0f, 100.0f);
				f.direction = Vector2(Randomizer::GetRandom(0.0f, 10.0f), Randomizer::GetRandom(0.0f, 10.0f));
				f.direction = f.direction.Normalize();
				newp->f = f;
				p->forceGenKey |= pe::Keys::IMPULSE;
			}
		}
	}
}