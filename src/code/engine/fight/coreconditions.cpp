// The conditions of the fight core itself (see coreconditions.h).
#include "code/engine/fight/coreconditions.h"
#include <new>

namespace fight
{
	// GLOBAL: ENGINE 0x11276260
	Property** gSequencerBranchConditionProperties;
	// GLOBAL: ENGINE 0x11276264
	Property** gSequencerIsBusyConditionProperties;
	// GLOBAL: ENGINE 0x11276268
	Property** gSequencerTimeConditionProperties;

	// ---- fight::SequencerBranchCondition, SequencerIsBusyCondition, SequencerTimeCondition --------------------------

	// FUNCTION: ENGINE 0x105ADB60
	bool SequencerBranchCondition::SetCompare(int newValue)
	{
		compare = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105ADB70
	BranchHolder* SequencerBranchCondition::GetBranch()
	{
		return &branch;
	}

	// FUNCTION: ENGINE 0x105ADB80
	bool SequencerBranchCondition::SetRecurse(bool newValue)
	{
		recurse = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105ADB90
	bool SequencerIsBusyCondition::SetMatch(bool newValue)
	{
		match = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105ADBA0
	bool SequencerTimeCondition::SetCompare(int newValue)
	{
		compare = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105ADBB0
	bool SequencerTimeCondition::SetTime(float newValue)
	{
		time = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105ADBC0
	Property* SequencerBranchCondition::GetProperty(int index)
	{
		return gSequencerBranchConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x105ADBD0
	void SequencerBranchCondition::ClearProperties()
	{
		FreePropertyList(&gSequencerBranchConditionProperties);
	}

	// FUNCTION: ENGINE 0x105ADBE0
	SequencerBranchCondition::SequencerBranchCondition() : Condition(0), branch(0), compare(0), recurse(false)
	{
	}

	// FUNCTION: ENGINE 0x105ADC10
	SequencerBranchCondition::~SequencerBranchCondition()
	{
	}

	// FUNCTION: ENGINE 0x105ADC30
	Property* SequencerIsBusyCondition::GetProperty(int index)
	{
		return gSequencerIsBusyConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x105ADC40
	void SequencerIsBusyCondition::ClearProperties()
	{
		FreePropertyList(&gSequencerIsBusyConditionProperties);
	}

	// FUNCTION: ENGINE 0x105ADC50
	SequencerIsBusyCondition::SequencerIsBusyCondition() : Condition(0), match(true)
	{
	}

	// FUNCTION: ENGINE 0x105ADC70
	SequencerIsBusyCondition::~SequencerIsBusyCondition()
	{
	}

	// FUNCTION: ENGINE 0x105ADC80
	Property* SequencerTimeCondition::GetProperty(int index)
	{
		return gSequencerTimeConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x105ADC90
	void SequencerTimeCondition::ClearProperties()
	{
		FreePropertyList(&gSequencerTimeConditionProperties);
	}

	// FUNCTION: ENGINE 0x105ADCA0
	SequencerTimeCondition::SequencerTimeCondition() : Condition(0), time(0.0f), compare(0)
	{
	}

	// FUNCTION: ENGINE 0x105ADCD0
	SequencerTimeCondition::~SequencerTimeCondition()
	{
	}

	// FUNCTION: ENGINE 0x105AE040
	ConditionFactory* CreateSequencerBranchConditionFactory(const char* name)
	{
		ConditionFactoryCasterTemplate<SequencerBranchCondition> caster;
		return FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x105AE060
	ConditionFactory* CreateSequencerIsBusyConditionFactory(const char* name)
	{
		ConditionFactoryCasterTemplate<SequencerIsBusyCondition> caster;
		return FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x105AE080
	ConditionFactory* CreateSequencerTimeConditionFactory(const char* name)
	{
		ConditionFactoryCasterTemplate<SequencerTimeCondition> caster;
		return FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x105AE0A0
	// EQUIVALENT: shrink-wrap (the engine saves esi and edi in the entry block; ours saves edi inside the block of the enum property, which also moves the store of its count; 47.5 %)
	void SequencerBranchCondition::RegisterProperties()
	{
		if (gSequencerBranchConditionProperties == 0)
		{
			Property* properties[256] = { 0 };
			Property* property = 0;
			property = new PropertyEnumConstList<SequencerBranchCondition>("compare", engine::gEqualityOperatorTable, engine::gEqualityOperatorCount, &SequencerBranchCondition::SetCompare);
			properties[0] = property;
			property = new PropertyBranch<SequencerBranchCondition>("branch", &SequencerBranchCondition::GetBranch);
			properties[1] = property;
			property = new PropertyBool<SequencerBranchCondition>("recurse", &SequencerBranchCondition::SetRecurse);
			properties[2] = property;
			RegisterPropertyList(properties, &gSequencerBranchConditionProperties);
		}
	}

	// FUNCTION: ENGINE 0x105AE190
	// EQUIVALENT: shrink-wrap
	void SequencerIsBusyCondition::RegisterProperties()
	{
		if (gSequencerIsBusyConditionProperties == 0)
		{
			Property* properties[256] = { 0 };
			Property* property = 0;
			property = new PropertyBool<SequencerIsBusyCondition>("match", &SequencerIsBusyCondition::SetMatch);
			properties[0] = property;
			RegisterPropertyList(properties, &gSequencerIsBusyConditionProperties);
		}
	}

	// FUNCTION: ENGINE 0x105AE210
	// EQUIVALENT: shrink-wrap (the engine saves esi and edi in the entry block; ours saves edi inside the block of the enum property, which also moves the store of its count; 49.7 %)
	void SequencerTimeCondition::RegisterProperties()
	{
		if (gSequencerTimeConditionProperties == 0)
		{
			Property* properties[256] = { 0 };
			Property* property = 0;
			property = new PropertyEnumConstList<SequencerTimeCondition>("compare", engine::gCompareOperatorTable, engine::gCompareOperatorCount, &SequencerTimeCondition::SetCompare);
			properties[0] = property;
			property = new PropertyFloatConstRange<SequencerTimeCondition>("time", &SequencerTimeCondition::SetTime);
			properties[1] = property;
			RegisterPropertyList(properties, &gSequencerTimeConditionProperties);
		}
	}

	template class PropertyEnumConstList<SequencerBranchCondition>;
	template class PropertyBranch<SequencerBranchCondition>;
	template class PropertyBool<SequencerBranchCondition>;
	template class PropertyBool<SequencerIsBusyCondition>;
	template class PropertyEnumConstList<SequencerTimeCondition>;
	template class PropertyFloatConstRange<SequencerTimeCondition>;
	template class ConditionFactoryTemplate<SequencerBranchCondition>;
	template class ConditionFactoryCasterTemplate<SequencerBranchCondition>;
	template class ConditionFactoryTemplate<SequencerIsBusyCondition>;
	template class ConditionFactoryCasterTemplate<SequencerIsBusyCondition>;
	template class ConditionFactoryTemplate<SequencerTimeCondition>;
	template class ConditionFactoryCasterTemplate<SequencerTimeCondition>;

	// FUNCTION: ENGINE 0x105AE2D0
	void RegisterSequencerBranchConditionFactory(TrackRegistry* registry, const char* name)
	{
		ConditionFactoryCasterTemplate<SequencerBranchCondition> caster;
		registry->AddFactory(FindConditionFactory(name, &caster));
	}

	// FUNCTION: ENGINE 0x105AE300
	void RegisterSequencerIsBusyConditionFactory(TrackRegistry* registry, const char* name)
	{
		ConditionFactoryCasterTemplate<SequencerIsBusyCondition> caster;
		registry->AddFactory(FindConditionFactory(name, &caster));
	}

	// FUNCTION: ENGINE 0x105AE330
	void RegisterSequencerTimeConditionFactory(TrackRegistry* registry, const char* name)
	{
		ConditionFactoryCasterTemplate<SequencerTimeCondition> caster;
		registry->AddFactory(FindConditionFactory(name, &caster));
	}
}

namespace fight
{
	// GLOBAL: ENGINE 0x1127626C
	Property** gRandomConditionProperties;
	// GLOBAL: ENGINE 0x11276270
	Property** gMaybeConditionProperties;
	// GLOBAL: ENGINE 0x11276274
	Property** gPrintConditionProperties;
	// GLOBAL: ENGINE 0x11276278
	Property** gPrintTrackProperties;
	// GLOBAL: ENGINE 0x1127627C
	Property** gPlatformConditionProperties;
	// GLOBAL: ENGINE 0x11276280
	Property** gNotConditionProperties;
	// GLOBAL: ENGINE 0x11276284
	Property** gOrConditionProperties;
	// GLOBAL: ENGINE 0x11276288
	Property** gConditionGroupConditionProperties;
	// GLOBAL: ENGINE 0x1127628C
	Property** gTrackGroupTrackProperties;
	// GLOBAL: ENGINE 0x11276290
	Property** gFalseConditionProperties;
	// GLOBAL: ENGINE 0x11276294
	Property** gDebugConditionProperties;
	// GLOBAL: ENGINE 0x11276298
	Property** gCommentConditionProperties;
	// GLOBAL: ENGINE 0x1127629C
	Property** gCommentTrackProperties;
	// GLOBAL: ENGINE 0x112762A0
	Property** gStopTrackProperties;
	// GLOBAL: ENGINE 0x112762A4
	Property** gSequenceTrackProperties;

	// ---- fight::RandomCondition, MaybeCondition ------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105AE510
	bool RandomCondition::SetWeight(float newValue)
	{
		weight = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105AE520
	bool MaybeCondition::SetPercent(float newValue)
	{
		percent = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105AE530
	Property* RandomCondition::GetProperty(int index)
	{
		return gRandomConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x105AE540
	void RandomCondition::ClearProperties()
	{
		FreePropertyList(&gRandomConditionProperties);
	}

	// FUNCTION: ENGINE 0x105AE550
	RandomCondition::RandomCondition() : Condition(0), weight(0.0f)
	{
	}

	// FUNCTION: ENGINE 0x105AE570
	RandomCondition::~RandomCondition()
	{
	}

	// FUNCTION: ENGINE 0x105AE580
	Property* MaybeCondition::GetProperty(int index)
	{
		return gMaybeConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x105AE590
	void MaybeCondition::ClearProperties()
	{
		FreePropertyList(&gMaybeConditionProperties);
	}

	// FUNCTION: ENGINE 0x105AE5A0
	MaybeCondition::MaybeCondition() : Condition(0), percent(0.0f)
	{
	}

	// FUNCTION: ENGINE 0x105AE5C0
	MaybeCondition::~MaybeCondition()
	{
	}

	// FUNCTION: ENGINE 0x105AE730
	ConditionFactory* CreateRandomConditionFactory(const char* name)
	{
		ConditionFactoryCasterTemplate<RandomCondition> caster;
		return FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x105AE750
	ConditionFactory* CreateMaybeConditionFactory(const char* name)
	{
		ConditionFactoryCasterTemplate<MaybeCondition> caster;
		return FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x105AE770
	// EQUIVALENT: shrink-wrap
	void RandomCondition::RegisterProperties()
	{
		if (gRandomConditionProperties == 0)
		{
			Property* properties[256] = { 0 };
			Property* property = 0;
			property = new PropertyFloatConstRange<RandomCondition>("weight", &RandomCondition::SetWeight);
			properties[0] = property;
			RegisterPropertyList(properties, &gRandomConditionProperties);
		}
	}

	// FUNCTION: ENGINE 0x105AE7F0
	// EQUIVALENT: shrink-wrap
	void MaybeCondition::RegisterProperties()
	{
		if (gMaybeConditionProperties == 0)
		{
			Property* properties[256] = { 0 };
			Property* property = 0;
			property = new PropertyFloatConstRange<MaybeCondition>("percent", &MaybeCondition::SetPercent);
			properties[0] = property;
			RegisterPropertyList(properties, &gMaybeConditionProperties);
		}
	}

	template class PropertyFloatConstRange<RandomCondition>;
	template class PropertyFloatConstRange<MaybeCondition>;
	template class ConditionFactoryTemplate<RandomCondition>;
	template class ConditionFactoryCasterTemplate<RandomCondition>;
	template class ConditionFactoryTemplate<MaybeCondition>;
	template class ConditionFactoryCasterTemplate<MaybeCondition>;

	// FUNCTION: ENGINE 0x105AE870
	void RegisterRandomConditionFactory(TrackRegistry* registry, const char* name)
	{
		ConditionFactoryCasterTemplate<RandomCondition> caster;
		registry->AddFactory(FindConditionFactory(name, &caster));
	}

	// FUNCTION: ENGINE 0x105AE8A0
	void RegisterMaybeConditionFactory(TrackRegistry* registry, const char* name)
	{
		ConditionFactoryCasterTemplate<MaybeCondition> caster;
		registry->AddFactory(FindConditionFactory(name, &caster));
	}

	// ---- fight::PrintCondition, PrintTrack -----------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105AE9F0
	bool PrintTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105AEA00
	Property* PrintCondition::GetProperty(int index)
	{
		return gPrintConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x105AEA10
	void PrintCondition::ClearProperties()
	{
		FreePropertyList(&gPrintConditionProperties);
	}

	// FUNCTION: ENGINE 0x105AEA20
	PrintCondition::PrintCondition() : Condition(0), channel(0), text(0)
	{
	}

	// FUNCTION: ENGINE 0x105AEA50
	PrintCondition::~PrintCondition()
	{
		delete[] channel;
		delete[] text;
	}

	// FUNCTION: ENGINE 0x105AEA80
	bool PrintCondition::SetChannel(const char* newValue)
	{
		channel = ReplaceString(channel, newValue);
		return true;
	}

	// FUNCTION: ENGINE 0x105AEAA0
	bool PrintCondition::SetText(const char* newValue)
	{
		text = ReplaceString(text, newValue);
		return true;
	}

	// FUNCTION: ENGINE 0x105AEAC0
	Property* PrintTrack::GetProperty(int index)
	{
		return gPrintTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x105AEAD0
	void PrintTrack::ClearProperties()
	{
		FreePropertyList(&gPrintTrackProperties);
	}

	// FUNCTION: ENGINE 0x105AEAE0
	PrintTrack::PrintTrack() : channel(0), text(0), timeBegin(0.0f)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x105AEB10
	float PrintTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x105AEB20
	float PrintTrack::Slot10() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x105AEB30
	PrintTrack::~PrintTrack()
	{
		delete[] channel;
		delete[] text;
	}

	// FUNCTION: ENGINE 0x105AEB60
	bool PrintTrack::SetChannel(const char* newValue)
	{
		channel = ReplaceString(channel, newValue);
		return true;
	}

	// FUNCTION: ENGINE 0x105AEB80
	bool PrintTrack::SetText(const char* newValue)
	{
		text = ReplaceString(text, newValue);
		return true;
	}

	// FUNCTION: ENGINE 0x105AED50
	ConditionFactory* CreatePrintConditionFactory(const char* name)
	{
		ConditionFactoryCasterTemplate<PrintCondition> caster;
		return FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x105AED70
	TrackFactory* CreatePrintTrackFactory(const char* name)
	{
		TrackFactoryCasterTemplate<PrintTrack> caster;
		return FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x105AED90
	// EQUIVALENT: shrink-wrap
	void PrintCondition::RegisterProperties()
	{
		if (gPrintConditionProperties == 0)
		{
			Property* properties[256] = { 0 };
			Property* property = 0;
			property = new PropertyString<PrintCondition>("channel", &PrintCondition::SetChannel);
			properties[0] = property;
			property = new PropertyString<PrintCondition>("text", &PrintCondition::SetText);
			properties[1] = property;
			RegisterPropertyList(properties, &gPrintConditionProperties);
		}
	}

	// FUNCTION: ENGINE 0x105AEE40
	// EQUIVALENT: shrink-wrap
	void PrintTrack::RegisterProperties()
	{
		if (gPrintTrackProperties == 0)
		{
			Property* properties[256] = { 0 };
			Property* property = 0;
			property = new PropertyFloatConstRange<PrintTrack>("timeBegin", &PrintTrack::SetTimeBegin);
			properties[0] = property;
			property = new PropertyString<PrintTrack>("channel", &PrintTrack::SetChannel);
			properties[1] = property;
			property = new PropertyString<PrintTrack>("text", &PrintTrack::SetText);
			properties[2] = property;
			RegisterPropertyList(properties, &gPrintTrackProperties);
		}
	}

	template class PropertyString<PrintCondition>;
	template class PropertyFloatConstRange<PrintTrack>;
	template class PropertyString<PrintTrack>;
	template class ConditionFactoryTemplate<PrintCondition>;
	template class ConditionFactoryCasterTemplate<PrintCondition>;
	template class TrackFactoryTemplate<PrintTrack>;
	template class TrackFactoryCasterTemplate<PrintTrack>;

	// FUNCTION: ENGINE 0x105AEF20
	void RegisterPrintConditionFactory(TrackRegistry* registry, const char* name)
	{
		ConditionFactoryCasterTemplate<PrintCondition> caster;
		registry->AddFactory(FindConditionFactory(name, &caster));
	}

	// FUNCTION: ENGINE 0x105AEF50
	void RegisterPrintTrackFactory(TrackRegistry* registry, const char* name)
	{
		TrackFactoryCasterTemplate<PrintTrack> caster;
		registry->AddFactory(FindTrackFactory(name, &caster));
	}

	// ---- fight::PlatformCondition --------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105AF0A0
	bool PlatformCondition::SetPS2(bool newValue)
	{
		pS2 = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105AF0B0
	bool PlatformCondition::SetXBox(bool newValue)
	{
		xBox = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105AF0C0
	bool PlatformCondition::SetGameCube(bool newValue)
	{
		gameCube = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105AF0D0
	bool PlatformCondition::SetWin32(bool newValue)
	{
		win32 = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105AF0E0
	bool PlatformCondition::SetXenon(bool newValue)
	{
		xenon = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105AF0F0
	bool PlatformCondition::SetPS3(bool newValue)
	{
		pS3 = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105AF100
	Property* PlatformCondition::GetProperty(int index)
	{
		return gPlatformConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x105AF110
	void PlatformCondition::ClearProperties()
	{
		FreePropertyList(&gPlatformConditionProperties);
	}

	// FUNCTION: ENGINE 0x105AF120
	PlatformCondition::PlatformCondition() : Condition(0), gameCube(true), pS2(true), pS3(true), win32(true), xBox(true), xenon(true)
	{
	}

	// FUNCTION: ENGINE 0x105AF150
	PlatformCondition::~PlatformCondition()
	{
	}

	// FUNCTION: ENGINE 0x105AF210
	ConditionFactory* CreatePlatformConditionFactory(const char* name)
	{
		ConditionFactoryCasterTemplate<PlatformCondition> caster;
		return FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x105AF230
	// EQUIVALENT: shrink-wrap
	void PlatformCondition::RegisterProperties()
	{
		if (gPlatformConditionProperties == 0)
		{
			Property* properties[256] = { 0 };
			Property* property = 0;
			property = new PropertyBool<PlatformCondition>("pS2", &PlatformCondition::SetPS2);
			properties[0] = property;
			property = new PropertyBool<PlatformCondition>("xBox", &PlatformCondition::SetXBox);
			properties[1] = property;
			property = new PropertyBool<PlatformCondition>("gameCube", &PlatformCondition::SetGameCube);
			properties[2] = property;
			property = new PropertyBool<PlatformCondition>("win32", &PlatformCondition::SetWin32);
			properties[3] = property;
			property = new PropertyBool<PlatformCondition>("xenon", &PlatformCondition::SetXenon);
			properties[4] = property;
			property = new PropertyBool<PlatformCondition>("pS3", &PlatformCondition::SetPS3);
			properties[5] = property;
			RegisterPropertyList(properties, &gPlatformConditionProperties);
		}
	}

	template class PropertyBool<PlatformCondition>;
	template class ConditionFactoryTemplate<PlatformCondition>;
	template class ConditionFactoryCasterTemplate<PlatformCondition>;

	// FUNCTION: ENGINE 0x105AF3A0
	void RegisterPlatformConditionFactory(TrackRegistry* registry, const char* name)
	{
		ConditionFactoryCasterTemplate<PlatformCondition> caster;
		registry->AddFactory(FindConditionFactory(name, &caster));
	}

	// ---- fight::NotCondition, OrCondition, ConditionGroupCondition, TrackGroupTrack ------------------------------

	// FUNCTION: ENGINE 0x105AF460
	ConditionList* ConditionGroupCondition::GetConditions()
	{
		return &conditions;
	}

	// FUNCTION: ENGINE 0x105AF470
	bool TrackGroupTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105AF480
	bool TrackGroupTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105AF490
	ConditionList* TrackGroupTrack::GetConditions()
	{
		return &conditions;
	}

	// FUNCTION: ENGINE 0x105AF4A0
	TrackGroup* TrackGroupTrack::GetTracks()
	{
		return &tracks;
	}

	// FUNCTION: ENGINE 0x105AF4B0
	void NotCondition::RegisterProperties()
	{
		if (gNotConditionProperties == 0)
		{
			Property* properties[256] = { 0 };
			RegisterPropertyList(properties, &gNotConditionProperties);
		}
	}

	// FUNCTION: ENGINE 0x105AF500
	Property* NotCondition::GetProperty(int index)
	{
		return gNotConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x105AF510
	void NotCondition::ClearProperties()
	{
		FreePropertyList(&gNotConditionProperties);
	}

	// FUNCTION: ENGINE 0x105AF520
	NotCondition::NotCondition() : Condition(2)
	{
	}

	// FUNCTION: ENGINE 0x105AF540
	NotCondition::~NotCondition()
	{
	}

	// FUNCTION: ENGINE 0x105AF550
	void OrCondition::RegisterProperties()
	{
		if (gOrConditionProperties == 0)
		{
			Property* properties[256] = { 0 };
			RegisterPropertyList(properties, &gOrConditionProperties);
		}
	}

	// FUNCTION: ENGINE 0x105AF5A0
	Property* OrCondition::GetProperty(int index)
	{
		return gOrConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x105AF5B0
	void OrCondition::ClearProperties()
	{
		FreePropertyList(&gOrConditionProperties);
	}

	// FUNCTION: ENGINE 0x105AF5C0
	OrCondition::OrCondition() : Condition(1)
	{
	}

	// FUNCTION: ENGINE 0x105AF5E0
	OrCondition::~OrCondition()
	{
	}

	// FUNCTION: ENGINE 0x105AF5F0
	Property* ConditionGroupCondition::GetProperty(int index)
	{
		return gConditionGroupConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x105AF600
	void ConditionGroupCondition::ClearProperties()
	{
		FreePropertyList(&gConditionGroupConditionProperties);
	}

	// FUNCTION: ENGINE 0x105AF610
	ConditionGroupCondition::ConditionGroupCondition() : Condition(0)
	{
	}

	// FUNCTION: ENGINE 0x105AF630
	ConditionGroupCondition::~ConditionGroupCondition()
	{
	}

	// FUNCTION: ENGINE 0x105AF650
	Property* TrackGroupTrack::GetProperty(int index)
	{
		return gTrackGroupTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x105AF660
	void TrackGroupTrack::ClearProperties()
	{
		FreePropertyList(&gTrackGroupTrackProperties);
	}

	// FUNCTION: ENGINE 0x105AF670
	bool TrackGroupTrack::SetGroupName(const Name& newValue)
	{
		groupName = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105AF6F0
	TrackGroupTrack::TrackGroupTrack() : timeBegin(0.0f), timeEnd(-1.0f)
	{
	}

	// FUNCTION: ENGINE 0x105AF730
	float TrackGroupTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x105AF740
	float TrackGroupTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x105AF750
	TrackGroupTrack::~TrackGroupTrack()
	{
	}

	// FUNCTION: ENGINE 0x105AFAA0
	ConditionFactory* CreateNotConditionFactory(const char* name)
	{
		ConditionFactoryCasterTemplate<NotCondition> caster;
		return FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x105AFAC0
	ConditionFactory* CreateOrConditionFactory(const char* name)
	{
		ConditionFactoryCasterTemplate<OrCondition> caster;
		return FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x105AFAE0
	ConditionFactory* CreateConditionGroupConditionFactory(const char* name)
	{
		ConditionFactoryCasterTemplate<ConditionGroupCondition> caster;
		return FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x105AFB00
	TrackFactory* CreateTrackGroupTrackFactory(const char* name)
	{
		TrackFactoryCasterTemplate<TrackGroupTrack> caster;
		return FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x105AFB20
	// EQUIVALENT: shrink-wrap
	void ConditionGroupCondition::RegisterProperties()
	{
		if (gConditionGroupConditionProperties == 0)
		{
			Property* properties[256] = { 0 };
			Property* property = 0;
			property = new PropertyConditionGroup<ConditionGroupCondition>("conditions", &ConditionGroupCondition::GetConditions);
			properties[0] = property;
			RegisterPropertyList(properties, &gConditionGroupConditionProperties);
		}
	}

	template class ConditionFactoryTemplate<NotCondition>;
	template class ConditionFactoryCasterTemplate<NotCondition>;
	template class ConditionFactoryTemplate<OrCondition>;
	template class ConditionFactoryCasterTemplate<OrCondition>;
	template class PropertyConditionGroup<ConditionGroupCondition>;
	template class ConditionFactoryTemplate<ConditionGroupCondition>;
	template class ConditionFactoryCasterTemplate<ConditionGroupCondition>;
	template class PropertyName<TrackGroupTrack>;
	template class PropertyFloatConstRange<TrackGroupTrack>;
	template class PropertyConditionGroup<TrackGroupTrack>;
	template class PropertyTrackGroup<TrackGroupTrack>;
	template class TrackFactoryTemplate<TrackGroupTrack>;
	template class TrackFactoryCasterTemplate<TrackGroupTrack>;

	// FUNCTION: ENGINE 0x105AFBA0
	void RegisterNotConditionFactory(TrackRegistry* registry, const char* name)
	{
		ConditionFactoryCasterTemplate<NotCondition> caster;
		registry->AddFactory(FindConditionFactory(name, &caster));
	}

	// FUNCTION: ENGINE 0x105AFBD0
	void RegisterOrConditionFactory(TrackRegistry* registry, const char* name)
	{
		ConditionFactoryCasterTemplate<OrCondition> caster;
		registry->AddFactory(FindConditionFactory(name, &caster));
	}

	// FUNCTION: ENGINE 0x105AFC00
	void RegisterConditionGroupConditionFactory(TrackRegistry* registry, const char* name)
	{
		ConditionFactoryCasterTemplate<ConditionGroupCondition> caster;
		registry->AddFactory(FindConditionFactory(name, &caster));
	}

	// FUNCTION: ENGINE 0x105AFC30
	void RegisterTrackGroupTrackFactory(TrackRegistry* registry, const char* name)
	{
		TrackFactoryCasterTemplate<TrackGroupTrack> caster;
		registry->AddFactory(FindTrackFactory(name, &caster));
	}

	// FUNCTION: ENGINE 0x105AFCF0
	// EQUIVALENT: shrink-wrap
	void TrackGroupTrack::RegisterProperties()
	{
		if (gTrackGroupTrackProperties == 0)
		{
			Property* properties[256] = { 0 };
			Property* property = 0;
			property = new PropertyName<TrackGroupTrack>("groupName", &TrackGroupTrack::SetGroupName);
			properties[0] = property;
			property = new PropertyFloatConstRange<TrackGroupTrack>("timeBegin", &TrackGroupTrack::SetTimeBegin);
			properties[1] = property;
			property = new PropertyFloatConstRange<TrackGroupTrack>("timeEnd", &TrackGroupTrack::SetTimeEnd);
			properties[2] = property;
			property = new PropertyConditionGroup<TrackGroupTrack>("conditions", &TrackGroupTrack::GetConditions);
			properties[3] = property;
			property = new PropertyTrackGroup<TrackGroupTrack>("tracks", &TrackGroupTrack::GetTracks);
			properties[4] = property;
			RegisterPropertyList(properties, &gTrackGroupTrackProperties);
		}
	}

	// ---- fight::FalseCondition, DebugCondition -------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105AFF00
	void FalseCondition::RegisterProperties()
	{
		if (gFalseConditionProperties == 0)
		{
			Property* properties[256] = { 0 };
			RegisterPropertyList(properties, &gFalseConditionProperties);
		}
	}

	// FUNCTION: ENGINE 0x105AFF50
	Property* FalseCondition::GetProperty(int index)
	{
		return gFalseConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x105AFF60
	void FalseCondition::ClearProperties()
	{
		FreePropertyList(&gFalseConditionProperties);
	}

	// FUNCTION: ENGINE 0x105AFF70
	FalseCondition::FalseCondition() : Condition(0)
	{
	}

	// FUNCTION: ENGINE 0x105AFF90
	FalseCondition::~FalseCondition()
	{
	}

	// FUNCTION: ENGINE 0x105B0090
	ConditionFactory* CreateFalseConditionFactory(const char* name)
	{
		ConditionFactoryCasterTemplate<FalseCondition> caster;
		return FindConditionFactory(name, &caster);
	}

	template class ConditionFactoryTemplate<FalseCondition>;
	template class ConditionFactoryCasterTemplate<FalseCondition>;

	// FUNCTION: ENGINE 0x105B00B0
	void RegisterFalseConditionFactory(TrackRegistry* registry, const char* name)
	{
		ConditionFactoryCasterTemplate<FalseCondition> caster;
		registry->AddFactory(FindConditionFactory(name, &caster));
	}

	// FUNCTION: ENGINE 0x105B00E0
	bool DebugCondition::SetCompare(int newValue)
	{
		compare = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105B00F0
	bool DebugCondition::SetMode(int newValue)
	{
		mode = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105B0100
	Property* DebugCondition::GetProperty(int index)
	{
		return gDebugConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x105B0110
	void DebugCondition::ClearProperties()
	{
		FreePropertyList(&gDebugConditionProperties);
	}

	// FUNCTION: ENGINE 0x105B0120
	DebugCondition::DebugCondition() : Condition(0), compare(0), mode(0)
	{
	}

	// FUNCTION: ENGINE 0x105B0150
	DebugCondition::~DebugCondition()
	{
	}

	// FUNCTION: ENGINE 0x105B0250
	ConditionFactory* CreateDebugConditionFactory(const char* name)
	{
		ConditionFactoryCasterTemplate<DebugCondition> caster;
		return FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x105B0270
	// EQUIVALENT: shrink-wrap
	void DebugCondition::RegisterProperties()
	{
		if (gDebugConditionProperties == 0)
		{
			Property* properties[256] = { 0 };
			Property* property = 0;
			property = new PropertyEnumConstList<DebugCondition>("compare", engine::gEqualityOperatorTable, engine::gEqualityOperatorCount, &DebugCondition::SetCompare);
			properties[0] = property;
			property = new PropertyEnumConstList<DebugCondition>("mode", gDebugConditionModeTable, gDebugConditionModeCount, &DebugCondition::SetMode);
			properties[1] = property;
			RegisterPropertyList(properties, &gDebugConditionProperties);
		}
	}

	template class PropertyEnumConstList<DebugCondition>;
	template class ConditionFactoryTemplate<DebugCondition>;
	template class ConditionFactoryCasterTemplate<DebugCondition>;

	// FUNCTION: ENGINE 0x105B0340
	void RegisterDebugConditionFactory(TrackRegistry* registry, const char* name)
	{
		ConditionFactoryCasterTemplate<DebugCondition> caster;
		registry->AddFactory(FindConditionFactory(name, &caster));
	}

	// ---- fight::CommentCondition, CommentTrack -------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105B0400
	Property* CommentCondition::GetProperty(int index)
	{
		return gCommentConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x105B0410
	void CommentCondition::ClearProperties()
	{
		FreePropertyList(&gCommentConditionProperties);
	}

	// FUNCTION: ENGINE 0x105B0420
	CommentCondition::CommentCondition() : Condition(3), text(0)
	{
	}

	// FUNCTION: ENGINE 0x105B0440
	CommentCondition::~CommentCondition()
	{
		delete[] text;
	}

	// FUNCTION: ENGINE 0x105B0460
	bool CommentCondition::SetText(const char* newValue)
	{
		text = ReplaceString(text, newValue);
		return true;
	}

	// FUNCTION: ENGINE 0x105B0480
	Property* CommentTrack::GetProperty(int index)
	{
		return gCommentTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x105B0490
	void CommentTrack::ClearProperties()
	{
		FreePropertyList(&gCommentTrackProperties);
	}

	// FUNCTION: ENGINE 0x105B04A0
	CommentTrack::CommentTrack() : text(0)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x105B04C0
	float CommentTrack::GetTimeBegin() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x105B04D0
	float CommentTrack::Slot10() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x105B04E0
	CommentTrack::~CommentTrack()
	{
		delete[] text;
	}

	// FUNCTION: ENGINE 0x105B0500
	bool CommentTrack::SetText(const char* newValue)
	{
		text = ReplaceString(text, newValue);
		return true;
	}

	// FUNCTION: ENGINE 0x105B0680
	ConditionFactory* CreateCommentConditionFactory(const char* name)
	{
		ConditionFactoryCasterTemplate<CommentCondition> caster;
		return FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x105B06A0
	TrackFactory* CreateCommentTrackFactory(const char* name)
	{
		TrackFactoryCasterTemplate<CommentTrack> caster;
		return FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x105B06C0
	// EQUIVALENT: shrink-wrap
	void CommentCondition::RegisterProperties()
	{
		if (gCommentConditionProperties == 0)
		{
			Property* properties[256] = { 0 };
			Property* property = 0;
			property = new PropertyString<CommentCondition>("text", &CommentCondition::SetText);
			properties[0] = property;
			RegisterPropertyList(properties, &gCommentConditionProperties);
		}
	}

	// FUNCTION: ENGINE 0x105B0740
	// EQUIVALENT: shrink-wrap
	void CommentTrack::RegisterProperties()
	{
		if (gCommentTrackProperties == 0)
		{
			Property* properties[256] = { 0 };
			Property* property = 0;
			property = new PropertyString<CommentTrack>("text", &CommentTrack::SetText);
			properties[0] = property;
			RegisterPropertyList(properties, &gCommentTrackProperties);
		}
	}

	template class PropertyString<CommentCondition>;
	template class PropertyString<CommentTrack>;
	template class ConditionFactoryTemplate<CommentCondition>;
	template class ConditionFactoryCasterTemplate<CommentCondition>;
	template class TrackFactoryTemplate<CommentTrack>;
	template class TrackFactoryCasterTemplate<CommentTrack>;

	// FUNCTION: ENGINE 0x105B07C0
	void RegisterCommentConditionFactory(TrackRegistry* registry, const char* name)
	{
		ConditionFactoryCasterTemplate<CommentCondition> caster;
		registry->AddFactory(FindConditionFactory(name, &caster));
	}

	// FUNCTION: ENGINE 0x105B07F0
	void RegisterCommentTrackFactory(TrackRegistry* registry, const char* name)
	{
		TrackFactoryCasterTemplate<CommentTrack> caster;
		registry->AddFactory(FindTrackFactory(name, &caster));
	}

	// ---- fight::StopTrack, SequenceTrack -------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105B0940
	bool StopTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105B0950
	bool StopTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105B0960
	ConditionList* StopTrack::GetConditions()
	{
		return &conditions;
	}

	// FUNCTION: ENGINE 0x105B0970
	Property* StopTrack::GetProperty(int index)
	{
		return gStopTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x105B0980
	void StopTrack::ClearProperties()
	{
		FreePropertyList(&gStopTrackProperties);
	}

	// FUNCTION: ENGINE 0x105B0990
	StopTrack::StopTrack() : timeBegin(0.0f), timeEnd(-1.0f)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x105B09D0
	float StopTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x105B09E0
	float StopTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x105B09F0
	StopTrack::~StopTrack()
	{
	}

	// FUNCTION: ENGINE 0x105B0AF0
	TrackFactory* CreateStopTrackFactory(const char* name)
	{
		TrackFactoryCasterTemplate<StopTrack> caster;
		return FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x105B0B10
	// EQUIVALENT: shrink-wrap
	void StopTrack::RegisterProperties()
	{
		if (gStopTrackProperties == 0)
		{
			Property* properties[256] = { 0 };
			Property* property = 0;
			property = new PropertyFloatConstRange<StopTrack>("timeBegin", &StopTrack::SetTimeBegin);
			properties[0] = property;
			property = new PropertyFloatConstRange<StopTrack>("timeEnd", &StopTrack::SetTimeEnd);
			properties[1] = property;
			property = new PropertyConditionGroup<StopTrack>("conditions", &StopTrack::GetConditions);
			properties[2] = property;
			RegisterPropertyList(properties, &gStopTrackProperties);
		}
	}

	template class PropertyFloatConstRange<StopTrack>;
	template class PropertyConditionGroup<StopTrack>;
	template class TrackFactoryTemplate<StopTrack>;
	template class TrackFactoryCasterTemplate<StopTrack>;

	// FUNCTION: ENGINE 0x105B0BF0
	void RegisterStopTrackFactory(TrackRegistry* registry, const char* name)
	{
		TrackFactoryCasterTemplate<StopTrack> caster;
		registry->AddFactory(FindTrackFactory(name, &caster));
	}

	// FUNCTION: ENGINE 0x105B0CB0
	bool SequenceTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105B0CC0
	BranchHolder* SequenceTrack::GetBranch()
	{
		return &branch;
	}

	// FUNCTION: ENGINE 0x105B0CD0
	bool SequenceTrack::SetPriority(int newValue)
	{
		priority = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105B0CE0
	ConditionList* SequenceTrack::GetConditions()
	{
		return &conditions;
	}

	// FUNCTION: ENGINE 0x105B0CF0
	Property* SequenceTrack::GetProperty(int index)
	{
		return gSequenceTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x105B0D00
	void SequenceTrack::ClearProperties()
	{
		FreePropertyList(&gSequenceTrackProperties);
	}

	// FUNCTION: ENGINE 0x105B0D10
	SequenceTrack::SequenceTrack() : branch(0), priority(1), timeBegin(0.0f)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x105B0D50
	float SequenceTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x105B0D60
	float SequenceTrack::Slot10() const
	{
		return -1.0f;
	}

	// FUNCTION: ENGINE 0x105B0D70
	SequenceTrack::~SequenceTrack()
	{
	}

	// FUNCTION: ENGINE 0x105B0F00
	TrackFactory* CreateSequenceTrackFactory(const char* name)
	{
		TrackFactoryCasterTemplate<SequenceTrack> caster;
		return FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x105B0F20
	// EQUIVALENT: shrink-wrap
	void SequenceTrack::RegisterProperties()
	{
		if (gSequenceTrackProperties == 0)
		{
			Property* properties[256] = { 0 };
			Property* property = 0;
			property = new PropertyFloatConstRange<SequenceTrack>("timeBegin", &SequenceTrack::SetTimeBegin);
			properties[0] = property;
			property = new PropertyBranch<SequenceTrack>("branch", &SequenceTrack::GetBranch);
			properties[1] = property;
			property = new PropertyIntConstRange<SequenceTrack>("priority", &SequenceTrack::SetPriority);
			properties[2] = property;
			property = new PropertyConditionGroup<SequenceTrack>("conditions", &SequenceTrack::GetConditions);
			properties[3] = property;
			RegisterPropertyList(properties, &gSequenceTrackProperties);
		}
	}

	template class PropertyFloatConstRange<SequenceTrack>;
	template class PropertyBranch<SequenceTrack>;
	template class PropertyIntConstRange<SequenceTrack>;
	template class PropertyConditionGroup<SequenceTrack>;
	template class TrackFactoryTemplate<SequenceTrack>;
	template class TrackFactoryCasterTemplate<SequenceTrack>;

	// FUNCTION: ENGINE 0x105B1030
	void RegisterSequenceTrackFactory(TrackRegistry* registry, const char* name)
	{
		TrackFactoryCasterTemplate<SequenceTrack> caster;
		registry->AddFactory(FindTrackFactory(name, &caster));
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x105ADD40
// FUNCTION: ENGINE 0x105ADD50
// FUNCTION: ENGINE 0x105ADD80
// FUNCTION: ENGINE 0x105ADD90
// FUNCTION: ENGINE 0x105ADDC0
// FUNCTION: ENGINE 0x105ADDD0
// FUNCTION: ENGINE 0x105ADE00
// FUNCTION: ENGINE 0x105ADE30
// FUNCTION: ENGINE 0x105ADE40
// FUNCTION: ENGINE 0x105ADE60
// FUNCTION: ENGINE 0x105ADE80
// FUNCTION: ENGINE 0x105ADE90
// FUNCTION: ENGINE 0x105ADEB0
// FUNCTION: ENGINE 0x105ADEC0
// FUNCTION: ENGINE 0x105ADEE0
// FUNCTION: ENGINE 0x105ADF00
// FUNCTION: ENGINE 0x105ADF10
// FUNCTION: ENGINE 0x105ADF30
// FUNCTION: ENGINE 0x105ADF50
// FUNCTION: ENGINE 0x105ADF60
// FUNCTION: ENGINE 0x105ADF90
// FUNCTION: ENGINE 0x105ADFA0
// FUNCTION: ENGINE 0x105ADFC0
// FUNCTION: ENGINE 0x105ADFE0
// FUNCTION: ENGINE 0x105ADFF0
// FUNCTION: ENGINE 0x105AE010
// FUNCTION: ENGINE 0x105AE030
// FUNCTION: ENGINE 0x105AE360
// FUNCTION: ENGINE 0x105AE390
// FUNCTION: ENGINE 0x105AE3B0
// FUNCTION: ENGINE 0x105AE3E0
// FUNCTION: ENGINE 0x105AE400
// FUNCTION: ENGINE 0x105AE430
// FUNCTION: ENGINE 0x105AE450
// FUNCTION: ENGINE 0x105AE490
// FUNCTION: ENGINE 0x105AE4D0
// FUNCTION: ENGINE 0x105AE610
// FUNCTION: ENGINE 0x105AE620
// FUNCTION: ENGINE 0x105AE650
// FUNCTION: ENGINE 0x105AE660
// FUNCTION: ENGINE 0x105AE690
// FUNCTION: ENGINE 0x105AE6B0
// FUNCTION: ENGINE 0x105AE6D0
// FUNCTION: ENGINE 0x105AE6E0
// FUNCTION: ENGINE 0x105AE700
// FUNCTION: ENGINE 0x105AE720
// FUNCTION: ENGINE 0x105AE8D0
// FUNCTION: ENGINE 0x105AE900
// FUNCTION: ENGINE 0x105AE920
// FUNCTION: ENGINE 0x105AE950
// FUNCTION: ENGINE 0x105AE970
// FUNCTION: ENGINE 0x105AE9B0
// FUNCTION: ENGINE 0x105AEBE0
// FUNCTION: ENGINE 0x105AEBF0
// FUNCTION: ENGINE 0x105AEC20
// FUNCTION: ENGINE 0x105AEC30
// FUNCTION: ENGINE 0x105AEC60
// FUNCTION: ENGINE 0x105AEC80
// FUNCTION: ENGINE 0x105AECA0
// FUNCTION: ENGINE 0x105AECB0
// FUNCTION: ENGINE 0x105AECD0
// FUNCTION: ENGINE 0x105AECF0
// FUNCTION: ENGINE 0x105AED00
// FUNCTION: ENGINE 0x105AED20
// FUNCTION: ENGINE 0x105AED40
// FUNCTION: ENGINE 0x105AEF80
// FUNCTION: ENGINE 0x105AEFB0
// FUNCTION: ENGINE 0x105AEFD0
// FUNCTION: ENGINE 0x105AF000
// FUNCTION: ENGINE 0x105AF020
// FUNCTION: ENGINE 0x105AF060
// FUNCTION: ENGINE 0x105AF180
// FUNCTION: ENGINE 0x105AF190
// FUNCTION: ENGINE 0x105AF1C0
// FUNCTION: ENGINE 0x105AF1E0
// FUNCTION: ENGINE 0x105AF200
// FUNCTION: ENGINE 0x105AF3D0
// FUNCTION: ENGINE 0x105AF400
// FUNCTION: ENGINE 0x105AF420
// FUNCTION: ENGINE 0x105AF780
// FUNCTION: ENGINE 0x105AF790
// FUNCTION: ENGINE 0x105AF7C0
// FUNCTION: ENGINE 0x105AF7F0
// FUNCTION: ENGINE 0x105AF810
// FUNCTION: ENGINE 0x105AF850
// FUNCTION: ENGINE 0x105AF860
// FUNCTION: ENGINE 0x105AF890
// FUNCTION: ENGINE 0x105AF8C0
// FUNCTION: ENGINE 0x105AF8E0
// FUNCTION: ENGINE 0x105AF920
// FUNCTION: ENGINE 0x105AF930
// FUNCTION: ENGINE 0x105AF960
// FUNCTION: ENGINE 0x105AF970
// FUNCTION: ENGINE 0x105AF9C0
// FUNCTION: ENGINE 0x105AF9E0
// FUNCTION: ENGINE 0x105AF9F0
// FUNCTION: ENGINE 0x105AFA10
// FUNCTION: ENGINE 0x105AFA30
// FUNCTION: ENGINE 0x105AFA40
// FUNCTION: ENGINE 0x105AFA60
// FUNCTION: ENGINE 0x105AFA70
// FUNCTION: ENGINE 0x105AFA90
// FUNCTION: ENGINE 0x105AFC60
// FUNCTION: ENGINE 0x105AFC80
// FUNCTION: ENGINE 0x105AFCA0
// FUNCTION: ENGINE 0x105AFCD0
// FUNCTION: ENGINE 0x105AFE30
// FUNCTION: ENGINE 0x105AFE70
// FUNCTION: ENGINE 0x105AFEA0
// FUNCTION: ENGINE 0x105AFEC0
// FUNCTION: ENGINE 0x105AFFC0
// FUNCTION: ENGINE 0x105AFFD0
// FUNCTION: ENGINE 0x105B0000
// FUNCTION: ENGINE 0x105B0030
// FUNCTION: ENGINE 0x105B0050
// FUNCTION: ENGINE 0x105B0180
// FUNCTION: ENGINE 0x105B0190
// FUNCTION: ENGINE 0x105B01C0
// FUNCTION: ENGINE 0x105B01F0
// FUNCTION: ENGINE 0x105B0200
// FUNCTION: ENGINE 0x105B0220
// FUNCTION: ENGINE 0x105B0240
// FUNCTION: ENGINE 0x105B0370
// FUNCTION: ENGINE 0x105B03A0
// FUNCTION: ENGINE 0x105B03C0
// FUNCTION: ENGINE 0x105B0560
// FUNCTION: ENGINE 0x105B0570
// FUNCTION: ENGINE 0x105B05A0
// FUNCTION: ENGINE 0x105B05B0
// FUNCTION: ENGINE 0x105B05E0
// FUNCTION: ENGINE 0x105B0600
// FUNCTION: ENGINE 0x105B0620
// FUNCTION: ENGINE 0x105B0630
// FUNCTION: ENGINE 0x105B0650
// FUNCTION: ENGINE 0x105B0670
// FUNCTION: ENGINE 0x105B0820
// FUNCTION: ENGINE 0x105B0850
// FUNCTION: ENGINE 0x105B0870
// FUNCTION: ENGINE 0x105B08A0
// FUNCTION: ENGINE 0x105B08C0
// FUNCTION: ENGINE 0x105B0900
// FUNCTION: ENGINE 0x105B0A30
// FUNCTION: ENGINE 0x105B0A40
// FUNCTION: ENGINE 0x105B0A70
// FUNCTION: ENGINE 0x105B0A90
// FUNCTION: ENGINE 0x105B0AB0
// FUNCTION: ENGINE 0x105B0AC0
// FUNCTION: ENGINE 0x105B0AE0
// FUNCTION: ENGINE 0x105B0C20
// FUNCTION: ENGINE 0x105B0C50
// FUNCTION: ENGINE 0x105B0C70
// FUNCTION: ENGINE 0x105B0DC0
// FUNCTION: ENGINE 0x105B0DD0
// FUNCTION: ENGINE 0x105B0E00
// FUNCTION: ENGINE 0x105B0E20
// FUNCTION: ENGINE 0x105B0E40
// FUNCTION: ENGINE 0x105B0E50
// FUNCTION: ENGINE 0x105B0E70
// FUNCTION: ENGINE 0x105B0E80
// FUNCTION: ENGINE 0x105B0EA0
// FUNCTION: ENGINE 0x105B0EC0
// FUNCTION: ENGINE 0x105B0ED0
// FUNCTION: ENGINE 0x105B0EF0
// FUNCTION: ENGINE 0x105B1060
// FUNCTION: ENGINE 0x105B1090
// FUNCTION: ENGINE 0x105B10B0
