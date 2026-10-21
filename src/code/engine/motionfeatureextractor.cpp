#include "code/engine/motionfeatureextractor.h"

namespace engine
{
#define ENGINE_EXTRACTOR_INFO(Class, Name) \
	content::ClassInfo* Class::GetClassInfo() \
	{ \
		static content::ClassInfo sInfo; \
		sInfo.version = 1; \
		sInfo.name = Name; \
		sInfo.code = "pn"; \
		return &sInfo; \
	}

	// FUNCTION: ENGINE 0x10914AB0
	ENGINE_EXTRACTOR_INFO(MotionFeatureExtractor, "engine::MotionFeatureExtractor")

	// FUNCTION: ENGINE 0x10914AF0
	content::MemberList* MotionFeatureExtractor::GetMembers()
	{
		static content::MemberList sList;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10914B20
	ENGINE_EXTRACTOR_INFO(ProjectedMotionFeatureExtractor, "engine::ProjectedMotionFeatureExtractor")

	// FUNCTION: ENGINE 0x10914B60
	ENGINE_EXTRACTOR_INFO(LinearDisplacementExtractor, "engine::LinearDisplacementExtractor")

	// FUNCTION: ENGINE 0x10914BA0
	ENGINE_EXTRACTOR_INFO(LinearSpeedExtractor, "engine::LinearSpeedExtractor")

	// FUNCTION: ENGINE 0x10914BE0
	ENGINE_EXTRACTOR_INFO(LinearAccelerationExtractor, "engine::LinearAccelerationExtractor")

	// FUNCTION: ENGINE 0x10914C20
	ENGINE_EXTRACTOR_INFO(AngularDisplacementExtractor, "engine::AngularDisplacementExtractor")

	// FUNCTION: ENGINE 0x10914C60
	ENGINE_EXTRACTOR_INFO(AngularSpeedExtractor, "engine::AngularSpeedExtractor")

	// FUNCTION: ENGINE 0x10914CA0
	ENGINE_EXTRACTOR_INFO(AngularAccelerationExtractor, "engine::AngularAccelerationExtractor")

	// FUNCTION: ENGINE 0x10914CF0
	// EQUIVALENT: the last product's operands are loaded the other way round (a product commutes), 95.9 %
	float LinearDisplacementExtractor::Extract(const MotionState& current, const math::Matrix& root,
		const MotionState& previous)
	{
		math::Vector axis;
		math::Vector difference;
		math::Vector previousPosition(previous.transform.m[3][0], previous.transform.m[3][1], previous.transform.m[3][2]);
		math::Vector currentPosition(current.transform.m[3][0], current.transform.m[3][1], current.transform.m[3][2]);
		difference.x = currentPosition.x - previousPosition.x;
		difference.y = currentPosition.y - previousPosition.y;
		difference.z = currentPosition.z - previousPosition.z;
		root.Rotate(rootSpaceProjectionAxis, axis);
		return axis.z * difference.z + axis.y * difference.y + axis.x * difference.x;
	}

	// FUNCTION: ENGINE 0x10914D70
	float LinearSpeedExtractor::Extract(const MotionState& current, const math::Matrix& root,
		const MotionState& previous)
	{
		math::Vector axis;
		root.Rotate(rootSpaceProjectionAxis, axis);
		return current.linearVelocity.x * axis.x + current.linearVelocity.z * axis.z
			+ current.linearVelocity.y * axis.y;
	}

	// FUNCTION: ENGINE 0x10914DB0
	float LinearAccelerationExtractor::Extract(const MotionState& current, const math::Matrix& root,
		const MotionState& previous)
	{
		math::Vector axis;
		root.Rotate(rootSpaceProjectionAxis, axis);
		return current.linearAcceleration.x * axis.x + current.linearAcceleration.z * axis.z
			+ current.linearAcceleration.y * axis.y;
	}

	// FUNCTION: ENGINE 0x10914DF0
	float AngularDisplacementExtractor::Extract(const MotionState& current, const math::Matrix& root,
		const MotionState& previous)
	{
		math::Vector delta;
		float angle;
		GetRotationDelta(previous.transform, current.transform, delta, angle);
		math::Vector axis;
		root.Rotate(rootSpaceProjectionAxis, axis);
		return (delta.z * axis.z + delta.x * axis.x + axis.y * delta.y) * angle;
	}

	// FUNCTION: ENGINE 0x10914E50
	float AngularSpeedExtractor::Extract(const MotionState& current, const math::Matrix& root,
		const MotionState& previous)
	{
		math::Vector axis;
		root.Rotate(rootSpaceProjectionAxis, axis);
		return current.angularVelocity.x * axis.x + current.angularVelocity.z * axis.z
			+ current.angularVelocity.y * axis.y;
	}

	// FUNCTION: ENGINE 0x10914E90
	float AngularAccelerationExtractor::Extract(const MotionState& current, const math::Matrix& root,
		const MotionState& previous)
	{
		math::Vector axis;
		root.Rotate(rootSpaceProjectionAxis, axis);
		return current.angularAcceleration.x * axis.x + current.angularAcceleration.z * axis.z
			+ current.angularAcceleration.y * axis.y;
	}

	// FUNCTION: ENGINE 0x10914F00
	ProjectedMotionFeatureExtractor::ProjectedMotionFeatureExtractor()
	{
		rootSpaceProjectionAxis.x = 0.0f;
		rootSpaceProjectionAxis.y = 1.0f;
		rootSpaceProjectionAxis.z = 0.0f;
	}

	// FUNCTION: ENGINE 0x10915110
	content::MemberList* ProjectedMotionFeatureExtractor::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<MotionFeatureExtractor>();
		static content::BaseClassCasterImpl<MotionFeatureExtractor, ProjectedMotionFeatureExtractor> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<ProjectedMotionFeatureExtractor, 0>("pn"), 4,
				"rootSpaceProjectionAxis" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

#define ENGINE_EXTRACTOR_MEMBERS(Class) \
	content::MemberList* Class::GetMembers() \
	{ \
		static content::MemberList sList; \
		sList.baseType = content::GetClassMetaType<ProjectedMotionFeatureExtractor>(); \
		static content::BaseClassCasterImpl<ProjectedMotionFeatureExtractor, Class> sCaster; \
		sList.baseCaster = &sCaster; \
		return &sList; \
	}

	// FUNCTION: ENGINE 0x10915210
	ENGINE_EXTRACTOR_MEMBERS(LinearDisplacementExtractor)

	// FUNCTION: ENGINE 0x10915270
	ENGINE_EXTRACTOR_MEMBERS(LinearSpeedExtractor)

	// FUNCTION: ENGINE 0x109152D0
	ENGINE_EXTRACTOR_MEMBERS(LinearAccelerationExtractor)

	// FUNCTION: ENGINE 0x10915330
	ENGINE_EXTRACTOR_MEMBERS(AngularDisplacementExtractor)

	// FUNCTION: ENGINE 0x10915390
	ENGINE_EXTRACTOR_MEMBERS(AngularSpeedExtractor)

	// FUNCTION: ENGINE 0x109153F0
	ENGINE_EXTRACTOR_MEMBERS(AngularAccelerationExtractor)
}


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10914CE0
// FUNCTION: ENGINE 0x10914ED0
// FUNCTION: ENGINE 0x10914F30
// FUNCTION: ENGINE 0x10914F40
// FUNCTION: ENGINE 0x10914F70
// FUNCTION: ENGINE 0x10914F80
// FUNCTION: ENGINE 0x10914FB0
// FUNCTION: ENGINE 0x10914FC0
// FUNCTION: ENGINE 0x10914FF0
// FUNCTION: ENGINE 0x10915000
// FUNCTION: ENGINE 0x10915030
// FUNCTION: ENGINE 0x10915040
// FUNCTION: ENGINE 0x10915070
// FUNCTION: ENGINE 0x10915080
// FUNCTION: ENGINE 0x109150B0
// FUNCTION: ENGINE 0x109150C0
// FUNCTION: ENGINE 0x109151C0
