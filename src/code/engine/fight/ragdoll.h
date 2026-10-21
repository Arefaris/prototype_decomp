// The fight conditions and tracks of the ragdoll (unit 0x108F7400 - 0x108F93D0; no assert path, file name guessed).
#ifndef ENGINE_FIGHT_RAGDOLL_H
#define ENGINE_FIGHT_RAGDOLL_H

#include "code/engine/fight/trackfactory.h"

namespace engine
{
	// RTTI: engine::RagdollEnabledCondition (10 vftable slots, 0x10 bytes)
	class RagdollEnabledCondition : public fight::Condition
	{
	public:
		// 0x108F7600
		RagdollEnabledCondition();
		virtual ~RagdollEnabledCondition();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9 (0x1092E6F0)
		virtual bool Evaluate(int a, int b, int c, int d);

		// The members the properties write
		bool SetEnabled(bool value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		bool enabled;  // +0xC
	};

	extern fight::Property** gRagdollEnabledConditionProperties;
	// 0x108F84F0
	// 0x108F8B20
	fight::ConditionFactory* CreateRagdollEnabledConditionFactory(const char* name);
	void RegisterRagdollEnabledConditionFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::RagdollPossibleCondition (10 vftable slots, 0x10 bytes)
	class RagdollPossibleCondition : public fight::Condition
	{
	public:
		// 0x108F7650
		RagdollPossibleCondition();
		virtual ~RagdollPossibleCondition();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9 (0x1092E780)
		virtual bool Evaluate(int a, int b, int c, int d);

		// The members the properties write
		bool SetRagdollAlreadyCreated(bool value);
		bool SetPossible(bool value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		bool possible;  // +0xC
		bool ragdollAlreadyCreated;  // +0xD
	};

	extern fight::Property** gRagdollPossibleConditionProperties;
	// 0x108F8510
	// 0x108F8B50
	fight::ConditionFactory* CreateRagdollPossibleConditionFactory(const char* name);
	void RegisterRagdollPossibleConditionFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::RagdollSetKeyframeUpdatedTrack (16 vftable slots, 0x1C bytes)
	class RagdollSetKeyframeUpdatedTrack : public fight::Track
	{
	public:
		// 0x108F76A0
		RagdollSetKeyframeUpdatedTrack();
		virtual ~RagdollSetKeyframeUpdatedTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x1092FD80)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetKeyframeUpdated(bool value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float timeBegin;  // +0x10
		float timeEnd;  // +0x14
		bool keyframeUpdated;  // +0x18
	};

	extern fight::Property** gRagdollSetKeyframeUpdatedTrackProperties;
	// 0x108F8530
	// 0x108F8B80
	fight::TrackFactory* CreateRagdollSetKeyframeUpdatedTrackFactory(const char* name);
	void RegisterRagdollSetKeyframeUpdatedTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::DeactivateRagdollTrack (16 vftable slots, 0x18 bytes)
	class DeactivateRagdollTrack : public fight::Track
	{
	public:
		// 0x108F7730
		DeactivateRagdollTrack();
		virtual ~DeactivateRagdollTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x1092FD40)
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

	extern fight::Property** gDeactivateRagdollTrackProperties;
	// 0x108F8550
	// 0x108F8BB0
	fight::TrackFactory* CreateDeactivateRagdollTrackFactory(const char* name);
	void RegisterDeactivateRagdollTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::RagdollStoreJointVelocitiesTrack (16 vftable slots, 0x18 bytes)
	class RagdollStoreJointVelocitiesTrack : public fight::Track
	{
	public:
		// 0x108F77D0
		RagdollStoreJointVelocitiesTrack();
		virtual ~RagdollStoreJointVelocitiesTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x1092E2A0)
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

	extern fight::Property** gRagdollStoreJointVelocitiesTrackProperties;
	// 0x108F8590
	// 0x108F8C10
	fight::TrackFactory* CreateRagdollStoreJointVelocitiesTrackFactory(const char* name);
	void RegisterRagdollStoreJointVelocitiesTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::UnpowerRagdollTrack (16 vftable slots, 0x14 bytes)
	class UnpowerRagdollTrack : public fight::Track
	{
	public:
		// 0x108F7870
		UnpowerRagdollTrack();
		virtual ~UnpowerRagdollTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x1092E3C0)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float timeBegin;  // +0x10
	};

