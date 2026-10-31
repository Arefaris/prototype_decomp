// The fight conditions that test health, object templates, attributes and velocities (unit 0x1080A6B0 - 0x1080BA40).
#include "code/engine/fight/conditions.h"

namespace engine
{
	extern fight::EnumEntry gCompareOperatorTable[];
	extern const int gCompareOperatorCount;

	fight::Property** gHealthConditionProperties;  // 0x11284B64

	// FUNCTION: ENGINE 0x1080A6B0
	bool HealthCondition::SetCompare(int newValue)
	{
		compare = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080A6C0
	bool HealthCondition::SetHealthThreshold(float newValue)
	{
		healthThreshold = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080A6D0
	bool HealthCondition::SetUsePercentage(bool newValue)
	{
		usePercentage = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080A6E0
	fight::Property* HealthCondition::GetProperty(int index)
	{
		return gHealthConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x1080A6F0
	void HealthCondition::ClearProperties()
	{
		fight::FreePropertyList(&gHealthConditionProperties);
	}

	// FUNCTION: ENGINE 0x1080A700
	// ctor stores: [('mov', 'dword', 0, '0x10e6ba48'), ('movss', 'dword', 12, '0.0f'), ('mov', 'dword', 16, '0'), ('mov', 'byte', 20, '0')]
	HealthCondition::HealthCondition() : fight::Condition(0), healthThreshold(0.0f), compare(0), usePercentage(false)
	{
	}

	// TODO Evaluate at 0x108AACC0: mov eax, dword ptr [esp + 0xc]; sub esp, 0x1c; push esi; mov esi, ecx; push eax; lea ecx, [esp + 0x30]; push ecx; call 0x107fc7a0; mov eax, dword ptr [esp + 0x34]; add esp, 8; cmp ax, 0xffff; je 0x108

	// FUNCTION: ENGINE 0x1080A730
	HealthCondition::~HealthCondition()
	{
	}

	// FUNCTION: ENGINE 0x1080A8F0
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void HealthCondition::RegisterProperties()
	{
		if (gHealthConditionProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyEnumConstList<HealthCondition>("compare", gCompareOperatorTable, gCompareOperatorCount, &HealthCondition::SetCompare);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<HealthCondition>("healthThreshold", &HealthCondition::SetHealthThreshold);
			properties[1] = property;
			property = new fight::PropertyBool<HealthCondition>("usePercentage", &HealthCondition::SetUsePercentage);
			properties[2] = property;
			fight::RegisterPropertyList(properties, &gHealthConditionProperties);
		}
	}

	// FUNCTION: ENGINE 0x1080A8D0
	fight::ConditionFactory* CreateHealthConditionFactory(const char* name)
	{
		fight::ConditionFactoryCasterTemplate<HealthCondition> caster;
		return fight::FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x1080A9E0
	void RegisterHealthConditionFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::ConditionFactoryCasterTemplate<HealthCondition> caster;
		registry->AddFactory(fight::FindConditionFactory(name, &caster));
	}

	template class fight::PropertyBool<HealthCondition>;
	template class fight::PropertyEnumConstList<HealthCondition>;
	template class fight::PropertyFloatConstRange<HealthCondition>;
	template class fight::ConditionFactoryTemplate<HealthCondition>;
	template class fight::ConditionFactoryCasterTemplate<HealthCondition>;

	extern fight::EnumEntry gEqualityOperatorTable[];
	extern const int gEqualityOperatorCount;

	fight::Property** gObjectTemplateConditionProperties;  // 0x11284B68

	// FUNCTION: ENGINE 0x1080AAA0
	bool ObjectTemplateCondition::SetCompare(int newValue)
	{
		compare = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080AAD0
	bool ObjectTemplateCondition::SetObjectTemplate(const fight::Name& newValue)
	{
		objectTemplate = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080AAB0
	fight::Property* ObjectTemplateCondition::GetProperty(int index)
	{
		return gObjectTemplateConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x1080AAC0
	void ObjectTemplateCondition::ClearProperties()
	{
		fight::FreePropertyList(&gObjectTemplateConditionProperties);
	}

	// FUNCTION: ENGINE 0x1080AAF0
	// ctor stores: [('mov', 'dword', 0, '0x10e6bb34'), ('mov', 'dword', 24, '0')]
	ObjectTemplateCondition::ObjectTemplateCondition() : fight::Condition(0), compare(0)
	{
	}

	// TODO Evaluate at 0x1082B9A0: push ecx; mov eax, dword ptr [esp + 0x10]; push esi; mov esi, ecx; push eax; lea ecx, [esp + 0x18]; push ecx; call 0x107fc7a0; mov eax, dword ptr [esp + 0x1c]; lea edx, [esi + 0x10]; push edx; push ea

	// FUNCTION: ENGINE 0x1080AB20
	ObjectTemplateCondition::~ObjectTemplateCondition()
	{
	}

	// FUNCTION: ENGINE 0x1080ACB0
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void ObjectTemplateCondition::RegisterProperties()
	{
		if (gObjectTemplateConditionProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyEnumConstList<ObjectTemplateCondition>("compare", gEqualityOperatorTable, gEqualityOperatorCount, &ObjectTemplateCondition::SetCompare);
			properties[0] = property;
			property = new fight::PropertyName<ObjectTemplateCondition>("objectTemplate", &ObjectTemplateCondition::SetObjectTemplate);
			properties[1] = property;
			fight::RegisterPropertyList(properties, &gObjectTemplateConditionProperties);
		}
	}

	// FUNCTION: ENGINE 0x1080AC20
	fight::ConditionFactory* CreateObjectTemplateConditionFactory(const char* name)
	{
		fight::ConditionFactoryCasterTemplate<ObjectTemplateCondition> caster;
		return fight::FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x1080AC40
	void RegisterObjectTemplateConditionFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::ConditionFactoryCasterTemplate<ObjectTemplateCondition> caster;
		registry->AddFactory(fight::FindConditionFactory(name, &caster));
	}

	template class fight::PropertyEnumConstList<ObjectTemplateCondition>;
	template class fight::PropertyName<ObjectTemplateCondition>;
	template class fight::ConditionFactoryTemplate<ObjectTemplateCondition>;
	template class fight::ConditionFactoryCasterTemplate<ObjectTemplateCondition>;

	extern fight::EnumEntry gEqualityOperatorTable[];
	extern const int gEqualityOperatorCount;

	fight::Property** gAttributeNameConditionProperties;  // 0x11284B6C

	// FUNCTION: ENGINE 0x1080AE00
	bool AttributeNameCondition::SetCompare(int newValue)
	{
		compare = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080AE30
	bool AttributeNameCondition::SetKey(const fight::Name& newValue)
	{
		key = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080AE50
	bool AttributeNameCondition::SetValue(const fight::Name& newValue)
	{
		value = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080AE10
	fight::Property* AttributeNameCondition::GetProperty(int index)
	{
		return gAttributeNameConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x1080AE20
	void AttributeNameCondition::ClearProperties()
	{
		fight::FreePropertyList(&gAttributeNameConditionProperties);
	}

	// FUNCTION: ENGINE 0x1080AE70
	// ctor stores: [('mov', 'dword', 0, '0x10e6bbe0'), ('mov', 'dword', 32, '0')]
	AttributeNameCondition::AttributeNameCondition() : fight::Condition(0), compare(0)
	{
	}

	// TODO Evaluate at 0x108AADE0: mov eax, dword ptr [esp + 0xc]; push esi; mov esi, ecx; push eax; lea ecx, [esp + 0x14]; push ecx; call 0x107fc7a0; mov eax, dword ptr [esp + 0x18]; add esp, 8; cmp ax, 0xffff; je 0x108aae1b; movzx ed

	// FUNCTION: ENGINE 0x1080AEA0
	AttributeNameCondition::~AttributeNameCondition()
	{
	}

	// FUNCTION: ENGINE 0x1080B030
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void AttributeNameCondition::RegisterProperties()
	{
		if (gAttributeNameConditionProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyName<AttributeNameCondition>("key", &AttributeNameCondition::SetKey);
			properties[0] = property;
			property = new fight::PropertyEnumConstList<AttributeNameCondition>("compare", gEqualityOperatorTable, gEqualityOperatorCount, &AttributeNameCondition::SetCompare);
			properties[1] = property;
			property = new fight::PropertyName<AttributeNameCondition>("value", &AttributeNameCondition::SetValue);
			properties[2] = property;
			fight::RegisterPropertyList(properties, &gAttributeNameConditionProperties);
		}
	}

	// FUNCTION: ENGINE 0x1080AFA0
	fight::ConditionFactory* CreateAttributeNameConditionFactory(const char* name)
	{
		fight::ConditionFactoryCasterTemplate<AttributeNameCondition> caster;
		return fight::FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x1080AFC0
	void RegisterAttributeNameConditionFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::ConditionFactoryCasterTemplate<AttributeNameCondition> caster;
		registry->AddFactory(fight::FindConditionFactory(name, &caster));
	}

	template class fight::PropertyEnumConstList<AttributeNameCondition>;
	template class fight::PropertyName<AttributeNameCondition>;
	template class fight::ConditionFactoryTemplate<AttributeNameCondition>;
	template class fight::ConditionFactoryCasterTemplate<AttributeNameCondition>;

	namespace animation
	{
		fight::EnumEntry gVelocityTypeTable[2] =
			{
				{ fight::Name("Locomotion", 0) },
				{ fight::Name("Physics", 0) }
			};
		extern const int gVelocityTypeCount;
		fight::EnumEntry gVelocityDirectionTable[8] =
			{
				{ fight::Name("X", 0) },
				{ fight::Name("Y", 0) },
				{ fight::Name("Z", 0) },
				{ fight::Name("XZ", 0) },
				{ fight::Name("Magnitude", 0) },
				{ fight::Name("AbsX", 0) },
				{ fight::Name("AbsY", 0) },
				{ fight::Name("AbsZ", 0) }
			};
		extern const int gVelocityDirectionCount;
		extern fight::EnumEntry gCompareOperatorTable[];
		extern const int gCompareOperatorCount;

		fight::Property** gVelocityConditionProperties;  // 0x11284B70

		// FUNCTION: ENGINE 0x1080B1B0
		bool VelocityCondition::SetType(int newValue)
		{
			type = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x1080B1C0
		bool VelocityCondition::SetDirection(int newValue)
		{
			direction = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x1080B1D0
		bool VelocityCondition::SetCompare(int newValue)
		{
			compare = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x1080B1E0
		bool VelocityCondition::SetVelocity(float newValue)
		{
			velocity = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x1080B240
		fight::Property* VelocityCondition::GetProperty(int index)
		{
			return gVelocityConditionProperties[index];
		}

		// FUNCTION: ENGINE 0x1080B250
		void VelocityCondition::ClearProperties()
		{
			fight::FreePropertyList(&gVelocityConditionProperties);
		}

		// FUNCTION: ENGINE 0x1080B260
		// ctor stores: [('mov', 'dword', 0, '0x10e6bc8c'), ('movss', 'dword', 12, '0.0f'), ('mov', 'dword', 16, '0'), ('mov', 'dword', 20, '0'), ('mov', 'dword', 24, '0')]
		VelocityCondition::VelocityCondition() : fight::Condition(0), velocity(0.0f), compare(0), direction(0), type(0)
		{
		}

		// TODO Evaluate at 0x107F1C50: mov eax, dword ptr [esp + 0xc]; sub esp, 0xc; push esi; push edi; mov esi, ecx; push eax; lea ecx, [esp + 0x24]; push ecx; call 0x107fc7a0; movzx ecx, word ptr [eax]; add esp, 8; cmp cx, 0xffff; je 0x

		// FUNCTION: ENGINE 0x1080B2A0
		VelocityCondition::~VelocityCondition()
		{
		}

		// FUNCTION: ENGINE 0x1080B5E0
		// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
		// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
		void VelocityCondition::RegisterProperties()
		{
			if (gVelocityConditionProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyEnumConstList<VelocityCondition>("type", gVelocityTypeTable, gVelocityTypeCount, &VelocityCondition::SetType);
				properties[0] = property;
				property = new fight::PropertyEnumConstList<VelocityCondition>("direction", gVelocityDirectionTable, gVelocityDirectionCount, &VelocityCondition::SetDirection);
				properties[1] = property;
				property = new fight::PropertyEnumConstList<VelocityCondition>("compare", gCompareOperatorTable, gCompareOperatorCount, &VelocityCondition::SetCompare);
				properties[2] = property;
				property = new fight::PropertyFloatConstRange<VelocityCondition>("velocity", &VelocityCondition::SetVelocity);
				properties[3] = property;
				fight::RegisterPropertyList(properties, &gVelocityConditionProperties);
			}
		}

		// FUNCTION: ENGINE 0x1080B5A0
		fight::ConditionFactory* CreateVelocityConditionFactory(const char* name)
		{
			fight::ConditionFactoryCasterTemplate<VelocityCondition> caster;
			return fight::FindConditionFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x1080B860
		void RegisterVelocityConditionFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::ConditionFactoryCasterTemplate<VelocityCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}

		template class fight::PropertyEnumConstList<VelocityCondition>;
		template class fight::PropertyFloatConstRange<VelocityCondition>;
		template class fight::ConditionFactoryTemplate<VelocityCondition>;
		template class fight::ConditionFactoryCasterTemplate<VelocityCondition>;
	}

	namespace animation
	{
		extern fight::EnumEntry gVelocityTypeTable[];
		extern const int gVelocityTypeCount;
		extern fight::EnumEntry gVelocityDirectionTable[];
		extern const int gVelocityDirectionCount;
		extern fight::EnumEntry gCompareOperatorTable[];
		extern const int gCompareOperatorCount;

		fight::Property** gVelocityAngularConditionProperties;  // 0x11284B74

		// FUNCTION: ENGINE 0x1080B1F0
		bool VelocityAngularCondition::SetType(int newValue)
		{
			type = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x1080B200
		bool VelocityAngularCondition::SetDirection(int newValue)
		{
			direction = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x1080B210
		bool VelocityAngularCondition::SetCompare(int newValue)
		{
			compare = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x1080B220
		bool VelocityAngularCondition::SetAngularVelocity(float newValue)
		{
			// Degrees per second in the property, radians per second in the condition
			angularVelocity = newValue * 0.017453292f;
			return true;
		}

		// FUNCTION: ENGINE 0x1080B2B0
		fight::Property* VelocityAngularCondition::GetProperty(int index)
		{
			return gVelocityAngularConditionProperties[index];
		}

		// FUNCTION: ENGINE 0x1080B2C0
		void VelocityAngularCondition::ClearProperties()
		{
			fight::FreePropertyList(&gVelocityAngularConditionProperties);
		}

		// FUNCTION: ENGINE 0x1080B2D0
		// ctor stores: [('mov', 'dword', 0, '0x10e6bcb8'), ('movss', 'dword', 12, '0.0f'), ('mov', 'dword', 16, '4'), ('mov', 'dword', 20, '0'), ('mov', 'dword', 24, '0')]
		VelocityAngularCondition::VelocityAngularCondition() : fight::Condition(0), angularVelocity(0.0f), compare(4), direction(0), type(0)
		{
		}

		// TODO Evaluate at 0x107F1D00: mov eax, dword ptr [esp + 0xc]; sub esp, 0xc; push esi; push edi; mov esi, ecx; push eax; lea ecx, [esp + 0x24]; push ecx; call 0x107fc7a0; movzx ecx, word ptr [eax]; add esp, 8; cmp cx, 0xffff; je 0x

		// FUNCTION: ENGINE 0x1080B310
		VelocityAngularCondition::~VelocityAngularCondition()
		{
		}

		// FUNCTION: ENGINE 0x1080B720
		// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
		// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
		void VelocityAngularCondition::RegisterProperties()
		{
			if (gVelocityAngularConditionProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyEnumConstList<VelocityAngularCondition>("type", gVelocityTypeTable, gVelocityTypeCount, &VelocityAngularCondition::SetType);
				properties[0] = property;
				property = new fight::PropertyEnumConstList<VelocityAngularCondition>("direction", gVelocityDirectionTable, gVelocityDirectionCount, &VelocityAngularCondition::SetDirection);
				properties[1] = property;
				property = new fight::PropertyEnumConstList<VelocityAngularCondition>("compare", gCompareOperatorTable, gCompareOperatorCount, &VelocityAngularCondition::SetCompare);
				properties[2] = property;
				property = new fight::PropertyFloatConstRange<VelocityAngularCondition>("angularVelocity", &VelocityAngularCondition::SetAngularVelocity);
				properties[3] = property;
				fight::RegisterPropertyList(properties, &gVelocityAngularConditionProperties);
			}
		}

		// FUNCTION: ENGINE 0x1080B5C0
		fight::ConditionFactory* CreateVelocityAngularConditionFactory(const char* name)
		{
			fight::ConditionFactoryCasterTemplate<VelocityAngularCondition> caster;
			return fight::FindConditionFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x1080B890
		void RegisterVelocityAngularConditionFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::ConditionFactoryCasterTemplate<VelocityAngularCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}

		template class fight::PropertyEnumConstList<VelocityAngularCondition>;
		template class fight::PropertyFloatConstRange<VelocityAngularCondition>;
		template class fight::ConditionFactoryTemplate<VelocityAngularCondition>;
		template class fight::ConditionFactoryCasterTemplate<VelocityAngularCondition>;
	}

}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D74010
// FUNCTION: ENGINE 0x10D74040
// FUNCTION: ENGINE 0x10D89D00
// FUNCTION: ENGINE 0x10D89D10
