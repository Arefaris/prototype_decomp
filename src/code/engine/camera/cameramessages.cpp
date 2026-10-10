#include "code/engine/camera/cameramessages.h"

namespace engine
{
	namespace camera
	{
		// FUNCTION: ENGINE 0x107DD9F0
		CameraResetMessage::CameraResetMessage() : IntrusiveMessage(sizeof(CameraResetMessage), 2)
		{
		}

		// FUNCTION: ENGINE 0x107DDA20
		CameraCutMessage::CameraCutMessage() : IntrusiveMessage(sizeof(CameraCutMessage), 3)
		{
		}
	}
}
