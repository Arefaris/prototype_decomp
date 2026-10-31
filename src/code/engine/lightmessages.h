// engine::SetLightPropertiesMessage and engine::GetLightPropertiesMessage (RTTI names; both also derive from
// engine::LightPropertiesMessage, a plain struct 0x80 bytes behind the message header): set the properties of a light
// object, or ask for the ones it has. The constructors (0x10514090 and 0x1053D740) are out of line in other units;
// the member names are guesses from the light action that blends them.
#ifndef ENGINE_LIGHTMESSAGES_H
#define ENGINE_LIGHTMESSAGES_H

#include "code/engine/message.h"
#include "code/math/colour128.h"

namespace engine
{
	// RTTI: engine::LightPropertiesMessage (a struct without virtual functions)
	struct LightPropertiesMessage
	{
		// The properties the message sets (bit 1: colour, bit 2: intensity, 0x1438: shadow caster, 0x300: umbra, 0x40:
		// decay, 0x400: whether the light casts shadows)
		unsigned int changed;  // +0xC
		float eulerAngleX;  // +0x10
		float eulerAngleY;  // +0x14
		float eulerAngleZ;  // +0x18
		float intensity;  // +0x1C
		math::Colour128 colour;  // +0x20
		float shadowRadiusMultiplier;  // +0x30
		float shadowRangeMultiplier;  // +0x34
		float shadowMaxRadius;  // +0x38
		float decayInner;  // +0x3C
		float decayOuter;  // +0x40
		float unknown44;
		float umbra;  // +0x48
		float penumbra;  // +0x4C
		bool shadowCaster;  // +0x50
		int unknown54;
		float shadowOffset;  // +0x58
		int unknown5C;
		float unknown60;
		float unknown64;
		float unknown68;
		float unknown6C;
		float unknown70;
		int unknown74;
		float unknown78;
		float unknown7C;
		float unknown80;
		float unknown84;
		float unknown88;
	};

	// RTTI: engine::SetLightPropertiesMessage (type 9, id 2)
	struct SetLightPropertiesMessage : public IntrusiveMessage, public LightPropertiesMessage
	{
		// 0x10514090
		SetLightPropertiesMessage();
	};

	// RTTI: engine::GetLightPropertiesMessage (type 9, id 3)
	struct GetLightPropertiesMessage : public NonintrusiveMessage, public LightPropertiesMessage
	{
		// 0x1053D740
		GetLightPropertiesMessage();
	};
}

#endif
