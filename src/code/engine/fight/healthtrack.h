// The fight track that changes an object's health (unit 0x10815010 - 0x10815900).
#ifndef ENGINE_FIGHT_HEALTHTRACK_H
#define ENGINE_FIGHT_HEALTHTRACK_H

#include "code/engine/fight/trackfactory.h"

namespace engine
{
	// RTTI: engine::HealthTrack (16 vftable slots, 0x24 bytes)
	class HealthTrack : public fight::Track
	{
	public:
		// 0x10815070
		HealthTrack();
		virtual ~HealthTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108BA900)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetOperation(int value);
		bool SetApplyTo(int value);
		bool SetHealth(float value);
		bool SetChangeMaxHealth(bool value);
		bool SetChangeMinHealth(bool value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float health;  // +0x10
		float timeBegin;  // +0x14
		int applyTo;  // +0x18
		int operation;  // +0x1C
		bool changeMaxHealth;  // +0x20
		bool changeMinHealth;  // +0x21
	};

	extern fight::Property** gHealthTrackProperties;
	// 0x10815260
	// 0x10815410
	fight::TrackFactory* CreateHealthTrackFactory(const char* name);
	void RegisterHealthTrackFactory(fight::TrackRegistry* registry, const char* name);

}

#endif
