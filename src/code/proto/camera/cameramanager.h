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

namespace math
{
	class Spline;
}

namespace engine
{
	namespace camera
	{
		class Cinematographer;
		class DramaticCamera;
		class ScriptedCamera;
	}
}

namespace proto
{
	class ChaseCamera;
	class FramerCam;
	class GameCamera;

	class CameraManager
	{
	public:
		// The arguments of cm_CameraShakeRequest that pick what a shake is aimed at
		enum ShakeArgument
		{
			ShakeArgumentNone
		};

		// 0x1032F560
		CameraManager();

		// 0x1032BAD0: the chase camera (the game camera of type 0)
		ChaseCamera* GetChaseCamera();
		// 0x1032BAE0
		engine::camera::DramaticCamera* GetDramaticCamera();
		// 0x1032BAF0
		FramerCam* GetFramerCam();
		// 0x1032BB20: hands a hint to the current camera
		void SendCameraHint(engine::GameObjectHandle object, int hint);
		// 0x1032BBB0: the type of the current game camera
		int GetCurrentCameraType() const;
		// 0x1032BBD0 / 0x1032BBF0 and 0x1032BC20 / 0x1032BC40: the lowest and the highest height the cameras keep
		float GetCameraMinHeight();
		void SetCameraMinHeight(float height);
		float GetCameraMaxHeight();
		void SetCameraMaxHeight(float height);
		// 0x1032BC70 / 0x1032BC90: turn the chase / vehicle camera behind its avatar over the time
		void ResetChaseCamBehind(float time);
		void ResetVehicleCamBehind(float time);
		// 0x1032BD40: the field of view of the chase camera (-1 without one)
		float GetChaseCamFOV();
		// 0x1032BF00: the spline of the scripted cameras is complete
		bool IsSplineComplete();
		// 0x1032BF90 / 0x1032BFA0: the camera shake is enabled
		bool IsShakeEnabled();
		void SetShakeEnabled(bool value);
		// 0x1032C170: the history parameter of the cinematographer
		void ClearCameraShake(float value);
		// 0x1032C190: the dramatic camera is wanted
		void SetDramaticCameraWanted(bool value);
		// 0x1032C1C0 / 0x1032C1D0 / 0x1032C1E0 / 0x1032C1F0 / 0x1032C200: the bits of the camera mask
		bool IsGameCameraEnabled();
		bool IsDramaticCameraEnabled();
		bool IsScriptedCameraEnabled();
		bool IsFramerCameraEnabled();
		bool IsUnknownCameraEnabled();
		// 0x1032C3A0: whether a point is in view of the rendered camera
		bool IsPointInCameraView(math::Vector point);
		// 0x1032C430: the zoom factor of a camera (a camera value divided by another, at least 1)
		float GetScale(const pure3d::Camera* camera) const;
		// 0x1032C480 / 0x1032C490: whether a type is one of the game cameras (0 - 4) / of the scripted cameras (0 - 2)
		static bool IsGameCameraType(unsigned int type);
		static bool IsScriptedCameraType(unsigned int type);
		// 0x1032C4A0: makes a camera the one of a slot of the camera mask, blending over the time
		void StartCamera(int camera, int slot, float blendTime);
		// 0x1032C500: takes the camera of a slot of the camera mask away again
		void StopCamera(int slot, float blendTime);
		// 0x1032C8A0: the scripted camera of an index (0 - 2), or null
		engine::camera::ScriptedCamera* GetScriptedCamera(int index);
		// 0x1032C8D0: makes the camera of a type the current one, blending over the time
		void SwitchCamera(int type, float blendTime);
		// 0x1032C950: cm_SetCameraType
		void SetCameraType(int type, float blendTime);
		// 0x1032C970 / 0x1032C9A0: how far the camera of a type aims off its avatar
		const math::Vector* GetCameraAvatarOffsetPointer(int type);
		math::Vector GetCameraAvatarOffset(int type);
		// 0x1032C9D0 / 0x1032CA10
		void SetCameraAvatarOffsetVector(int type, const math::Vector& offset);
		void SetCameraAvatarOffset(int type, math::Vector offset);
		// 0x1032CA30 / 0x1032CA70 and 0x1032CA80 / 0x1032CAB0: the base distance of the camera of a type
		float GetCameraBaseDistance(int type);
		float GetCameraBaseDist(int type);
		void SetCameraBaseDistanceValue(int type, float distance);
		void SetCameraBaseDist(int type, float distance);
		// 0x1032CAD0: restarts the scripted camera of an index
		void ClearScriptedCamera(int index);
		// 0x1032CEF0 / 0x1032CF20 / 0x1032CF50 / 0x1032CF80: start, release, ask whether it runs, whether it is over
		bool StartScriptedCamera(int index);
		void ReleaseScriptedCamera(int index);
		bool IsScriptedCameraRunning(int index);
		bool IsScriptedCameraFinished(int index);
		// 0x1032D0B0: the first scripted camera that is free (-1: none)
		int FindFreeScriptedCamera();
		// 0x1032D0E0: ends the scripted cameras, blending over the time
		void EndScriptedCamera(float blendTime);
		// 0x1032D110: the busy flag of a scripted camera
		void SetScriptedCameraBusy(int index, bool value);
		// 0x1032D2C0: asks for a shake at a position (false when the request is dropped; the arguments say how far and
		// how strong)
		bool RequestShake(math::Vector position, ShakeArgument size, ShakeArgument range);
		// 0x1032D410: ends the dramatic camera, blending over the time (a negative time takes the default)
		void EndDramaticCamera(float blendTime);
		// 0x1032F780: hands the camera of a type the game object it follows
		void SetCameraAvatar(int type, engine::GameObjectHandle object);

		int unknown0;
		unsigned int cameraMask;  // +4
		unsigned char unknown8[4];
		bool dramaticWanted;  // +0xC
		unsigned char unknownD[3];
		float defaultBlendTime;  // +0x10
		engine::camera::Cinematographer* cinematographer;  // +0x14
		int currentCamera;  // +0x18
		GameCamera* cameras[5];  // +0x1C
		FramerCam* framerCam;  // +0x30
		void* unknown34;
		engine::camera::DramaticCamera* dramaticCamera;  // +0x38
		engine::camera::ScriptedCamera* scriptedCameras[3];  // +0x3C
		int activeScriptedCamera;  // +0x48
		bool scriptedBusy[3];  // +0x4C
		unsigned char unknown4F;
		bool shakeEnabled;  // +0x50
		unsigned char unknown51[3];
		float shakeTimer;  // +0x54
		int shakeType;  // +0x58
		float unknown5C;
		float unknown60;
		float unknown64;
		float zoom;  // +0x68
		math::Spline* spline;  // +0x6C
		int splineKeyCount;  // +0x70
		int splineKeyIndex;  // +0x74
		bool unknown78;
		unsigned char unknown79[3];
	};

	// 0x11263108
	extern CameraManager* gCameraManager;
}

#endif
