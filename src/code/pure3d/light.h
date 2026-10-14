// pure3d::Light (RTTI name; bases pure3d::Entity, pure3d::RefCounted, core::IRefCount) and the user data the engine
// hangs on it (pure3d::LightUserData and its subclass pure3d::ProtoLightUserData). Only what the render passes read;
// the accessors are small functions of the light unit (0x10758300 - 0x10758B50) that the passes call. Member and
// method names are guesses.
#ifndef PURE3D_LIGHT_H
#define PURE3D_LIGHT_H

#include "code/math/vector.h"
#include "code/math/vector4.h"
#include "code/pure3d/entity.h"

namespace pure3d
{
	class LightUserData : public RefCounted
	{
	};

	// The engine's own light user data: two intensity scales (the lit pass picks one by mode), a range scale and a
	// flag (1: the light is a cheap, per-vertex light)
	class ProtoLightUserData : public LightUserData
	{
	public:
		float unknown8;
		float unknownC;
		float unknown10;
		unsigned char unknown14[4];
		int cheap;
	};

	// How far a light reaches: kind 0 means without limit, otherwise the range is at +8
	class LightDecay
	{
	public:
		// 0x10758B10 / 0x10758B50
		int GetKind();
		float GetRange();

		int kind;
		int unknown4;
		float range;
	};

	class Light : public Entity
	{
	public:
		enum LightType
		{
			TYPE_AMBIENT = 1,
			TYPE_DIRECTIONAL = 2,
			TYPE_POINT = 3,
			TYPE_SPOT = 4
		};

		// 0x10758300: the colour (red, green, blue, intensity)
		const math::Vector4* GetColour();
		// 0x10758340 / 0x10758380
		const math::Vector* GetPosition();
		const math::Vector* GetDirection();
		// 0x107584D0
		LightDecay* GetDecay();
		// 0x10758560
		bool IsEnabled();
		// 0x107582A0
		LightUserData* GetUserData();
		// 0x10758760: how much of the light's colour goes to the second colour constant
		float GetUnknown10758760();

		unsigned char unknown10[0xB8];
		math::Vector4 colour;
		math::Vector position;
		math::Vector direction;
		unsigned char unknownF0[0x18];
		LightDecay decay;
		unsigned char unknown114[0x4C];
		bool enabled;
		unsigned char unknown161[0x2B];
		int type;
		unsigned char unknown190[0x80];
		LightUserData* userData;
	};
}

#endif
