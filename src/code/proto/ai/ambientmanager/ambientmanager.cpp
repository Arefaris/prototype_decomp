// proto::AmbientManager: see the header. The file name and the names are guesses.
#include "code/core/heap.h"
#include "code/engine/frontend/frontend.h"
#include "code/engine/system/enginememory.h"
#include "code/math/vector.h"
#include "code/proto/ai/ambientmanager/ambientmanager.h"
#include "code/proto/ai/ambientmanager/parkedcarcloudmanager.h"

namespace math
{
	// 0x11283234
	extern const Vector kZeroVector;
}

namespace proto
{
	// 0x11267760
	AmbientManager* gAmbientManager;

	// The growable arrays of the manager allocate through these instances (one for every kind of element)
	// FUNCTION: ENGINE 0x1040B2A0
	// FUNCTION: ENGINE 0x1040B330
	// FUNCTION: ENGINE 0x1040B3C0
	// FUNCTION: ENGINE 0x1040B450
	// FUNCTION: ENGINE 0x1040B4E0
	// FUNCTION: ENGINE 0x1040B570
	// FUNCTION: ENGINE 0x1040B690
	// FUNCTION: ENGINE 0x1040B720
	// FUNCTION: ENGINE 0x1040B840

	// FUNCTION: ENGINE 0x1041FA40
	// The pools take their heap from an AllocatorCoreAligned member, which is what makes the engine's `mov eax, esi`
	// before the push of the heap and the register choices of the whole body come out the same; the member at +0x604
	// is an object with its own constructor (that puts the push of the empty name's flag between its store and the
	// next member's).
	AmbientManager::AmbientManager(const AmbientConfig* newConfig) :
		unknown10(newConfig->physicsCount, container::AllocatorCoreAligned<16>(0xA8)),
		unknown40(false),
		unknown41(true),
		unknown42(false),
		unknown43(false),
		config(*newConfig),
		unknown1FC(0),
		unknown200(newConfig->unknown14),
		unknown204(newConfig->pedestrianCount),
		unknown208(newConfig->unknown5C),
		unknown20C(0),
		unknown210(newConfig->unknown0, container::AllocatorCoreAligned<16>(0xA1)),
		unknown220(newConfig->pedestrianCount, container::AllocatorCoreAligned<16>(0xA1)),
		unknown230(newConfig->unknownC, container::AllocatorCoreAligned<16>(0xA1)),
		unknown240(newConfig->unknown14, container::AllocatorCoreAligned<16>(0xA8)),
		unknown250(newConfig->unknown50, container::AllocatorCoreAligned<16>(0xA8)),
		unknown260(newConfig->unknown50, container::AllocatorCoreAligned<16>(0xA1)),
		unknown270(15, 0xA1),
		unknown280(1.0f),
		unknown284(1.0f),
		unknown288(math::kZeroVector),
		unknown294(math::kZeroVector),
		unknown2A0(0),
		unknown2A4(0),
		unknown2A8(false),
		unknown4EC(math::kZeroVector),
		unknown4F8(1.0f),
		unknown4FC(1.0f),
		unknown500(1.0f),
		unknown504(0.0f),
		unknown508(10.0f),
		unknown514(false),
		unknown515(false),
		unknown516(false),
		unknown520(newConfig->unknown64, container::AllocatorCoreAligned<16>(0xA1)),
		unknown530(newConfig->unknown68, container::AllocatorCoreAligned<16>(0xA1)),
		unknown540(15, 0xA1),
		unknown550(0),
		unknown554(false),
		unknown558(0),
		unknown55C(0),
		unknown560(newConfig->unknown44),
		unknown5A0(0),
		unknown5A4(false),
		unknown5A8(newConfig->unknown6C, container::AllocatorCoreAligned<16>(0xA1)),
		unknown5B8(0xA1),
		unknown5C8(0),
		unknown5CC(0xA1),
		unknown5DC(25, 0xA1),
		unknown5EC(30, 0xA1),
		unknown5FC(-1.0f),
		unknown600(true),
		unknown601(false),
		unknown602(false),
		unknown603(false),
		unknown608(0),
		unknown60C(-1),
		unknown610(-1),
		unknown614(false)
	{
		gAmbientManager = this;
		{
			core::Name<core::CaseSensitiveKey> name("", 1);
			unknown518 = name;
		}
		CloudConfig cloud;
		cloud.unknown4 = newConfig->unknown2C;
		cloud.unknown8 = newConfig->vehicleBase + newConfig->unknown14 - 0x14;
		cloud.unknown4C = 100.0f;
		cloud.unknownC = 0x19;
		cloud.unknown10 = 1;
		cloud.unknown14 = 1;
		cloud.unknown48 = 25.0f;
		{
			core::HeapScope scope(0xA8);
			unknown550 = new ParkedCarCloudManager(&cloud);
		}
		RegisterScript();
		unknown50C = -1;
		unknown510 = -1;
		{
			AmbientPoint& point = unknown48C;
			point.position.x = math::kZeroVector.x;
			point.position.y = math::kZeroVector.y;
			point.position.z = math::kZeroVector.z;
			point.value = config.unknown84;
		}
		{
			AmbientPoint& point = unknown49C;
			point.position.x = math::kZeroVector.x;
			point.position.y = math::kZeroVector.y;
			point.position.z = math::kZeroVector.z;
			point.value = config.unknown90;
		}
		{
			AmbientPoint& point = unknown4AC;
			point.position.x = math::kZeroVector.x;
			point.position.y = math::kZeroVector.y;
			point.position.z = math::kZeroVector.z;
			point.value = config.unknown8C;
		}
		{
			AmbientPoint& point = unknown42C;
			point.position.x = math::kZeroVector.x;
			point.position.y = math::kZeroVector.y;
			point.position.z = math::kZeroVector.z;
			point.value = config.unknown94;
		}
		{
			AmbientPoint& point = unknown43C;
			point.position.x = math::kZeroVector.x;
			point.position.y = math::kZeroVector.y;
			point.position.z = math::kZeroVector.z;
			point.value = config.unknown94 - 10.0f;
		}
		{
			AmbientPoint& point = unknown47C;
			point.position.x = math::kZeroVector.x;
			point.position.y = math::kZeroVector.y;
			point.position.z = math::kZeroVector.z;
			point.value = config.unknown88 + config.unknown84;
		}
		engine::CreateBlockHeap(0xA3, newConfig->pedestrianCount, 0x360, 0, 0x10, "PedGameObjectPool", 0, 2, 0);
		engine::CreateBlockHeap(0xAA, newConfig->vehicleBase + 8 + newConfig->unknown14, 0x8000, 0, 0x10,
			"VehGameObjectPool", 0, 2, 0);
		engine::CreateBlockHeap(0xAB, newConfig->physicsCount, 0x4000, 0, 0x10, "VehiclePhysicsObjectPool", 0xA8, 2, 0);
	}
}

