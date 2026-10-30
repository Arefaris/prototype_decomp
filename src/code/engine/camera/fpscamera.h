// engine::camera::FPSCamera (RTTI and reflection names; base engine::camera::Camera): the camera that looks out of
// the eyepoint of the game object it is bound to (the object's "EYEPOINT" matrix attribute, or its transform when it
// has none). Unit 0x10915450 - 0x10915790 (no assert path; the directory and file names are guesses). Member and
// method names are guesses.
#ifndef ENGINE_CAMERA_FPSCAMERA_H
#define ENGINE_CAMERA_FPSCAMERA_H

#include "code/content/metatype.h"
#include "code/engine/camera/camera.h"

namespace engine
{
	namespace camera
	{
		class FPSCamera : public Camera
		{
		public:
			// 0x10915490
			FPSCamera();

			// vftable slot 3 (0x109155A0): looks along the object's view from its eyepoint
			virtual void Update(float delta, float time, int flags);
			// vftable slot 5 (0x109154B0)
			virtual int GetType();

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();
		};
	}
}

#endif
