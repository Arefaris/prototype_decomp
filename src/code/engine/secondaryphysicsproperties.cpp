#include "code/engine/secondaryphysicsproperties.h"
#include "code/core/refptr.h"
#include <new>

namespace math
{
	// The zero vector (another unit's constant)
	extern const Vector kZeroVector;
}

namespace content
{
	static const EnumValue sVolumeTypeValues[] =
	{
		{ "Sphere", 0 },
		{ "Capsule", 1 },
		{ "Cylinder", 2 },
		{ "OBB", 3 }
	};

	static const EnumValue sRotationTypeValues[] =
	{
		{ "XYZ", 0 },
		{ "YZX", 1 },
		{ "ZXY", 2 }
	};

	// FUNCTION: ENGINE 0x1090DE30
	template<> void EnumInfo<engine::SecondaryPhysicsProperties::VolumeType>::Get(const char** name,
		const EnumValue** values, int* count, const char** code)
	{
		*name = "engine::SecondaryPhysicsProperties::JointData::VolumeType";
		*code = "pn";
		*values = sVolumeTypeValues;
		*count = 4;
	}

	// FUNCTION: ENGINE 0x1090DE60
	template<> void EnumInfo<engine::SecondaryPhysicsProperties::RotationType>::Get(const char** name,
		const EnumValue** values, int* count, const char** code)
	{
		*name = "engine::SecondaryPhysicsProperties::JointData::RotationType";
		*code = "pn";
		*values = sRotationTypeValues;
		*count = 3;
	}
}

namespace engine
{
	typedef SecondaryPhysicsProperties Properties;

#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define ENGINE_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x1090E0A0
	Properties::DebugDisplayData::DebugDisplayData()
	{
		displayOffset.x = 0.0f;
		displayOffset.y = 0.0f;
		displayOffset.z = 0.0f;
		displayScale = 0.2f;
		drawXAxisInRed = true;
		drawYAxisInGreen = true;
		drawZAxisInBlue = true;
	}

	// FUNCTION: ENGINE 0x1090DE90
	content::ClassInfo* Properties::DebugDisplayData::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::SecondaryPhysicsProperties::JointData::DebugDisplayData";
		sInfo.code = "";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1090DED0
	content::ClassInfo* Properties::JointData::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::SecondaryPhysicsProperties::JointData";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1090DF10
	content::ClassInfo* Properties::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::SecondaryPhysicsProperties";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1090DF50
	int Properties::JointData::FindJoint(const pure3d::Skeleton* skeleton) const
	{
		int result = 0xffff;
		if (skeleton != 0)
		{
			result = skeleton->FindJoint(jointName);
		}
		return result;
	}

	// FUNCTION: ENGINE 0x1090DFC0
	void Properties::JointData::UpdateRotation()
	{
		math::Vector angles;
		angles.x = rotationAnglesDegrees.x * 0.0174532924f;
		angles.y = rotationAnglesDegrees.y * 0.0174532924f;
		angles.z = rotationAnglesDegrees.z * 0.0174532924f;
		float x = angles.x;
		float y = angles.y;
		float z = angles.z;
		rotation.Identity();
		switch (rotationType)
		{
			case ROTATION_XYZ:
				rotation.RotationEulerXYZ(x, y, z);
				break;
			case ROTATION_YZX:
				rotation.RotationEulerYZX(x, y, z);
				break;
			case ROTATION_ZXY:
				rotation.RotationEulerZXY(x, y, z);
				break;
		}
	}

	// FUNCTION: ENGINE 0x1090E480
	bool Properties::JointData::HasDrivers() const
	{
		SecondaryPhysicsJointDriver** last = jointDrivers.end;
		bool result = false;
		for (SecondaryPhysicsJointDriver** driver = jointDrivers.begin; driver != last; driver++)
		{
			if (*driver != 0)
			{
				result = true;
				break;
			}
		}
		return result;
	}

	// FUNCTION: ENGINE 0x1090E4A0
	int Properties::JointData::GetHandleCount() const
	{
		SecondaryPhysicsJointDriver** last = jointDrivers.end;
		int count = 0;
		for (SecondaryPhysicsJointDriver** driver = jointDrivers.begin; driver != last; driver++)
		{
			if (*driver != 0)
			{
				count += (*driver)->GetHandleCount();
			}
		}
		return count;
	}

	// FUNCTION: ENGINE 0x1090E7A0
	void Properties::JointData::ApplyDrivers(ravenphysics::CollisionShape* shape, const math::Matrix* matrix)
	{
		SecondaryPhysicsJointDriver** last = jointDrivers.end;
		for (SecondaryPhysicsJointDriver** driver = jointDrivers.begin; driver != last; driver++)
		{
			if (*driver != 0)
			{
				(*driver)->Slot5(shape, matrix);
			}
		}
	}

	// FUNCTION: ENGINE 0x1090E7E0
	void Properties::JointData::SetRotationAnglesDegrees(const math::Vector* degrees)
	{
		rotationAnglesDegrees.x = degrees->x;
		rotationAnglesDegrees.y = degrees->y;
		rotationAnglesDegrees.z = degrees->z;
		UpdateRotation();
	}

