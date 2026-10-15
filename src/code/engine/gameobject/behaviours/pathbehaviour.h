// The path behaviours of the game object package (RTTI names engine::IPathBehaviour, engine::PatrolPoint,
// engine::PatrolPathBehaviour, engine::SplineCV, engine::SplineBehaviour). No assert path names the file, so the
// directory and file names are guesses. IPathBehaviour (vftable 0x10E734AC, 15 slots) extends engine::Behaviour;
// PatrolPathBehaviour (0x10E733FC) and SplineBehaviour (0x10E73454) are its two implementations; PatrolPoint and
// SplineCV are plain value classes the behaviours hold (one vftable slot each). Member and method names are guesses
// until the binary names them.
#ifndef ENGINE_GAMEOBJECT_BEHAVIOURS_PATHBEHAVIOUR_H
#define ENGINE_GAMEOBJECT_BEHAVIOURS_PATHBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"

namespace engine
{
	// A behaviour that drives its owner along a path
	class IPathBehaviour : public Behaviour
	{
	public:
		// 0x10864C30
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	};

	// One point of a patrol path (0x10864C70; a container::String at +0x1C)
	class PatrolPoint
	{
	public:
		// 0x10864C70
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	};

	// 0x10864CB0
	class PatrolPathBehaviour : public IPathBehaviour
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	};

	// One control vertex of a spline (0x10864D00; seven floats at +4, a flag at +0x20)
	class SplineCV
	{
	public:
		// 0x10864DF0: starts at the origin, unset
		SplineCV();
		virtual ~SplineCV();

		// 0x10864D00
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		float x;
		float y;
		float z;
		float unknown10;
		float unknown14;
		float unknown18;
		float unknown1C;
		bool flag;
	};

	// 0x10864D40
	class SplineBehaviour : public IPathBehaviour
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	};
}

#endif
