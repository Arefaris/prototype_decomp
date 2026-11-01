// Fight items of the damage tracks: DebugDamageTrack, CauseDamageTrack (unit 0x10503C60 - 0x105049C0; no assert path, the file name is a guess).
#include "code/proto/damage/damagetracks.h"

namespace proto
{
	fight::Property** gDebugDamageTrackProperties;  // 0x1126F66C

	// FUNCTION: ENGINE 0x10503C60
	bool DebugDamageTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10503C80
	bool DebugDamageTrack::SetDistance(float newValue)
	{
		distance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10503CA0
	bool DebugDamageTrack::SetDamageType(int newValue)
	{
		damageType = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10503CB0
	bool DebugDamageTrack::SetScaleX(float newValue)
	{
		scaleX = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10503CD0
	bool DebugDamageTrack::SetScaleY(float newValue)
	{
		scaleY = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10503DE0
	bool DebugDamageTrack::SetDamageSource(const fight::Name& newValue)
	{
		damageSource = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10503D80
	fight::Property* DebugDamageTrack::GetProperty(int index)
	{
		return gDebugDamageTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x10503DA0
	void DebugDamageTrack::ClearProperties()
	{
		fight::FreePropertyList(&gDebugDamageTrackProperties);
	}

	// FUNCTION: ENGINE 0x10503E20
	DebugDamageTrack::DebugDamageTrack() : distance(1e+03f), scaleX(1.0f), scaleY(1.0f), timeBegin(0.0f), damageType(0)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x10503E90
	float DebugDamageTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x10503EA0
	float DebugDamageTrack::Slot10() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x10503EB0
	DebugDamageTrack::~DebugDamageTrack()
	{
	}

	// FUNCTION: ENGINE 0x10504430
	// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
	void DebugDamageTrack::RegisterProperties()
	{
		if (gDebugDamageTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<DebugDamageTrack>("timeBegin", &DebugDamageTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<DebugDamageTrack>("distance", &DebugDamageTrack::SetDistance);
			properties[1] = property;
			property = new fight::PropertyEnumConstList<DebugDamageTrack>("damageType", gDebugDamageTrackDamageTypeTable, gDebugDamageTrackDamageTypeCount, &DebugDamageTrack::SetDamageType);
			properties[2] = property;
			property = new fight::PropertyFloatConstRange<DebugDamageTrack>("scaleX", &DebugDamageTrack::SetScaleX);
			properties[3] = property;
			property = new fight::PropertyFloatConstRange<DebugDamageTrack>("scaleY", &DebugDamageTrack::SetScaleY);
			properties[4] = property;
			property = new fight::PropertyName<DebugDamageTrack>("damageSource", &DebugDamageTrack::SetDamageSource);
			properties[5] = property;
			fight::RegisterPropertyList(properties, &gDebugDamageTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x105042C0
	fight::TrackFactory* CreateDebugDamageTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<DebugDamageTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x10504320
	void RegisterDebugDamageTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<DebugDamageTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	fight::Property** gCauseDamageTrackProperties;  // 0x1126F670

	// FUNCTION: ENGINE 0x10503CF0
	bool CauseDamageTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10503D10
	bool CauseDamageTrack::SetForceZeroHealth(bool newValue)
	{
		forceZeroHealth = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10503D20
	bool CauseDamageTrack::SetDamage(float newValue)
	{
		damage = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10503D40
	bool CauseDamageTrack::SetAttackType(int newValue)
	{
		attackType = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10503D50
	bool CauseDamageTrack::SetOriginator(int newValue)
	{
		originator = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10503E00
	bool CauseDamageTrack::SetGrabSlot(const fight::Name& newValue)
	{
		grabSlot = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10503D60
	bool CauseDamageTrack::SetIgnoreShield(bool newValue)
	{
		ignoreShield = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10503D70
	bool CauseDamageTrack::SetSendAlert(bool newValue)
	{
		sendAlert = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10503DB0
	fight::Property* CauseDamageTrack::GetProperty(int index)
	{
		return gCauseDamageTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x10503DD0
	void CauseDamageTrack::ClearProperties()
	{
		fight::FreePropertyList(&gCauseDamageTrackProperties);
	}

	// FUNCTION: ENGINE 0x10503EC0
	CauseDamageTrack::CauseDamageTrack() : damage(0.0f), timeBegin(0.0f), attackType(0), originator(0), forceZeroHealth(false), ignoreShield(true), sendAlert(true)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x10503F10
	float CauseDamageTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x10503F20
	float CauseDamageTrack::Slot10() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x10503F30
	CauseDamageTrack::~CauseDamageTrack()
	{
	}

	// FUNCTION: ENGINE 0x10504610
	// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
	void CauseDamageTrack::RegisterProperties()
	{
		if (gCauseDamageTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<CauseDamageTrack>("timeBegin", &CauseDamageTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyBool<CauseDamageTrack>("forceZeroHealth", &CauseDamageTrack::SetForceZeroHealth);
			properties[1] = property;
			property = new fight::PropertyFloatConstRange<CauseDamageTrack>("damage", &CauseDamageTrack::SetDamage);
			properties[2] = property;
			property = new fight::PropertyEnumConstList<CauseDamageTrack>("attackType", gCauseDamageTrackAttackTypeTable, gCauseDamageTrackAttackTypeCount, &CauseDamageTrack::SetAttackType);
			properties[3] = property;
			property = new fight::PropertyEnumConstList<CauseDamageTrack>("originator", gCauseDamageTrackOriginatorTable, gCauseDamageTrackOriginatorCount, &CauseDamageTrack::SetOriginator);
			properties[4] = property;
			property = new fight::PropertyNameList<CauseDamageTrack>("grabSlot", &CauseDamageTrack::SetGrabSlot);
			properties[5] = property;
			property = new fight::PropertyBool<CauseDamageTrack>("ignoreShield", &CauseDamageTrack::SetIgnoreShield);
			properties[6] = property;
			property = new fight::PropertyBool<CauseDamageTrack>("sendAlert", &CauseDamageTrack::SetSendAlert);
			properties[7] = property;
			fight::RegisterPropertyList(properties, &gCauseDamageTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x105042F0
	fight::TrackFactory* CreateCauseDamageTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<CauseDamageTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x10504350
	void RegisterCauseDamageTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<CauseDamageTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyFloatConstRange<DebugDamageTrack>;
	template class fight::PropertyEnumConstList<DebugDamageTrack>;
	template class fight::PropertyName<DebugDamageTrack>;
	template class fight::TrackFactoryTemplate<DebugDamageTrack>;
	template class fight::TrackFactoryCasterTemplate<DebugDamageTrack>;
	template class fight::PropertyFloatConstRange<CauseDamageTrack>;
	template class fight::PropertyBool<CauseDamageTrack>;
	template class fight::PropertyEnumConstList<CauseDamageTrack>;
	template class fight::PropertyNameList<CauseDamageTrack>;
	template class fight::TrackFactoryTemplate<CauseDamageTrack>;
	template class fight::TrackFactoryCasterTemplate<CauseDamageTrack>;
}

namespace proto
{
	// FUNCTION: ENGINE 0x104FB220
	DebugDamageAction::DebugDamageAction(DebugDamageTrack* newTrack) : fight::Action(0xE00), link(newTrack)
	{
	}

	// FUNCTION: ENGINE 0x104FAE50
	DebugDamageAction::~DebugDamageAction()
	{
	}

	// FUNCTION: ENGINE 0x104FAF40
	CauseDamageAction::CauseDamageAction(CauseDamageTrack* newTrack, const engine::HandleBase& newOriginator, const engine::HandleBase& newTarget) : fight::Action(0xE00), originator(newOriginator), target(newTarget), link(newTrack)
	{
	}

	// FUNCTION: ENGINE 0x104FAE00
	CauseDamageAction::~CauseDamageAction()
	{
	}

	// FUNCTION: ENGINE 0x104FB4B0
	fight::Action* DebugDamageTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		if (owner != 0)
		{
			return new DebugDamageAction(this);
		}
		return 0;
	}
}

namespace proto
{
	namespace fightitems
	{
		// FUNCTION: ENGINE 0x104FAC90
		bool RegisterAt104FAC90Factories(fight::TrackRegistry* registry)
		{
			RegisterCauseDamageTrackFactory(registry, "causeDamage");
			RegisterDebugDamageTrackFactory(registry, "debugDamage");
			return true;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10503F40
// FUNCTION: ENGINE 0x10503F50
// FUNCTION: ENGINE 0x10503F80
// FUNCTION: ENGINE 0x10503F90
// FUNCTION: ENGINE 0x10503FC0
// FUNCTION: ENGINE 0x10503FF0
// FUNCTION: ENGINE 0x10504020
// FUNCTION: ENGINE 0x10504050
// FUNCTION: ENGINE 0x10504080
// FUNCTION: ENGINE 0x10504090
// FUNCTION: ENGINE 0x105040D0
// FUNCTION: ENGINE 0x105040E0
// FUNCTION: ENGINE 0x10504110
// FUNCTION: ENGINE 0x10504130
// FUNCTION: ENGINE 0x10504140
// FUNCTION: ENGINE 0x10504170
// FUNCTION: ENGINE 0x105041A0
// FUNCTION: ENGINE 0x105041B0
// FUNCTION: ENGINE 0x105041E0
// FUNCTION: ENGINE 0x10504200
// FUNCTION: ENGINE 0x10504210
// FUNCTION: ENGINE 0x10504250
// FUNCTION: ENGINE 0x10504260
// FUNCTION: ENGINE 0x10504290
// FUNCTION: ENGINE 0x105042B0
// FUNCTION: ENGINE 0x10504380
// FUNCTION: ENGINE 0x105043B0
// FUNCTION: ENGINE 0x105043D0
// FUNCTION: ENGINE 0x10504400
// FUNCTION: ENGINE 0x10504420
// FUNCTION: ENGINE 0x10504880
// FUNCTION: ENGINE 0x105048B0
// FUNCTION: ENGINE 0x105048D0
// FUNCTION: ENGINE 0x10504900
// FUNCTION: ENGINE 0x10504920
// FUNCTION: ENGINE 0x10504970
// FUNCTION: ENGINE 0x104FAD30
// FUNCTION: ENGINE 0x104FADE0
// FUNCTION: ENGINE 0x104FAE80
// FUNCTION: ENGINE 0x104FB8E0
// FUNCTION: ENGINE 0x104FAFC0
// FUNCTION: ENGINE 0x104FB290
