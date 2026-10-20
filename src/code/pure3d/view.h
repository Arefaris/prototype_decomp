// pure3d::View (RTTI name; bases pure3d::RefCounted / core::IRefCount): what a render pass looks through, a camera,
// the window of the target it draws into and the clear settings, with the transforms between the spaces a point goes
// through on its way to the screen. Names are guesses.
#ifndef PURE3D_VIEW_H
#define PURE3D_VIEW_H

#include "code/math/matrix.h"
#include "code/math/vector.h"
#include "code/math/vector2.h"
#include "code/pure3d/entity.h"

namespace pure3d
{
	// The camera of a view (RTTI pure3d::Camera, reference counted; camera.h has the view volume test): the camera's
	// world matrix is at +0x90, the matrix that takes a point into its space at +0x50
	struct CameraData
	{
		// The reference count (0x106E2A00 / 0x106E2A10)
		virtual void AddRef();
		virtual void Release();

		// 0x106DD2B0: sets the aspect ratio of the camera (the second argument is 0 for every caller)
		void SetAspect(float aspect, int unknown);
		// 0x106DD120: the size of the camera's picture (name guess)
		void GetSize(float* outWidth, float* outHeight);

		unsigned char unknown4[0xC];
		bool unknown10;
		unsigned char unknown11[3];
		float unknown14;
		unsigned char unknown18[4];
		float unknown1C;
		float nearClip;
		float farClip;
		float halfWidth;
		float halfHeight;
		unsigned char unknown30[0x20];
		math::Matrix view;
		math::Matrix transform;
	};

	class View : public RefCounted
	{
	public:
		// 0x1073A260: the whole target, a clear to opaque black and an identity matrix
		View();
		// 0x1073A2E0; the scalar deleting destructor is 0x1073A6D0
		virtual ~View();

		// 0x1073A300: takes the camera (reference counted)
		void SetCamera(CameraData* newCamera);
		// 0x1073A340: the window of the view in the target (left, top, right, bottom as fractions)
		void SetWindow(float newLeft, float newTop, float newRight, float newBottom);
		// 0x10739BA0
		void GetWindow(float* outLeft, float* outTop, float* outRight, float* outBottom);
		// 0x1073A3A0: a window with that aspect ratio inside the whole target (centred when the flag is set)
		void SetAspect(float newAspect, bool centre);
		// 0x1073A490: puts the view's camera, window and clear settings on the device
		void Apply();
		// 0x10739BD0: does nothing
		void End();
		// 0x1073A220, 0x1073A250: set a flag and answer the old one (names guessed)
		bool SetUpdatesCamera(bool value);
		bool SetFixedAspect(bool value);

		// The spaces a point passes through: 0x10739BE0 the device's, 0x10739C00 the camera's, 0x10739C20 the camera's
		// window (-0.5 - 0.5), 0x10739CB0 the window's, 0x10739D80 back from the window's, 0x10739F00 the world's
		void ToDeviceSpace(const math::Vector& point, math::Vector* out);
		void ToCameraSpace(const math::Vector& point, math::Vector* out);
		void Project(const math::Vector* point, math::Vector* out);
		void ToWindow(const math::Vector* point, math::Vector* out);
		void FromWindow(const math::Vector* point, math::Vector* out);
		void ToWorldSpace(const math::Vector& point, math::Vector* out);
		// 0x10739E50: the points of the near and far planes that the window position shows
		void GetFrustumPoints(const math::Vector2* position, math::Vector* outNear, math::Vector* outFar);
		// 0x1073A5C0: back from the device's space
		void FromDeviceSpace(const math::Vector& point, math::Vector* out);
		// 0x10739F20, 0x10739F60, 0x10739F90, 0x10739FF0: chains of those
		void WorldToCameraWindow(math::Vector point, math::Vector* out);
		void WorldToCameraSpace(math::Vector point, math::Vector* out);
		void WorldToWindow(math::Vector point, math::Vector* out);
		void DeviceToCameraWindow(math::Vector point, math::Vector* out);
		// 0x1073A030, 0x1073A110: the camera window position of a point in the world's space / in the camera's
		void ProjectWorldPoint(float x, float y, float z, math::Vector* out);
		void ProjectCameraPoint(float x, float y, float z, math::Vector* out);
		// 0x1073A600, 0x1073A670: the world points of the near and far planes that a camera window / window position
		// shows
		void GetWorldRay(math::Vector position, math::Vector* outNear, math::Vector* outFar);
		void GetWindowRay(math::Vector position, math::Vector* outNear, math::Vector* outFar);

		float left;
		float top;
		float right;
		float bottom;
		CameraData* camera;
		int clearColour;
		float clearDepth;
		int clearStencil;
		int clearFlags;
		math::Matrix matrix;
		float requestedAspect;
		float aspect;
		bool fixedAspect;
		bool updatesCamera;

	private:
		// 0x1073A1D0: the aspect ratio of the window, handed to the camera
		void UpdateAspect();
	};
}

#endif
