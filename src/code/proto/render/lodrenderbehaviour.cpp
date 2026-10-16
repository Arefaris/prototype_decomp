// proto::LODRenderBehaviour: see the header. The file name and the member names are guesses.
#include <math.h>

#include "code/engine/camera/camera.h"
#include "code/engine/camera/director.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/math/mathutils.h"
#include "code/proto/render/lodrenderbehaviour.h"

namespace proto
{
	// FUNCTION: ENGINE 0x102DA540
	// NONMATCHING: the engine computes the three coordinate differences in SSE and spills them for the x87 sum; this
	// compiler evaluates the whole expression on the x87 stack (same values and order, 28 %)
#ifdef NONMATCHING
	void LODRenderBehaviour::UpdateFade()
	{
		fade = 1.0f;
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
		float dz = transform.m[3][2] - camera->position.z;
		float dy = transform.m[3][1] - camera->position.y;
		float dx = transform.m[3][0] - camera->position.x;
		float distance = sqrtf(dz * dz + dy * dy + dx * dx);
		float scale = gLODDetailScale->GetScale(camera);
		float divisor = scale > 1.0f ? scale : 1.0f;
		float value = fadeScale * gLODDistanceScale * (distance / divisor);
		const LODRange& range = gLODRanges[distanceLevel];
		float clamped = math::Clamp(value, range.minimum, range.maximum);
		fade = 1.0f - (clamped - range.minimum) / (range.maximum - range.minimum);
		fade = math::Clamp(fade, 0.0f, 1.0f);
	}
#endif

	// FUNCTION: ENGINE 0x102DA700
	void LODRenderBehaviour::UpdateLevel()
	{
		unsigned int wanted = 0;
		if ((flags & 1) != 0 && readyBegin != readyEnd)
		{
			unsigned int size = (levelsEnd - levelsBegin) >> 3;
			float t = math::Clamp(fade, 0.0f, 1.0f);
			wanted = (unsigned int)((1.0f - t) * (float)(unsigned int)(size - 1));
		}
		unsigned int previous = level;
		if (wanted != previous)
		{
			level = wanted;
			unsigned int last = wanted >= minimumLevels ? wanted : minimumLevels;
			ChangeDrawableLevels(previous, levelsBegin + wanted * 8, levelsBegin + last * 8);
		}
	}
}
