#include "code/proto/ai/ambientmanager/ambientspawners.h"
#include "code/core/refptr.h"
#include "code/proto/reflectedstubs.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10420710
	content::ClassInfo* AmbientSpawner::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::AmbientSpawner";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10420750
	content::ClassInfo* VehicleSpawner::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::VehicleSpawner";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10420790
	content::ClassInfo* PedestrianSpawner::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::PedestrianSpawner";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10420940
	// NONMATCHING: the engine builds the name member's address after the second vftable store (82.9 %)
#ifdef NONMATCHING
	AmbientSpawner::AmbientSpawner() : templateName(0)
	{
	}
#endif

	// FUNCTION: ENGINE 0x10420A60
	AmbientSpawner::~AmbientSpawner()
	{
		core::SafeRelease(templateName);
	}

	// FUNCTION: ENGINE 0x10420970
	void AmbientSpawner::Slot3(int unused)
	{
	}

	// FUNCTION: ENGINE 0x10420980
	bool AmbientSpawner::IsReady()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x10420990
	bool AmbientSpawner::Slot7(void* argument)
	{
		return true;
	}

	// FUNCTION: ENGINE 0x10420A90
	void AmbientSpawner::SetName(const content::ObjectName& newName)
	{
		name = newName;
	}

	// FUNCTION: ENGINE 0x10420AA0
	VehicleSpawner::VehicleSpawner()
	{
	}

	// FUNCTION: ENGINE 0x10420B50
	VehicleSpawner::~VehicleSpawner()
	{
	}

	// FUNCTION: ENGINE 0x10420850
	bool VehicleSpawner::Slot7(void* argument)
	{
		return false;
	}

	// FUNCTION: ENGINE 0x10420AC0
	PedestrianSpawner::PedestrianSpawner() : type(0)
	{
	}

	// FUNCTION: ENGINE 0x10420AE0
	PedestrianSpawner::~PedestrianSpawner()
	{
		core::SafeRelease(type);
	}

	// FUNCTION: ENGINE 0x104208A0
	bool PedestrianSpawner::Slot7(void* argument)
	{
		return false;
	}

	// FUNCTION: ENGINE 0x10420D30
	content::MemberList* AmbientSpawner::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMetaType<AmbientSpawner, content::MetaObjectTemplate>("p"),
				PROTO_OFFSET(AmbientSpawner, templateName), "templateName" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10421060
	content::MemberList* VehicleSpawner::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<AmbientSpawner>();
		static content::BaseClassCasterImpl<AmbientSpawner, VehicleSpawner> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

	// FUNCTION: ENGINE 0x104210E0
	content::MemberList* PedestrianSpawner::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<AmbientSpawner>();
		static content::BaseClassCasterImpl<AmbientSpawner, PedestrianSpawner> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMetaType<PedestrianSpawner, NPCType>("pn"),
				PROTO_OFFSET(PedestrianSpawner, type), "type" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}
}
