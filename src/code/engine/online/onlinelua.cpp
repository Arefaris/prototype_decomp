// The online scripting helpers (unit 0x107F27E0 - 0x107F2970; no assert path, the file name and every name here are
// guesses): which player controls a character, registered for the scripts as online_DeterminePlayerIndex.
#include "code/engine/controller/inputsystem.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/message.h"
#include "code/engine/scriptcontext.h"

namespace engine
{
	// engine::CharacterQueryMessage (RTTI): the questions a character's behaviours answer (message type 0x10)
	class CharacterQueryMessage : public IntrusiveMessage
	{
	public:
		explicit CharacterQueryMessage(short newId) : IntrusiveMessage(0x10, newId)
		{
		}
	};

	// engine::CharacterQueryPlayerControlStateMessage (RTTI): the answer points at the controlling player's index
	class CharacterQueryPlayerControlStateMessage : public CharacterQueryMessage
	{
	public:
		CharacterQueryPlayerControlStateMessage() : CharacterQueryMessage(1)
		{
			playerIndex = 0;
		}

		const int* playerIndex;
	};

	// The owner the unit's script functions are registered under
	// GLOBAL: ENGINE 0x112838A8
	char gOnlineScriptOwner;

	// FUNCTION: ENGINE 0x107F27E0
	void UnregisterOnlineScript()
	{
		ScriptContext* context = GetScriptContext();
		context->Unregister(&gOnlineScriptOwner);
	}

	// FUNCTION: ENGINE 0x107F2800
	int GetControllingPlayer(GameObject* object)
	{
		CharacterQueryPlayerControlStateMessage message;
		object->SendMessage(&message);
		if (message.playerIndex != 0)
		{
			return *message.playerIndex;
		}
		return -1;
	}

	// FUNCTION: ENGINE 0x107F2850
	// EQUIVALENT: the engine sets the result with `sete al` in the register it masked; ours clears another one first
	bool IsLocalSlot(int slot)
	{
		return controller::InputSystem::IsLocal(controller::InputSystem::Get()->slots[slot].id);
	}

	// FUNCTION: ENGINE 0x107F2870
	bool IsLocallyControlled(GameObject* object)
	{
		return IsLocalSlot(GetControllingPlayer(object));
	}

	// FUNCTION: ENGINE 0x107F2890
	// EQUIVALENT: the engine compares the handle's serial a second time for Get after IsValid (see poimanager.cpp's
	// WorldStreamerPOI::GetPosition) and returns the handle in a local; ours folds the check and reuses the argument
	int DeterminePlayerIndex(LuaGOH object)
	{
		GameObjectHandle handle = DeserializeHandle(object);
		if (handle.IsValid())
		{
			return GetControllingPlayer(handle.Get());
		}
		return -1;
	}

	// FUNCTION: ENGINE 0x107F28F0
	// EQUIVALENT: the second serial compare for Get after IsValid, as in DeterminePlayerIndex
	bool IsLocallyControlled(GameObjectHandle handle)
	{
		if (handle.IsValid())
		{
			return IsLocallyControlled(handle.Get());
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107F2940
	void RegisterOnlineScript()
	{
		ScriptContext* context = GetScriptContext();
		context->SetOwner(&gOnlineScriptOwner);
		context->Register("online_DeterminePlayerIndex", DeterminePlayerIndex);
		context->ClearOwner();
	}
}