	// FUNCTION: ENGINE 0x1090E810
	void Properties::JointData::SetRotationType(RotationType type)
	{
		rotationType = type;
		UpdateRotation();
	}

	// FUNCTION: ENGINE 0x1090F0E0
	content::MemberList* Properties::DebugDisplayData::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<DebugDisplayData, 0>("pn"), 0, "displayOffset" },
			{ content::GetMemberPrimitiveMetaType<DebugDisplayData, float, 0>("pn"),
				ENGINE_OFFSET(DebugDisplayData, displayScale), "displayScale" },
			{ content::GetMemberPrimitiveMetaType<DebugDisplayData, bool, 0>("pn"),
				ENGINE_OFFSET(DebugDisplayData, drawXAxisInRed), "drawXAxisInRed" },
			{ content::GetMemberPrimitiveMetaType<DebugDisplayData, bool, 1>("pn"),
				ENGINE_OFFSET(DebugDisplayData, drawYAxisInGreen), "drawYAxisInGreen" },
			{ content::GetMemberPrimitiveMetaType<DebugDisplayData, bool, 2>("pn"),
				ENGINE_OFFSET(DebugDisplayData, drawZAxisInBlue), "drawZAxisInBlue" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1090F9A0
	content::MemberList* Properties::JointData::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<JointData>(true, true, "pn"), ENGINE_NAME_OFFSET(JointData, jointName),
				"jointName" },
			{ content::GetArrayDynamicMetaType<JointData, DriverArray>(
				content::GetObjectMetaType<SecondaryPhysicsJointDriver>("pn"), "pn"),
				ENGINE_OFFSET(JointData, jointDrivers), "jointDrivers" },
			{ content::GetReferenceMetaType<JointData, ravenphysics::MassProperties>("pn"),
				ENGINE_OFFSET(JointData, massProperties), "massProperties" },
			{ content::GetMemberPrimitiveMetaType<JointData, bool, 0>("pn"),
				ENGINE_OFFSET(JointData, gravityEnabled), "gravityEnabled" },
			{ content::GetEnumMetaType<VolumeType>(), 0x20, "volumeType" },
			{ content::GetMemberPrimitiveMetaType<JointData, float, 0>("pn"), ENGINE_OFFSET(JointData, radius),
				"radius" },
			{ content::GetMemberVectorMetaType<JointData, 0>("pn"), 0x28, "centerOffset" },
			{ content::GetMemberPrimitiveMetaType<JointData, float, 1>("pn"), ENGINE_OFFSET(JointData, halfLength),
				"halfLength" },
			{ content::GetMemberVectorMetaType<JointData, 1>(&JointData::GetRotationAnglesDegrees,
				&JointData::SetRotationAnglesDegrees, "pn"), 0, "rotationAnglesDegrees" },
			{ content::GetMemberEnumMetaType(&JointData::GetRotationType, &JointData::SetRotationType), 0,
				"rotationType" },
			{ content::GetClassMetaType<DebugDisplayData>(), ENGINE_OFFSET(JointData, debugDisplay),
				"debugDisplay" }
		};
		sList.members = sMembers;
		sList.count = 11;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1090FDD0
	content::MemberList* Properties::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<Properties, JointArray>(content::GetClassMetaType<JointData>(),
				"rpn"), ENGINE_OFFSET(Properties, joints), "joints" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1090FE60
	Properties::JointData::JointData() : massProperties(0), gravityEnabled(true), volumeType(VOLUME_SPHERE),
		radius(0.1f), centerOffset(0.0f, 0.0f, 0.0f), halfLength(0.2f), rotationType(ROTATION_XYZ)
	{
		SetRotationAnglesDegrees(&math::kZeroVector);
	}

	// FUNCTION: ENGINE 0x1090FED0
	Properties::JointData::~JointData()
	{
		SecondaryPhysicsJointDriver** last = jointDrivers.end;
		for (SecondaryPhysicsJointDriver** driver = jointDrivers.begin; driver != last; driver++)
		{
			if (*driver != 0)
			{
				delete *driver;
				*driver = 0;
			}
		}
		core::SafeRelease(massProperties);
	}

	// FUNCTION: ENGINE 0x109103D0
	// EQUIVALENT: the engine pushes edi after the first stores of the constructor, ours before them, 95.7 %
	Properties::SecondaryPhysicsProperties() : physicsData(0)
	{
		core::RefAssign(physicsData, new pure3d::Loaded1066F430);
	}

	// FUNCTION: ENGINE 0x10910430
	Properties::~SecondaryPhysicsProperties()
	{
		core::SafeRelease(physicsData);
	}

	// FUNCTION: ENGINE 0x1090E0D0
	void Properties::SetName(const core::Name<core::CaseSensitiveKey>& name)
	{
	}
}

