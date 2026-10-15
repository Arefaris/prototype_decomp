// The effect track of the fight tree: a fight::Track that starts a particle effect when its action begins, the two
// action classes that carry it (engine::EffectAction plays the effect, engine::AbortEffectAction stops it) and the
// reflected accessors of the track and of the effect itself. Unit 0x10804EC0 - 0x10807550 (no assert path; the
// directory and file names are guesses). The class and member names are guesses until the binary tells the real
// ones; the layouts are read off the engine's accessors.
#ifndef ENGINE_FIGHT_EFFECTTRACK_H
#define ENGINE_FIGHT_EFFECTTRACK_H

#include "code/core/linklist.h"
#include "code/engine/fight/sequencer.h"
#include "code/math/matrix.h"
#include "code/math/vector.h"

namespace engine
{
	// The game's veto on an effect track's begin (set through the track factory's exposed functions; names guessed)
	typedef bool (*EffectTrackCheck)(unsigned int, const float*, int);
	extern EffectTrackCheck gEffectTrackCheck;
	extern int gEffectTrackCheckContext;
	// The counter a script holds the effect tracks with; 0x111BEA74 keeps the value in force when it was changed
	extern int gEffectSuspendSaved;
	extern int gEffectSuspendCount;

	// The engine's own copies of core's reference helpers, per type (core::RefAssign / core::SafeRelease)
	// 0x108058E0 / 0x10805910
	void AssignEffectRef(core::IRefCount*& pointer, core::IRefCount* object);
	void ReleaseEffectRef(core::IRefCount*& object);

	// The particle effect an action plays (RTTI: engine::Effect, another unit). Only the members this unit touches
	// are laid out here.
	class Effect
	{
	public:
		unsigned char unknown0[0x10];
		// Six handles the begin locks one after another
		unsigned char unknown10[8];
		unsigned char unknown18[8];
		unsigned char unknown20[8];
		unsigned char unknown28[8];
		unsigned char unknown30[8];
		unsigned char unknown38[8];
		unsigned char unknown40[8];
		unsigned char unknown48[8];
		// Nine vectors: the six the begin scales, then the three it copies
		math::Vector vectors50[9];
		float unknownbC;
		float unknownc0;
		float unknownc4;
		int unknownc8;
		float unknowncc;
		bool unknownd0;
		bool unknownd1;

		// 0x10805550
		math::Vector GetVector98() const;
		// 0x10805580
		int GetC8() const;
		// 0x10805590
		unsigned char* GetHandle10();
		// 0x108055A0
		math::Vector GetVector50() const;
		// 0x108055C0
		unsigned char* GetHandle18();
		// 0x108055D0
		math::Vector GetVector5c() const;
		// 0x108055F0
		unsigned char* GetHandle20();
		// 0x10805600
		math::Vector GetVector68() const;
		// 0x10805620
		unsigned char* GetHandle28();
		// 0x10805630
		math::Vector GetVector74() const;
		// 0x10805650
		unsigned char* GetHandle30();
		// 0x10805660
		math::Vector GetVector80() const;
		// 0x10805690
		unsigned char* GetHandle38();
		// 0x108056A0
		math::Vector GetVector8c() const;
		// 0x10805530
		bool GetD1() const;
		// 0x10805540
		unsigned char* GetHandle48();
		// 0x108056D0
		bool GetD0() const;
	};

	// The track of an effect action (RTTI: engine::EffectTrack and its abort / motion trail variants, another unit).
	// This is the layout the engine's accessors read.
	class EffectTrack : public fight::Track
	{
	public:
		unsigned char unknown4[4];
		// The head of the list of the actions the track drives: every action carries a core::Link node at +0x1C
		// and inserts itself into it (0x10805B90 is the converting copy of that node's constructor)
		core::LinkList<EffectTrack> watchList;
		unsigned char unknownC[4];
		int unknown10;
		int unknown14;
		math::Vector unknown18;
		bool unknown24;
		unsigned char unknown25[0xB];
		unsigned char unknown30[8];
		unsigned char unknown38[8];
		unsigned char unknown40[8];
		unsigned char unknown48[0x18];
		math::Vector unknown60;
		math::Vector unknown6c;
		math::Vector unknown78;
		float unknown84;
		// Nine four-float colours
		float unknown88;
		float unknown8c;
		float unknown90;
		float unknown94;
		float unknown98;
		float unknown9c;
		float unknowna0;
		float unknowna4;
		float unknowna8;
		float unknownac;
		float unknownb0;
		float unknownb4;
		float unknownb8;
		float unknownbc;
		float unknownc0;
		float unknownc4;
		float unknownc8;
		float unknowncc;
		float unknownd0;
		float unknownd4;
		float unknownd8;
		float unknowndc;
		float unknowne0;
		float unknowne4;
		float unknowne8;
		float unknownec;
		float unknownf0;
		float unknownf4;
		float unknownf8;
		float unknownfc;
		float unknown100;
		float unknown104;
		float unknown108;
		float unknown10c;
		float unknown110;
		float unknown114;
		// The second run of floats the unit keeps accessors for (0x108052D0 - 0x10805520)
		float unknown118;
		float unknown11c;
		float unknown120;
		float unknown124;
		float unknown128;
		float unknown12c;
		float unknown130;
		float unknown134;
		float unknown138;
		float unknown13c;
		float unknown140;
		float unknown144;
		float unknown148;
		float unknown14c;
		float unknown150;
		float unknown154;
		float unknown158;
		float unknown15c;
		float unknown160;
		float unknown164;
		float unknown168;
		float unknown16c;
		float unknown170;
		float unknown174;
		float unknown178;
		float unknown17c;
		float unknown180;
		float unknown184;
		float unknown188;
		float unknown18c;
		float unknown190;
		int unknown194;
		int unknown198;
		int unknown19c;
		int unknown1a0;
		int unknown1a4;
		bool unknown1a8;
		bool unknown1a9;
		bool unknown1aa;
		bool unknown1ab;
		bool unknown1ac;
		bool unknown1ad;

