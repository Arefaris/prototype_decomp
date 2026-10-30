#include "code/proto/smarthint/smarthintsettimer.h"

namespace proto
{
	extern fight::EnumEntry gSmartHintTimerTable[];
	extern const int gSmartHintTimerCount;

	fight::Property** gSmartHintSetTimerTrackProperties;  // 0x11275B90

	// FUNCTION: ENGINE 0x1059EB90
	bool SmartHintSetTimerTrack::SetTimer(int newTimer)
	{
		timer = newTimer;
		return true;
	}

	// FUNCTION: ENGINE 0x1059EBA0
	bool SmartHintSetTimerTrack::SetValue(float newValue)
	{
		value = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1059EBC0
	fight::Property* SmartHintSetTimerTrack::GetProperty(int index)
	{
		return gSmartHintSetTimerTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x1059EBE0
	void SmartHintSetTimerTrack::ClearProperties()
	{
		fight::FreePropertyList(&gSmartHintSetTimerTrackProperties);
	}

	// FUNCTION: ENGINE 0x1059EBF0
	SmartHintSetTimerTrack::SmartHintSetTimerTrack() : value(0.0f), timer(0)
	{
	}

	// FUNCTION: ENGINE 0x1059EC20
	float SmartHintSetTimerTrack::GetTimeBegin() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x1059EC30
	float SmartHintSetTimerTrack::Slot10() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x1059EC40
	SmartHintSetTimerTrack::~SmartHintSetTimerTrack()
	{
	}

	// FUNCTION: ENGINE 0x1059EB40
	fight::Action* SmartHintSetTimerTrack::CreateAction(fight::Track* listener, core::IRefCount* effect,
		core::IRefCount* owner)
	{
		engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
		return new SmartHintSetTimerAction(this, handle);
	}

	// FUNCTION: ENGINE 0x1059EE10
	// EQUIVALENT: shrink-wrap (the engine saves esi and edi in the entry block, before the guard's branch; ours sinks the
	// pushes behind it)
	void SmartHintSetTimerTrack::RegisterProperties()
	{
		if (gSmartHintSetTimerTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyEnumConstList<SmartHintSetTimerTrack>("timer", gSmartHintTimerTable,
				gSmartHintTimerCount, &SmartHintSetTimerTrack::SetTimer);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<SmartHintSetTimerTrack>("value",
				&SmartHintSetTimerTrack::SetValue);
			properties[1] = property;
			fight::RegisterPropertyList(properties, &gSmartHintSetTimerTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x1059EDE0
	fight::TrackFactory* CreateSmartHintSetTimerTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<SmartHintSetTimerTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x1059EF00
	void RegisterSmartHintSetTimerTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<SmartHintSetTimerTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyEnumConstList<SmartHintSetTimerTrack>;
	template class fight::PropertyFloatConstRange<SmartHintSetTimerTrack>;
	template class fight::TrackFactoryTemplate<SmartHintSetTimerTrack>;
	template class fight::TrackFactoryCasterTemplate<SmartHintSetTimerTrack>;

	// FUNCTION: ENGINE 0x1059EA40
	SmartHintSetTimerAction::SmartHintSetTimerAction(SmartHintSetTimerTrack* newTrack,
		engine::GameObjectHandle newTarget) : fight::Action(0x200), target(newTarget), link(newTrack)
	{
	}

	// FUNCTION: ENGINE 0x1059E9A0
	SmartHintSetTimerAction::~SmartHintSetTimerAction()
	{
	}

	// FUNCTION: ENGINE 0x1059EAE0
	bool SmartHintSetTimerAction::Slot5(int arg, float time)
	{
		if (link.object != 0 && target.IsValid())
		{
			gSmartHintManager->SetTimer(link.object->timer, link.object->value);
		}
		return false;
	}
}
