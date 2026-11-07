// proto::GameDatabaseBitRecord (RTTI name; base engine::DBObserver): a set of flags kept in the integer values of one
// game database subject, 32 flags to a value (the smart hint manager keeps the hints it has shown in one). It watches
// the subject: when the subject goes away it forgets it. Unit 0x104DF2D0 - 0x104DF4A0 (no assert path; the file name
// is a guess). The member names are guesses.
#ifndef PROTO_GAMEDATABASEBITRECORD_H
#define PROTO_GAMEDATABASEBITRECORD_H

#include "code/core/name.h"
#include "code/engine/database/gamedatabase.h"
#include "code/engine/dbobserver.h"

namespace proto
{
	class GameDatabaseBitRecord : public engine::DBObserver
	{
	public:
		// 0x104E07C0 / 0x104E0860: a record of count flags in the game database subject with the name
		GameDatabaseBitRecord(core::Name<core::CaseSensitiveKey> newName, int newCount);
		~GameDatabaseBitRecord();
		// vftable slots 0 and 1 (0x104DF2D0, 0x104DF2E0): the second one lets go of the subject
		virtual void OnDBSlot0(int a, int b);
		virtual void OnDBSlot1(int a, int b);

		// 0x104DF2F0: whether the flag is set
		bool Test(int index);
		// 0x104DF330 / 0x104DF3E0: sets / clears the flag
		void Set(int index);
		void Clear(int index);
		// 0x104DF380 / 0x104DF440: sets / clears every flag
		void SetAll();
		void ClearAll();

		int unknown4;
		core::Name<core::CaseSensitiveKey> subjectName;  // +8
		int count;  // +0x10: the number of flags
		engine::DBSubject* subject;  // +0x14
	};
}

#endif
