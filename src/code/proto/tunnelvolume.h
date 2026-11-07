// proto::TunnelVolume (RTTI and reflection names; a content library object): a box of the world with the two points
// where an object enters it (a tunnel). The loaded boxes are kept in a table of the tunnel manager, which the object
// joins when it is made ready and leaves when it goes. Unit 0x103B2500 - 0x103B31B0 (no assert path; the file name is a
// guess). The reflected names are original, the rest is guessed; the table handling is left to the engine.
#ifndef PROTO_TUNNELVOLUME_H
#define PROTO_TUNNELVOLUME_H

#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/math/obb.h"
#include "code/math/vector.h"

namespace proto
{
	struct TunnelVolume : public content::MetaLoadObject
	{
		// 0x103B2C70
		TunnelVolume();
		// 0x103B25D0 (deleting destructor 0x103B2DC0)
		virtual ~TunnelVolume();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 3 (0x103B2ED0: joins the table of the manager) and 4 (0x103B2F20: leaves it), left to the engine
		virtual void Slot3(int unused);
		virtual bool IsReady();

		math::OBB box;  // +8
		math::Vector entrance1;  // +0x44
		math::Vector entrance2;  // +0x50
	};
}

#endif
