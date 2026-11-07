// proto::ChaseCamera (RTTI name; base proto::GameCamera): the camera that follows the player on foot. Only what the other
// units call is declared; the names are guesses.
#ifndef PROTO_CAMERA_CHASECAMERA_H
#define PROTO_CAMERA_CHASECAMERA_H

#include "code/math/vector.h"
#include "code/proto/camera/vehiclecamera.h"

namespace proto
{
	class ChaseCamera : public GameCamera
	{
	public:
		// 0x1033A3D0 (name guess)
		bool Unknown1033A3D0();
		// 0x10341FF0 (name guess)
		void Unknown10341FF0();
		// 0x1033FDB0: turns the camera to face along a direction over the time
		void ResetFacing3D(const math::Vector* direction, float time);
	};
}

#endif
