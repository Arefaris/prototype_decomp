#include "code/proto/messages/targetselectionmessages.h"

// A function that constructs each message with the expansion of inline functions off: the compiler keeps the out-of-line
// copy of the constructor and of the destructor the engine has too
#pragma inline_depth(0)
namespace
{
	void EmitGetDynamicAllianceRatioMsg(engine::GameObjectHandle handle)
	{
		proto::GetDynamicAllianceRatioMsg message(handle);
	}

	void EmitGetTokenScoreMsg(engine::GameObjectHandle handle)
	{
		proto::GetTokenScoreMsg message(handle);
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103FED60
// FUNCTION: ENGINE 0x103FEDA0
// FUNCTION: ENGINE 0x103FEDB0
// FUNCTION: ENGINE 0x103FEDE0
// FUNCTION: ENGINE 0x103FF4E0
// FUNCTION: ENGINE 0x103FF510
