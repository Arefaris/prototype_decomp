// engine::SecondaryPhysicsProperties (RTTI and reflection names): a content library object that describes the
// secondary physics of an object, the physics of the parts that follow the main motion (cloth, tails, antennas): per
// joint a collision volume (sphere, capsule, cylinder or box with its centre and orientation), the mass properties
// to take, whether gravity acts on it and the drivers that move it (see secondaryphysicsjoints.h), plus the data
// the debug display draws. Unit 0x1090DDD0 - 0x10910550 (no assert path; the directory and file name are guesses).
// The reflected member names are original; the rest is guessed.
#ifndef ENGINE_SECONDARYPHYSICSPROPERTIES_H
#define ENGINE_SECONDARYPHYSICSPROPERTIES_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/container/arraydynamicstatic.h"
#include "code/content/enummetatype.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/content/vectormetatype.h"
#include "code/core/name.h"
#include "code/engine/secondaryphysicsjoints.h"
#include "code/math/matrix.h"
#include "code/math/vector.h"
#include "code/pure3d/loaders/loader1067f4d0.h"
#include "code/pure3d/pose.h"
#include "code/ravenphysics/massproperties.h"

namespace engine
{
	class SecondaryPhysicsProperties : public content::MetaLoadObject
	{
	public:
		// What the volume of a joint is
		enum VolumeType
		{
			VOLUME_SPHERE = 0,
			VOLUME_CAPSULE = 1,
			VOLUME_CYLINDER = 2,
			VOLUME_OBB = 3
		};

		// The order the three angles of a joint's orientation are applied in
		enum RotationType
		{
			ROTATION_XYZ = 0,
			ROTATION_YZX = 1,
			ROTATION_ZXY = 2
		};

		typedef container::ArrayDynamic<SecondaryPhysicsJointDriver*, container::AllocatorNew> DriverArray;

		// How a joint's volume is drawn when the debug display is on (0x14 bytes)
		struct DebugDisplayData
		{
			// 0x1090E0A0
			DebugDisplayData();

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			math::Vector displayOffset;  // +0
			float displayScale;  // +0xC
			bool drawXAxisInRed;  // +0x10
			bool drawYAxisInGreen;  // +0x11
			bool drawZAxisInBlue;  // +0x12
		};

		// One joint with a volume (0xA0 bytes)
		struct JointData
		{
			// 0x1090FE60
			JointData();
			// 0x1090FED0 (deletes the drivers)
			~JointData();

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// 0x1090DF50: the index of the joint in a skeleton, or 0xFFFF without one
			int FindJoint(const pure3d::Skeleton* skeleton) const;
			// 0x1090DF70
			const core::Name<core::CaseSensitiveKey>* GetJointName() const
			{
				return &jointName;
			}
			// 0x1090DF80 / 0x1090DF90 / 0x1090DFA0 / 0x1090DFB0
			ravenphysics::MassProperties* GetMassProperties() const
			{
				return massProperties;
			}
			bool IsGravityEnabled() const
			{
				return gravityEnabled;
			}
			const math::Vector* GetRotationAnglesDegrees() const
			{
				return &rotationAnglesDegrees;
			}
			RotationType GetRotationType() const
			{
				return rotationType;
			}
			// 0x1090E7E0 / 0x1090E810: both rebuild the orientation matrix
			void SetRotationAnglesDegrees(const math::Vector* degrees);
			void SetRotationType(RotationType type);
			// 0x1090DFC0: the orientation matrix from the angles in the order of the rotation type
			void UpdateRotation();
			// 0x1090E480: whether the joint has a driver
			bool HasDrivers() const;
			// 0x1090E4A0: how many constraint handles all drivers need
			int GetHandleCount() const;
			// 0x1090E4D0: hands every driver its run of the handle range (the handles are set to fresh constraints)
			void CreateConstraints(SecondaryPhysicsHandleRange* range);
			// 0x1090E7A0: lets every driver act on the shape
			void ApplyDrivers(ravenphysics::CollisionShape* shape, const math::Matrix* matrix);

			__declspec(align(8)) core::Name<core::CaseSensitiveKey> jointName;  // +0
			DriverArray jointDrivers;  // +8
			// The word behind the array (the arrays of this kind are followed by one; never touched here)
			int unknown14;  // +0x14
			ravenphysics::MassProperties* massProperties;  // +0x18
			bool gravityEnabled;  // +0x1C
			VolumeType volumeType;  // +0x20
			float radius;  // +0x24
			math::Vector centerOffset;  // +0x28
			float halfLength;  // +0x34
			RotationType rotationType;  // +0x38
			math::Matrix rotation;  // +0x3C
			math::Vector rotationAnglesDegrees;  // +0x7C
			DebugDisplayData debugDisplay;  // +0x88
		};

		typedef container::ArrayDynamic<JointData, container::AllocatorNew> JointArray;

		// 0x109103D0
		SecondaryPhysicsProperties();
		// 0x10910430 (deleting destructor 0x10910530)
		virtual ~SecondaryPhysicsProperties();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 5 (0x1090F470): makes the physics objects of the joints
		virtual bool Slot5();
		// vftable slot 6 (0x1090E0D0): the name is not kept
		virtual void SetName(const core::Name<core::CaseSensitiveKey>& name);

		pure3d::Loaded1066F430* physicsData;  // +8
		JointArray joints;  // +0xC
		// The word behind the array (the arrays of this kind are followed by one; never touched here)
		int unknown18;  // +0x18
	};
}

namespace container
{
	// The joints are too large for the compiler to inline the assignment of their elements
	template<> struct ArrayEraseInline<engine::SecondaryPhysicsProperties::JointData>
	{
		enum
		{
			value = 0
		};
	};
}

#endif
