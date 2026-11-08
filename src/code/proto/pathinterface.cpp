#include "code/proto/pathinterface.h"

namespace proto
{
	// FUNCTION: ENGINE 0x1038C610
	bool PathInterface::Slot2(int unused1, int unused2)
	{
		return true;
	}

	// FUNCTION: ENGINE 0x1038CEF0
	FlyingPathfinder::PathWrapper::PathWrapper(FlyingPath* newPath, float newOffset)
	{
		offset = newOffset;
		path = newPath;
	}

	// FUNCTION: ENGINE 0x1038D5F0
	int FlyingPathfinder::PathWrapper::GetPointCount()
	{
		return path->points.Size();
	}

	// FUNCTION: ENGINE 0x1038D600
	math::Vector FlyingPathfinder::PathWrapper::GetPoint(int index)
	{
		return path->points.begin[index].position;
	}

	// FUNCTION: ENGINE 0x10398D40
	HunterPathfinder::PathWrapper::PathWrapper(HunterPath* newPath, float newOffset)
	{
		offset = newOffset;
		path = newPath;
	}

	// FUNCTION: ENGINE 0x10399460
	int HunterPathfinder::PathWrapper::GetPointCount()
	{
		return path->points.Size();
	}

	// FUNCTION: ENGINE 0x10399470
	// NONMATCHING: the engine keeps the position in SSE registers and the vector copies mix fld / fstp with movss (9 %)
#ifdef NONMATCHING
	math::Vector HunterPathfinder::PathWrapper::GetPoint(int index)
	{
		HunterPathPoint* points = path->points.begin;
		math::Vector result = points[index].position;
		math::Vector direction;
		if (index < (int)path->points.Size() - 1 && points[index + 1].unknownC)
		{
			if (index < 1)
			{
				direction.x = points[index].position.x - points[index + 1].position.x;
				direction.z = points[index].position.z - points[index + 1].position.z;
			}
			else
			{
				direction.x = points[index - 1].position.x - points[index].position.x;
				direction.z = points[index - 1].position.z - points[index].position.z;
			}
		}
		else
		{
			if (!points[index].unknownC || index < 1)
			{
				result.y = 0.0f;
				return result;
			}
			direction.x = points[index - 1].position.x - points[index].position.x;
			direction.y = points[index - 1].position.y - points[index].position.y;
			direction.z = points[index - 1].position.z - points[index].position.z;
		}
		direction.y = 0.0f;
		direction.Normalize();
		result.x += offset * direction.x;
		result.y += offset * direction.y;
		result.z += offset * direction.z;
		result.y = 0.0f;
		return result;
	}
#endif

	// FUNCTION: ENGINE 0x103A0690
	int HunterShortRangePathfinder::PathWrapper::GetPointCount()
	{
		return path->points.Size();
	}

	// FUNCTION: ENGINE 0x103A06B0
	math::Vector HunterShortRangePathfinder::PathWrapper::GetPoint(int index)
	{
		return path->points.begin[index].position;
	}

	// FUNCTION: ENGINE 0x103A06E0
	// NONMATCHING: the engine clamps the indices with branches, ours selects with set instructions (3.1 %)
#ifdef NONMATCHING
	bool HunterShortRangePathfinder::PathWrapper::Slot2(int first, int second)
	{
		int last = path->points.Size() - 1;
		if (first < 0)
		{
			if (first <= last)
			{
				first = 0;
			}
			else
			{
				first = last;
			}
		}
		else if (first > last)
		{
			first = last;
		}
		if (second < 0)
		{
			if (second <= last)
			{
				second = 0;
			}
			else
			{
				second = last;
			}
		}
		else if (second > last)
		{
			second = last;
		}
		if (second - first > 0 && first < second)
		{
			HunterShortRangePathPoint* point = path->points.begin + first;
			for (; first < second; first++)
			{
				if (0.9f > point->direction.x * point[1].direction.x + point->direction.y * point[1].direction.y
					+ point->direction.z * point[1].direction.z)
				{
					return false;
				}
				point++;
			}
		}
		return true;
	}
#endif
}

template class container::ArrayDynamic<proto::FlyingPathPoint, container::AllocatorNew>;
template class container::ArrayDynamic<proto::HunterPathPoint, container::AllocatorNew>;


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1038C600
// FUNCTION: ENGINE 0x1038C680
// FUNCTION: ENGINE 0x1038C6B0
// FUNCTION: ENGINE 0x1038C6C0
// FUNCTION: ENGINE 0x1038C6D0
// FUNCTION: ENGINE 0x1038C6E0
// FUNCTION: ENGINE 0x1038C720
// FUNCTION: ENGINE 0x1038C730
// FUNCTION: ENGINE 0x1038C790
// FUNCTION: ENGINE 0x1038C7A0
// FUNCTION: ENGINE 0x1038C800
// FUNCTION: ENGINE 0x1038C810
// FUNCTION: ENGINE 0x1038C830
// FUNCTION: ENGINE 0x1038C8B0
// FUNCTION: ENGINE 0x1038C960
// FUNCTION: ENGINE 0x1038CB60
// FUNCTION: ENGINE 0x1038D840
// FUNCTION: ENGINE 0x1038D850
// FUNCTION: ENGINE 0x1038DA60
// FUNCTION: ENGINE 0x1038E510
// FUNCTION: ENGINE 0x1038E5A0
// FUNCTION: ENGINE 0x1038E5D0
// FUNCTION: ENGINE 0x1038E7E0
// FUNCTION: ENGINE 0x10390010
// FUNCTION: ENGINE 0x10390030
// FUNCTION: ENGINE 0x10390130
// FUNCTION: ENGINE 0x10390270
// FUNCTION: ENGINE 0x10398990
// FUNCTION: ENGINE 0x103989B0
// FUNCTION: ENGINE 0x103989D0
// FUNCTION: ENGINE 0x103989E0
// FUNCTION: ENGINE 0x10398A00
// FUNCTION: ENGINE 0x10398AC0
// FUNCTION: ENGINE 0x103997D0
// FUNCTION: ENGINE 0x1039A3A0
// FUNCTION: ENGINE 0x1039B280
