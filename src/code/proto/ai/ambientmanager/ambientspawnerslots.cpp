// The slot of the ambient spawners that makes the object of the spawner's template (slot 8): a unit of
// ambientspawners.cpp, apart from it because the messages it sends clash with the declarations that file includes.
#include "code/core/heap.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/proto/ai/ambientmanager/ambientmanagermessages.h"
#include "code/proto/ai/ambientmanager/ambientspawners.h"

namespace engine
{
	// 0x11283508 (gameobjectspawner.cpp)
	extern content::ObjectName gPackageNameName;

	// 0x10288F70 (another unit): a name made from a counter of the given kind (the text is for the debugging build)
	core::Name<core::CaseSensitiveKey> MakeUniqueName(int kind, const char* text);
}

namespace proto
{
	// The write access to the "packageName" attribute of an object (the engine expands it here)
	static inline engine::AttributeWriter<core::Name<core::CaseSensitiveKey> > GetPackageNameWriter(
		engine::GameObject* object)
	{
		engine::BaseAttribute* attribute = object->FindAttribute(engine::gPackageNameName);
		if (attribute != 0)
		{
			core::Name<core::CaseSensitiveKey>* value =
				&static_cast<engine::Attribute<core::Name<core::CaseSensitiveKey> >*>(attribute)->Get();
			return engine::AttributeWriter<core::Name<core::CaseSensitiveKey> >(value, engine::gPackageNameName, object);
		}
		return engine::AttributeWriter<core::Name<core::CaseSensitiveKey> >();
	}

	// FUNCTION: ENGINE 0x10420DD0
	void VehicleSpawner::Slot8(void* argument)
	{
		core::HeapScope scope(0xA9);
		core::Name<core::CaseSensitiveKey> name;
		name = engine::MakeUniqueName(2, "AmbientVehicle");
		engine::GameObject* object = engine::GameObjectSpawner::Create(templateName, name, 0xAA, 0, 0, true);
		CreateVehicleMessage message(argument);
		object->SendMessage(&message);
	}

	// FUNCTION: ENGINE 0x10420EA0
	void PedestrianSpawner::Slot8(void* argument)
	{
		core::HeapScope scope(0xA1);
		core::Name<core::CaseSensitiveKey> objectName;
		objectName = engine::MakeUniqueName(2, "NPC");
		engine::GameObject* object = engine::GameObjectSpawner::Create(templateName, objectName, 0xA3, 0, 0, true);
		CreatePedMessage message(argument, type);
		object->SendMessage(&message);
		engine::AttributeWriter<core::Name<core::CaseSensitiveKey> > writer = GetPackageNameWriter(object);
		if (writer.value != 0)
		{
			*writer.value = name;
		}
	}
}
