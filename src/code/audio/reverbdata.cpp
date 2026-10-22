// The tables of the reverberation effect (0x10E2F008 - 0x10E2F087).
#include "code/audio/reverb.h"

namespace audio
{
	const unsigned int gReverbEarlyDelays[4][4] =
	{
		{ 587, 1439, 1373, 643 },
		{ 1493, 373, 911, 1091 },
		{ 1201, 773, 521, 1637 },
		{ 997, 1297, 1579, 439 }
	};
	const unsigned int gReverbLateDelays[4][4] =
	{
		{ 293, 479, 0, 0 },
		{ 1051, 1237, 0, 0 },
		{ 0, 0, 1169, 1663 },
		{ 0, 0, 113, 607 }
	};
}
