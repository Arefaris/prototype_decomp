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

	// FUNCTION: ENGINE 0x102E8BB0
	// A kept copy of an inline constructor
	ShaderParameters::ShaderParameters() : unknown0(0), unknown4(0), unknown8(2), unknownC(0)
	{
		unknown110 = false;
		unknown114 = 0;
	}

	// FUNCTION: ENGINE 0x10707B00
	ShaderParameters& ShaderParameters::operator=(const ShaderParameters& other)
	{
		unknown0 = other.unknown0;
		unknown4 = other.unknown4;
		unknown8 = other.unknown8;
		unknownC = other.unknownC;
		for (int i = 0; i < 16; i++)
		{
			parameters[i] = other.parameters[i];
		}
		unknown110 = other.unknown110;
		unknown114 = other.unknown114;
		return *this;
	}
}
