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
#include "code/math/plane.h"
#include "code/math/vector.h"
#include "code/ravenphysics/context.h"

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
		ravenphysics::IntersectionFilter filter;
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
		// Where a cast starts from (0x58 bytes; members other than the transform are guesses)
		struct CastInput
		{
			CastInput();

			// Handed to the query (whose object to ignore, presumably)
			int unknown0;
			// The character's frame
			math::Matrix transform;
			// The cast direction in the world (default down)
			math::Vector down;
			// How far behind the origin the ray starts
			float startOffset;
			// Added to the definition's maximum length
			float extraLength;
		};

		// What a cast found (0x28 bytes)
		struct CastResult
		{
			CastResult();

			// The point hit, moved back by the offset of the cast origin from the limb's origin
			math::Vector position;
			math::Vector normal;
			// From the ray start (less the start offset)
			float distance;
			int unknown1C;
			int unknown20;
			unsigned char material;
		};

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
		// The cast direction back to the definition's (through m when the definition says so), the basis and an
		// identity transform
		void ResetDirection(const math::Matrix& m);
		// The plane facing back along the cast direction (rotated by m) through the end of the limb at its current
		// length (unknown68)
		void GetSupportPlane(const math::Matrix& m, math::Plane& plane) const;
		// The nearest supporting hit along the cast from origin (in the limb's frame) no farther than maxDistance
		bool CastRay(const CastInput& input, const math::Vector& origin, float maxDistance, CastResult& result);
		// A cast from the definition's origin, or from each random ray around it (keeping the nearest, whose index
		// goes to rayIndex) when the definition has them and rayIndex is given
		bool Cast(const CastInput& input, CastResult& result, int* rayIndex);
		bool Cast(const CastInput& input, CastResult& result);

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
