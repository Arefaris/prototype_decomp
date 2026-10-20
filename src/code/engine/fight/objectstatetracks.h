// The fight tracks that give an object a velocity, set its transform or rotation attribute, send it a message and play puppet animations (unit 0x108AD0B0 - 0x108AEE20; no assert path, file name guessed).
#ifndef ENGINE_FIGHT_OBJECTSTATETRACKS_H
#define ENGINE_FIGHT_OBJECTSTATETRACKS_H

#include "code/engine/fight/trackfactory.h"

namespace engine
{
	// RTTI: engine::VelocityLinearTrack (16 vftable slots, 0x24 bytes)
	class VelocityLinearTrack : public fight::Track
	{
	public:
		// 0x108AD170
		VelocityLinearTrack();
		virtual ~VelocityLinearTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108ED010)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetOperation(int value);
		bool SetLinearVelocity(const math::Vector& value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		math::Vector linearVelocity;  // +0x10
		float timeBegin;  // +0x1C
		int operation;  // +0x20
	};

	extern fight::Property** gVelocityLinearTrackProperties;
	// 0x108AD570
	// 0x108AD790
	fight::TrackFactory* CreateVelocityLinearTrackFactory(const char* name);
	void RegisterVelocityLinearTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::VelocityAngularTrack (16 vftable slots, 0x24 bytes)
	class VelocityAngularTrack : public fight::Track
	{
	public:
		// 0x108AD1F0
		VelocityAngularTrack();
		virtual ~VelocityAngularTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108ED050)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetOperation(int value);
		bool SetAngularVelocity(const math::Vector& value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		math::Vector angularVelocity;  // +0x10
		float timeBegin;  // +0x1C
		int operation;  // +0x20
	};

	extern fight::Property** gVelocityAngularTrackProperties;
	// 0x108AD590
	// 0x108AD7C0
	fight::TrackFactory* CreateVelocityAngularTrackFactory(const char* name);
	void RegisterVelocityAngularTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::SimpleMessageTrack (16 vftable slots, 0x18 bytes)
	class SimpleMessageTrack : public fight::Track
	{
	public:
		// 0x108AD950
		SimpleMessageTrack();
		virtual ~SimpleMessageTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108ED280)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetMessage(int value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float timeBegin;  // +0x10
		int message;  // +0x14
	};

	extern fight::Property** gSimpleMessageTrackProperties;
	// 0x108ADAF0
	// 0x108ADBD0
	fight::TrackFactory* CreateSimpleMessageTrackFactory(const char* name);
	void RegisterSimpleMessageTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::SetTransformAttributeTrack (16 vftable slots, 0x28 bytes)
	class SetTransformAttributeTrack : public fight::Track
	{
	public:
		// 0x108ADD50
		SetTransformAttributeTrack();
		virtual ~SetTransformAttributeTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108ED870)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTransform(const math::Vector& value);
		bool SetRotationEulerAnglesXYZ(const math::Vector& value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		math::Vector rotationEulerAnglesXYZ;  // +0x10
		math::Vector transform;  // +0x1C
	};

	extern fight::Property** gSetTransformAttributeTrackProperties;
	// 0x108ADFF0
	// 0x108AE190
	fight::TrackFactory* CreateSetTransformAttributeTrackFactory(const char* name);
	void RegisterSetTransformAttributeTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::SetRotationAttributeTrack (16 vftable slots, 0x20 bytes)
	class SetRotationAttributeTrack : public fight::Track
	{
	public:
		// 0x108ADDE0
		SetRotationAttributeTrack();
		virtual ~SetRotationAttributeTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108ED830)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetRotationAxis(const math::Vector& value);
		bool SetRotationDegrees(float value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		math::Vector rotationAxis;  // +0x10
		float rotationDegrees;  // +0x1C
	};

	extern fight::Property** gSetRotationAttributeTrackProperties;
	// 0x108AE010
	// 0x108AE1C0
	fight::TrackFactory* CreateSetRotationAttributeTrackFactory(const char* name);
	void RegisterSetRotationAttributeTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::PuppetAnimationTrack (16 vftable slots, 0x60 bytes)
	class PuppetAnimationTrack : public fight::Track
	{
	public:
		// 0x108AE500
		PuppetAnimationTrack();
		virtual ~PuppetAnimationTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108EE670)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetAnimation(const fight::Name& value);
		bool SetSpeed(float value);
		bool SetRandomSpeedVariation(float value);
		bool SetInitFrame(float value);
		bool SetStartFrame(float value);
		bool SetEndFrame(float value);
		bool SetCyclic(int value);
		bool SetSyncFrame(bool value);
		bool SetPhaseMatch(bool value);
		bool SetReuseExistingDriver(bool value);
		bool SetSyncPhase(int value);
		bool SetSyncPhaseMinFrame(float value);
		bool SetSyncPhaseMaxFrame(float value);
		bool SetHasRootTranslation(bool value);
		bool SetHasRootRotation(bool value);
		bool SetPartition(const fight::Name& value);
		bool SetWeight(float value);
		bool SetPriority(int value);
		bool SetBlendInTime(float value);
		bool SetBlendOutTime(float value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name animation;  // +0x10
		fight::Name partition;  // +0x18
		float blendInTime;  // +0x20
		float blendOutTime;  // +0x24
		float endFrame;  // +0x28
		float initFrame;  // +0x2C
		float randomSpeedVariation;  // +0x30
		float speed;  // +0x34
		float startFrame;  // +0x38
		float syncPhaseMaxFrame;  // +0x3C
		float syncPhaseMinFrame;  // +0x40
		float timeBegin;  // +0x44
		float timeEnd;  // +0x48
		float weight;  // +0x4C
		int cyclic;  // +0x50
		int priority;  // +0x54
		int syncPhase;  // +0x58
		bool hasRootRotation : 1;  // +0x5C bit 0
		bool hasRootTranslation : 1;  // +0x5C bit 1
		bool phaseMatch : 1;  // +0x5C bit 2
		bool reuseExistingDriver : 1;  // +0x5C bit 3
		bool syncFrame : 1;  // +0x5C bit 4
	};

	extern fight::Property** gPuppetAnimationTrackProperties;
	// 0x108AE7A0
	// 0x108AE7C0
	fight::TrackFactory* CreatePuppetAnimationTrackFactory(const char* name);
	void RegisterPuppetAnimationTrackFactory(fight::TrackRegistry* registry, const char* name);

}

#endif
