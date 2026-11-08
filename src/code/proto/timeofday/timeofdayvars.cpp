#include "code/proto/timeofday/timeofdayvars.h"
#include "code/content/colourmetatype.h"
#include "code/content/vectormetatype.h"
#include "code/math/colour128.h"
#include "code/math/vector.h"
#include "code/math/vector2.h"

namespace container
{
	// The arrays of this unit's objects with all their members, as the unit's template instances (the engine's copies of the
	// variation array's functions call the key arrays' and the rigs' special members)
	template class ArrayDynamic<proto::TimeOfDayVariation, AllocatorNew>;
	template class ArrayDynamic<proto::TimeOfDayLightInfo, AllocatorNew>;
	template class ArrayDynamic<proto::TimeOfDayVarChannel<float>::Key, AllocatorNew>;
	template class ArrayDynamic<proto::TimeOfDayVarChannel<math::Vector>::Key, AllocatorNew>;
	template class ArrayDynamic<proto::TimeOfDayVarChannel<math::Colour128>::Key, AllocatorNew>;
	template class ArrayDynamic<proto::TimeOfDayVarChannel<math::Vector2>::Key, AllocatorNew>;
}

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// The reflection of the keys of the plain value channels
	// FUNCTION: ENGINE 0x105203E0
	template<> content::MemberList* TimeOfDayVarChannel<float>::Key::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<Key, float, 0>("p"), PROTO_OFFSET(Key, time), "time" },
			{ content::GetMemberPrimitiveMetaType<Key, float, 1>("p"), PROTO_OFFSET(Key, value), "value" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10520310
	template<> content::MemberList* TimeOfDayVarChannel<math::Vector>::Key::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<Key, float, 0>("p"), PROTO_OFFSET(Key, time), "time" },
			{ content::GetMemberVectorMetaType<Key, 1>("p"), 4, "value" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10520240
	template<> content::MemberList* TimeOfDayVarChannel<math::Colour128>::Key::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<Key, float, 0>("p"), PROTO_OFFSET(Key, time), "time" },
			{ content::GetMemberColourMetaType<Key, 1>("p"), PROTO_OFFSET(Key, value), "value" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10520DC0
	template<> content::MemberList* TimeOfDayVarChannel<float>::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<TimeOfDayVarChannel<float>, KeyArray>(content::GetClassMetaType<Key>(), "p"),
				PROTO_OFFSET(TimeOfDayVarChannel<float>, keys), "keys" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10520D10
	template<> content::MemberList* TimeOfDayVarChannel<math::Vector>::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<TimeOfDayVarChannel<math::Vector>, KeyArray>(content::GetClassMetaType<Key>(), "p"),
				PROTO_OFFSET(TimeOfDayVarChannel<math::Vector>, keys), "keys" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10520C60
	template<> content::MemberList* TimeOfDayVarChannel<math::Colour128>::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<TimeOfDayVarChannel<math::Colour128>, KeyArray>(content::GetClassMetaType<Key>(), "p"),
				PROTO_OFFSET(TimeOfDayVarChannel<math::Colour128>, keys), "keys" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1051F370
	template<> content::ClassInfo* TimeOfDayVarChannel<math::Colour128>::Key::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TimeOfDayVarChannel<math::Colour>::Key";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1051F3B0
	template<> content::ClassInfo* TimeOfDayVarChannel<math::Colour128>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TimeOfDayVarChannel<math::Colour>";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1051F3F0
	template<> content::ClassInfo* TimeOfDayVarChannel<math::Vector>::Key::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TimeOfDayVarChannel<math::Vector>::Key";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1051F430
	template<> content::ClassInfo* TimeOfDayVarChannel<math::Vector>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TimeOfDayVarChannel<math::Vector>";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1051F470
	template<> content::ClassInfo* TimeOfDayVarChannel<float>::Key::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TimeOfDayVarChannel<float>::Key";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1051F4B0
	template<> content::ClassInfo* TimeOfDayVarChannel<float>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TimeOfDayVarChannel<float>";
		sInfo.code = "p";
		return &sInfo;
	}


	// The class infos of the fog values, their keys and channel, and of the objects of the time of day
	// FUNCTION: ENGINE 0x10521530
	content::ClassInfo* FogAreaValues::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::FogAreaValues";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10521570
	content::ClassInfo* TimeOfDayVarChannel<FogAreaValues>::Key::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TimeOfDayVarChannel<proto::FogAreaValues>::Key";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x105215B0
	content::ClassInfo* TimeOfDayVarChannel<FogAreaValues>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TimeOfDayVarChannel<proto::FogAreaValues>";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x105215F0
	content::ClassInfo* TimeOfDayLightInfo::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TimeOfDayLightInfo";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10521630
	content::ClassInfo* TimeOfDayVariation::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TimeOfDayVariation";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10521670
	content::ClassInfo* TimeOfDayVarGroup::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TimeOfDayVarGroup";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x105216B0
	content::ClassInfo* TimeOfDayVars::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TimeOfDayVars";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10521DA0
	content::MemberList* TimeOfDayLightInfo::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberNameMetaType<TimeOfDayLightInfo, 0>(true, true, "p"), PROTO_OFFSET(TimeOfDayLightInfo, name), "name" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}



	// FUNCTION: ENGINE 0x10521730
	float TimeOfDayVars::GetDawnTime()
	{
		return dawnTime;
	}

	// FUNCTION: ENGINE 0x10521740
	float TimeOfDayVars::GetDuskTime()
	{
		return duskTime;
	}

	// FUNCTION: ENGINE 0x10521750
	float TimeOfDayVars::GetRenderDawnTime()
	{
		return renderDawnTime;
	}

	// FUNCTION: ENGINE 0x10521760
	float TimeOfDayVars::GetRenderDuskTime()
	{
		return renderDuskTime;
	}

	// FUNCTION: ENGINE 0x10521770
	float TimeOfDayVars::GetDayLength()
	{
		return dayLength;
	}

	// FUNCTION: ENGINE 0x10521780
	pure3d::Texture* TimeOfDayVars::GetCloudCover()
	{
		return cloudCover;
	}

	// FUNCTION: ENGINE 0x10521E40
	int TimeOfDayVars::GetDayGroupCount()
	{
		return dayGroups.Size();
	}

	// FUNCTION: ENGINE 0x10521E50
	core::Name<core::CaseSensitiveKey>* TimeOfDayVars::GetDayGroupName(int index)
	{
		return &dayGroups[index];
	}

	// FUNCTION: ENGINE 0x10521E60
	int TimeOfDayVars::GetGroupCount()
	{
		return groups.Size();
	}

	// FUNCTION: ENGINE 0x10521E70
	TimeOfDayVarGroup* TimeOfDayVars::GetGroup(int index)
	{
		return groups[index];
	}

	// FUNCTION: ENGINE 0x10521E80
	TimeOfDayVarGroup* TimeOfDayVars::FindGroup(const char* groupName)
	{
		TimeOfDayVarGroup* result = 0;
		for (unsigned int i = 0; i < groups.Size(); i++)
		{
			TimeOfDayVarGroup* group = groups[i];
			__declspec(align(8)) core::Name<core::CaseSensitiveKey> key(groupName, 1);
			if (group->name == key)
			{
				result = group;
				break;
			}
		}
		return result;
	}

	// FUNCTION: ENGINE 0x10521F10
	TimeOfDayVarGroup* TimeOfDayVars::FindGroup(const char* groupName) const
	{
		TimeOfDayVarGroup* result = 0;
		for (unsigned int i = 0; i < groups.Size(); i++)
		{
			TimeOfDayVarGroup* group = groups[i];
			__declspec(align(8)) core::Name<core::CaseSensitiveKey> key(groupName, 1);
			if (group->name == key)
			{
				result = group;
				break;
			}
		}
		return result;
	}

	// FUNCTION: ENGINE 0x10521FA0
	// NONMATCHING: 77 %: the engine walks the groups with a pointer it loads behind the emptiness test
