#include "code/proto/messages/movementmessages.h"
#include "code/proto/fightitems/ai/aihelpers.h"
#include "code/proto/fightitems/ai/aimessages.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectmessages.h"

namespace choreo
{
	// 0x10D94FF8: -1.0f in the pooled constants
	extern const float gMinusOne;
}

namespace proto
{
	// The message that names the target to take (type 0x20, id 2)
	class SetTargetMessage : public TargetMessage
	{
	public:
		explicit SetTargetMessage(engine::GameObjectHandle newTarget) : TargetMessage(2), target(newTarget)
		{
		}
		virtual ~SetTargetMessage()
		{
		}

		engine::GameObjectHandle target;  // +0xC
	};

	// More helpers that send messages to an object (unit 0x103B81A0 - 0x103BEA10, no assert path; the file name is a
	// guess)

	// FUNCTION: ENGINE 0x103B81A0
	void Unknown103B81A0(engine::GameObject* object)
	{
		engine::CharacterQueryIntentionMessage query;
		object->SendMessage(&query);
		if (query.intention != 0)
		{
			query.intention->Reset();
		}
		ResetAIFrameInfoMovementMessage message;
		object->SendMessage(&message);
	}

	// 0x103B83D0: sends the object along a flight path (name guess)
	struct FlyPathParams
	{
		float speed;
		bool unknown4;
		bool unknown5;
	};

	// FUNCTION: ENGINE 0x103B83D0
	void SendGotoFlyPath(engine::GameObject* object, void* path, const FlyPathParams* params)
	{
		GotoFlyPathMovementMessage message(params->speed, params->unknown4, params->unknown5, path);
		object->SendMessage(&message);
	}

	// FUNCTION: ENGINE 0x103B8690
	void SendSetTarget(engine::GameObject* object, engine::GameObjectHandle target)
	{
		SetTargetMessage message(target);
		object->SendMessage(&message);
	}

	// FUNCTION: ENGINE 0x103B8860
	// NONMATCHING: the engine selects the value on the x87 stack (fld1 or the pooled constant), ours through SSE (61.7 %)
#ifdef NONMATCHING
	void SendButton19(engine::GameObject* object, bool pressed)
	{
		engine::CharacterQueryIntentionMessage query;
		object->SendMessage(&query);
		engine::CharacterIntentionButton* button = query.intention->GetButtonOther(0x13);
		button->Press(pressed ? 1.0f : choreo::gMinusOne);
	}
#endif

	// FUNCTION: ENGINE 0x103B8C10
	void SendButton6(engine::GameObject* object)
	{
		engine::CharacterQueryIntentionMessage query;
		object->SendMessage(&query);
		query.intention->GetButtonOther(6)->Press(1.0f);
	}
}
