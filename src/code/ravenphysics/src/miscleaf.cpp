// Small leaf functions of 0x106A0000 - 0x106C0000 whose shape is used once: out-parameter fillers, tiny counters and
// comparison functions. Their owners are not named by the image, so each group is a stand-in struct named after its
// first function; every name and layout is a guess.
#include "code/core/interlocked.h"
#include "code/math/capsule.h"
#include "code/math/matrix.h"
#include "code/math/obb.h"
#include "code/math/plane.h"
#include "code/ravenphysics/collision/collisioninfo.h"

namespace math
{
	// Library tests (another unit)
	int Intersects(const Plane& first, const Capsule& second);
	int Intersects(const Plane& first, const OBB& second);
}

namespace ravenphysics
{
	// The plane tests with their arguments the other way round
	// FUNCTION: ENGINE 0x106B20D0
	int IntersectsCapsulePlane(const math::Capsule& capsule, const math::Plane& plane)
	{
		return math::Intersects(plane, capsule);
	}

	// FUNCTION: ENGINE 0x106B20F0
	int IntersectsBoxPlane(const math::OBB& box, const math::Plane& plane)
	{
		return math::Intersects(plane, box);
	}

	// Moves the points through the matrix and turns the normal
	// FUNCTION: ENGINE 0x106A8090
	void ContactRecord::Transform(const math::Matrix& matrix)
	{
		points[0].Transform(matrix);
		points[1].Transform(matrix);
		matrix.Rotate(normal, normal);
	}

	struct MiscKeyed
	{
		unsigned char padding[0x24];
		unsigned int key;
	};

	// The entries with the smaller key first
	// FUNCTION: ENGINE 0x106B3D70
	int KeyLess(const MiscKeyed* first, const MiscKeyed* second)
	{
		return first->key < second->key;
	}

	struct Misc106B57B0
	{
		// 0 when the key is the first, 1 when it is the second, -1 for another
		int Unknown106B57B0(const int* key) const;

		int first;
		int second;
	};

	// FUNCTION: ENGINE 0x106B57B0
	int Misc106B57B0::Unknown106B57B0(const int* key) const
	{
		if (*key == first)
		{
			return 0;
		}
		return *key == second ? 1 : -1;
	}

	struct Misc106B5860
	{
		void Unknown106B5860();

		unsigned char padding[0x24];
		int first;
		int second;
	};

	// FUNCTION: ENGINE 0x106B5860
	void Misc106B5860::Unknown106B5860()
	{
		first = 0;
		second = 0;
	}

	struct Misc106B3590
	{
		long Unknown106B3590();
		long Unknown106B35A0();

		unsigned char padding[0x24];
		long flag;
	};

	// FUNCTION: ENGINE 0x106B3590
	long Misc106B3590::Unknown106B3590()
	{
		return _InterlockedExchange(&flag, 1);
	}

	// FUNCTION: ENGINE 0x106B35A0
	long Misc106B3590::Unknown106B35A0()
	{
		return _InterlockedExchange(&flag, 0);
	}

	struct MiscTriple
	{
		MiscTriple()
		{
		}
		MiscTriple(int newFirst, int newThird)
		{
			first = newFirst;
			second = 0;
			third = newThird;
		}

		int first;
		int second;
		int third;
	};

	struct Misc106B36B0
	{
		void Unknown106B36B0(MiscTriple* out) const;

		int first;
		int second;
	};

	// FUNCTION: ENGINE 0x106B36B0
	// EQUIVALENT: the same loads and stores; the engine keeps the first word in edx and the second in ecx, ours the other way round, 62.5 %
	void Misc106B36B0::Unknown106B36B0(MiscTriple* out) const
	{
		int a = first;
		int b = second;
		out->first = a;
		out->second = 0;
		out->third = b;
	}

	struct Misc106B36D0
	{
		void Unknown106B36D0(MiscTriple* out) const;

		unsigned char padding[0x20];
		int first;
		int second;
	};

