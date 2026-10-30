// The lighting scene (code/pure3d/lighting/lightingscene.cpp, path from the asserts). Names are guesses.
#include "code/pure3d/light.h"
#include "code/pure3d/lighting.h"

namespace pure3d
{
	unsigned int gLastLightGroup;

	// FUNCTION: ENGINE 0x10756350
	bool LightingScene::Contains(Light* light)
	{
		LightArray* list;
		if (light->unknown214 == 0xFFFF)
		{
			list = &unbounded;
		}
		else
		{
			list = &bounded;
		}
		Light** found = list->begin;
		for (; found != list->end && *found != light; found++)
		{
		}
		return found != list->end;
	}

	// FUNCTION: ENGINE 0x10756AA0
	// EQUIVALENT: the engine's copy loop is unrolled four times (the members loaded once for the unrolled part);
	// our compiler keeps the plain loop for every form tried
	void LightingScene::GetLights(LightArray* lights, const unsigned int* region)
	{
		unsigned int count = query.Select(indicesBegin, indicesEnd - indicesBegin, region);
		Light* none = 0;
		lights->Resize(count, none);
		for (unsigned int i = 0; i < count; i++)
		{
			lights->begin[i] = this->lights[indicesBegin[i]];
		}
	}

	// FUNCTION: ENGINE 0x10757A10
	bool LightGroupTable::Contains(Light* light)
	{
		return scene->Contains(light);
	}

	// FUNCTION: ENGINE 0x10757A80
	int LightingScene::GetBoundedCount()
	{
		return bounded.Size();
	}

	// FUNCTION: ENGINE 0x10757A90
	int LightingScene::GetUnboundedCount()
	{
		return unbounded.Size();
	}

	// FUNCTION: ENGINE 0x10757AA0
	// EQUIVALENT: the same four loads and two subtractions; the engine reads the first list into eax, ours the second (83.3 %)
	int LightGroupTable::GetLightCount()
	{
		return scene->bounded.Size() + scene->unbounded.Size();
	}

	// FUNCTION: ENGINE 0x10757AC0
	Entity* LightGroupTable::FindGroup(const core::Name<core::CaseSensitiveKey>* name)
	{
		Entity* last = groups[gLastLightGroup];
		if (last->mName == *name)
		{
			return last;
		}
		for (unsigned int i = 0; i < 0x20; i++)
		{
			if (groups[i]->mName == *name)
			{
				Entity* found = groups[i];
				gLastLightGroup = i;
				return found;
			}
		}
		return 0;
	}
}
