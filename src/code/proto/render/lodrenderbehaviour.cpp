// proto::LODRenderBehaviour: see the header. The file name and the member names are guesses.
#include <math.h>

#include "code/engine/camera/camera.h"
#include "code/engine/camera/director.h"
#include "code/core/heap.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/math/random.h"
#include "code/pure3d/primitive.h"
#include "code/math/mathutils.h"
#include "code/proto/render/lodrenderbehaviour.h"

namespace proto
{
	inline float LengthOf(const math::Vector& v)
	{
		return sqrtf(v.z * v.z + v.y * v.y + v.x * v.x);
	}

	// FUNCTION: ENGINE 0x102DA540
	void LODRenderBehaviour::UpdateFade()
	{
		// Reset through a reference: the store then stays ahead of the load and compare of the ready range
		float& reset = fade;
		reset = 1.0f;
		if (readyBegin == readyEnd)
		{
			return;
		}
		// The Director hands out the word at the camera's +0x40, which is itself a camera (name guess)
		engine::camera::Camera* camera =
			(engine::camera::Camera*)engine::camera::Director::Get()->GetCameraUnknown40(0, 0);
		if (camera == 0)
		{
			return;
		}
		const math::Matrix& transform = owner->transform->value;
		math::Vector position;
		transform.GetTranslation(position);
		math::Vector delta;
		math::Vector cameraPosition = camera->position;
		delta.Sub(position, cameraPosition);
		float distance = LengthOf(delta);
		float scale = gLODDetailScale->GetScale(camera);
		float divisor = scale > 1.0f ? scale : 1.0f;
		float scaled = fadeScale * gLODDistanceScale;
		float value = scaled * (distance / divisor);
		float clamped = math::Clamp(value, gLODRanges[distanceLevel].minimum, gLODRanges[distanceLevel].maximum);
		fade = 1.0f - (clamped - gLODRanges[distanceLevel].minimum) /
			(gLODRanges[distanceLevel].maximum - gLODRanges[distanceLevel].minimum);
		fade = math::Clamp(fade, 0.0f, 1.0f);
	}

	// FUNCTION: ENGINE 0x102DA700
	void LODRenderBehaviour::UpdateLevel()
	{
		unsigned int wanted = 0;
		if ((flags & 1) != 0 && readyBegin != readyEnd)
		{
			unsigned int size = levelsEnd - levelsBegin;
			float t = math::Clamp(fade, 0.0f, 1.0f);
			wanted = (unsigned int)((1.0f - t) * (float)(unsigned int)(size - 1));
		}
		unsigned int previous = level;
		if (wanted != previous)
		{
			level = wanted;
			unsigned int last = wanted >= minimumLevels ? wanted : minimumLevels;
			ChangeDrawableLevels(previous, levelsBegin + wanted, levelsBegin + last);
		}
	}

	// The first update: the entry of the shader palette is picked and every level gets its drawable bound
	// FUNCTION: ENGINE 0x102DC5F0
	// EQUIVALENT: scheduling (79.4 %): the half extents of the first ready drawable are subtracted, halved, squared and
	// summed in the engine's order (z, y, x); this compiler only stores the distance level earlier and picks other
	// registers
	// Storing the distance level after the half diagonal gives the engine's store (its zero shared with the loop), but the
	// ready / level tests and the joint loop then still use other registers (60 %).
	inline float HalfDiagonal(const math::AABB& box)
	{
		math::Vector half;
		half.Sub(box.max, box.min);
		half.x *= 0.5f;
		half.y *= 0.5f;
		half.z *= 0.5f;
		return LengthOf(half);
	}

	void LODRenderBehaviour::Slot1()
	{
		ShaderPaletteData* entry = 0;
		availableIndex = -1;
		if (available != 0 && available->data.begin != available->data.end)
		{
			availableIndex = math::gRandom->Range(0, available->data.Size() - 1);
			entry = &available->data.begin[availableIndex];
			Listen(0x16, true);
		}
		if ((flags & 8) == 0)
		{
			for (unsigned int i = 0; i < (unsigned int)(readyEnd - readyBegin); i++)
			{
				AddLevel(readyBegin + i);
			}
			for (unsigned int i = 0; i < (unsigned int)(levelsEnd - levelsBegin); i++)
			{
				LODLevel* item = levelsBegin + i;
				if (entry != 0)
				{
					pure3d::pddiShaderInputInitData inputs;
					entry->FillShaderInputs(&inputs);
					item->drawable.CreateBindings(inputs);
					item->ApplyPalette(entry);
				}
				if (animation != 0)
				{
					item->drawable.PlayAnimation(animation, 1.0f, 0.0f, 0.0f, animation->numFrames,
						pure3d::Animation::CYCLE_MODE_2);
				}
			}
			if (readyBegin != readyEnd && levelsBegin != levelsEnd)
			{
				const math::AABB* box = readyBegin->source->GetBounds();
				distanceLevel = 0;
				float length = HalfDiagonal(*box);
				for (int i = 0; i < 3; i++)
				{
					if (length < gLODDistances[i])
					{
						distanceLevel = i;
						break;
					}
				}
			}
		}
		int count = levelsEnd - levelsBegin;
		if (count != 0)
		{
			unsigned int joints = 0;
			for (int i = 0; i < count; i++)
			{
				pure3d::Skeleton* skeleton = levelsBegin[i].drawable.GetSkeleton();
				if (skeleton != 0 && skeleton->mData.mJointCount > joints)
				{
					joints = skeleton->mData.mJointCount;
				}
			}
			core::HeapScope scope(heap);
			boneData = pure3d::AllocateBoneData(joints, &boneDataSize, 3);
		}
	}

	// FUNCTION: ENGINE 0x102DAF80
	void LODRenderBehaviour::Update(float dt, unsigned short mask)
	{
		math::Matrix matrix = owner->transform->value;
		if (scaleSource != 0)
		{
			LODScaleSource* source = scaleSource;
			math::Matrix scale = math::Matrix::IDENTITY;
			scale.Scale(source->scale.x, source->scale.y, source->scale.z);
			matrix.Multiply(scale, matrix);
		}
		if (shownFirst != 0)
		{
			shownFirst->drawable.SetTransform(matrix);
			if (shownFirst != shownLast)
			{
				shownLast->drawable.SetTransform(matrix);
			}
		}
		if (1.0f != fadeInPosition || 1.0f != fadeInTarget)
		{
			UpdateFadeIn(dt);
		}
		if ((flags & 4) != 0)
		{
			forcedFirst->drawable.SetTransform(matrix);
			if (forcedFirst != forcedLast)
			{
				forcedLast->drawable.SetTransform(matrix);
			}
			UpdateForced(dt);
		}
		else
		{
			if ((flags & 1) != 0)
			{
				UpdateFade();
			}
			UpdateLevel();
		}
		if (poseSource != 0)
		{
			pure3d::Pose* pose = poseSource->pose;
			if (pose != 0)
			{
				pose->Update();
				shownFirst->drawable.CopyPoseStateFrom(pose);
			}
		}
	}
}
