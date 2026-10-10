// engine::camera::CameraResetMessage / CameraCutMessage (names from the RTTI): intrusive messages without payload,
// ids 2 and 3. The destructors are inline: the engine's deleting destructors store the base vftable themselves. The
// constructors are inline too, defined in director.cpp: the Director's Reset / Update construct the messages in
// place, and the out-of-line copies at 0x107DD9F0 / 0x107DDA20 are the COMDATs the incremental link kept.
#ifndef ENGINE_CAMERA_CAMERAMESSAGES_H
#define ENGINE_CAMERA_CAMERAMESSAGES_H

#include "code/engine/message.h"

namespace engine
{
	namespace camera
	{
		class CameraResetMessage : public IntrusiveMessage
		{
		public:
			CameraResetMessage();
			virtual ~CameraResetMessage()
			{
			}
		};

		class CameraCutMessage : public IntrusiveMessage
		{
		public:
			CameraCutMessage();
			virtual ~CameraCutMessage()
			{
			}
		};
	}
}

#endif
