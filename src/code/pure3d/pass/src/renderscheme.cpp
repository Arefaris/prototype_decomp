// pure3d::RenderScheme (unit around 0x1074D860 - 0x1074DD00; the file name is guessed from the class). Names are guesses.
#include "code/pure3d/renderscheme.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x1074D860
	void RenderScheme::Begin()
	{
		if (pass != 0)
		{
			pass->BeginOnce();
		}
	}

	// FUNCTION: ENGINE 0x1074D870
	void RenderScheme::End()
	{
		if (pass != 0)
		{
			pass->EndOnce();
		}
	}

	// FUNCTION: ENGINE 0x1074DC60
	void RenderScheme::Unknown4(int a)
	{
	}

	// FUNCTION: ENGINE 0x1074DC70
	void RenderScheme::Unknown5(int a, int b, int c, int d)
	{
	}
}
