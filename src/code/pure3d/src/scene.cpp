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

	// FUNCTION: ENGINE 0x10712360
	void Drawable::CollectBatchParts(container::ArrayDynamicHeap<DrawablePart*>* list)
	{
		unsigned int count = parts.Size();
		for (unsigned int i = 0; i < count; i++)
		{
			if (parts.begin[i].UpdateBatch())
			{
				list->PushBack(&parts.begin[i]);
			}
		}
	}

	// FUNCTION: ENGINE 0x10712760
	void Scene::Unknown10712760()
	{
		unsigned int count = this->parts.Size();
		for (unsigned int i = 0; i < count; i++)
		{
			this->parts.begin[i]->UpdateBatch();
		}
		count = addedDrawables.Size();
		for (unsigned int i = 0; i < count; i++)
		{
			addedDrawables.begin[i]->CollectBatchParts(&this->parts);
		}
		addedDrawables.Reset();
	}

	// FUNCTION: ENGINE 0x107127E0
	void Scene::GetDrawables(container::ArrayDynamicHeap<Drawable*>* list, int unused)
	{
		for (unsigned int i = 0; i < allDrawables.Size(); i++)
		{
			if (list->end == list->capacity)
			{
				return;
			}
			list->PushBack(allDrawables[i]);
		}
	}

	// FUNCTION: ENGINE 0x10711FE0
	bool RemoveFromList(container::ArrayDynamicHeap<Drawable*>* list, Drawable* drawable)
	{
		for (Drawable** item = list->begin; item != list->end; item++)
		{
			if (*item == drawable)
			{
				list->EraseFast(item);
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10712540
	// NONMATCHING: the engine's frame is eight bytes smaller (one part reference slot is shared and the loop counter lives in the
	// dead argument slot; best 98.0 %)
#ifdef NONMATCHING
	void Scene::Remove(Drawable* drawable)
	{
		for (unsigned int index = 0; index < allDrawables.Size(); index++)
		{
			if (allDrawables[index] == drawable)
			{
				for (unsigned int i = 0; i < drawable->parts.Size(); i++)
				{
					PartRef ref(drawable, i);
					DrawablePart* part = ref.Get();
					part->client.Unregister();
					part->client.Clear();
					DrawablePart** found = parts.Find(part);
					if (found != parts.end)
					{
						parts.EraseFast(found);
					}
					if (part->primitive->type == 4)
					{
						for (PartClient* client = partClients.begin; client < partClients.end; client++)
						{
							if (client->part == part && client->active)
							{
								client->active = false;
								client->part = 0;
								client->Unregister();
								client->Clear();
								break;
							}
						}
					}
				}
				RemoveFromList(&addedDrawables, drawable);
				drawable->registered = 0;
				allDrawables.EraseFast(allDrawables.begin + index);
				if (drawable->IsCyclic())
				{
					RemoveFromList(&cyclicDrawables, drawable);
				}
				if (drawable->IsCyclic() || drawable->flag04)
				{
					RemoveFromList(&drawables, drawable);
				}
				PartRef first(drawable, 0);
				if (first->primitive->type == 0x10)
				{
					RemoveFromList(&particleDrawables, drawable);
				}
				if (!drawable->IsCyclic())
				{
					unknown118 = true;
				}
				RemoveFromList(&refreshList, drawable);
				drawable->Release();
				return;
			}
		}
	}
#endif

	// FUNCTION: ENGINE 0x10712410
	void Scene::Add(Drawable* drawable, bool unknown)
	{
		if (drawable != 0)
		{
			drawable->UpdateBounds(false);
			drawable->AddRef();
			drawable->MarkFrame();
			drawable->registered = 1;
			allDrawables.PushBack(drawable);
			Refresh(drawable);
			Unknown2(drawable);
			Unknown3(drawable);
			if (drawable->IsCyclic())
			{
				cyclicDrawables.PushBack(drawable);
			}
			if (drawable->IsCyclic() || drawable->flag04 || unknown)
			{
				drawables.PushBack(drawable);
			}
			PartRef ref(drawable, 0);
			if (ref->primitive->type == 0x10)
			{
				particleDrawables.PushBack(drawable);
			}
			addedDrawables.PushBack(drawable);
			if (!drawable->IsCyclic())
			{
				unknown118 = true;
			}
		}
	}

	// FUNCTION: ENGINE 0x10712300
	// NONMATCHING: register allocation (the engine keeps the end of the refresh list in two registers and the drawable in
	// edi; 37 %). Not compiled: with our copy in this unit the compiler keeps ecx across the call in Add, the engine's does not.
#ifdef NONMATCHING
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
#endif

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
