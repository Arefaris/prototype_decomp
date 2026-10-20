// The fight tracks that switch motion tracked expressions, play expression animations, lock joints, move puppets and make an object undamageable (unit 0x108B72A0 - 0x108B8CE0; no assert path, file name guessed).
#ifndef ENGINE_FIGHT_EXPRESSIONTRACKS_H
#define ENGINE_FIGHT_EXPRESSIONTRACKS_H

#include "code/engine/fight/trackfactory.h"

namespace engine
{
	namespace animation
	{
		// RTTI: engine::animation::DisableMotionTrackedExpressionTrack (16 vftable slots, 0x18 bytes)
		class DisableMotionTrackedExpressionTrack : public fight::Track
		{
		public:
			// 0x108B72C0
			DisableMotionTrackedExpressionTrack();
			virtual ~DisableMotionTrackedExpressionTrack();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9
			virtual float GetTimeBegin() const;
			// vftable slot 10
			virtual float Slot10() const;
			// vftable slot 15 (0x108F4B60)
			virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

			// The members the properties write
			bool SetTimeBegin(float value);
			bool SetBlendDuration(float value);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

			float blendDuration;  // +0x10
			float timeBegin;  // +0x14
		};

		extern fight::Property** gDisableMotionTrackedExpressionTrackProperties;
		// 0x108B7500
		// 0x108B76A0
		fight::TrackFactory* CreateDisableMotionTrackedExpressionTrackFactory(const char* name);
		void RegisterDisableMotionTrackedExpressionTrackFactory(fight::TrackRegistry* registry, const char* name);
	}

	namespace animation
	{
		// RTTI: engine::animation::EnableMotionTrackedExpressionTrack (16 vftable slots, 0x18 bytes)
		class EnableMotionTrackedExpressionTrack : public fight::Track
		{
		public:
			// 0x108B7340
			EnableMotionTrackedExpressionTrack();
			virtual ~EnableMotionTrackedExpressionTrack();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9
			virtual float GetTimeBegin() const;
			// vftable slot 10
			virtual float Slot10() const;
			// vftable slot 15 (0x108F4B20)
			virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

			// The members the properties write
			bool SetTimeBegin(float value);
			bool SetBlendDuration(float value);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

			float blendDuration;  // +0x10
			float timeBegin;  // +0x14
		};

		extern fight::Property** gEnableMotionTrackedExpressionTrackProperties;
		// 0x108B7520
		// 0x108B76D0
		fight::TrackFactory* CreateEnableMotionTrackedExpressionTrackFactory(const char* name);
		void RegisterEnableMotionTrackedExpressionTrackFactory(fight::TrackRegistry* registry, const char* name);
	}

	namespace animation
	{
		// RTTI: engine::animation::ExpressionAnimationTrack (16 vftable slots, 0x38 bytes)
		class ExpressionAnimationTrack : public fight::Track
		{
		public:
			// 0x108B78D0
			ExpressionAnimationTrack();
			virtual ~ExpressionAnimationTrack();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9
			virtual float GetTimeBegin() const;
			// vftable slot 10
			virtual float Slot10() const;
			// vftable slot 15 (0x108F4F00)
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

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

			fight::Name animation;  // +0x10
			float endFrame;  // +0x18
			float initFrame;  // +0x1C
			float speed;  // +0x20
			float startFrame;  // +0x24
			float timeBegin;  // +0x28
			float timeEnd;  // +0x2C
			int cyclic;  // +0x30
			int unknown34;
		};

		extern fight::Property** gExpressionAnimationTrackProperties;
		// 0x108B7AA0
		// 0x108B7AC0
		fight::TrackFactory* CreateExpressionAnimationTrackFactory(const char* name);
		void RegisterExpressionAnimationTrackFactory(fight::TrackRegistry* registry, const char* name);
	}

	namespace animation
	{
		// RTTI: engine::animation::JointLockTrack (16 vftable slots, 0x50 bytes)
		class JointLockTrack : public fight::Track
		{
		public:
			// 0x108B8060
			JointLockTrack();
			virtual ~JointLockTrack();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9
			virtual float GetTimeBegin() const;
			// vftable slot 10
			virtual float Slot10() const;
			// vftable slot 15 (0x108F64B0)
			virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

			// The members the properties write
			bool SetTimeBegin(float value);
			bool SetTimeEnd(float value);
			bool SetLockedJoint(const fight::Name& value);
			bool SetTranslationLock(int value);
			bool SetOffsetTranslation(const math::Vector& value);
			bool SetOffsetOrientation(const math::Vector& value);
			bool SetAutoUpdate(bool value);
			bool SetPriority(int value);
			bool SetBlendInTime(float value);
			bool SetBlendOutTime(float value);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

			fight::Name lockedJoint;  // +0x10
			math::Vector offsetOrientation;  // +0x18
			math::Vector offsetTranslation;  // +0x24
			float blendInTime;  // +0x30
			float blendOutTime;  // +0x34
			float timeBegin;  // +0x38
			float timeEnd;  // +0x3C
			int priority;  // +0x40
			int translationLock;  // +0x44
			bool autoUpdate;  // +0x48
			int unknown4c;
		};

		extern fight::Property** gJointLockTrackProperties;
		// 0x108B8480
		// 0x108B8630
		fight::TrackFactory* CreateJointLockTrackFactory(const char* name);
		void RegisterJointLockTrackFactory(fight::TrackRegistry* registry, const char* name);
	}

	namespace animation
	{
		// RTTI: engine::animation::PuppetMoveTrack (16 vftable slots, 0x30 bytes)
		class PuppetMoveTrack : public fight::Track
		{
		public:
			// 0x108B7FC0
			PuppetMoveTrack();
			virtual ~PuppetMoveTrack();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9
			virtual float GetTimeBegin() const;
			// vftable slot 10
			virtual float Slot10() const;
			// vftable slot 15 (0x108F6470)
			virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

			// The members the properties write
			bool SetTimeBegin(float value);
			bool SetTimeEnd(float value);
			bool SetDistance(const math::Vector& value);
			bool SetPriority(int value);
			bool SetBlendInTime(float value);
			bool SetBlendOutTime(float value);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

			math::Vector distance;  // +0x10
			float blendInTime;  // +0x1C
			float blendOutTime;  // +0x20
			float timeBegin;  // +0x24
			float timeEnd;  // +0x28
			int priority;  // +0x2C
		};

		extern fight::Property** gPuppetMoveTrackProperties;
		// 0x108B84A0
		// 0x108B8660
		fight::TrackFactory* CreatePuppetMoveTrackFactory(const char* name);
		void RegisterPuppetMoveTrackFactory(fight::TrackRegistry* registry, const char* name);
	}

	// RTTI: engine::UndamageableTrack (16 vftable slots, 0x18 bytes)
	class UndamageableTrack : public fight::Track
	{
	public:
		// 0x108B8A80
		UndamageableTrack();
		virtual ~UndamageableTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108F6520)
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

	extern fight::Property** gUndamageableTrackProperties;
	// 0x108B8B90
	// 0x108B8C60
	fight::TrackFactory* CreateUndamageableTrackFactory(const char* name);
	void RegisterUndamageableTrackFactory(fight::TrackRegistry* registry, const char* name);

}

#endif
