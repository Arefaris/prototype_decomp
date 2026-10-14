// pure3d::View (RTTI name): what a render pass looks through. Only the camera data the particle code reads; names
// are guesses.
#ifndef PURE3D_VIEW_H
#define PURE3D_VIEW_H

#include "code/math/matrix.h"

namespace pure3d
{
	// The camera of a view: its world matrix at +0x90
	struct CameraData
	{
		unsigned char unknown0[0x90];
		math::Matrix transform;
	};

	class View
	{
	public:
		// 0x1073A300: takes the camera (reference counted)
		void SetCamera(CameraData* newCamera);
		// 0x1073A340: the window of the view in the target (left, top, right, bottom as fractions)
		void SetWindow(float left, float top, float right, float bottom);
		// 0x1073A490: puts the view's camera, window and clear settings on the device
		void Apply();
		// 0x10739BD0: does nothing
		void End();

		unsigned char unknown0[0x18];
		CameraData* camera;
		unsigned char unknown1C[0xC];
		int unknown28;
	};
}

#endif
