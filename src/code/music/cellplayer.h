// The cell players of the music library (RTTI: music::CellPlayer and music::MGraphCellPlayer): play one cell of a cue.
// Only the layout and the state enumeration are described so far; the state names come from the strings the
// reflection registers them under.
#ifndef MUSIC_CELLPLAYER_H
#define MUSIC_CELLPLAYER_H

#include "code/om/allocation.h"

#include "code/mgraph/patch.h"
#include "code/audio/remoteplayerevent.h"

namespace music
{
	class Cell;
	class Cue;


	// What a request to a cell player carries (0x28 bytes; the meaning of the members is not known)
	struct CellPlayerParameters
	{
		int unknown0;
		int unknown4;
		int unknown8;
		int unknownC;
		bool unknown10;
		int unknown14;
		int unknown18;
		int unknown1C;
		int unknown20;
		bool unknown24;
	};

	// A request that has been made (0x2C bytes)
	struct CellPlayerRequest
	{
		bool valid;
		CellPlayerParameters parameters;
	};

	class CellPlayer
	{
	public:
		enum State
		{
			StateFree = 0,
			StateWaitingToFadeIn = 3,
			StatePlaying = 5,
			StateWaitingToFadeOut = 6
		};

		CellPlayer() :
			state(0),
			unknown8(0),
			unknownC(0),
			cue(0)
		{
		}
		// Slot 0 (0x105E2AA0 is the deleting destructor)
		virtual ~CellPlayer()
		{
		}
		// Slots 1 to 9 (0x105E2A10 - 0x105E2A90): the base class does nothing, whatever the arguments are
		virtual bool Slot1(Cell* cell, int layer, int part);
		virtual void Slot2();
		virtual void Slot3();
		virtual void Slot4();
		virtual bool Slot5();
		virtual void Slot6(int unknown);
		virtual void Slot7(CellPlayerParameters parameters);
		virtual void Slot8(CellPlayerParameters parameters);
		virtual int Slot9();
		// Slot 10 (0x105F9A10): the new state
		virtual void SetState(int newState);
		// Slots 11 and 12 (0x105F9A00 / 0x105F9A60): the second answers the cell of the cue that the player plays
		virtual void Slot11(int unknown);
		virtual Cell* Slot12();

		int state;  // 4
		int unknown8;
		int unknownC;
		Cue** cue;  // 0x10
		int unknown14;
	};

	// 0x105E3790 (name guessed): makes the reflection of the player
	void RegisterMGraphCellPlayerMeta();

	// The player of a cell that plays a graph of the music graph library (0x88 bytes)
	class MGraphCellPlayer : public CellPlayer
	{
	public:
		// 0x105E3120
		MGraphCellPlayer();
		// Slot 0 (0x105E3840 is the body, the deleting destructor 0x105E38C0)
		virtual ~MGraphCellPlayer();
		OM_ALLOCATION(MGraphCellPlayer);

		virtual bool Slot1(Cell* cell, int layer, int part);
		virtual void Slot2();
		virtual void Slot3();
		virtual void Slot4();
		virtual bool Slot5();
		virtual void Slot7(CellPlayerParameters parameters);
		virtual void Slot8(CellPlayerParameters parameters);
		virtual int Slot9();
		virtual void SetState(int newState);
		virtual void Slot11(int unknown);
		// Slot 12 (0x105E2F00): the base class's
		virtual Cell* Slot12();

		// 0x105E3E10: takes the cell to play (its layer and part) and makes the player's state from its patch; resets the
		// player and answers false when the cell has no patch
		bool Setup(Cell* cell, int layer, int part);
		// 0x105E38F0: makes the player's state from the patch (not reconstructed)
		bool SetUpFromPatch(mgraph::Patch* patch);

		// 0x105E2F50 (name guessed): how many of the patch's samples make one of 48000 samples a second
		float GetSampleScale();

		// 0x105E3220 (name guessed): plays the next frames of the cell and answers how many of them it played (not
		// reconstructed)
		int Advance(int frames);

		// 0x105E31D0: lets the graph go and puts the player back in the state it starts from
		void Reset();

		audio::RemotePlayer* graph;  // 0x18: the player the patch plays in
		float unknown1C;
		bool unknown20;
		bool unknown21;
		bool unknown22;
		unsigned int unknown24;
		unsigned int unknown28;
		int unknown2C;
		CellPlayerRequest first;  // 0x30
		CellPlayerRequest second;  // 0x5C
	};
}

#endif