	// FUNCTION: ENGINE 0x106B36D0
	// EQUIVALENT: the same loads and stores; the engine keeps the first word in edx and the second in ecx, ours the other way round, 64.0 %
	void Misc106B36D0::Unknown106B36D0(MiscTriple* out) const
	{
		int a = first;
		int b = second;
		out->first = a;
		out->second = 0;
		out->third = b;
	}

	struct MiscPair
	{
		int first;
		int second;
	};

	struct Misc106AF550
	{
		void Unknown106AF550(MiscPair* out) const;

		unsigned char padding[0xC2];
		unsigned short small;
		unsigned char pad[4];
		int word;
	};

	// FUNCTION: ENGINE 0x106AF550
	// EQUIVALENT: the same two loads and two stores; the engine reads both members before it takes the output pointer, 56.0 %
	void Misc106AF550::Unknown106AF550(MiscPair* out) const
	{
		int a = word;
		int b = small;
		out->first = a;
		out->second = b;
	}

	struct Misc106AEC90
	{
		void Unknown106AEC90(char newFirst, char newSecond);

		unsigned char padding[0x2C];
		char first;
		char second;
	};

	// FUNCTION: ENGINE 0x106AEC90
	void Misc106AEC90::Unknown106AEC90(char newFirst, char newSecond)
	{
		first = newFirst;
		second = newSecond;
	}

	struct Misc106AEDD0
	{
		int Unknown106AEDD0() const;

		unsigned char padding[6];
		unsigned char flags;
	};

	// FUNCTION: ENGINE 0x106AEDD0
	int Misc106AEDD0::Unknown106AEDD0() const
	{
		return flags & 7;
	}

	struct Misc106ABE70
	{
		char* Unknown106ABE70(char* out) const;

		char first;
		char second;
	};

	// FUNCTION: ENGINE 0x106ABE70
	char* Misc106ABE70::Unknown106ABE70(char* out) const
	{
		*out = second;
		return out;
	}

	struct Misc106B5B50
	{
		char* Unknown106B5B50();

		char* begin;
		char* current;
		char* end;
	};

	// The next eight bytes of the buffer, or null when it is used up
	// FUNCTION: ENGINE 0x106B5B50
	char* Misc106B5B50::Unknown106B5B50()
	{
		if (current < end)
		{
			char* result = current;
			current += 8;
			return result;
		}
		return 0;
	}

	struct Misc106A74C0
	{
		void Unknown106A74C0(unsigned short value);

		int unknown0;
		int unknown4;
		char* begin;
		char* current;
	};

	// Appends a short while the buffer holds less than four kilobytes
	// FUNCTION: ENGINE 0x106A74C0
	void Misc106A74C0::Unknown106A74C0(unsigned short value)
	{
		if (current < begin + 0x1000)
		{
			*(unsigned short*)current = value;
			current += 2;
		}
	}

	struct Misc106A76F0
	{
		Misc106A76F0* Unknown106A76F0();
		int Unknown106A7710();
		void Unknown106A7730(int value);

		int items[256];
		unsigned short top;
	};

	// FUNCTION: ENGINE 0x106A76F0
	Misc106A76F0* Misc106A76F0::Unknown106A76F0()
	{
		top = 0;
		return this;
	}

	// FUNCTION: ENGINE 0x106A7710
	int Misc106A76F0::Unknown106A7710()
	{
		top--;
		return items[top];
	}

	// FUNCTION: ENGINE 0x106A7730
	void Misc106A76F0::Unknown106A7730(int value)
	{
		items[top] = value;
		top++;
	}

	struct Misc106B56E0
	{
		void Unknown106B56E0(const Misc106B56E0* source, float* newFirst, float* newLast);

		float first;
		float unknown4;
		float unknown8;
		float last;
	};

	// FUNCTION: ENGINE 0x106B56E0
	void Misc106B56E0::Unknown106B56E0(const Misc106B56E0* source, float* newFirst, float* newLast)
	{
		*newFirst = source->first;
		*newLast = source->last;
	}
}
