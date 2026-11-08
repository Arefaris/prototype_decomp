// Small float helpers of the target selection and movement code (unit 0x103B3040 - 0x103B3270, no assert path; the
// names and the file name are guesses): an inverse linear interpolation, the cubic ease 3t^2 - 2t^3, a score that
// adds up eased values, and the side test of a point against a line in two dimensions.
#ifndef PROTO_SCOREACCUMULATOR_H
#define PROTO_SCOREACCUMULATOR_H

namespace proto
{
	// 0x103B3040: where value lies between min and max, 0 below min and 1 above max (the arguments in this order)
	float InverseLerpClamped(float value, float min, float max);

	// 0x103B3080: 3 t^2 - 2 t^3
	float EaseCubic(float t);

	// 0x103B3230: (e - b) * (c - a) - (d - b) * (f - a): which side of the line from (a, b) through (c, d) the point
	// (e, f) lies on
	float SideOfLine(float a, float b, float c, float d, float e, float f);

	struct ScoreAccumulator
	{
		// 0x103B30B0: eases t `iterations` times, adds the result times scale to the score and answers it
		float Add(float t, float scale, int iterations);
		// 0x103B3110: Add of the position of value between min and max
		float AddRamp(float value, float scale, float min, float max, int iterations);
		// 0x103B3160: the same with the position mirrored (1 - position)
		float AddInverseRamp(float value, float scale, float min, float max, int iterations);

		float score;
	};
}

#endif
