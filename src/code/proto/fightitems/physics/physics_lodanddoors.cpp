// Fight items of the physics group: SetPhysicsLODTrack and SetVehicleDoorsLatchedTrack with their actions (unit
// 0x1030F7D0 - 0x10310000; no assert path, the file name is a guess).
#include "code/proto/fightitems/physics/physics_lodanddoors.h"

namespace proto
{
	fight::Property** gSetPhysicsLODTrackProperties;  // 0x11261108
	fight::Property** gSetVehicleDoorsLatchedTrackProperties;  // 0x1126110C

	// FUNCTION: ENGINE 0x1030F7D0
	bool SetPhysicsLODTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1030F7F0
	bool SetVehicleDoorsLatchedTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1030F810
	bool SetVehicleDoorsLatchedTrack::SetLatched(bool newValue)
	{
		latched = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1030F820
	fight::Property* SetPhysicsLODTrack::GetProperty(int index)
	{
		return gSetPhysicsLODTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x1030F840
	void SetPhysicsLODTrack::ClearProperties()
	{
		fight::FreePropertyList(&gSetPhysicsLODTrackProperties);
	}

	// FUNCTION: ENGINE 0x1030F850
	fight::Property* SetVehicleDoorsLatchedTrack::GetProperty(int index)
	{
		return gSetVehicleDoorsLatchedTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x1030F870
	void SetVehicleDoorsLatchedTrack::ClearProperties()
	{
		fight::FreePropertyList(&gSetVehicleDoorsLatchedTrackProperties);
	}

	// FUNCTION: ENGINE 0x1030F880
	SetVehicleDoorsLatchedTrack::SetVehicleDoorsLatchedTrack() : timeBegin(0.0f), latched(false)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x1030F8B0
	float SetVehicleDoorsLatchedTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x1030F8C0
	float SetVehicleDoorsLatchedTrack::Slot10() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x1030F8D0
	SetVehicleDoorsLatchedTrack::~SetVehicleDoorsLatchedTrack()
	{
	}

	// FUNCTION: ENGINE 0x1030F8E0
	bool SetPhysicsLODTrack::SetPhysicsLOD(const fight::Name& newValue)
	{
		physicsLOD = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1030F900
	SetPhysicsLODTrack::SetPhysicsLODTrack() : timeBegin(0.0f)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x1030F940
	float SetPhysicsLODTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x1030F950
	float SetPhysicsLODTrack::Slot10() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x1030F960
	SetPhysicsLODTrack::~SetPhysicsLODTrack()
	{
	}

	// FUNCTION: ENGINE 0x1030FB90
	fight::TrackFactory* CreateSetPhysicsLODTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<SetPhysicsLODTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x1030FBC0
	fight::TrackFactory* CreateSetVehicleDoorsLatchedTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<SetVehicleDoorsLatchedTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x1030FBF0
	// EQUIVALENT: shrink-wrap; the engine saves esi and edi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
	void SetVehicleDoorsLatchedTrack::RegisterProperties()
	{
		if (gSetVehicleDoorsLatchedTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<SetVehicleDoorsLatchedTrack>("timeBegin", &SetVehicleDoorsLatchedTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyBool<SetVehicleDoorsLatchedTrack>("latched", &SetVehicleDoorsLatchedTrack::SetLatched);
			properties[1] = property;
			fight::RegisterPropertyList(properties, &gSetVehicleDoorsLatchedTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x1030FDE0
	// EQUIVALENT: shrink-wrap; the engine saves esi and edi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
	void SetPhysicsLODTrack::RegisterProperties()
	{
		if (gSetPhysicsLODTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<SetPhysicsLODTrack>("timeBegin", &SetPhysicsLODTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyNameList<SetPhysicsLODTrack>("physicsLOD", &SetPhysicsLODTrack::SetPhysicsLOD);
			properties[1] = property;
			fight::RegisterPropertyList(properties, &gSetPhysicsLODTrackProperties);
		}
	}

	namespace fightitems
	{
		// FUNCTION: ENGINE 0x1030FCD0
		void RegisterSetPhysicsLODTrackFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::TrackFactoryCasterTemplate<SetPhysicsLODTrack> caster;
			registry->AddFactory(fight::FindTrackFactory(name, &caster));
		}

		// FUNCTION: ENGINE 0x1030FD00
		void RegisterSetVehicleDoorsLatchedTrackFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::TrackFactoryCasterTemplate<SetVehicleDoorsLatchedTrack> caster;
			registry->AddFactory(fight::FindTrackFactory(name, &caster));
		}

		// FUNCTION: ENGINE 0x1030ECF0
		bool RegisterPhysicsLODAndDoorsFactories(fight::TrackRegistry* registry)
		{
			RegisterSetPhysicsLODTrackFactory(registry, "setPhysicsLOD");
			RegisterSetVehicleDoorsLatchedTrackFactory(registry, "setVehicleDoorsLatched");
			return true;
		}
	}

	// FUNCTION: ENGINE 0x1030EFF0
	SetPhysicsLODAction::SetPhysicsLODAction(SetPhysicsLODTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), target(newTarget), link(newTrack)
	{
	}

	// FUNCTION: ENGINE 0x1030EE90
	SetPhysicsLODAction::~SetPhysicsLODAction()
	{
	}

	// FUNCTION: ENGINE 0x1030F120
	SetVehicleDoorsLatchedAction::SetVehicleDoorsLatchedAction(SetVehicleDoorsLatchedTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), target(newTarget), link(newTrack)
	{
	}

	// FUNCTION: ENGINE 0x1030EEE0
	SetVehicleDoorsLatchedAction::~SetVehicleDoorsLatchedAction()
	{
	}

	// FUNCTION: ENGINE 0x1030F250
	fight::Action* SetPhysicsLODTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
		return new SetPhysicsLODAction(this, handle);
	}

	// FUNCTION: ENGINE 0x1030F2A0
	fight::Action* SetVehicleDoorsLatchedTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
		return new SetVehicleDoorsLatchedAction(this, handle);
	}

	// FUNCTION: ENGINE 0x1030F090
	bool SetPhysicsLODAction::Slot5(int arg, float value)
	{
		if (link.Get() == 0)
		{
			return false;
		}
		engine::GameObject* object = target.Get();
		if (object == 0)
		{
			return false;
		}
		SetPhysicsLODMessage message(link.Get()->GetPhysicsLOD());
		object->SendMessage(&message);
		return true;
	}

	// FUNCTION: ENGINE 0x1030F1C0
	bool SetVehicleDoorsLatchedAction::Slot5(int arg, float value)
	{
		if (link.Get() != 0)
		{
			engine::GameObject* object = target.Get();
			if (object != 0)
			{
				SetVehicleDoorsLatchedMessage message(link.Get()->GetLatched());
				object->SendMessage(&message);
			}
		}
		return false;
	}

	template class fight::PropertyFloatConstRange<SetPhysicsLODTrack>;
	template class fight::PropertyNameList<SetPhysicsLODTrack>;
	template class fight::PropertyFloatConstRange<SetVehicleDoorsLatchedTrack>;
	template class fight::PropertyBool<SetVehicleDoorsLatchedTrack>;
	template class fight::TrackFactoryTemplate<SetPhysicsLODTrack>;
	template class fight::TrackFactoryCasterTemplate<SetPhysicsLODTrack>;
	template class fight::TrackFactoryTemplate<SetVehicleDoorsLatchedTrack>;
	template class fight::TrackFactoryCasterTemplate<SetVehicleDoorsLatchedTrack>;
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1030E960
// FUNCTION: ENGINE 0x1030E9C0
// FUNCTION: ENGINE 0x1030EA10
// FUNCTION: ENGINE 0x1030EA60
// FUNCTION: ENGINE 0x1030EC90
// FUNCTION: ENGINE 0x1030ECA0
// FUNCTION: ENGINE 0x1030ECB0
// FUNCTION: ENGINE 0x1030ED40
// FUNCTION: ENGINE 0x1030ED70
// FUNCTION: ENGINE 0x1030EDC0
// FUNCTION: ENGINE 0x1030F060
// FUNCTION: ENGINE 0x1030F190
// FUNCTION: ENGINE 0x1030F970
// FUNCTION: ENGINE 0x1030F9A0
// FUNCTION: ENGINE 0x1030F9B0
// FUNCTION: ENGINE 0x1030F9E0
// FUNCTION: ENGINE 0x1030F9F0
// FUNCTION: ENGINE 0x1030FA20
// FUNCTION: ENGINE 0x1030FA50
// FUNCTION: ENGINE 0x1030FA80
// FUNCTION: ENGINE 0x1030FAB0
// FUNCTION: ENGINE 0x1030FAC0
// FUNCTION: ENGINE 0x1030FAF0
// FUNCTION: ENGINE 0x1030FB20
// FUNCTION: ENGINE 0x1030FB30
// FUNCTION: ENGINE 0x1030FB60
// FUNCTION: ENGINE 0x1030FB80
// FUNCTION: ENGINE 0x1030FD30
// FUNCTION: ENGINE 0x1030FD60
// FUNCTION: ENGINE 0x1030FD80
// FUNCTION: ENGINE 0x1030FD90
// FUNCTION: ENGINE 0x1030FDC0
// FUNCTION: ENGINE 0x1030FEC0
// FUNCTION: ENGINE 0x1030FF10
// FUNCTION: ENGINE 0x1030FF40
// FUNCTION: ENGINE 0x1030FF60
