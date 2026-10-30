// engine::camera::OnFootCamera (RTTI and reflection names; base engine::camera::Camera): the third person camera that
// follows the game object it is bound to from behind, at a distance and an elevation, with an optional lag. Unit
// 0x109157E0 - 0x10915FD0 (no assert path; the directory and file names are guesses). The reflected member names are
// original; the rest is guessed.
#ifndef ENGINE_CAMERA_ONFOOTCAMERA_H
#define ENGINE_CAMERA_ONFOOTCAMERA_H

#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/camera/camera.h"
#include "code/math/vector.h"

namespace engine
{
	namespace camera
	{
		// The pooled constants the camera reads from memory (3.0, 15.0 and 0.001; 0x10D95F28, 0x10DB82FC, 0x10D9FDFC;
		// names guessed) and the up vector (0x111E8024)
		extern const float gThree;
		extern const float gFifteen;
		extern const float gThousandth;
		extern const math::Vector gUpVector;

		class OnFootCamera : public Camera
		{
		public:
			// 0x10915860
			OnFootCamera();
			// vftable slot 0 (0x10915BD0 deletes); the destructor body is 0x10915900
			virtual ~OnFootCamera();

			// vftable slot 3 (0x10915BF0): follows the object from behind
			virtual void Update(float delta, float time, int flags);
			// vftable slot 5 (0x109158B0)
			virtual int GetType();

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// The point of the followed object and the direction it faces (flattened to the ground), set by Update
			math::Vector focus;  // +0x48
			math::Vector heading;  // +0x54
			float elevation;  // +0x60
			float distance;  // +0x64
			float lookAhead;  // +0x68
			float lag;  // +0x6C
			bool reverseTargetHeading;  // +0x70
			int unknown74;
			core::Name<core::CaseSensitiveKey> targetName;  // +0x78
		};
	}
}

#endif