#ifdef NONMATCHING
	TimeOfDayVarGroup* TimeOfDayVars::FindGroup(const core::Name<core::CaseSensitiveKey>& groupName)
	{
		TimeOfDayVarGroup* group = 0;
		unsigned int i = 0;
		if (groups.Size() != 0)
		{
			TimeOfDayVarGroup** p = groups.begin;
			do
			{
				group = *p;
				if (group->name == groupName)
				{
					return group;
				}
				i++;
				p++;
			} while (i < groups.Size());
			return 0;
		}
		return group;
	}
#endif

	// FUNCTION: ENGINE 0x10522010
	// NONMATCHING: 77 %: the same
#ifdef NONMATCHING
	TimeOfDayVarGroup* TimeOfDayVars::FindGroup(const core::Name<core::CaseSensitiveKey>& groupName) const
	{
		TimeOfDayVarGroup* group = 0;
		unsigned int i = 0;
		if (groups.Size() != 0)
		{
			TimeOfDayVarGroup** p = groups.begin;
			do
			{
				group = *p;
				if (group->name == groupName)
				{
					return group;
				}
				i++;
				p++;
			} while (i < groups.Size());
			return 0;
		}
		return group;
	}
#endif

	// FUNCTION: ENGINE 0x10522080
	TimeOfDayVariation* TimeOfDayVars::FindVariation(const char* groupName, const char* variationName)
	{
		TimeOfDayVarGroup* group = FindGroup(groupName);
		TimeOfDayVariation* result = 0;
		if (group != 0)
		{
			for (unsigned int i = 0; i < group->dayVariations.Size(); i++)
			{
				TimeOfDayVariation* variation = &group->dayVariations[i];
				__declspec(align(8)) core::Name<core::CaseSensitiveKey> key(variationName, 1);
				if (variation->name == key)
				{
					result = variation;
					break;
				}
			}
		}
		return result;
	}

	// FUNCTION: ENGINE 0x10522150
	TimeOfDayVariation* TimeOfDayVars::FindVariation(const char* groupName, const char* variationName) const
	{
		TimeOfDayVarGroup* group = FindGroup(groupName);
		TimeOfDayVariation* result = 0;
		if (group != 0)
		{
			for (unsigned int i = 0; i < group->dayVariations.Size(); i++)
			{
				TimeOfDayVariation* variation = &group->dayVariations[i];
				__declspec(align(8)) core::Name<core::CaseSensitiveKey> key(variationName, 1);
				if (variation->name == key)
				{
					result = variation;
					break;
				}
			}
		}
		return result;
	}

	// FUNCTION: ENGINE 0x10522220
	// NONMATCHING: 30 %: the same walk over the variations
