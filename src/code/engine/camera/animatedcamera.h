// engine::camera::AnimatedCamera (RTTI name; base engine::camera::Camera): the camera that plays animations. Only
// what the Cinematographer calls is declared; its unit is reconstructed elsewhere. Member names are guesses.
#ifndef ENGINE_CAMERA_ANIMATEDCAMERA_H
#define ENGINE_CAMERA_ANIMATEDCAMERA_H

#include "code/engine/camera/camera.h"
#include "code/math/matrix.h"

namespace pure3d
{
	class Animation;
	class CameraAnimationController;
}

namespace engine
{
	namespace camera
	{
		class AnimatedCamera : public Camera
		{
		public:
			// 0x108D53A0 (0xA0 bytes)
			AnimatedCamera();

			// 0x108D5230: starts the animation at a frame within a range with a cycle mode and answers the controller that plays
			// it (names and the meaning of the floats guessed)
			pure3d::CameraAnimationController* Play(pure3d::Animation* animation, float frame, float first, float last, int mode);
			// 0x108D5310: puts the camera where the matrix says (name guessed)
			void SetTransform(const math::Matrix& matrix);

			pure3d::CameraAnimationController* controller;  // +0x48
			unsigned char unknown4C[0x9f - 0x4c];
			// Read and cleared by the camera clipping plane action (name guessed)
			bool unknown9F;
		};
	}
}

#endif
