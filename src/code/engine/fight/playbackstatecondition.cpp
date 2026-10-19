// The fight condition that tests the state of a playback (unit 0x10812C10 - 0x10812F90).
#include "code/engine/fight/playbackstatecondition.h"

namespace engine
{
	extern fight::EnumEntry gEqualityOperatorTable[];
	extern const int gEqualityOperatorCount;

	fight::Property** gPlaybackStateConditionProperties;  // 0x11284BF0

	// FUNCTION: ENGINE 0x10812C10
	bool PlaybackStateCondition::SetCompare(int newValue)
	{
		compare = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10812C40
	bool PlaybackStateCondition::SetState(const fight::Name& newValue)
	{
		state = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10812C60
	bool PlaybackStateCondition::SetSpecificPlaybackSet(const fight::Name& newValue)
	{
		specificPlaybackSet = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10812C20
	fight::Property* PlaybackStateCondition::GetProperty(int index)
	{
		return gPlaybackStateConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x10812C30
	void PlaybackStateCondition::ClearProperties()
	{
		fight::FreePropertyList(&gPlaybackStateConditionProperties);
	}

	// FUNCTION: ENGINE 0x10812C80
	// ctor stores: [('mov', 'dword', 0, '0x10e6d020'), ('mov', 'dword', 32, '0')]
	PlaybackStateCondition::PlaybackStateCondition() : fight::Condition(0), compare(0)
	{
	}

	// TODO Evaluate at 0x108B94F0: mov eax, dword ptr [esp + 0xc]; sub esp, 0x30; push ebx; push esi; push edi; mov esi, ecx; push eax; lea ecx, [esp + 0x4c]; push ecx; call 0x107fc7a0; mov eax, dword ptr [esp + 0x50]; add esp, 8; cmp 

	// FUNCTION: ENGINE 0x10812CB0
	PlaybackStateCondition::~PlaybackStateCondition()
	{
	}

	// FUNCTION: ENGINE 0x10812E40
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void PlaybackStateCondition::RegisterProperties()
	{
		if (gPlaybackStateConditionProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyEnumConstList<PlaybackStateCondition>("compare", gEqualityOperatorTable, gEqualityOperatorCount, &PlaybackStateCondition::SetCompare);
			properties[0] = property;
			property = new fight::PropertyName<PlaybackStateCondition>("state", &PlaybackStateCondition::SetState);
			properties[1] = property;
			property = new fight::PropertyName<PlaybackStateCondition>("specificPlaybackSet", &PlaybackStateCondition::SetSpecificPlaybackSet);
			properties[2] = property;
			fight::RegisterPropertyList(properties, &gPlaybackStateConditionProperties);
		}
	}

	// FUNCTION: ENGINE 0x10812DB0
	fight::ConditionFactory* CreatePlaybackStateConditionFactory(const char* name)
	{
		fight::ConditionFactoryCasterTemplate<PlaybackStateCondition> caster;
		return fight::FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x10812DD0
	void RegisterPlaybackStateConditionFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::ConditionFactoryCasterTemplate<PlaybackStateCondition> caster;
		registry->AddFactory(fight::FindConditionFactory(name, &caster));
	}

	template class fight::PropertyEnumConstList<PlaybackStateCondition>;
	template class fight::PropertyName<PlaybackStateCondition>;
	template class fight::ConditionFactoryTemplate<PlaybackStateCondition>;
	template class fight::ConditionFactoryCasterTemplate<PlaybackStateCondition>;

}
