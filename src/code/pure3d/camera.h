// pure3d::Camera (RTTI name; bases pure3d::Entity / RefCounted / core::IRefCount): the camera whose view volume the
// render code tests against. Only the volume test is known; the vftable and the rest of the class are not
// reconstructed yet, so it is declared as a plain struct with the members the test touches. Unit 0x106DCC20 (the
// nearby pose functions are another unit). Member names are guesses.
#ifndef PURE3D_CAMERA_H
#define PURE3D_CAMERA_H

#include "code/math/matrix.h"
#include "code/pure3d/entity.h"
#include "code/math/vector.h"

namespace pure3d
{
	class Camera : public Entity
	{
	public:
		// 0x106DD480 (another unit): a camera without a view volume; the destructor is not reconstructed
		Camera();
		virtual ~Camera();
		// 0x106DD190: the vertical field of view in radians; 0x106DCA20 / 0x106DCA30: the clipping planes; 0x106DD2B0:
		// the aspect ratio (and whether it is fixed); 0x106DCE40: the camera's matrix at 0x90 (names guessed)
		void SetFov(float radians);
		void SetNearPlane(float distance);
		void SetFarPlane(float distance);
		void SetAspect(float aspect, int fixed);
		void SetMatrix(const math::Matrix& newMatrix);
		// 0x106DC850: takes over the settings, the planes and the matrix of another camera (name guessed)
		void CopyFrom(const Camera* other);
		// 0x106E2920: a thunk that calls the virtual Release through the vftable (the engine's code reaches it through
		// a pointer; name guessed)
		void ReleaseThunk();
		// 0x106DCC20: true when the sphere of radius around point lies in the view volume (a frustum, or an
		// axis-aligned box when unknown10 is set)
		bool Contains(const math::Vector& point, float radius) const;
		// 0x106DCD70: whether a sphere (point and radius) is inside the view (the point goes through the matrix at
		// +0x50); 0x106DD380: whether a point is inside the view (name guesses)
		bool IsPointVisible(const math::Vector* point, float radius);
		bool IsPointInside(const math::Vector* point);

		bool unknown10;
		unsigned char unknown11[3];
		float fov;
		float unknown18;
		float unknown1C;
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
		// The camera's own matrix at 0x90: its translation (the camera's position in the world) is the vector at 0xC0
		unsigned char unknown90[0xc0 - 0x90];
		math::Vector position;
		unsigned char unknownCC[0xf0 - 0xcc];

		math::Matrix* GetWorldMatrix()
		{
			return (math::Matrix*)(unknown90);
		}
		// The 16 floats of the matrix at 0x90 (rows of four)
		const float* GetWorldFloats() const
		{
			return (const float*)unknown90;
		}
	};
}

#endif
