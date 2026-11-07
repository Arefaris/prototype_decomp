// proto::PathInterface (RTTI class; 3 vftable slots) and the wrappers that let a pathfinder's path be read through it:
// proto::FlyingPathfinder::PathWrapper and proto::HunterPathfinder::PathWrapper (RTTI structs). A path is a list of points; the wrapper answers how
// many there are and where each is. Unit 0x1038C600 - 0x1038C610, 0x1038CEF0, 0x1038D5F0 - 0x1038D640 and the
// corresponding places of the other pathfinders (no assert path; the file name is a guess); member names are guesses.
#ifndef PROTO_PATHINTERFACE_H
#define PROTO_PATHINTERFACE_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/math/vector.h"

namespace proto
{
	class PathInterface
	{
	public:
		// 0x1038C600 (the engine's copy is kept out of line)
		PathInterface()
		{
		}

		virtual int GetPointCount() = 0;
		virtual math::Vector GetPoint(int index) = 0;
		// Vftable slot 2 (0x1038C610)
		virtual bool Slot2(int unused1, int unused2);
	};

	// One point of a flying path (0x10 bytes)
	struct FlyingPathPoint
	{
		int unknown0;  // +0
		math::Vector position;  // +4
	};

	struct FlyingPath
	{
		container::ArrayDynamic<FlyingPathPoint, container::AllocatorNew> points;  // +0
	};

	class FlyingPathfinder
	{
	public:
		struct PathWrapper : public PathInterface
		{
			// 0x1038CEF0
			PathWrapper(FlyingPath* newPath, float newOffset);

			// Vftable slot 0 (0x1038D5F0) and 1 (0x1038D600)
			virtual int GetPointCount();
			virtual math::Vector GetPoint(int index);

			float offset;  // +4
			FlyingPath* path;  // +8
		};
	};
	// One point of a hunter's path (0x10 bytes)
	struct HunterPathPoint
	{
		math::Vector position;  // +0
		bool unknownC;  // +0xC
	};

	struct HunterPath
	{
		container::ArrayDynamic<HunterPathPoint, container::AllocatorNew> points;  // +0
	};

	class HunterPathfinder
	{
	public:
		struct PathWrapper : public PathInterface
		{
			// 0x10398D40
			PathWrapper(HunterPath* newPath, float newOffset);

			// Vftable slot 0 (0x10399460) and 1 (0x10399470): the point moved on by offset along the path
			virtual int GetPointCount();
			virtual math::Vector GetPoint(int index);

			float offset;  // +4
			HunterPath* path;  // +8
		};
	};
}

#endif
