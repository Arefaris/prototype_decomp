// proto::SmartHintManager (RTTI name; the global 0x11275A58, 0xA6C0 bytes): the hints the game shows to the player:
// which one is on screen, the log of the ones seen, timers kept in the game database and the hint texts and images
// read from the script. The Lua functions that control it are registered by the unit's registration function
// (0x1059DFB0). Unit 0x1059AB30 - 0x1059E870 (no assert path; the file name is a guess). All member names except the
// class are guesses.
#ifndef PROTO_SMARTHINT_SMARTHINTMANAGER_H
#define PROTO_SMARTHINT_SMARTHINTMANAGER_H

#include "code/core/name.h"

namespace proto
{
	// The set of hint flags the manager keeps (the object at +4 of the manager; two members of another unit)
	class SmartHintLog
	{
	public:
		// 0x104DF330 / 0x104DF3E0: marks / unmarks the hint with the index
		void Set(int index);
		void Clear(int index);
	};

	// The hint on screen: what is shown, how far it is and which hint it is
	struct SmartHintShown
	{
		// 0x1059B340
		void Reset();

		int kind;  // +0
		int state;  // +4: 0 nothing, 1 and 2 shown, 3 starting
		int id;  // +8
		int unknownC;
		bool flag;  // +0x10
	};

	// The three flags kept next to the shown hint (0x1059B360)
	struct SmartHintFlags
	{
		// 0x1059B360
		void Reset();

		bool unknown0;
		bool unknown1;
		bool unknown2;
	};

	class SmartHintManager
	{
	public:
		// 0x1059AB30
		void SetEnabledFlag(bool value);
		// 0x1059AB40 / 0x1059AB50 / 0x1059AB70 / 0x1059AB80 / 0x1059ABA0: the mode word (0 off, 1, 2 and 3 on)
		bool IsModeOne();
		void SetModeTwo(bool on);
		bool IsModeTwo();
		void SetModeThree(bool on);
		bool IsModeThree();
		// 0x1059ABB0
		void SetFlags0(bool value);
		// 0x1059AC60: marks or unmarks a hint in the log
		void SetHintFlag(int index, bool set);
		// 0x1059AC90 / 0x1059ACB0: the timers, kept in the game database
		float GetTimer(int index);
		void SetTimer(int index, float value);
		// 0x1059AED0: something is shown
		bool IsShowing();
		// 0x1059B0F0: moves the shown hint on one step
		void AdvanceShown();
		// 0x1059B110: starts showing the hint with the id
		void StartShowing(int newId);
		// 0x1059B140: stops the hint on screen and marks it as seen
		void StopShowing(bool unused);
		// 0x1059B160: reads the player's setting from the game database
		void ReadSetting();
		// 0x1059B190
		void SetFlag2C();
		// 0x1059B210
		void SetUnknown20(float value);
		// 0x1059B510: switches the manager on or off (off hides what is shown)
		void SetActive(bool active);
		// 0x1059B1A0: hides the hint on screen when it is the one being shown (not reconstructed)
		void HideShown();
		// 0x1059B4D0: puts the state back to the start
		void ResetState();

		bool enabled;  // +0
		bool active;  // +1
		unsigned char unknown2[2];
		SmartHintLog* log;  // +4
		SmartHintShown shown;  // +8
		float unknown1C;
		float unknown20;
		unsigned char unknown24[4];
		int mode;  // +0x28
		bool flag2C;  // +0x2C
		unsigned char unknown2D[3];
		int setting;  // +0x30
		unsigned char unknown34[0xa6bd - 0x34];
		SmartHintFlags flags;  // +0xA6BD
	};

	extern SmartHintManager* gSmartHintManager;
}

#endif
