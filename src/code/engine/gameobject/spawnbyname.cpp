// Spawning a game object from the template of a name (unit 0x1086B940 - 0x1086B9A0 with the spawn function 0x10868150;
// no assert path, the file name and every name are guesses).
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectspawner.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/math/matrix.h"

namespace engine
{
	// 0x10868150 (not reconstructed): makes the object from the template under the name, places it and sends it its
	// initial state
	GameObject* SpawnTemplateObject(const core::Name<core::CaseSensitiveKey>& name, content::MetaObjectTemplate* objectTemplate,
		const math::Matrix* transform);

	// FUNCTION: ENGINE 0x1086B940
	static __declspec(noinline) content::MetaObjectTemplate* FindTemplate(const core::Name<core::CaseSensitiveKey>& name)
	{
		return content::gRootInventory->Find<content::MetaObjectTemplate>(name);
	}

	// FUNCTION: ENGINE 0x1086B960
	GameObjectHandle SpawnObject(const core::Name<core::CaseSensitiveKey>& name, const core::Name<core::CaseSensitiveKey>& templateName,
		const math::Matrix* transform)
	{
		GameObject* object = 0;
		content::MetaObjectTemplate* objectTemplate = FindTemplate(templateName);
		if (objectTemplate != 0)
		{
			object = SpawnTemplateObject(name, objectTemplate, transform);
		}
		return GetHandle(object);
	}
}
