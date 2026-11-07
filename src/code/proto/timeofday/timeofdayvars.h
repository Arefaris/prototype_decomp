// proto::TimeOfDayVars, TimeOfDayVarGroup, TimeOfDayVariation, TimeOfDayLightInfo and FogAreaValues (RTTI and reflection
// names): the content objects of the time of day. A TimeOfDayVars object holds the lengths of the day, the names of
// the groups, the lights and the cloud cover; a TimeOfDayVarGroup the variations of the day (TimeOfDayVariation: the
// lighting, framebuffer effects, shader parameters and the fog values over the day). Unit 0x1051F1F0 - 0x1052E100
// with the channels of timeofdayvarchannel.h (no assert path; the file name is a guess). The reflected names are
// original, the other member names are guesses.
#ifndef PROTO_TIMEOFDAY_TIMEOFDAYVARS_H
#define PROTO_TIMEOFDAY_TIMEOFDAYVARS_H

#include "code/container/arrayfixed.h"
#include "code/content/loadinventory.h"
#include "code/core/name.h"
#include "code/core/refptr.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/proto/timeofday/globalfbeffectsrig.h"
#include "code/proto/timeofday/globallightingrig.h"
#include "code/proto/timeofday/globalshaderrig.h"
#include "code/pure3d/light.h"
#include "code/pure3d/primitive.h"

namespace proto
{
	// The fog of an area at one time of the day (60 bytes): two tints and the parameters of the fog layer
	struct FogAreaValues
	{
		__forceinline FogAreaValues()
		{
			darkTint.r = 0.25f;
			darkTint.g = 0.25f;
			darkTint.b = 0.25f;
			darkTint.a = engine::driving::gOne;
			lightTint.r = 0.75f;
			lightTint.g = 0.75f;
			lightTint.b = 0.75f;
			lightTint.a = engine::driving::gOne;
			fogTilingX = engine::driving::gHalf;
			fogTilingY = engine::driving::gOne;
			speed = 0.02f;
			fogFalloff = engine::driving::gOne;
			falloffModifier = 4.0f;
			fogVariation = engine::driving::gTwo;
			noiseStrength = 0.0f;
		}
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		math::Colour128 darkTint;
		math::Colour128 lightTint;  // +0x10
		float fogTilingX;  // +0x20
		float fogTilingY;
		float speed;
		float fogFalloff;
		float falloffModifier;
		float fogVariation;
		float noiseStrength;  // +0x38
	};

	// The channel of the fog values (RTTI proto::TimeOfDayVarChannel<struct proto::FogAreaValues>, 0x14 bytes): its
	// virtual functions are the engine's (0x102A2B40 - 0x102A6300, in a unit of their own); the vftable and the
	// functions are mapped in symbols.txt
	template<> class TimeOfDayVarChannel<FogAreaValues> : public TimeOfDayVarChannelBase
	{
	public:
		struct Key
		{
			Key()
			{
			}

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			float time;
			FogAreaValues value;
		};
		typedef container::ArrayDynamic<Key, container::AllocatorNew> KeyArray;

		TimeOfDayVarChannel()
		{
		}
		TimeOfDayVarChannel(const TimeOfDayVarChannel& other) : keys(other.keys)
		{
		}
		virtual ~TimeOfDayVarChannel();
		virtual bool HasKey(float time);
		virtual int GetValueSize();
		virtual void SetKeyValue(float time, const void* value);
		virtual void AddKey(float time);
		virtual void SetSingleKey(float time);
		virtual void RemoveKey(float time);
		virtual void Clear();
		virtual void ResetKey(float time);

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		KeyArray keys;  // +4
		int unknown10;
	};

	typedef TimeOfDayVarChannel<FogAreaValues> FogChannel;
	typedef container::ArrayDynamic<core::Name<core::CaseSensitiveKey>, container::AllocatorNew> NameArray;

	// One entry of the lights of the day (0x18 bytes): the name of a game object, the handle it was found as and the
	// light user data the lit pass reads
	struct TimeOfDayLightInfo
	{
		TimeOfDayLightInfo()
		{
			userData = 0;
			unknown10 = true;
		}
		TimeOfDayLightInfo(const TimeOfDayLightInfo& other);
		TimeOfDayLightInfo& operator=(const TimeOfDayLightInfo& other);
		~TimeOfDayLightInfo()
		{
			core::SafeRelease(userData);
		}
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		core::Name<core::CaseSensitiveKey> name;
		engine::HandleBase handle;  // +8
		pure3d::ProtoLightUserData* userData;  // +0xC
		bool unknown10;
	};

	typedef container::ArrayDynamic<TimeOfDayLightInfo, container::AllocatorNew> LightInfoArray;

	// One variation of the day (0x108 bytes): the lighting, framebuffer effects and shader parameters and the fog
	struct TimeOfDayVariation
	{
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		core::Name<core::CaseSensitiveKey> name;
		GlobalLightingRig globalLights;  // +8
		GlobalFBEffectsRig globalFBEffects;  // +0x54
		GlobalShaderRig globalShaderParams;  // +0xB4
		FogChannel globalFogValues;  // +0xF4
	};

	typedef container::ArrayDynamic<TimeOfDayVariation, container::AllocatorNew> VariationArray;

	// RTTI proto::TimeOfDayVarGroup (7 slots): the variations of one group of days
	class TimeOfDayVarGroup : public content::MetaLoadObject
	{
	public:
		virtual ~TimeOfDayVarGroup();
		virtual bool Slot3();
		virtual bool Slot4();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		core::Name<core::CaseSensitiveKey> name;  // +8
		container::ArrayDynamic<TimeOfDayVariation, container::AllocatorNew> dayVariations;  // +0x10
		int unknown1C;
	};

	// RTTI proto::TimeOfDayVars (7 slots; 0x258 bytes): the day lengths, the groups of days and the lights
	class TimeOfDayVars : public content::MetaLoadObject
	{
	public:
		TimeOfDayVars();
		virtual ~TimeOfDayVars();
		virtual bool Slot3();
		virtual bool Slot4();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		float dayLength;  // +8
		float dawnTime;
		float duskTime;
		float renderDawnTime;
		float renderDuskTime;  // +0x18
		container::ArrayDynamic<TimeOfDayVarGroup*, container::AllocatorNew> groups;  // +0x1C
		int unknown28;
		container::ArrayDynamic<core::Name<core::CaseSensitiveKey>, container::AllocatorNew> dayGroups;  // +0x2C
		int unknown38;
		container::ArrayDynamic<TimeOfDayLightInfo, container::AllocatorNew> lights;  // +0x3C
		int unknown48;
		pure3d::Texture* cloudCover;  // +0x4C
		content::LoadInventory* inventory;  // +0x50
		container::ArrayFixed<TimeOfDayVarGroup*, 128> loadedGroups;  // +0x54
	};
}

#endif
