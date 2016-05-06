#pragma once
#include "PE_Types.h"

namespace pe
{
	namespace forceSolver
	{
		const Vector2 gravity(0.0f, 9.81f);
		const float friction  = 0.99999f;
		const float preassure = 0.99999f;

		Vector2 GravitySolver(Particle* particle)
		{
			return gravity / particle->mass;
		}
		Vector2 DragSolver(Particle* particle, float friction, float pressure)
		{
			Vector2 force;
			float velLength = particle->velocity.Length();

			if (particle->velocity.x == 0 && particle->velocity.y == 0)
			{
				return force;
			}
			Vector2 velNormalized = particle->velocity.Normalize() * -1;
			float draglength = friction * velLength + preassure * powf(velLength, 2);
			velNormalized *= draglength;
			return velNormalized;
		}
		Vector2 ImpulseSolver(Particle* particle)
		{
			return (particle->f.direction*particle->f.amount) / particle->mass;
		}

		Vector2 ApplyForces(Particle* particle, std::vector<Surface*> &surfaces, float deltatime)
		{
			Vector2 finalforce;

			if (particle->forceGenKey & pe::Keys::GRAVITY)
			{
				finalforce += GravitySolver(particle);
			}
			if (particle->forceGenKey & pe::Keys::DRAG)
			{
				finalforce += DragSolver(particle,friction,preassure);
			}
			if(particle->forceGenKey & pe::Keys::IMPULSE)
			{
				particle->forceGenKey &= ~pe::Keys::IMPULSE;
				finalforce += ImpulseSolver(particle);
			}
			if (particle->forceGenKey & pe::Keys::DELAYEDIMPULSE)
			{
				pe::Emitter* p = reinterpret_cast<Emitter*>(particle);
				p->currenttime += deltatime;
				if (p->currenttime > p->timer)
				{
					p->forceGenKey &= ~pe::Keys::DELAYEDIMPULSE;
					return EMITNEW;
				}
			}
			return finalforce;
		}
	}
}