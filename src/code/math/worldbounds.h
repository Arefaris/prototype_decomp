// The world's minimum coordinate (0x10D94664, the value -0.0f: the world is centred at the origin). One definition;
// declared here so the units that subtract it see an unknown-clobber load, as the original's cross-unit reference.
// Name guessed.
#ifndef MATH_WORLDBOUNDS_H
#define MATH_WORLDBOUNDS_H

namespace math
{
	extern const float WORLD_MIN;
}

#endif
