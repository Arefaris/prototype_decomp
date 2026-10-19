// The fight condition that tests the state of a playback (unit 0x10812C10 - 0x10812F90).
#ifndef ENGINE_FIGHT_PLAYBACKSTATECONDITION_H
#define ENGINE_FIGHT_PLAYBACKSTATECONDITION_H

#include "code/engine/fight/trackfactory.h"

namespace engine
{
	// RTTI: engine::PlaybackStateCondition (10 vftable slots, 0x28 bytes)
	class PlaybackStateCondition : public fight::Condition
	{
	public:
		// 0x10812C80
		PlaybackStateCondition();
		virtual ~PlaybackStateCondition();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9 (0x108B94F0)
		virtual bool Evaluate(int a, int b, int c, int d);

		// The members the properties write
		bool SetCompare(int value);
		bool SetState(const fight::Name& value);
		bool SetSpecificPlaybackSet(const fight::Name& value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		int unknownc;
		fight::Name specificPlaybackSet;  // +0x10
		fight::Name state;  // +0x18
		int compare;  // +0x20
		int unknown24;
	};

	extern fight::Property** gPlaybackStateConditionProperties;
	// 0x10812DB0
	// 0x10812DD0
	fight::ConditionFactory* CreatePlaybackStateConditionFactory(const char* name);

}

#endif
