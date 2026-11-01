// Fight items of the physics group: SetIntersectionPropertiesTrack with its action (unit 0x1030E910 - 0x1030F7C0; no
// assert path, the file name is a guess).
#include "code/proto/fightitems/physics/physics_setintersectionproperties.h"

namespace proto
{
	fight::Property** gSetIntersectionPropertiesTrackProperties;  // 0x112610F4

	// FUNCTION: ENGINE 0x1030F2F0
	bool SetIntersectionPropertiesTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1030F310
	bool SetIntersectionPropertiesTrack::SetCollider(int newValue)
	{
		collider = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1030F320
	bool SetIntersectionPropertiesTrack::SetCollideWith(int newValue)
	{
		collideWith = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1030F330
	fight::Property* SetIntersectionPropertiesTrack::GetProperty(int index)
	{
		return gSetIntersectionPropertiesTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x1030F350
	void SetIntersectionPropertiesTrack::ClearProperties()
	{
		fight::FreePropertyList(&gSetIntersectionPropertiesTrackProperties);
	}

	// FUNCTION: ENGINE 0x1030F360
	SetIntersectionPropertiesTrack::SetIntersectionPropertiesTrack() : timeBegin(0.0f), collideWith(0), collider(0)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x1030F3A0
	float SetIntersectionPropertiesTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x1030F3B0
	float SetIntersectionPropertiesTrack::Slot10() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x1030F3C0
	SetIntersectionPropertiesTrack::~SetIntersectionPropertiesTrack()
	{
	}

	// FUNCTION: ENGINE 0x1030F5C0
	// EQUIVALENT: shrink-wrap; the engine saves esi and edi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
	void SetIntersectionPropertiesTrack::RegisterProperties()
	{
		if (gSetIntersectionPropertiesTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<SetIntersectionPropertiesTrack>("timeBegin", &SetIntersectionPropertiesTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyBitfieldConstList<SetIntersectionPropertiesTrack>("collider", fightitems::motion::gDetectObbCollisionConditionCollideWithTable, fightitems::motion::gDetectObbCollisionConditionCollideWithCount, &SetIntersectionPropertiesTrack::SetCollider);
			properties[1] = property;
			property = new fight::PropertyBitfieldConstList<SetIntersectionPropertiesTrack>("collideWith", fightitems::motion::gDetectObbCollisionConditionCollideWithTable, fightitems::motion::gDetectObbCollisionConditionCollideWithCount, &SetIntersectionPropertiesTrack::SetCollideWith);
			properties[2] = property;
			fight::RegisterPropertyList(properties, &gSetIntersectionPropertiesTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x1030F590
	fight::TrackFactory* CreateSetIntersectionPropertiesTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<SetIntersectionPropertiesTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	namespace fightitems
	{
		// FUNCTION: ENGINE 0x1030F700
		void RegisterPhysicsSetIntersectionPropertiesFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::TrackFactoryCasterTemplate<SetIntersectionPropertiesTrack> caster;
			registry->AddFactory(fight::FindTrackFactory(name, &caster));
		}
	}

	// FUNCTION: ENGINE 0x1030EA80
	SetIntersectionPropertiesAction::SetIntersectionPropertiesAction(SetIntersectionPropertiesTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0x200), link(newTrack), target(newTarget)
	{
	}

	// FUNCTION: ENGINE 0x1030E9E0
	SetIntersectionPropertiesAction::~SetIntersectionPropertiesAction()
	{
	}

	// FUNCTION: ENGINE 0x1030EC40
	fight::Action* SetIntersectionPropertiesTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
		return new SetIntersectionPropertiesAction(this, handle);
	}

	// FUNCTION: ENGINE 0x1030EB30
	// EQUIVALENT: shrink-wrap; the engine saves ebx and esi in the entry block before the handle's test, ours after it, so ours also repeats the epilogue for the early exit; every other instruction is the engine's
	bool SetIntersectionPropertiesAction::Slot5(int arg, float value)
	{
		engine::GameObject* object = target.Get();
		if (object != 0 && link.Get() != 0)
		{
			engine::SetIntersectionPropertiesMessage first(link.Get()->GetCollider(), true, 0, false);
			object->SendMessage(&first);
			engine::SetIntersectionPropertiesMessage second(link.Get()->GetCollideWith(), true, 1, false);
			object->SendMessage(&second);
		}
		return false;
	}

	template class fight::PropertyFloatConstRange<SetIntersectionPropertiesTrack>;
	template class fight::PropertyBitfieldConstList<SetIntersectionPropertiesTrack>;
	template class fight::TrackFactoryTemplate<SetIntersectionPropertiesTrack>;
	template class fight::TrackFactoryCasterTemplate<SetIntersectionPropertiesTrack>;
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1030E930
// FUNCTION: ENGINE 0x1030E940
// FUNCTION: ENGINE 0x1030E970
// FUNCTION: ENGINE 0x1030EB00
// FUNCTION: ENGINE 0x1030ECE0
// FUNCTION: ENGINE 0x1030F3D0
// FUNCTION: ENGINE 0x1030F400
// FUNCTION: ENGINE 0x1030F410
// FUNCTION: ENGINE 0x1030F440
// FUNCTION: ENGINE 0x1030F470
// FUNCTION: ENGINE 0x1030F4A0
// FUNCTION: ENGINE 0x1030F4B0
// FUNCTION: ENGINE 0x1030F4F0
// FUNCTION: ENGINE 0x1030F500
// FUNCTION: ENGINE 0x1030F520
// FUNCTION: ENGINE 0x1030F530
// FUNCTION: ENGINE 0x1030F730
// FUNCTION: ENGINE 0x1030F760
// FUNCTION: ENGINE 0x1030F780

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1030E910
// FUNCTION: ENGINE 0x1030E920
