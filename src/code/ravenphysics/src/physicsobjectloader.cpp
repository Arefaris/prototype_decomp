// The loader of the physics content (RTTI: ravenphysics::PhysicsObjectLoader) and what it keeps in its lists: unit
// 0x1067C400 - 0x1067F800, no assert path, so the file name is a guess. Its chunk handler is in
// pure3d/loaders/loader1067f4d0.cpp.
#include "code/content/chunkhandler.h"
#include "code/ravenphysics/constraints/constraints.h"
#include <new>

namespace ravenphysics
{
	// The class meta types of the constraints (0x1065D3D0 - 0x1065DDD0, another unit: the engine keeps one instance of
	// each there; names guessed)
	content::ClassMetaType* GetBallInSocketMetaType();
	content::ClassMetaType* GetHingeMetaType();
	content::ClassMetaType* GetInsideOfConeMetaType();
	content::ClassMetaType* GetInsideOfSphereMetaType();
	content::ClassMetaType* GetAlign2AxesMetaType();
	content::ClassMetaType* GetSliderMetaType();
	content::ClassMetaType* GetSpringAlongAxisMetaType();
	content::ClassMetaType* GetAngularSpringMetaType();
	content::ClassMetaType* GetAngularVelocityMetaType();
	content::ClassMetaType* GetPerpendicular2AxesMetaType();

	// The creators of the constraints the loader reads: a new constraint of the kind and the meta type of its class
	// (names guessed)
	// FUNCTION: ENGINE 0x1067CA80
	void CreateBallInSocket(Constraint** object, content::ClassMetaType** type)
	{
		*object = new ConstraintBallInSocket;
		*type = GetBallInSocketMetaType();
	}

	// FUNCTION: ENGINE 0x1067CAC0
	void CreateHinge(Constraint** object, content::ClassMetaType** type)
	{
		*object = new ConstraintHinge;
		*type = GetHingeMetaType();
	}

	// FUNCTION: ENGINE 0x1067CB00
	void CreateInsideOfCone(Constraint** object, content::ClassMetaType** type)
	{
		*object = new ConstraintInsideOfCone;
		*type = GetInsideOfConeMetaType();
	}

	// FUNCTION: ENGINE 0x1067CB40
	void CreateInsideOfSphere(Constraint** object, content::ClassMetaType** type)
	{
		*object = new ConstraintInsideOfSphere;
		*type = GetInsideOfSphereMetaType();
	}

	// FUNCTION: ENGINE 0x1067CB80
	void CreateAlign2Axes(Constraint** object, content::ClassMetaType** type)
	{
		*object = new ConstraintAlign2Axes;
		*type = GetAlign2AxesMetaType();
	}

	// FUNCTION: ENGINE 0x1067CBC0
	void CreateSlider(Constraint** object, content::ClassMetaType** type)
	{
		*object = new ConstraintSlider;
		*type = GetSliderMetaType();
	}

	// FUNCTION: ENGINE 0x1067CC40
	void CreateSpringAlongAxis(Constraint** object, content::ClassMetaType** type)
	{
		*object = new ConstraintSpringAlongAxis;
		*type = GetSpringAlongAxisMetaType();
	}

	// FUNCTION: ENGINE 0x1067CC80
	void CreateAngularSpring(Constraint** object, content::ClassMetaType** type)
	{
		*object = new ConstraintAngularSpring;
		*type = GetAngularSpringMetaType();
	}

	// FUNCTION: ENGINE 0x1067CCC0
	void CreateAngularVelocity(Constraint** object, content::ClassMetaType** type)
	{
		*object = new ConstraintAngularVelocity;
		*type = GetAngularVelocityMetaType();
	}

	// FUNCTION: ENGINE 0x1067CD80
	void CreatePerpendicular2Axes(Constraint** object, content::ClassMetaType** type)
	{
		*object = new ConstraintPerpendicular2Axes;
		*type = GetPerpendicular2AxesMetaType();
	}
}

namespace content
{
	// FUNCTION: ENGINE 0x1067C400
	float ChunkStream::ReadFloat()
	{
		float value;
		Read(&value, 1, 4, 1);
		return value;
	}

	// FUNCTION: ENGINE 0x1067C420
	float ChunkReader::ReadFloat()
	{
		float value;
		Read(&value, 1, 4, 1);
		return value;
	}

	// FUNCTION: ENGINE 0x1067C440
	void ChunkReader::ReadVector(math::Vector* vector)
	{
		Read(vector, 3, 4, 1);
	}
}
