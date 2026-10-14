#include "code/ravenphysics/batch/narrowphasebatcher.h"

namespace ravenphysics
{
	// FUNCTION: ENGINE 0x10690100
	void PairDetails::Set(const int& idA, void* pointerA, const int& idB, void* objectA, unsigned char typeA,
		void* volumeA, const int& idC, void* bodyB, const int& idD, void* objectB, unsigned char typeB, void* volumeB,
		unsigned short unknown28, unsigned short unknown2A, int unknown30)
	{
		unknown0 = idA;
		unknown4 = pointerA;
		unknown8 = idB;
		unknownC = objectA;
		this->typeA = typeA;
		unknown10 = volumeA;
		unknown14 = idC;
		unknown18 = bodyB;
		unknown1C = idD;
		unknown20 = objectB;
		this->typeB = typeB;
		unknown24 = volumeB;
		this->unknown28 = unknown28;
		this->unknown2A = unknown2A;
		this->unknown30 = unknown30;
	}
}
