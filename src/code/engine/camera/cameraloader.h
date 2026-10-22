// engine::camera::CameraLoader (RTTI and reflection names): a content library object that describes a camera of a
// level: the camera object itself, the names of the avatar it follows and of the cinematographer that drives it, and
// whether it is active when it is spawned. Unit 0x109067F0 - 0x10906B20 (no assert path; the directory and file name
// are guesses). The reflected member names are original; the rest is guessed.
#ifndef ENGINE_CAMERA_CAMERALOADER_H
#define ENGINE_CAMERA_CAMERALOADER_H

#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/camera/camera.h"

namespace engine
{
	namespace camera
	{
		// The kinds of cinematographer a camera can be driven by (the reflection names the enumeration; its values
		// come with its unit, 0x1084DE40)
		enum CinematographerType
		{
			CINEMATOGRAPHER_DEFAULT_VIEW = 0,
			CINEMATOGRAPHER_SECOND_VIEW = 1
		};
	}
}

namespace content
{
	template<> void EnumInfo<engine::camera::CinematographerType>::Get(const char** name, const EnumValue** values,
		int* count, const char** code);
}

namespace engine
{
	namespace camera
	{
		class CameraLoader : public content::MetaLoadObject
		{
		public:
			// 0x10906940
			CameraLoader();
			virtual ~CameraLoader();

			// The class's reflection
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// 0x109068C0: the name of the avatar the camera follows
			core::Name<core::CaseSensitiveKey> GetAvatarName() const;

			// vftable slot 3 (0x109069A0): once the object is loaded, hands the camera to the director
			virtual void Slot3(int unused);
			// vftable slot 4
			virtual bool IsReady();

			// The camera the object holds (deleted with it)
			Camera* camera;  // +0x08
			int unknownC;
			core::Name<core::CaseSensitiveKey> avatarName;  // +0x10
			core::Name<core::CaseSensitiveKey> cinematographerName;  // +0x18
			bool spawnActive;  // +0x20
			int type;  // +0x24
		};
	}
}

#endif
