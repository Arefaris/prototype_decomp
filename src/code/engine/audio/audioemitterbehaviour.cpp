#include "code/engine/audio/audioemitterbehaviour.h"
#include "code/engine/audio/audioglobalsettings.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/om/dynamicproperty.h"
#include "code/om/vector.h"

namespace engine
{
	// The name an emitter's sound list starts with (0x11276940)
	extern AudioName gUnknownName11276940;

	namespace driving
	{
		extern const float gOne;
	}

	// The engine's own instance of the check the tree walks make (audiosoundlist.cpp has its copy)
	template<class T> bool IsPresent(T* item);

	template<class T> inline T* NodeToItem(om::TreeNode* node)
	{
		if (node != 0)
		{
			return (T*)((char*)node - 0x8c);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1093C290
	content::ClassInfo* AudioEmitterBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::AudioEmitterBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1093C5F0
	content::MemberList* AudioEmitterBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Behaviour>();
		static content::BaseClassCasterImpl<Behaviour, AudioEmitterBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1093C3C0
	void AudioSound::SetSpatial(const math::Vector* newPosition, const math::Vector* newVelocity)
	{
		positionProperty->Set(om::Vector(newPosition->x, newPosition->y, newPosition->z));
		velocityProperty->Set(om::Vector(newVelocity->x, newVelocity->y, newVelocity->z));
	}

	// FUNCTION: ENGINE 0x1093C2D0
	void AudioEmitterBehaviour::Initialize()
	{
		position.Set(1e10f, 1e10f, 1e10f);
		velocity.Set(0.0f, 0.0f, 0.0f);
		Listen(0x15, true);
		Listen(0x14, true);
		Listen(2, true);
		AudioManager::Get()->AddUpdatable((AudioUpdatable*)this);
	}

	// FUNCTION: ENGINE 0x1093C4F0
	AudioEmitterBehaviour::AudioEmitterBehaviour(GameObject* newOwner) : Behaviour(newOwner), sounds(gUnknownName11276940)
	{
		Initialize();
	}

	// FUNCTION: ENGINE 0x1093C330
	AudioEmitterBehaviour::~AudioEmitterBehaviour()
	{
		AudioManager::Get()->RemoveUpdatable((AudioUpdatable*)this);
	}

	// FUNCTION: ENGINE 0x1093C570
	void AudioEmitterBehaviour::Slot1()
	{
		const math::Matrix& matrix = owner->transform->Get();
		math::Vector translation(matrix.m[3][0], matrix.m[3][1], matrix.m[3][2]);
		position.x = translation.x;
		position.y = translation.y;
		position.z = translation.z;
	}

	// FUNCTION: ENGINE 0x1093C360
	void AudioEmitterBehaviour::OnMessage(Message* message)
	{
		switch (message->type)
		{
		case 0x15:
			if (message->id == 0)
			{
				static_cast<AudioEmitterMessage*>(message)->Apply((AudioEmitter*)this);
			}
			break;
		case 2:
			sounds.RemoveAll(1);
			position.x = 1e10f;
			position.y = 1e10f;
			position.z = 1e10f;
			velocity.x = 0.0f;
			velocity.y = 0.0f;
			velocity.z = 0.0f;
			break;
		}
	}

	// FUNCTION: ENGINE 0x1093C5A0
	void AudioEmitterBehaviour::UpdateSound(AudioSound* sound, float distanceSquared)
	{
		float volume = 0.0f;
		if (sound->bank->unknownE)
		{
			sound->SetSpatial(&position, &velocity);
			float distanceFactor = sound->distanceProperty->GetValue();
			volume = distanceSquared / (distanceFactor * distanceFactor);
		}
		sound->volume = volume;
	}

	// FUNCTION: ENGINE 0x1093C650
	// NONMATCHING: the engine keeps the two node conversions of the walk apart (a branch each) and the compiler merges the zeros, 57.6 %
#ifdef NONMATCHING
	void AudioEmitterBehaviour::UpdateSounds()
	{
		float x = position.x - gAudioListener->x;
		float y = position.y - gAudioListener->y;
		float z = position.z - gAudioListener->z;
		float distanceSquared = z * z + y * y + x * x;
		AudioSound* current = NodeToItem<AudioSound>(sounds.tree.First());
		AudioSound* following = 0;
		if (current != 0)
		{
			following = NodeToItem<AudioSound>(sounds.tree.Next(&current->node));
		}
		if (IsPresent(current))
		{
			do
			{
				UpdateSound(current, distanceSquared);
				AudioSound* previous = following;
				if (following != 0)
				{
					following = NodeToItem<AudioSound>(sounds.tree.Next(&following->node));
				}
				else
				{
					following = 0;
				}
				current = previous;
			}
			while (IsPresent(current));
		}
	}
#endif

	// FUNCTION: ENGINE 0x1093C730
	// NONMATCHING: the engine loads the owner's position before the time step test and takes the differences first (11.9 %)
#ifdef NONMATCHING
	void AudioEmitterBehaviour::UpdateAudio(float dt)
	{
		if (owner->transform != 0)
		{
			math::Vector newPosition;
			owner->transform->value.GetTranslation(newPosition);
			if (dt > 1e-5f)
			{
				float inverse = driving::gOne / dt;
				velocity.Sub(newPosition, position);
				velocity.Scale(inverse);
			}
			position.x = newPosition.x;
			position.y = newPosition.y;
			position.z = newPosition.z;
			UpdateSounds();
		}
	}
#endif
}
