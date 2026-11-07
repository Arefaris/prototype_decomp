// The helpers the game top level keeps between the heap set-up and the cloud manager (0x104E78A0 - 0x104E7D00): the Lua
// natives that answer a random number and a heading in degrees, a clamped linear interpolation, copies and
// case-insensitive compares of C strings, and the defaults of the parked car cloud manager's configuration. No assert
// path names the unit, so the file name and every function name here are guesses.
#include <ctype.h>
#include <new>
#include <string.h>

#include "code/engine/fmv/fmvplayer.h"
#include "code/proto/ai/ambientmanager/ambientmanager.h"
#include "code/proto/protomain.h"

namespace choreo
{
	// 0x10D94F78 / 0x10D94FF8: 0.0f and -1.0f in the pooled constants (name guesses)
	extern const float gZero;
	extern const float gMinusOne;
	// 0x10945950 (name guess)
	float HeadingXZ(float x, float z);
}

namespace engine
{
	namespace driving
	{
		extern const float gOne;
		extern const float gTwo;
	}

	// 0x1082F990 (fmvplayer.cpp declares the fourth argument as an int; the caller passes a float)
	void PlayMovie(const char* path, bool unknown12, int id, float unused, bool unknown13, bool unknown11, int unknown14,
		bool unknown15);
}

namespace proto
{
	// FUNCTION: ENGINE 0x104E7900
	float InterpolateClamped(float x0, float y0, float x1, float y1, float x)
	{
		if (!(x0 >= x))
		{
			if (x1 <= x)
			{
				return y1;
			}
			float width = x1 - x0;
			if (choreo::gZero < x1 - x0)
			{
				return (y1 - y0) * ((x - x0) / width) + y0;
			}
		}
		return y0;
	}

	// FUNCTION: ENGINE 0x104E7AB0
	float GetWorldOrientation(float a, float b)
	{
		return choreo::HeadingXZ(a, b) * 57.2957764f;
	}
	// FUNCTION: ENGINE 0x104E7C00
	void PlayMovieDefault(const char* path)
	{
		engine::PlayMovie(path, true, -1, choreo::gMinusOne, true, false, 0, false);
	}
}
