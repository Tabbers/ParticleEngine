#pragma once
#include "PE_Types.h"
#include <algorithm>

namespace pe
{
	namespace collision
	{
		const float dampening = 0.2f;
		const float frictionValues[2] = {0.5f,0.2f};
		//returns the time of Collision between a particle and a surface
		static bool VectorLineCollision(Particle* particle, std::vector<pe::Surface*> &surfaces, pe::CollisionData &coldata, float deltatime)
		{
			Vector2 p1 = particle->pos + particle->velocity * deltatime;

			float x1 = particle->pos.x;
			float x2 = p1.x;
			float y1 = particle->pos.y;
			float y2 = p1.y;

			for (unsigned int i = 0; i < surfaces.size(); ++i)
			{
				
				float x3 = surfaces[i]->point1.x;
				float x4 = surfaces[i]->point2.x;

				float y3 = surfaces[i]->point1.y;
				float y4 = surfaces[i]->point2.y;

				float den = (y4 - y3)*(x2 - x1) - (x4 - x3)*(y2 - y1);
				float numA = (x4 - x3)*(y1 - y3) - (y4 - y3)*(x1 - x3);
				float numB = (x2 - x1)*(y1 - y3) - (y2 - y1)*(x1 - x3);

				// the lines are coincident
				if (numA == numB && numA == 0.0f)
				{
					return false;
				}

				float ua = numA / den;
				float ub = numB / den;

				if (ua > 0.0f && ua <= 1.0f && ub > 0.0f && ub <= 1.0f)
				{
					coldata.surfaceIndex = i;
					coldata.poi.x = x1 + (x2 - x1)*ua;
					coldata.poi.y = y1 + (y2 - y1)*ua;
					return true;
				}
			}
		return false;
		}
		//Returns a Vector reflected on the surface around the surface normal
		static Vector2 ReflectOfSurface(Vector2 in, Surface* surface)
		{
			return in - surface->normal * (2 * in.dot(surface->normal));
		}

		static bool CollissionSolver(Particle* particle, std::vector<Surface*> &surfaces, Vector2 &futurepos, float deltatime)
		{
			bool collision = false;
			pe::CollisionData colData;
			collision = collision::VectorLineCollision(particle, surfaces, colData, deltatime);
			if (collision)
			{
				particle->forceGenKey &= ~pe::Keys::WIND;
				Surface* colSurface = surfaces[colData.surfaceIndex];
				Vector2 correction = colSurface->normal;
				particle->pos = colData.poi + correction;
				if (particle->forceGenKey & pe::Keys::COLLISION_REFLEXION)
				{
					if (particle->velocity.Length() > 100.0f && particle->constact == false)
					{
						particle->velocity = ReflectOfSurface(particle->velocity, surfaces[colData.surfaceIndex]) * dampening;
						particle->pos += particle->velocity * deltatime;
					}
					else
					{
						particle->forceGenKey &= ~pe::Keys::COLLISION_REFLEXION;
						particle->constact = true;
					}
				}
				else if (particle->forceGenKey & pe::Keys::COLLISION_FRICTION)
				{
					particle->contacttimer -= 1;
					if (particle->contacttimer < 0)
					{
						particle->contacttimer = 4;
						particle->constact = false;
					}
					Surface* colSurface = surfaces[colData.surfaceIndex];
					Vector2 surfaceNormal = colSurface->normal * -1.0f;
					Vector2 surfaceDirection = (colSurface->point2 - colSurface->point1).Normalize();
					Vector2 particleForce = particle->VelocityToForce(deltatime);
					if (surfaceDirection.y < 0)
					{
						surfaceDirection *= -1;
					}

					//FRICTION
					Vector2 fn = surfaceNormal * surfaceNormal.dot(particleForce);
					Vector2 fp = surfaceDirection * surfaceDirection.dot(particleForce);

					float fpLength = fp.Length();
					float fnLength = fn.Length();
					float staticThreshold = fnLength * frictionValues[0];
					float kinematicThreshold = fnLength * frictionValues[1];

					if (fpLength > staticThreshold)
					{
						float slidefactor = std::max(fpLength - kinematicThreshold, fpLength * 0.01f);

						Vector2 accelerationForce = surfaceDirection * slidefactor;
						particle->velocity = surfaceDirection * particle->velocity.dot(surfaceDirection);
						particle->velocity += accelerationForce * particle->massfactor * powf(deltatime,2)*0.5f;
						particle->pos += particle->velocity * deltatime;
					}
					else
					{
						particle->velocity -= particle->velocity;
						particle->contacttimer -= 1;
						if (particle->contacttimer < 0)
						{
							particle->active = false;
						}
					}
				}
			}
			else
			{
				particle->pos = futurepos;
				particle->contacttimer -= 1;
				if (particle->contacttimer < 0)
				{
					particle->contacttimer = 2;
					particle->constact = false;
					particle->forceGenKey |= pe::Keys::COLLISION_REFLEXION;
					particle->forceGenKey |= pe::Keys::WIND;
				}	
			}
			return collision;
		}
	}
}