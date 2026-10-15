// The effect track of the fight tree: a fight::Track that starts a particle effect when its action begins, the two
// action classes that carry it (engine::EffectAction plays the effect, engine::AbortEffectAction stops it) and the
// reflected accessors of the track and of the effect itself. Unit 0x10804EC0 - 0x10807550 (no assert path; the
// directory and file names are guesses). The class and member names are guesses until the binary tells the real
// ones; the layouts are read off the engine's accessors.
#ifndef ENGINE_FIGHT_EFFECTTRACK_H
#define ENGINE_FIGHT_EFFECTTRACK_H

#include "code/engine/fight/sequencer.h"
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
		// 0x108056D0
		bool GetD0() const;
	};

	// The track of an effect action (RTTI: engine::EffectTrack and its abort / motion trail variants, another unit).
	// This is the layout the engine's accessors read.
	class EffectTrack : public fight::Track
	{
	public:
		unsigned char unknown4[0xC];
		int unknown10;
		int unknown14;
		math::Vector unknown18;
		bool unknown24;
		unsigned char unknown25[0xB];
		unsigned char unknown30[8];
		unsigned char unknown38[8];
		unsigned char unknown40[8];
		unsigned char unknown48[0x24];
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
		unsigned char unknown118[0x68];
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
}

#endif
