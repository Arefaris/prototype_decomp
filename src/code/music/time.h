// The small value types of the music library (RTTI: music::Time, music::TimeSignature, music::FollowAction with its
// enum Type, and music::Fade); they are reflected as om meta classes (time.cpp). Member names come from the strings
// the reflection registers them under.
#ifndef MUSIC_TIME_H
#define MUSIC_TIME_H

#include "code/om/allocation.h"

namespace music
{
	// A position in the music: bar, beat and note, or a number of milliseconds (0x14 bytes)
	class Time
	{
	public:
		// Inlined by the users (the engine's own copy is 0x105D2760)
		Time() :
			note(0),
			beat(0),
			bar(0),
			milliseconds(0),
			isInMilliseconds(false)
		{
		}
		// 0x105D2780 / 0x105D2790
		void SetBar(unsigned int newBar);
		unsigned int GetBar() const;
		// 0x105D27A0 / 0x105D27B0
		void SetBeat(unsigned int newBeat);
		unsigned int GetBeat() const;
		// 0x105D27C0 / 0x105D27D0
		void SetNote(unsigned int newNote);
		unsigned int GetNote() const;
		// 0x105D27E0 / 0x105D27F0
		void SetMilliseconds(unsigned int newMilliseconds);
		unsigned int GetMilliseconds() const;
		// 0x105D2800 / 0x105D2810
		void SetIsInMilliseconds(bool newIsInMilliseconds);
		bool GetIsInMilliseconds() const;
		OM_ALLOCATION(Time);

		unsigned int note;
		unsigned int beat;
		unsigned int bar;
		unsigned int milliseconds;
		bool isInMilliseconds;
	};

	class TimeSignature
	{
	public:
		// 0x105D73B0
		TimeSignature(unsigned int newNumerator, unsigned int newDenominator);
		// 0x105D72F0 / 0x105D2820
		void SetNumerator(const unsigned int& newNumerator);
		const unsigned int& GetNumerator() const;
		// 0x105D7310 / 0x105D7300
		void SetDenominator(const unsigned int& newDenominator);
		const unsigned int& GetDenominator() const;

		unsigned int numerator;
		unsigned int denominator;
	};

	class FollowAction
	{
	public:
		enum Type
		{
			TypeStop,
			TypeNext,
			TypePrev,
			TypeFirst,
			TypeLast,
			TypeRandom
		};

		// Inlined by the users (a value that is read into)
		FollowAction() :
			type(TypeStop)
		{
		}
		// 0x105D73D0
		FollowAction(Type newType);
		// 0x105D7320 / 0x105D2830
		void SetType(const Type& newType);
		const Type& GetType() const;
		OM_ALLOCATION(FollowAction);

		Type type;
	};

	// A fade between two points of the music (0x28 bytes)
	class Fade
	{
	public:
		// 0x105D7340 / 0x105D7330
		void SetStart(const Time& newStart);
		const Time& GetStart() const;
		// 0x105D7380 / 0x105D7370
		void SetLength(const Time& newLength);
		const Time& GetLength() const;
		OM_ALLOCATION(Fade);

		Time start;
		Time length;
	};
}

#endif
