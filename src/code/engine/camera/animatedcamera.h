// engine::camera::AnimatedCamera (RTTI name; base engine::camera::Camera): the camera that plays animations. Only
// what the Cinematographer calls is declared; its unit is reconstructed elsewhere. Member names are guesses.
#ifndef ENGINE_CAMERA_ANIMATEDCAMERA_H
#define ENGINE_CAMERA_ANIMATEDCAMERA_H

#include "code/engine/camera/camera.h"

namespace engine
{
	namespace camera
	{
		class AnimatedCamera : public Camera
		{
		public:
			// 0x108D53A0 (0xA0 bytes)
			AnimatedCamera();

			unsigned char unknown44[0xa0 - 0x44];
		};
	}
}

#endif
