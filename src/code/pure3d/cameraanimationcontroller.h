// pure3d::CameraAnimationController (RTTI name; bases pure3d::BlendFrameController / AnimationFrameController /
// FrameController / Entity / RefCounted / core::IRefCount; 0x120 bytes, 31 vftable slots): plays a camera animation on
// a camera. The slots are those of the frame controllers (framecontroller.h); the camera code calls them under the names
// of the base classes. Method names are guesses.
#ifndef PURE3D_CAMERAANIMATIONCONTROLLER_H
#define PURE3D_CAMERAANIMATIONCONTROLLER_H

#include "code/pure3d/camera.h"
#include "code/pure3d/framecontroller.h"

namespace pure3d
{
	class CameraAnimationController : public BlendFrameController
	{
	public:
		// 0x107B43C0 / 0x107B5260 (the copy takes the same camera)
		CameraAnimationController();
		CameraAnimationController(const CameraAnimationController& other);
		// Slot 2 (the body is 0x107B5150, the deleting destructor 0x107B5240)
		virtual ~CameraAnimationController();

		// Slot 3 (0x107B52E0): the camera is the target when it is one
		virtual void SetTarget(Entity* target);
		// Slot 24 (0x107B4410): a camera animation
		virtual bool IsSupported(Animation* animation);
		// Slots 26 and 27 (0x107B4450, 0x107B4A90): lay the values of the animation (of the first entry, of all of them
		// by their weights) over the camera
		virtual void Unknown26();
		virtual void Unknown27();
		// Slot 29 (0x107B4400): true
		virtual bool Unknown29();
		// Slot 30 (0x107B52B0)
		virtual CameraAnimationController* Clone();

		// 0x107B5170: the camera the animation drives (the controller takes a reference and keeps which kind of camera it
		// is: 1 a vector camera, 2 a point camera, 0 any other, -1 none)
		void SetCamera(Camera* camera);
		// 0x107B4440
		Camera* GetCamera();
		// 0x107B4330: whether the animation has played to its end between the previous and the current frame (name
		// and parameters guessed)
		bool IsFinished(float previousFrame, float frame);

		unsigned char unknown10C[4];
		int cameraKind;   // +0x110
		Camera* camera;   // +0x114
		bool unknown118;
		// Cleared by the camera animation action once it has started the playback (name guessed)
		bool unknown119;
		unsigned char unknown11A[6];
	};
}

#endif