namespace container
{
	template class ArrayDynamic<engine::SecondaryPhysicsJointDriver*, AllocatorNew>;
	template class ArrayDynamic<engine::SecondaryPhysicsProperties::JointData, AllocatorNew>;
}


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1090DFA0
// FUNCTION: ENGINE 0x1090DFB0
// FUNCTION: ENGINE 0x1090E0F0
// FUNCTION: ENGINE 0x1090E100
// FUNCTION: ENGINE 0x1090E110
// FUNCTION: ENGINE 0x1090E120
// FUNCTION: ENGINE 0x1090E170
// FUNCTION: ENGINE 0x1090E190
// FUNCTION: ENGINE 0x1090E230
// FUNCTION: ENGINE 0x1090E290
// FUNCTION: ENGINE 0x1090E2A0
// FUNCTION: ENGINE 0x1090E300
// FUNCTION: ENGINE 0x1090E310
// FUNCTION: ENGINE 0x1090E340
// FUNCTION: ENGINE 0x1090E380
// FUNCTION: ENGINE 0x1090E3A0
// FUNCTION: ENGINE 0x1090E3D0
// FUNCTION: ENGINE 0x1090E3E0
// FUNCTION: ENGINE 0x1090E3F0
// FUNCTION: ENGINE 0x1090E420
// FUNCTION: ENGINE 0x1090E8D0
// FUNCTION: ENGINE 0x1090E8E0
// FUNCTION: ENGINE 0x1090E8F0
// FUNCTION: ENGINE 0x1090E930
// FUNCTION: ENGINE 0x1090E970
// FUNCTION: ENGINE 0x1090E9B0
// FUNCTION: ENGINE 0x1090E9F0
// FUNCTION: ENGINE 0x1090EA30
// FUNCTION: ENGINE 0x1090EA70
// FUNCTION: ENGINE 0x1090EAC0
// FUNCTION: ENGINE 0x1090EAD0
// FUNCTION: ENGINE 0x1090EAF0
// FUNCTION: ENGINE 0x1090EB00
// FUNCTION: ENGINE 0x1090EB50
// FUNCTION: ENGINE 0x1090EB60
// FUNCTION: ENGINE 0x1090EB70
// FUNCTION: ENGINE 0x1090EB80
// FUNCTION: ENGINE 0x1090EB90
// FUNCTION: ENGINE 0x1090EBA0
// FUNCTION: ENGINE 0x1090EBC0
// FUNCTION: ENGINE 0x1090EBF0
// FUNCTION: ENGINE 0x1090EC20
// FUNCTION: ENGINE 0x1090EC30
// FUNCTION: ENGINE 0x1090EC50
// FUNCTION: ENGINE 0x1090ECA0
// FUNCTION: ENGINE 0x1090ECC0
// FUNCTION: ENGINE 0x1090ECD0
// FUNCTION: ENGINE 0x1090ECE0
// FUNCTION: ENGINE 0x1090ED60
// FUNCTION: ENGINE 0x1090ED90
// FUNCTION: ENGINE 0x1090EDC0
// FUNCTION: ENGINE 0x1090EDD0
// FUNCTION: ENGINE 0x1090EDE0
// FUNCTION: ENGINE 0x1090EDF0
// FUNCTION: ENGINE 0x1090EE00
// FUNCTION: ENGINE 0x1090EE20
// FUNCTION: ENGINE 0x1090EE30
// FUNCTION: ENGINE 0x1090EE50
// FUNCTION: ENGINE 0x1090EE70
// FUNCTION: ENGINE 0x1090EE80
// FUNCTION: ENGINE 0x1090EEA0
// FUNCTION: ENGINE 0x1090EEC0
// FUNCTION: ENGINE 0x1090EEE0
// FUNCTION: ENGINE 0x1090EF30
// FUNCTION: ENGINE 0x1090EF60
// FUNCTION: ENGINE 0x1090F4E0
// FUNCTION: ENGINE 0x1090F530
// FUNCTION: ENGINE 0x1090F540
// FUNCTION: ENGINE 0x1090F590
// FUNCTION: ENGINE 0x1090F5E0
// FUNCTION: ENGINE 0x1090F630
// FUNCTION: ENGINE 0x1090F6A0
// FUNCTION: ENGINE 0x1090F740
// FUNCTION: ENGINE 0x1090F790
// FUNCTION: ENGINE 0x1090F7D0
// FUNCTION: ENGINE 0x1090FBD0
// FUNCTION: ENGINE 0x1090FC20
// FUNCTION: ENGINE 0x1090FCA0
// FUNCTION: ENGINE 0x1090FF20
// FUNCTION: ENGINE 0x1090FFA0
// FUNCTION: ENGINE 0x1090FFE0
// FUNCTION: ENGINE 0x10910040
// FUNCTION: ENGINE 0x10910070
// FUNCTION: ENGINE 0x109100B0
// FUNCTION: ENGINE 0x10910100
// FUNCTION: ENGINE 0x10910150
// FUNCTION: ENGINE 0x10910190
// FUNCTION: ENGINE 0x109102B0
// FUNCTION: ENGINE 0x109102F0
// FUNCTION: ENGINE 0x10910330
// FUNCTION: ENGINE 0x10910390
// FUNCTION: ENGINE 0x10910480
