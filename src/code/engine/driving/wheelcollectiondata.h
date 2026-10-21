// engine::driving::WheelCollectionData (RTTI and reflection names): a content library object that holds the wheels of
// a vehicle: the physics object factory to make the vehicle's body from, its skeleton and one record per wheel
// (WheelData, a name with a handle and the numbers of the wheel). When it is loaded without wheels it makes four
// default ones. Unit 0x10907020 - 0x10907E90 (no assert path; the directory and file name are guesses). The reflected
// member names are original; the rest is guessed. WheelData's own reflection is in another unit (0x10937570 -
// 0x10937640).
#ifndef ENGINE_DRIVING_WHEELCOLLECTIONDATA_H
#define ENGINE_DRIVING_WHEELCOLLECTIONDATA_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/container/arraydynamicstatic.h"
#include "code/container/string.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/pure3d/pose.h"

namespace ravenphysics
{
	class PhysicsObjectFactory;
}

namespace engine
{
	namespace driving
	{
		// One wheel (0x68 bytes): a name, then two words and seven floats; the members are not recovered
		struct WheelData
		{
			// 0x109375F0 (another unit)
			WheelData();
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			container::StringC<64> name;  // +0
			unsigned int unknown44;  // +0x44
			unsigned int unknown48;
			float unknown4C;
			float unknown50;
			float unknown54;
			float unknown58;
			float unknown5C;
			float unknown60;
			float unknown64;
		};

		class WheelCollectionData : public content::MetaLoadObject
		{
		public:
			typedef container::ArrayDynamic<WheelData, container::AllocatorNew> WheelArray;

			// 0x10907B60
			WheelCollectionData();
			// 0x10907B90 (deleting destructor 0x10907C20)
			virtual ~WheelCollectionData();

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// 0x10907060
			WheelArray* GetWheels();
			// 0x10907C40: when there are a physics object and a skeleton, makes four wheels at the corners of the
			// physics object's bounds
			void CreateDefaultWheels();

			// vftable slot 3 (0x10907DB0)
			virtual void Slot3(int unused);

			ravenphysics::PhysicsObjectFactory* physicsObject;  // +8
			pure3d::Skeleton* skeleton;  // +0xC
			WheelArray wheels;  // +0x10
			// The word behind the array (the arrays of this kind are followed by one; never touched here)
			int unknown1C;  // +0x1C
		};
	}
}

namespace container
{
	// The wheels are too large for the compiler to inline the assignment of their elements
	template<> struct ArrayEraseInline<engine::driving::WheelData>
	{
		enum
		{
			value = 0
		};
	};
}

#endif
