#pragma once
#include "PE_Types.h"

namespace pe
{
	namespace forceSolver
	{
		const Vector2 m_gravity(0.0f, 200.81f);
		const Vector2 m_wind(100.0f, 0.0f);
		const float m_friction  = 0.001f;
		const float m_preassure = 0.001f;

		static float windtime = 0.0f;

		static Vector2 WindSolver(float deltatime)
		{
			windtime += deltatime * 0.125f;
			return m_wind * sin(windtime );
		}
		static Vector2 GravitySolver(Particle* particle)
		{
			return m_gravity;
		}
		static Vector2 DragSolver(Particle* particle)
		{
			Vector2 force;
			float velLength = particle->velocity.Length();
			if (particle->velocity.x == 0 && particle->velocity.y == 0)
			{
				return force;
			}
			Vector2 velNormalized = particle->velocity.Normalize() * -1;
			float draglength = m_friction * velLength + m_preassure * powf(velLength, 2);
			velNormalized *= draglength;
			return velNormalized;
		}
		static Vector2 ImpulseSolver(Particle* particle)
		{
			return particle->force;
		}

		static Vector2 ForceSolver(Particle* particle,float deltatime)
		{
			Vector2 finalforce;
			unsigned short gravity = (particle->forceGenKey & pe::Keys::GRAVITY);
			unsigned short drag = ((particle->forceGenKey & pe::Keys::DRAG) >> 1);
			unsigned short impulse = ((particle->forceGenKey & pe::Keys::IMPULSE) >> 2);
			unsigned short wind = ((particle->forceGenKey & pe::Keys::WIND) >> 3);
			particle->forceGenKey &= ~pe::Keys::IMPULSE;

			finalforce += GravitySolver(particle) * gravity;
			finalforce += DragSolver(particle) * drag;
			finalforce += ImpulseSolver(particle) * impulse;
			finalforce += WindSolver(deltatime) * wind;
			
			return finalforce;
		}
	}
}