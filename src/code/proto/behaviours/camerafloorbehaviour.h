// proto::CameraFloorBehaviour (RTTI and reflection names; base engine::Behaviour): the heights between which the
// camera may go while the object is in view. Unit 0x103B4180 - 0x103B4310 (no assert path; the file name is a guess).
// The reflected names are original, the rest is guessed; the message handler is left to the engine.
#ifndef PROTO_BEHAVIOURS_CAMERAFLOORBEHAVIOUR_H
#define PROTO_BEHAVIOURS_CAMERAFLOORBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/message.h"

namespace proto
{
	class CameraFloorBehaviour : public engine::Behaviour
	{
	public:
		// 0x103B41C0
		explicit CameraFloorBehaviour(engine::GameObject* newOwner);
		// 0x103B4210 (deleting destructor 0x103B46A0)
		virtual ~CameraFloorBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 6 (0x103B4220, left to the engine)
		virtual void OnMessage(engine::Message* message);

		float cameraMinHeight;  // +0xC
		float cameraMaxHeight;  // +0x10
		float restoreCameraMinHeight;  // +0x14
	};
}

#endif
