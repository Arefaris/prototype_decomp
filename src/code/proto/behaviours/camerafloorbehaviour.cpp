#include "code/proto/behaviours/camerafloorbehaviour.h"
#include "code/proto/fightitems/motion/motion_boundary.h"
#include "code/proto/camera/cameramanager.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x103B4180
	content::ClassInfo* CameraFloorBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::CameraFloorBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103B41C0
	CameraFloorBehaviour::CameraFloorBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner),
		cameraMinHeight(0.0f), cameraMaxHeight(1000000000000.0f), restoreCameraMinHeight(0.0f)
	{
		Listen(0xd, true);
	}

	// FUNCTION: ENGINE 0x103B4210
	CameraFloorBehaviour::~CameraFloorBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x103B4150
	bool WorldTriggerCollisionCallback::IsInCameraFloor() const
	{
		return cameraFloorCount > 0;
	}

	// FUNCTION: ENGINE 0x103B4160
	void WorldTriggerCollisionCallback::EnterCameraFloor()
	{
		cameraFloorCount++;
	}

	// FUNCTION: ENGINE 0x103B4170
	void WorldTriggerCollisionCallback::LeaveCameraFloor()
	{
		cameraFloorCount--;
	}

	// FUNCTION: ENGINE 0x103B4220
	void CameraFloorBehaviour::OnMessage(engine::Message* message)
	{
		if (message->type == 0xd)
		{
			switch ((unsigned short)message->id)
			{
			case 4:
				gWorldTriggerCollisionCallback->cameraFloorCount--;
				if (gWorldTriggerCollisionCallback->cameraFloorCount <= 0)
				{
					gCameraManager->SetCameraMinHeight(restoreCameraMinHeight);
					gCameraManager->SetCameraMaxHeight(1000000000000.0f);
				}
				break;
			case 3:
				gWorldTriggerCollisionCallback->cameraFloorCount++;
				gCameraManager->SetCameraMinHeight(cameraMinHeight);
				gCameraManager->SetCameraMaxHeight(cameraMaxHeight);
				break;
			}
		}
	}

	// FUNCTION: ENGINE 0x103B4910
	content::MemberList* CameraFloorBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, CameraFloorBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<CameraFloorBehaviour, float, 0>("p"),
				PROTO_OFFSET(CameraFloorBehaviour, cameraMinHeight), "cameraMinHeight" },
			{ content::GetMemberPrimitiveMetaType<CameraFloorBehaviour, float, 1>("p"),
				PROTO_OFFSET(CameraFloorBehaviour, cameraMaxHeight), "cameraMaxHeight" },
			{ content::GetMemberPrimitiveMetaType<CameraFloorBehaviour, float, 2>("p"),
				PROTO_OFFSET(CameraFloorBehaviour, restoreCameraMinHeight), "restoreCameraMinHeight" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103B4660
// FUNCTION: ENGINE 0x103B4670
// FUNCTION: ENGINE 0x103B46A0
// FUNCTION: ENGINE 0x103B47F0
// FUNCTION: ENGINE 0x103B4830
// FUNCTION: ENGINE 0x103B4870
