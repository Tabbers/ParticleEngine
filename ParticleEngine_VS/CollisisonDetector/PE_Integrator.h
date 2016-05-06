#pragma once
#include "../ParticleEngine/Vector2.h"
#include "PE_Types.h"
#include <math.h>

namespace pe
{
	namespace integrator
	{
		const static float dampening = 0.9999f;

		// Calculate Possible future Position
		Vector2 Integrator(Vector2 &force, Particle* particle, float &deltatime)
		{
			Vector2 newPosition;
			Vector2 acceleration;
			Vector2 velocity;

			acceleration = force / particle->mass;
			velocity = particle->velocity*dampening + acceleration * deltatime;
			particle->velocity = velocity;
			return particle->pos + velocity;
		}
	}
}
