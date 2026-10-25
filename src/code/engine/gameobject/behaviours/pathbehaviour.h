// The path behaviours of the game object package (RTTI names engine::IPathBehaviour, engine::PatrolPoint,
// engine::PatrolPathBehaviour, engine::SplineCV, engine::SplineBehaviour). No assert path names the file, so the
// directory and file names are guesses. IPathBehaviour (vftable 0x10E734AC, 15 slots) extends engine::Behaviour with
// the seven operations on a path's points; PatrolPathBehaviour (0x10E733FC) and SplineBehaviour (0x10E73454) are its
// two implementations; PatrolPoint and SplineCV are the plain value classes they hold (one vftable slot each). Both
// behaviours keep the owner's transform at the time of the last transform message: when the owner moves, the points
// move with it (the points are positions in the world). The reflected member names are original; method and other
// member names are guesses.
#ifndef ENGINE_GAMEOBJECT_BEHAVIOURS_PATHBEHAVIOUR_H
#define ENGINE_GAMEOBJECT_BEHAVIOURS_PATHBEHAVIOUR_H

#include "code/container/arraydynamicnew.h"
#include "code/container/string.h"
#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/math/matrix.h"
#include "code/math/spline.h"
#include "code/math/vector.h"

namespace engine
{
	// A behaviour that drives its owner along a path
	class IPathBehaviour : public Behaviour
	{
	public:
		// 0x108678C0
		explicit IPathBehaviour(GameObject* newOwner);
		// 0x108678E0 (deleting destructor 0x10867980)
		virtual ~IPathBehaviour();

		// 0x10864C30 / 0x10865D10
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x108678F0): nothing to do
		virtual void Slot1();
		// vftable slot 4 of the implementations: nothing to do (0x10864DD0, 0x10864EC0)
		// vftable slots 8 - 14: the points of the path
		// The number of points
		virtual int GetPointCount() = 0;
		// The position of a point (the owner's when there is no such point)
		virtual void GetPoint(math::Vector* position, int index) = 0;
		// Moves a point; false when there is no such point
		virtual bool SetPoint(int index, const math::Vector* position) = 0;
		// Makes a new point before / after the point at index, halfway to its neighbour
		virtual void InsertBefore(int index) = 0;
		virtual void InsertAfter(int index) = 0;
		virtual void RemovePoint(int index) = 0;
		virtual void Slot14(int index) = 0;
	};

	// One point of a patrol path (0x60 bytes, a virtual destructor): where to stand, the way to face and a text
	class PatrolPoint
	{
	public:
		// 0x10865350
		PatrolPoint();
		// 0x10864DA0 (deleting destructor 0x10865390)
		virtual ~PatrolPoint();

		// 0x10864C70 / 0x10865D70
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		math::Vector position;  // +4, reflected as "pos"
		math::Vector orientation;  // +0x10, reflected as "ori"
		container::StringC<64> text;  // +0x1C
	};

	// A behaviour that walks its owner along a list of points, closed into a loop or not
	class PatrolPathBehaviour : public IPathBehaviour
	{
	public:
		typedef container::ArrayDynamicNew<PatrolPoint*> PointArray;

		// 0x10867600
		explicit PatrolPathBehaviour(GameObject* newOwner);
		// 0x108668F0 (deleting destructor 0x10866DE0): deletes the points
		virtual ~PatrolPathBehaviour();

		// 0x10864CB0 / 0x10866C40
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x108653B0, a jump to the base's), slot 4 (0x10864DD0, empty), slot 6 (0x108653C0): when the
		// owner's transform changed, moves the points with it
		virtual void Slot1();
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(Message* message);
		// Slots 8 - 14 (0x10865520, 0x10865530, 0x10865590, 0x10866E00, 0x10866FC0, 0x10865FA0, 0x10866940)
		virtual int GetPointCount();
		virtual void GetPoint(math::Vector* position, int index);
		virtual bool SetPoint(int index, const math::Vector* position);
		virtual void InsertBefore(int index);
		virtual void InsertAfter(int index);
		virtual void RemovePoint(int index);
		virtual void Slot14(int index);
		// Slot 15 (0x10865510)
		virtual void Slot15();

		// 0x10866020: makes count points one unit apart, from the owner's position, when there are none yet
		void CreatePoints(int count);

		bool closed;  // +0xC, reflected as "closed"
		PointArray points;  // +0x10, reflected as "points"
		int unknown1C;
		int unknown20;
		bool unknown24;
		// False while the behaviour moves its owner itself
		bool followOwner;  // +0x25
		math::Matrix transform;  // +0x28
	};

	// One control vertex of a spline (0x24 bytes, a virtual destructor): the time it is reached at, where it is and the
	// Kochanek-Bartels parameters of the curve through it
	class SplineCV
	{
	public:
		// 0x10864DF0: starts at the origin, unset
		SplineCV();
		// 0x10864E30 (deleting destructor 0x108655F0)
		virtual ~SplineCV();

		// 0x10864D00 / 0x10865E60
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

	// A behaviour that moves its owner along a spline through its control vertices
	class SplineBehaviour : public IPathBehaviour
	{
	public:
		typedef container::ArrayDynamicNew<SplineCV*> PointArray;

		// 0x10867760
		explicit SplineBehaviour(GameObject* newOwner);
		// 0x108669E0 (deleting destructor 0x108671C0): deletes the points and the spline
		virtual ~SplineBehaviour();

		// 0x10864D40 / 0x10866D20
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x108660F0), slot 4 (0x10864EC0, empty), slot 6 (0x10866100)
		virtual void Slot1();
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(Message* message);
		// Slots 8 - 14 (0x10865610, 0x10865620, 0x10866260, 0x108671E0, 0x108673D0, 0x108662D0, 0x10866A50)
		virtual int GetPointCount();
		virtual void GetPoint(math::Vector* position, int index);
		virtual bool SetPoint(int index, const math::Vector* position);
		virtual void InsertBefore(int index);
		virtual void InsertAfter(int index);
		virtual void RemovePoint(int index);
		virtual void Slot14(int index);
		// Slot 15 (0x10866250, a jump to 0x10865680)
		virtual void Slot15();

		// 0x10865680: builds the spline through the points
		void BuildSpline();
		// 0x10866360: makes count points one time unit apart, step apart, from the owner's position, when there are
		// none yet
		void CreatePoints(int count, const math::Vector* step);

		PointArray points;  // +0xC, reflected as "points"
		int unknown18;
		math::Spline* spline;  // +0x1C
		int unknown20;
		int unknown24;
		int unknown28;
		bool unknown2C;
		bool followOwner;  // +0x2D
		math::Matrix transform;  // +0x30
	};
}

#endif
