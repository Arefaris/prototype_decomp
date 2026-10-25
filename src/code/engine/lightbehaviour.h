// engine::LightBehaviour (RTTI and reflection names; base engine::Behaviour): a light of the world. Reflected: the
// kind of light (pure3d::Light::LightType, its movement, shadow type and decay shape), the colour and the six
// spherical harmonics colours, intensity, umbra and penumbra, the shadow's settings and cascades (the PS3 values are
// kept in the data), decay and attenuation, the offset transform, the size of an area light, the flags of what it
// affects and the groups it belongs to. Unit 0x1089B580 - 0x1089FF00 (no assert path; the directory and file name are
// guesses). The reflected member names are original; the rest is guessed.
#ifndef ENGINE_LIGHTBEHAVIOUR_H
#define ENGINE_LIGHTBEHAVIOUR_H

#include "code/container/arrayc.h"
#include "code/container/arraydynamic.h"
#include "code/container/arraydynamicallocatornew.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"
#include "code/math/colour128.h"
#include "code/math/matrix.h"
#include "code/pure3d/light.h"

namespace engine
{
	// How a light may move (reflected as engine::LightMovementType)
	enum LightMovementType
	{
		LIGHT_DYNAMIC_MOBILE = 0,
		LIGHT_DYNAMIC_IMMOBILE = 1,
		LIGHT_STATIC = 2
	};

	// How a light casts its shadow (reflected as pure3d::Shadow::ShadowType)
	enum LightShadowType
	{
		SHADOW_SPOT_SIMPLE = 0,
		SHADOW_SPOT_TSM = 1,
		SHADOW_DIRECTIONAL_BBOX = 2,
		SHADOW_DIRECTIONAL_TSM = 3,
		SHADOW_DIRECTIONAL_CSM = 4,
		SHADOW_SUNLIGHT_BBOX = 5,
		SHADOW_SUNLIGHT_TSM = 6,
		SHADOW_AUTOMATIC = 7
	};

	// Switches a light on or off (RTTI and reflection names; no constructor of the unit is used here)
	struct EnableLightMessage : public IntrusiveMessage
	{
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		bool on;  // +0xC
	};

	// Gives a light another colour
	struct ChangeLightColourMessage : public IntrusiveMessage
	{
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		math::Colour128 colour;  // +0xC
	};

	class LightBehaviour : public Behaviour
	{
	public:
		// 0x1089F9D0 (another unit; the second argument is passed as 1 by the creator, meaning unknown)
		explicit LightBehaviour(GameObject* newOwner, bool unknownFlag = true);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		float eulerAngleX;  // +0xC
		float eulerAngleY;  // +0x10
		float eulerAngleZ;  // +0x14
		unsigned char unknown18[0x60 - 0x18];
		pure3d::Light::LightType type;  // +0x60
		LightMovementType movement;  // +0x64
		math::Colour128 colour;  // +0x68
		math::Colour128 sphericalHarmonicColour[6];  // +0x78
		float intensity;  // +0xD8
		float ambientContribution;  // +0xDC
		float umbra;  // +0xE0
		float penumbra;  // +0xE4
		LightShadowType shadowType;  // +0xE8
		bool castShadow;  // +0xEC
		int shadowResolution;  // +0xF0
		float shadowSoftness;  // +0xF4
		float shadowOffset;  // +0xF8
		pure3d::DecayRange::DecayShape decayShape;  // +0xFC
		float decayInner;  // +0x100
		float decayOuter;  // +0x104
		float attenConstant;  // +0x108
		float attenLinear;  // +0x10C
		float attenQuadratic;  // +0x110
		bool isDynamic;  // +0x114
		bool isCheap;  // +0x115
		math::Matrix offsetTransform;  // +0x118
		float length;  // +0x158
		float width;  // +0x15C
		float height;  // +0x160
		bool useSphericalHarmonicValues;  // +0x164
		float scale;  // +0x168
		bool renderingEnabled;  // +0x16C
		bool emitSpecular;  // +0x16D
		unsigned char unknown16E[0x17C - 0x16E];
		unsigned int affectsFlags;  // +0x17C
		unsigned int numShadowCascades;  // +0x180
		float shadowCascadeExtent[5];  // +0x184
		unsigned int numShadowCascadesPS3;  // +0x198
		float shadowCascadeExtentPS3[5];  // +0x19C
		container::ArrayC<float, 27> sphericalHarmonicValues;  // +0x1B0
		container::ArrayDynamic<core::Name<core::CaseSensitiveKey>, container::AllocatorNew> lightGroups;  // +0x21C
		unsigned char unknown228[0x2BC - 0x228];
	};
}

#endif
