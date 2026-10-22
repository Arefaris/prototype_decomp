#include "code/content/metafactory.h"
#include "code/core/heap.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobject.h"

namespace engine
{
	// FUNCTION: ENGINE 0x10841F80
	MetaBehaviourCreator::MetaBehaviourCreator(const char* newName, unsigned short newFlag, content::ClassMetaType* newType)
		: MetaInstanceCreator(newName, newFlag, newType)
	{
	}

	// FUNCTION: ENGINE 0x10841FB0
	void* MetaBehaviourCreator::Create()
	{
		GameObject* object = GetConstructingObject();
		core::HeapScope scope(GetConstructionHeap());
		Behaviour* behaviour = CreateBehaviour(object);
		if (dynamic_cast<BehaviourController*>(behaviour) == 0)
		{
			object->RegisterBehaviour(behaviour);
		}
		return behaviour;
	}
}
