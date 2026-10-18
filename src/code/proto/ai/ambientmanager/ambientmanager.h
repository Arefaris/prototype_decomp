// proto::AmbientManager (RTTI names Method0 .. Method3 / Closure of proto::AmbientManager for its script natives; the
// singleton is 0x11267760): the manager of the ambient pedestrians and vehicles. The unit has no assert path, so the
// file name, the member names and the layout above the constructor's reach are guesses; the constructor
// (0x1041FA40) sets 0x618 bytes up from a configuration the game hands it.
#ifndef PROTO_AI_AMBIENTMANAGER_AMBIENTMANAGER_H
#define PROTO_AI_AMBIENTMANAGER_AMBIENTMANAGER_H

#include "code/container/arraydynamic.h"
#include "code/core/heap.h"
#include "code/core/name.h"
#include "code/math/vector.h"

namespace proto
{
	class NavMesh;
	class ParkedCarCloudManager;
	class VehicleBehaviourAmbient;

	// The sizes and counts the manager is made from (0xA0 bytes, copied into the manager at +0x44); only what the
	// constructor reads is named
	struct AmbientConfig
	{
		unsigned int unknown0;
		unsigned int pedestrianCount;
		unsigned int unknown8;
		unsigned int unknownC;
		unsigned int unknown10;
		unsigned int unknown14;
		unsigned int unknown18;
		unsigned int physicsCount;
		unsigned int unknown20;
		unsigned int vehicleBase;
		unsigned int unknown28;
		unsigned int unknown2C;
		unsigned char unknown30[0x44 - 0x30];
		float unknown44;
		unsigned char unknown48[0x50 - 0x48];
		unsigned int unknown50;
		unsigned char unknown54[0x5C - 0x54];
		unsigned int unknown5C;
		unsigned char unknown60[4];
		unsigned int unknown64;
		unsigned int unknown68;
		unsigned int unknown6C;
		unsigned char unknown70[0x84 - 0x70];
		float unknown84;
		float unknown88;
		float unknown8C;
		float unknown90;
		float unknown94;
		unsigned char unknown98[0xA0 - 0x98];
	};

	// The three pointers of an array that is emptied by one out-of-line function (0x1060E6C0, a copy another unit
	// kept): begin, end and capacity
	struct ArrayStorage
	{
		void Reset();

		void* begin;
		void* end;
		void* capacity;
	};

	// Those with no allocator, and those with the number of the heap they come from after them
	struct AmbientArray12 : public ArrayStorage
	{
		AmbientArray12()
		{
			Reset();
		}
	};

	struct AmbientArray16 : public ArrayStorage
	{
		explicit AmbientArray16(int newHeap)
		{
			heap = newHeap;
			Reset();
		}

		int heap;
	};

	// A fixed block of count elements from a heap (begin, end, capacity and the heap after them), made once
	template<class T> struct AmbientPool
	{
		AmbientPool(unsigned int count, int newHeap)
		{
			heap = newHeap;
			begin = (T*)core::HeapAllocAligned(heap, count * sizeof(T), 16);
			if (begin != 0)
			{
				end = begin;
				capacity = begin + count;
			}
			else
			{
				end = 0;
				capacity = 0;
			}
		}

		T* begin;
		T* end;
		T* capacity;
		int heap;
	};

	// Where something is, with a fourth value (the first three start at zero)
	struct AmbientPoint
	{
		AmbientPoint() : position(0.0f, 0.0f, 0.0f)
		{
		}
		math::Vector position;
		float value;
	};

	// Objects of 0x8C bytes the manager holds two of (0x104279C0 makes one)
	struct AmbientBlock
	{
		AmbientBlock();
		unsigned char unknown0[0x8C];
	};

	// The elements of the manager's arrays; only their sizes are known
	struct AmbientElement8A { unsigned int a, b; };
	struct AmbientElement8B { unsigned int a, b; };
	struct AmbientElement4A { unsigned int a; };
	struct AmbientElement4B { unsigned int a; };
	struct AmbientElement4C { unsigned int a; };
	struct AmbientElement4D { unsigned int a; };
	struct AmbientElement4E { unsigned int a; };
	struct AmbientElement20 { unsigned int a[5]; };
	struct AmbientElement790 { unsigned char a[0x790]; };
	struct AmbientElement10 { unsigned int a[4]; };
	struct AmbientElement8C { unsigned int a, b; };
	struct AmbientElement12 { unsigned int a[3]; };

