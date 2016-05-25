#pragma once
#include "../ParticleEngine/Vector2.h"
#include "../ParticleEngine/Vectord2.h"
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
		WIND = (1 << 3),
		COLLISION_FRICTION =(1 <<29),
		COLLISION_REFLEXION = (1 << 30),
		EMITTER = (1 << 31),
	};
	struct Particle 
	{
		bool active = true;
		bool constact = false;
		int contacttimer = 2;
		uint32_t forceGenKey;
		Vector2  pos;
		Vector2	 velocity;
		//1/mass
		float	 massfactor;
		Vector2  force;

		Vector2 VelocityToForce(float deltatime) const
		{
			Vector2 force;
			force = velocity / (massfactor*deltatime);
			return force;
		}
	};
	struct Emitter : Particle
	{
		float currenttime;
		int	  NumberOfParticles;
		int   stage = 1;

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
		float CalculateAngle() const
		{
			Vector2 v = point2 - point1;
			return v.GetAngleDeg();
		}
	};
	struct CollisionData
	{
		Vector2 poi;
		int surfaceIndex;
	};
}