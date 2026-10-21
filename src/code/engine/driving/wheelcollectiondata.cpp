#include "code/engine/driving/wheelcollectiondata.h"
#include "code/core/refptr.h"
#include "code/ravenphysics/physicsobjectfactory.h"
#include <new>

namespace engine
{
	namespace driving
	{
#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

		// FUNCTION: ENGINE 0x10907020
		content::ClassInfo* WheelCollectionData::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "WheelCollectionData";
			sInfo.code = "p";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x109075A0
		content::MemberList* WheelCollectionData::GetMembers()
		{
			static content::MemberList sList;
			static content::MemberInfo sMembers[] =
			{
				{ content::GetReferenceMetaType<WheelCollectionData, ravenphysics::PhysicsObjectFactory>("p"),
					ENGINE_OFFSET(WheelCollectionData, physicsObject), "physicsObject" },
				{ content::GetReferenceMetaType<WheelCollectionData, pure3d::Skeleton>("p"),
					ENGINE_OFFSET(WheelCollectionData, skeleton), "skeleton" },
				{ content::GetArrayDynamicMetaType<WheelCollectionData, WheelArray>(
					content::GetClassMetaType<WheelData>(), "p"), ENGINE_OFFSET(WheelCollectionData, wheels),
					"wheels" }
			};
			sList.members = sMembers;
			sList.count = 3;
			return &sList;
		}

		// FUNCTION: ENGINE 0x10907B60
		WheelCollectionData::WheelCollectionData() : physicsObject(0), skeleton(0)
		{
		}

		// FUNCTION: ENGINE 0x10907060
		WheelCollectionData::WheelArray* WheelCollectionData::GetWheels()
		{
			return &wheels;
		}

		// FUNCTION: ENGINE 0x10907B90
		WheelCollectionData::~WheelCollectionData()
		{
			core::SafeRelease(skeleton);
			core::SafeRelease(physicsObject);
		}

		// FUNCTION: ENGINE 0x10907DB0
		void WheelCollectionData::Slot3(int unused)
		{
			CreateDefaultWheels();
		}
	}
}

namespace container
{
	template class ArrayDynamic<engine::driving::WheelData, AllocatorNew>;
}


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10907070
// FUNCTION: ENGINE 0x10907080
// FUNCTION: ENGINE 0x109070D0
// FUNCTION: ENGINE 0x10907140
// FUNCTION: ENGINE 0x10907160
// FUNCTION: ENGINE 0x10907170
// FUNCTION: ENGINE 0x10907180
// FUNCTION: ENGINE 0x109071D0
// FUNCTION: ENGINE 0x109071E0
// FUNCTION: ENGINE 0x109071F0
// FUNCTION: ENGINE 0x10907210
// FUNCTION: ENGINE 0x10907240
// FUNCTION: ENGINE 0x10907250
// FUNCTION: ENGINE 0x10907260
// FUNCTION: ENGINE 0x109072D0
// FUNCTION: ENGINE 0x10907340
// FUNCTION: ENGINE 0x10907360
// FUNCTION: ENGINE 0x10907370
// FUNCTION: ENGINE 0x10907390
// FUNCTION: ENGINE 0x109073E0
// FUNCTION: ENGINE 0x10907430
// FUNCTION: ENGINE 0x10907510
// FUNCTION: ENGINE 0x10907540
// FUNCTION: ENGINE 0x10907680
// FUNCTION: ENGINE 0x109076E0
// FUNCTION: ENGINE 0x10907720
// FUNCTION: ENGINE 0x10907750
// FUNCTION: ENGINE 0x10907790
// FUNCTION: ENGINE 0x109077C0
// FUNCTION: ENGINE 0x10907940
// FUNCTION: ENGINE 0x10907970
// FUNCTION: ENGINE 0x10907A30
// FUNCTION: ENGINE 0x10907AD0
