// engine::driving::VehiclePhysicsAttributes, CarPhysicsAttributes and HelicopterPhysicsAttributes (RTTI and
// reflection names): the content library objects that describe how a vehicle behaves. The attributes of a vehicle
// hold its mass attributes; those of a car the suspension and control attributes (and two more groups the reflection
// leaves out), those of a helicopter the control attributes. The groups are plain reflected structs of another unit
// (0x10934120 - 0x10937200): only their size, constructor and reflection are known here. The reflected member names
// are original; the rest is guessed.
#ifndef ENGINE_DRIVING_PHYSICSATTRIBUTES_H
#define ENGINE_DRIVING_PHYSICSATTRIBUTES_H

#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/math/vector.h"

namespace engine
{
	namespace driving
	{
		// 0x10934120 (constructor), 0x109340E0 / 0x109343D0 (reflection): 0x1C bytes
		struct VehicleMassAttributes
		{
			VehicleMassAttributes();
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			unsigned char unknown0[0x1C];
		};

		// A vector the driving system keeps for all vehicles (0x1131B4B4; set by 0x10905A50, read by the vehicle
		// behaviours): name and meaning guessed
		const math::Vector* GetVehicleVector();
		void SetVehicleVector(const math::Vector* value);

		class VehiclePhysicsAttributes : public content::MetaLoadObject
		{
		public:
			// 0x10905B60
			VehiclePhysicsAttributes();
			virtual ~VehiclePhysicsAttributes()
			{
			}
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// 0x10905A70
			VehicleMassAttributes* GetMassAttributes()
			{
				return &massAttributes;
			}

			VehicleMassAttributes massAttributes;  // +8
		};

		// 0x10935470 (constructor), 0x10934540 / 0x10935220 (reflection): 0x40 bytes
		struct CarSuspensionAttributes
		{
			CarSuspensionAttributes();
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			unsigned char unknown0[0x40];
		};

		// 0x109355F0, 0x109355B0 / 0x10935A70: 0x3C bytes
		struct CarControlAttributes
		{
			CarControlAttributes();
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			unsigned char unknown0[0x3C];
		};

		// 0x10936BD0 (0x68 bytes) and 0x10936890 (0x124 bytes): groups the reflection does not show
		struct CarAttributesGroup3
		{
			CarAttributesGroup3();
			unsigned char unknown0[0x68];
		};
		struct CarAttributesGroup4
		{
			CarAttributesGroup4();
			unsigned char unknown0[0x124];
		};

		class CarPhysicsAttributes : public content::MetaLoadObject
		{
		public:
			// 0x10906E20
			CarPhysicsAttributes();
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// 0x10906C80 - 0x10906CB0
			CarSuspensionAttributes* GetSuspension()
			{
				return &suspension;
			}
			CarControlAttributes* GetControl()
			{
				return &control;
			}
			CarAttributesGroup3* GetGroup3()
			{
				return &group3;
			}
			CarAttributesGroup4* GetGroup4()
			{
				return &group4;
			}

			CarSuspensionAttributes suspension;  // +0x08
			CarControlAttributes control;  // +0x48
			CarAttributesGroup3 group3;  // +0x84
			CarAttributesGroup4 group4;  // +0xEC
		};

		// 0x10936CC0 (constructor), 0x10936C80 / 0x109371B0 (reflection): 0x64 bytes
		struct HelicopterControlAttributes
		{
			HelicopterControlAttributes();
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			unsigned char unknown0[0x64];
		};

		class HelicopterPhysicsAttributes : public content::MetaLoadObject
		{
		public:
			// 0x10906FC0
			HelicopterPhysicsAttributes();
			virtual ~HelicopterPhysicsAttributes()
			{
			}
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// 0x10906ED0
			HelicopterControlAttributes* GetControl()
			{
				return &control;
			}

			HelicopterControlAttributes control;  // +0x08
		};
	}
}

#endif
