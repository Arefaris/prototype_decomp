// The web of intrigue manager (RTTI proto::WebOfIntrigueManager, base engine::DBObserver): the mission-like web of
// targets the player works through. Only what the units around it use is declared; the layout is not recovered.
#ifndef PROTO_WEBOFINTRIGUE_WEBOFINTRIGUEMANAGER_H
#define PROTO_WEBOFINTRIGUE_WEBOFINTRIGUEMANAGER_H

#include "code/engine/dbobserver.h"
#include "code/engine/gameobject/gameobjecthandle.h"

namespace proto
{
	// RTTI: proto::WebOfIntrigueManager
	class WebOfIntrigueManager : public engine::DBObserver
	{
	public:
		// RTTI: proto::WebOfIntrigueManager::Node (a node of the web: its index is at +8)
		class Node;

		// 0x1055CC40: the node of the web an object is the target of (null when it is none; name guess)
		Node* FindNode(engine::GameObjectHandle handle);
	};

	// 0x11272D48: the one manager (null: none)
	extern WebOfIntrigueManager* gWebOfIntrigueManager;
}

#endif
