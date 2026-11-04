// proto::GlobalLightingRig (reflection names): the lighting of the time of day, as channels of keys over the day: the
// sky, the global light and the clouds, and the lights, each a channel of its own data. The parameter structs are
// proto::GlobalLightingRig::SkyParameters, GlobalLightParameters, CloudParameters and Light::LightData. Unit
// 0x1053D870 - 0x1054D580 (no assert path; the file name is a guess). The reflected names are original, the defaults
// are the ones the engine's key constructors store.
#ifndef PROTO_TIMEOFDAY_GLOBALLIGHTINGRIG_H
#define PROTO_TIMEOFDAY_GLOBALLIGHTINGRIG_H

#include "code/core/name.h"
#include "code/engine/lightbehaviour.h"
#include "code/proto/timeofday/timeofdayvarchannel.h"

namespace engine
{
	namespace driving
	{
		// 0x10D946E0, 0x10D94CC4: 1 and 0.5 in the pooled constants
		extern const float gOne;
		extern const float gHalf;
	}
}

namespace proto
{
	struct GlobalLightingRig
	{
		// 136 bytes
		struct SkyParameters
		{
			__forceinline SkyParameters()
			{
				skyColour.r = 0.2f;
				skyColour.g = 0.4f;
				skyColour.b = engine::driving::gOne;
				skyColour.a = engine::driving::gOne;
				fogColour.r = engine::driving::gOne;
				fogColour.g = engine::driving::gOne;
				fogColour.b = engine::driving::gOne;
				fogColour.a = engine::driving::gOne;
				decayColour.r = engine::driving::gOne;
				decayColour.g = engine::driving::gOne;
				decayColour.b = engine::driving::gOne;
				decayColour.a = engine::driving::gOne;
				horizonColour.r = 0.0f;
				horizonColour.g = 0.0f;
				horizonColour.b = 0.0f;
				horizonColour.a = engine::driving::gOne;
				sunColour.r = engine::driving::gOne;
				sunColour.g = engine::driving::gOne;
				sunColour.b = engine::driving::gOne;
				sunColour.a = engine::driving::gOne;
				starStrength = 0.0f;
				horizonSize = 0.0f;
				sunSize = 0.0f;
				sunStrength = engine::driving::gHalf;
				glowSize = 32.0f;
				glowStrength = 0.0f;
				fogDensity = 0.0f;
				fogMaxDensity = engine::driving::gOne;
				skyHalfHeight = 1024.0f;
				decayDensity = 0.0f;
				decayHalfHeight = 1024.0f;
				fogHalfHeight = 512.0f;
				scatterDensity = 0.0f;
				scatterDistance = 1000.0f;
			}
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			math::Colour128 skyColour;
			math::Colour128 fogColour;
			math::Colour128 decayColour;
			math::Colour128 horizonColour;
			math::Colour128 sunColour;
			float starStrength;
			float horizonSize;
			float sunSize;
			float sunStrength;
			float glowSize;
			float glowStrength;
			float fogDensity;
			float fogMaxDensity;
			float skyHalfHeight;
			float decayDensity;
			float decayHalfHeight;
			float fogHalfHeight;
			float scatterDensity;
			float scatterDistance;
		};

		// 96 bytes
		struct GlobalLightParameters
		{
			__forceinline GlobalLightParameters()
			{
				hemiLightUpper.r = 0.0f;
				hemiLightUpper.g = 0.0f;
				hemiLightUpper.b = 0.0f;
				hemiLightUpper.a = engine::driving::gOne;
				hemiLightLower.r = 0.0f;
				hemiLightLower.g = 0.0f;
				hemiLightLower.b = 0.0f;
				hemiLightLower.a = engine::driving::gOne;
				clearColour.r = 0.0f;
				clearColour.g = 0.0f;
				clearColour.b = 0.0f;
				clearColour.a = engine::driving::gOne;
				midgroundColour.r = engine::driving::gOne;
				midgroundColour.g = engine::driving::gOne;
				midgroundColour.b = engine::driving::gOne;
				midgroundColour.a = engine::driving::gOne;
				desatStartDist = 300.0f;
				desatRange = 300.0f;
				desatMin = 0.6f;
				nearYScale = engine::driving::gOne;
				farYScale = 20.0f;
				camDistBias = 20.0f;
				yFalloff = 2.0f;
				streetLevel = 14.0f;
			}
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			math::Colour128 hemiLightUpper;
			math::Colour128 hemiLightLower;
			math::Colour128 clearColour;
			math::Colour128 midgroundColour;
			float desatStartDist;
			float desatRange;
			float desatMin;
			float nearYScale;
			float farYScale;
			float camDistBias;
			float yFalloff;
			float streetLevel;
		};

