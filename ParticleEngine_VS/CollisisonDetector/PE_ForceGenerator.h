#pragma once
#include "PE_Types.h"

namespace pe
{
	namespace forceSolver
	{
		Vector2 gravity(0.0f, 9.81f);

		Vector2 ApplyForces(Particle* particle)
		{
			Vector2 force;

			if (particle->forceGenKey & pe::Keys::GRAVITY)
			{

			}
			if (particle->forceGenKey & pe::Keys::DRAG)
			{

			}
			if (particle->forceGenKey & pe::Keys::ELASTIC)
			{

			}

			return force;
		}

		Vector2 GravitySolver(Particle* particle)
		{
			return gravity * particle->mass;
		}
		Vector2 DragSolver(Particle* particle)
		{
			return gravity * particle->mass;
		}
		Vector2 ElasticSolver(Particle* particle)
		{
			return gravity * particle->mass;
		}
	}
}