// The actions of the camera clipping plane, camera animation and time dilation tracks (unit 0x108F20C0 - 0x108F2B00,
// no assert path; file name guessed). The tracks are in cameratracks.cpp.
#ifndef ENGINE_FIGHT_CAMERAACTIONS_H
#define ENGINE_FIGHT_CAMERAACTIONS_H

#include "code/core/linklist.h"
#include "code/engine/fight/cameratracks.h"
#include "code/engine/fight/effecttrack.h"
#include "code/engine/fight/nisactions.h"

namespace engine
{
	namespace camera
	{
		class Camera;
		class AnimatedCamera;
	}

	// RTTI: engine::CameraClipPlaneAction (9 vftable slots, size 0x3C): sets the clipping planes of the active camera
	class CameraClipPlaneAction : public fight::Action
	{
	public:
		// 0x108F2150
		CameraClipPlaneAction(CameraClippingPlanesTrack* newTrack, core::IRefCount* newOwner);
		// 0x108F20C0
		virtual ~CameraClipPlaneAction();

		// vftable slot 5 (0x108F2220) and slot 6 (0x108F22C0)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();

		core::Link<CameraClippingPlanesTrack> link;  // +0x1C
		core::IRefCount* owner;  // +0x28
		camera::AnimatedCamera* camera;  // +0x2C
		bool unknown30;
		float nearPlane;  // +0x34
		float farPlane;  // +0x38
	};

	// RTTI: engine::CameraAnimationAction (9 vftable slots, size 0x30)
	class CameraAnimationAction : public fight::Action
	{
	public:
		// 0x108F24F0
		CameraAnimationAction(CameraAnimationTrack* newTrack, core::IRefCount* newOwner);
		// 0x108F2460
		virtual ~CameraAnimationAction();

		// vftable slot 5 (0x108F25A0), slot 6 (0x108F27E0) and slot 7 (0x108F2790)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();
		virtual bool Slot7(int arg, float value);

		core::Link<CameraAnimationTrack> link;  // +0x1C
		core::IRefCount* owner;  // +0x28
		int unknown2c;
	};

	// RTTI: engine::TimeDilationAction (9 vftable slots, size 0x30): scales the simulation time while it runs
	class TimeDilationAction : public fight::Action
	{
	public:
		// 0x108F2A10
		explicit TimeDilationAction(TimeDilationTrack* newTrack);
		// 0x108F2980
		virtual ~TimeDilationAction();

		// vftable slot 5 (0x108F2AA0), slot 6 (0x108F28E0) and slot 7 (0x108F28C0)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();
		virtual bool Slot7(int arg, float value);

		core::Link<TimeDilationTrack> link;  // +0x1C
		float previousScale;  // +0x28
		float elapsed;  // +0x2C
	};
}

#endif
