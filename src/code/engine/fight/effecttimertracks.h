// The fight tracks and conditions that clear decals, time effects and drive shader animations (unit 0x10810E00 - 0x10812300).
#ifndef ENGINE_FIGHT_EFFECTTIMERTRACKS_H
#define ENGINE_FIGHT_EFFECTTIMERTRACKS_H

#include "code/engine/fight/trackfactory.h"

namespace engine
{
	// RTTI: engine::DeleteAllDecalsTrack (16 vftable slots, 0x14 bytes)
	class DeleteAllDecalsTrack : public fight::Track
	{
	public:
		// 0x10810E30
		DeleteAllDecalsTrack();
		virtual ~DeleteAllDecalsTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108AC8E0)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float timeBegin;  // +0x10
	};

	extern fight::Property** gDeleteAllDecalsTrackProperties;
	// 0x10810F30
	// 0x10810FD0
	fight::TrackFactory* CreateDeleteAllDecalsTrackFactory(const char* name);
	void RegisterDeleteAllDecalsTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::CheckEffectTimerCondition (10 vftable slots, 0x20 bytes)
	class CheckEffectTimerCondition : public fight::Condition
	{
	public:
		// 0x108110F0
		CheckEffectTimerCondition();
		virtual ~CheckEffectTimerCondition();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9 (0x108AC940)
		virtual bool Evaluate(int a, int b, int c, int d);

		// The members the properties write
		bool SetTimerName(const fight::Name& value);
		bool SetCompare(int value);
		bool SetTimeElapsed(float value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		int unknownc;
		fight::Name timerName;  // +0x10
		float timeElapsed;  // +0x18
		int compare;  // +0x1C
	};

	extern fight::Property** gCheckEffectTimerConditionProperties;
	// 0x10811270
	// 0x10811290
	fight::ConditionFactory* CreateCheckEffectTimerConditionFactory(const char* name);

	// RTTI: engine::SetEffectTimerTrack (16 vftable slots, 0x20 bytes)
	class SetEffectTimerTrack : public fight::Track
	{
	public:
		// 0x108114D0
		SetEffectTimerTrack();
		virtual ~SetEffectTimerTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108ACBA0)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetName(const fight::Name& value);
		bool SetTime(float value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name name;  // +0x10
		float time;  // +0x18
		int unknown1c;
	};

	extern fight::Property** gSetEffectTimerTrackProperties;
	// 0x108115E0
	// 0x10811600
	fight::TrackFactory* CreateSetEffectTimerTrackFactory(const char* name);
	void RegisterSetEffectTimerTrackFactory(fight::TrackRegistry* registry, const char* name);

	namespace animation
	{
		// RTTI: engine::animation::ShaderAnimationTrack (16 vftable slots, 0x38 bytes)
		class ShaderAnimationTrack : public fight::Track
		{
		public:
			// 0x10811870
			ShaderAnimationTrack();
			virtual ~ShaderAnimationTrack();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9
			virtual float GetTimeBegin() const;
			// vftable slot 10
			virtual float Slot10() const;
			// vftable slot 15 (0x108AD070)
			virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

			// The members the properties write
			bool SetTimeBegin(float value);
			bool SetTimeEnd(float value);
			bool SetRestoreStateOnEnd(bool value);
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
			bool restoreStateOnEnd;  // +0x34
		};

		extern fight::Property** gShaderAnimationTrackProperties;
		// 0x10811A90
		// 0x10811AB0
		fight::TrackFactory* CreateShaderAnimationTrackFactory(const char* name);
		void RegisterShaderAnimationTrackFactory(fight::TrackRegistry* registry, const char* name);
	}

}

#endif