		// 108 bytes
		struct CloudParameters
		{
			__forceinline CloudParameters()
			{
				lowScaleDir.r = engine::driving::gOne;
				lowScaleDir.g = engine::driving::gOne;
				lowScaleDir.b = 0.0f;
				lowScaleDir.a = 0.0f;
				highScaleDir.r = engine::driving::gOne;
				highScaleDir.g = engine::driving::gOne;
				highScaleDir.b = 0.0f;
				highScaleDir.a = 0.0f;
				lowOpacity = 0.0f;
				highOpacity = 0.0f;
				lowColour.r = 0.0f;
				lowColour.g = 0.0f;
				lowColour.b = 0.0f;
				lowColour.a = engine::driving::gOne;
				highColour.r = engine::driving::gOne;
				highColour.g = engine::driving::gOne;
				highColour.b = engine::driving::gOne;
				highColour.a = engine::driving::gOne;
				softness = engine::driving::gHalf;
				sunColour.r = engine::driving::gOne;
				sunColour.g = engine::driving::gOne;
				sunColour.b = engine::driving::gOne;
				sunColour.a = 16.0f;
				sunLightRadius = 2.0f;
				terrainScale = 0.01f;
				terrainDarkness = engine::driving::gOne;
				terrainOpacity = engine::driving::gOne;
			}
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			math::Colour128 lowScaleDir;
			math::Colour128 highScaleDir;
			float lowOpacity;
			float highOpacity;
			math::Colour128 lowColour;
			math::Colour128 highColour;
			float softness;
			math::Colour128 sunColour;
			float sunLightRadius;
			float terrainScale;
			float terrainDarkness;
			float terrainOpacity;
		};

		// One light of the rig (128 + 32 bytes)
		class Light
		{
		public:
			// The data of a light over the day (128 bytes)
			struct LightData
			{
				__forceinline LightData()
				{
					colour.r = engine::driving::gOne;
					colour.g = engine::driving::gOne;
					colour.b = engine::driving::gOne;
					colour.a = engine::driving::gOne;
					euler.x = 0.0f;
					euler.y = 0.0f;
					euler.z = 0.0f;
					position.x = 0.0f;
					position.y = 0.0f;
					position.z = 0.0f;
					propIntensity = engine::driving::gOne;
					specIntensity = engine::driving::gOne;
					shadowIntensity = engine::driving::gOne;
					innerDecay = 0.0f;
					outerDecay = 10.0f;
					ambientShade = 0.0f;
					umbra = 1.57f;
					penumbra = 0.175f;
					shadowType = engine::SHADOW_AUTOMATIC;
					shadowOffset = 0.001f;
					numShadowCascades = 5;
					shadowCascadeExtent1 = engine::driving::gOne;
					shadowCascadeExtent2 = 2.0f;
					shadowCascadeExtent3 = 4.0f;
					shadowCascadeExtent4 = 12.0f;
					shadowCascadeExtent5 = 24.0f;
					numShadowCascadesPS3 = 4;
					shadowCascadeExtentPS3_1 = engine::driving::gOne;
					shadowCascadeExtentPS3_2 = 2.0f;
					shadowCascadeExtentPS3_3 = 4.0f;
					shadowCascadeExtentPS3_4 = 16.0f;
					shadowCascadeExtentPS3_5 = 24.0f;
				}
				static content::ClassInfo* GetClassInfo();
				static content::MemberList* GetMembers();

				math::Colour128 colour;
				math::Vector euler;  // +0x10
				math::Vector position;  // +0x1C
				float propIntensity;  // +0x28
				float specIntensity;
				float shadowIntensity;
				float innerDecay;
				float outerDecay;
				float ambientShade;
				float umbra;
				float penumbra;
				engine::LightShadowType shadowType;  // +0x48
				float shadowOffset;
				unsigned int numShadowCascades;  // +0x50
				float shadowCascadeExtent1;
				float shadowCascadeExtent2;
				float shadowCascadeExtent3;
				float shadowCascadeExtent4;
				float shadowCascadeExtent5;
				unsigned int numShadowCascadesPS3;  // +0x68
				float shadowCascadeExtentPS3_1;
				float shadowCascadeExtentPS3_2;
				float shadowCascadeExtentPS3_3;
				float shadowCascadeExtentPS3_4;
				float shadowCascadeExtentPS3_5;
			};

