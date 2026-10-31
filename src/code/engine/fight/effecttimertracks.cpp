// The fight tracks and conditions that clear decals, time effects and drive shader animations (unit 0x10810E00 - 0x10812300).
#include "code/engine/fight/effecttimertracks.h"

namespace engine
{
	fight::Property** gDeleteAllDecalsTrackProperties;  // 0x11284BA0

	// FUNCTION: ENGINE 0x10810E00
	bool DeleteAllDecalsTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10810E10
	fight::Property* DeleteAllDecalsTrack::GetProperty(int index)
	{
		return gDeleteAllDecalsTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x10810E20
	void DeleteAllDecalsTrack::ClearProperties()
	{
		fight::FreePropertyList(&gDeleteAllDecalsTrackProperties);
	}

	// FUNCTION: ENGINE 0x10810E30
	// ctor stores: [('mov', 'dword', 0, '0x10e6c8d4'), ('movss', 'dword', 16, '0.0f')]
	DeleteAllDecalsTrack::DeleteAllDecalsTrack() : timeBegin(0.0f)
	{
	}

	// FUNCTION: ENGINE 0x10810E50
	float DeleteAllDecalsTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x10810E60
	float DeleteAllDecalsTrack::Slot10() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x10810E70
	DeleteAllDecalsTrack::~DeleteAllDecalsTrack()
	{
	}

	// FUNCTION: ENGINE 0x10810F50
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void DeleteAllDecalsTrack::RegisterProperties()
	{
		if (gDeleteAllDecalsTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<DeleteAllDecalsTrack>("timeBegin", &DeleteAllDecalsTrack::SetTimeBegin);
			properties[0] = property;
			fight::RegisterPropertyList(properties, &gDeleteAllDecalsTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x10810F30
	fight::TrackFactory* CreateDeleteAllDecalsTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<DeleteAllDecalsTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x10810FD0
	void RegisterDeleteAllDecalsTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<DeleteAllDecalsTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyFloatConstRange<DeleteAllDecalsTrack>;
	template class fight::TrackFactoryTemplate<DeleteAllDecalsTrack>;
	template class fight::TrackFactoryCasterTemplate<DeleteAllDecalsTrack>;

	extern fight::EnumEntry gCompareOperatorTable[];
	extern const int gCompareOperatorCount;

	fight::Property** gCheckEffectTimerConditionProperties;  // 0x11284BA4

	// FUNCTION: ENGINE 0x10811090
	bool CheckEffectTimerCondition::SetCompare(int newValue)
	{
		compare = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108110A0
	bool CheckEffectTimerCondition::SetTimeElapsed(float newValue)
	{
		timeElapsed = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108110D0
	bool CheckEffectTimerCondition::SetTimerName(const fight::Name& newValue)
	{
		timerName = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108110B0
	fight::Property* CheckEffectTimerCondition::GetProperty(int index)
	{
		return gCheckEffectTimerConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x108110C0
	void CheckEffectTimerCondition::ClearProperties()
	{
		fight::FreePropertyList(&gCheckEffectTimerConditionProperties);
	}

	// FUNCTION: ENGINE 0x108110F0
	// ctor stores: [('mov', 'dword', 0, '0x10e6c968'), ('movss', 'dword', 24, '0.0f'), ('mov', 'dword', 28, '0')]
	CheckEffectTimerCondition::CheckEffectTimerCondition() : fight::Condition(0), timeElapsed(0.0f), compare(0)
	{
	}

	// TODO Evaluate at 0x108AC940: sub esp, 8; push ebx; push ebp; push esi; push edi; mov esi, ecx; call 0x108193a0; mov ebp, dword ptr [esi + 0x1c]; mov edi, eax; lea ebx, [esi + 0x10]; push ebx; mov ecx, edi; call 0x1081d030; test a

	// FUNCTION: ENGINE 0x10811120
	CheckEffectTimerCondition::~CheckEffectTimerCondition()
	{
	}

	// FUNCTION: ENGINE 0x10811300
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void CheckEffectTimerCondition::RegisterProperties()
	{
		if (gCheckEffectTimerConditionProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyName<CheckEffectTimerCondition>("timerName", &CheckEffectTimerCondition::SetTimerName);
			properties[0] = property;
			property = new fight::PropertyEnumConstList<CheckEffectTimerCondition>("compare", gCompareOperatorTable, gCompareOperatorCount, &CheckEffectTimerCondition::SetCompare);
			properties[1] = property;
			property = new fight::PropertyFloatConstRange<CheckEffectTimerCondition>("timeElapsed", &CheckEffectTimerCondition::SetTimeElapsed);
			properties[2] = property;
			fight::RegisterPropertyList(properties, &gCheckEffectTimerConditionProperties);
		}
	}

	// FUNCTION: ENGINE 0x10811270
	fight::ConditionFactory* CreateCheckEffectTimerConditionFactory(const char* name)
	{
		fight::ConditionFactoryCasterTemplate<CheckEffectTimerCondition> caster;
		return fight::FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x10811290
	void RegisterCheckEffectTimerConditionFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::ConditionFactoryCasterTemplate<CheckEffectTimerCondition> caster;
		registry->AddFactory(fight::FindConditionFactory(name, &caster));
	}

	template class fight::PropertyEnumConstList<CheckEffectTimerCondition>;
	template class fight::PropertyFloatConstRange<CheckEffectTimerCondition>;
	template class fight::PropertyName<CheckEffectTimerCondition>;
	template class fight::ConditionFactoryTemplate<CheckEffectTimerCondition>;
	template class fight::ConditionFactoryCasterTemplate<CheckEffectTimerCondition>;

	fight::Property** gSetEffectTimerTrackProperties;  // 0x11284BA8

	// FUNCTION: ENGINE 0x10811480
	bool SetEffectTimerTrack::SetTime(float newValue)
	{
		time = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108114B0
	bool SetEffectTimerTrack::SetName(const fight::Name& newValue)
	{
		name = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10811490
	fight::Property* SetEffectTimerTrack::GetProperty(int index)
	{
		return gSetEffectTimerTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108114A0
	void SetEffectTimerTrack::ClearProperties()
	{
		fight::FreePropertyList(&gSetEffectTimerTrackProperties);
	}

	// FUNCTION: ENGINE 0x108114D0
	// ctor stores: [('mov', 'dword', 0, '0x10e6ca44'), ('movss', 'dword', 24, '0.0f')]
	SetEffectTimerTrack::SetEffectTimerTrack() : time(0.0f)
	{
	}

	// FUNCTION: ENGINE 0x10811500
	float SetEffectTimerTrack::GetTimeBegin() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x10811510
	float SetEffectTimerTrack::Slot10() const
	{
		return -1.0f;
	}

	// FUNCTION: ENGINE 0x10811520
	SetEffectTimerTrack::~SetEffectTimerTrack()
	{
	}

	// FUNCTION: ENGINE 0x10811670
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void SetEffectTimerTrack::RegisterProperties()
	{
		if (gSetEffectTimerTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyName<SetEffectTimerTrack>("name", &SetEffectTimerTrack::SetName);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<SetEffectTimerTrack>("time", &SetEffectTimerTrack::SetTime);
			properties[1] = property;
			fight::RegisterPropertyList(properties, &gSetEffectTimerTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108115E0
	fight::TrackFactory* CreateSetEffectTimerTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<SetEffectTimerTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x10811600
	void RegisterSetEffectTimerTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<SetEffectTimerTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyFloatConstRange<SetEffectTimerTrack>;
	template class fight::PropertyName<SetEffectTimerTrack>;
	template class fight::TrackFactoryTemplate<SetEffectTimerTrack>;
	template class fight::TrackFactoryCasterTemplate<SetEffectTimerTrack>;

	namespace animation
	{
		fight::EnumEntry gShaderAnimationTrackCyclicTable[4] =
			{
				{ fight::Name("From Animation", 0) },
				{ fight::Name("Not Cyclic", 0) },
				{ fight::Name("Cyclic", 0) },
				{ fight::Name("Hold End Frame", 0) }
			};

		fight::Property** gShaderAnimationTrackProperties;  // 0x11284BB0

		// FUNCTION: ENGINE 0x108117B0
		bool ShaderAnimationTrack::SetTimeBegin(float newValue)
		{
			timeBegin = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108117C0
		bool ShaderAnimationTrack::SetTimeEnd(float newValue)
		{
			timeEnd = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108117D0
		bool ShaderAnimationTrack::SetRestoreStateOnEnd(bool newValue)
		{
			restoreStateOnEnd = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108117E0
		bool ShaderAnimationTrack::SetSpeed(float newValue)
		{
			speed = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108117F0
		bool ShaderAnimationTrack::SetInitFrame(float newValue)
		{
			initFrame = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10811800
		bool ShaderAnimationTrack::SetStartFrame(float newValue)
		{
			startFrame = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10811810
		bool ShaderAnimationTrack::SetEndFrame(float newValue)
		{
			endFrame = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10811820
		bool ShaderAnimationTrack::SetCyclic(int newValue)
		{
			cyclic = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10811850
		bool ShaderAnimationTrack::SetAnimation(const fight::Name& newValue)
		{
			animation = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10811830
		fight::Property* ShaderAnimationTrack::GetProperty(int index)
		{
			return gShaderAnimationTrackProperties[index];
		}

		// FUNCTION: ENGINE 0x10811840
		void ShaderAnimationTrack::ClearProperties()
		{
			fight::FreePropertyList(&gShaderAnimationTrackProperties);
		}

		// FUNCTION: ENGINE 0x10811870
		// ctor stores: [('mov', 'dword', 0, '0x10e6cb04'), ('movss', 'dword', 24, '-1.0f'), ('movss', 'dword', 28, '0.0f'), ('movss', 'dword', 32, '1.0f'), ('movss', 'dword', 36, '0.0f'), ('movss', 'dword', 40, '0.0f'), ('movss', 'dword', 44, '-1.0f'), ('mov', 'dword', 48, '0'), ('mov', 'byte', 52, '1')]
		ShaderAnimationTrack::ShaderAnimationTrack() : endFrame(-1.0f), initFrame(0.0f), speed(1.0f), startFrame(0.0f), timeBegin(0.0f), timeEnd(-1.0f), cyclic(0), restoreStateOnEnd(1)
		{
		}

		// FUNCTION: ENGINE 0x108118D0
		float ShaderAnimationTrack::GetTimeBegin() const
		{
			return timeBegin;
		}

		// FUNCTION: ENGINE 0x108118E0
		float ShaderAnimationTrack::Slot10() const
		{
			return timeEnd - timeBegin;
		}

		// FUNCTION: ENGINE 0x108118F0
		ShaderAnimationTrack::~ShaderAnimationTrack()
		{
		}

		// FUNCTION: ENGINE 0x10811B20
		// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
		// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
		void ShaderAnimationTrack::RegisterProperties()
		{
			if (gShaderAnimationTrackProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyFloatConstRange<ShaderAnimationTrack>("timeBegin", &ShaderAnimationTrack::SetTimeBegin);
				properties[0] = property;
				property = new fight::PropertyFloatConstRange<ShaderAnimationTrack>("timeEnd", &ShaderAnimationTrack::SetTimeEnd);
				properties[1] = property;
				property = new fight::PropertyBool<ShaderAnimationTrack>("restoreStateOnEnd", &ShaderAnimationTrack::SetRestoreStateOnEnd);
				properties[2] = property;
				property = new fight::PropertyName<ShaderAnimationTrack>("animation", &ShaderAnimationTrack::SetAnimation);
				properties[3] = property;
				property = new fight::PropertyFloatConstRange<ShaderAnimationTrack>("speed", &ShaderAnimationTrack::SetSpeed);
				properties[4] = property;
				property = new fight::PropertyFloatConstRange<ShaderAnimationTrack>("initFrame", &ShaderAnimationTrack::SetInitFrame);
				properties[5] = property;
				property = new fight::PropertyFloatConstRange<ShaderAnimationTrack>("startFrame", &ShaderAnimationTrack::SetStartFrame);
				properties[6] = property;
				property = new fight::PropertyFloatConstRange<ShaderAnimationTrack>("endFrame", &ShaderAnimationTrack::SetEndFrame);
				properties[7] = property;
				property = new fight::PropertyEnumConstList<ShaderAnimationTrack>("cyclic", gShaderAnimationTrackCyclicTable, 4, &ShaderAnimationTrack::SetCyclic);
				properties[8] = property;
				fight::RegisterPropertyList(properties, &gShaderAnimationTrackProperties);
			}
		}

		// FUNCTION: ENGINE 0x10811A90
		fight::TrackFactory* CreateShaderAnimationTrackFactory(const char* name)
		{
			fight::TrackFactoryCasterTemplate<ShaderAnimationTrack> caster;
			return fight::FindTrackFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x10811AB0
		void RegisterShaderAnimationTrackFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::TrackFactoryCasterTemplate<ShaderAnimationTrack> caster;
			registry->AddFactory(fight::FindTrackFactory(name, &caster));
		}

		template class fight::PropertyBool<ShaderAnimationTrack>;
		template class fight::PropertyEnumConstList<ShaderAnimationTrack>;
		template class fight::PropertyFloatConstRange<ShaderAnimationTrack>;
		template class fight::PropertyName<ShaderAnimationTrack>;
		template class fight::TrackFactoryTemplate<ShaderAnimationTrack>;
		template class fight::TrackFactoryCasterTemplate<ShaderAnimationTrack>;
	}

}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D74B70
// FUNCTION: ENGINE 0x10D8A000
