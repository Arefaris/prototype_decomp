// engine::camera::BlendCamera (RTTI name; base engine::camera::Camera): the camera that blends from one camera to
// another. Only what the Cinematographer calls is declared; its unit (0x108522B0 - 0x10853200) is reconstructed
// elsewhere. Member and method names are guesses.
#ifndef ENGINE_CAMERA_BLENDCAMERA_H
#define ENGINE_CAMERA_BLENDCAMERA_H

#include "code/engine/camera/camera.h"

namespace engine
{
	namespace camera
	{
		class BlendCamera : public Camera
		{
		public:
			// 0x108523A0 (0xC0 bytes)
			BlendCamera();
			// 0x10852310: the blend has reached its end
			bool IsDone() const;
			// 0x10852330: stops the blend and forgets both cameras
			void Stop();
			// 0x108525A0: blends from one camera (slot and id) to another over time; kind 3 is the only one used
			void Begin(int fromSlot, int fromId, int toSlot, int toId, bool reverse, int kind, float time);

			// The same with one of the two cameras as a reference
			__forceinline void Begin(int fromSlot, int fromId, const ControllerRef& toRef, bool reverse, int kind, float time)
			{
				Begin(fromSlot, fromId, toRef.slot, toRef.id, reverse, kind, time);
			}
			__forceinline void Begin(const ControllerRef& fromRef, const ControllerRef& toRef, bool reverse, int kind,
				float time)
			{
				Begin(fromRef.slot, fromRef.id, toRef.slot, toRef.id, reverse, kind, time);
			}

			unsigned char unknown44[0x90 - 0x44];
			ControllerRef from;  // +0x90
			ControllerRef to;  // +0x98
			float unknownA0;
			float elapsed;  // +0xA4
			float duration;  // +0xA8
			unsigned char unknownAC[0xb3 - 0xac];
			bool unknownB3;
			unsigned char unknownB4[0xc0 - 0xb4];
		};
	}
}

#endif
