#include "code/engine/controller/characterintentioninputmap.h"

namespace engine
{
	typedef CharacterIntentionInputMap Map;

	// GLOBAL: ENGINE 0x1130CD08
	Map::NameTable Map::sNameTables[3];
	// GLOBAL: ENGINE 0x111C308C
	int Map::sNextSerial = 1;

	// FUNCTION: ENGINE 0x108217C0
	content::ClassInfo* Map::ButtonMapEntry::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::CharacterIntentionInputMap::ButtonMapEntry";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10821800
	content::ClassInfo* Map::ButtonPairToAxisMapEntry::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::CharacterIntentionInputMap::ButtonPairToAxisMapEntry";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10821840
	content::ClassInfo* Map::AxisMapEntry::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::CharacterIntentionInputMap::AxisMapEntry";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10821880
	content::ClassInfo* Map::AxisToButtonMapEntry::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::CharacterIntentionInputMap::AxisToButtonMapEntry";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x108218C0
	content::ClassInfo* Map::AxisPairToButtonMapEntry::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::CharacterIntentionInputMap::AxisPairToButtonMapEntry";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10821900
	content::ClassInfo* Map::PlayerSpaceTranslationMapEntry::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::CharacterIntentionInputMap::PlayerSpaceTranslationMapEntry";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10821940
	content::ClassInfo* Map::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "CharacterIntentionInputMap";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10822480
	Map::ButtonMapEntry::ButtonMapEntry() : button(controller::BUTTON_NONE), index(-1)
	{
	}

	// FUNCTION: ENGINE 0x108224A0
	Map::ButtonPairToAxisMapEntry::ButtonPairToAxisMapEntry()
		: negative(controller::BUTTON_NONE), positive(controller::BUTTON_NONE), index(-1)
	{
	}

	// FUNCTION: ENGINE 0x108224D0
	Map::AxisMapEntry::AxisMapEntry() : axis(controller::AXIS_NONE), index(-1), invert(false)
	{
	}

	// FUNCTION: ENGINE 0x108224F0
	Map::AxisToButtonMapEntry::AxisToButtonMapEntry() : axis(controller::AXIS_NONE), index(-1), direction(1.0f)
	{
	}

	// FUNCTION: ENGINE 0x10822520
	Map::AxisPairToButtonMapEntry::AxisPairToButtonMapEntry()
		: x(controller::AXIS_NONE), y(controller::AXIS_NONE), index(-1)
	{
	}

