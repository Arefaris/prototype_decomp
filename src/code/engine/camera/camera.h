// engine::camera::Camera (RTTI name): only the members the Director touches are known; everything else is padding
// until the camera units are reconstructed. Member and method names are guesses.
#ifndef ENGINE_CAMERA_CAMERA_H
#define ENGINE_CAMERA_CAMERA_H

namespace engine
{
	namespace camera
	{
		class Camera
		{
		public:
			virtual ~Camera()
			{
			}
			// vftable slot 1
			virtual void Update(float delta, float time, int flags) = 0;

			int unknown4;
			// Index of the player this camera belongs to (the Director keeps two cameras per player)
			int playerIndex;
			int unknownC;
			int unknown10;
			int unknown14;
			// 0 or 1: which of the player's two camera slots
			int kind;
			unsigned char unknown1C;
			unsigned char unknown1D;
			// Set by the camera when its update cut; the Director broadcasts a CameraCutMessage
			bool cut;
			unsigned char unknown1F[0x7ac - 0x1f];
			bool active;
			bool unknown7AD;

			int GetPlayerIndex() const;
			bool IsActive() const;
			void SetUnknown7AD(bool value);
			// 0x1084E260: back to the default state (another unit)
			void Reset();
			// 0x1084DF40 (another unit)
			void StartTransition(int target, float time);
		};
	}
}

#endif
