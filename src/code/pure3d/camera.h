// pure3d::Camera (RTTI name; bases pure3d::Entity / RefCounted / core::IRefCount): the camera whose view volume the
// render code tests against. Only the volume test is known; the vftable and the rest of the class are not
// reconstructed yet, so it is declared as a plain struct with the members the test touches. Unit 0x106DCC20 (the
// nearby pose functions are another unit). Member names are guesses.
#ifndef PURE3D_CAMERA_H
#define PURE3D_CAMERA_H

#include "code/math/matrix.h"
#include "code/math/plane.h"
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

	// 0x106DCE70: the matrix of a camera at position looking along forward with the up vector (name guessed)
	void SetViewMatrix(math::Matrix* target, const math::Vector* position, math::Vector forward, math::Vector up);

	class Camera : public Entity
	{
	public:
		// 0x106DD480: a camera with the unit aspect ratio and the default field of view; 0x106DD510: a copy of the
		// settings, the planes and both matrices of another camera (the copy constructor of the engine's unit)
		Camera();
		Camera(const Camera& other);
		// 0x106DC840
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
		// 0x106DC940: recomputes the four side planes from the two field-of-view angles (not for the box volume)
		void UpdatePlanes();
		// 0x106DCA40: the clipping plane of the side the bit selects (1 near, 2 far, 4 / 8 bottom / top, 0x10 / 0x20
		// left / right) in camera space; 0x106DCC00 the same moved through the camera's matrix at 0x90 (names guessed)
		void GetPlane(int side, math::Plane* plane);
		void GetWorldPlane(int side, math::Plane* plane);
		// 0x106DCDB0: a bit per side of the view volume the point (in camera space) lies outside of; 0x106DD360: none
		// (names guessed)
		unsigned int Classify(const math::Vector* point);
		bool IsInsideView(const math::Vector* point);
		// 0x106DCEA0: the near and far point of the view ray through the screen position (two floats), in camera
		// space; 0x106DCF40: a point of camera space in the world; 0x106DD430: the two ray points in the world (names
		// guessed)
		void GetRayPoints(const float* screen, math::Vector* nearPoint, math::Vector* farPoint);
		void ToWorld(const math::Vector* point, math::Vector* out);
		void GetRay(const float* screen, math::Vector* nearPoint, math::Vector* farPoint);
		// 0x106DCF50: the position of a world point on the screen (two floats) and its depth (name guessed)
		void ToScreen(const math::Vector* point, float* out);
		// 0x106DD0B0: the window in pieces (name guessed); 0x106DD100 / 0x106DD120: the size of the view
		void GetWindow(bool* enabled, float* a, float* b, float* c, float* d, bool* flag);
		void SetSize(float width, float height);
		void GetSize(float* width, float* height);
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
		// The camera's own matrix at 0x90: its translation (the camera's position in the world) is the row at 0xC0
		math::Matrix world;
		CameraWindow window;
		float width;
		float height;

		// The camera's position in the world: the translation row of the matrix
		const math::Vector& GetPosition() const
		{
			return *(const math::Vector*)world.m[3];
		}
		math::Matrix* GetWorldMatrix()
		{
			return &world;
		}
		// The 16 floats of the matrix at 0x90 (rows of four)
		const float* GetWorldFloats() const
		{
			return &world.m[0][0];
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
