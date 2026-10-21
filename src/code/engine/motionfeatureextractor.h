// engine::MotionFeatureExtractor and its reflected extractors (RTTI and reflection names): a feature extractor reads
// one number off a tracked motion (the displacement, speed or acceleration of a body along or around an axis that is
// given in the space of a root transform). They are plain reflected classes (no content library base); the
// projected extractors share the axis they project onto. Unit 0x10914AB0 - 0x10915450 (no assert path; the directory
// and file name are guesses). The reflected member name is original; the other names are guesses.
#ifndef ENGINE_MOTIONFEATUREEXTRACTOR_H
#define ENGINE_MOTIONFEATUREEXTRACTOR_H

#include "code/content/metatype.h"
#include "code/engine/motiontrackingfilter.h"
#include "code/math/matrix.h"
#include "code/math/vector.h"

namespace engine
{
	// 0x107FE0F0 (another unit): the rotation from one transform to another as an axis and an angle
	void GetRotationDelta(const math::Matrix& from, const math::Matrix& to, math::Vector& axis, float& angle);

	class MotionFeatureExtractor
	{
	public:
		// 0x10914CE0
		MotionFeatureExtractor()
		{
		}
		virtual ~MotionFeatureExtractor()
		{
		}

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1: the number the extractor reads off the motion of current, with root as the space of the
		// axis and previous the state a step ago
		virtual float Extract(const MotionState& current, const math::Matrix& root, const MotionState& previous) = 0;
	};

	// The extractors that project onto an axis given in the root's space
	class ProjectedMotionFeatureExtractor : public MotionFeatureExtractor
	{
	public:
		// 0x10914F00
		ProjectedMotionFeatureExtractor();
		virtual ~ProjectedMotionFeatureExtractor()
		{
		}

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		math::Vector rootSpaceProjectionAxis;  // +4
	};

	class LinearDisplacementExtractor : public ProjectedMotionFeatureExtractor
	{
	public:
		virtual ~LinearDisplacementExtractor()
		{
		}
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
		// 0x10914CF0: the difference of the positions along the axis
		virtual float Extract(const MotionState& current, const math::Matrix& root, const MotionState& previous);
	};

	class LinearSpeedExtractor : public ProjectedMotionFeatureExtractor
	{
	public:
		virtual ~LinearSpeedExtractor()
		{
		}
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
		// 0x10914D70
		virtual float Extract(const MotionState& current, const math::Matrix& root, const MotionState& previous);
	};

	class LinearAccelerationExtractor : public ProjectedMotionFeatureExtractor
	{
	public:
		virtual ~LinearAccelerationExtractor()
		{
		}
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
		// 0x10914DB0
		virtual float Extract(const MotionState& current, const math::Matrix& root, const MotionState& previous);
	};

	class AngularDisplacementExtractor : public ProjectedMotionFeatureExtractor
	{
	public:
		virtual ~AngularDisplacementExtractor()
		{
		}
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
		// 0x10914DF0: the angle between the two orientations along the axis
		virtual float Extract(const MotionState& current, const math::Matrix& root, const MotionState& previous);
	};

	class AngularSpeedExtractor : public ProjectedMotionFeatureExtractor
	{
	public:
		virtual ~AngularSpeedExtractor()
		{
		}
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
		// 0x10914E50
		virtual float Extract(const MotionState& current, const math::Matrix& root, const MotionState& previous);
	};

	class AngularAccelerationExtractor : public ProjectedMotionFeatureExtractor
	{
	public:
		virtual ~AngularAccelerationExtractor()
		{
		}
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
		// 0x10914E90
		virtual float Extract(const MotionState& current, const math::Matrix& root, const MotionState& previous);
	};
}

#endif
