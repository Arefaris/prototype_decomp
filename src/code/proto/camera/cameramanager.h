// proto::CameraManager (RTTI name; no vftable, the object is the global 0x11263108): the camera manager. It owns the
// game camera, the dramatic camera, the framer, the scripted cameras and the camera shake, and registers the camera
// natives (cm_*, sc_*, fcam_*) with the script context. The member names are guesses taken from the natives.
#ifndef PROTO_CAMERA_CAMERAMANAGER_H
#define PROTO_CAMERA_CAMERAMANAGER_H

namespace pure3d
{
	class Camera;
}

namespace proto
{
	class CameraManager
	{
	public:
		// The arguments of cm_CameraShakeRequest that pick what a shake is aimed at
		enum ShakeArgument
		{
			ShakeArgumentNone
		};

		// 0x1032C430: the zoom factor of a camera (a camera value divided by another, at least 1)
		float GetScale(const pure3d::Camera* camera) const;
	};

	// 0x11263108
	extern CameraManager* gCameraManager;
}

#endif
