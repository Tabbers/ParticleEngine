#pragma once
#include "PE_Types.h"

namespace pe
{
	namespace collision
	{
		const float dampening = 0.1;
		//returns the time of Collision between a particle and a surface
		static float VectorLineCollision(Particle* particle, Surface* surface, float deltatime)
		{
			Vector2 s = particle->velocity*deltatime;
			Vector2 r = surface->point2 - surface->point1;

			float rdets = r.det(s);

			float t = (particle->pos - surface->point1).det(s) / rdets;
			float u = (particle->pos - surface->point1).det(r) / rdets;
			if (fabsf(rdets) > r.EPSILON && (t >= 0 && t <= 1) && (u >= 0 && u <= 1))
			{
				return t;
			}
			else
			{
				return -1.0f;
			}

		}
		//Returns a Vector reflected on the surface around the surface normal
		static Vector2 ReflectOfSurface(Vector2 in, Surface* surface)
		{
			return in - surface->normal * (2 * in.dot(surface->normal));
		}
		static bool SurfaceCollissionSolver(Particle* particle, std::vector<Surface*> &surfaces, float deltatime)
		{
			for (unsigned int i = 0; i < surfaces.size(); ++i)
			{
				float timeOfCollision = collision::VectorLineCollision(particle, surfaces[i], deltatime);
				if (timeOfCollision == -1.0f)
				{
					continue;
				}
				else
				{
					//Point of Impact
					Vector2 poi = particle->pos + particle->velocity * timeOfCollision;
					particle->velocity = ReflectOfSurface(particle->velocity, surfaces[i]) * dampening;
					return true;
				}
			}
			return false;
		}
	}
}