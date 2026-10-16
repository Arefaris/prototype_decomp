// proto::LODRenderBehaviour: see the header. The file name and the member names are guesses.
#include <math.h>

#include "code/engine/camera/camera.h"
#include "code/engine/camera/director.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/math/mathutils.h"
#include "code/proto/render/lodrenderbehaviour.h"

namespace proto
{
	inline float LengthOf(const math::Vector& v)
	{
		return sqrtf(v.z * v.z + v.y * v.y + v.x * v.x);
	}

	// FUNCTION: ENGINE 0x102DA540
	// EQUIVALENT: scheduling: the engine issues the store of the fade of 1.0 before the load and compare of the ready
	// range, this compiler after them (97.1 %)
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
