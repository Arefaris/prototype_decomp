// The fight tracks that switch physics and collision on objects (unit 0x1080F070 - 0x10810E00).
#ifndef ENGINE_FIGHT_PHYSICSTRACKS_H
#define ENGINE_FIGHT_PHYSICSTRACKS_H

#include "code/engine/fight/trackfactory.h"

namespace engine
{
	// RTTI: engine::PhysicsSetKeyframedTrack (16 vftable slots, 0x18 bytes)
	class PhysicsSetKeyframedTrack : public fight::Track
	{
	public:
		// 0x1080F3B0
		PhysicsSetKeyframedTrack();
		virtual ~PhysicsSetKeyframedTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108AC6A0)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetKeyframed(bool value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float timeBegin;  // +0x10
		bool keyframed;  // +0x14
	};

	extern fight::Property** gPhysicsSetKeyframedTrackProperties;
	// 0x1080FF60
	// 0x108103B0
	fight::TrackFactory* CreatePhysicsSetKeyframedTrackFactory(const char* name);
	void RegisterPhysicsSetKeyframedTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::PhysicsEnableTrack (16 vftable slots, 0x20 bytes)
	class PhysicsEnableTrack : public fight::Track
	{
	public:
		// 0x1080F430
		PhysicsEnableTrack();
		virtual ~PhysicsEnableTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108AC540)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetActionOnBegin(int value);
		bool SetActionOnEnd(int value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float timeBegin;  // +0x10
		float timeEnd;  // +0x14
		int actionOnBegin;  // +0x18
		int actionOnEnd;  // +0x1C
	};

	extern fight::Property** gPhysicsEnableTrackProperties;
	// 0x1080FF80
	// 0x108103E0
	fight::TrackFactory* CreatePhysicsEnableTrackFactory(const char* name);
	void RegisterPhysicsEnableTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::PhysicsDisallowSleepingTrack (16 vftable slots, 0x1C bytes)
	class PhysicsDisallowSleepingTrack : public fight::Track
	{
	public:
		// 0x1080F4F0
		PhysicsDisallowSleepingTrack();
		virtual ~PhysicsDisallowSleepingTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108AC6E0)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetKeepPhysicsObjectAwake(bool value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float timeBegin;  // +0x10
		float timeEnd;  // +0x14
		bool keepPhysicsObjectAwake;  // +0x18
	};

	extern fight::Property** gPhysicsDisallowSleepingTrackProperties;
	// 0x1080FFE0
	// 0x10810470
	fight::TrackFactory* CreatePhysicsDisallowSleepingTrackFactory(const char* name);
	void RegisterPhysicsDisallowSleepingTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::PhysicsKeyframedEnableTrack (16 vftable slots, 0x18 bytes)
	class PhysicsKeyframedEnableTrack : public fight::Track
	{
	public:
		// 0x1080F5A0
		PhysicsKeyframedEnableTrack();
		virtual ~PhysicsKeyframedEnableTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108AB1F0)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float timeBegin;  // +0x10
		float timeEnd;  // +0x14
	};

	extern fight::Property** gPhysicsKeyframedEnableTrackProperties;
	// 0x10810020
	// 0x108104D0
	fight::TrackFactory* CreatePhysicsKeyframedEnableTrackFactory(const char* name);
	void RegisterPhysicsKeyframedEnableTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::CollisionEnableOnJointTrack (16 vftable slots, 0x28 bytes)
	class CollisionEnableOnJointTrack : public fight::Track
	{
	public:
		// 0x1080F6A0
		CollisionEnableOnJointTrack();
		virtual ~CollisionEnableOnJointTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108AC5C0)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetSimulatedJoint(const fight::Name& value);
		bool SetActionOnBegin(int value);
		bool SetActionOnEnd(int value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name simulatedJoint;  // +0x10
		float timeBegin;  // +0x18
		float timeEnd;  // +0x1C
		int actionOnBegin;  // +0x20
		int actionOnEnd;  // +0x24
	};

	extern fight::Property** gCollisionEnableOnJointTrackProperties;
	// 0x1080FFA0
	// 0x10810410
	fight::TrackFactory* CreateCollisionEnableOnJointTrackFactory(const char* name);
	void RegisterCollisionEnableOnJointTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::CollisionEnableFromRootJointTrack (16 vftable slots, 0x28 bytes)
	class CollisionEnableFromRootJointTrack : public fight::Track
	{
	public:
		// 0x1080F710
		CollisionEnableFromRootJointTrack();
		virtual ~CollisionEnableFromRootJointTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108AC720)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetRootJoint(const fight::Name& value);
		bool SetActionOnBegin(int value);
		bool SetActionOnEnd(int value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name rootJoint;  // +0x10
		float timeBegin;  // +0x18
		float timeEnd;  // +0x1C
		int actionOnBegin;  // +0x20
		int actionOnEnd;  // +0x24
	};

	extern fight::Property** gCollisionEnableFromRootJointTrackProperties;
	// 0x1080FFC0
	// 0x10810440
	fight::TrackFactory* CreateCollisionEnableFromRootJointTrackFactory(const char* name);
	void RegisterCollisionEnableFromRootJointTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::CollisionEnableByNameTrack (16 vftable slots, 0x28 bytes)
	class CollisionEnableByNameTrack : public fight::Track
	{
	public:
		// 0x1080F7A0
		CollisionEnableByNameTrack();
		virtual ~CollisionEnableByNameTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108AC580)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetCollisionObject(const fight::Name& value);
		bool SetActionOnBegin(int value);
		bool SetActionOnEnd(int value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name collisionObject;  // +0x10
		float timeBegin;  // +0x18
		float timeEnd;  // +0x1C
		int actionOnBegin;  // +0x20
		int actionOnEnd;  // +0x24
	};

	extern fight::Property** gCollisionEnableByNameTrackProperties;
	// 0x10810000
	// 0x108104A0
	fight::TrackFactory* CreateCollisionEnableByNameTrackFactory(const char* name);
	void RegisterCollisionEnableByNameTrackFactory(fight::TrackRegistry* registry, const char* name);

}

#endif
