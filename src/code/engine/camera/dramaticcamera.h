// engine::camera::DramaticCamera (RTTI name; base engine::camera::Camera): the camera that plays camera animations
// for a cinematic. It keeps up to four animations to play one after the other, samples their position tracks and
// checks them against the world with rays. Unit 0x1084EE20 - 0x1084FF91 (no assert path; the directory and file names
// are guesses). Member and method names are guesses.
#ifndef ENGINE_CAMERA_DRAMATICCAMERA_H
#define ENGINE_CAMERA_DRAMATICCAMERA_H

#include "code/engine/camera/camera.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/math/matrix.h"
#include "code/math/vector.h"
#include "code/pure3d/camera.h"
#include "code/pure3d/cameraanimationcontroller.h"

namespace pure3d
{
	class Animation;
}

namespace engine
{
	namespace camera
	{
		// One animation of the queue (0x18 bytes)
		struct DramaticAnimation
		{
			pure3d::Animation* animation;
			float start;  // +0x04
			float end;  // +0x08
			float speed;  // +0x0C
			bool unknown10;
			bool unknown11;
			float unknown14;
		};

		class DramaticCamera : public Camera
		{
		public:
			// 0x1084EF00
			DramaticCamera();
			// vftable slot 0 (0x1084F400 deletes); the destructor body is 0x1084F060
			virtual ~DramaticCamera();
			// vftable slot 3 (0x1084F9D0)
			virtual void Update(float delta, float time, int flags);
			// vftable slot 4 (0x1084EE00)
			virtual bool Slot4();
			// vftable slot 10 (0x1084F0B0): back to the initial state
			virtual void Reset();

			// 0x1084ED90
			void SetUnknown12C(int first, int second);
			// 0x1084EDB0: stops the animation that plays
			void Stop();
			// 0x1084EDE0
			bool IsOver() const;
			// 0x1084EE10: the mask of what the rays hit
			void SetCollisionMask(int value);
			// 0x1084F120: queues an animation: the part between the frames start and end (an end below zero: its
			// end), played at speed; unknown14 must not be negative, and with neither flag set nothing is queued
			bool AddAnimation(pure3d::Animation* newAnimation, float startFrame, float endFrame, float newSpeed,
				bool newUnknown10, bool newUnknown11, float newUnknown14);
			// 0x1084F7C0: starts playing the queued animations around a game object (the offset is turned by the
			// object's transform); the queue is emptied afterwards. False when it plays already, when nothing is
			// queued or when no animation fits
			bool Play(HandleBase object, const math::Vector* offset, bool newUnknownD2, float delay, float duration,
				float tail, float limit);
			// 0x1084F420: the index of the queued animation that fits a start (matrix) and a point (name and parameters
			// guessed), or -1; sets the flags at 0xD1 and 0xD2
			int FindAnimation(const math::Matrix* start, float limit, const math::Vector* point, bool* checked);
			// 0x1084EE20: the rays hit the objects between two points
			void QueryRay(const math::Vector* from, const math::Vector* to);

			DramaticAnimation animations[4];  // +0x48
			int animationCount;  // +0xA8
			int collisionMask;  // +0xAC
			float unknownB0;
			float unknownB4;
			float unknownB8;
			float unknownBC;
			float unknownC0;
			float unknownC4;
			bool playing;  // +0xC8
			float unknownCC;
			bool unknownD0;
			bool unknownD1;
			bool unknownD2;
			math::Vector offsetWorld;  // +0xD4
			math::Matrix matrix;  // +0xE0
			HandleBase unknown120;
			pure3d::CameraAnimationController* controller;  // +0x124
			pure3d::Camera* animationCamera;  // +0x128
			int unknown12C;
			int unknown130;
		};
	}
}

#endif
