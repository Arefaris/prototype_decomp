// pure3d::LightSelection (0x10717920 - 0x10718DB9; file name guessed from the class). Only the small accessors and
// the scales the lit passes call are reconstructed. Names are guesses.
#include "code/pure3d/light.h"
#include "code/pure3d/lightselection.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10717920
	LightSelection* LightSelection::Get()
	{
		return gLightSelection;
	}

	// FUNCTION: ENGINE 0x10717930
	void LightSelection::SetMode(int newMode)
	{
		if (unknown34 && newMode == 1)
		{
			newMode = 3;
		}
		mode = newMode;
	}

	// FUNCTION: ENGINE 0x10717950
	int LightSelection::GetMode()
	{
		return mode;
	}

	// FUNCTION: ENGINE 0x10717960
	LightList* LightSelection::GetActiveLights()
	{
		return &active;
	}

	// FUNCTION: ENGINE 0x10717970
	LightList* LightSelection::GetVertexLights()
	{
		return &vertex;
	}

	// FUNCTION: ENGINE 0x10717980
	void LightSelection::SetUnknown34(bool value)
	{
		unknown34 = value;
	}

	// FUNCTION: ENGINE 0x10717990
	float LightSelection::GetRangeScale(Light* light)
	{
		float scale = 1.0f;
		if (light->GetUserData())
		{
			scale = ((ProtoLightUserData*)light->GetUserData())->unknown10;
		}
		return scale;
	}

	// FUNCTION: ENGINE 0x107179D0
	float LightSelection::GetIntensityScale(Light* light, int scaleMode)
	{
		float scale = 1.0f;
		if (light->GetUserData())
		{
			ProtoLightUserData* data = (ProtoLightUserData*)light->GetUserData();
			switch (scaleMode)
			{
			case 0:
				scale = data->unknownC;
				break;
			case 1:
				scale = data->unknown8;
				break;
			}
		}
		return scale;
	}
}
