// The audio system's dialogue resolvers (unit 0x1049B110 - 0x1049C2D0).
#include "code/proto/soundresolvers.h"
#include "code/engine/controller/inputsystem.h"
#include "code/engine/frontend/fesubtitle.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/proto/fightitems/ai/aicodemessages.h"
#include "code/proto/fightitems/motion/motionactionmessages.h"
#include "code/proto/messages/airequestmessages.h"
#include "code/engine/scenariomessage.h"
#include "code/om/string.h"

namespace engine
{
	namespace driving
	{
		extern const float gOne;
	}
	// 0x1126BE78: the channel of the scenario's messages (incidentnames.cpp)
	extern MessageListeners gScenario84;
	// 0x1126BFF8: the name "default_text"
	extern core::Name<core::CaseSensitiveKey> gDefaultText;
	// 0x10864A00 (another unit)
	core::Name<core::CaseSensitiveKey> GetLanguageName();
	// The names the dialogue tells its speaker by (incidentnames.cpp, mixnames.cpp, charactertypenames.cpp)
	extern core::Name<core::CaseSensitiveKey> gAttacker2;
	extern core::Name<core::CaseSensitiveKey> gVehicle;
	extern core::Name<core::CaseSensitiveKey> gDriverPlayer;
	extern core::Name<core::CaseSensitiveKey> gNoDriver;
}

namespace proto
{
	// 0x10575B30 (another unit): the game mode word of the singleton
	int* GetGameMode();
	// 0x1126BE64: the subtitle manager the dialogue is shown on (name guess)
	extern engine::FESubtitle* gDialogueSubtitles;

	// 0x1126E40C: the handles of the players
	extern engine::GameObjectHandle gPlayerHandles[];
	// 0x103C01F0 (another unit)
	engine::GameObject* GetLinkedObject(engine::GameObject* object);

	// A dialogue the audio system plays (layout from the resolver's slots; names guessed)
	struct DialogueLine
	{
		unsigned char unknown0[0x18];
		core::Name<core::CaseSensitiveKey> role;  // +0x18: how the speaker is named
		unsigned char unknown20[0x10];
		engine::GameObjectHandle speaker;  // +0x30
		unsigned char unknown34[0xc];
		om::String text;  // +0x40
	};

	// FUNCTION: ENGINE 0x1049E0C0
	void SoundDialogueResolver::Update(int first)
	{
		DialogueLine* line = (DialogueLine*)first;
		if (line->role == engine::gAttacker2)
		{
			if (line->speaker.Get() != 0)
			{
				GetDamageOriginatorDamageMessage message;
				line->speaker.Get()->SendMessage(&message);
				if (message.originator.IsValid())
				{
					line->speaker = message.originator;
					line->role = core::Name<core::CaseSensitiveKey>("", 0);
				}
			}
		}
		else if (line->role == engine::gVehicle)
		{
			if (line->speaker.Exists())
			{
				line->role = core::Name<core::CaseSensitiveKey>("", 0);
				engine::GameObject* linked = GetLinkedObject(line->speaker.Get());
				if (linked != 0)
				{
					line->speaker = engine::GetHandle(linked);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x1049BB30
	int SoundDialogueResolver::Slot2(int first, int second, int third, int fourth)
	{
		if (*GetGameMode() != 0)
		{
			return 0;
		}
		return gDialogueSubtitles->Add((const char*)third, engine::gDefaultText,
			*(const core::Name<core::CaseSensitiveKey>*)second, fourth);
	}

	// FUNCTION: ENGINE 0x1049BB70
	void SoundDialogueResolver::Slot3(int first)
	{
		gDialogueSubtitles->Stop(first);
	}

	// FUNCTION: ENGINE 0x1049CD70
	core::Name<core::CaseSensitiveKey> SoundDialogueResolver::GetLanguageName()
	{
		return engine::GetLanguageName();
	}

	// FUNCTION: ENGINE 0x1049CD90
	void SoundDialogueResolver::Slot7(int first, int second)
	{
		bool hasText;
		{
			om::String empty("", 0);
			DialogueLine* line = (DialogueLine*)first;
			hasText = line->text != empty;
		}
		if (hasText)
		{
			DialogueLine* line = (DialogueLine*)first;
			core::Name<core::CaseSensitiveKey> name(line->text.GetText(), 1);
			engine::StringMessage message(name);
			message.handles[0] = line->speaker;
			engine::SendMessage(&message, &engine::gScenario84);
		}
	}

	// FUNCTION: ENGINE 0x1049E2C0
	// NONMATCHING: the engine keeps the table and the halves of the handle in registers across the calls and looks the object up again from them, 21 %
#ifdef NONMATCHING
	bool SoundDialogueResolver::Slot8(int first)
	{
		engine::GameObjectHandle handle(((engine::GameObjectHandle*)first)->index, ((engine::GameObjectHandle*)first)->serial);
		if (handle.Get() != 0)
		{
			engine::GameObjectHandle player;
			if (engine::controller::InputSystem::Get()->slotCount > 0)
			{
				player = gPlayerHandles[0];
			}
			engine::GameObject* playerObject = player.Get();
			if (playerObject != 0)
			{
				PlayerSeenPerceptionMessage message((int)playerObject, engine::driving::gOne);
				handle.Get()->SendMessage(&message);
				return message.unknown14;
			}
		}
		return false;
	}
#endif

	// FUNCTION: ENGINE 0x1049E3F0
	// NONMATCHING: the engine keeps the table and the halves of the handle in registers across the calls and looks the object up again from them, 22 %
#ifdef NONMATCHING
	bool SoundDialogueResolver::Slot9(int first)
	{
		engine::GameObjectHandle handle(((engine::GameObjectHandle*)first)->index, ((engine::GameObjectHandle*)first)->serial);
		if (handle.Get() != 0)
		{
			GetStateStateChangeMessage message;
			if (handle.Get()->SendMessage(&message) == true)
			{
				if (engine::gDriverPlayer == message.state || engine::gNoDriver == message.state)
				{
					return false;
				}
			}
		}
		return true;
	}
#endif

	// FUNCTION: ENGINE 0x1049B310
	SoundDialogueResolver::SoundDialogueResolver()
	{
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1049B110
// FUNCTION: ENGINE 0x1049B120
// FUNCTION: ENGINE 0x1049B130
// FUNCTION: ENGINE 0x1049B140
// FUNCTION: ENGINE 0x1049B150
// FUNCTION: ENGINE 0x1049B160
// FUNCTION: ENGINE 0x1049B170
// FUNCTION: ENGINE 0x1049B180
// FUNCTION: ENGINE 0x1049B320
// FUNCTION: ENGINE 0x1049C1E0
// FUNCTION: ENGINE 0x1049C2D0
