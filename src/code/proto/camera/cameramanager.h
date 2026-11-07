// proto::CameraManager (RTTI name; no vftable, the object is the global 0x11263108, 0x7C bytes): the camera manager. It
// keeps the game cameras by type (index 0 is the chase camera, 1 the vehicle camera), the scripted cameras, the dramatic
// camera, the framer and the camera shake, and registers the camera natives (cm_*, sc_*, fcam_*) with the script context.
// The member names are guesses taken from the natives.
#ifndef PROTO_CAMERA_CAMERAMANAGER_H
#define PROTO_CAMERA_CAMERAMANAGER_H

#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/math/vector.h"

namespace pure3d
{
	class Camera;
}

namespace engine
{
	namespace camera
	{
		class DramaticCamera;
		class ScriptedCamera;
	}
}

namespace proto
{
	class ChaseCamera;
	class FramerCam;

	class CameraManager
	{
	public:
		// The arguments of cm_CameraShakeRequest that pick what a shake is aimed at
		enum ShakeArgument
		{
			ShakeArgumentNone
		};

		// 0x1032BAD0: the chase camera (the game camera of type 0)
		ChaseCamera* GetChaseCamera();
		// 0x1032BAF0
		FramerCam* GetFramerCam();
		// 0x1032BB20: hands a hint to the current camera
		void SendCameraHint(engine::GameObjectHandle object, int hint);
		// 0x1032C1D0: the dramatic camera is switched on (bit 1 of the camera mask)
		bool IsDramaticCameraEnabled();
		// 0x1032C430: the zoom factor of a camera (a camera value divided by another, at least 1)
		float GetScale(const pure3d::Camera* camera) const;
		// 0x1032C8A0: the scripted camera of an index (0 - 2), or null
		engine::camera::ScriptedCamera* GetScriptedCamera(int index);
		// 0x1032C8D0: makes the camera of a type the current one, blending over the time
		void SwitchCamera(int type, float blendTime);
		// 0x1032CF80: the scripted camera of an index has run out (true when there is none)
		bool IsScriptedCameraFinished(int index);
		// 0x1032D0E0: ends the scripted cameras, blending over the time
		void EndScriptedCamera(float blendTime);
		// 0x1032D2C0: asks for a shake at a position (false when the request is dropped; the arguments say how far and
		// how strong)
		bool RequestShake(math::Vector position, ShakeArgument size, ShakeArgument range);
		// 0x1032D410: ends the dramatic camera, blending over the time (a negative time takes the default)
		void EndDramaticCamera(float blendTime);
		// 0x1032F780: hands the camera of a type the game object it follows
		void SetCameraAvatar(int type, engine::GameObjectHandle object);

		int unknown0;
		unsigned int cameraMask;  // +4
		unsigned char unknown8[0x68 - 8];
		float zoom;  // +0x68
		unsigned char unknown6C[0x7c - 0x6c];
	};

	// 0x11263108
	extern CameraManager* gCameraManager;
}

#endif
