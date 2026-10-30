// pure3d::PartBinding (the shader object a part is drawn with; 0x10704AF0 - 0x10704B00, in the shader unit; file name
// guessed from the class). Names are guesses.
#include "code/pure3d/drawable.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10704AF0
	void PartBinding::Attach(DrawablePart* part)
	{
		if (part != 0)
		{
			users++;
		}
	}

	// FUNCTION: ENGINE 0x10704B00
	void PartBinding::Detach(DrawablePart* part)
	{
		if (part != 0)
		{
			users--;
		}
	}
}
