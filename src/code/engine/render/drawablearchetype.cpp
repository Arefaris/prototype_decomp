#include "code/engine/render/drawablearchetype.h"
#include "code/pure3d/drawable.h"
#include "code/pure3d/pose.h"

namespace engine
{
	namespace render
	{
		// FUNCTION: ENGINE 0x108258B0
		const core::Name<core::CaseSensitiveKey>* DrawableArchetype::GetName() const
		{
			return &drawable->mName;
		}

		// FUNCTION: ENGINE 0x108258C0
		bool DrawableArchetype::IsFlagged() const
		{
			return drawable->GetFlag100Bit3();
		}

		// FUNCTION: ENGINE 0x108258D0
		bool DrawableArchetype::HasFrameController() const
		{
			return hasFrameController;
		}

		// FUNCTION: ENGINE 0x10825910
		bool DrawableArchetype::IsCyclic() const
		{
			return cyclic;
		}

		// FUNCTION: ENGINE 0x10825920
		float DrawableArchetype::GetLength() const
		{
			return length;
		}

		// FUNCTION: ENGINE 0x10825930
		const math::AABB* DrawableArchetype::GetBounds() const
		{
			return &bounds;
		}

		// FUNCTION: ENGINE 0x10825940
		pure3d::DrawableSegment* DrawableArchetype::GetSegment(unsigned short segment)
		{
			return drawable->GetSegment(segment);
		}

		// FUNCTION: ENGINE 0x10825950
		void DrawableArchetype::GetSegmentParts(unsigned short segment, unsigned int* first, unsigned int* count)
		{
			drawable->GetSegmentParts(segment, first, count);
		}

		// FUNCTION: ENGINE 0x10825960
		pure3d::Pose* DrawableArchetype::CreatePoseInstance()
		{
			if (drawable->GetPose() != 0)
			{
				return drawable->GetPose()->CreateInstance(3);
			}
			if (drawable->GetSkeleton() != 0)
			{
				return drawable->GetSkeleton()->CreatePose(3);
			}
			return 0;
		}

		// FUNCTION: ENGINE 0x10825AD0
		int DrawableArchetype::GetSegmentCount()
		{
			return drawable->segments.Size();
		}
	}
}
