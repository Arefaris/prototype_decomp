#include "code/engine/audio/audiozonebehaviour.h"
#include "code/engine/audio/audiomanager.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/ravenphysics/collision/collisionobject.h"
#include "code/ravenphysics/physicsobject.h"

namespace engine
{
#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define ENGINE_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x1093C7C0
	content::ClassInfo* AudioZoneBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::AudioZoneBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1093C800
	void AudioZoneBehaviour::Slot0()
	{
		Listen2(4, true);
	}

	// FUNCTION: ENGINE 0x1093C920
	AudioZoneBehaviour::AudioZoneBehaviour(GameObject* newOwner)
		: Behaviour(newOwner), zoneName("", 1), volume(0), reverbName("", 1), ambienceName("", 1), mixName("", 1), inside(false)
	{
		Listen(0x15, true);
		Listen2(4, true);
	}

	// FUNCTION: ENGINE 0x1093CA00
	AudioZoneBehaviour::AudioZoneBehaviour(GameObject* newOwner, trigger::OBBVolume* newVolume)
		: Behaviour(newOwner), zoneName("", 1), volume(newVolume), reverbName("", 1), ambienceName("", 1), mixName("", 1), inside(false)
	{
		Listen(0x15, true);
		Listen2(4, true);
	}

	// FUNCTION: ENGINE 0x1093CA80
	void AudioZoneBehaviour::Slot1()
	{
		volume->SetKind(0);
		volume->SetOwner(GetHandle(owner));
		volume->SetObjectTransform(owner->transform->value);
		volume->Slot4();
	}

	// FUNCTION: ENGINE 0x1093CAD0
	AudioZoneBehaviour::~AudioZoneBehaviour()
	{
		delete volume;
	}

	// FUNCTION: ENGINE 0x1093CAF0
	void AudioZoneBehaviour::Update(float dt, unsigned short mask)
	{
		if (volume != 0 && volume->GetHandle()->IsValid())
		{
			math::Vector position;
			gSoundZoneManager->GetListenerPosition(&position);
			// The physics object of a trigger volume is a trigger object
			const math::AABB& bounds = ((ravenphysics::TriggerObject*)volume->GetHandle()->GetObjectUnchecked())->volume->bounds;
			bool contains = position.x >= bounds.min.x && bounds.max.x >= position.x
				&& position.y >= bounds.min.y && bounds.max.y >= position.y
				&& position.z >= bounds.min.z && bounds.max.z >= position.z;
			if (contains != inside)
			{
				if (contains)
				{
					// The fifth argument is the volume's collision volume (the track's zone passes none)
					int boundary = (int)((ravenphysics::TriggerObject*)volume->GetHandle()->GetObjectUnchecked())->volume;
					SoundZoneManager* manager = gSoundZoneManager;
					manager->AddZone(zoneName, reverbName, ambienceName, mixName, boundary);
				}
				else
				{
					SoundZoneManager* manager = gSoundZoneManager;
					manager->RemoveZone(zoneName);
				}
				inside = contains;
			}
		}
	}

	// FUNCTION: ENGINE 0x1093C9B0
	void AudioZoneBehaviour::OnPostedMessage(Message* message)
	{
	}

	// FUNCTION: ENGINE 0x1093C9A0
	void AudioZoneBehaviour::OnMessage(Message* message)
	{
	}

	// FUNCTION: ENGINE 0x1093CCE0
	content::MemberList* AudioZoneBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Behaviour>();
		static content::BaseClassCasterImpl<Behaviour, AudioZoneBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberNameMetaType<AudioZoneBehaviour, 0>(true, true, "pn"), ENGINE_NAME_OFFSET(AudioZoneBehaviour, zoneName), "zoneName" },
			{ content::GetMemberNameMetaType<AudioZoneBehaviour, 1>(true, true, "pn"), ENGINE_NAME_OFFSET(AudioZoneBehaviour, reverbName), "reverbName" },
			{ content::GetMemberNameMetaType<AudioZoneBehaviour, 2>(true, true, "pn"), ENGINE_NAME_OFFSET(AudioZoneBehaviour, ambienceName), "ambienceName" },
			{ content::GetMemberNameMetaType<AudioZoneBehaviour, 3>(true, true, "pn"), ENGINE_NAME_OFFSET(AudioZoneBehaviour, mixName), "mixName" },
			{ content::GetObjectMetaType<trigger::OBBVolume>("pnr"), ENGINE_OFFSET(AudioZoneBehaviour, volume), "volume" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1093C810
// FUNCTION: ENGINE 0x1093C850
// FUNCTION: ENGINE 0x1093C890
// FUNCTION: ENGINE 0x1093C8D0
// FUNCTION: ENGINE 0x1093C910
// FUNCTION: ENGINE 0x1093C9C0
// FUNCTION: ENGINE 0x1093C9D0
// FUNCTION: ENGINE 0x1093CC40
// FUNCTION: ENGINE 0x1093CC50
// FUNCTION: ENGINE 0x1093CC70
// FUNCTION: ENGINE 0x1093CC90
