// Fight items of the physics group: SetIntersectionPropertiesTrack with its action (unit 0x1030E910 - 0x1030F7C0; no
// assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_PHYSICS_PHYSICS_SETINTERSECTIONPROPERTIES_H
#define PROTO_FIGHTITEMS_PHYSICS_PHYSICS_SETINTERSECTIONPROPERTIES_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/physics/physicsmessages.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace engine
{
	// 0x107FC7A0: the handle of the object an effect or action runs on
	GameObjectHandle GetObjectHandle(core::IRefCount* object);
}

namespace proto
{
	// RTTI: proto::SetIntersectionPropertiesTrack (16 vftable slots, 0x1C bytes): which collision layers an object is
	// on and which it collides with
	class SetIntersectionPropertiesTrack : public fight::Track
	{
	public:
		// 0x1030F360
		SetIntersectionPropertiesTrack();
		virtual ~SetIntersectionPropertiesTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x1030EC40)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float newValue);
		bool SetCollideWith(int newValue);
		bool SetCollider(int newValue);

		// 0x1030E910 / 0x1030E920 (copies of the unit)
		int GetCollider() const
		{
			return collider;
		}
		int GetCollideWith() const
		{
			return collideWith;
		}

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float timeBegin;  // +0x10
		int collideWith;  // +0x14
		int collider;  // +0x18
	};

	extern fight::Property** gSetIntersectionPropertiesTrackProperties;
	fight::TrackFactory* CreateSetIntersectionPropertiesTrackFactory(const char* name);
	namespace fightitems
	{
		void RegisterPhysicsSetIntersectionPropertiesFactory(fight::TrackRegistry* registry, const char* name);
	}

	// RTTI: proto::SetIntersectionPropertiesAction (9 vftable slots, 0x2C bytes)
	class SetIntersectionPropertiesAction : public fight::Action
	{
	public:
		// 0x1030EA80
		SetIntersectionPropertiesAction(SetIntersectionPropertiesTrack* newTrack, engine::GameObjectHandle newTarget);
		// 0x1030E9E0
		virtual ~SetIntersectionPropertiesAction();

		// vftable slot 5 (0x1030EB30): puts the object on the track's collision layers
		virtual bool Slot5(int arg, float value);

		core::Link<SetIntersectionPropertiesTrack> link;  // +0x1C
		engine::GameObjectHandle target;  // +0x28
	};
}

#endif
