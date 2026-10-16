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
	// NONMATCHING: the engine materialises the three coordinate differences in SSE registers (it loads both
	// members of each pair and stores the difference to the vector's slot), our build keeps them on the x87 stack
	// and folds the camera's members into the fsub, 30 %. A Vector temporary, three float locals, the squares in
	// either order and the detail scale call before or after the distance all give the same x87 form.
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
		math::Vector difference(transform.m[3][0] - camera->position.x,
			transform.m[3][1] - camera->position.y, transform.m[3][2] - camera->position.z);
		float distance = sqrtf(difference.z * difference.z + difference.y * difference.y
			+ difference.x * difference.x);
		float scale = gLODDetailScale->GetScale(camera);
		float divisor = scale > 1.0f ? scale : 1.0f;
		float value = fadeScale * gLODDistanceScale * (distance / divisor);
		const LODRange& range = gLODRanges[distanceLevel];
		float clamped = math::Clamp(value, range.minimum, range.maximum);
		fade = math::Clamp(1.0f - (clamped - range.minimum) / (range.maximum - range.minimum), 0.0f, 1.0f);
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
