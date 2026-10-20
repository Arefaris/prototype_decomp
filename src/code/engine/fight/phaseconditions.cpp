// The fight conditions on a keyboard key and on a puppet's animation phase (unit 0x108B8E50 - 0x108B94F0; no assert path, file name guessed).
#include "code/engine/fight/phaseconditions.h"

namespace engine
{
	fight::Property** gPCKeyboardConditionProperties;  // 0x1131848C

	// FUNCTION: ENGINE 0x108B8EA0
	fight::Property* PCKeyboardCondition::GetProperty(int index)
	{
		return gPCKeyboardConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x108B8EB0
	void PCKeyboardCondition::ClearProperties()
	{
		fight::FreePropertyList(&gPCKeyboardConditionProperties);
	}

	// FUNCTION: ENGINE 0x108B8EC0
	// ctor stores: [('mov', 'dword', 0, '0x10e7d0b8')]
	PCKeyboardCondition::PCKeyboardCondition() : fight::Condition(0)
	{
	}

	// TODO Evaluate at 0x108FCE80: sub esp, 8; push esi; mov esi, dword ptr [0x11283cb4]; test esi, esi; je 0x108fceb7; push 0; push 0; push 0; push 0x10df274c; lea ecx, [esp + 0x14]; call 0x1002355b; push eax; mov ecx, esi; call 0x107

	// FUNCTION: ENGINE 0x108B8EE0
	PCKeyboardCondition::~PCKeyboardCondition()
	{
	}

	// FUNCTION: ENGINE 0x108B8E50
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void PCKeyboardCondition::RegisterProperties()
	{
		if (gPCKeyboardConditionProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			fight::RegisterPropertyList(properties, &gPCKeyboardConditionProperties);
		}
	}

	// FUNCTION: ENGINE 0x108B8FE0
	fight::ConditionFactory* CreatePCKeyboardConditionFactory(const char* name)
	{
		fight::ConditionFactoryCasterTemplate<PCKeyboardCondition> caster;
		return fight::FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108B9000
	void RegisterPCKeyboardConditionFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::ConditionFactoryCasterTemplate<PCKeyboardCondition> caster;
		registry->AddFactory(fight::FindConditionFactory(name, &caster));
	}

	template class fight::ConditionFactoryTemplate<PCKeyboardCondition>;
	template class fight::ConditionFactoryCasterTemplate<PCKeyboardCondition>;

	namespace animation
	{
		extern fight::EnumEntry gPuppetPhaseConditionPositionConditionTypeTable[];
		extern fight::EnumEntry gPuppetPhaseConditionVelocityConditionTypeTable[];

		fight::Property** gPuppetPhaseConditionProperties;  // 0x11318490

		// FUNCTION: ENGINE 0x108B9030
		bool PuppetPhaseCondition::SetPositionConditionType(int newValue)
		{
			positionConditionType = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B9040
		bool PuppetPhaseCondition::SetMinPositionPhase(float newValue)
		{
			minPositionPhase = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B9050
		bool PuppetPhaseCondition::SetMaxPositionPhase(float newValue)
		{
			maxPositionPhase = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B9060
		bool PuppetPhaseCondition::SetVelocityConditionType(int newValue)
		{
			velocityConditionType = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B9070
		bool PuppetPhaseCondition::SetMinVelocityPhase(float newValue)
		{
			minVelocityPhase = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B9080
		bool PuppetPhaseCondition::SetMaxVelocityPhase(float newValue)
		{
			maxVelocityPhase = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108B9090
		fight::Property* PuppetPhaseCondition::GetProperty(int index)
		{
			return gPuppetPhaseConditionProperties[index];
		}

		// FUNCTION: ENGINE 0x108B90A0
		void PuppetPhaseCondition::ClearProperties()
		{
			fight::FreePropertyList(&gPuppetPhaseConditionProperties);
		}

		// FUNCTION: ENGINE 0x108B90B0
		// ctor stores: [('movss', 'dword', 12, '1.0f'), ('movss', 'dword', 16, '1.0f'), ('mov', 'dword', 0, '0x10e7d118'), ('movss', 'dword', 20, '0.0f'), ('movss', 'dword', 24, '0.0f'), ('mov', 'dword', 28, '0'), ('mov', 'dword', 32, '0')]
		PuppetPhaseCondition::PuppetPhaseCondition() : fight::Condition(0), maxPositionPhase(1.0f), maxVelocityPhase(1.0f), minPositionPhase(0.0f), minVelocityPhase(0.0f), positionConditionType(0), velocityConditionType(0)
		{
		}

		// TODO Evaluate at 0x108FCFF0: mov eax, dword ptr [esp + 0xc]; push edi; mov edi, ecx; push eax; lea ecx, [esp + 0x14]; push ecx; call 0x107fc7a0; movzx ecx, word ptr [eax]; add esp, 8; cmp cx, 0xffff; je 0x108fd02b; movzx edx, cx;

		// FUNCTION: ENGINE 0x108B9100
		PuppetPhaseCondition::~PuppetPhaseCondition()
		{
		}

		// FUNCTION: ENGINE 0x108B9270
		// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
		// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
		void PuppetPhaseCondition::RegisterProperties()
		{
			if (gPuppetPhaseConditionProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyEnumConstList<PuppetPhaseCondition>("positionConditionType", gPuppetPhaseConditionPositionConditionTypeTable, 2, &PuppetPhaseCondition::SetPositionConditionType);
				properties[0] = property;
				property = new fight::PropertyFloatConstRange<PuppetPhaseCondition>("minPositionPhase", &PuppetPhaseCondition::SetMinPositionPhase);
				properties[1] = property;
				property = new fight::PropertyFloatConstRange<PuppetPhaseCondition>("maxPositionPhase", &PuppetPhaseCondition::SetMaxPositionPhase);
				properties[2] = property;
				property = new fight::PropertyEnumConstList<PuppetPhaseCondition>("velocityConditionType", gPuppetPhaseConditionVelocityConditionTypeTable, 2, &PuppetPhaseCondition::SetVelocityConditionType);
				properties[3] = property;
				property = new fight::PropertyFloatConstRange<PuppetPhaseCondition>("minVelocityPhase", &PuppetPhaseCondition::SetMinVelocityPhase);
				properties[4] = property;
				property = new fight::PropertyFloatConstRange<PuppetPhaseCondition>("maxVelocityPhase", &PuppetPhaseCondition::SetMaxVelocityPhase);
				properties[5] = property;
				fight::RegisterPropertyList(properties, &gPuppetPhaseConditionProperties);
			}
		}

		// FUNCTION: ENGINE 0x108B9250
		fight::ConditionFactory* CreatePuppetPhaseConditionFactory(const char* name)
		{
			fight::ConditionFactoryCasterTemplate<PuppetPhaseCondition> caster;
			return fight::FindConditionFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x108B9400
		void RegisterPuppetPhaseConditionFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::ConditionFactoryCasterTemplate<PuppetPhaseCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}

		template class fight::PropertyEnumConstList<PuppetPhaseCondition>;
		template class fight::PropertyFloatConstRange<PuppetPhaseCondition>;
		template class fight::ConditionFactoryTemplate<PuppetPhaseCondition>;
		template class fight::ConditionFactoryCasterTemplate<PuppetPhaseCondition>;
	}

}