#ifdef NONMATCHING
	TimeOfDayVariation* TimeOfDayVars::FindVariation(const core::Name<core::CaseSensitiveKey>& groupName,
		const core::Name<core::CaseSensitiveKey>& variationName)
	{
		TimeOfDayVarGroup* group = FindGroup(groupName);
		if (group != 0)
		{
			for (unsigned int i = 0; i < group->dayVariations.Size(); i++)
			{
				TimeOfDayVariation* variation = &group->dayVariations[i];
				if (variation->name == variationName)
				{
					return variation;
				}
			}
		}
		return 0;
	}
#endif

	// FUNCTION: ENGINE 0x105222D0
	// NONMATCHING: 30 %: the same
#ifdef NONMATCHING
	TimeOfDayVariation* TimeOfDayVars::FindVariation(const core::Name<core::CaseSensitiveKey>& groupName,
		const core::Name<core::CaseSensitiveKey>& variationName) const
	{
		TimeOfDayVarGroup* group = FindGroup(groupName);
		if (group != 0)
		{
			for (unsigned int i = 0; i < group->dayVariations.Size(); i++)
			{
				TimeOfDayVariation* variation = &group->dayVariations[i];
				if (variation->name == variationName)
				{
					return variation;
				}
			}
		}
		return 0;
	}
#endif

	// FUNCTION: ENGINE 0x10522380
	TimeOfDayLightInfo* TimeOfDayVars::GetLight(int index)
	{
		return &lights[index];
	}

	// FUNCTION: ENGINE 0x105223A0
	int TimeOfDayVars::GetLightCount()
	{
		return lights.Size();
	}


	extern const float gEighteen;

	// FUNCTION: ENGINE 0x1052C0A0
	// NONMATCHING: 75 %: the engine stores the base class's vftable and count before the first constant, ours schedules the floats first
#ifdef NONMATCHING
	TimeOfDayVars::TimeOfDayVars() : dayLength(300.0f), dawnTime(6.0f), duskTime(gEighteen), renderDawnTime(9.0f),
		renderDuskTime(16.0f), cloudCover(0)
	{
		inventory = new content::LoadInventory(0x20);
		inventory->AddRef();
	}
