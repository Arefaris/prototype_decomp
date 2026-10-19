// The fight tracks that clear decals and set the effect timers (unit 0x10810E00 - 0x10811750).
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

}

#endif
