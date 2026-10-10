#include "code/math/noise.h"

namespace math
{
	// FUNCTION: ENGINE 0x107D8200
	Noise::Noise()
	{
		power = 1.0f;
		octaves = 1;
		frequency.Set(1.0f / 256.0f, 1.0f / 256.0f, 1.0f / 256.0f);
		persistence = 0.5f;
		normaliser = 1.0f;
		bias = 0.0f;
		seed = 0;
		period[0] = -1;
		period[1] = -1;
		period[2] = -1;
	}

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
		frequency.Set(x, y, z);
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
		period[0] = value;
	}

	// FUNCTION: ENGINE 0x107D8360
	void Noise::SetPeriodY(int value)
	{
		period[1] = value;
	}

	// FUNCTION: ENGINE 0x107D8370
	void Noise::SetPeriodZ(int value)
	{
		period[2] = value;
	}
}
