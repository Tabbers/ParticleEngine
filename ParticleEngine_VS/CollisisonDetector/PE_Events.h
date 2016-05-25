#pragma once
#include "PE_Types.h"
#include "PE_Collision.h"

namespace pe
{
	namespace events
	{
		static bool EmitterUpdateTimer(Particle* particle, float deltatime)
		{
			Emitter* p = static_cast<Emitter*>(particle);
			p->currenttime -= deltatime;
			if (p->currenttime < 0)
			{
				return true;
			}
			return false;
		}
		static void Emit(int index, std::vector<Particle*> &particles)
		{
			pe::Emitter* p = static_cast<pe::Emitter*>(particles[index]);
			if (p->stage > 1)
			{
				particles.reserve(particles.size() + p->NumberOfParticles);
				for (unsigned int i = 0; i < p->NumberOfParticles; ++i)
				{
					float desiredForce = Randomizer::GetRandom(100.0f, 5000.0f);
					pe::Emitter* newp = new pe::Emitter();
					newp->pos = p->pos;
					newp->stage = p->stage - 1;
					newp->velocity = p->velocity;
					newp->massfactor = p->massfactor;
					newp->currenttime = 1.0f;
					newp->NumberOfParticles = 1000;
					Vector2 f;
					f = Vector2(desiredForce, 0).rotate(Randomizer::GetRandom(0.0f, 360.0f));
					newp->forceGenKey =
						pe::Keys::EMITTER |
						pe::Keys::WIND |
						pe::Keys::IMPULSE |
						pe::Keys::GRAVITY |
						pe::Keys::DRAG |
						pe::Keys::COLLISION_REFLEXION |
						pe::Keys::COLLISION_FRICTION;
					newp->force = f;
					particles.push_back(newp);
				}
			}
			else
			{
				particles.reserve(particles.size() + p->NumberOfParticles);
				for (unsigned int i = 0; i < p->NumberOfParticles; ++i)
				{
					float desiredForce = Randomizer::GetRandom(100.0f, 5000.0f);
					pe::Particle* newp = new pe::Particle();
					newp->pos = p->pos;
					newp->velocity = p->velocity;
					newp->massfactor = p->massfactor;
					Vector2 f;
					f = Vector2(desiredForce, 0).rotate(Randomizer::GetRandom(0.0f, 360.0f));
					newp->forceGenKey =
						pe::Keys::WIND |
						pe::Keys::IMPULSE |
						pe::Keys::GRAVITY |
						pe::Keys::DRAG |
						pe::Keys::COLLISION_REFLEXION |
						pe::Keys::COLLISION_FRICTION;
					newp->force = f;
					particles.push_back(newp);
				}
			}
			std::swap(particles[index], particles[particles.size() - 1]);
			delete particles[particles.size() - 1];
			particles.resize(particles.size() - 1);
		}
	}
}