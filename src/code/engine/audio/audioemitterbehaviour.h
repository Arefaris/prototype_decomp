// engine::AudioEmitterBehaviour (RTTI and reflection name; base engine::Behaviour): a game object that plays sounds.
// It keeps the sounds it plays by name (AudioSoundList), follows the position of its owner, and every audio frame
// hands each of its sounds the position, the velocity and the distance-scaled volume. The audio manager's list of
// the objects that are told the time step holds it through the node at +0x50 (the AudioUpdatable view of
// audiomanager.h; vftable slot 8 is the time step). Unit 0x1093C290 - 0x1093C7B0 (no assert path; the directory and
// file name are guesses). The reflected name is original; the rest is guessed.
#ifndef ENGINE_AUDIO_AUDIOEMITTERBEHAVIOUR_H
#define ENGINE_AUDIO_AUDIOEMITTERBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/audio/audiomanager.h"
#include "code/engine/audio/audiomessage.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"
#include "code/math/vector.h"

namespace engine
{
	class AudioEmitterBehaviour : public Behaviour
	{
	public:
		// 0x1093C4F0 (the engine keeps a second copy of the same code at 0x1093C540)
		explicit AudioEmitterBehaviour(GameObject* newOwner);
		// 0x1093C330 (deleting destructor 0x1093C520)
		virtual ~AudioEmitterBehaviour();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x1093C570): takes the owner's position
		virtual void Slot1();
		// vftable slot 6 (0x1093C360): forgets the sounds when the game object is reset, plays the sounds of a trigger
		virtual void OnMessage(Message* message);
		// vftable slot 8 (0x1093C730): works out the velocity from the movement of the owner and updates the sounds
		virtual void UpdateAudio(float dt);

		// 0x1093C2D0: puts the emitter far away and still, and enters it in the manager's list
		void Initialize();
		// 0x1093C650: hands every sound the position and the volume for its distance from the listener
		void UpdateSounds();
		// 0x1093C5A0: hands one sound the position and the velocity, and the volume for the squared distance
		void UpdateSound(AudioSound* sound, float distanceSquared);

		AudioSoundList sounds;  // +0x10
		math::Vector position;  // +0x38
		math::Vector velocity;  // +0x44
		AudioUpdatableLink link;  // +0x50
	};
}

#endif
