// engine::AdvertisementBehaviour (RTTI and reflection names; base engine::Behaviour): unit 0x10917A30 - 0x10919F50 (no
// assert path; the file name is a guess). The behaviour's class information and the mappings it lists are
// reconstructed so far; the behaviour itself is declared in reflectedclasses.h.
#include "code/engine/advertisementbehaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/surfacedefinition.h"
#include "code/engine/world/zoneset.h"
#include "code/engine/reflectedclasses.h"

namespace engine
{
	// The name of the scale attribute (attributenames.cpp)
	extern content::ObjectName gScaleName;

#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define ENGINE_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10917A30
	content::ClassInfo* AdvertisementBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::AdvertisementBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10919D70
	AdvertisementBehaviour::AdvertisementBehaviour(GameObject* newOwner) : Behaviour(newOwner), registered(false)
	{
		Listen(8, true);
		Listen2(0x100, true);
		scale = owner->FindAttribute(gScaleName);
	}

	// FUNCTION: ENGINE 0x10919DD0
	AdvertisementBehaviour::~AdvertisementBehaviour()
	{
		if (registered)
		{
			for (unsigned int i = 0; i < (unsigned int)mappings.Size(); i++)
			{
				GetZoneSet()->Unknown108951F0(&mappings[i].unknown90);
			}
		}
	}

	// FUNCTION: ENGINE 0x109197C0
	content::MemberList* AdvertisementBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Behaviour>();
		static content::BaseClassCasterImpl<Behaviour, AdvertisementBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<AdvertisementBehaviour, AdvertisementMappingArray>(
				content::GetClassMetaType<AdvertisementMapping>(), "pn"),
				ENGINE_OFFSET(AdvertisementBehaviour, mappings), "mappings" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x109179F0
	content::ClassInfo* AdvertisementMapping::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::AdvertisementMapping";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10919780
	AdvertisementMapping::AdvertisementMapping() : primitiveIndex(0), unknownA4(true), unknownA5(false)
	{
	}

	// FUNCTION: ENGINE 0x10919690
	// NONMATCHING: the engine loads the end pointer into eax before the element count division, ours into edx (39.4 %)
#ifdef NONMATCHING
	AdvertisementMapping::AdvertisementMapping(const AdvertisementMapping& other) : primitiveGroup(other.primitiveGroup),
		primitiveIndex(other.primitiveIndex), shaderInput(other.shaderInput), adPoly(other.adPoly), slot(other.slot)
	{
		unknown90 = other.unknown90;
		unknown94 = other.unknown94;
		unknown98 = other.unknown98;
		unknown9C = other.unknown9C;
		unknownA0 = other.unknownA0;
		unknownA4 = other.unknownA4;
		unknownA5 = other.unknownA5;
		unknownA8 = other.unknownA8;
		unknownAC = other.unknownAC;
	}
#endif

	// FUNCTION: ENGINE 0x10919230
	AdvertisementMapping& AdvertisementMapping::operator=(const AdvertisementMapping& other)
	{
		primitiveGroup = other.primitiveGroup;
		primitiveIndex = other.primitiveIndex;
		shaderInput = other.shaderInput;
		adPoly = other.adPoly;
		slot = other.slot;
		unknown90 = other.unknown90;
		unknown94 = other.unknown94;
		unknown98 = other.unknown98;
		unknown9C = other.unknown9C;
		unknownA0 = other.unknownA0;
		unknownA4 = other.unknownA4;
		unknownA5 = other.unknownA5;
		unknownA8 = other.unknownA8;
		unknownAC = other.unknownAC;
		return *this;
	}

