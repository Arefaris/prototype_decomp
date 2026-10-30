// proto::NavArea (the name is a guess; the symbols AddVehicle / RemoveVehicle name it): the 64-byte runtime record of an
// area of the navigation mesh (the records navmesh.h reaches through NavMesh::areas). It keeps the kind of the area, the
// list of the vehicles on it and the counters of the walkers and the lanes that are claimed. Unit 0x10568010 - 0x10568380
// (no assert path). The member names are guesses.
#ifndef PROTO_NAVAREA_H
#define PROTO_NAVAREA_H

#include "code/container/doublelist.h"

namespace proto
{
	class NavArea
	{
	public:
		// 0x10568010: a sidewalk, a crosswalk, its corner or a stairway
		bool IsOnFoot() const;
		// 0x10568040: an intersection or a crosswalk
		bool IsCrossing() const;
		// 0x10568100
		int GetVehicleCount() const;
		// 0x10568110 / 0x10568130: claims a lane (the counter counts below zero while claimed)
		void ClaimBackward();
		void ClaimForward();
		// 0x10568150 / 0x10568170: lets a lane go again
		void ReleaseBackward();
		void ReleaseForward();
		// 0x105681F0 / 0x10568220: the load a lane counter stands for
		float GetBackwardLoad(float scale) const;
		float GetForwardLoad(float scale) const;
		// 0x10568360 / 0x10568370
		void AddWalker();
		void RemoveWalker();

		unsigned char unknown0[0x20];
		int areaType;  // +0x20
		int unknown24;
		container::DoubleListBase vehicles;  // +0x28
		unsigned short walkers;  // +0x34
		short forwardClaims;  // +0x36
		short backwardClaims;  // +0x38
		unsigned short index;  // +0x3A
		unsigned char unknown3C[4];
	};
}

#endif
