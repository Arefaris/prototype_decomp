// The bounds of the vehicle graphs (namespace engine::driving; the code sits in 0x1093CE40 - 0x1093DA50, no assert
// path; directory and file names guessed): how far a graph reaches in speed or in steering angle. The speed
// attributes are kept in metres per second and the angle attributes in radians; the reflected members are in
// kilometres per hour and degrees.
#ifndef ENGINE_DRIVING_BOUNDEDGRAPHS_H
#define ENGINE_DRIVING_BOUNDEDGRAPHS_H

#include "code/content/metatype.h"

namespace engine
{
	namespace driving
	{
		// 0x111EB9D4 (symbols.txt): kilometres per hour in metres per second (name guess)
		extern float gKmhToMetresPerSecond;

		// 0x10069040 (the math module's clamp, kept out of line there; name guess)
		float ClampFloat(float value, float lo, float hi);

		// The graph helpers (names guessed). 0x1093D2D0: value as a fraction of limit; beyond the limit it goes on
		// with the given slope
		float NormalizeBounded(float value, float limit, float slope);
		// 0x1093D330: the same for a value that may be negative, with a limit for each side
		float NormalizeBoundedSigned(float value, float positiveLimit, float negativeLimit, float slope);
		// 0x1093D3D0: the value moved towards target by at most the step the faster side allows
		float MoveTowardsBound(float value, float target, float stepIfFaster, float stepOtherwise, float scale);
		// 0x1093D440: the value of the piecewise linear graph through (xs[i], ys[i]) at x
		float InterpolateGraph(float x, unsigned int count, const float* xs, const float* ys);

		// A speed graph reaching in both directions (no vftable; 8 bytes)
		class BoundedSpeedGraphAttributes
		{
		public:
			// 0x1093CE40 / 0x1093D1A0
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// 0x1093CEC0
			BoundedSpeedGraphAttributes();

			// 0x1093CEE0 / 0x1093CF20 and 0x1093CEF0 / 0x1093CF50
			float GetMaxPositiveKmh() const;
			void SetMaxPositiveKmh(float kmh);
			float GetMaxNegativeKmh() const;
			void SetMaxNegativeKmh(float kmh);

			float maxPositive;  // +0x0
			float maxNegative;  // +0x4
		};

		// A speed graph reaching as far in both directions (no vftable; 4 bytes)
		class BoundedSymmetricSpeedGraphAttributes
		{
		public:
			// 0x1093CE80 / 0x1093D250
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// 0x1093CF00
			BoundedSymmetricSpeedGraphAttributes();

			// 0x1093CF10 / 0x1093CF80
			float GetMaxKmh() const;
			void SetMaxKmh(float kmh);

			float maxSpeed;  // +0x0
		};

		// A steering angle graph reaching in both directions (no vftable; 8 bytes)
		class BoundedAngleGraphAttributes
		{
		public:
			// 0x1093D5F0 / 0x1093D920
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// 0x1093D670
			BoundedAngleGraphAttributes();

			// 0x1093D690 / 0x1093D6A0 and 0x1093D6C0 / 0x1093D6D0
			float GetMaxPositiveDegrees() const;
			void SetMaxPositiveDegrees(float degrees);
			float GetMaxNegativeDegrees() const;
			void SetMaxNegativeDegrees(float degrees);

			float maxPositive;  // +0x0
			float maxNegative;  // +0x4
		};

		// A steering angle graph reaching as far in both directions (no vftable; 4 bytes)
		class BoundedSymmetricAngleGraphAttributes
		{
		public:
			// 0x1093D630 / 0x1093D9D0
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// 0x1093D6F0
			BoundedSymmetricAngleGraphAttributes();

			// 0x1093D700 / 0x1093D710
			float GetMaxDegrees() const;
			void SetMaxDegrees(float degrees);

			float maxAngle;  // +0x0
		};
	}
}

#endif