	extern fight::Property** gUnpowerRagdollTrackProperties;
	// 0x108F85D0
	// 0x108F8C70
	fight::TrackFactory* CreateUnpowerRagdollTrackFactory(const char* name);
	void RegisterUnpowerRagdollTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::DisableRagdollTrack (16 vftable slots, 0x1C bytes)
	class DisableRagdollTrack : public fight::Track
	{
	public:
		// 0x108F7910
		DisableRagdollTrack();
		virtual ~DisableRagdollTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x1092FC40)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetPhysicsBlendTime(float value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float physicsBlendTime;  // +0x10
		float timeBegin;  // +0x14
		float timeEnd;  // +0x18
	};

	extern fight::Property** gDisableRagdollTrackProperties;
	// 0x108F8610
	// 0x108F8CD0
	fight::TrackFactory* CreateDisableRagdollTrackFactory(const char* name);
	void RegisterDisableRagdollTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::PowerRagdollByPuppetTrack (16 vftable slots, 0x20 bytes)
	class PowerRagdollByPuppetTrack : public fight::Track
	{
	public:
		// 0x108F7AE0
		PowerRagdollByPuppetTrack();
		virtual ~PowerRagdollByPuppetTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x1092FD00)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetConstraintPropertiesName(const fight::Name& value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name constraintPropertiesName;  // +0x10
		float timeBegin;  // +0x18
		int unknown1C;
	};

	extern fight::Property** gPowerRagdollByPuppetTrackProperties;
	// 0x108F8570
	// 0x108F8BE0
	fight::TrackFactory* CreatePowerRagdollByPuppetTrackFactory(const char* name);
	void RegisterPowerRagdollByPuppetTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::PowerRagdollByPoseTrack (16 vftable slots, 0x28 bytes)
	class PowerRagdollByPoseTrack : public fight::Track
	{
	public:
		// 0x108F7B60
		PowerRagdollByPoseTrack();
		virtual ~PowerRagdollByPoseTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x1092FC80)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetPoseAnimName(const fight::Name& value);
		bool SetAnimFrame(float value);
		bool SetConstraintPropertiesName(const fight::Name& value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name constraintPropertiesName;  // +0x10
		fight::Name poseAnimName;  // +0x18
		float animFrame;  // +0x20
		float timeBegin;  // +0x24
	};

	extern fight::Property** gPowerRagdollByPoseTrackProperties;
	// 0x108F85B0
	// 0x108F8C40
	fight::TrackFactory* CreatePowerRagdollByPoseTrackFactory(const char* name);
	void RegisterPowerRagdollByPoseTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::PowerRagdollByAnimationTrack (16 vftable slots, 0x40 bytes)
	class PowerRagdollByAnimationTrack : public fight::Track
	{
	public:
		// 0x108F7C80
		PowerRagdollByAnimationTrack();
		virtual ~PowerRagdollByAnimationTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x1092FCC0)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetAnimation(const fight::Name& value);
		bool SetSpeed(float value);
		bool SetInitFrame(float value);
		bool SetStartFrame(float value);
		bool SetEndFrame(float value);
		bool SetCyclic(int value);
		bool SetConstraintPropertiesName(const fight::Name& value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name animation;  // +0x10
		fight::Name constraintPropertiesName;  // +0x18
		float endFrame;  // +0x20
		float initFrame;  // +0x24
		float speed;  // +0x28
		float startFrame;  // +0x2C
		float timeBegin;  // +0x30
		float timeEnd;  // +0x34
		int cyclic;  // +0x38
		int unknown3C;
	};

	extern fight::Property** gPowerRagdollByAnimationTrackProperties;
	// 0x108F8630
	// 0x108F8D00
	fight::TrackFactory* CreatePowerRagdollByAnimationTrackFactory(const char* name);
	void RegisterPowerRagdollByAnimationTrackFactory(fight::TrackRegistry* registry, const char* name);

}

#endif
