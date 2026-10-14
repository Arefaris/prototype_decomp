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
		unsigned char unknown0[0x18];
		CameraData* camera;
	};
}

#endif
