// The tracks and actions of the fight core itself: the event, spawn and wait tracks (RTTI namespace fight) and the
// actions they create. Part of the unit 0x105A2440 - 0x105A7BF0 (no assert path; file name guessed).
#ifndef ENGINE_FIGHT_CORETRACKS_H
#define ENGINE_FIGHT_CORETRACKS_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/engine/fight/trackfactory.h"

namespace fight
{
	// The table of named bits the event mask of an 'onEvent' track is picked from (set by the game with SetEventMaskTable)
	// 0x105A6E80 / 0x105A6EA0 / 0x105A6ED0
	void SetEventMaskTable(const EnumEntry* table, int count);

	// RTTI: fight::OnEventTrack (16 vftable slots, 0x50 bytes): runs its branch when an event of the mask comes
	class OnEventTrack : public Track
	{
	public:
		// 0x105A5FC0
		OnEventTrack();
		virtual ~OnEventTrack();

		// vftable slot 0
		virtual Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x105A7390)
		virtual Action* CreateAction(Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetTimeHook(float value);
		bool SetEventMask(int value);
		bool SetInitialTest(bool value);
		BranchHolder* GetBranch();
		bool SetPriority(int value);
		ConditionList* GetConditions();
		// 0x105A6EA0 / 0x105A6ED0: the entries of the event mask table (members that use no member)
		const EnumEntry* GetEventMaskEntry(int index);
		int GetEventMaskCount();

		// 0x105A6E10 - 0x105A6E70: the editor's getters of the same members (nothing calls them)
		float GetTimeEnd() const;
		float GetTimeHook() const;
		int GetEventMask() const;
		bool GetInitialTest() const;
		BranchHolder* GetBranchOf();
		int GetPriority() const;
		ConditionList* GetConditionsOf();

		static void RegisterProperties();
		static void ClearProperties();

		BranchHolder branch;  // +0x10
		ConditionList conditions;  // +0x34
		float timeBegin;  // +0x38
		float timeEnd;  // +0x3C
		float timeHook;  // +0x40
		int priority;  // +0x44
		int eventMask;  // +0x48
		bool initialTest;  // +0x4C
	};

	extern Property** gOnEventTrackProperties;

	// 0x105A62B0 / 0x105A64B0
	TrackFactory* CreateOnEventTrackFactory(const char* name);
	void RegisterEventTrackFactory(TrackRegistry* registry, const char* name);

	// RTTI: fight::SpawnTrack (16 vftable slots, 0x40 bytes)
	class SpawnTrack : public Track
	{
	public:
		// 0x105A6720
		SpawnTrack();
		virtual ~SpawnTrack();

		// vftable slot 0
		virtual Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15
		virtual Action* CreateAction(Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		BranchHolder* GetBranch();
		ConditionList* GetConditions();

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		BranchHolder branch;  // +0x10
		ConditionList conditions;  // +0x34
		float timeBegin;  // +0x38
		float timeEnd;  // +0x3C
	};

	extern Property** gSpawnTrackProperties;

	// 0x105A68C0 / 0x105A69F0
	TrackFactory* CreateSpawnTrackFactory(const char* name);
	void RegisterSpawnTrackFactory(TrackRegistry* registry, const char* name);

	// RTTI: fight::WaitTrack (16 vftable slots, 0x1C bytes)
	class WaitTrack : public Track
	{
	public:
		// 0x105A6B00
		WaitTrack();
		virtual ~WaitTrack();

		// vftable slot 0
		virtual Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x105B1F30)
		virtual Action* CreateAction(Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEndMin(float value);
		bool SetTimeEndMax(float value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float timeBegin;  // +0x10
		float timeEndMax;  // +0x14
		float timeEndMin;  // +0x18
	};

	extern Property** gWaitTrackProperties;

	// 0x105A6C10 / 0x105A6D10
	TrackFactory* CreateWaitTrackFactory(const char* name);
	void RegisterWaitTrackFactory(TrackRegistry* registry, const char* name);
}

#endif
