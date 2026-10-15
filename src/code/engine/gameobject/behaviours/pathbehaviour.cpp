// The path behaviours: see the header. The unit has no name of its own in the binary, the file name is a guess.
#include "code/engine/gameobject/behaviours/pathbehaviour.h"

namespace engine
{
	// FUNCTION: ENGINE 0x10864C30
	content::ClassInfo* IPathBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::IPathBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10864C70
	content::ClassInfo* PatrolPoint::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::PatrolPoint";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10864CB0
	content::ClassInfo* PatrolPathBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::PatrolPathBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10864D00
	content::ClassInfo* SplineCV::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::SplineCV";
		sInfo.code = "pn";
		return &sInfo;
	}

	// 0x10864D90 (constructor, kept copy) and 0x10864FA0 (IsDerived): the caster the class meta type of
	// engine::IPathBehaviour carries for engine::SplineBehaviour. The unit kept them out of line, which is what an
	// explicit instantiation makes the compiler do.
	template struct content::BaseClassCasterImpl<IPathBehaviour, SplineBehaviour>;

	// FUNCTION: ENGINE 0x10864DF0
	SplineCV::SplineCV() :
		x(0.0f),
		y(0.0f),
		z(0.0f),
		unknown10(0.0f),
		unknown14(0.0f),
		unknown18(0.0f),
		unknown1C(0.0f),
		flag(false)
	{
	}

	// FUNCTION: ENGINE 0x10864E30
	SplineCV::~SplineCV()
	{
	}

	// FUNCTION: ENGINE 0x10864D40
	content::ClassInfo* SplineBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::SplineBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}
}
