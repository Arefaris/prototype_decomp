// proto::GameCamera and proto::VehicleCamera (RTTI names: VehicleCamera : GameCamera : engine::camera::Camera). The
// original's vftables (VehicleCamera's is 0x10DF42C4, 16 slots) are not reconstructed, so the slot functions are
// declared as ordinary members here; only what the reconstructed ones read is declared. Names are guesses.
#ifndef PROTO_CAMERA_VEHICLECAMERA_H
#define PROTO_CAMERA_VEHICLECAMERA_H

#include "code/engine/camera/camera.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/math/vector.h"

namespace proto
{
	// The engine's game cameras (RTTI name; AirCamera, AirGunnerCamera, ChaseCamera and VehicleCamera derive from it)
	class GameCamera : public engine::camera::Camera
	{
	public:
		// vftable slot 5 (0x10351140; the subclasses share it)
		virtual int GetType();
		// vftable slots 11 - 15 (this class's own; the subclasses override them)
		virtual void Slot11();
		virtual void Slot12();
		virtual void Slot13(int first, int second);
		virtual bool Slot14(int value);
		// The camera hint of an object (GameCamera's own slot is empty)
		virtual void Slot15(engine::GameObjectHandle object, int hint);

		bool unknown48;
		unsigned char unknown49[3];
		float unknown4C;
		// How far the camera aims off its avatar (cm_GetCameraAvatarOffset)
		math::Vector avatarOffset;  // +0x50
		float baseDistance;  // +0x5C
		float maxHeight;  // +0x60
		float minHeight;  // +0x64
		unsigned char unknown68[0xcc - 0x68];
		// Read by VehicleCamera's vftable slot 4 (0x10354B60); meaning unknown, name is a guess
		bool unknownCC;
	};

	class VehicleCamera : public GameCamera
	{
	public:
		// 0x10354B60: the vftable's slot 4 in the original
		bool GetUnknownCC();
		// 0x103563B0: turns the camera behind its avatar over the time
		void ResetBehind(float time);
	};
}

#endif
