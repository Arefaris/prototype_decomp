// The fight tracks that control the root, adjust a strafe, steer a character and test the choreography (unit 0x108FB4B0 - 0x108FCA50; no assert path, file name guessed).
#ifndef ENGINE_FIGHT_ROOTCONTROL_H
#define ENGINE_FIGHT_ROOTCONTROL_H

#include "code/engine/fight/trackfactory.h"

namespace engine
{
	// RTTI: engine::ControlRootTrack (16 vftable slots, 0x34 bytes)
	class ControlRootTrack : public fight::Track
	{
	public:
		// 0x108FB790
		ControlRootTrack();
		virtual ~ControlRootTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x109336E0)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetMovementEnabled(bool value);
		bool SetMaxSpeed(float value);
		bool SetGravity(float value);
		bool SetSteeringEnabled(bool value);
		bool SetMaxTurnSpeed(float value);
		bool SetPriority(int value);
		bool SetBlendInTime(float value);
		bool SetBlendOutTime(float value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float blendInTime;  // +0x10
		float blendOutTime;  // +0x14
		float gravity;  // +0x18
		float maxSpeed;  // +0x1C
		float maxTurnSpeed;  // +0x20
		float timeBegin;  // +0x24
		float timeEnd;  // +0x28
		int priority;  // +0x2C
		bool movementEnabled;  // +0x30
		bool steeringEnabled;  // +0x31
	};

	extern fight::Property** gControlRootTrackProperties;
	// 0x108FC070
	// 0x108FC340
	fight::TrackFactory* CreateControlRootTrackFactory(const char* name);
	void RegisterControlRootTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::StrafeAdjustRootTrack (16 vftable slots, 0x40 bytes)
	class StrafeAdjustRootTrack : public fight::Track
	{
	public:
		// 0x108FB940
		StrafeAdjustRootTrack();
		virtual ~StrafeAdjustRootTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x10933720)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetAdjustJoint(const fight::Name& value);
		bool SetOriginalDirection(const math::Vector& value);
		bool SetAngleAdjustRate(float value);
		bool SetPriority(int value);
		bool SetBlendInTime(float value);
		bool SetBlendOutTime(float value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name adjustJoint;  // +0x10
		math::Vector originalDirection;  // +0x18
		float angleAdjustRate;  // +0x24
		float blendInTime;  // +0x28
		float blendOutTime;  // +0x2C
		float timeBegin;  // +0x30
		float timeEnd;  // +0x34
		int priority;  // +0x38
		int unknown3C;
	};

	extern fight::Property** gStrafeAdjustRootTrackProperties;
	// 0x108FC050
	// 0x108FC310
	fight::TrackFactory* CreateStrafeAdjustRootTrackFactory(const char* name);
	void RegisterStrafeAdjustRootTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::CharacterSteerTrack (16 vftable slots, 0x68 bytes)
	class CharacterSteerTrack : public fight::Track
	{
	public:
		// 0x108FB9F0
		CharacterSteerTrack();
		virtual ~CharacterSteerTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x109336A0)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetAcceleration(float value);
		bool SetTurningVelocity(float value);
		bool SetVelocityWalk(float value);
		bool SetVelocityRun(float value);
		bool SetGravity(float value);
		bool SetPhase(float value);
		bool SetLocomotion(const fight::Name& value);
		bool SetAnimIdle(const fight::Name& value);
		bool SetAnimWalk(const fight::Name& value);
		bool SetAnimRun(const fight::Name& value);
		bool SetPartition(const fight::Name& value);
		bool SetPriority(int value);
		bool SetBlendInTime(float value);
		bool SetBlendOutTime(float value);
		bool SetDisableRootMotion(bool value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name animIdle;  // +0x10
		fight::Name animRun;  // +0x18
		fight::Name animWalk;  // +0x20
		fight::Name locomotion;  // +0x28
		fight::Name partition;  // +0x30
		float acceleration;  // +0x38
		float blendInTime;  // +0x3C
		float blendOutTime;  // +0x40
		float gravity;  // +0x44
		float phase;  // +0x48
		float timeBegin;  // +0x4C
		float timeEnd;  // +0x50
		float turningVelocity;  // +0x54
		float velocityRun;  // +0x58
		float velocityWalk;  // +0x5C
		int priority;  // +0x60
		bool disableRootMotion;  // +0x64
	};

	extern fight::Property** gCharacterSteerTrackProperties;
	// 0x108FC090
	// 0x108FC370
	fight::TrackFactory* CreateCharacterSteerTrackFactory(const char* name);
	void RegisterCharacterSteerTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::ChoreoTestsTrack (16 vftable slots, 0x30 bytes)
	class ChoreoTestsTrack : public fight::Track
	{
	public:
		// 0x108FBAA0
		ChoreoTestsTrack();
		virtual ~ChoreoTestsTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x10933760)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetTestRandomSteer(bool value);
		bool SetTestPoseDriver(bool value);
		bool SetTestRestPoseDriver(bool value);
		bool SetTestDriverCopy(bool value);
		bool SetTestDriverCopySource(const fight::Name& value);
		bool SetPriority(int value);
		bool SetBlendInTime(float value);
		bool SetBlendOutTime(float value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name testDriverCopySource;  // +0x10
		float blendInTime;  // +0x18
		float blendOutTime;  // +0x1C
		float timeBegin;  // +0x20
		float timeEnd;  // +0x24
		int priority;  // +0x28
		bool testDriverCopy;  // +0x2C
		bool testPoseDriver;  // +0x2D
		bool testRandomSteer;  // +0x2E
		bool testRestPoseDriver;  // +0x2F
	};

	extern fight::Property** gChoreoTestsTrackProperties;
	// 0x108FC0B0
	// 0x108FC3A0
	fight::TrackFactory* CreateChoreoTestsTrackFactory(const char* name);
	void RegisterChoreoTestsTrackFactory(fight::TrackRegistry* registry, const char* name);

}

#endif
