// pure3d::Camera (RTTI name; bases pure3d::Entity / RefCounted / core::IRefCount): the camera whose view volume the
// render code tests against. Only the volume test is known; the vftable and the rest of the class are not
// reconstructed yet, so it is declared as a plain struct with the members the test touches. Unit 0x106DCC20 (the
// nearby pose functions are another unit). Member names are guesses.
#ifndef PURE3D_CAMERA_H
#define PURE3D_CAMERA_H

#include "code/math/matrix.h"
#include "code/math/vector.h"

namespace pure3d
{
	class Camera
	{
	public:
		// 0x106DCC20: true when the sphere of radius around point lies in the view volume (a frustum, or an
		// axis-aligned box when unknown10 is set)
		bool Contains(const math::Vector& point, float radius) const;

		unsigned char unknown0[0x10];
		bool unknown10;
		unsigned char unknown11[0xf];
		float minZ;
		float maxZ;
		float halfX;
		float halfY;
		float plane0x;
		float plane0z;
		float plane1x;
		float plane1z;
		float plane2y;
		float plane2z;
		float plane3y;
		float plane3z;
		math::Matrix matrix;
	};
}

#endif
