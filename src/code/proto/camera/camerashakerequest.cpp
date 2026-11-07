// Fight items of the motion group: CameraShakeRequestTrack (unit 0x1035BFB0 - 0x1035C460; no assert path, the file name is a guess).
#include "code/proto/camera/camerashakerequest.h"

namespace proto
{
	namespace camera
	{
		fight::Property** gCameraShakeRequestTrackProperties;  // 0x11263878

		// FUNCTION: ENGINE 0x1035BFB0
		bool CameraShakeRequestTrack::SetTimeBegin(float newValue)
		{
			timeBegin = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x1035BFD0
		bool CameraShakeRequestTrack::SetSize(int newValue)
		{
			size = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x1035BFE0
		bool CameraShakeRequestTrack::SetRange(int newValue)
		{
			range = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x1035BFF0
		fight::Property* CameraShakeRequestTrack::GetProperty(int index)
		{
			return gCameraShakeRequestTrackProperties[index];
		}

		// FUNCTION: ENGINE 0x1035C010
		void CameraShakeRequestTrack::ClearProperties()
		{
			fight::FreePropertyList(&gCameraShakeRequestTrackProperties);
		}

		// FUNCTION: ENGINE 0x1035C020
		CameraShakeRequestTrack::CameraShakeRequestTrack() : timeBegin(0.0f), range(0), size(0)
		{
			unknownC = 1;
		}

		// FUNCTION: ENGINE 0x1035C060
		float CameraShakeRequestTrack::GetTimeBegin() const
		{
			return timeBegin;
		}

		// FUNCTION: ENGINE 0x1035C070
		float CameraShakeRequestTrack::Slot10() const
		{
			return 0.0f;
		}

		// FUNCTION: ENGINE 0x1035C080
		CameraShakeRequestTrack::~CameraShakeRequestTrack()
		{
		}

		// FUNCTION: ENGINE 0x1035C250
		// NONMATCHING: shrink-wrap (the engine saves esi in the entry block before the guard's branch, the compiler places the push after it)
#ifdef NONMATCHING
		void CameraShakeRequestTrack::RegisterProperties()
		{
			if (gCameraShakeRequestTrackProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyFloatConstRange<CameraShakeRequestTrack>("timeBegin", &CameraShakeRequestTrack::SetTimeBegin);
				properties[0] = property;
				property = new fight::PropertyEnumConstList<CameraShakeRequestTrack>("size", gCameraShakeRequestTrackSizeTable, gCameraShakeRequestTrackSizeCount, &CameraShakeRequestTrack::SetSize);
				properties[1] = property;
				property = new fight::PropertyEnumConstList<CameraShakeRequestTrack>("range", gCameraShakeRequestTrackSizeTable, gCameraShakeRequestTrackSizeCount, &CameraShakeRequestTrack::SetRange);
				properties[2] = property;
				fight::RegisterPropertyList(properties, &gCameraShakeRequestTrackProperties);
			}
		}
#endif

		// FUNCTION: ENGINE 0x1035C220
		fight::TrackFactory* CreateCameraShakeRequestTrackFactory(const char* name)
		{
			fight::TrackFactoryCasterTemplate<CameraShakeRequestTrack> caster;
			return fight::FindTrackFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x1035C390
		void RegisterCameraShakeRequestTrackFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::TrackFactoryCasterTemplate<CameraShakeRequestTrack> caster;
			registry->AddFactory(fight::FindTrackFactory(name, &caster));
		}

			// FUNCTION: ENGINE 0x103591A0
			int CameraShakeRequestTrack::GetSize() const
			{
				return size;
			}

			// FUNCTION: ENGINE 0x103591B0
			int CameraShakeRequestTrack::GetRange() const
			{
				return range;
			}

		// ---- actions begin
		// FUNCTION: ENGINE 0x10359320
		CameraShakeRequestAction::CameraShakeRequestAction(CameraShakeRequestTrack* newTrack, const math::Vector& newPosition) : fight::Action(0x200), link(newTrack)
		{
			position.x = newPosition.x;
			position.y = newPosition.y;
			position.z = newPosition.z;
		}

		// FUNCTION: ENGINE 0x10359290
		CameraShakeRequestAction::~CameraShakeRequestAction()
		{
		}

		// FUNCTION: ENGINE 0x10359410
		// NONMATCHING: the engine reads the translation into three registers before storing it and writes the position of the second owner kind before the allocation (best 46.4 %)
#ifdef NONMATCHING
		fight::Action* CameraShakeRequestTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
		{
			if (owner == 0)
			{
				return 0;
			}
			fightitems::motion::TrackOwner* trackOwner = (fightitems::motion::TrackOwner*)owner;
			math::Vector position;
			if (trackOwner->kind - 0x10000 <= 0x1ffff)
			{
				engine::GameObjectHandle handle = trackOwner->handle;
				engine::GameObject* object = handle.Get();
				if (object == 0)
				{
					return 0;
				}
				math::Matrix* matrix = object->transform->GetPointer();
				position.Set(matrix->m[3][0], matrix->m[3][1], matrix->m[3][2]);
			}
			else if (trackOwner->kind == 0x40000)
			{
				ShakeOwnerPoint* point = (ShakeOwnerPoint*)owner;
				position.x = point->position.x;
				position.y = point->position.y;
				position.z = point->position.z;
			}
			else
			{
				return 0;
			}
			return new CameraShakeRequestAction(this, position);
		}
#endif

		// FUNCTION: ENGINE 0x103593D0
		bool CameraShakeRequestAction::Slot5(int arg, float value)
		{
			CameraShakeRequestTrack* track = link.object;
			CameraManager::ShakeArgument size = (CameraManager::ShakeArgument)track->size;
			CameraManager::ShakeArgument range = (CameraManager::ShakeArgument)track->range;
			gCameraManager->RequestShake(position, size, range);
			return true;
		}
		// ---- actions end

		template class fight::PropertyFloatConstRange<CameraShakeRequestTrack>;
		template class fight::PropertyEnumConstList<CameraShakeRequestTrack>;
		template class fight::TrackFactoryTemplate<CameraShakeRequestTrack>;
		template class fight::TrackFactoryCasterTemplate<CameraShakeRequestTrack>;
	}
}


namespace proto
{
	namespace fightitems
	{
		// FUNCTION: ENGINE 0x103591C0
		bool RegisterAt103591C0Factories(fight::TrackRegistry* registry)
		{
			camera::RegisterCameraShakeRequestTrackFactory(registry, "cameraShakeRequest");
			return true;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1035C090
// FUNCTION: ENGINE 0x1035C0C0
// FUNCTION: ENGINE 0x1035C0D0
// FUNCTION: ENGINE 0x1035C100
// FUNCTION: ENGINE 0x1035C130
// FUNCTION: ENGINE 0x1035C160
// FUNCTION: ENGINE 0x1035C170
// FUNCTION: ENGINE 0x1035C1B0
// FUNCTION: ENGINE 0x1035C1C0
// FUNCTION: ENGINE 0x1035C1F0
// FUNCTION: ENGINE 0x1035C210
// FUNCTION: ENGINE 0x1035C3C0
// FUNCTION: ENGINE 0x1035C3F0
// FUNCTION: ENGINE 0x1035C410