	// FUNCTION: ENGINE 0x10822550
	Map::PlayerSpaceTranslationMapEntry::PlayerSpaceTranslationMapEntry()
		: x(controller::AXIS_NONE), y(controller::AXIS_NONE), indexX(-1), invertX(false), invertY(false)
	{
		indexY = -1;
	}

#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define ENGINE_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10822220
	content::MemberList* Map::ButtonMapEntry::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetEnumMetaType<controller::ControllerButton>(), 0, "in" },
			{ content::GetNameMetaType<ButtonMapEntry>(true, true, "pn"), ENGINE_NAME_OFFSET(ButtonMapEntry, name), "out" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x108222C0
	content::MemberList* Map::ButtonPairToAxisMapEntry::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetEnumMetaType<controller::ControllerButton>(), 0, "in1" },
			{ content::GetEnumMetaType<controller::ControllerButton>(), 4, "in2" },
			{ content::GetNameMetaType<ButtonPairToAxisMapEntry>(true, true, "pn"),
				ENGINE_NAME_OFFSET(ButtonPairToAxisMapEntry, name), "out" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10822380
	content::MemberList* Map::AxisPairToButtonMapEntry::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetEnumMetaType<controller::ControllerAxis>(), 0, "inX" },
			{ content::GetEnumMetaType<controller::ControllerAxis>(), 4, "inY" },
			{ content::GetNameMetaType<AxisPairToButtonMapEntry>(true, true, "pn"),
				ENGINE_NAME_OFFSET(AxisPairToButtonMapEntry, name), "out" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10823590
	content::MemberList* Map::AxisMapEntry::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetEnumMetaType<controller::ControllerAxis>(), 0, "in" },
			{ content::GetNameMetaType<AxisMapEntry>(true, true, "pn"), ENGINE_NAME_OFFSET(AxisMapEntry, name), "out" },
			{ content::GetMemberPrimitiveMetaType<AxisMapEntry, bool, 0>("pn"), ENGINE_OFFSET(AxisMapEntry, invert),
				"invert" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10823660
	content::MemberList* Map::AxisToButtonMapEntry::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetEnumMetaType<controller::ControllerAxis>(), 0, "in" },
			{ content::GetNameMetaType<AxisToButtonMapEntry>(true, true, "pn"), ENGINE_NAME_OFFSET(AxisToButtonMapEntry, name),
				"out" },
			{ content::GetMemberPrimitiveMetaType<AxisToButtonMapEntry, float, 0>("pn"),
				ENGINE_OFFSET(AxisToButtonMapEntry, direction), "direction" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10823730
	content::MemberList* Map::PlayerSpaceTranslationMapEntry::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetEnumMetaType<controller::ControllerAxis>(), 0, "inX" },
			{ content::GetEnumMetaType<controller::ControllerAxis>(), 4, "inY" },
			{ content::GetNameMetaType<PlayerSpaceTranslationMapEntry>(true, true, "pn"),
				ENGINE_NAME_OFFSET(PlayerSpaceTranslationMapEntry, nameX), "outX" },
			{ content::GetNameMetaType<core::Name<core::CaseSensitiveKey> >(true, true, "pn"),
				ENGINE_NAME_OFFSET(PlayerSpaceTranslationMapEntry, nameY), "outY" },
			{ content::GetMemberPrimitiveMetaType<PlayerSpaceTranslationMapEntry, bool, 1>("pn"),
				ENGINE_OFFSET(PlayerSpaceTranslationMapEntry, invertX), "invertX" },
			{ content::GetMemberPrimitiveMetaType<PlayerSpaceTranslationMapEntry, bool, 2>("pn"),
				ENGINE_OFFSET(PlayerSpaceTranslationMapEntry, invertY), "invertY" }
		};
		sList.members = sMembers;
		sList.count = 6;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10824380
	content::MemberList* Map::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<Map, unsigned char, 0>("pn"), ENGINE_OFFSET(Map, playerIndex),
				"index" },
			{ content::GetArrayDynamicMetaType<Map, ButtonMapArray>(content::GetClassMetaType<ButtonMapEntry>(), "pn"),
				ENGINE_OFFSET(Map, buttonMap), "buttonMap" },
			{ content::GetArrayDynamicMetaType<Map, ButtonPairToAxisMapArray>(
				content::GetClassMetaType<ButtonPairToAxisMapEntry>(), "pn"),
				ENGINE_OFFSET(Map, buttonPairToAxisMap), "buttonPairToAxisMap" },
			{ content::GetArrayDynamicMetaType<Map, AxisMapArray>(content::GetClassMetaType<AxisMapEntry>(), "pn"),
				ENGINE_OFFSET(Map, axisMap), "axisMap" },
			{ content::GetArrayDynamicMetaType<Map, AxisToButtonMapArray>(
				content::GetClassMetaType<AxisToButtonMapEntry>(), "pn"),
				ENGINE_OFFSET(Map, axisToButtonMap), "axisToButtonMap" },
			{ content::GetArrayDynamicMetaType<Map, AxisPairToButtonMapArray>(
				content::GetClassMetaType<AxisPairToButtonMapEntry>(), "pn"),
				ENGINE_OFFSET(Map, axisPairToButtonMap), "axisPairToButtonMap" },
			{ content::GetArrayDynamicMetaType<Map, PlayerSpaceTranslationMapArray>(
				content::GetClassMetaType<PlayerSpaceTranslationMapEntry>(), "pn"),
				ENGINE_OFFSET(Map, playerSpaceTranslationMap), "playerSpaceTranslationMap" }
		};
		sList.members = sMembers;
		sList.count = 7;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10822440
	unsigned int Map::FindNameIndex(core::Name<core::CaseSensitiveKey> name, unsigned int count,
		const core::Name<core::CaseSensitiveKey>* names, unsigned int unused)
	{
		for (unsigned int i = 0; i < count; i++)
		{
			if (name == names[i])
			{
				return i;
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10823870
	void Map::ResolveNames(unsigned int buttonCount, const core::Name<core::CaseSensitiveKey>* buttonNames,
		unsigned int buttonUnknown, unsigned int axisCount, const core::Name<core::CaseSensitiveKey>* axisNames,
		unsigned int axisUnknown)
	{
		for (ButtonMapEntry* entry = buttonMap.Begin(), *last = buttonMap.End(); entry != last; entry++)
		{
			entry->index = FindNameIndex(entry->name, buttonCount, buttonNames, buttonUnknown);
		}
		for (ButtonPairToAxisMapEntry* entry = buttonPairToAxisMap.Begin(), *last = buttonPairToAxisMap.End();
			entry != last; entry++)
		{
			entry->index = FindNameIndex(entry->name, axisCount, axisNames, axisUnknown);
		}
		for (AxisMapEntry* entry = axisMap.Begin(), *last = axisMap.End(); entry != last; entry++)
		{
			entry->index = FindNameIndex(entry->name, axisCount, axisNames, axisUnknown);
		}
		for (AxisToButtonMapEntry* entry = axisToButtonMap.Begin(), *last = axisToButtonMap.End(); entry != last;
			entry++)
		{
			entry->index = FindNameIndex(entry->name, buttonCount, buttonNames, buttonUnknown);
		}
		for (AxisPairToButtonMapEntry* entry = axisPairToButtonMap.Begin(), *last = axisPairToButtonMap.End();
			entry != last; entry++)
		{
			entry->index = FindNameIndex(entry->name, buttonCount, buttonNames, buttonUnknown);
		}
		for (PlayerSpaceTranslationMapEntry* entry = playerSpaceTranslationMap.Begin(),
			*last = playerSpaceTranslationMap.End(); entry != last; entry++)
		{
			entry->indexX = FindNameIndex(entry->nameX, axisCount, axisNames, axisUnknown);
			entry->indexY = FindNameIndex(entry->nameY, axisCount, axisNames, axisUnknown);
		}
		resolved = true;
	}

	// FUNCTION: ENGINE 0x10824520
	void Map::Slot3(int unused)
	{
		ResolveNames(sNameTables[0].count, sNameTables[0].names, sNameTables[0].unknown, sNameTables[1].count,
			sNameTables[1].names, sNameTables[1].unknown);
		if (playerIndex < 8)
		{
			SetPlayerIntentionMap(this, playerIndex);
		}
	}

	// FUNCTION: ENGINE 0x10821980
	bool Map::IsReady()
	{
		if (playerIndex < 8)
		{
			if (GetPlayerIntentionMap(playerIndex) == this)
			{
				SetPlayerIntentionMap(0, playerIndex);
			}
		}
		return true;
	}

	// FUNCTION: ENGINE 0x108219B0
	void Map::SetNameTables(unsigned int buttonCount, const core::Name<core::CaseSensitiveKey>* buttonNames,
		unsigned int buttonUnknown, unsigned int axisCount, const core::Name<core::CaseSensitiveKey>* axisNames,
		unsigned int axisUnknown, unsigned int thirdCount, const core::Name<core::CaseSensitiveKey>* thirdNames,
		unsigned int thirdUnknown)
	{
		sNameTables[0].count = buttonCount;
		sNameTables[0].names = buttonNames;
		sNameTables[0].unknown = buttonUnknown;
		sNameTables[1].count = axisCount;
		sNameTables[1].names = axisNames;
		sNameTables[1].unknown = axisUnknown;
		sNameTables[2].count = thirdCount;
		sNameTables[2].names = thirdNames;
		sNameTables[2].unknown = thirdUnknown;
	}

	// FUNCTION: ENGINE 0x10821A10
	unsigned int Map::GetButtonCount()
	{
		return sNameTables[0].count;
	}

	// FUNCTION: ENGINE 0x10821A20
	const core::Name<core::CaseSensitiveKey>* Map::GetButtonNames()
	{
		return sNameTables[0].names;
	}

	// FUNCTION: ENGINE 0x10821A30
	unsigned int Map::GetButtonUnknown()
	{
		return sNameTables[0].unknown;
	}

	// FUNCTION: ENGINE 0x10821A40
	unsigned int Map::GetAxisCount()
	{
		return sNameTables[1].count;
	}

	// FUNCTION: ENGINE 0x10821A50
	const core::Name<core::CaseSensitiveKey>* Map::GetAxisNames()
	{
		return sNameTables[1].names;
	}

	// FUNCTION: ENGINE 0x10821A60
	unsigned int Map::GetAxisUnknown()
	{
		return sNameTables[1].unknown;
	}

	// FUNCTION: ENGINE 0x10821A70
	unsigned int Map::GetThirdCount()
	{
		return sNameTables[2].count;
	}

	// FUNCTION: ENGINE 0x10821A80
	const core::Name<core::CaseSensitiveKey>* Map::GetThirdNames()
	{
		return sNameTables[2].names;
	}

	// FUNCTION: ENGINE 0x10821A90
	unsigned int Map::GetThirdUnknown()
	{
		return sNameTables[2].unknown;
	}

	// FUNCTION: ENGINE 0x108253C0
	Map::CharacterIntentionInputMap() : serial(sNextSerial++), playerIndex(0), resolved(false)
	{
	}

	// FUNCTION: ENGINE 0x10825420
	Map::~CharacterIntentionInputMap()
	{
	}

}

namespace container
{
	template class ArrayDynamic<engine::CharacterIntentionInputMap::ButtonMapEntry, AllocatorNew>;
	template class ArrayDynamic<engine::CharacterIntentionInputMap::ButtonPairToAxisMapEntry, AllocatorNew>;
	template class ArrayDynamic<engine::CharacterIntentionInputMap::AxisMapEntry, AllocatorNew>;
	template class ArrayDynamic<engine::CharacterIntentionInputMap::AxisToButtonMapEntry, AllocatorNew>;
	template class ArrayDynamic<engine::CharacterIntentionInputMap::AxisPairToButtonMapEntry, AllocatorNew>;
	template class ArrayDynamic<engine::CharacterIntentionInputMap::PlayerSpaceTranslationMapEntry, AllocatorNew>;
}
// the default elements the reflection inserts into the arrays, kept as the engine kept them
template engine::CharacterIntentionInputMap::ButtonMapEntry& content::ArrayDynamicHelper<
	engine::CharacterIntentionInputMap::ButtonMapArray>::Default();
template engine::CharacterIntentionInputMap::ButtonPairToAxisMapEntry& content::ArrayDynamicHelper<
	engine::CharacterIntentionInputMap::ButtonPairToAxisMapArray>::Default();
template engine::CharacterIntentionInputMap::AxisMapEntry& content::ArrayDynamicHelper<
	engine::CharacterIntentionInputMap::AxisMapArray>::Default();
template engine::CharacterIntentionInputMap::AxisToButtonMapEntry& content::ArrayDynamicHelper<
	engine::CharacterIntentionInputMap::AxisToButtonMapArray>::Default();
template engine::CharacterIntentionInputMap::AxisPairToButtonMapEntry& content::ArrayDynamicHelper<
	engine::CharacterIntentionInputMap::AxisPairToButtonMapArray>::Default();
template engine::CharacterIntentionInputMap::PlayerSpaceTranslationMapEntry& content::ArrayDynamicHelper<
	engine::CharacterIntentionInputMap::PlayerSpaceTranslationMapArray>::Default();

// Kept copies: the explicitly instantiated members of the entry arrays and their reflection helpers, the entries
// copies, the reflection meta type getters and the default elements
// FUNCTION: ENGINE 0x10821AA0
// FUNCTION: ENGINE 0x10821AB0
// FUNCTION: ENGINE 0x10821AC0
// FUNCTION: ENGINE 0x10821AD0
// FUNCTION: ENGINE 0x10821AE0
// FUNCTION: ENGINE 0x10821AF0
// FUNCTION: ENGINE 0x10821B00
// FUNCTION: ENGINE 0x10821B10
// FUNCTION: ENGINE 0x10821B20
// FUNCTION: ENGINE 0x10821B30
// FUNCTION: ENGINE 0x10821B40
// FUNCTION: ENGINE 0x10821B50
// FUNCTION: ENGINE 0x10821B60
// FUNCTION: ENGINE 0x10821BC0
// FUNCTION: ENGINE 0x10821C20
// FUNCTION: ENGINE 0x10821C90
// FUNCTION: ENGINE 0x10821D00
// FUNCTION: ENGINE 0x10821D70
// FUNCTION: ENGINE 0x10821DE0
// FUNCTION: ENGINE 0x10821E50
// FUNCTION: ENGINE 0x10821ED0
// FUNCTION: ENGINE 0x10821F10
// FUNCTION: ENGINE 0x10821F60
// FUNCTION: ENGINE 0x10821FA0
// FUNCTION: ENGINE 0x10821FE0
// FUNCTION: ENGINE 0x10822020
// FUNCTION: ENGINE 0x10822060
// FUNCTION: ENGINE 0x108220A0
// FUNCTION: ENGINE 0x108220B0
// FUNCTION: ENGINE 0x108220C0
// FUNCTION: ENGINE 0x108220D0
// FUNCTION: ENGINE 0x108220E0
// FUNCTION: ENGINE 0x108220F0
// FUNCTION: ENGINE 0x10822590
// FUNCTION: ENGINE 0x108225A0
// FUNCTION: ENGINE 0x108225B0
// FUNCTION: ENGINE 0x108225C0
// FUNCTION: ENGINE 0x108225D0
// FUNCTION: ENGINE 0x108225E0
// FUNCTION: ENGINE 0x108225F0
// FUNCTION: ENGINE 0x10822640
// FUNCTION: ENGINE 0x10822690
// FUNCTION: ENGINE 0x108226E0
// FUNCTION: ENGINE 0x10822720
// FUNCTION: ENGINE 0x10822760
// FUNCTION: ENGINE 0x108227A0
// FUNCTION: ENGINE 0x108227E0
// FUNCTION: ENGINE 0x10822820
// FUNCTION: ENGINE 0x10822830
// FUNCTION: ENGINE 0x10822880
// FUNCTION: ENGINE 0x108228A0
// FUNCTION: ENGINE 0x108228C0
// FUNCTION: ENGINE 0x108228D0
// FUNCTION: ENGINE 0x108228E0
// FUNCTION: ENGINE 0x10822910
// FUNCTION: ENGINE 0x10822920
// FUNCTION: ENGINE 0x10822970
// FUNCTION: ENGINE 0x10822990
// FUNCTION: ENGINE 0x108229B0
// FUNCTION: ENGINE 0x108229C0
// FUNCTION: ENGINE 0x108229D0
// FUNCTION: ENGINE 0x10822A00
// FUNCTION: ENGINE 0x10822A10
// FUNCTION: ENGINE 0x10822A60
// FUNCTION: ENGINE 0x10822A80
// FUNCTION: ENGINE 0x10822AA0
// FUNCTION: ENGINE 0x10822AB0
// FUNCTION: ENGINE 0x10822AC0
// FUNCTION: ENGINE 0x10822AF0
// FUNCTION: ENGINE 0x10822B00
// FUNCTION: ENGINE 0x10822B50
// FUNCTION: ENGINE 0x10822B70
// FUNCTION: ENGINE 0x10822B90
// FUNCTION: ENGINE 0x10822BA0
// FUNCTION: ENGINE 0x10822BB0
// FUNCTION: ENGINE 0x10822BE0
// FUNCTION: ENGINE 0x10822BF0
// FUNCTION: ENGINE 0x10822C40
// FUNCTION: ENGINE 0x10822C60
// FUNCTION: ENGINE 0x10822C80
// FUNCTION: ENGINE 0x10822C90
// FUNCTION: ENGINE 0x10822CA0
// FUNCTION: ENGINE 0x10822CD0
// FUNCTION: ENGINE 0x10822CE0
// FUNCTION: ENGINE 0x10822D30
// FUNCTION: ENGINE 0x10822D50
// FUNCTION: ENGINE 0x10822D70
// FUNCTION: ENGINE 0x10822D80
// FUNCTION: ENGINE 0x10822D90
// FUNCTION: ENGINE 0x10822DE0
// FUNCTION: ENGINE 0x10822E00
// FUNCTION: ENGINE 0x10822E20
// FUNCTION: ENGINE 0x10822E40
// FUNCTION: ENGINE 0x10822E60
// FUNCTION: ENGINE 0x10822E80
// FUNCTION: ENGINE 0x10822EA0
// FUNCTION: ENGINE 0x10822EC0
// FUNCTION: ENGINE 0x10822EE0
// FUNCTION: ENGINE 0x10822F00
// FUNCTION: ENGINE 0x10822F20
// FUNCTION: ENGINE 0x10822F40
// FUNCTION: ENGINE 0x10822F60
// FUNCTION: ENGINE 0x10822F80
// FUNCTION: ENGINE 0x10822FA0
// FUNCTION: ENGINE 0x10822FC0
// FUNCTION: ENGINE 0x10822FE0
// FUNCTION: ENGINE 0x10823000
// FUNCTION: ENGINE 0x10823020
// FUNCTION: ENGINE 0x10823040
// FUNCTION: ENGINE 0x10823060
// FUNCTION: ENGINE 0x10823080
// FUNCTION: ENGINE 0x108230A0
// FUNCTION: ENGINE 0x108230C0
// FUNCTION: ENGINE 0x10823140
// FUNCTION: ENGINE 0x10823170
// FUNCTION: ENGINE 0x108231A0
// FUNCTION: ENGINE 0x108231D0
// FUNCTION: ENGINE 0x10823200
// FUNCTION: ENGINE 0x10823230
// FUNCTION: ENGINE 0x10823250
// FUNCTION: ENGINE 0x108232A0
// FUNCTION: ENGINE 0x108232F0
// FUNCTION: ENGINE 0x10823340
// FUNCTION: ENGINE 0x10823390
// FUNCTION: ENGINE 0x108233E0
// FUNCTION: ENGINE 0x10823450
// FUNCTION: ENGINE 0x10823480
// FUNCTION: ENGINE 0x108234B0
// FUNCTION: ENGINE 0x108234E0
// FUNCTION: ENGINE 0x10823510
// FUNCTION: ENGINE 0x10823540
// FUNCTION: ENGINE 0x10823A20
// FUNCTION: ENGINE 0x10823A70
// FUNCTION: ENGINE 0x10823AC0
// FUNCTION: ENGINE 0x10823B10
// FUNCTION: ENGINE 0x10823B60
// FUNCTION: ENGINE 0x10823BB0
// FUNCTION: ENGINE 0x10823C00
// FUNCTION: ENGINE 0x10823C50
// FUNCTION: ENGINE 0x10823CA0
// FUNCTION: ENGINE 0x10823D50
// FUNCTION: ENGINE 0x10823D80
// FUNCTION: ENGINE 0x10823DB0
// FUNCTION: ENGINE 0x10823DE0
// FUNCTION: ENGINE 0x10823E10
// FUNCTION: ENGINE 0x10823E40
// FUNCTION: ENGINE 0x10823E70
// FUNCTION: ENGINE 0x10823EA0
// FUNCTION: ENGINE 0x10823ED0
// FUNCTION: ENGINE 0x10823F00
// FUNCTION: ENGINE 0x10823F30
// FUNCTION: ENGINE 0x10823F60
// FUNCTION: ENGINE 0x10823F90
// FUNCTION: ENGINE 0x10823FE0
// FUNCTION: ENGINE 0x10824030
// FUNCTION: ENGINE 0x10824080
// FUNCTION: ENGINE 0x108240D0
// FUNCTION: ENGINE 0x10824120
// FUNCTION: ENGINE 0x10824190
// FUNCTION: ENGINE 0x108241D0
// FUNCTION: ENGINE 0x10824220
// FUNCTION: ENGINE 0x10824270
// FUNCTION: ENGINE 0x108242C0
// FUNCTION: ENGINE 0x10824310
// FUNCTION: ENGINE 0x10824570
// FUNCTION: ENGINE 0x10824580
// FUNCTION: ENGINE 0x10824590
// FUNCTION: ENGINE 0x108245A0
// FUNCTION: ENGINE 0x108245B0
// FUNCTION: ENGINE 0x108245C0
// FUNCTION: ENGINE 0x108245D0
// FUNCTION: ENGINE 0x108246C0
// FUNCTION: ENGINE 0x108246F0
// FUNCTION: ENGINE 0x108247F0
// FUNCTION: ENGINE 0x10824820
// FUNCTION: ENGINE 0x10824920
// FUNCTION: ENGINE 0x10824950
// FUNCTION: ENGINE 0x10824A50
// FUNCTION: ENGINE 0x10824A80
// FUNCTION: ENGINE 0x10824B80
// FUNCTION: ENGINE 0x10824BB0
// FUNCTION: ENGINE 0x10824CD0
// FUNCTION: ENGINE 0x10824D00
// FUNCTION: ENGINE 0x10824D40
// FUNCTION: ENGINE 0x10824D80
// FUNCTION: ENGINE 0x10824DC0
// FUNCTION: ENGINE 0x10824E00
// FUNCTION: ENGINE 0x10824E40
// FUNCTION: ENGINE 0x10824E80
// FUNCTION: ENGINE 0x10824EA0
// FUNCTION: ENGINE 0x10824EC0
// FUNCTION: ENGINE 0x10824EE0
// FUNCTION: ENGINE 0x10824F00
// FUNCTION: ENGINE 0x10824F20
// FUNCTION: ENGINE 0x10824F40
// FUNCTION: ENGINE 0x10824F70
// FUNCTION: ENGINE 0x10824FD0
// FUNCTION: ENGINE 0x10825000
// FUNCTION: ENGINE 0x10825060
// FUNCTION: ENGINE 0x10825090
// FUNCTION: ENGINE 0x108250F0
// FUNCTION: ENGINE 0x10825120
// FUNCTION: ENGINE 0x10825180
// FUNCTION: ENGINE 0x108251B0
// FUNCTION: ENGINE 0x10825210
// FUNCTION: ENGINE 0x10825240
// FUNCTION: ENGINE 0x108252A0
// FUNCTION: ENGINE 0x108252D0
// FUNCTION: ENGINE 0x10825300
// FUNCTION: ENGINE 0x10825330
// FUNCTION: ENGINE 0x10825360
// FUNCTION: ENGINE 0x10825390
// FUNCTION: ENGINE 0x108254B0
// FUNCTION: ENGINE 0x10825550
// FUNCTION: ENGINE 0x108255F0
// FUNCTION: ENGINE 0x10825690
// FUNCTION: ENGINE 0x10825730
// FUNCTION: ENGINE 0x108257D0
// FUNCTION: ENGINE 0x10825870
// FUNCTION: ENGINE 0x10D8A040
// FUNCTION: ENGINE 0x10D8A050
// FUNCTION: ENGINE 0x10D8A060
// FUNCTION: ENGINE 0x10D8A070
// FUNCTION: ENGINE 0x10D8A080
// FUNCTION: ENGINE 0x10D8A090
