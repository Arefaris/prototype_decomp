#include "code/proto/tunnelvolume.h"
#include "code/core/heap.h"
#include "code/math/matrix3.h"

namespace engine
{
	namespace driving
	{
		extern const float gOne;
	}
}

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x103B2590
	content::ClassInfo* TunnelVolume::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TunnelVolume";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103B28D0
	content::MemberList* TunnelVolume::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetClassMetaType<math::OBB>(), PROTO_OFFSET(TunnelVolume, box), "box" },
			{ content::GetMemberVectorMetaType<TunnelVolume, 0>("p"), 0x44, "entrance1" },
			{ content::GetMemberVectorMetaType<TunnelVolume, 1>("p"), 0x50, "entrance2" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x103B2C70
	// NONMATCHING: scheduling, the engine stores the address of the Matrix3 temporary after the reference count (95.8 %)
#ifdef NONMATCHING
	TunnelVolume::TunnelVolume()
	{
		math::Matrix3 identity;
		identity.Identity();
		box.centre.x = 0.0f;
		box.centre.y = 0.0f;
		box.centre.z = 0.0f;
		box.axis[0].x = identity.m[0][0];
		box.axis[0].y = identity.m[0][1];
		box.axis[0].z = identity.m[0][2];
		box.axis[1].x = identity.m[1][0];
		box.axis[1].y = identity.m[1][1];
		box.axis[1].z = identity.m[1][2];
		box.axis[2].x = identity.m[2][0];
		box.axis[2].y = identity.m[2][1];
		box.axis[2].z = identity.m[2][2];
		box.extents.x = 1.0f;
		box.extents.y = 1.0f;
		box.extents.z = 1.0f;
		entrance1.x = math::kZeroVector.x;
		entrance1.y = math::kZeroVector.y;
		entrance1.z = math::kZeroVector.z;
		entrance2.x = math::kZeroVector.x;
		entrance2.y = math::kZeroVector.y;
		entrance2.z = math::kZeroVector.z;
	}
#endif

	TunnelVolume::~TunnelVolume()
	{
	}

	TunnelVolumeManager* gTunnelVolumeManager = 0;

	// FUNCTION: ENGINE 0x103B25E0
	// NONMATCHING: scheduling of the subtractions, 90.2 %
#ifdef NONMATCHING
	const math::Vector* TunnelVolume::GetFarEntrance(const math::Vector* from, const math::Vector* to)
	{
		math::Vector direction;
		direction.Sub(*to, *from);
		math::Vector first;
		first.Sub(entrance1, *from);
		math::Vector second;
		second.Sub(entrance2, *from);
		float secondDot = second.Dot(direction);
		float firstDot = first.Dot(direction);
		if (secondDot > firstDot)
		{
			return &entrance1;
		}
		return &entrance2;
	}
#endif

	// FUNCTION: ENGINE 0x103B2ED0
	void TunnelVolume::Slot3(int unused)
	{
		if (gTunnelVolumeManager)
		{
			entrance1.y -= 1.0f;
			entrance2.y -= 1.0f;
			gTunnelVolumeManager->Add(this);
		}
	}

	// FUNCTION: ENGINE 0x103B2F20
	bool TunnelVolume::IsReady()
	{
		if (gTunnelVolumeManager)
		{
			gTunnelVolumeManager->Remove(this);
		}
		return true;
	}

	// FUNCTION: ENGINE 0x103B2F40
	TunnelVolumeManager::TunnelVolumeManager()
	{
	}

	// FUNCTION: ENGINE 0x103B2F50
	TunnelVolumeManager::~TunnelVolumeManager()
	{
	}

	// FUNCTION: ENGINE 0x103B29C0
	TunnelEntry* TunnelVolumeManager::Find(TunnelVolume* volume)
	{
		TunnelEntry* entry = entries.Begin();
		if (entry != entries.End())
		{
			do
			{
				if (entry->volume == volume)
				{
					break;
				}
				entry++;
			}
			while (entry != entries.End());
		}
		return entry;
	}

	// FUNCTION: ENGINE 0x103B29F0
	// NONMATCHING: the engine keeps `this` and the entry in separate registers and rereads the end through `this`
	// (6 %)
#ifdef NONMATCHING
	bool TunnelVolumeManager::GetEntrance(const math::Vector* point, math::Vector* entrance)
	{
		bool result = false;
		TunnelEntry* entry = entries.Begin();
		while (entry != entries.End())
		{
			if (point->x >= entry->bounds.min.x && entry->bounds.max.x >= point->x
				&& point->y >= entry->bounds.min.y && entry->bounds.max.y >= point->y
				&& point->z >= entry->bounds.min.z && entry->bounds.max.z >= point->z
				&& entry->volume->box.Contains(*point))
			{
				const math::Vector* first = &entry->volume->entrance1;
				entrance->x = first->x;
				entrance->y = first->y;
				entrance->z = first->z;
				return true;
			}
			entry++;
		}
		return result;
	}
#endif

	// FUNCTION: ENGINE 0x103B2AD0
	// NONMATCHING: the same register split as GetEntrance (4.8 %)
#ifdef NONMATCHING
	TunnelVolume* TunnelVolumeManager::FindVolume(const math::Vector* point)
	{
		TunnelVolume* result = 0;
		TunnelEntry* entry = entries.Begin();
		while (entry != entries.End())
		{
			if (point->x >= entry->bounds.min.x && entry->bounds.max.x >= point->x
				&& point->y >= entry->bounds.min.y && entry->bounds.max.y >= point->y
				&& point->z >= entry->bounds.min.z && entry->bounds.max.z >= point->z
				&& entry->volume->box.Contains(*point))
			{
				return entry->volume;
			}
			entry++;
		}
		return result;
	}
#endif

	// FUNCTION: ENGINE 0x103B2DF0
	void TunnelVolumeManager::Add(TunnelVolume* volume)
	{
		if (Find(volume) == entries.End() && !entries.IsFull())
		{
			TunnelEntry* entry = entries.AllocateBack();
			entry->volume = volume;
			volume->box.GetAABB(entry->bounds);
		}
	}

	// FUNCTION: ENGINE 0x103B2E50
	void TunnelVolumeManager::Remove(TunnelVolume* volume)
	{
		TunnelEntry* entry = Find(volume);
		if (entry != entries.End())
		{
			entries.EraseFast(entry);
		}
	}

	// FUNCTION: ENGINE 0x103B2FC0
	void CreateTunnelVolumeManager()
	{
		core::HeapScope scope(0xB6);
		delete gTunnelVolumeManager;
		gTunnelVolumeManager = new TunnelVolumeManager;
	}

	// FUNCTION: ENGINE 0x103B2F90
	void DestroyTunnelVolumeManager()
	{
		delete gTunnelVolumeManager;
		gTunnelVolumeManager = 0;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103B2750
// FUNCTION: ENGINE 0x103B2820

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103B25D0

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103B2830
// FUNCTION: ENGINE 0x103B2870
