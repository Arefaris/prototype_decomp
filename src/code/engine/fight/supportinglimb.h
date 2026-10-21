// The fight tracks of the supporting limb (unit 0x108F99F0 - 0x108FA380; no assert path, file name guessed).
#ifndef ENGINE_FIGHT_SUPPORTINGLIMB_H
#define ENGINE_FIGHT_SUPPORTINGLIMB_H

#include "code/engine/fight/trackfactory.h"

namespace engine
{
	// RTTI: engine::SupportingLimbTrack (16 vftable slots, 0x28 bytes)
	class SupportingLimbTrack : public fight::Track
	{
	public:
		// 0x108F9BC0
		SupportingLimbTrack();
		virtual ~SupportingLimbTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x109307B0)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetSupportingLimb(const fight::Name& value);
		bool SetDirection(const math::Vector& value);

		// The members the engine reads through accessors
		// 0x1092FDC0
		const fight::Name* GetSupportingLimb() const;
		// 0x1092FDD0
		math::Vector GetDirection() const;

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name supportingLimb;  // +0x10
		math::Vector direction;  // +0x18
		float timeBegin;  // +0x24
	};

	extern fight::Property** gSupportingLimbTrackProperties;
	// 0x108F9F50
	// 0x108FA120
	fight::TrackFactory* CreateSupportingLimbTrackFactory(const char* name);
	void RegisterSupportingLimbTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::SupportingLimbExtraLengthTrack (16 vftable slots, 0x28 bytes)
	class SupportingLimbExtraLengthTrack : public fight::Track
	{
	public:
		// 0x108F9C30
		SupportingLimbExtraLengthTrack();
		virtual ~SupportingLimbExtraLengthTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x10930830)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetSupportingLimb(const fight::Name& value);
		bool SetExtraLength(float value);

		// The members the engine reads through accessors
		// 0x1092FDF0
		const fight::Name* GetSupportingLimb() const;
		// 0x1092FE00
		float GetExtraLength() const;

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name supportingLimb;  // +0x10
		float extraLength;  // +0x18
		float timeBegin;  // +0x1C
		float timeEnd;  // +0x20
		int unknown24;
	};

	extern fight::Property** gSupportingLimbExtraLengthTrackProperties;
	// 0x108F9F70
	// 0x108FA150
	fight::TrackFactory* CreateSupportingLimbExtraLengthTrackFactory(const char* name);
	void RegisterSupportingLimbExtraLengthTrackFactory(fight::TrackRegistry* registry, const char* name);

}

#endif
