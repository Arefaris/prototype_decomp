// engine::camera::Camera (RTTI name): only the members the Director touches are known; everything else is padding
// until the camera units are reconstructed. Member and method names are guesses.
#ifndef ENGINE_CAMERA_CAMERA_H
#define ENGINE_CAMERA_CAMERA_H

#include "code/math/vector.h"

namespace math
{
	class Matrix;
}

namespace engine
{
	namespace camera
	{
		// Slot and id of a registered Cinematographer
		class ControllerRef
		{
		public:
			int slot;
			int id;
		};

		// Whatever a camera follows: only its matrix at 0x90 is known
		class CameraTarget
		{
		public:
			unsigned char unknown0[0x90];
			math::Matrix* MatrixAt90()
			{
				return (math::Matrix*)(unknown0 + 0x90);
			}
		};

		class Camera
		{
		public:
			virtual ~Camera()
			{
			}
			// vftable slot 1
			virtual void Update(float delta, float time, int flags) = 0;

			// 0x106DCD70: whether a sphere (point and radius) is inside the view (the point goes through the matrix at +0x50)
			bool IsPointVisible(const math::Vector* point, float radius);

			int unknown4;
			// Index of the player this camera belongs to (the Director keeps two cameras per player)
			int playerIndex;
			int unknownC;
			int unknown10;
			int unknown14;
			// 0 or 1: which of the player's two camera slots
			int kind;
			// Set by Activate; the Director only hands out cameras that are active and enabled
			bool enabled;
			unsigned char unknown1D;
			// Set by the camera when its update cut; the Director broadcasts a CameraCutMessage
			bool cut;
			unsigned char unknown1F[0x3c - 0x1f];
			// The object the camera follows; its matrix sits at 0x90
			CameraTarget* target;
			int unknown40;
			int unknown44;
			// Slot and id of the Cinematographer driving this camera (Director::GetController)
			ControllerRef controller;
			unsigned char unknown50[0xc0 - 0x50];
			// The camera's position in the world (proto::LODRenderBehaviour's fade measures the object's distance
			// to it); name guess
			math::Vector position;
			// Read by proto::VehicleCamera's vftable slot 4 (0x10354B60); meaning unknown, name is a guess
			bool unknownCC;
			unsigned char unknownCD[0x7a5 - 0xcd];
			bool unknown7A5;
			unsigned char unknown7A6[0x7ac - 0x7a6];
			bool active;
			bool unknown7AD;

			int GetPlayerIndex() const;
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
