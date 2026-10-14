// pure3d::Mesh and pure3d::MeshState (unit around 0x10707400 - 0x10709A00; file name guessed from the classes).
// Names are guesses.
#include "code/pure3d/primitive.h"
#include "code/pure3d/shaderparameters.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10707680
	FrameController* MeshState::GetController3()
	{
		return controller3;
	}

	// FUNCTION: ENGINE 0x10707B00
	ShaderParameters& ShaderParameters::operator=(const ShaderParameters& other)
	{
		unknown0[0] = other.unknown0[0];
		unknown0[1] = other.unknown0[1];
		unknown0[2] = other.unknown0[2];
		unknown0[3] = other.unknown0[3];
		for (int i = 0; i < 16; i++)
		{
			parameters[i] = other.parameters[i];
		}
		unknown110 = other.unknown110;
		unknown114 = other.unknown114;
		return *this;
	}
}
