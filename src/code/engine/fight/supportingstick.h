// The fight track that sticks a character to the supporting surface (unit 0x108F9A50 - 0x108FA180; no assert path, file name guessed).
#ifndef ENGINE_FIGHT_SUPPORTINGSTICK_H
#define ENGINE_FIGHT_SUPPORTINGSTICK_H

#include "code/engine/fight/trackfactory.h"

namespace engine
{
	// RTTI: engine::SupportingSurfaceStickTrack (16 vftable slots, 0x1C bytes)
	class SupportingSurfaceStickTrack : public fight::Track
	{
	public:
		// 0x108F9B10
		SupportingSurfaceStickTrack();
		virtual ~SupportingSurfaceStickTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x109307F0)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetStickToSupportingSurface(bool value);
		bool SetResetOrientationDelta(bool value);
		bool SetResetLimbSmoothing(bool value);
		bool SetRestoreOnEnd(bool value);

		// The members the engine reads through accessors
		// 0x1092FE10
		bool GetStickToSupportingSurface() const;
		// 0x1092FE20
		bool GetResetOrientationDelta() const;
		// 0x1092FE30
		bool GetResetLimbSmoothing() const;
		// 0x1092FE40
		bool GetRestoreOnEnd() const;

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float timeBegin;  // +0x10
		float timeEnd;  // +0x14
		bool resetLimbSmoothing;  // +0x18
		bool resetOrientationDelta;  // +0x19
		bool restoreOnEnd;  // +0x1A
		bool stickToSupportingSurface;  // +0x1B
	};

	extern fight::Property** gSupportingSurfaceStickTrackProperties;
	// 0x108F9F90
	// 0x108FA180
	fight::TrackFactory* CreateSupportingSurfaceStickTrackFactory(const char* name);
	void RegisterSupportingSurfaceStickTrackFactory(fight::TrackRegistry* registry, const char* name);

}

#endif
