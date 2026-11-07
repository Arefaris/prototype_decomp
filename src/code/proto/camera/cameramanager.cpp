// proto::CameraManager: the global that owns the game cameras, the scripted cameras, the dramatic camera and the camera
// shake (0x1032BAD0 - 0x1032D4F0 and 0x1032F560 on, no assert path; the file name is a guess). The natives the script
// context calls are wrappers of these members.
#include "code/proto/camera/cameramanager.h"
#include "code/engine/camera/cinematographer.h"
#include "code/engine/camera/dramaticcamera.h"
#include "code/engine/camera/scriptedcamera.h"
#include "code/core/heap.h"
#include "code/engine/luascriptmanager.h"
#include "code/math/spline.h"
#include "code/proto/camera/chasecamera.h"
#include "code/proto/camera/framercam.h"
#include "code/proto/fightitems/motion/motioncommon.h"

namespace proto
{
	// The bit tests of the camera mask the engine expands in place
	static inline bool MaskBit(unsigned int mask, int bit)
	{
		return (mask >> bit) & 1;
	}

	// FUNCTION: ENGINE 0x1032F560
	CameraManager::CameraManager()
	{
		unknown0 = 0;
		shakeEnabled = true;
		shakeTimer = 0.0f;
		shakeType = -1;
		zoom = 0.0f;
		spline = 0;
		splineKeyCount = 0;
		splineKeyIndex = 0;
		unknown78 = false;
	}

	// FUNCTION: ENGINE 0x1032BAD0
	ChaseCamera* CameraManager::GetChaseCamera()
	{
		return (ChaseCamera*)cameras[0];
	}

	// FUNCTION: ENGINE 0x1032BAE0
	engine::camera::DramaticCamera* CameraManager::GetDramaticCamera()
	{
		return dramaticCamera;
	}

	// FUNCTION: ENGINE 0x1032BAF0
	FramerCam* CameraManager::GetFramerCam()
	{
		return framerCam;
	}

	// FUNCTION: ENGINE 0x1032BB20
	void CameraManager::SendCameraHint(engine::GameObjectHandle object, int hint)
	{
		GameCamera* camera = cameras[currentCamera];
		if (camera != 0)
		{
			camera->Slot15(object, hint);
		}
	}

	// FUNCTION: ENGINE 0x1032BBB0
	int CameraManager::GetCurrentCameraType() const
	{
		return currentCamera;
	}

	// FUNCTION: ENGINE 0x1032BBD0
	float CameraManager::GetCameraMinHeight()
	{
		GameCamera* camera = cameras[0];
		if (camera != 0)
		{
			return camera->minHeight;
		}
		return -1000000000000.0f;
	}

	// FUNCTION: ENGINE 0x1032BBF0
	void CameraManager::SetCameraMinHeight(float height)
	{
		for (int i = 0; i < 5; ++i)
		{
			GameCamera* camera = cameras[i];
			if (camera != 0)
			{
				camera->minHeight = height;
				return;
			}
		}
	}

	// FUNCTION: ENGINE 0x1032BC20
	float CameraManager::GetCameraMaxHeight()
	{
		GameCamera* camera = cameras[0];
		if (camera != 0)
		{
			return camera->maxHeight;
		}
		return 1000000000000.0f;
	}

	// FUNCTION: ENGINE 0x1032BC40
	void CameraManager::SetCameraMaxHeight(float height)
	{
		for (int i = 0; i < 5; ++i)
		{
			GameCamera* camera = cameras[i];
			if (camera != 0)
			{
				camera->maxHeight = height;
				return;
			}
		}
	}

	// FUNCTION: ENGINE 0x1032BC70
	void CameraManager::ResetChaseCamBehind(float time)
	{
		ChaseCamera* camera = (ChaseCamera*)cameras[0];
		if (camera != 0)
		{
			camera->ResetBehind(time);
		}
	}

	// FUNCTION: ENGINE 0x1032BC90
	void CameraManager::ResetVehicleCamBehind(float time)
	{
		VehicleCamera* camera = (VehicleCamera*)cameras[1];
		if (camera != 0)
		{
			camera->ResetBehind(time);
		}
	}

	// FUNCTION: ENGINE 0x1032BD40
	float CameraManager::GetChaseCamFOV()
	{
		ChaseCamera* camera = (ChaseCamera*)cameras[0];
		if (camera != 0)
		{
			return camera->GetFieldOfView();
		}
		return choreo::gMinusOne;
	}

