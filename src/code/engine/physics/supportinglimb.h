// engine::SupportingLimbDefinition, engine::SupportingLimbDefinitionList and engine::SupportingLimb (RTTI and
// reflection names): a character's supporting limbs (feet on the ground, hands on walls), each a ray or sphere cast
// from the character along a direction that finds the supporting surface. Unit 0x107F2970 - 0x107F66E0 (no assert
// path; the directory and file name are guesses). The reflected member names are original; others are guesses.
#ifndef ENGINE_PHYSICS_SUPPORTINGLIMB_H
#define ENGINE_PHYSICS_SUPPORTINGLIMB_H

#include "code/container/arraycdynamic.h"
#include "code/container/arraydynamicnew.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/core/refptr.h"
#include "code/math/matrix.h"
#include "code/math/vector.h"

namespace ravenphysics
{
	// What a query collides with (0x10653860 constructs it from the physics library's defaults; meanings unknown)
	struct IntersectionProperties
	{
		IntersectionProperties();

		int unknown0;
		int unknown4;
	};

	// ravenphysics::IntersectionPropertiesLoader (RTTI; a load object of the physics library)
	class IntersectionPropertiesLoader : public content::LoadObject
	{
	public:
		unsigned char unknown8[0x3c - 8];
		int unknown3C;
		int unknown40;
	};
}

namespace engine
{
	class SupportingLimbDefinition : public content::MetaLoadObject
	{
	public:
		// Which axis of the character a limb orientation follows
		enum ORIENTATION_AXIS
		{
			None = -1,
			PositiveX,
			PositiveY,
			PositiveZ,
			NegativeX,
			NegativeY,
			NegativeZ
		};

		// How fast the limb may follow the surface at a character velocity: a piecewise linear map
		class SmoothingVelocityMap
		{
		public:
			struct Entry
			{
				static content::ClassInfo* GetClassInfo();
				static content::MemberList* GetMembers();

				Entry()
				{
					characterVelocity = 1.0f;
					smoothingVelocity = 1.0f;
				}

				float characterVelocity;
				float smoothingVelocity;
			};

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			bool IsEmpty() const
			{
				return map.IsEmpty();
			}
			// True when the character velocities rise
			bool IsSorted() const;
			// The smoothing velocity at characterVelocity
			float Evaluate(float characterVelocity) const;

			container::ArrayCDynamic<Entry, 3> map;
		};

		SupportingLimbDefinition();
		virtual ~SupportingLimbDefinition();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// Slot 3: takes the loader's intersection properties
		virtual void Slot3(int unused);

		core::Name<core::CaseSensitiveKey> name;
		float sphereRadius;
		ravenphysics::IntersectionProperties properties;
		int unknown1C;
		ravenphysics::IntersectionPropertiesLoader* intersectionProperties;
		math::Vector origin;
		math::Vector direction;
		float restingLength;
		float maxLength;
		float cosineSupportAngleTolerance;
		bool directionFollowsSurfaceNormal;
		bool smoothDirection;
		bool smoothRestingLength;
		ORIENTATION_AXIS characterSurfaceOrientation;
		ORIENTATION_AXIS characterUpVectorOrientation;
		float smoothMaxLinearVelocity;
		float smoothFractionalMaxLinearVelocity;
		SmoothingVelocityMap smoothMaxLinearVelocityMap;
		float smoothMaxAngularVelocity;
		float smoothMinRestingLength;
		float smoothMaxRestingLength;
		unsigned int numRandomRays;
		float randomRayCircleRadius;
	};

	class SupportingLimbDefinitionList : public content::MetaLoadObject
	{
	public:
		SupportingLimbDefinitionList();
		virtual ~SupportingLimbDefinitionList();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		container::ArrayDynamicNew<SupportingLimbDefinition*> limbDefs;
	};

	// One limb of a character: its definition and the state of its cast
	class SupportingLimb
	{
	public:
		// One of the random rays around the limb's direction (angle and fraction of the circle radius)
		struct RandomRay
		{
			RandomRay();

			float angle;
			float radius;
			bool active;
		};

		SupportingLimb();
		SupportingLimb(const SupportingLimb& other);
		~SupportingLimb();
		SupportingLimb& operator=(const SupportingLimb& other);

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// Inline; its copy is in another unit (0x100ECB50)
		SupportingLimbDefinition* GetDefinition() const
		{
			return limbDef;
		}
		void SetDefinition(SupportingLimbDefinition* definition);
		void Swap(SupportingLimb& other);
		// Recomputes the two directions perpendicular to the cast direction
		void UpdateBasis();

		SupportingLimbDefinition* limbDef;
		math::Vector castDirection;
		math::Vector basisU;
		math::Vector basisV;
		math::Matrix transform;
		float unknown68;
		float unknown6C;
		bool unknown70;
		container::ArrayCDynamic<RandomRay, 4> rays;
	};
}

#endif
