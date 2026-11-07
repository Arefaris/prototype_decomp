// proto::HitEffectManager::HitEffectParams: what one hit passes to the fight tree of the hit effects (see the header).
#include "code/proto/hiteffects/hiteffectparams.h"

namespace proto
{
	namespace HitEffectManager
	{
		// FUNCTION: ENGINE 0x104F51A0
		// NONMATCHING: the engine zeroes the integer register after the floats' stores and writes the flag byte behind the serial, 71.9 %
#ifdef NONMATCHING
		HitEffectParams::HitEffectParams() : fight::Params(0x40000), kind(10), giver(), receiver(), chargeValue(0.0f), hitType(), effectType()
		{
			float one = engine::driving::gOne;
			unknown84 = one;
			unknown90 = one;
			unknown94 = one;
			unknown88 = 0;
			unknown8C = 0;
			physicsObject = -1;
			physicsObjectSerial = 0xFFFF;
			objectVolume = 0.0f;
			objectSpeed = 0.0f;
			fromMuscleMass = false;
		}
#endif

		// FUNCTION: ENGINE 0x104F5270
		HitEffectParams::~HitEffectParams()
		{
		}
	}
}
