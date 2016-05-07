#pragma once
#include "../ParticleEngine/Vector2.h"
#include "PE_Types.h"
#include <math.h>

namespace pe
{
	namespace integrator
	{
		const static float dampening = 0.99f;

		// Calculate Possible future Position
		static Vector2 Integrator(Vector2 &force, Particle* particle, float &deltatime)
		{
			Vector2 newPosition;
			Vector2 acceleration;
			Vector2 velocity;
			//UpdatePostion
			acceleration = force * particle->massfactor;
			newPosition = particle->pos + particle->velocity*deltatime + acceleration*(powf(deltatime,2.0f) * 0.5f);
			// Update Veloctiy
			velocity = particle->velocity*powf(dampening,deltatime) + acceleration * deltatime;
			particle->velocity = velocity;
			return  newPosition;
		}
	}
}
