#pragma once
#include "../ParticleEngine/Vector2.h"
#include <inttypes.h>

namespace pe
{
	enum Keys
	{
		GRAVITY = (1 << 0),
		DRAG	= (1 << 1),
		ELASTIC = (1 << 2)
	};
	struct Particle 
	{
		uint16_t forceGenKey;
		Vector2  pos;
		Vector2	 velocity;
		float	 mass;
	};
	struct EmitterParticle : Particle
	{
		float timer;
		float currenttime;
	};
	struct Surface
	{
		Vector2 point1;
		Vector2 point2;
		Vector2 normal;
	};
}