			Light()
			{
			}
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			core::Name<core::CaseSensitiveKey> name;
			TimeOfDayVarChannel<LightData> lightKeys;  // +8
			bool shadowEnabled;  // +0x1C
		};

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		container::ArrayDynamic<Light, container::AllocatorNew> lights;
		int unknownC;
		TimeOfDayVarChannel<SkyParameters> skyKeys;  // +0x10
		TimeOfDayVarChannel<GlobalLightParameters> globalKeys;  // +0x24
		TimeOfDayVarChannel<CloudParameters> cloudKeys;  // +0x38
	};
}


namespace proto
{
	// The lighting's RemoveKey reaches the array through a reference
	template<> struct KeyOrder<GlobalLightingRig::SkyParameters>
	{
		enum
		{
			sizeFirst = 0,
			arrayReference = 0
		};
	};
	template<> struct KeyOrder<GlobalLightingRig::GlobalLightParameters>
	{
		enum
		{
			sizeFirst = 0,
			arrayReference = 0
		};
	};
	template<> struct KeyOrder<GlobalLightingRig::CloudParameters>
	{
		enum
		{
			sizeFirst = 0,
			arrayReference = 0
		};
	};
	template<> struct KeyOrder<GlobalLightingRig::Light::LightData>
	{
		enum
		{
			sizeFirst = 0,
			arrayReference = 0
		};
	};
}

namespace container
{
	// The keys of the lighting are moved down by the out-of-line AssignRange
	template<> struct ArrayEraseInline<proto::TimeOfDayVarChannel<proto::GlobalLightingRig::SkyParameters>::Key>
	{
		enum
		{
			value = 0
		};
	};
	template<> struct ArrayEraseInline<proto::TimeOfDayVarChannel<proto::GlobalLightingRig::GlobalLightParameters>::Key>
	{
		enum
		{
			value = 0
		};
	};
	template<> struct ArrayEraseInline<proto::TimeOfDayVarChannel<proto::GlobalLightingRig::CloudParameters>::Key>
	{
		enum
		{
			value = 0
		};
	};
	template<> struct ArrayEraseInline<proto::TimeOfDayVarChannel<proto::GlobalLightingRig::Light::LightData>::Key>
	{
		enum
		{
			value = 0
		};
	};
	template<> struct ArrayEraseInline<proto::GlobalLightingRig::Light>
	{
		enum
		{
			value = 0
		};
	};
}

namespace content
{
	PROTO_KEY_ARRAY_HELPER_BEGIN(proto::TimeOfDayVarChannel<proto::GlobalLightingRig::SkyParameters>::Key)
	PROTO_KEY_ARRAY_HELPER_INSERT(static T sDefault; a->Insert(position, sDefault);)
	PROTO_KEY_ARRAY_HELPER_END

	PROTO_KEY_ARRAY_HELPER_BEGIN(proto::TimeOfDayVarChannel<proto::GlobalLightingRig::GlobalLightParameters>::Key)
		static T& Default()
		{
			static T sDefault;
			return sDefault;
		}
	PROTO_KEY_ARRAY_HELPER_INSERT(a->Insert(position, 1, Default());)
	PROTO_KEY_ARRAY_HELPER_END

	PROTO_KEY_ARRAY_HELPER_BEGIN(proto::TimeOfDayVarChannel<proto::GlobalLightingRig::CloudParameters>::Key)
		static T& Default()
		{
			static T sDefault;
			return sDefault;
		}
	PROTO_KEY_ARRAY_HELPER_INSERT(a->Insert(position, 1, Default());)
	PROTO_KEY_ARRAY_HELPER_END

	PROTO_KEY_ARRAY_HELPER_BEGIN(proto::TimeOfDayVarChannel<proto::GlobalLightingRig::Light::LightData>::Key)
	PROTO_KEY_ARRAY_HELPER_INSERT(static T sDefault; a->Insert(position, sDefault);)
	PROTO_KEY_ARRAY_HELPER_END
}

#endif
