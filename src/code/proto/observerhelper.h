// proto::ObserverHelper (RTTI name; base engine::DBObserver): watches the game database's settings that the game
// applies when they change: the gamepad rumble, the language and the camera inversions. Unit 0x104DF580 - 0x104DF8D0 (no
// assert path; the file name is a guess). Names other than the RTTI one are guesses.
#ifndef PROTO_OBSERVERHELPER_H
#define PROTO_OBSERVERHELPER_H

#include "code/core/name.h"
#include "code/engine/dbobserver.h"

namespace proto
{
	// What the database tells an observer about a change (names guessed)
	struct DBChange
	{
		int unknown0;
		unsigned char player;  // +4
		unsigned char index;  // +5
		int value;  // +8
	};

	class ObserverHelper : public engine::DBObserver
	{
	public:
		// 0x104DF580
		ObserverHelper();
		// 0x104DF660
		~ObserverHelper();

		// vftable slots 0 and 1 (0x104DF710, 0x104DED90)
		virtual void OnDBSlot0(int key, int change);
		virtual void OnDBSlot1(int a, int b);

		int unknown4;
		core::Name<core::CaseSensitiveKey> languageKey;  // +8
	};
}

#endif
