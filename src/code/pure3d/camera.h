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
	// A window of the camera's view (copied to the camera's bytes 0xD0 - 0xE7; the engine's name is not known): the
	// constructor at 0x106DC810 leaves it disabled with all four values zero and the last flag set
	struct CameraWindow
	{
		// 0x106DC810
		CameraWindow();

		bool enabled;
		float values[4];
		bool flag;
	};

	// 0x106DCFE0: the field of view that gives the field of view fov at the first aspect ratio at the second one, and
	// the horizontal one (names and meanings guessed)
	void ConvertFov(float fov, float aspect, float otherAspect, float* vertical, float* horizontal);

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
		// 0x106DD160: switches the camera between the frustum and the axis-aligned box volume (name guessed)
		void SetOrthographic(bool value);
		// 0x106DD220: the horizontal field of view in radians (name guessed)
		void SetFovHorizontal(float radians);
		// 0x106DD3B0: the camera at position looking along forward with the up vector (names and the order of the
		// two vectors guessed)
		void SetView(const math::Vector* position, math::Vector forward, math::Vector up);
		// 0x106DD020: the window of the view
		void SetWindow(const CameraWindow* window);
		// 0x106DD060: the window in pieces (name guessed)
		void SetWindow(bool enabled, float a, float b, float c, float d, bool flag);
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
		unsigned char unknownCC[4];
		CameraWindow window;
		unsigned char unknownE8[8];

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

	// The kinds of camera the camera animation tells apart (RTTI names, bases pure3d::Camera)
	class VectorCamera : public Camera
	{
	};

	class PointCamera : public Camera
	{
	};

	class OrbitCamera : public Camera
	{
	};
}

#endif
