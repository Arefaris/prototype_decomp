// Fight items of the physics group: SetPhysicsLODTrack and SetVehicleDoorsLatchedTrack with their actions (unit
// 0x1030F7D0 - 0x10310000; no assert path, the file name is a guess). The actions and the factory registration lie in
// front of the tracks' code, in the run of the previous unit.
#ifndef PROTO_FIGHTITEMS_PHYSICS_PHYSICS_LODANDDOORS_H
#define PROTO_FIGHTITEMS_PHYSICS_PHYSICS_LODANDDOORS_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/proto/messages/physicsmessages.h"

namespace engine
{
	// 0x107FC7A0: the handle of the object an effect or action runs on
	GameObjectHandle GetObjectHandle(core::IRefCount* object);
}

namespace proto
{
	// RTTI: proto::SetPhysicsLODTrack (16 vftable slots, 0x20 bytes): puts the object's physics on a named level of
	// detail
	class __declspec(align(8)) SetPhysicsLODTrack : public fight::Track
	{
	public:
		// 0x1030F900
		SetPhysicsLODTrack();
		virtual ~SetPhysicsLODTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x1030F250)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float newValue);
		bool SetPhysicsLOD(const fight::Name& newValue);

		// 0x1030EC90 (a copy of the unit)
		const fight::Name* GetPhysicsLOD() const
		{
			return &physicsLOD;
		}

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name physicsLOD;  // +0x10
		float timeBegin;  // +0x18
	};

	// RTTI: proto::SetVehicleDoorsLatchedTrack (16 vftable slots, 0x18 bytes): latches or unlatches the doors of a
	// vehicle
	class SetVehicleDoorsLatchedTrack : public fight::Track
	{
	public:
		// 0x1030F880
		SetVehicleDoorsLatchedTrack();
		virtual ~SetVehicleDoorsLatchedTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x1030F2A0)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float newValue);
		bool SetLatched(bool newValue);

		// 0x1030ECA0 (a copy of the unit)
		bool GetLatched() const
		{
			return latched;
		}

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float timeBegin;  // +0x10
		bool latched;  // +0x14
	};

	fight::TrackFactory* CreateSetPhysicsLODTrackFactory(const char* name);
	fight::TrackFactory* CreateSetVehicleDoorsLatchedTrackFactory(const char* name);
	namespace fightitems
	{
		void RegisterSetPhysicsLODTrackFactory(fight::TrackRegistry* registry, const char* name);
		void RegisterSetVehicleDoorsLatchedTrackFactory(fight::TrackRegistry* registry, const char* name);
		// 0x1030ECF0: registers both tracks under their script names
		bool RegisterPhysicsLODAndDoorsFactories(fight::TrackRegistry* registry);
	}

	// RTTI: proto::SetPhysicsLODAction (9 vftable slots, 0x2C bytes)
	class SetPhysicsLODAction : public fight::Action
	{
	public:
		// 0x1030EFF0
		SetPhysicsLODAction(SetPhysicsLODTrack* newTrack, engine::GameObjectHandle newTarget);
		// 0x1030EE90
		virtual ~SetPhysicsLODAction();

		// vftable slot 5 (0x1030F090): sends the level of detail to the object
		virtual bool Slot5(int arg, float value);

		engine::GameObjectHandle target;  // +0x1C
		core::Link<SetPhysicsLODTrack> link;  // +0x20
	};

	// RTTI: proto::SetVehicleDoorsLatchedAction (9 vftable slots, 0x2C bytes)
	class SetVehicleDoorsLatchedAction : public fight::Action
	{
	public:
		// 0x1030F120
		SetVehicleDoorsLatchedAction(SetVehicleDoorsLatchedTrack* newTrack, engine::GameObjectHandle newTarget);
		// 0x1030EEE0
		virtual ~SetVehicleDoorsLatchedAction();

		// vftable slot 5 (0x1030F1C0): sends the track's latch state to the object
		virtual bool Slot5(int arg, float value);

		engine::GameObjectHandle target;  // +0x1C
		core::Link<SetVehicleDoorsLatchedTrack> link;  // +0x20
	};
}

#endif
