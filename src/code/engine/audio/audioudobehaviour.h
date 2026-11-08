// engine::AudioUDOBehaviour (RTTI and reflection name; base engine::Behaviour): the behaviour that gives a game object
// the voice of a character class. It keeps the audio object made for the class named by the reflected member
// "characterClass" and, every update, sends the loudness of the voice to its owner as an AudioPeakAmplitudeMessage
// (the jaw flap behaviour listens). Unit 0x1087D3E0 - 0x1087D9A0 (no assert path; the file name is a guess). Member
// and method names other than the reflected one are guesses.
#ifndef ENGINE_AUDIO_AUDIOUDOBEHAVIOUR_H
#define ENGINE_AUDIO_AUDIOUDOBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/audio/audiomessage.h"
#include "code/engine/audio/audioplayer.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/om/allocation.h"

namespace engine
{
	// The audio object of a character class (0x68 bytes, made by the audio system's unit 0x10859720; its second slot
	// holds the player whose amplitude is read)
	class __declspec(align(8)) AudioObject
	{
	public:
		// 0x10859720: for the class of that name, owned by that game object
		AudioObject(int mode, const core::Name<core::CaseSensitiveKey>& newName, GameObject* newOwner);
		// 0x108588D0
		~AudioObject();
		// 0x108589A0: the part that holds the player (null when it has none)
		struct AudioObjectPart* GetPart();

		OM_ALLOCATION(AudioObject);

		unsigned char unknown0[0x68];
	};

	// The part of an audio object that holds the player at +0x18
	struct AudioObjectPart
	{
		unsigned char unknown0[0x18];
		AudioPlayer* player;
	};

	// The owner of an audio object (the template instance the behaviour keeps out of line: constructor 0x1087D450, the
	// getter 0x1087D460, the test 0x1087D470, the destructor 0x1087D640; the assignment 0x1087D660 is the engine's; names guessed)
	template<class T> class OwnedPointer
	{
	public:
		OwnedPointer() : object(0)
		{
		}
		~OwnedPointer()
		{
			if (object != 0)
			{
				delete object;
			}
		}
		T* Get() const
		{
			return object;
		}
		bool IsSet() const
		{
			return object != 0;
		}
		T* operator=(T* newObject)
		{
			T* old = object;
			if (old != newObject)
			{
				if (old != 0)
				{
					delete old;
				}
				object = newObject;
				return newObject;
			}
			return old;
		}

		T* object;
	};

	// RTTI: engine::AudioPeakAmplitudeMessage (type 0x15, id 2): the loudness of a voice at this moment
	class AudioPeakAmplitudeMessage : public AudioMessage
	{
	public:
		// 0x1087D520 (the out-of-line copy of the constructor; the deleting destructor is 0x1087D6A0)
		AudioPeakAmplitudeMessage(const AudioName& newJoint, float newAmplitude);

		AudioName joint;
		float amplitude;
	};

	class AudioUDOBehaviour : public Behaviour
	{
	public:
		// 0x1087D770
		explicit AudioUDOBehaviour(GameObject* newOwner);
		// The destructor is the compiler's (0x1087D7C0, the deleting destructor 0x1087D910)

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x1087D950): makes the audio object again for the same class
		virtual void Slot1();
		// vftable slot 4 (0x1087D5B0): sends the loudness of the voice
		virtual void Update(float dt, unsigned short mask);
		// vftable slot 6 (0x1087D420): hands an audio message of id 1 the behaviour to apply
		virtual void OnMessage(Message* message);

		// 0x1087D7F0: makes the audio object for that class unless it is the one it already has
		void SetCharacterClass(const core::Name<core::CaseSensitiveKey>& newClass);

		__declspec(align(8)) core::Name<core::CaseSensitiveKey> characterClass;  // +0x10
		OwnedPointer<AudioObject> audioObject;
	};
}

#endif
