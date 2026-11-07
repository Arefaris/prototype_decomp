#include "code/proto/ai/ambientmanager/ambientexclusionvolume.h"
#include "code/proto/ai/ambientmanager/ambientmanager.h"
#include "code/proto/citymanager.h"
#include "code/ravenphysics/collision/collisionobject.h"

namespace engine
{
	namespace driving
	{
		extern const float gHalf;
	}
}

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x1040BCE0
	bool AmbientExclusionVolume::GetExcludePedestrians() const
	{
		return flags.Test(AMBIENT_EXCLUDE_PEDESTRIANS);
	}

	// FUNCTION: ENGINE 0x10415680
	void AmbientExclusionVolume::SetExcludePedestrians(bool exclude)
	{
		flags.Assign(AMBIENT_EXCLUDE_PEDESTRIANS, exclude);
	}

	// FUNCTION: ENGINE 0x1040BCF0
	bool AmbientExclusionVolume::GetExcludeTrafficVehicles() const
	{
		return flags.Test(AMBIENT_EXCLUDE_TRAFFIC_VEHICLES);
	}

	// FUNCTION: ENGINE 0x10415720
	void AmbientExclusionVolume::SetExcludeTrafficVehicles(bool exclude)
	{
		flags.Assign(AMBIENT_EXCLUDE_TRAFFIC_VEHICLES, exclude);
	}

	// FUNCTION: ENGINE 0x1040C8B0
	// NONMATCHING: the engine loads the extents' constant first and stores it three times from one register, and keeps the
	// zero of the reference count and of the decay state apart (28.7 %)
#ifdef NONMATCHING
	AmbientExclusionVolume::AmbientExclusionVolume() : extents(engine::driving::gHalf, engine::driving::gHalf,
		engine::driving::gHalf)
	{
		decayState = 0;
		physicsObject.value = 0xffffffff;
		transform.Identity();
		flags.Clear();
	}
#endif

	// FUNCTION: ENGINE 0x1040BBE0
	AmbientExclusionVolume::ExcludeFlags::ExcludeFlags()
	{
		bits = 0;
	}

	// FUNCTION: ENGINE 0x1040BC00
	void AmbientExclusionVolume::ExcludeFlags::Clear()
	{
		bits = 0;
	}

	// FUNCTION: ENGINE 0x1040BC20
	bool AmbientExclusionVolume::ExcludeFlags::Test(unsigned char bit) const
	{
		unsigned char mask = 1;
		mask <<= bit;
		return (mask & bits) != 0;
	}

	// FUNCTION: ENGINE 0x1040BC40
	void AmbientExclusionVolume::ExcludeFlags::ClearBit(unsigned char bit)
	{
		unsigned char mask = 1;
		mask <<= bit;
		bits &= ~mask;
	}

	// FUNCTION: ENGINE 0x1040C220
	void AmbientExclusionVolume::ExcludeFlags::SetBit(unsigned char bit)
	{
		unsigned char mask = 1;
		mask <<= bit;
		bits |= mask;
	}

	// FUNCTION: ENGINE 0x10411740
	void AmbientExclusionVolume::ExcludeFlags::Assign(unsigned char bit, bool value)
	{
		if (value)
		{
			SetBit(bit);
		}
		else
		{
			ClearBit(bit);
		}
	}

	// FUNCTION: ENGINE 0x1041C9E0
	bool AmbientExclusionVolume::IsReady()
	{
		if (gAmbientManager != 0)
		{
			if (physicsObject.IsValid())
			{
				gAmbientManager->SetAreaDensity(physicsObject, 1.0f, 1.0f);
				physicsObject.DestroyObject();
			}
		}
		return true;
	}

	// FUNCTION: ENGINE 0x104163A0
	content::MemberList* AmbientExclusionVolume::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMatrixMetaType<AmbientExclusionVolume>(false, false, "p"),
				PROTO_OFFSET(AmbientExclusionVolume, transform), "transform" },
			{ content::GetMemberVectorMetaType<AmbientExclusionVolume, 0>("p"),
				((int)&((AmbientExclusionVolume*)0)->extents), "extents" },
			{ content::GetMemberMetaType<AmbientExclusionVolume, bool, 0>(
				&AmbientExclusionVolume::GetExcludePedestrians, &AmbientExclusionVolume::SetExcludePedestrians, "p"),
				0, "excludePedestrians" },
			{ content::GetMemberMetaType<AmbientExclusionVolume, bool, 1>(
				&AmbientExclusionVolume::GetExcludeTrafficVehicles, &AmbientExclusionVolume::SetExcludeTrafficVehicles, "p"),
				0, "excludeTrafficVehicles" },
			{ content::GetEnumMetaType<CityManager::DecayState>(),
				((int)&((AmbientExclusionVolume*)0)->decayState), "decayState" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1040AE40
// FUNCTION: ENGINE 0x1040BC60
// FUNCTION: ENGINE 0x1040BCA0
// FUNCTION: ENGINE 0x10410D50
// FUNCTION: ENGINE 0x10410D70
// FUNCTION: ENGINE 0x10410D90
// FUNCTION: ENGINE 0x104156A0
// FUNCTION: ENGINE 0x10415740
