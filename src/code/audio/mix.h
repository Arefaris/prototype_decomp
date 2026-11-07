// The audio library's mixer (RTTI: audio::Mix and audio::MixStrip, om entities whose reflection is in mix.cpp). Only
// the reflected accessors are declared.
#ifndef AUDIO_MIX_H
#define AUDIO_MIX_H

#include "code/om/delegate.h"
#include "code/om/entity.h"
#include "code/om/name.h"

namespace audio
{
	class Mix;

	// A strip of the mixer (RTTI: audio::MixStrip, a class without virtual functions, 0x40 bytes). The members are named
	// after the properties the reflection registers them under.
	class MixStrip
	{
	public:

		// 0x105CFCC0 (moves the strip within the mixer's tree)
		void SetName(const om::Name<om::CaseSensitive64BitKey>& newName);
		// 0x105C25C0
		const om::Name<om::CaseSensitive64BitKey>& GetName() const;
		// 0x105C25D0 / 0x105CC070
		float GetVolume() const;
		void SetVolume(float newVolume);
		// 0x105C25E0 / 0x105CC080
		float GetPitch() const;
		void SetPitch(float newPitch);
		// 0x105C25F0 / 0x105CE090
		bool GetMuted() const;
		void SetMuted(bool newMuted);
		// 0x105CC090 / 0x105CE070
		bool GetSolo() const;
		void SetSolo(bool newSolo);
		// 0x105C2600 / 0x105CC0A0
		float GetReverb1() const;
		void SetReverb1(float newReverb1);
		// 0x105C2610 / 0x105CC0B0
		float GetSub() const;
		void SetSub(float newSub);
		// 0x105C2620 / 0x105CC0C0
		bool GetPause() const;
		void SetPause(bool newPause);

		om::GarbageList children;  // 0: the list the strip's destructor deletes
		Mix* mix;  // 8
		int unknownC;
		om::ClassName name;  // 0x10
		float volume;  // 0x18
		float pitch;  // 0x1C
		float reverb1;  // 0x20
		float sub;  // 0x24
		bool muted;  // 0x28
		bool solo;
		bool pause;
		char unknown2B[0x15];
	};

	// An entity of the mixer: a set of strips (0x48 bytes)
	class Mix : public om::Entity
	{
	public:
		// 0x105CCB70
		explicit Mix(const om::ClassName& newName);
		// Slot 0 (0x105D0C90 is the body, the deleting destructor 0x105D0F40)
		virtual ~Mix();
		// Slots 3 to 7 and 9 (0x105D0CB0, 0x105CEF50, 0x105CF7F0, 0x105D0E50, 0x105CF060, 0x105CDFF0)
		virtual bool Slot3(void* argument);
		virtual void Slot4(void* argument);
		virtual bool Slot5(void* argument);
		virtual bool Slot6(void* argument);
		virtual bool Slot7(void* argument);
		virtual om::EntityTypeBase* GetEntityType();
		OM_ENTITY_ALLOCATION(Mix);

		// 0x105CC0D0 / 0x105CC0E0 and 0x105CC0F0 / 0x105CC100 (the times are milliseconds)
		unsigned int GetFadeInTime() const;
		void SetFadeInTime(unsigned int newFadeInTime);
		unsigned int GetFadeOutTime() const;
		void SetFadeOutTime(unsigned int newFadeOutTime);

		om::GarbageList strips;  // 0x20: the list of the strips
		unsigned int fadeInTime;  // 0x28
		unsigned int fadeOutTime;  // 0x2C
		om::TreeHead stripsByName;  // 0x30
	};
}

#endif
