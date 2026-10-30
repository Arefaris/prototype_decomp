// The audio library's mixer (RTTI: audio::Mix and audio::MixStrip, om entities whose reflection is in mix.cpp). Only
// the reflected accessors are declared.
#ifndef AUDIO_MIX_H
#define AUDIO_MIX_H

#include "code/om/entity.h"
#include "code/om/name.h"

namespace audio
{
	class MixStrip
	{
	public:
		virtual ~MixStrip();

		void SetName(const om::Name<om::CaseSensitive64BitKey>& name);
		const om::Name<om::CaseSensitive64BitKey>& GetName() const;
		void SetGain(float gain);
		float GetGain() const;
		void SetMute(bool mute);
		bool GetMute() const;
	};

	// An entity of the mixer: a set of strips (0x48 bytes)
	class Mix : public om::Entity
	{
	public:
		// 0x105CCB70
		explicit Mix(const om::ClassName& newName);
		virtual ~Mix();
		OM_ENTITY_ALLOCATION(Mix);

		void SetSelected(unsigned int index);
		unsigned int GetSelected() const;

		char unknown20[0x28];
	};
}

#endif
