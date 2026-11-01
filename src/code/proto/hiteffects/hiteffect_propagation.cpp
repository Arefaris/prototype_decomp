// Fight items of the hit effects: PropagationTrack (unit 0x10510430 - 0x10511200; no assert path, the file name is a guess).
#include "code/proto/hiteffects/hiteffect_propagation.h"

namespace proto
{
	namespace HitEffectManager
	{
		fight::Property** gPropagationTrackProperties;  // 0x1126F69C

		// FUNCTION: ENGINE 0x10510960
		bool PropagationTrack::SetTimeBegin(float newValue)
		{
			timeBegin = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10510980
		bool PropagationTrack::SetMaxDeflection(float newValue)
		{
			maxDeflection = newValue * 0.017453292f;
			return true;
		}

		// FUNCTION: ENGINE 0x105109A0
		bool PropagationTrack::SetEnableDirection(bool newValue)
		{
			enableDirection = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x105109B0
		bool PropagationTrack::SetDirection(const math::Vector& newValue)
		{
			direction.x = newValue.x;
			direction.y = newValue.y;
			direction.z = newValue.z;
			return true;
		}

		// FUNCTION: ENGINE 0x105109D0
		bool PropagationTrack::SetDistance(float newValue)
		{
			distance = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x105109F0
		bool PropagationTrack::SetDamagePercentage(float newValue)
		{
			damagePercentage = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10510A10
		bool PropagationTrack::SetDamageType(int newValue)
		{
			damageType = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10510A20
		bool PropagationTrack::SetAttackType(int newValue)
		{
			attackType = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10510A60
		bool PropagationTrack::SetHitType(const fight::Name& newValue)
		{
			hitType = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10510A80
		bool PropagationTrack::SetEffectType(const fight::Name& newValue)
		{
			effectType = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x10510A30
		fight::Property* PropagationTrack::GetProperty(int index)
		{
			return gPropagationTrackProperties[index];
		}

		// FUNCTION: ENGINE 0x10510A50
		void PropagationTrack::ClearProperties()
		{
			fight::FreePropertyList(&gPropagationTrackProperties);
		}

		// FUNCTION: ENGINE 0x10510AA0
		PropagationTrack::PropagationTrack() : direction(0.0f, 0.0f, -1.0f), damagePercentage(5e+01f), distance(5.0f), maxDeflection(0.0f), timeBegin(0.0f), attackType(0), damageType(0), enableDirection(false)
		{
		}

		// FUNCTION: ENGINE 0x10510B30
		float PropagationTrack::GetTimeBegin() const
		{
			return timeBegin;
		}

		// FUNCTION: ENGINE 0x10503750
		float PropagationTrack::Slot10() const
		{
			return 0.0f;
		}

		// FUNCTION: ENGINE 0x10510B40
		PropagationTrack::~PropagationTrack()
		{
		}

		// FUNCTION: ENGINE 0x10510E60
		// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
		void PropagationTrack::RegisterProperties()
		{
			if (gPropagationTrackProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyFloatConstRange<PropagationTrack>("timeBegin", &PropagationTrack::SetTimeBegin);
				properties[0] = property;
				property = new fight::PropertyFloatConstRange<PropagationTrack>("maxDeflection", &PropagationTrack::SetMaxDeflection);
				properties[1] = property;
				property = new fight::PropertyBool<PropagationTrack>("enableDirection", &PropagationTrack::SetEnableDirection);
				properties[2] = property;
				property = new fight::PropertyVector<PropagationTrack>("direction", &PropagationTrack::SetDirection);
				properties[3] = property;
				property = new fight::PropertyFloatConstRange<PropagationTrack>("distance", &PropagationTrack::SetDistance);
				properties[4] = property;
				property = new fight::PropertyFloatConstRange<PropagationTrack>("damagePercentage", &PropagationTrack::SetDamagePercentage);
				properties[5] = property;
				property = new fight::PropertyEnumConstList<PropagationTrack>("damageType", gDamageTypeConditionDamageTypeTable, gDamageTypeConditionDamageTypeCount, &PropagationTrack::SetDamageType);
				properties[6] = property;
				property = new fight::PropertyEnumConstList<PropagationTrack>("attackType", gAttackTypeConditionAttackTypeTable, gAttackTypeConditionAttackTypeCount, &PropagationTrack::SetAttackType);
				properties[7] = property;
				property = new fight::PropertyNameList<PropagationTrack>("hitType", &PropagationTrack::SetHitType);
				properties[8] = property;
				property = new fight::PropertyNameList<PropagationTrack>("effectType", &PropagationTrack::SetEffectType);
				properties[9] = property;
				fight::RegisterPropertyList(properties, &gPropagationTrackProperties);
			}
		}

		// FUNCTION: ENGINE 0x10510DA0
		fight::TrackFactory* CreatePropagationTrackFactory(const char* name)
		{
			fight::TrackFactoryCasterTemplate<PropagationTrack> caster;
			return fight::FindTrackFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x10510DD0
		void RegisterPropagationTrackFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::TrackFactoryCasterTemplate<PropagationTrack> caster;
			registry->AddFactory(fight::FindTrackFactory(name, &caster));
		}

		template class fight::PropertyFloatConstRange<PropagationTrack>;
		template class fight::PropertyBool<PropagationTrack>;
		template class fight::PropertyVector<PropagationTrack>;
		template class fight::PropertyEnumConstList<PropagationTrack>;
		template class fight::PropertyNameList<PropagationTrack>;
		template class fight::TrackFactoryTemplate<PropagationTrack>;
		template class fight::TrackFactoryCasterTemplate<PropagationTrack>;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10510B50
// FUNCTION: ENGINE 0x10510B60
// FUNCTION: ENGINE 0x10510B90
// FUNCTION: ENGINE 0x10510BC0
// FUNCTION: ENGINE 0x10510BF0
// FUNCTION: ENGINE 0x10510C20
// FUNCTION: ENGINE 0x10510C30
// FUNCTION: ENGINE 0x10510C60
// FUNCTION: ENGINE 0x10510C80
// FUNCTION: ENGINE 0x10510C90
// FUNCTION: ENGINE 0x10510CC0
// FUNCTION: ENGINE 0x10510CE0
// FUNCTION: ENGINE 0x10510CF0
// FUNCTION: ENGINE 0x10510D30
// FUNCTION: ENGINE 0x10510D40
// FUNCTION: ENGINE 0x10510D70
// FUNCTION: ENGINE 0x10510D90
// FUNCTION: ENGINE 0x10510E00
// FUNCTION: ENGINE 0x10510E30
// FUNCTION: ENGINE 0x10510E50
// FUNCTION: ENGINE 0x10511150
// FUNCTION: ENGINE 0x10511180
// FUNCTION: ENGINE 0x105111A0
