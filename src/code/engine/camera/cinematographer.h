// engine::camera::Cinematographer (RTTI name, reflection name "engine::camera::Cinematographer"): the director of one
// view. The Director keeps two per player (index playerIndex * 2 + type); a Cinematographer is driven by a Camera (the
// reference at 0x48) and follows a pure3d camera, and the game's cameras are switched through it. Only the members the
// Director touches are known; everything else is padding until the unit is reconstructed. Member and method names
// are guesses.
#ifndef ENGINE_CAMERA_CINEMATOGRAPHER_H
#define ENGINE_CAMERA_CINEMATOGRAPHER_H

#include "code/core/name.h"
#include "code/engine/camera/camera.h"
#include "code/math/vector.h"

namespace math
{
	class Matrix;
}

namespace content
{
	struct ClassInfo;
	struct MemberList;
}

namespace engine
{
	namespace camera
	{
		// Whatever a view follows: only its matrix at 0x90 is known (it is a pure3d camera)
		class CameraTarget
		{
		public:
			unsigned char unknown0[0x90];
			math::Matrix* MatrixAt90()
			{
				return (math::Matrix*)(unknown0 + 0x90);
			}
		};

		class Cinematographer
		{
		public:
			virtual ~Cinematographer()
			{
			}
			// vftable slot 1
			virtual void Update(float delta, float time, int flags) = 0;

			// 0x1084DE70 / 0x1084E7E0: the class's reflection
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			int unknown4;
			// The kind of the view (the reflected enumeration CinematographerType: the second index of the Director's
			// table)
			int type;
			core::Name<core::CaseSensitiveKey> name;
			int unknown14;
			// The player the Cinematographer belongs to (the Director keeps two per player)
			int playerIndex;
			// Set by Activate; the Director only hands out the ones that are active and enabled
			bool enabled;
			unsigned char unknown1D;
			// Set when its update cut; the Director broadcasts a CameraCutMessage
			bool cut;
			unsigned char unknown1F[0x3c - 0x1f];
			// The pure3d camera the view follows; its matrix sits at 0x90
			CameraTarget* target;
			int unknown40;
			int unknown44;
			// Slot and id of the Camera driving this one (Director::GetController)
			ControllerRef controller;
			unsigned char unknown50[0x7a5 - 0x50];
			bool unknown7A5;
			unsigned char unknown7A6[0x7ac - 0x7a6];
			bool active;
			bool unknown7AD;

			// 0x107DDAC0 (the type)
			int GetType() const;
			bool IsActive() const;
			void SetUnknown7AD(bool value);
			// The target's matrix (0x107DDAF0; name guessed)
			math::Matrix* GetTargetMatrix() const;
			// 0x1084E260: back to the default state (another unit)
			void Reset();
			// 0x1084DF40 (another unit)
			void StartTransition(int target, float time);
			// 0x1084DF70 (another unit): sets the byte at 0x7a5 when the pointer at 0x5c is set
			void SetUnknown7A5(bool value);
			// 0x1084E720 (another unit): sets enabled and tells the Director
			void Activate(bool value);
		};
	}
}

#endif
