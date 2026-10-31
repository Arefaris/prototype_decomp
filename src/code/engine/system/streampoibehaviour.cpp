#include "code/engine/system/streampoibehaviour.h"
#include "code/engine/system/poimanager.hpp"

namespace engine
{
	// FUNCTION: ENGINE 0x108982B0
	StreamPOIBehaviour::StreamPOIBehaviour(GameObject* newOwner) : Behaviour(newOwner)
	{
		playerIndex = -1;
		Listen(0x18, true);
	}

	// FUNCTION: ENGINE 0x108982E0
	StreamPOIBehaviour::~StreamPOIBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x108982F0
	void StreamPOIBehaviour::Slot1()
	{
		Listen2(4, true);
	}

	// FUNCTION: ENGINE 0x10898300
	void StreamPOIBehaviour::Update(float dt, unsigned short mask)
	{
		if (playerIndex >= 0)
		{
			math::Matrix& transform = GetTransformAttribute()->Get();
			POIManager& manager = POIManager::Get(playerIndex);
			POIManager::WorldStreamerPOI* poi = manager.GetWorldStreamerPOI();
			transform.SetTranslation(poi->GetPosition());
		}
	}

	// FUNCTION: ENGINE 0x10898360
	void StreamPOIBehaviour::OnMessage(Message* message)
	{
		if (message->type == 0x18 && message->id == 7)
		{
			Update(0.0f, 4);
		}
	}
}
