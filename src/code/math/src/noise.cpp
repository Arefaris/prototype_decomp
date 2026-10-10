#include "code/math/noise.h"

namespace math
{
	// FUNCTION: ENGINE 0x107D8260
	Noise::~Noise()
	{
	}

	// FUNCTION: ENGINE 0x107D8270
	void Noise::UpdateNormaliser()
	{
		float sum = 0.0f;
		float term = 1.0f;
		for (int i = 0; i < octaves; i++)
		{
			sum += term;
			term *= persistence;
		}
		normaliser = 1.0f / sum;
	}

	// FUNCTION: ENGINE 0x107D82C0
	void Noise::SetBias(float value)
	{
		bias = value;
	}

	// FUNCTION: ENGINE 0x107D82D0
	void Noise::SetPower(float value)
	{
		power = value;
	}

	// FUNCTION: ENGINE 0x107D82E0
	void Noise::SetOctaves(int value)
	{
		octaves = value;
		UpdateNormaliser();
	}

	// FUNCTION: ENGINE 0x107D82F0
	void Noise::SetFrequency(float x, float y, float z)
	{
		frequencyX = x;
		frequencyY = y;
		frequencyZ = z;
		UpdateNormaliser();
	}

	// FUNCTION: ENGINE 0x107D8320
	void Noise::SetPersistence(float value)
	{
		persistence = value;
		UpdateNormaliser();
	}

	// FUNCTION: ENGINE 0x107D8340
	void Noise::SetSeed(int value)
	{
		seed = value;
	}

	// FUNCTION: ENGINE 0x107D8350
	void Noise::SetPeriodX(int value)
	{
		periodX = value;
	}

	// FUNCTION: ENGINE 0x107D8360
	void Noise::SetPeriodY(int value)
	{
		periodY = value;
	}

	// FUNCTION: ENGINE 0x107D8370
	void Noise::SetPeriodZ(int value)
	{
		periodZ = value;
	}
}
