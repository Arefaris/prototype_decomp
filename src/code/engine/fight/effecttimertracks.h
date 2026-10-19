// The fight tracks that clear decals, set effect timers and drive shader animations (unit 0x10810E00 - 0x10812300).
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
		virtual void Slot15();

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
		virtual void Slot15();

		// The members the properties write
		bool SetName(const fight::Name& value);
		bool SetTime(float value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name name;  // +0x10
		float time;  // +0x18
		unsigned char unknown1c[4];  // TODO tail
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
			virtual void Slot15();

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
