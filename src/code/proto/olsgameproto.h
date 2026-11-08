// proto::OLSGameProto and proto::OLSGameSystemLinkProto (RTTI names): the game's own layers of the online services' game
// session. They start the level the game database names when a session begins and keep the database and the texture
// loading in the mode the session needs while it runs. Unit 0x104DC5D0 - 0x104DC830 (no assert path; the file name is a
// guess). Names other than the RTTI ones are guesses.
#ifndef PROTO_OLSGAMEPROTO_H
#define PROTO_OLSGAMEPROTO_H

#include "code/engine/online/olsgame.h"

namespace proto
{
	class OLSGameProto : public engine::OLSGame
	{
	public:
		// 0x104DC5D0
		explicit OLSGameProto(int newState);
		// The destructor is the compiler's: 0x104DC600 (deleting destructor 0x104DC6D0)

		// vftable slots 4, 6, 7 and 8 (0x104DC610, 0x104DC660, 0x104DC670, 0x104DC6A0)
		virtual void Slot4();
		virtual void Slot6();
		virtual void Slot7();
		virtual void Slot8();

		bool savedTextureLoadFlag;  // +0x24
	};

	class OLSGameSystemLinkProto : public engine::OLSGameSystemLink
	{
	public:
		// 0x104DC700
		explicit OLSGameSystemLinkProto(int newState);
		// The destructor is the compiler's: 0x104DC730 (deleting destructor 0x104DC800)

		// vftable slots 4, 6, 7 and 8 (0x104DC740, 0x104DC790, 0x104DC7A0, 0x104DC7D0)
		virtual void Slot4();
		virtual void Slot6();
		virtual void Slot7();
		virtual void Slot8();

		bool savedTextureLoadFlag;  // +0x28
	};
}

#endif
