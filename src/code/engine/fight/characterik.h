// The fight tracks of the character limb IK and jump (unit 0x108FA5F0 - 0x108FB3F0; no assert path, file name guessed).
#ifndef ENGINE_FIGHT_CHARACTERIK_H
#define ENGINE_FIGHT_CHARACTERIK_H

#include "code/engine/fight/trackfactory.h"

namespace engine
{
	// RTTI: engine::CharacterEnableLimbIKTrack (16 vftable slots, 0x20 bytes)
	class CharacterEnableLimbIKTrack : public fight::Track
	{
	public:
		// 0x108FA6D0
		CharacterEnableLimbIKTrack();
		virtual ~CharacterEnableLimbIKTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x109313F0)
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

	extern fight::Property** gCharacterEnableLimbIKTrackProperties;
	// 0x108FAB00
	// 0x108FAC80
	fight::TrackFactory* CreateCharacterEnableLimbIKTrackFactory(const char* name);
	void RegisterCharacterEnableLimbIKTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::CharacterIKTrack (16 vftable slots, 0x40 bytes)
	class CharacterIKTrack : public fight::Track
	{
	public:
		// 0x108FA790
		CharacterIKTrack();
		virtual ~CharacterIKTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x109313B0)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetRootJoint(const fight::Name& value);
		bool SetMidJoint(const fight::Name& value);
		bool SetEndJoint(const fight::Name& value);
		bool SetTargetType(int value);
		bool SetPriority(int value);
		bool SetBlendInTime(float value);
		bool SetBlendOutTime(float value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name endJoint;  // +0x10
		fight::Name midJoint;  // +0x18
		fight::Name rootJoint;  // +0x20
		float blendInTime;  // +0x28
		float blendOutTime;  // +0x2C
		float timeBegin;  // +0x30
		float timeEnd;  // +0x34
		int priority;  // +0x38
		int targetType;  // +0x3C
	};

	extern fight::Property** gCharacterIKTrackProperties;
	// 0x108FAAE0
	// 0x108FAC50
	fight::TrackFactory* CreateCharacterIKTrackFactory(const char* name);
	void RegisterCharacterIKTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::CharacterJumpTrack (16 vftable slots, 0x2C bytes)
	class CharacterJumpTrack : public fight::Track
	{
	public:
		// 0x108FB0C0
		CharacterJumpTrack();
		virtual ~CharacterJumpTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x10931980)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetJumpHeight(float value);
		bool SetGravity(float value);
		bool SetPriority(int value);
		bool SetBlendInTime(float value);
		bool SetBlendOutTime(float value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float blendInTime;  // +0x10
		float blendOutTime;  // +0x14
		float gravity;  // +0x18
		float jumpHeight;  // +0x1C
		float timeBegin;  // +0x20
		float timeEnd;  // +0x24
		int priority;  // +0x28
	};

	extern fight::Property** gCharacterJumpTrackProperties;
	// 0x108FB230
	// 0x108FB3F0
	fight::TrackFactory* CreateCharacterJumpTrackFactory(const char* name);
	void RegisterCharacterJumpTrackFactory(fight::TrackRegistry* registry, const char* name);

}

#endif
