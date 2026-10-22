// engine::camera::DramaticCamera (RTTI name; base engine::camera::Camera): the camera the Cinematographer uses by
// default. Only what the Cinematographer reads is declared; its unit is reconstructed elsewhere. Member and method
// names are guesses.
#ifndef ENGINE_CAMERA_DRAMATICCAMERA_H
#define ENGINE_CAMERA_DRAMATICCAMERA_H

#include "code/engine/camera/camera.h"

namespace engine
{
	namespace camera
	{
		class DramaticCamera : public Camera
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
