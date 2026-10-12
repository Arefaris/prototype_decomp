// engine::camera::CameraResetMessage / CameraCutMessage (names from the RTTI): intrusive messages without payload,
// ids 2 and 3. Constructors and destructors are inline, defined in director.cpp: the Director's Reset / Update
// construct the messages in place, the deleting destructors inline the destructors, and the out-of-line copies
// (0x107DD9F0 / 0x107DDA20 and 0x107DDA10 / 0x107DDA40) are the COMDATs the incremental link kept.
#ifndef ENGINE_CAMERA_CAMERAMESSAGES_H
#define ENGINE_CAMERA_CAMERAMESSAGES_H

#include "code/engine/message.h"

namespace engine
{
	namespace camera
	{
		struct CameraResetMessage : public IntrusiveMessage
		{
		public:
			CameraResetMessage();
			virtual ~CameraResetMessage();
		};

		struct CameraCutMessage : public IntrusiveMessage
		{
		public:
			CameraCutMessage();
			virtual ~CameraCutMessage();
		};
	}
}

#endif
