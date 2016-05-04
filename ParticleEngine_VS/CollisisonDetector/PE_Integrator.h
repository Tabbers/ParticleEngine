#pragma once
#include "../ParticleEngine/Vector2.h"
#include "PE_Types.h"
#include <math.h>

namespace pe
{
	namespace integrator
	{
		const static float dampening = 0.99f;

		void Integrator(Vector2 &force, Particle* particle, float &deltatime)
		{
			Vector2 newPosition;
			Vector2 acceleration;
			Vector2 velocity;

			acceleration = force / particle->mass;
			velocity = particle->velocity*powf(dampening, deltatime) + acceleration * deltatime;

			newPosition = particle->pos + velocity*deltatime;
			particle->pos = newPosition;
		}
	}
}
