// math::Noise: parameters of a multi-octave Perlin noise evaluation (the evaluation itself, 0x101043F0, lives in
// another unit). Callers build one on the stack, set a seed tag, four octaves, a frequency, a persistence of 0.25
// and sample it along time. Class and member names are guesses from that use; the layout and defaults are the
// binary's.
#ifndef MATH_NOISE_H
#define MATH_NOISE_H

namespace math
{
	class Noise
	{
	public:
		int seed;
		float frequencyX;
		float frequencyY;
		float frequencyZ;
		// The result is raised to this power unless it is 1
		float power;
		// Amplitude ratio between octaves
		float persistence;
		// 1 / (1 + persistence + persistence^2 + ...), keeps the sum of the octaves within [-1, 1]
		float normaliser;
		// Subtracted from the normalised result
		float bias;
		int octaves;
		// Integer periods for tiling noise, -1 for none
		int periodX;
		int periodY;
		int periodZ;

		Noise();
		~Noise();

		void SetBias(float value);
		void SetPower(float value);
		void SetOctaves(int value);
		void SetFrequency(float x, float y, float z);
		void SetPersistence(float value);
		void SetSeed(int value);
		void SetPeriodX(int value);
		void SetPeriodY(int value);
		void SetPeriodZ(int value);

	private:
		// Recomputes normaliser from persistence and octaves
		void UpdateNormaliser();
	};
}

#endif
