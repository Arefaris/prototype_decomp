// Globals that the engine's static initialisers combine or compute from other globals of their unit (translation units whose
// code is not reconstructed; unit name guess).
#include <math.h>

namespace engine
{
	unsigned int gMaskA = 0x4000;
	unsigned int gMaskB = 0x80000;
	unsigned int gMaskC = 0x40;
	unsigned int gMaskD = 0x108000;
	unsigned int gMaskE = 0x200000;
	float gAngle = 1.2217305f;
	float gDivisor = 1995.8694f;
	unsigned int gMaskABCD = gMaskA | gMaskB | gMaskC | gMaskD;
	unsigned int gMaskAB = gMaskA | gMaskB;
	unsigned int gMaskEFlags = gMaskE | 0x148040;
	float gAngleSine = sinf(gAngle);
	float gRatio = 673.6f / gDivisor;
}

// The dynamic initialisers of the unit's globals:
// FUNCTION: ENGINE 0x10D54950
// FUNCTION: ENGINE 0x10D54980
// FUNCTION: ENGINE 0x10D54A60
// FUNCTION: ENGINE 0x10D54B50
// FUNCTION: ENGINE 0x10D5F880