		// 0x10804EE0
		void GetUnknown14(int& value) const;
		// 0x10804EF0
		int* GetUnknown10();
		// 0x10804F00
		bool GetUnknown24() const;
		// 0x10804F10
		float GetUnknown18x() const;
		// 0x10804F20
		float GetUnknown190() const;
		// 0x10804F30
		unsigned char* GetUnknown30();
		// 0x10804F40
		unsigned char* GetUnknown40();
		// 0x10804F50
		int GetUnknown1a4() const;
		// 0x10804F60
		unsigned char* GetUnknown38();
		// 0x10804F70
		math::Vector GetUnknown6c() const;
		// 0x10804F90
		math::Vector GetUnknown78() const;
		// 0x10804FB0
		int GetUnknown194() const;
		// 0x10804FC0
		math::Vector* GetUnknown18();
		// 0x10804FD0
		bool GetUnknown1a8() const;
		// 0x10804FE0
		unsigned char* GetUnknown48();
		// 0x10804FF0
		float GetUnknown88() const;
		// 0x10805000
		float GetUnknown110() const;
		// 0x10805010
		int GetUnknown1a0() const;
		// 0x10805020
		float GetUnknown188() const;
		// 0x10805030
		bool GetUnknown1aa() const;
		// 0x10805040
		float GetUnknown184() const;
		// 0x10805050
		float GetUnknown114() const;
		// 0x10805060
		float GetUnknown180() const;
		// 0x10805070
		bool GetUnknown1ad() const;
		// 0x10805080
		float* GetUnknown20();
		// 0x10805090
		bool GetUnknown1a9() const;
		// 0x108050A0
		float GetUnknownc0() const;
		// 0x108050B0
		float GetUnknownc4() const;
		// 0x108050C0
		int GetUnknown198() const;
		// 0x108050D0
		float GetUnknowne4() const;
		// 0x108050E0
		float GetUnknowne8() const;
		// 0x108050F0
		float GetUnknownf8() const;
		// 0x10805100
		float GetUnknownfc() const;
		// 0x10805110
		float GetUnknownec() const;
		// 0x10805120
		float GetUnknownf4() const;
		// 0x10805130
		float GetUnknownf0() const;
		// 0x10805140
		int GetUnknown19c() const;
		// 0x10805150
		float GetUnknown100() const;
		// 0x10805160
		float GetUnknown104() const;
		// 0x10805170
		float GetUnknown108() const;
		// 0x10805180
		float GetUnknown10c() const;
		// 0x10805190
		float GetUnknown98() const;
		// 0x108051A0
		float GetUnknown9c() const;
		// 0x108051B0
		float GetUnknowne0() const;
		// 0x108051C0
		float GetUnknownbc() const;
		// 0x108051D0
		float GetUnknownb4() const;
		// 0x108051E0
		float GetUnknowna4() const;
		// 0x108051F0
		float GetUnknowna0() const;
		// 0x10805200
		float GetUnknown8c() const;
		// 0x10805210
		float GetUnknownb0() const;
		// 0x10805220
		float GetUnknownac() const;
		// 0x10805230
		float GetUnknowna8() const;
		// 0x10805240
		float GetUnknown90() const;
		// 0x10805250
		float GetUnknownb8() const;
		// 0x10805260
		float GetUnknown94() const;
		// 0x10805270
		float GetUnknownd4() const;
		// 0x10805280
		float GetUnknownd0() const;
		// 0x10805290
		float GetUnknowncc() const;
		// 0x108052A0
		float GetUnknownd8() const;
		// 0x108052B0
		float GetUnknowndc() const;
		// 0x108052C0
		float GetUnknownc8() const;
	};

