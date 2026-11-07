// engine::AudioUDOBehaviour: see the header.
#include "code/engine/audio/audioudobehaviour.h"
#include "code/engine/gameobject/gameobject.h"

namespace engine
{
#define ENGINE_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	extern AudioName gAmplitude;

	// 0x1087D570 (constructor, kept copy) and 0x1087D580 (IsDerived): the caster the class meta type carries
	// FUNCTION: ENGINE 0x1087D570
	// FUNCTION: ENGINE 0x1087D580
	template struct content::BaseClassCasterImpl<Behaviour, AudioUDOBehaviour>;

	// The kept out-of-line members of the owner of the audio object
	// FUNCTION: ENGINE 0x1087D450
	// FUNCTION: ENGINE 0x1087D460
	// FUNCTION: ENGINE 0x1087D470
	// FUNCTION: ENGINE 0x1087D640
	template OwnedPointer<AudioObject>::OwnedPointer();
	template AudioObject* OwnedPointer<AudioObject>::Get() const;
	template bool OwnedPointer<AudioObject>::IsSet() const;
	template OwnedPointer<AudioObject>::~OwnedPointer();

	// FUNCTION: ENGINE 0x1087D3E0
	content::ClassInfo* AudioUDOBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::AudioUDOBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1087D4C0
	// FUNCTION: ENGINE 0x1087D6C0
	content::MemberList* AudioUDOBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Behaviour>();
		static content::BaseClassCasterImpl<Behaviour, AudioUDOBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<AudioUDOBehaviour>(true, true, "pn"),
				ENGINE_NAME_OFFSET(AudioUDOBehaviour, characterClass), "characterClass" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1087D770
	AudioUDOBehaviour::AudioUDOBehaviour(GameObject* newOwner) :
		Behaviour(newOwner)
	{
		Listen(0x15, true);
		Listen(0x14, true);
		Listen2(4, true);
	}

	// FUNCTION: ENGINE 0x1087D7C0
	// The compiler's destructor of AudioUDOBehaviour (the class declares none)

	// FUNCTION: ENGINE 0x1087D950
	void AudioUDOBehaviour::Slot1()
	{
		SetCharacterClass(characterClass);
	}

	// FUNCTION: ENGINE 0x1087D5B0
	// NONMATCHING: the engine expands the message constructor in place (the compiler keeps it out of line here), 69.2 %
#ifdef NONMATCHING
	void AudioUDOBehaviour::Update(float dt, unsigned short mask)
	{
		AudioObjectPart* part = audioObject.Get()->GetPart();
		if (part != 0 && part->player != 0)
		{
			float amplitude;
			if (part->player->Slot8(gAmplitude, &amplitude))
			{
				AudioName joint("jaw", 1);
				AudioPeakAmplitudeMessage message(joint, amplitude);
				owner->SendMessage(&message);
			}
		}
	}
#endif

	// FUNCTION: ENGINE 0x1087D420
	void AudioUDOBehaviour::OnMessage(Message* message)
	{
		if (message->type == 0x15 && message->id == 1)
		{
			static_cast<AudioEmitterMessage*>(message)->Apply((AudioEmitter*)this);
		}
	}

	// FUNCTION: ENGINE 0x1087D7F0
	void AudioUDOBehaviour::SetCharacterClass(const core::Name<core::CaseSensitiveKey>& newClass)
	{
		if (!audioObject.IsSet() || !(characterClass == newClass))
		{
			audioObject = 0;
			characterClass = newClass;
			audioObject = new AudioObject(0, characterClass, owner);
		}
	}
}

