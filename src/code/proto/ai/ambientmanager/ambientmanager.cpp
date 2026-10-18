// proto::AmbientManager: see the header. The file name and the names are guesses.
#include "code/core/heap.h"
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
	// EQUIVALENT: the same members started the same way in the same order, the same calls (the nine array
	// allocations, the pools, the cloud manager, the script natives and the three block heaps); what is left are
	// register choices: the engine copies the pools' heap into eax / ecx before pushing it, picks other registers
	// for the empty name and the cloud's sums and pushes one argument later (28.9 %, 37 of 396 instruction lines)
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
		unknown604(-1),
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
