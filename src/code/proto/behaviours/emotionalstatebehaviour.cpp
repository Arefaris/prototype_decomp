#include "code/proto/behaviours/emotionalstatebehaviour.h"

namespace engine
{
	// 0x11265910: the name "Idle" (charactertypenames.cpp)
	extern core::Name<core::CaseSensitiveKey> gIdle;
}

namespace proto
{
	// 0x103BBB40 (another unit): the answer to the messages of type 0x2F
	void Unknown103BBB40(engine::Message* message, engine::Behaviour* behaviour);

	// FUNCTION: ENGINE 0x103D7600
	content::ClassInfo* EmotionalStateBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "EmotionalStateBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103D7640
	void EmotionalStateBehaviour::Slot1()
	{
		Listen2(4, true);
	}

	// FUNCTION: ENGINE 0x103D76A0
	EmotionalStateBehaviour::EmotionalStateBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner),
		state(engine::gIdle)
	{
		Listen(0x28, true);
		Listen(2, true);
		Listen(0x2f, true);
	}

	// FUNCTION: ENGINE 0x103D7700
	EmotionalStateBehaviour::~EmotionalStateBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x103D7710
	void EmotionalStateBehaviour::Update(float dt, unsigned short mask)
	{
	}

	// FUNCTION: ENGINE 0x103D7720
	void EmotionalStateBehaviour::Reset()
	{
		state = engine::gIdle;
	}

	// FUNCTION: ENGINE 0x103D77F0
	void EmotionalStateBehaviour::OnMessage(engine::Message* message)
	{
		switch (message->type)
		{
		case 2:
			Reset();
			break;
		case 0x28:
			switch ((unsigned short)message->id)
			{
			case 0:
				static_cast<EmotionalStateMessage*>(message)->state = state;
				break;
			case 1:
				state = static_cast<EmotionalStateMessage*>(message)->state;
				break;
			}
			break;
		case 0x2f:
			Unknown103BBB40(message, this);
			break;
		}
	}

	// FUNCTION: ENGINE 0x103D7740
	content::MemberList* EmotionalStateBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, EmotionalStateBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103D7660
