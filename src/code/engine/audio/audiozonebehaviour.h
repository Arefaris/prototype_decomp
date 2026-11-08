// engine::AudioZoneBehaviour (RTTI and reflection name; base engine::Behaviour): a box in the world that tells the sound
// zone manager when the audio listener is inside ("zoneName", "reverbName", "ambienceName", "mixName", "volume"). The
// zone is added to the manager when the listener enters the volume and removed again when it leaves. Unit
// 0x1093C7C0 - 0x1093CE00 (no assert path; the directory and file name are guesses). The reflected names are
// original; the rest is guessed.
#ifndef ENGINE_AUDIO_AUDIOZONEBEHAVIOUR_H
#define ENGINE_AUDIO_AUDIOZONEBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"
#include "code/engine/trigger/volume.h"

namespace engine
{
	class AudioZoneBehaviour : public Behaviour
	{
	public:
		// 0x1093C920 and 0x1093CA00 (the second one takes the volume)
		explicit AudioZoneBehaviour(GameObject* newOwner);
		AudioZoneBehaviour(GameObject* newOwner, trigger::OBBVolume* newVolume);
		// 0x1093CAD0 (deleting destructor 0x1093CC70)
		virtual ~AudioZoneBehaviour();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 0 (0x1093C800)
		virtual void Slot0();
		// vftable slot 1 (0x1093CA80): sets the volume up
		virtual void Slot1();
		// vftable slot 4 (0x1093CAF0): adds or removes the zone when the listener enters or leaves the volume
		virtual void Update(float dt, unsigned short mask);
		// vftable slots 5 and 6 (0x1093C9B0 and 0x1093C9A0): do nothing
		virtual void OnPostedMessage(Message* message);
		virtual void OnMessage(Message* message);

		int unknownC;
		__declspec(align(8)) core::Name<core::CaseSensitiveKey> zoneName;  // +0x10
		trigger::OBBVolume* volume;  // +0x18
		// The engine's names are 8-byte aligned
		int unknown1C;
		core::Name<core::CaseSensitiveKey> reverbName;  // +0x20
		core::Name<core::CaseSensitiveKey> ambienceName;  // +0x28
		core::Name<core::CaseSensitiveKey> mixName;  // +0x30
		bool inside;  // +0x38
	};
}

#endif