namespace proto
{
	// FUNCTION: ENGINE 0x10409CF0
	void AmbientManager::SetMaxVehicles(unsigned int count)
	{
	}

	// FUNCTION: ENGINE 0x10409D00
	void AmbientManager::SetMaxCharacters(unsigned int count)
	{
		config.unknown5C = count;
	}

	// FUNCTION: ENGINE 0x10409D10
	void AmbientManager::SetFarSpawnDistance(float distance)
	{
		config.unknown44 = distance;
	}

	// FUNCTION: ENGINE 0x10409D30
	void AmbientManager::SetNearSpawnDistance(float distance)
	{
		config.unknown40 = distance;
	}

	// FUNCTION: ENGINE 0x10409D50
	void AmbientManager::SetSpawnAreaSize(float size)
	{
		config.unknown38 = size;
	}

	// FUNCTION: ENGINE 0x10409D70
	void AmbientManager::SetPedestrianDensityScale(float scale)
	{
		unknown280 = scale;
	}

	// FUNCTION: ENGINE 0x10409D90
	void AmbientManager::SetPercentInfectedLevelZero(float percent)
	{
		unknown504 = percent;
	}

	// FUNCTION: ENGINE 0x10409DB0
	void AmbientManager::SetVehicleDensityScale(float scale)
	{
		unknown284 = scale;
	}

	// FUNCTION: ENGINE 0x10409E70
	void AmbientManager::SetInMissionBriefing(bool briefing)
	{
		unknown515 = briefing;
	}

	// FUNCTION: ENGINE 0x10409F60
	void AmbientManager::SetPercentageLowMorale(float percent)
	{
		unknown5FC = percent;
	}

