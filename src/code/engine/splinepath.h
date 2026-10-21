// engine::SplinePath and engine::SplinePathCV (RTTI and reflection names): a path of control points that a path
// behaviour follows. The path is a content library object (it derives from engine::IPath, the interface of the
// paths); its control points, SplinePathCV, are plain reflected objects it owns. The control point's reflected names
// are original ("position", "tension", "continuity", "bias", "forceSpeedMatch" and the first member's "time"); the
// layout comes from the reflection and the constructors, the other names are guesses. Unit 0x10910550 - 0x10911500
// (no assert path; the file name is a guess).
#ifndef ENGINE_SPLINEPATH_H
#define ENGINE_SPLINEPATH_H

#include "code/container/arraydynamicstatic.h"
#include "code/container/arraydynamicallocatornew.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/math/matrix.h"
#include "code/math/spline.h"
#include "code/math/vector.h"

namespace engine
{
	class SplinePathCV;
}

namespace container
{
	// The engine moves the elements of an array of pointers down through CopyRange (the loop keeps the distance
	// between its two pointers in a register); the class template's own loop is for the other element types
	template<> inline engine::SplinePathCV** ArrayDynamic<engine::SplinePathCV*, AllocatorNew>::Erase(
		engine::SplinePathCV** position)
	{
		CopyRange(position + 1, end, position);
		end--;
		return position;
	}
}

namespace engine
{
	// RTTI: engine::IPath (7 vftable slots, base content::MetaLoadObject): what the path behaviours follow. Its
	// constructor, destructor and deleting destructor are 0x10937830 / 0x10937820 / 0x10937850 (another unit); this
	// unit holds its class info and the empty member list.
	class IPath : public content::MetaLoadObject
	{
	public:
		IPath();
		virtual ~IPath();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	};

	// One control point of a path: where it is, the time it is reached at and the Kochanek-Bartels parameters of the
	// curve through it (0x24 bytes, virtual destructor)
	class SplinePathCV
	{
	public:
		// 0x10910640
		SplinePathCV();
		// 0x10910680 (deleting destructor 0x10910880)
		virtual ~SplinePathCV();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// The time the point is reached at and where it is (the two travel together)
		struct Key
		{
			float time;
			math::Vector position;
		};
		Key key;  // +4
		float tension;  // +0x14
		float continuity;  // +0x18
		float bias;  // +0x1C
		bool forceSpeedMatch;  // +0x20
	};

	class SplinePath : public IPath
	{
	public:
		typedef container::ArrayDynamic<SplinePathCV*, container::AllocatorNew> PointArray;

		// 0x10911310
		SplinePath();
		// 0x10911410 (deleting destructor 0x109114E0): deletes the points and the spline
		virtual ~SplinePath();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 3 (0x10910E70): once loaded, the first point becomes the path's origin and the spline is
		// built
		virtual void Slot3(int unused);
		// vftable slot 5
		virtual bool Slot5();

		// 0x109106A0: the spline through the points (null before it is built)
		math::Spline* GetSpline() const;
		// 0x109108A0: builds the spline from the points
		void BuildSpline();
		// 0x10910EB0: makes count points at one time step apart and count - 1 offsets from the path's origin when
		// there are none yet, then builds the spline (name guess)
		void CreatePoints(int count, const math::Vector* step);

		PointArray points;  // +8
		math::Matrix transform;  // +0x18
		math::Spline* spline;  // +0x58
		int unknown5C;
		bool unknown60;  // the object is 0x64 bytes
	};
}

namespace content
{
	// The element access of the path's point array for its meta type; its own copy because the default element the
	// reflection inserts is kept in a static of the helper (Default)
	template<> class ArrayDynamicHelper<engine::SplinePath::PointArray> : public ArrayDynamicHelperBase
	{
	public:
		typedef engine::SplinePath::PointArray A;
		typedef A::Element T;

		static T& Default()
		{
			static T sDefault;
			return sDefault;
		}

		virtual int Size(void* array)
		{
			return ((A*)array)->Size();
		}
		virtual void* Get(void* array, int index)
		{
			return &(*(A*)array)[index];
		}
		virtual void* GetConst(void* array, int index)
		{
			return &(*(A*)array)[index];
		}
		virtual void Insert(void* array, int index, int unused);
		virtual void Erase(void* array, int index, int unused);
		virtual int Capacity(void* array)
		{
			return ((A*)array)->Capacity();
		}
		virtual void Expand(void* array, unsigned int count);
	};
}

#endif
