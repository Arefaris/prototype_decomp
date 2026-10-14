// The particle module of pure3d (unit around 0x106EA000 - 0x106F2800; the class and file names are guesses): one
// manager, reached through GetParticleManager, that keeps the particle system states and their buffers.
#include "code/math/mathutils.h"
#include "code/math/pddicolour.h"
#include "code/math/vector4.h"
#include "code/pure3d/primitive.h"

namespace math
{
	static inline int ToByte(float value)
	{
		int v = (int)(value * 255.5f);
		if (v < 0)
		{
			v = 0;
		}
		else if (v > 255)
		{
			v = 255;
		}
		return v;
	}

	// FUNCTION: ENGINE 0x102CD6D0
	// EQUIVALENT: the engine tests v < 0 first and then v > 255 on both paths; every clamp form tried here tests in
	// another order
	// An inline of the math headers whose kept copy sits in another unit (the particle colours use it here)
	pddiColour::pddiColour(const Vector4& colour)
	{
		int alpha = ToByte(colour.w);
		int blue = ToByte(colour.z);
		int green = ToByte(colour.y);
		int red = ToByte(colour.x);
		*(unsigned int*)this = ((alpha << 8 | red) << 8 | green) << 8 | blue;
	}
}

namespace pure3d
{
	// 0x1127EE4C
	extern ParticleManager* gParticleManager;

	// FUNCTION: ENGINE 0x106ED9D0
	// A state may take the flag from the state it was made from
	bool ParticleSystemState::GetUnknown4BC()
	{
		return inheritUnknown4BC ? parent->GetUnknown4BC() : unknown4BC;
	}

	// FUNCTION: ENGINE 0x106EDA80
	ParticleManager* GetParticleManager()
	{
		return gParticleManager;
	}

	// FUNCTION: ENGINE 0x106EDC90
	bool ParticleManager::HasUnknown1A0()
	{
		return unknown1A0 != -1;
	}

	// FUNCTION: ENGINE 0x106EDCA0
	unsigned __int64 ParticleManager::GetUnknown1B0()
	{
		return unknown1B0;
	}
}
