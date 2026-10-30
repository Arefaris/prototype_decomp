// pure3d::Scene (unit 0x10710930 - 0x10714400; file name guessed from the class): the drawables the render thread
// draws and their asynchronous updates. Names are guesses unless noted.
#include "code/pure3d/drawable.h"
#include "code/pure3d/lighting.h"
#include "code/pure3d/scene.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10710B40
	void* Scene::GetUnknownD8()
	{
		return unknownD8;
	}

	// FUNCTION: ENGINE 0x10710AC0
	void Scene::AddLight(Light* light)
	{
		lightingScene->AddLight(light);
	}

	// FUNCTION: ENGINE 0x10710AE0
	void Scene::RemoveLight(Light* light)
	{
		lightingScene->RemoveLight(light);
	}

	// FUNCTION: ENGINE 0x10710B00
	LightGroupTable* Scene::GetLightGroupTable()
	{
		return lightGroupTable;
	}

	// FUNCTION: ENGINE 0x10710B10
	LightingScene* Scene::GetLightingScene()
	{
		return lightingScene;
	}

	// FUNCTION: ENGINE 0x10712300
	// EQUIVALENT: register allocation (the engine keeps the end of the refresh list in two registers and the drawable in
	// edi; 37 %)
	void Scene::Refresh(Drawable* drawable)
	{
		if (allDrawables.Find(drawable) != allDrawables.end)
		{
			if (refreshList.Find(drawable) == refreshList.end)
			{
				refreshList.PushBack(drawable);
			}
		}
	}

	// FUNCTION: ENGINE 0x10711400
	void Scene::UpdateDrawables(unsigned int first, float dt, unsigned int step)
	{
		unsigned int frame = GetCurrentFrame();
		unsigned int count = drawables.Size();
		for (unsigned int i = first; i < count; i += step)
		{
			if (drawables[i]->frameC0 == frame || drawables[i]->IsCyclic())
			{
				drawables[i]->UpdateParts();
				drawables[i]->UpdateBounds(true);
			}
		}
	}
}
