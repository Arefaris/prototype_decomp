// The fight condition on a game object's physics and the tracks that blend the physics of a pose or of a joint (unit
// 0x108F4F40 - 0x108F5A00; no assert path, file name guessed).
#ifndef ENGINE_FIGHT_PHYSICSBLEND_H
#define ENGINE_FIGHT_PHYSICSBLEND_H

#include "code/engine/fight/trackfactory.h"

namespace engine
{
	// RTTI: engine::HasPhysicsCondition (10 vftable slots, 0x18 bytes)
	class HasPhysicsCondition : public fight::Condition
	{
	public:
		// 0x108F4F90
		HasPhysicsCondition();
		virtual ~HasPhysicsCondition();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9 (0x1092D040)
		virtual bool Evaluate(int a, int b, int c, int d);

		// The members the properties write
		bool SetValidPhysicsObject(bool value);
		bool SetInContext(int value);
		bool SetEnabledCollisionObjects(int value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		int enabledCollisionObjects;  // +0xC
		int inContext;  // +0x10
		bool validPhysicsObject;  // +0x14
	};

	extern fight::Property** gHasPhysicsConditionProperties;
	// 0x108F5110
	// 0x108F5230
	fight::ConditionFactory* CreateHasPhysicsConditionFactory(const char* name);
	void RegisterHasPhysicsConditionFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::PhysicsPoseBlendFactorTrack (16 vftable slots, 0x1C bytes)
	class PhysicsPoseBlendFactorTrack : public fight::Track
	{
	public:
		// 0x108F5370
		PhysicsPoseBlendFactorTrack();
		virtual ~PhysicsPoseBlendFactorTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetTargetBlendFactor(float value);

		// 0x1092D120
		float GetTargetBlendFactor() const;

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float targetBlendFactor;  // +0x10
		float timeBegin;  // +0x14
		float timeEnd;  // +0x18
	};

	extern fight::Property** gPhysicsPoseBlendFactorTrackProperties;
	// 0x108F55E0
	// 0x108F5700
	fight::TrackFactory* CreatePhysicsPoseBlendFactorTrackFactory(const char* name);
	void RegisterPhysicsPoseBlendFactorTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::PhysicsJointBlendFactorTrack (16 vftable slots, 0x28 bytes)
	class PhysicsJointBlendFactorTrack : public fight::Track
	{
	public:
		// 0x108F5430
		PhysicsJointBlendFactorTrack();
		virtual ~PhysicsJointBlendFactorTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetTargetBlendFactor(float value);
		bool SetJointName(const fight::Name& value);

		// 0x1092D130 / 0x1092D140
		float GetTargetBlendFactor() const;
		const fight::Name* GetJointName() const;

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name jointName;  // +0x10
		float targetBlendFactor;  // +0x18
		float timeBegin;  // +0x1C
		float timeEnd;  // +0x20
	};

	extern fight::Property** gPhysicsJointBlendFactorTrackProperties;
	// 0x108F5600
	// 0x108F5730
	fight::TrackFactory* CreatePhysicsJointBlendFactorTrackFactory(const char* name);
	void RegisterPhysicsJointBlendFactorTrackFactory(fight::TrackRegistry* registry, const char* name);
}

#endif
