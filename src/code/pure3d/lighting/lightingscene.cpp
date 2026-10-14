// The lighting scene (code/pure3d/lighting/lightingscene.cpp, path from the asserts). Names are guesses.
#include "code/pure3d/lighting.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10756AA0
	// EQUIVALENT: the engine's copy loop is unrolled four times (the members loaded once for the unrolled part);
	// our compiler keeps the plain loop for every form tried
	void LightingScene::GetLights(LightArray* lights, int region)
	{
		unsigned int count = query.Select(indicesBegin, indicesEnd - indicesBegin, region);
		Light* none = 0;
		lights->Resize(count, none);
		for (unsigned int i = 0; i < count; i++)
		{
			lights->begin[i] = this->lights[indicesBegin[i]];
		}
	}
}
