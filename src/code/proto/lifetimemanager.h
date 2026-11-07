// The manager that limits how long dead objects stay in the world (RTTI proto::LifetimeManager; only the members the fight actions call).
#ifndef PROTO_LIFETIMEMANAGER_H
#define PROTO_LIFETIMEMANAGER_H

#include "code/engine/gameobject/gameobjecthandle.h"

namespace proto
{
	class LifetimeManager
	{
	public:
		// 0x104988C0: takes an object out of the world, optionally telling the scenario it died (name guess)
		void Unknown104988C0(engine::GameObjectHandle* object, engine::GameObjectHandle* killer, bool unknown, bool sendMessage);
	};

	// 0x1126BDF8
	extern LifetimeManager* gLifetimeManager;
}

#endif
