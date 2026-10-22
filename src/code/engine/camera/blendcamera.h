// engine::camera::BlendCamera (RTTI name; base engine::camera::Camera): the camera that blends from one camera to
// another. It remembers the first camera's view when a blend begins and, while it runs, follows both cameras (the
// Cinematographer asks it for the pure3d camera of the view). Unit 0x108522B0 - 0x10853200 (no assert path; the
// directory and file names are guesses). Member and method names are guesses.
#ifndef ENGINE_CAMERA_BLENDCAMERA_H
#define ENGINE_CAMERA_BLENDCAMERA_H

#include "code/engine/camera/camera.h"
#include "code/math/vector.h"
#include "code/pure3d/camera.h"

namespace engine
{
	namespace camera
	{
		// A view as the blend sees it (0x48 bytes): where the camera is, where it looks, how it is turned and how its
		// lens is set
		struct CameraSnapshot
		{
			math::Vector position;
			math::Vector target;  // +0x0C: position + the view direction * distance
			float distance;  // +0x18
			float yaw;  // +0x1C
			float pitch;  // +0x20
			float roll;  // +0x24
			float fov;  // +0x28
			float nearPlane;  // +0x2C
			float farPlane;  // +0x30
			bool windowEnabled;  // +0x34
			float window[4];
		};

		class BlendCamera : public Camera
		{
		public:
			// 0x108523A0 (0xC0 bytes)
			BlendCamera();
			// vftable slot 0 (0x10852440 deletes); the destructor body is 0x108522C0
			virtual ~BlendCamera();
			// vftable slot 3 (0x108528A0)
			virtual void Update(float delta, float time, int flags);
			// vftable slot 4 (0x10852390): the blend has been running into its end
			virtual bool Slot4();
			// vftable slot 5 (0x10852300): the type of the camera
			virtual int GetType();
			// vftable slot 10 (0x10852460): stops the blend
			virtual void Reset();
			// vftable slot 11 (0x108522F0): does nothing
			virtual void Slot11();

			// 0x10852310: the blend has reached its end
			bool IsDone() const;
			// 0x10852330: stops the blend and forgets both cameras
			void Stop();
			// 0x10852370: how long the blend lasts
			float GetDuration() const;
			// 0x10852380: the mask of what the cameras' collision sweeps hit
			void SetCollisionMask(int value);
			// 0x10852470: takes the view of a camera
			void Capture(Camera* source, CameraSnapshot* out);
			// 0x108525A0: blends from one camera to another over time; kind 3 is the only one used (the cameras are
			// passed by value and destroyed by the callee)
			bool Begin(ControllerRef from, ControllerRef to, bool reverse, int newKind, float time);
			// 0x108526D0: the point where a ray from one point to another stops at the first thing it hits (false when it
			// hits nothing or the mask is empty)
			bool Sweep(const math::Vector* from, const math::Vector* to, math::Vector* out);

			CameraSnapshot start;  // +0x48
			ControllerRef fromCamera;  // +0x90
			ControllerRef toCamera;  // +0x98
			float unknownA0;
			float elapsed;  // +0xA4
			float duration;  // +0xA8
			int unknownAC;
			bool reverse;  // +0xB0
			bool unknownB1;
			bool unknownB2;
			bool done;  // +0xB3
			int unknownB4;
			int collisionMask;  // +0xB8
			int unknownBC;
		};
	}
}

#endif
