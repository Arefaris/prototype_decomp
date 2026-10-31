// The actions of the camera clipping plane, camera animation and time dilation tracks (unit 0x108F20C0 - 0x108F2B00,
// no assert path; file name guessed). The tracks are in cameratracks.cpp.
#include "code/engine/fight/cameraactions.h"
#include "code/engine/camera/animatedcamera.h"
#include "code/engine/camera/cinematographer.h"
#include "code/engine/camera/director.h"
#include "code/engine/system/simulationdriver.h"
#include "code/pure3d/animation.h"

namespace engine
{
	// What the owner is seen as: an IRefCount-derived object whose kind says whether it is a game object
	struct CameraOwner : core::IRefCount
	{
		int unknown4;
		unsigned int kind;  // +0x8
		GameObjectHandle handle;  // +0xC
		int unknown10;
		int unknown14;
		content::LoadInventory* inventory;  // +0x18
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

	// FUNCTION: ENGINE 0x108F2220
	// EQUIVALENT: block layout (the engine's failure return of the camera search sits behind the success path, ours right after the search's test); every other instruction is the engine's
	bool CameraClipPlaneAction::Slot5(int arg, float value)
	{
		if (link.object == 0)
		{
			return false;
		}
		camera::Director* director = camera::Director::Get();
		int index = director->playerCamera[0];
		if (index < 0 && !director->NextActiveCamera(&index, 0))
		{
			return false;
		}
		camera::AnimatedCamera* animated = director->GetCamera(index, 0)->animated;
		camera = animated;
		nearPlane = animated->camera->minZ;
		farPlane = animated->camera->maxZ;
		unknown30 = animated->unknown9F;
		animated->unknown9F = false;
		animated->camera->SetNearPlane(link.object->nearPlane);
		animated->camera->SetFarPlane(link.object->farPlane);
		return true;
	}

	// FUNCTION: ENGINE 0x108F22C0
	void CameraClipPlaneAction::Slot6()
	{
		if (link.object != 0 && link.object->restoreAtEnd)
		{
			camera->unknown9F = unknown30;
			camera->camera->SetFarPlane(farPlane);
			camera->camera->SetNearPlane(nearPlane);
			camera = 0;
		}
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
		: fight::Action(0xE00), link(newTrack), owner(0), playback(0)
	{
		CameraOwner* object = (CameraOwner*)newOwner;
		AssignNISRef(&owner, object == 0 ? 0 : (object->kind + 0xfffefffb > 0xfffa ? 0 : newOwner));
	}

	// FUNCTION: ENGINE 0x108F2460
	CameraAnimationAction::~CameraAnimationAction()
	{
		ReleaseNISRef(&owner);
	}

	// FUNCTION: ENGINE 0x108F23A0
	void AssignCameraController(pure3d::CameraAnimationController** slot, pure3d::CameraAnimationController* value)
	{
		if (value != 0)
		{
			value->AddRef();
		}
		if (*slot != 0)
		{
			(*slot)->Release();
		}
		*slot = value;
	}

	// FUNCTION: ENGINE 0x108F23D0
	void ReleaseCameraController(pure3d::CameraAnimationController** slot)
	{
		if (*slot != 0)
		{
			(*slot)->Release();
			*slot = 0;
		}
	}

	// FUNCTION: ENGINE 0x108F25A0
	// NONMATCHING: the engine copies the whole simulation time into a local (two dead stores) where ours reads the seconds in place, and the failure return of the camera search is a second epilogue; 62 %
#ifdef NONMATCHING
	bool CameraAnimationAction::Slot5(int arg, float value)
	{
		CameraAnimationTrack* track = link.object;
		if (track == 0)
		{
			return false;
		}
		CameraOwner* object = (CameraOwner*)owner;
		content::LoadInventory* inventory = object->inventory;
		if (inventory == 0)
		{
			return false;
		}
		GameObjectHandle ownerHandle = object->handle;
		GameObject* ownerObject = ownerHandle.Get();
		if (ownerObject == 0)
		{
			return false;
		}
		pure3d::Animation* animation = inventory->Find<pure3d::Animation>(track->animation);
		if (animation == 0)
		{
			animation = content::gRootInventory->Find<pure3d::Animation>(track->animation);
			if (animation == 0)
			{
				return false;
			}
		}
		float init = link.object->initFrame;
		if (init < 0.0f)
		{
			float sum = animation->numFrames + init;
			if (sum < 0.0f)
			{
				init = 0.0f;
			}
			else
			{
				init = sum;
			}
		}
		float start = link.object->startFrame;
		if (start < 0.0f)
		{
			float sum = animation->numFrames + start;
			if (sum < 0.0f)
			{
				start = 0.0f;
			}
			else
			{
				start = sum;
			}
		}
		float end = link.object->endFrame;
		if (end < 0.0f)
		{
			float sum = animation->numFrames + end;
			if (sum < 0.0f)
			{
				end = 0.0f;
			}
			else
			{
				end = sum;
			}
		}
		core::Time now = GetSimulationDriver()->time3;
		const core::Time* nowPointer = &now;
		value = (value - nowPointer->seconds) * animation->mFrameRate + init;
		if (value > end)
		{
			return false;
		}
		camera::Director* director = camera::Director::Get();
		int index = director->playerCamera[0];
		if (index < 0 && !director->NextActiveCamera(&index, 0))
		{
			return false;
		}
		camera::AnimatedCamera* animated = director->GetCamera(index, 0)->animated;
		pure3d::CameraAnimationController* controller = animated->Play(animation, value, start, end, link.object->cyclic);
		controller->unknown119 = false;
		AssignCameraController(&playback, controller);
		animated->SetTransform(ownerObject->transform->value);
		return true;
	}
#endif

	// FUNCTION: ENGINE 0x108F2790
	// EQUIVALENT: scheduling (the engine loads the track pointer and calls the animation getter before it forms the name's address, ours forms the address first); every other instruction is the engine's
	bool CameraAnimationAction::Slot7(int arg, float value)
	{
		if (link.object == 0)
		{
			return false;
		}
		if (playback != 0)
		{
			if (playback->Unknown20())
			{
				return false;
			}
			if (playback->GetAnimation()->mName != link.object->animation)
			{
				return false;
			}
		}
		return true;
	}

	// FUNCTION: ENGINE 0x108F27E0
	// EQUIVALENT: scheduling (the engine loads the track pointer and calls the animation getter before it forms the name's address, ours forms the address first); every other instruction is the engine's
	void CameraAnimationAction::Slot6()
	{
		if (link.object != 0 && playback != 0)
		{
			if (playback->Unknown20() || playback->GetAnimation()->mName == link.object->animation)
			{
				camera::Director* director = camera::Director::Get();
				int index = director->playerCamera[0];
				if (index >= 0 || director->NextActiveCamera(&index, 0))
				{
					camera::Cinematographer* view = director->GetCamera(index, 0);
					if (view != 0)
					{
						view->animated->Reset();
					}
				}
			}
			ReleaseCameraController(&playback);
		}
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

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108F2200
// FUNCTION: ENGINE 0x108F2580
// FUNCTION: ENGINE 0x108F2A80
// FUNCTION: ENGINE 0x108F2050
// FUNCTION: ENGINE 0x108F2070
// FUNCTION: ENGINE 0x108F23F0
// FUNCTION: ENGINE 0x108F2410
// FUNCTION: ENGINE 0x108F2910
// FUNCTION: ENGINE 0x108F2930