	// FUNCTION: ENGINE 0x1032BF00
	bool CameraManager::IsSplineComplete()
	{
		if (spline == 0)
		{
			return false;
		}
		if (splineKeyIndex == splineKeyCount)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1032BF90
	bool CameraManager::IsShakeEnabled()
	{
		return shakeEnabled;
	}

	// FUNCTION: ENGINE 0x1032BFA0
	void CameraManager::SetShakeEnabled(bool value)
	{
		shakeEnabled = value;
	}

	// FUNCTION: ENGINE 0x1032C170
	void CameraManager::ClearCameraShake(float value)
	{
		if (cinematographer != 0)
		{
			cinematographer->SetHistoryParameter(value);
		}
	}

	// FUNCTION: ENGINE 0x1032C190
	void CameraManager::SetDramaticCameraWanted(bool value)
	{
		dramaticWanted = value;
	}

	// FUNCTION: ENGINE 0x1032C1C0
	bool CameraManager::IsGameCameraEnabled()
	{
		return (cameraMask & 1) != 0;
	}

	// FUNCTION: ENGINE 0x1032C1D0
	bool CameraManager::IsDramaticCameraEnabled()
	{
		return ((cameraMask >> 1) & 1) != 0;
	}

	// FUNCTION: ENGINE 0x1032C1E0
	bool CameraManager::IsScriptedCameraEnabled()
	{
		return ((cameraMask >> 2) & 1) != 0;
	}

	// FUNCTION: ENGINE 0x1032C1F0
	bool CameraManager::IsFramerCameraEnabled()
	{
		return ((cameraMask >> 3) & 1) != 0;
	}

	// FUNCTION: ENGINE 0x1032C200
	bool CameraManager::IsUnknownCameraEnabled()
	{
		return ((cameraMask >> 4) & 1) != 0;
	}

	// FUNCTION: ENGINE 0x1032C430
	float CameraManager::GetScale(const pure3d::Camera* camera) const
	{
		if (camera == 0 && cinematographer != 0)
		{
			camera = cinematographer->unknown40;
		}
		if (camera != 0)
		{
			float value = zoom;
			if (0.0f >= value)
			{
				return 1.0f;
			}
			return value / camera->halfY;
		}
		return 1.0f;
	}

	// FUNCTION: ENGINE 0x1032C480
	bool CameraManager::IsGameCameraType(unsigned int type)
	{
		if (type <= 4)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1032C490
	bool CameraManager::IsScriptedCameraType(unsigned int type)
	{
		if (type <= 2)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1032C8A0
	engine::camera::ScriptedCamera* CameraManager::GetScriptedCamera(int index)
	{
		if (IsScriptedCameraType(index))
		{
			return scriptedCameras[index];
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1032C8D0
	void CameraManager::SwitchCamera(int type, float blendTime)
	{
		if (IsGameCameraType(type) && type != currentCamera)
		{
			GameCamera* previous = cameras[currentCamera];
			GameCamera* next = cameras[type];
			if (next != 0)
			{
				currentCamera = type;
				if ((cameraMask & 1) != 0 && cinematographer != 0)
				{
					if (previous != 0)
					{
						previous->Slot12();
					}
					next->Slot11();
					cinematographer->StartTransition((int)next, blendTime);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x1032C950
	void CameraManager::SetCameraType(int type, float blendTime)
	{
		SwitchCamera(type, blendTime);
	}

	// FUNCTION: ENGINE 0x1032C970
	const math::Vector* CameraManager::GetCameraAvatarOffsetPointer(int type)
	{
		if (IsGameCameraType(type))
		{
			GameCamera* camera = cameras[type];
			if (camera != 0)
			{
				return &camera->avatarOffset;
			}
		}
		return &math::kZeroVector;
	}

	// FUNCTION: ENGINE 0x1032C9A0
	math::Vector CameraManager::GetCameraAvatarOffset(int type)
	{
		const math::Vector* offset = GetCameraAvatarOffsetPointer(type);
		math::Vector result;
		result.x = offset->x;
		result.y = offset->y;
		result.z = offset->z;
		return result;
	}

	// FUNCTION: ENGINE 0x1032C9D0
	void CameraManager::SetCameraAvatarOffsetVector(int type, const math::Vector& offset)
	{
		if (IsGameCameraType(type))
		{
			GameCamera* camera = cameras[type];
			if (camera != 0)
			{
				camera->avatarOffset.x = offset.x;
				camera->avatarOffset.y = offset.y;
				camera->avatarOffset.z = offset.z;
			}
		}
	}

	// FUNCTION: ENGINE 0x1032CA10
	void CameraManager::SetCameraAvatarOffset(int type, math::Vector offset)
	{
		SetCameraAvatarOffsetVector(type, offset);
	}

	// FUNCTION: ENGINE 0x1032CA30
	float CameraManager::GetCameraBaseDistance(int type)
	{
		if (IsGameCameraType(type))
		{
			GameCamera* camera = cameras[type];
			if (camera != 0)
			{
				return camera->baseDistance;
			}
		}
		return choreo::gMinusOne;
	}

	// FUNCTION: ENGINE 0x1032CA70
	float CameraManager::GetCameraBaseDist(int type)
	{
		return GetCameraBaseDistance(type);
	}

	// FUNCTION: ENGINE 0x1032CA80
	void CameraManager::SetCameraBaseDistanceValue(int type, float distance)
	{
		if (IsGameCameraType(type))
		{
			GameCamera* camera = cameras[type];
			if (camera != 0)
			{
				camera->baseDistance = distance;
			}
		}
	}

	// FUNCTION: ENGINE 0x1032CAB0
	void CameraManager::SetCameraBaseDist(int type, float distance)
	{
		SetCameraBaseDistanceValue(type, distance);
	}

	// FUNCTION: ENGINE 0x1032CAD0
	void CameraManager::ClearScriptedCamera(int index)
	{
		if (IsScriptedCameraType(index))
		{
			scriptedCameras[index]->Restart();
			scriptedBusy[index] = false;
		}
	}

	// FUNCTION: ENGINE 0x1032CEF0
	bool CameraManager::StartScriptedCamera(int index)
	{
		if (IsScriptedCameraType(index))
		{
			return scriptedCameras[index]->Start();
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1032CF20
	void CameraManager::ReleaseScriptedCamera(int index)
	{
		if (IsScriptedCameraType(index))
		{
			scriptedCameras[index]->ReleaseAnimation();
		}
	}

	// FUNCTION: ENGINE 0x1032CF50
	bool CameraManager::IsScriptedCameraRunning(int index)
	{
		if (IsScriptedCameraType(index))
		{
			return scriptedCameras[index]->IsActive();
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1032CF80
	bool CameraManager::IsScriptedCameraFinished(int index)
	{
		if (IsScriptedCameraType(index))
		{
			return scriptedCameras[index]->IsFinished();
		}
		return true;
	}

	// FUNCTION: ENGINE 0x1032D0B0
	int CameraManager::FindFreeScriptedCamera()
	{
		for (unsigned int i = 0; i < 2; ++i)
		{
			engine::camera::ScriptedCamera* camera = scriptedCameras[i];
			if (camera != 0 && !camera->enabled)
			{
				return i;
			}
		}
		return -1;
	}

	// FUNCTION: ENGINE 0x1032D0E0
	void CameraManager::EndScriptedCamera(float blendTime)
	{
		if (MaskBit(cameraMask, 2))
		{
			StopCamera(2, blendTime);
			activeScriptedCamera = -1;
		}
	}

	// FUNCTION: ENGINE 0x1032D110
	void CameraManager::SetScriptedCameraBusy(int index, bool value)
	{
		if (IsScriptedCameraType(index))
		{
			scriptedBusy[index] = value;
		}
	}

	// FUNCTION: ENGINE 0x1032D410
	void CameraManager::EndDramaticCamera(float blendTime)
	{
		if (MaskBit(cameraMask, 1))
		{
			if (blendTime < 0.0f)
			{
				blendTime = defaultBlendTime;
			}
			StopCamera(1, blendTime);
			dramaticCamera->Stop();
		}
	}

	// FUNCTION: ENGINE 0x1032C4A0
	void CameraManager::StartCamera(int camera, int slot, float blendTime)
	{
		cameraMask &= 0xfffffffe;
		GameCamera* current = cameras[currentCamera];
		if (current != 0)
		{
			current->Slot12();
		}
		if (cinematographer != 0)
		{
			cinematographer->StartTransition(camera, blendTime);
		}
		cameraMask |= 1 << slot;
	}

	// FUNCTION: ENGINE 0x1032C500
	void CameraManager::StopCamera(int slot, float blendTime)
	{
		cameraMask &= ~(1 << slot);
		GameCamera* current = cameras[currentCamera];
		if (current != 0)
		{
			current->Slot11();
			if (cinematographer != 0)
			{
				cinematographer->StartTransition((int)current, blendTime);
			}
		}
		cameraMask |= 1;
	}

	// FUNCTION: ENGINE 0x1032BD90
	// NONMATCHING: the engine keeps the null in a register for every store (16.3 %)
#ifdef NONMATCHING
	bool CameraManager::StartSpline(int keyCount)
	{
		if (spline != 0)
		{
			delete spline;
			spline = 0;
			splineKeyCount = 0;
		}
		if (keyCount < 4)
		{
			return false;
		}
		spline = new math::Spline(keyCount, 4, false);
		if (spline == 0)
		{
			return false;
		}
		spline->SetFlag(true);
		splineKeyCount = keyCount;
		splineKeyIndex = 0;
		return true;
	}
#endif

	// FUNCTION: ENGINE 0x1032CB10
	bool CameraManager::SetScriptedCameraPosition(int index, math::Vector point)
	{
		if (IsScriptedCameraType(index))
		{
			return scriptedCameras[index]->SetPositionPoint(point);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1032CB40
	bool CameraManager::SetScriptedCameraTarget(int index, math::Vector point)
	{
		if (IsScriptedCameraType(index))
		{
			return scriptedCameras[index]->SetLookAtPoint(point);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1032CB70
	bool CameraManager::SetCameraObject(int index, engine::LuaGOH object, const char* part, math::Vector offset, int mode, bool active)
	{
		if (IsScriptedCameraType(index))
		{
			engine::GameObjectHandle handle = engine::DeserializeHandle(object);
			return scriptedCameras[index]->BindPosition(handle, part, &offset, mode, active);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1032CBE0
	bool CameraManager::SetTargetObject(int index, engine::LuaGOH object, const char* part, math::Vector offset, int mode, bool active)
	{
		if (IsScriptedCameraType(index))
		{
			engine::GameObjectHandle handle = engine::DeserializeHandle(object);
			return scriptedCameras[index]->BindLookAt(handle, part, &offset, mode, active);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1032CC50
	// NONMATCHING: register allocation of the handle and the by-value name differs (19.0 %)
#ifdef NONMATCHING
	bool CameraManager::AttachCameraToObject(int index, engine::LuaGOH object, const char* part, math::Vector offset, int mode, bool active)
	{
		if (IsScriptedCameraType(index))
		{
			engine::GameObjectHandle handle = engine::DeserializeHandle(object);
			return scriptedCameras[index]->BindPositionNamed(handle, core::Name<core::CaseSensitiveKey>(part, 1), &offset, mode, active);
		}
		return false;
	}
#endif

	// FUNCTION: ENGINE 0x1032CD30
	bool CameraManager::SetScriptedCameraFov(int index, float fov)
	{
		if (IsScriptedCameraType(index))
		{
			engine::camera::ScriptedCamera* camera = scriptedCameras[index];
			float value = camera->unknown57 ? fov : fov * 0.017453292f;
			camera->SetUnknownD8(value);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1032CE30
	bool CameraManager::SetScriptedCameraWindow(int index, float first, float second, float third, float fourth)
	{
		if (IsScriptedCameraType(index))
		{
			return scriptedCameras[index]->SetWindow(first, second, third, fourth);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1032CE90
	void CameraManager::SetScriptedCameraUp(int index, math::Vector up)
	{
		if (IsScriptedCameraType(index))
		{
			scriptedCameras[index]->SetUp(up);
		}
	}

	// FUNCTION: ENGINE 0x1032CEC0
	void CameraManager::SetScriptedCameraFlag(int index, bool value)
	{
		if (IsScriptedCameraType(index))
		{
			scriptedCameras[index]->SetUnknown57(value);
		}
	}

	// FUNCTION: ENGINE 0x1032CFB0
	bool CameraManager::SetCameraPositionSpline(int index)
	{
		if (IsScriptedCameraType(index) && IsSplineComplete())
		{
			bool result = scriptedCameras[index]->SetPositionSpline(*spline);
			delete spline;
			spline = 0;
			splineKeyCount = 0;
			return result;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1032D030
	bool CameraManager::SetCameraTargetSpline(int index)
	{
		if (IsScriptedCameraType(index) && IsSplineComplete())
		{
			bool result = scriptedCameras[index]->SetLookAtSpline(*spline);
			delete spline;
			spline = 0;
			splineKeyCount = 0;
			return result;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1032D220
	void CameraManager::EndUnknownCamera(float blendTime)
	{
		if (MaskBit(cameraMask, 4))
		{
			StopCamera(4, blendTime);
		}
	}

	// FUNCTION: ENGINE 0x1032D460
	// NONMATCHING: the engine tests the slot range with two compares, ours merges them (46.4 %)
#ifdef NONMATCHING
	int CameraManager::IsSlotBusy(int slot)
	{
		if (slot > 0 && slot <= 4)
		{
			if (slot == 2 && MaskBit(cameraMask, 2))
			{
				return 0;
			}
			unsigned int bit = 1 << slot;
			if ((cameraMask & bit) != 0)
			{
				return 1;
			}
			if (MaskBit(cameraMask, 1))
			{
				EndDramaticCamera(0.0f);
			}
			return ((cameraMask & ~bit) & 0x1e) != 0;
		}
		return 1;
	}
#endif

	// FUNCTION: ENGINE 0x1032BAB0
	void CameraManager::UnregisterNatives()
	{
		engine::LuaScriptManager* manager = engine::GetScriptManager();
		manager->Unregister(this);
	}

	// FUNCTION: ENGINE 0x1032C6E0
	CameraManager::~CameraManager()
	{
		UnregisterNatives();
		delete spline;
	}

	// FUNCTION: ENGINE 0x1032F5A0
	void CreateCameraManager()
	{
		core::HeapScope scope(0);
		gCameraManager = new CameraManager();
	}

	// FUNCTION: ENGINE 0x1032F600
	void DestroyCameraManager()
	{
		CameraManager* manager = gCameraManager;
		delete manager;
		gCameraManager = 0;
	}

	// FUNCTION: ENGINE 0x1032BB40
	void CameraManager::ChaseCameraVector(int first, float second, float third, float fourth)
	{
		ChaseCamera* camera = (ChaseCamera*)cameras[0];
		if (camera != 0)
		{
			camera->Unknown1033F3A0(first, second, third, fourth);
		}
	}

	// FUNCTION: ENGINE 0x1032BB80
	void CameraManager::ChaseCameraValue(int value, float time)
	{
		ChaseCamera* camera = (ChaseCamera*)cameras[0];
		if (camera != 0)
		{
			camera->Unknown1033F5B0(value, time);
		}
	}

	// FUNCTION: ENGINE 0x1032BCB0
	void CameraManager::ResetChaseCamFacing(math::Vector direction, float time)
	{
		ChaseCamera* camera = (ChaseCamera*)cameras[0];
		if (camera != 0)
		{
			camera->FaceDirection(&direction, time);
		}
	}

	// FUNCTION: ENGINE 0x1032BCE0
	void CameraManager::ResetChaseCamLooking(math::Vector direction, float time)
	{
		ChaseCamera* camera = (ChaseCamera*)cameras[0];
		if (camera != 0)
		{
			camera->LookAlongDirection(&direction, time);
		}
	}

	// FUNCTION: ENGINE 0x1032BD10
	void CameraManager::ResetChaseCamFacing3D(math::Vector direction, float time)
	{
		ChaseCamera* camera = (ChaseCamera*)cameras[0];
		if (camera != 0)
		{
			camera->ResetFacing3D(&direction, time);
		}
	}

	// FUNCTION: ENGINE 0x1032BD60
	void CameraManager::ChaseCameraPair(float first, float second)
	{
		ChaseCamera* camera = (ChaseCamera*)cameras[0];
		if (camera != 0)
		{
			camera->Unknown1033A300(first, second);
		}
	}

	// FUNCTION: ENGINE 0x1032BF20
	bool CameraManager::IsActiveScriptedCameraBusy()
	{
		if (activeScriptedCamera >= 0)
		{
			return scriptedBusy[activeScriptedCamera];
		}
		return false;
	}
}