	// 0x10805750 builds the spawn matrix of an effect from the parent matrix it hangs off: the parent's second row is
	// the direction the effect is aimed along and its translation row the origin. The engine's copy pops two arguments
	// and never reads ecx, so it is a member function that does not touch its object; its class is not known.
	class EffectSpawnTransform
	{
	public:
		void BuildMatrix(const math::Matrix& parent, math::Matrix& matrix) const;
	};

	// The variants of the effect track the game names (RTTI: engine::AbortEffectTrack / MotionTrailTrack, 16 vtable
	// slots each; nothing of their own is read here, they only have to be the type the actions link themselves on)
	class AbortEffectTrack : public EffectTrack
	{
	};

	// 0x108052D0 - 0x10805520: the second run of accessors, over the same members. RTTI gives the three track
	// classes the same base (fight::Track), so they are siblings that declare their own copies of the members and of
	// their accessors; which of the two variants owns this run is a guess. They are written on the motion trail
	// track, which shares the effect track's layout.
	class MotionTrailTrack : public EffectTrack
	{
	public:
		// 0x108052D0
		math::Vector GetUnknown60() const;
		// 0x108052F0
		bool GetUnknown1ac() const;
		// 0x10805300
		float GetUnknown13c() const;
		// 0x10805310
		float GetUnknown140() const;
		// 0x10805320
		float GetUnknown158() const;
		// 0x10805330
		float GetUnknown15c() const;
		// 0x10805340
		float GetUnknown150() const;
		// 0x10805350
		float GetUnknown154() const;
		// 0x10805360
		float GetUnknown168() const;
		// 0x10805370
		float GetUnknown16c() const;
		// 0x10805380
		float GetUnknown160() const;
		// 0x10805390
		float GetUnknown164() const;
		// 0x108053A0
		float GetUnknown170() const;
		// 0x108053B0
		float GetUnknown174() const;
		// 0x108053C0
		float GetUnknown178() const;
		// 0x108053D0
		float GetUnknown17c() const;
		// 0x108053E0
		float GetUnknown120() const;
		// 0x108053F0
		float GetUnknown124() const;
		// 0x10805400
		float GetUnknown14c() const;
		// 0x10805410
		float GetUnknown138() const;
		// 0x10805420
		float GetUnknown130() const;
		// 0x10805430
		float GetUnknown12c() const;
		// 0x10805440
		float GetUnknown128() const;
		// 0x10805450
		float GetUnknown118() const;
		// 0x10805460
		float GetUnknown134() const;
		// 0x10805470
		float GetUnknown11c() const;
		// 0x10805480
		float GetUnknown148() const;
		// 0x10805490
		float GetUnknown144() const;
		// 0x108054A0
		float* GetUnknown84();
		// 0x108054B0
		unsigned char* GetUnknown40();
		// 0x108054C0
		float GetUnknownb4() const;
		// 0x108054D0
		float GetUnknowna4() const;
		// 0x108054E0
		float GetUnknownac() const;
		// 0x108054F0
		float GetUnknownbc() const;
		// 0x10805500
		float GetUnknownb0() const;
		// 0x10805510
		float GetUnknowna8() const;
		// 0x10805520
		float GetUnknownb8() const;
	};

	// The node an action registers on a track it watches instead of driving it: the track keeps that list at +0x24
	// and the node is inserted and removed through the track (register, unregister)
	class TrackWatch
	{
	public:
		TrackWatch(fight::Track* newTrack)
		{
			track = newTrack;
			next = 0;
			prev = 0;
			if (newTrack != 0)
			{
				newTrack->Register(this);
			}
		}
		~TrackWatch()
		{
			if (track != 0)
			{
				track->Unregister(this);
			}
		}

		fight::Track* track;
		TrackWatch* next;
		TrackWatch* prev;
	};

	// The action that plays a particle effect (RTTI: engine::EffectAction, 9 vtable slots, size 0x50)
	class EffectAction : public fight::Action
	{
	public:
		EffectAction(EffectTrack* newTrack, fight::Track* listener, int object, core::IRefCount* effect, int mode);
		virtual ~EffectAction();

		core::Link<EffectTrack> link;
		TrackWatch watch;
		int unknown34;
		int unknown38;
		core::IRefCount* unknown3c;
		int unknown40;
		core::IRefCount* unknown44;
		int unknown48;
		bool unknown4c;
	};

	// The action that stops an effect again (RTTI: engine::AbortEffectAction, 9 vtable slots, size 0x28)
	class AbortEffectAction : public fight::Action
	{
	public:
		AbortEffectAction(AbortEffectTrack* newTrack, fight::Track* listener);
		virtual ~AbortEffectAction();

		core::Link<EffectTrack> link;
	};

	// The action that starts a motion trail (RTTI: engine::MotionTrailAction, 9 vtable slots, size 0x3C)
	class MotionTrailAction : public fight::Action
	{
	public:
		MotionTrailAction(EffectTrack* newTrack, fight::Track* listener, int value);
		virtual ~MotionTrailAction();

		core::Link<EffectTrack> link;
		TrackWatch watch;
		int unknown34;
		int unknown38;
	};
}

#endif
