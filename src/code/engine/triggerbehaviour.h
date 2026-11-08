// engine::TriggerBehaviour and engine::MovingTriggerBehaviour (RTTI and reflection names; base engine::Behaviour): a
// volume that tells a target when game objects enter or leave it ("volume", "targetMode", "targetName", "onEnter",
// "onExit"). The target is the owner, the object that touched the volume, the master scenario or the object called
// targetName. The moving trigger follows the transform of its owner. Unit 0x1083AD20 - 0x1083B950 (no assert path;
// the file name is a guess). The reflected names are original, the rest is guessed.
#ifndef ENGINE_TRIGGERBEHAVIOUR_H
#define ENGINE_TRIGGERBEHAVIOUR_H

#include "code/container/string.h"
#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/scenariomessage.h"
#include "code/engine/trigger/volume.h"

namespace engine
{
	class TriggerBehaviour : public Behaviour
	{
	public:
		// Who gets the messages of the trigger ("Self", "Touch", "MasterScenario", "Other")
		enum Target
		{
			TARGET_SELF = 0,
			TARGET_TOUCH = 1,
			TARGET_MASTER_SCENARIO = 2,
			TARGET_OTHER = 3
		};

		// 0x1083B6C0 / 0x1083B760 / 0x1083B860
		explicit TriggerBehaviour(GameObject* newOwner);
		TriggerBehaviour(GameObject* newOwner, trigger::Volume* newVolume);
		TriggerBehaviour(GameObject* newOwner, trigger::Volume* newVolume, Target newTarget);
		// 0x1083AFC0 (the deleting destructor is 0x1083B290)
		virtual ~TriggerBehaviour();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 0 (0x1083ADD0)
		virtual void Slot0();
		// vftable slot 1 (0x1083B060): sets the volume up
		virtual void Slot1();
		// vftable slots 3 and 4 (0x1083B100, 0x1083ADE0)
		virtual void OnActiveChanged(bool active);
		virtual void Update(float dt, unsigned short mask);
		// vftable slots 5 and 6 (0x1083AE00, 0x1083B1D0)
		virtual void OnPostedMessage(Message* message);
		virtual void OnMessage(Message* message);

		// 0x1083ADF0
		void SetTargetMode(Target newTarget);
		// 0x1083B170 / 0x1083B1A0: the text the enter / exit message carries
		void SetEnterText(const char* text);
		void SetExitText(const char* text);
		// 0x1083B2B0: sends the enter (0) or exit (1) message to the target
		void SendTriggerMessage(GameObjectHandle other, int exit);

		trigger::Volume* volume;  // +0x0C
		Target targetMode;  // +0x10
		container::StringC<128> targetName;  // +0x14
		GameObjectHandle targetHandle;  // +0x98
		IntrusiveMessage* onEnter;  // +0x9C
		IntrusiveMessage* onExit;  // +0xA0
	};

	class MovingTriggerBehaviour : public TriggerBehaviour
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 4 (0x1083B200): follows the transform of the owner
		virtual void Update(float dt, unsigned short mask);
	};
}

#endif