	// What the parked car cloud manager is made from (0x60 bytes; 0x104E7D00 starts it with its defaults)
	struct CloudConfig
	{
		CloudConfig();

		bool unknown0;
		int unknown4;
		int unknown8;
		int unknownC;
		int unknown10;
		int unknown14;
		float unknown18;
		float unknown1C;
		float unknown20[7];
		float unknown3C;
		float unknown40;
		float unknown44;
		float unknown48;
		float unknown4C;
		int unknown50;
		int unknown54;
		int unknown58;
		int unknown5C;
	};

	class AmbientManager
	{
	public:
		// 0x1041FA40
		explicit AmbientManager(const AmbientConfig* newConfig);
		// 0x10411FF0: adds the car to the list its record points at (this is not read)
		void AddVehicle(VehicleBehaviourAmbient* vehicle);
		// 0x104120F0: takes the car out of the manager's list
		void RemoveVehicle(VehicleBehaviourAmbient* vehicle);
		// 0x1040A110: lets go of the name a car was registered under (the flag is the car's)
		void ReleaseName(const core::Name<core::CaseSensitiveKey>& name, bool flag);
		// 0x1041F210: registers the script natives
		void RegisterScript();

		AmbientArray12 unknown0;
		unsigned char unknownC[4];
		container::ArrayDynamicHeap<AmbientElement8A> unknown10;
		AmbientArray12 unknown20;
		unsigned char unknown2C[4];
		AmbientArray12 unknown30;
		unsigned char unknown3C[4];
		bool unknown40;
		bool unknown41;
		bool unknown42;
		bool unknown43;
		AmbientConfig config;
		AmbientBlock unknownE4;
		AmbientBlock unknown170;
		int unknown1FC;
		unsigned int unknown200;
		unsigned int unknown204;
		unsigned int unknown208;
		NavMesh* unknown20C;
		container::ArrayDynamicHeap<AmbientElement4A> unknown210;
		container::ArrayDynamicHeap<AmbientElement4B> unknown220;
		container::ArrayDynamicHeap<AmbientElement20> unknown230;
		container::ArrayDynamicHeap<AmbientElement4C> unknown240;
		container::ArrayDynamicHeap<AmbientElement790> unknown250;
		container::ArrayDynamicHeap<AmbientElement790> unknown260;
		AmbientPool<AmbientElement10> unknown270;
		float unknown280;
		float unknown284;
		math::Vector unknown288;
		math::Vector unknown294;
		int unknown2A0;
		int unknown2A4;
		bool unknown2A8;
		unsigned char unknown2A9[0x42C - 0x2A9];
		AmbientPoint unknown42C;
		AmbientPoint unknown43C;
		AmbientPoint unknown44C;
		AmbientPoint unknown45C;
		AmbientPoint unknown46C;
		AmbientPoint unknown47C;
		AmbientPoint unknown48C;
		AmbientPoint unknown49C;
		AmbientPoint unknown4AC;
		AmbientPoint unknown4BC;
		AmbientPoint unknown4CC;
		bool unknown4DC;
		math::Vector unknown4E0;
		math::Vector unknown4EC;
		float unknown4F8;
		float unknown4FC;
		float unknown500;
		float unknown504;
		float unknown508;
		int unknown50C;
		int unknown510;
		bool unknown514;
		bool unknown515;
		bool unknown516;
		core::Name<core::CaseSensitiveKey> unknown518;
		container::ArrayDynamicHeap<AmbientElement4D> unknown520;
		container::ArrayDynamicHeap<AmbientElement8B> unknown530;
		AmbientPool<AmbientElement8C> unknown540;
		ParkedCarCloudManager* unknown550;
		bool unknown554;
		int unknown558;
		int unknown55C;
		float unknown560;
		unsigned char unknown564[4];
		core::Name<core::CaseSensitiveKey> unknown568[7];
		int unknown5A0;
		bool unknown5A4;
		container::ArrayDynamicHeap<AmbientElement4E> unknown5A8;
		AmbientArray16 unknown5B8;
		int unknown5C8;
		AmbientArray16 unknown5CC;
		AmbientPool<AmbientElement12> unknown5DC;
		AmbientPool<AmbientElement10> unknown5EC;
		float unknown5FC;
		bool unknown600;
		bool unknown601;
		bool unknown602;
		bool unknown603;
		int unknown604;
		int unknown608;
		int unknown60C;
		int unknown610;
		bool unknown614;
	};

	// 0x11267760
	extern AmbientManager* gAmbientManager;
}

#endif
