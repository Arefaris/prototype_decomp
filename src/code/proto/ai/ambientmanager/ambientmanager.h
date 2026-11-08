// proto::AmbientManager (RTTI names Method0 .. Method3 / Closure of proto::AmbientManager for its script natives; the
// singleton is 0x11267760): the manager of the ambient pedestrians and vehicles. The unit has no assert path, so the
// file name, the member names and the layout above the constructor's reach are guesses; the constructor
// (0x1041FA40) sets 0x618 bytes up from a configuration the game hands it.
#ifndef PROTO_AI_AMBIENTMANAGER_AMBIENTMANAGER_H
#define PROTO_AI_AMBIENTMANAGER_AMBIENTMANAGER_H

#include "code/container/arraydynamic.h"
#include "code/core/heap.h"
#include "code/core/name.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/math/vector.h"
#include "code/ravenphysics/context.h"

namespace proto
{
	class AmbientSpawner;
	class AmbientSpawner;
	class NavMesh;
	class ParkedCarCloudManager;
	class VehicleBehaviourAmbient;

	// The sizes and counts the manager is made from (0xA0 bytes, copied into the manager at +0x44); only what the
	// constructor reads is named
	struct AmbientConfig
	{
		// 0x104204A0: the defaults
		AmbientConfig();

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
		unsigned int unknown30;
		unsigned int unknown34;
		float unknown38;
		float unknown3C;
		float unknown40;
		float unknown44;
		float unknown48;
		float unknown4C;
		unsigned int unknown50;
		float unknown54;
		float unknown58;
		unsigned int unknown5C;
		unsigned int unknown60;
		unsigned int unknown64;
		unsigned int unknown68;
		unsigned int unknown6C;
		unsigned int unknown70;
		unsigned int unknown74;
		unsigned int unknown78;
		float unknown7C;
		unsigned int unknown80;
		float unknown84;
		float unknown88;
		float unknown8C;
		float unknown90;
		float unknown94;
		float unknown98;
		float unknown9C;
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

	// A fixed block of count elements from a heap (begin, end, capacity and the heap after them), made once; the
	// allocator is the same object the dynamic arrays carry, so the heap arrives in the call as its member
	template<class T> struct AmbientPool
	{
		AmbientPool(unsigned int count, int newHeap) : allocator(newHeap)
		{
			begin = (T*)allocator.Alloc(count * sizeof(T));
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
		container::AllocatorCoreAligned<16> allocator;
	};

	// A flag and a point (0x10 bytes; names are guesses)
	struct AmbientTarget
	{
		AmbientTarget() : position(0.0f, 0.0f, 0.0f)
		{
			flag = false;
		}
		bool flag;
		math::Vector position;
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

	// A word that starts at -1 through its own constructor (an index or a handle; the engine's constructor stores it
	// where a member object's inline constructor does, between the plain members around it)
	struct AmbientIndex
	{
		AmbientIndex() : value(-1)
		{
		}
		int value;
	};

	// Objects of 0x8C bytes the manager holds two of (0x104279C0 makes one)
	struct AmbientBlock
	{
		AmbientBlock();
		unsigned char unknown0[0x8C];
	};

	// The elements of the manager's arrays; only their sizes are known
	struct AmbientElement8A { unsigned int a, b; bool operator!=(const AmbientElement8A& other) const { return a != other.a; } };
	struct AmbientElement8B { unsigned int a, b; bool operator!=(const AmbientElement8B& other) const { return a != other.a; } };
	struct AmbientElement4A { unsigned int a; bool operator!=(const AmbientElement4A& other) const { return a != other.a; } };
	struct AmbientElement4B { unsigned int a; bool operator!=(const AmbientElement4B& other) const { return a != other.a; } };
	struct AmbientElement4C { unsigned int a; bool operator!=(const AmbientElement4C& other) const { return a != other.a; } };
	struct AmbientElement4D { unsigned int a; bool operator!=(const AmbientElement4D& other) const { return a != other.a; } };
	struct AmbientElement4E { unsigned int a; bool operator!=(const AmbientElement4E& other) const { return a != other.a; } };
	struct AmbientElement20 { unsigned int a[5]; bool operator!=(const AmbientElement20& other) const { return a[0] != other.a[0]; } };
	struct AmbientElement790 { unsigned char a[0x790]; bool operator!=(const AmbientElement790& other) const { return a[0] != other.a[0]; } };
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
		// 0x104138E0 / 0x10411D20 (names unknown): the first answers whether the object has the ambient attribute, the second
		// puts the object's visibility client right
		bool Unknown104138E0(engine::GameObjectHandle handle);
		void Unknown10411D20(engine::GameObjectHandle handle);
		// 0x10411FF0: adds the car to the list its record points at (this is not read)
		void AddVehicle(VehicleBehaviourAmbient* vehicle);
		// 0x104120F0: takes the car out of the manager's list
		void RemoveVehicle(VehicleBehaviourAmbient* vehicle);
		// 0x1040A110: lets go of the name a car was registered under (the flag is the car's)
		void ReleaseName(const core::Name<core::CaseSensitiveKey>& name, bool flag);
		// 0x1041F210: registers the script natives
		void RegisterScript();
		// 0x10409990 / 0x104099B0: keeps the spawner under the name it makes objects of (the vehicle spawners / the
		// pedestrian spawners); 0x104099A0 / 0x104099C0: a hook the same spawners call when they are ready (nothing)
		void AddVehicleSpawner(AmbientSpawner* spawner);
		void VehicleSpawnerReady(AmbientSpawner* spawner);
		void AddPedestrianSpawner(AmbientSpawner* spawner);
		void PedestrianSpawnerReady(AmbientSpawner* spawner);
		// 0x1041C190: how many pedestrians and vehicles the physics area lets in (1.0 all, 0.0 none; name guess)
		void SetAreaDensity(ravenphysics::ObjectHandle area, float pedestrians, float vehicles);
		// The script natives amb_SetMaxVehicles (0x10409CF0: nothing to set), amb_SetMaxCharacters, amb_SetSpawnAreaSize,
		// amb_SetNearSpawnDist, amb_SetFarSpawnDist, amb_SetPedsGlobalDensityScale, amb_SetVehiclesGlobalDensityScale,
		// amb_SetPercentInfectedLevelZero, amb_SetInMissionBriefing, amb_SetPercentageLowMorale and
		// amb_SetIgnoreDeadSphereLocaters (names of the members they set are guesses)
		void SetMaxVehicles(unsigned int count);
		void SetMaxCharacters(unsigned int count);
		void SetFarSpawnDistance(float distance);
		void SetNearSpawnDistance(float distance);
		void SetSpawnAreaSize(float size);
		void SetPedestrianDensityScale(float scale);
		void SetPercentInfectedLevelZero(float percent);
		void SetVehicleDensityScale(float scale);
		void SetInMissionBriefing(bool briefing);
		void SetPercentageLowMorale(float percent);
		void SetIgnoreDeadSphereLocaters(bool ignore);
		// amb_OnCameraSpawnFinished (0x1040A0B0) and amb_SpawnOnCamera (0x1040A0F0)
		bool OnCameraSpawnFinished();
		void SpawnOnCamera();

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
		AmbientTarget unknown4DC;
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
		AmbientIndex unknown604;
		int unknown608;
		int unknown60C;
		int unknown610;
		bool unknown614;
	};

	// 0x11267760
	extern AmbientManager* gAmbientManager;
}

#endif
