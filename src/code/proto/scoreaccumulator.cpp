#include "code/proto/scoreaccumulator.h"

namespace engine
{
	namespace camera
	{
		// 0x10D95F28: 3.0f in the pooled constants
		extern const float gThree;
	}
}

namespace proto
{
	// FUNCTION: ENGINE 0x103B3040
	float InverseLerpClamped(float value, float min, float max)
	{
		if (min > value)
		{
			return 0.0f;
		}
		if (value > max)
		{
			return 1.0f;
		}
		return (value - min) / (max - min);
	}

	// FUNCTION: ENGINE 0x103B3080
	float EaseCubic(float t)
	{
		float square = t * t;
		float cube = square * t;
		return engine::camera::gThree * square - (cube + cube);
	}

	// FUNCTION: ENGINE 0x103B3230
	// NONMATCHING: the engine evaluates the differences in another order (86 %)
#ifdef NONMATCHING
	float SideOfLine(float a, float b, float c, float d, float e, float f)
	{
		return (f - b) * (c - a) - (d - b) * (e - a);
	}
#endif

	// FUNCTION: ENGINE 0x103B30B0
	float ScoreAccumulator::Add(float t, float scale, int iterations)
	{
		for (int i = 0; i < iterations; i++)
		{
			t = EaseCubic(t);
		}
		float amount = t * scale;
		score += amount;
		return amount;
	}

	// FUNCTION: ENGINE 0x103B3110
	float ScoreAccumulator::AddRamp(float value, float scale, float min, float max, int iterations)
	{
		return Add(InverseLerpClamped(value, min, max), scale, iterations);
	}

	// FUNCTION: ENGINE 0x103B3160
	float ScoreAccumulator::AddInverseRamp(float value, float scale, float min, float max, int iterations)
	{
		return Add(1.0f - InverseLerpClamped(value, min, max), scale, iterations);
	}
}
