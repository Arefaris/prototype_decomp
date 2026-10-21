// engine::RemoteCamera (RTTI and reflection names): a content library object that describes a camera that is placed
// by position, target and up vector (the reflection shows the vectors, the field of view, the clip planes and whether
// the camera is active). Unit 0x1090DA00 - 0x1090DDD0 (no assert path; the directory and file name are guesses). The
// reflected member names are original; the rest is guessed.
#ifndef ENGINE_REMOTECAMERA_H
#define ENGINE_REMOTECAMERA_H

#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/math/vector.h"

namespace engine
{
	class RemoteCamera : public content::MetaLoadObject
	{
	public:
		// 0x1090DD30
		RemoteCamera();
		virtual ~RemoteCamera()
		{
		}

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		math::Vector position;  // +8
		math::Vector target;  // +0x14
		math::Vector up;  // +0x20
		float fov;  // +0x2C
		float nearPlane;  // +0x30
		float farPlane;  // +0x34
		bool active;  // +0x38
	};
}

#endif