	// FUNCTION: ENGINE 0x10919300
	content::MemberList* AdvertisementMapping::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<AdvertisementMapping>(true, true, "p"),
				ENGINE_NAME_OFFSET(AdvertisementMapping, primitiveGroup), "primitiveGroup" },
			{ content::GetMemberPrimitiveMetaType<AdvertisementMapping, int, 0>("pn"),
				ENGINE_OFFSET(AdvertisementMapping, primitiveIndex), "primitiveIndex" },
			{ content::GetMemberStringMetaType<0>(&((AdvertisementMapping*)content::gStringMemberBase)->shaderInput, "p"),
				content::StringBufferOffset(&((AdvertisementMapping*)content::gStringMemberBase)->shaderInput)
				+ (int)&((AdvertisementMapping*)0)->shaderInput, "shaderInput" },
			{ content::GetMemberNameMetaType<AdvertisementMapping, 0>(true, true, "p"),
				ENGINE_NAME_OFFSET(AdvertisementMapping, slot), "slot" },
			{ content::GetArrayCDynamicMetaType<AdvertisementMapping, container::ArrayCDynamic<math::Vector, 4> >(4,
				content::GetClassMetaType<math::Vector>(), "pn"), ENGINE_OFFSET(AdvertisementMapping, adPoly),
				"adPoly" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}
}

namespace container
{
	template class ArrayDynamic<engine::AdvertisementMapping, AllocatorNew>;
	template class ArrayCDynamic<math::Vector, 4>;
}


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10917A80
// FUNCTION: ENGINE 0x10917A90
// FUNCTION: ENGINE 0x10917AA0
// FUNCTION: ENGINE 0x10917AC0
// FUNCTION: ENGINE 0x10917AD0
// FUNCTION: ENGINE 0x10917AF0
// FUNCTION: ENGINE 0x10917B00
// FUNCTION: ENGINE 0x10917B50
// FUNCTION: ENGINE 0x10917BA0
// FUNCTION: ENGINE 0x10917BC0
// FUNCTION: ENGINE 0x10917C30
// FUNCTION: ENGINE 0x10917C70
// FUNCTION: ENGINE 0x10917C80
// FUNCTION: ENGINE 0x10917CA0
// FUNCTION: ENGINE 0x10918CC0
// FUNCTION: ENGINE 0x10918CD0
// FUNCTION: ENGINE 0x10918D20
// FUNCTION: ENGINE 0x10918D30
// FUNCTION: ENGINE 0x10918D50
// FUNCTION: ENGINE 0x10918D70
// FUNCTION: ENGINE 0x10918D80
// FUNCTION: ENGINE 0x10918D90
// FUNCTION: ENGINE 0x10918DA0
// FUNCTION: ENGINE 0x10918DC0
// FUNCTION: ENGINE 0x10918DE0
// FUNCTION: ENGINE 0x10918E30
// FUNCTION: ENGINE 0x10918E50
// FUNCTION: ENGINE 0x10918E60
// FUNCTION: ENGINE 0x10918E70
// FUNCTION: ENGINE 0x10918E80
// FUNCTION: ENGINE 0x10918E90
// FUNCTION: ENGINE 0x10918EB0
// FUNCTION: ENGINE 0x10918ED0
// FUNCTION: ENGINE 0x10918FB0
// FUNCTION: ENGINE 0x109190E0
// FUNCTION: ENGINE 0x109190F0
// FUNCTION: ENGINE 0x10919140
// FUNCTION: ENGINE 0x10919560
// FUNCTION: ENGINE 0x10919570
// FUNCTION: ENGINE 0x10919610
// FUNCTION: ENGINE 0x10919620
// FUNCTION: ENGINE 0x10919660
// FUNCTION: ENGINE 0x109198F0
// FUNCTION: ENGINE 0x10919910
// FUNCTION: ENGINE 0x10919930
// FUNCTION: ENGINE 0x10919970
// FUNCTION: ENGINE 0x10919A50
// FUNCTION: ENGINE 0x10919A90
// FUNCTION: ENGINE 0x10919AE0
// FUNCTION: ENGINE 0x10919C70
// FUNCTION: ENGINE 0x10919CB0
// FUNCTION: ENGINE 0x10919CD0
// FUNCTION: ENGINE 0x10919D30
// FUNCTION: ENGINE 0x10919F20
// FUNCTION: ENGINE 0x109191E0
