// engine::camera::DebugCamera (RTTI name; base engine::camera::Camera): the free camera the Cinematographer switches
// to as its default camera. Only what the Cinematographer uses is declared; its unit (0x10896450 - 0x10897800) is
// another one. Member and method names are guesses.
#ifndef ENGINE_CAMERA_DEBUGCAMERA_H
#define ENGINE_CAMERA_DEBUGCAMERA_H

#include "code/engine/camera/camera.h"

namespace engine
{
	namespace camera
	{
		class DebugCamera : public Camera
		{
		public:
			// 0x10897780: reads the input of the camera's player
			void ReadInput();

			unsigned char unknown44[0x94 - 0x44];
			int unknown94;
		};
	}
}

#endif