	// FUNCTION: ENGINE 0x1040A0B0
	bool AmbientManager::OnCameraSpawnFinished()
	{
		if (engine::HasCommandLineOption("DisableAmbientManager"))
		{
			return true;
		}
		if (!unknown41)
		{
			if (unknown55C > 3 || !unknown40)
			{
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1040A0F0
	void AmbientManager::SpawnOnCamera()
	{
		unknown55C = 1;
	}

	// FUNCTION: ENGINE 0x1040A100
	void AmbientManager::SetIgnoreDeadSphereLocaters(bool ignore)
	{
		unknown603 = ignore;
	}
}

// The containers of the manager's members: the engine keeps its out-of-line copies of their members
template class container::ArrayDynamicHeap<proto::AmbientElement8A>;
template class container::ArrayDynamicHeap<proto::AmbientElement8B>;
template class container::ArrayDynamicHeap<proto::AmbientElement4A>;
template class container::ArrayDynamicHeap<proto::AmbientElement4B>;
template class container::ArrayDynamicHeap<proto::AmbientElement4C>;
template class container::ArrayDynamicHeap<proto::AmbientElement4D>;
template class container::ArrayDynamicHeap<proto::AmbientElement4E>;
template class container::ArrayDynamicHeap<proto::AmbientElement20>;
template class container::ArrayDynamicHeap<proto::AmbientElement790>;

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10409340
// FUNCTION: ENGINE 0x1040A6D0
// FUNCTION: ENGINE 0x1040B200
// FUNCTION: ENGINE 0x10410220
// FUNCTION: ENGINE 0x104102C0
// FUNCTION: ENGINE 0x10410320
// FUNCTION: ENGINE 0x104103F0
// FUNCTION: ENGINE 0x10410460
// FUNCTION: ENGINE 0x10410530
// FUNCTION: ENGINE 0x104105E0
// FUNCTION: ENGINE 0x10410660
// FUNCTION: ENGINE 0x10410770
// FUNCTION: ENGINE 0x10414F50
// FUNCTION: ENGINE 0x10415060
// FUNCTION: ENGINE 0x104151F0
// FUNCTION: ENGINE 0x10415210
// FUNCTION: ENGINE 0x10415290
// FUNCTION: ENGINE 0x104152C0
// FUNCTION: ENGINE 0x104152E0
// FUNCTION: ENGINE 0x10415470
// FUNCTION: ENGINE 0x1041A020

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10400000
// FUNCTION: ENGINE 0x10400080
// FUNCTION: ENGINE 0x104030E0
// FUNCTION: ENGINE 0x10403100
// FUNCTION: ENGINE 0x10403860
// FUNCTION: ENGINE 0x10403870
// FUNCTION: ENGINE 0x104038A0
// FUNCTION: ENGINE 0x104038C0
// FUNCTION: ENGINE 0x10403A20
// FUNCTION: ENGINE 0x10403BD0
// FUNCTION: ENGINE 0x10403C00
// FUNCTION: ENGINE 0x1040A6F0
// FUNCTION: ENGINE 0x1040A760
// FUNCTION: ENGINE 0x1040A8A0
// FUNCTION: ENGINE 0x1040A8D0
// FUNCTION: ENGINE 0x1040A8E0
// FUNCTION: ENGINE 0x1040A960
// FUNCTION: ENGINE 0x1040A970
// FUNCTION: ENGINE 0x1040A980
// FUNCTION: ENGINE 0x1040A9B0
// FUNCTION: ENGINE 0x1040A9C0
// FUNCTION: ENGINE 0x1040A9F0
// FUNCTION: ENGINE 0x1040AA00
// FUNCTION: ENGINE 0x1040AA10
// FUNCTION: ENGINE 0x1040AA40
// FUNCTION: ENGINE 0x1040AA80
// FUNCTION: ENGINE 0x1040AAA0
// FUNCTION: ENGINE 0x1040AAD0
// FUNCTION: ENGINE 0x1040AB00
// FUNCTION: ENGINE 0x1040AB30
// FUNCTION: ENGINE 0x1040AB40
// FUNCTION: ENGINE 0x1040AB50
// FUNCTION: ENGINE 0x1040AB60
// FUNCTION: ENGINE 0x1040AB80
// FUNCTION: ENGINE 0x1040ABB0
// FUNCTION: ENGINE 0x1040ABF0
// FUNCTION: ENGINE 0x1040ACB0
// FUNCTION: ENGINE 0x1040AED0
// FUNCTION: ENGINE 0x1040AF20
// FUNCTION: ENGINE 0x1040B090
// FUNCTION: ENGINE 0x1040B0C0
// FUNCTION: ENGINE 0x1040BD10
// FUNCTION: ENGINE 0x1040BD30
// FUNCTION: ENGINE 0x1040BD50
// FUNCTION: ENGINE 0x1040BD70
// FUNCTION: ENGINE 0x1040BDA0
// FUNCTION: ENGINE 0x1040BE10
// FUNCTION: ENGINE 0x1040BE50
// FUNCTION: ENGINE 0x1040BEA0
// FUNCTION: ENGINE 0x1040BF30
// FUNCTION: ENGINE 0x1040C290
// FUNCTION: ENGINE 0x10410140
// FUNCTION: ENGINE 0x10410170
// FUNCTION: ENGINE 0x10410190
// FUNCTION: ENGINE 0x10410250
// FUNCTION: ENGINE 0x10410290
// FUNCTION: ENGINE 0x104102F0
// FUNCTION: ENGINE 0x10410390
// FUNCTION: ENGINE 0x104103C0
// FUNCTION: ENGINE 0x104103E0
// FUNCTION: ENGINE 0x104104D0
// FUNCTION: ENGINE 0x10410500
// FUNCTION: ENGINE 0x10410520
// FUNCTION: ENGINE 0x10410610
// FUNCTION: ENGINE 0x10410640
// FUNCTION: ENGINE 0x10410690
// FUNCTION: ENGINE 0x104107D0
// FUNCTION: ENGINE 0x104107F0
// FUNCTION: ENGINE 0x10410A70
// FUNCTION: ENGINE 0x10410AE0
// FUNCTION: ENGINE 0x10410AF0
// FUNCTION: ENGINE 0x10410B00
// FUNCTION: ENGINE 0x10410B10
// FUNCTION: ENGINE 0x10410B70
// FUNCTION: ENGINE 0x10411870
// FUNCTION: ENGINE 0x10415080
// FUNCTION: ENGINE 0x1041A090
// FUNCTION: ENGINE 0x1041A140
