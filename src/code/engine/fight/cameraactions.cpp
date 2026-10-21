// The actions of the camera clipping plane, camera animation and time dilation tracks (unit 0x108F20C0 - 0x108F2B00,
// no assert path; file name guessed). The tracks are in cameratracks.cpp.
#include "code/engine/fight/cameraactions.h"
#include "code/engine/system/simulationdriver.h"

namespace engine
{
	// What the owner is seen as: an IRefCount-derived object whose kind says whether it is a game object
	struct CameraOwner : core::IRefCount
	{
		int unknown4;
		unsigned int kind;  // +0x8
	};

	// FUNCTION: ENGINE 0x108F2150
	// EQUIVALENT: the engine tests the owner's kind with add eax, 0xFFFEFFFB where ours has sub eax, 0x10005 (the same value), and
	// the owner and the member's address swap ecx and edx; every other instruction is the engine's
	CameraClipPlaneAction::CameraClipPlaneAction(CameraClippingPlanesTrack* newTrack, core::IRefCount* newOwner)
		: fight::Action(0x600), link(newTrack), owner(0), camera(0), unknown30(true), nearPlane(0.01f), farPlane(1000.0f)
	{
		CameraOwner* object = (CameraOwner*)newOwner;
		AssignNISRef(&owner, object == 0 ? 0 : (object->kind + 0xfffefffb > 0xfffa ? 0 : newOwner));
	}

	// FUNCTION: ENGINE 0x108F20C0
	CameraClipPlaneAction::~CameraClipPlaneAction()
	{
		ReleaseNISRef(&owner);
	}

	// FUNCTION: ENGINE 0x108F2310
	fight::Action* CameraClippingPlanesTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		return new CameraClipPlaneAction(this, owner);
	}

	// FUNCTION: ENGINE 0x108F24F0
	// EQUIVALENT: the engine tests the owner's kind with add eax, 0xFFFEFFFB where ours has sub eax, 0x10005 (the same value), and
	// the owner and the member's address swap ecx and edx; every other instruction is the engine's
	CameraAnimationAction::CameraAnimationAction(CameraAnimationTrack* newTrack, core::IRefCount* newOwner)
		: fight::Action(0xE00), link(newTrack), owner(0), unknown2c(0)
	{
		CameraOwner* object = (CameraOwner*)newOwner;
		AssignNISRef(&owner, object == 0 ? 0 : (object->kind + 0xfffefffb > 0xfffa ? 0 : newOwner));
	}

	// FUNCTION: ENGINE 0x108F2460
	CameraAnimationAction::~CameraAnimationAction()
	{
		ReleaseNISRef(&owner);
	}

	// FUNCTION: ENGINE 0x108F2870
	fight::Action* CameraAnimationTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		return new CameraAnimationAction(this, owner);
	}

	// FUNCTION: ENGINE 0x108F28A0
	fight::Action* SwapDrawableTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x108F2A10
	TimeDilationAction::TimeDilationAction(TimeDilationTrack* newTrack)
		: fight::Action(0xE00), link(newTrack), previousScale(1.0f), elapsed(0.0f)
	{
	}

	// FUNCTION: ENGINE 0x108F2980
	TimeDilationAction::~TimeDilationAction()
	{
	}

	// FUNCTION: ENGINE 0x108F2AA0
	bool TimeDilationAction::Slot5(int arg, float value)
	{
		if (link.object == 0)
		{
			return false;
		}
		previousScale = GetSimulationDriver()->scaleA;
		GetSimulationDriver()->SetScaleA(link.object->simulationRate);
		elapsed = 0.0f;
		return true;
	}

	// FUNCTION: ENGINE 0x108F28E0
	void TimeDilationAction::Slot6()
	{
		GetSimulationDriver()->SetScaleA(previousScale);
	}

	// FUNCTION: ENGINE 0x108F28C0
	bool TimeDilationAction::Slot7(int arg, float value)
	{
		elapsed += value;
		if (elapsed > unknown14)
		{
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x108F2AE0
	fight::Action* TimeDilationTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		return new TimeDilationAction(this);
	}
}
