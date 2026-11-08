// proto::TunnelVolume (RTTI and reflection names; a content library object): a box of the world with the two points
// where an object enters it (a tunnel). The loaded boxes are kept in a table of the tunnel manager, which the object
// joins when it is made ready and leaves when it goes. Unit 0x103B2500 - 0x103B31B0 (no assert path; the file name is a
// guess). The reflected names are original, the rest is guessed; the table handling is left to the engine.
#ifndef PROTO_TUNNELVOLUME_H
#define PROTO_TUNNELVOLUME_H

#include "code/container/arrayfixed.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/math/aabb.h"
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

		// vftable slots 3 (0x103B2ED0: lowers the entrances by one metre and joins the table of the manager) and 4
		// (0x103B2F20: leaves it)
		virtual void Slot3(int unused);
		virtual bool IsReady();

		// 0x103B25E0: of the two entrances the one further along the way from `from` to `to`
		const math::Vector* GetFarEntrance(const math::Vector* from, const math::Vector* to);

		math::OBB box;  // +8
		math::Vector entrance1;  // +0x44
		math::Vector entrance2;  // +0x50
	};

	// One volume of the manager's table: the box around it and the volume (0x1C bytes; the engine copies the maximum
	// corner before the minimum one)
	struct TunnelEntry
	{
		TunnelEntry()
		{
		}
		TunnelEntry& operator=(const TunnelEntry& other)
		{
			bounds.max.x = other.bounds.max.x;
			bounds.max.y = other.bounds.max.y;
			bounds.max.z = other.bounds.max.z;
			bounds.min.x = other.bounds.min.x;
			bounds.min.y = other.bounds.min.y;
			bounds.min.z = other.bounds.min.z;
			volume = other.volume;
			return *this;
		}

		math::AABB bounds;
		TunnelVolume* volume;  // +0x18
	};

	// The table of the loaded tunnel volumes, up to sixteen (the singleton gTunnelVolumeManager, 0x11264590, made by
	// 0x103B2FC0 in heap 0xB6 and freed by 0x103B2F90); names are guesses
	class TunnelVolumeManager
	{
	public:
		// 0x103B2F40 and 0x103B2F50
		TunnelVolumeManager();
		~TunnelVolumeManager();
		// 0x103B29C0: the entry of volume, the end when there is none
		TunnelEntry* Find(TunnelVolume* volume);
		// 0x103B29F0: the first entrance of the volume that contains point
		bool GetEntrance(const math::Vector* point, math::Vector* entrance);
		// 0x103B2AD0: the volume that contains point
		TunnelVolume* FindVolume(const math::Vector* point);
		// 0x103B2DF0 and 0x103B2E50
		void Add(TunnelVolume* volume);
		void Remove(TunnelVolume* volume);

		container::ArrayFixed<TunnelEntry, 16> entries;
	};

	extern TunnelVolumeManager* gTunnelVolumeManager;

	// 0x103B2FC0
	void CreateTunnelVolumeManager();
	// 0x103B2F90
	void DestroyTunnelVolumeManager();
}

#endif