#endif

	// FUNCTION: ENGINE 0x1052C190
	TimeOfDayVars::~TimeOfDayVars()
	{
		inventory->Release();
		core::SafeRelease(cloudCover);
	}


	// FUNCTION: ENGINE 0x105230D0
	inline TimeOfDayLightInfo& TimeOfDayLightInfo::operator=(const TimeOfDayLightInfo& other)
	{
		name = other.name;
		handle = other.handle;
		userData = other.userData;
		unknown10 = other.unknown10;
		return *this;
	}

	// FUNCTION: ENGINE 0x10523130
	inline TimeOfDayLightInfo::TimeOfDayLightInfo(const TimeOfDayLightInfo& other) : name(other.name), handle(other.handle)
	{
		userData = 0;
		unknown10 = other.unknown10;
		core::RefAssign(userData, other.userData);
	}


	// FUNCTION: ENGINE 0x10523A50
	void TimeOfDayVars::RemoveGroup(TimeOfDayVarGroup* group)
	{
		for (unsigned int i = 0; i < groups.Size(); i++)
		{
			if (groups[i] == group)
			{
				groups.Erase(groups.begin + i);
				return;
			}
		}
	}

	// FUNCTION: ENGINE 0x10524BD0
	void TimeOfDayVars::AddGroup(TimeOfDayVarGroup* group)
	{
		if (groups.Capacity() == groups.Size())
		{
			groups.Reserve(groups.Size() + 16);
		}
		groups.PushBack(group);
	}

	// FUNCTION: ENGINE 0x10523820
	content::MemberList* FogAreaValues::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberColourMetaType<FogAreaValues, 0>("p"), PROTO_OFFSET(FogAreaValues, darkTint), "darkTint" },
			{ content::GetMemberColourMetaType<FogAreaValues, 1>("p"), PROTO_OFFSET(FogAreaValues, lightTint), "lightTint" },
			{ content::GetMemberPrimitiveMetaType<FogAreaValues, float, 0>("p"), PROTO_OFFSET(FogAreaValues, fogTilingX), "fogTiling_x" },
			{ content::GetMemberPrimitiveMetaType<FogAreaValues, float, 1>("p"), PROTO_OFFSET(FogAreaValues, fogTilingY), "fogTiling_y" },
			{ content::GetMemberPrimitiveMetaType<FogAreaValues, float, 2>("p"), PROTO_OFFSET(FogAreaValues, speed), "speed" },
			{ content::GetMemberPrimitiveMetaType<FogAreaValues, float, 3>("p"), PROTO_OFFSET(FogAreaValues, fogFalloff), "fogFalloff" },
			{ content::GetMemberPrimitiveMetaType<FogAreaValues, float, 4>("p"), PROTO_OFFSET(FogAreaValues, falloffModifier), "falloffModifier" },
			{ content::GetMemberPrimitiveMetaType<FogAreaValues, float, 5>("p"), PROTO_OFFSET(FogAreaValues, fogVariation), "fogVariation" },
			{ content::GetMemberPrimitiveMetaType<FogAreaValues, float, 6>("p"), PROTO_OFFSET(FogAreaValues, noiseStrength), "noiseStrength" }
		};
		sList.members = sMembers;
		sList.count = 9;
		return &sList;
	}

	// FUNCTION: ENGINE 0x105248E0
	content::MemberList* TimeOfDayVarChannel<FogAreaValues>::Key::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<Key, float, 0>("p"), PROTO_OFFSET(Key, time), "time" },
			{ content::GetClassMetaType<FogAreaValues>(), PROTO_OFFSET(Key, value), "value" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x105249B0
	content::MemberList* TimeOfDayVars::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<TimeOfDayVars, float, 0>("p"), PROTO_OFFSET(TimeOfDayVars, dayLength), "dayLength" },
			{ content::GetMemberPrimitiveMetaType<TimeOfDayVars, float, 1>("p"), PROTO_OFFSET(TimeOfDayVars, dawnTime), "dawnTime" },
			{ content::GetMemberPrimitiveMetaType<TimeOfDayVars, float, 2>("p"), PROTO_OFFSET(TimeOfDayVars, duskTime), "duskTime" },
			{ content::GetMemberPrimitiveMetaType<TimeOfDayVars, float, 3>("p"), PROTO_OFFSET(TimeOfDayVars, renderDawnTime), "renderDawnTime" },
			{ content::GetMemberPrimitiveMetaType<TimeOfDayVars, float, 4>("p"), PROTO_OFFSET(TimeOfDayVars, renderDuskTime), "renderDuskTime" },
			{ content::GetMemberReferenceMetaType<TimeOfDayVars, pure3d::Texture, 0>("p"), PROTO_OFFSET(TimeOfDayVars, cloudCover), "cloudCover" },
			{ content::GetArrayDynamicMetaType<TimeOfDayVars, NameArray>(content::GetMemberNameMetaType<TimeOfDayVars, 0>(true, true, "p"), "p"),
				PROTO_OFFSET(TimeOfDayVars, dayGroups), "dayGroups" },
			{ content::GetArrayDynamicMetaType<TimeOfDayVars, LightInfoArray>(content::GetClassMetaType<TimeOfDayLightInfo>(), "p"),
				PROTO_OFFSET(TimeOfDayVars, lights), "lights" }
		};
		sList.members = sMembers;
		sList.count = 8;
		return &sList;
	}

	// FUNCTION: ENGINE 0x105292C0
	content::MemberList* TimeOfDayVarChannel<FogAreaValues>::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<TimeOfDayVarChannel<FogAreaValues>, KeyArray>(content::GetClassMetaType<Key>(), "p"),
				PROTO_OFFSET(TimeOfDayVarChannel<FogAreaValues>, keys), "keys" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1052B8B0
	content::MemberList* TimeOfDayVariation::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberNameMetaType<TimeOfDayVariation, 0>(true, true, "p"), PROTO_OFFSET(TimeOfDayVariation, name), "name" },
			{ content::GetClassMetaType<GlobalLightingRig>(), PROTO_OFFSET(TimeOfDayVariation, globalLights), "globalLights" },
			{ content::GetClassMetaType<GlobalFBEffectsRig>(), PROTO_OFFSET(TimeOfDayVariation, globalFBEffects), "globalFBEffects" },
			{ content::GetClassMetaType<GlobalShaderRig>(), PROTO_OFFSET(TimeOfDayVariation, globalShaderParams), "globalShaderParams" },
			{ content::GetClassMetaType<FogChannel>(), PROTO_OFFSET(TimeOfDayVariation, globalFogValues), "globalFogValues" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1052BFC0
	content::MemberList* TimeOfDayVarGroup::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberNameMetaType<TimeOfDayVarGroup, 0>(true, true, "p"), PROTO_OFFSET(TimeOfDayVarGroup, name), "name" },
			{ content::GetArrayDynamicMetaType<TimeOfDayVarGroup, VariationArray>(content::GetClassMetaType<TimeOfDayVariation>(), "pn"),
				PROTO_OFFSET(TimeOfDayVarGroup, dayVariations), "dayVariations" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	template class TimeOfDayVarChannel<float>;
	template class TimeOfDayVarChannel<math::Vector>;
	template class TimeOfDayVarChannel<math::Colour128>;
	template class TimeOfDayVarChannel<math::Vector2>;
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1051F4F0
// FUNCTION: ENGINE 0x1051F530
// FUNCTION: ENGINE 0x1051F540
// FUNCTION: ENGINE 0x1051F580
// FUNCTION: ENGINE 0x1051F590
// FUNCTION: ENGINE 0x1051F5A0
// FUNCTION: ENGINE 0x1051F5E0
// FUNCTION: ENGINE 0x1051F620
// FUNCTION: ENGINE 0x1051F660
// FUNCTION: ENGINE 0x1051F6A0
// FUNCTION: ENGINE 0x1051F710
// FUNCTION: ENGINE 0x1051F740
// FUNCTION: ENGINE 0x1051F760
// FUNCTION: ENGINE 0x1051F7C0
// FUNCTION: ENGINE 0x1051F7F0
// FUNCTION: ENGINE 0x1051F810
// FUNCTION: ENGINE 0x1051F830
// FUNCTION: ENGINE 0x1051F860
// FUNCTION: ENGINE 0x1051F950
// FUNCTION: ENGINE 0x1051F9B0
// FUNCTION: ENGINE 0x1051F9E0
// FUNCTION: ENGINE 0x1051FA00
// FUNCTION: ENGINE 0x1051FA10
// FUNCTION: ENGINE 0x1051FA30
// FUNCTION: ENGINE 0x1051FA50
// FUNCTION: ENGINE 0x1051FA70
// FUNCTION: ENGINE 0x1051FA90
// FUNCTION: ENGINE 0x1051FBE0
// FUNCTION: ENGINE 0x1051FC10
// FUNCTION: ENGINE 0x1051FC30
// FUNCTION: ENGINE 0x1051FC40
// FUNCTION: ENGINE 0x1051FC50
// FUNCTION: ENGINE 0x1051FC70
// FUNCTION: ENGINE 0x1051FC90
// FUNCTION: ENGINE 0x1051FCB0
// FUNCTION: ENGINE 0x1051FD70
// FUNCTION: ENGINE 0x1051FD90
// FUNCTION: ENGINE 0x1051FDC0
// FUNCTION: ENGINE 0x1051FE10
// FUNCTION: ENGINE 0x1051FE40
// FUNCTION: ENGINE 0x1051FE80
// FUNCTION: ENGINE 0x1051FF10
// FUNCTION: ENGINE 0x1051FFB0
// FUNCTION: ENGINE 0x10520050
// FUNCTION: ENGINE 0x10520130
// FUNCTION: ENGINE 0x10520210
// FUNCTION: ENGINE 0x105204B0
// FUNCTION: ENGINE 0x10520510
// FUNCTION: ENGINE 0x10520570
// FUNCTION: ENGINE 0x105205D0
// FUNCTION: ENGINE 0x10520630
// FUNCTION: ENGINE 0x10520690
// FUNCTION: ENGINE 0x10520930
// FUNCTION: ENGINE 0x10520960
// FUNCTION: ENGINE 0x10520A20
// FUNCTION: ENGINE 0x10520A50
// FUNCTION: ENGINE 0x10520AA0
// FUNCTION: ENGINE 0x10520B50
// FUNCTION: ENGINE 0x10520BC0
// FUNCTION: ENGINE 0x10520C00
// FUNCTION: ENGINE 0x10521100
// FUNCTION: ENGINE 0x105211E0
// FUNCTION: ENGINE 0x10521250
// FUNCTION: ENGINE 0x105212D0
// FUNCTION: ENGINE 0x10521320
// FUNCTION: ENGINE 0x10521370
// FUNCTION: ENGINE 0x10521490
// FUNCTION: ENGINE 0x10522A30
// FUNCTION: ENGINE 0x10522C70
// FUNCTION: ENGINE 0x10522C90
// FUNCTION: ENGINE 0x10522F60
// FUNCTION: ENGINE 0x10523390
// FUNCTION: ENGINE 0x10523650
// FUNCTION: ENGINE 0x105237C0
// FUNCTION: ENGINE 0x10523FE0
// FUNCTION: ENGINE 0x10524790
// FUNCTION: ENGINE 0x10525B30
// FUNCTION: ENGINE 0x10525B60
// FUNCTION: ENGINE 0x10525C10
// FUNCTION: ENGINE 0x10525CA0
// FUNCTION: ENGINE 0x10525CE0
// FUNCTION: ENGINE 0x10525D30
// FUNCTION: ENGINE 0x10525D90
// FUNCTION: ENGINE 0x10525E00
// FUNCTION: ENGINE 0x10525E80
// FUNCTION: ENGINE 0x10525F10
// FUNCTION: ENGINE 0x10526000
// FUNCTION: ENGINE 0x10526040
// FUNCTION: ENGINE 0x10526060
// FUNCTION: ENGINE 0x10526100
// FUNCTION: ENGINE 0x10526110
// FUNCTION: ENGINE 0x10526180
// FUNCTION: ENGINE 0x10526240
// FUNCTION: ENGINE 0x105262F0
// FUNCTION: ENGINE 0x10526340
// FUNCTION: ENGINE 0x10526370
// FUNCTION: ENGINE 0x10526460
// FUNCTION: ENGINE 0x10526510
// FUNCTION: ENGINE 0x10526550
// FUNCTION: ENGINE 0x10526660
// FUNCTION: ENGINE 0x10526780
// FUNCTION: ENGINE 0x10526860
// FUNCTION: ENGINE 0x10526950
// FUNCTION: ENGINE 0x105269D0
// FUNCTION: ENGINE 0x10526A50
// FUNCTION: ENGINE 0x10526A70
// FUNCTION: ENGINE 0x10526A80
// FUNCTION: ENGINE 0x10526AF0
// FUNCTION: ENGINE 0x10526B80
// FUNCTION: ENGINE 0x10527010
// FUNCTION: ENGINE 0x10527090
// FUNCTION: ENGINE 0x105270D0
// FUNCTION: ENGINE 0x10527230
// FUNCTION: ENGINE 0x10527260
// FUNCTION: ENGINE 0x10527470
// FUNCTION: ENGINE 0x10527530
// FUNCTION: ENGINE 0x10527920
// FUNCTION: ENGINE 0x10527940
// FUNCTION: ENGINE 0x10527950
// FUNCTION: ENGINE 0x105279C0
// FUNCTION: ENGINE 0x10527A10
// FUNCTION: ENGINE 0x10527AD0
// FUNCTION: ENGINE 0x10527C30
// FUNCTION: ENGINE 0x10527D70
// FUNCTION: ENGINE 0x105281D0
// FUNCTION: ENGINE 0x10528750
// FUNCTION: ENGINE 0x10528DC0
// FUNCTION: ENGINE 0x10528EB0
// FUNCTION: ENGINE 0x10529130
// FUNCTION: ENGINE 0x10529190
// FUNCTION: ENGINE 0x10529580
// FUNCTION: ENGINE 0x105295B0
// FUNCTION: ENGINE 0x105295E0
// FUNCTION: ENGINE 0x10529610
// FUNCTION: ENGINE 0x10529640
// FUNCTION: ENGINE 0x105297E0
// FUNCTION: ENGINE 0x10529860
// FUNCTION: ENGINE 0x10529900
// FUNCTION: ENGINE 0x10529CF0
// FUNCTION: ENGINE 0x10529D10
// FUNCTION: ENGINE 0x10529DD0
// FUNCTION: ENGINE 0x10529DE0
// FUNCTION: ENGINE 0x1052A460
// FUNCTION: ENGINE 0x1052A4B0
// FUNCTION: ENGINE 0x1052A500
// FUNCTION: ENGINE 0x1052A550
// FUNCTION: ENGINE 0x1052AAE0
// FUNCTION: ENGINE 0x1052AB30
// FUNCTION: ENGINE 0x1052B530
// FUNCTION: ENGINE 0x1052B5A0
// FUNCTION: ENGINE 0x1052BF00
// FUNCTION: ENGINE 0x1052BF10
// FUNCTION: ENGINE 0x1052BF20
// FUNCTION: ENGINE 0x1052C7E0
// FUNCTION: ENGINE 0x1052C8E0
// FUNCTION: ENGINE 0x1052CA50
// FUNCTION: ENGINE 0x1052D740
// FUNCTION: ENGINE 0x1052D770
// FUNCTION: ENGINE 0x1052D7B0
// FUNCTION: ENGINE 0x1052D9D0
// FUNCTION: ENGINE 0x1052DAB0
// FUNCTION: ENGINE 0x1052DBE0
// FUNCTION: ENGINE 0x10521AE0
// FUNCTION: ENGINE 0x10521B20
// FUNCTION: ENGINE 0x10521B80
// FUNCTION: ENGINE 0x10521BC0
// FUNCTION: ENGINE 0x10521C40
// FUNCTION: ENGINE 0x10521C90
// FUNCTION: ENGINE 0x10522590
// FUNCTION: ENGINE 0x105225D0
// FUNCTION: ENGINE 0x10522610
// FUNCTION: ENGINE 0x10522650
// FUNCTION: ENGINE 0x10522690
// FUNCTION: ENGINE 0x105226D0
// FUNCTION: ENGINE 0x10522710
// FUNCTION: ENGINE 0x10522750
// FUNCTION: ENGINE 0x10522790
// FUNCTION: ENGINE 0x105227D0
// FUNCTION: ENGINE 0x10522810
// FUNCTION: ENGINE 0x10522850
// FUNCTION: ENGINE 0x10522890
// FUNCTION: ENGINE 0x1052EA30
// FUNCTION: ENGINE 0x1052F1D0
// FUNCTION: ENGINE 0x10521B60
// FUNCTION: ENGINE 0x10521B70
// FUNCTION: ENGINE 0x10521C00
// FUNCTION: ENGINE 0x10521C10
// FUNCTION: ENGINE 0x10521C20
// FUNCTION: ENGINE 0x10521C30
// FUNCTION: ENGINE 0x10521C80
// FUNCTION: ENGINE 0x10521CD0
// FUNCTION: ENGINE 0x105218B0
// FUNCTION: ENGINE 0x10521910
// FUNCTION: ENGINE 0x10521970
// FUNCTION: ENGINE 0x105224D0
// FUNCTION: ENGINE 0x10523D30
// FUNCTION: ENGINE 0x105253F0
// FUNCTION: ENGINE 0x10529440
// FUNCTION: ENGINE 0x1052BA60
// FUNCTION: ENGINE 0x10523DD0
// FUNCTION: ENGINE 0x10523E30
// FUNCTION: ENGINE 0x10523EF0
// FUNCTION: ENGINE 0x10523F50
// FUNCTION: ENGINE 0x10523E90
// FUNCTION: ENGINE 0x10521830
// FUNCTION: ENGINE 0x10521790
// FUNCTION: ENGINE 0x10521800
// FUNCTION: ENGINE 0x10521D90
// FUNCTION: ENGINE 0x10523080
// FUNCTION: ENGINE 0x10523020
// FUNCTION: ENGINE 0x10523100
// FUNCTION: ENGINE 0x10522FD0
// FUNCTION: ENGINE 0x10523210
// FUNCTION: ENGINE 0x10523280
// FUNCTION: ENGINE 0x105229C0
// FUNCTION: ENGINE 0x10522940
// FUNCTION: ENGINE 0x105229A0
// FUNCTION: ENGINE 0x10522D80
// FUNCTION: ENGINE 0x10522D20
// FUNCTION: ENGINE 0x10522CB0
// FUNCTION: ENGINE 0x105231C0
// FUNCTION: ENGINE 0x10523520
// FUNCTION: ENGINE 0x10524210
// FUNCTION: ENGINE 0x10524240
// FUNCTION: ENGINE 0x105243C0
// FUNCTION: ENGINE 0x105242E0
// FUNCTION: ENGINE 0x10529420
// FUNCTION: ENGINE 0x10525740
// FUNCTION: ENGINE 0x105257E0
// FUNCTION: ENGINE 0x10525590
// FUNCTION: ENGINE 0x10529530
// FUNCTION: ENGINE 0x1052BA40
// FUNCTION: ENGINE 0x105256F0
// FUNCTION: ENGINE 0x1052A690
// FUNCTION: ENGINE 0x1052A830
// FUNCTION: ENGINE 0x1052C390
// FUNCTION: ENGINE 0x1052C410
// FUNCTION: ENGINE 0x1052BB90
// FUNCTION: ENGINE 0x1052BF40
// FUNCTION: ENGINE 0x1052D680
// FUNCTION: ENGINE 0x1052D6F0
// FUNCTION: ENGINE 0x10522D00
// FUNCTION: ENGINE 0x10522CE0
// FUNCTION: ENGINE 0x105231F0
// FUNCTION: ENGINE 0x10523000
// FUNCTION: ENGINE 0x10522980
// FUNCTION: ENGINE 0x10522960
// FUNCTION: ENGINE 0x1052CCD0
// FUNCTION: ENGINE 0x1052C720
// FUNCTION: ENGINE 0x105228D0
// FUNCTION: ENGINE 0x10522A20
// FUNCTION: ENGINE 0x10522FC0
// FUNCTION: ENGINE 0x105217B0
// FUNCTION: ENGINE 0x10521850
// FUNCTION: ENGINE 0x105263B0
// FUNCTION: ENGINE 0x10525B80
// FUNCTION: ENGINE 0x10527280
// FUNCTION: ENGINE 0x10529660
// FUNCTION: ENGINE 0x105263D0
// FUNCTION: ENGINE 0x105272A0
// FUNCTION: ENGINE 0x10525BA0
// FUNCTION: ENGINE 0x105264F0
// FUNCTION: ENGINE 0x10526500
// FUNCTION: ENGINE 0x105273F0
// FUNCTION: ENGINE 0x10527400
// FUNCTION: ENGINE 0x10525C80
// FUNCTION: ENGINE 0x10525C90
// FUNCTION: ENGINE 0x105254B0
// FUNCTION: ENGINE 0x10525490
// FUNCTION: ENGINE 0x10525450
// FUNCTION: ENGINE 0x10525470
// FUNCTION: ENGINE 0x10526710
// FUNCTION: ENGINE 0x10524300
// FUNCTION: ENGINE 0x105254D0
// FUNCTION: ENGINE 0x105255F0
// FUNCTION: ENGINE 0x105294A0
// FUNCTION: ENGINE 0x1052BA10
// FUNCTION: ENGINE 0x105217F0
// FUNCTION: ENGINE 0x105223D0
// FUNCTION: ENGINE 0x10523C70
// FUNCTION: ENGINE 0x10522E00
// FUNCTION: ENGINE 0x10523720
// FUNCTION: ENGINE 0x10522F20
// FUNCTION: ENGINE 0x10522400
// FUNCTION: ENGINE 0x1052E680
// FUNCTION: ENGINE 0x1053DEA0
// FUNCTION: ENGINE 0x1053DF70
// FUNCTION: ENGINE 0x1053E030
// FUNCTION: ENGINE 0x1053EE50
// FUNCTION: ENGINE 0x1053EE90
// FUNCTION: ENGINE 0x1053EED0
// FUNCTION: ENGINE 0x105306E0
// FUNCTION: ENGINE 0x10524470
// FUNCTION: ENGINE 0x105245E0
// FUNCTION: ENGINE 0x10523550
// FUNCTION: ENGINE 0x105339E0
// FUNCTION: ENGINE 0x1053C3C0
// FUNCTION: ENGINE 0x1053CC20
// FUNCTION: ENGINE 0x105206F0
// FUNCTION: ENGINE 0x10520E70
// FUNCTION: ENGINE 0x10528200
// FUNCTION: ENGINE 0x10528DF0
// FUNCTION: ENGINE 0x105236E0
// FUNCTION: ENGINE 0x10523780
// FUNCTION: ENGINE 0x10524820
// FUNCTION: ENGINE 0x10524880
// FUNCTION: ENGINE 0x1052F0D0
// FUNCTION: ENGINE 0x10530050
// FUNCTION: ENGINE 0x1052F180
// FUNCTION: ENGINE 0x105300D0
// FUNCTION: ENGINE 0x105326D0
// FUNCTION: ENGINE 0x105336E0
// FUNCTION: ENGINE 0x10532790
// FUNCTION: ENGINE 0x105337A0
// FUNCTION: ENGINE 0x10522A40
// FUNCTION: ENGINE 0x10522AB0
// FUNCTION: ENGINE 0x10522B20
// FUNCTION: ENGINE 0x10522B90
// FUNCTION: ENGINE 0x10522AA0
// FUNCTION: ENGINE 0x10522B10
// FUNCTION: ENGINE 0x10522B80
// FUNCTION: ENGINE 0x10522BF0
// FUNCTION: ENGINE 0x1053DD30
// FUNCTION: ENGINE 0x1052E520
// FUNCTION: ENGINE 0x1052E5C0
// FUNCTION: ENGINE 0x1052E730
// FUNCTION: ENGINE 0x105259C0
// FUNCTION: ENGINE 0x10530880
// FUNCTION: ENGINE 0x105337F0
// FUNCTION: ENGINE 0x105394F0
// FUNCTION: ENGINE 0x1052E970
// FUNCTION: ENGINE 0x1052E9B0
// FUNCTION: ENGINE 0x1052EA10
// FUNCTION: ENGINE 0x1052EA50
// FUNCTION: ENGINE 0x1053E6F0
// FUNCTION: ENGINE 0x1053E770
// FUNCTION: ENGINE 0x1053E7E0
// FUNCTION: ENGINE 0x1053E840
// FUNCTION: ENGINE 0x105335C0
// FUNCTION: ENGINE 0x105335E0
// FUNCTION: ENGINE 0x10533600
// FUNCTION: ENGINE 0x10533620
// FUNCTION: ENGINE 0x1052CEE0
// FUNCTION: ENGINE 0x105228E0
// FUNCTION: ENGINE 0x10523450
// FUNCTION: ENGINE 0x105234B0
// FUNCTION: ENGINE 0x105258A0
// FUNCTION: ENGINE 0x1052A6E0
// FUNCTION: ENGINE 0x1052A880
// FUNCTION: ENGINE 0x105230b0
// FUNCTION: ENGINE 0x10521a50
// FUNCTION: ENGINE 0x105217d0
// FUNCTION: ENGINE 0x10526390
// FUNCTION: ENGINE 0x105201c0
// FUNCTION: ENGINE 0x10521190
// FUNCTION: ENGINE 0x105200f0
// FUNCTION: ENGINE 0x10523400
// FUNCTION: ENGINE 0x1052bc40
// FUNCTION: ENGINE 0x10525780
// FUNCTION: ENGINE 0x1052ab10
// FUNCTION: ENGINE 0x1052c590
// FUNCTION: ENGINE 0x1052AB50
// FUNCTION: ENGINE 0x10523C50
// FUNCTION: ENGINE 0x10520010
// FUNCTION: ENGINE 0x105200B0
// FUNCTION: ENGINE 0x10520AF0
// FUNCTION: ENGINE 0x105265D0
// FUNCTION: ENGINE 0x105274C0
