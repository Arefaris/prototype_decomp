// pure3d::pddiViewRect and pddiViewProjection: the small structs of the view state, compiled in a unit of their own (the
// context calls them as functions of another unit; the file name is guessed, no assert path survives).
#include "code/pure3d/pddi.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x1061DAE0
	pddiViewRect::pddiViewRect()
	{
	}

	// FUNCTION: ENGINE 0x1061DB20
	void pddiViewRect::Set(float a, float b, float c, float d)
	{
		values[0] = a;
		values[1] = b;
		values[2] = c;
		values[3] = d;
	}

	// FUNCTION: ENGINE 0x1061DB50
	void pddiViewProjection::Set(float a, float b, float c, float d, float e, float f)
	{
		values[0] = a;
		values[1] = b;
		values[2] = c;
		values[3] = d;
		values[4] = e;
		values[5] = f;
	}
}
