// proto::GameCamera and proto::VehicleCamera (RTTI names: VehicleCamera : GameCamera : engine::camera::Camera). The
// original's vftables (VehicleCamera's is 0x10DF42C4, 16 slots) are not reconstructed, so the slot functions are
// declared as ordinary members here; only what the reconstructed ones read is declared. Names are guesses.
#ifndef PROTO_CAMERA_VEHICLECAMERA_H
#define PROTO_CAMERA_VEHICLECAMERA_H

#include "code/engine/camera/camera.h"

namespace proto
{
	// The engine's game cameras (RTTI name; AirCamera, AirGunnerCamera, ChaseCamera and VehicleCamera derive from it)
	class GameCamera : public engine::camera::Camera
	{
	public:
		unsigned char unknown48[0xcc - 0x48];
		// Read by VehicleCamera's vftable slot 4 (0x10354B60); meaning unknown, name is a guess
		bool unknownCC;
	};

	class VehicleCamera : public GameCamera
	{
	public:
		// 0x10354B60: the vftable's slot 4 in the original
		bool GetUnknownCC();
	};
}

#endif
