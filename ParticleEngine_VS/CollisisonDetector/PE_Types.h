#pragma once
#include "../ParticleEngine/Vector2.h"
#include <inttypes.h>
#include <vector>
#include <limits>
#include "../ParticleEngine/Randomizer.h"

namespace pe
{
	enum Keys
	{
		GRAVITY = (1 << 0),
		DRAG	= (1 << 1),
		IMPULSE = (1 << 2),
		DELAYEDIMPULSE = (1 << 3),
		COLLISION_FRICTION =(1 << 30),
		COLLISION_REFLEXION = (1 << 31)
	};
	struct Force
	{
		Vector2 direction;
		float amount;
	};
	struct Particle 
	{
		uint32_t forceGenKey;
		Vector2  pos;
		Vector2	 velocity;
		float	 mass;
		Force	 f;
	};
	struct Emitter : Particle
	{
		float currenttime;
		float timer;
		int		 NumberOfParticles;

	};
	struct Surface
	{
		Vector2 point1;
		Vector2 point2;
		Vector2 normal;
		void CalculateLeftNormal()
		{
			Vector2 v = point2 - point1;
			v = v.Normalize();
			normal.x = v.y ;
			normal.y = v.x *-1;
		}
		void CalculateRightNormal()
		{
			Vector2 v = point2 - point1;
			v = v.Normalize();
			normal.x = v.y *-1;
			normal.y = v.x;
		}
	};
	const Vector2 EMITNEW(-std::numeric_limits<float>::infinity(), +std::numeric_limits<float>::infinity());
}