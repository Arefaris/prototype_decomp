// Fight items of the motion group: CameraResetTrack (unit 0x1035BB50 - 0x1035BFB0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_camerareset.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gCameraResetTrackProperties;  // 0x11263874

			// FUNCTION: ENGINE 0x1035BB50
			bool CameraResetTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035BB70
			bool CameraResetTrack::SetDirection(const math::Vector& newValue)
			{
				direction.x = newValue.x;
				direction.y = newValue.y;
				direction.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1035BB90
			bool CameraResetTrack::SetBlendTime(float newValue)
			{
				blendTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035BBB0
			fight::Property* CameraResetTrack::GetProperty(int index)
			{
				return gCameraResetTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1035BBD0
			void CameraResetTrack::ClearProperties()
			{
				fight::FreePropertyList(&gCameraResetTrackProperties);
			}

			// FUNCTION: ENGINE 0x1035BBE0
			CameraResetTrack::CameraResetTrack() : direction(0.0f, 0.0f, -1.0f), blendTime(0.0f), timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1035BC30
			float CameraResetTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1035BC40
			float CameraResetTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1035BC50
			CameraResetTrack::~CameraResetTrack()
			{
			}

			// FUNCTION: ENGINE 0x1035BDD0
			// NONMATCHING: shrink-wrap (the engine saves esi in the entry block before the guard's branch, the compiler places the push after it)
#ifdef NONMATCHING
			void CameraResetTrack::RegisterProperties()
			{
				if (gCameraResetTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<CameraResetTrack>("timeBegin", &CameraResetTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyVector<CameraResetTrack>("direction", &CameraResetTrack::SetDirection);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<CameraResetTrack>("blendTime", &CameraResetTrack::SetBlendTime);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gCameraResetTrackProperties);
				}
			}
#endif

			// FUNCTION: ENGINE 0x1035BDA0
			fight::TrackFactory* CreateCameraResetTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<CameraResetTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1035BEE0
			void RegisterCameraResetTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<CameraResetTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// FUNCTION: ENGINE 0x10358E80
			float CameraResetTrack::GetBlendTime() const
			{
				return blendTime;
			}

			// FUNCTION: ENGINE 0x10358E60
			math::Vector CameraResetTrack::GetDirection() const
			{
				return direction;
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x10358FE0
			CameraResetAction::CameraResetAction(CameraResetTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0x200), target(newTarget), link(newTrack)
			{
			}

			// FUNCTION: ENGINE 0x10358F40
			CameraResetAction::~CameraResetAction()
			{
			}

			// FUNCTION: ENGINE 0x10359150
			fight::Action* CameraResetTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new CameraResetAction(this, handle);
			}

			// FUNCTION: ENGINE 0x10359080
			bool CameraResetAction::Slot5(int arg, float value)
			{
				if (link.object != 0)
				{
					engine::GameObject* object = target.Get();
					if (object != 0)
					{
						math::Vector direction = link.object->direction;
						math::Vector rotated;
						object->transform->GetPointer()->Rotate(direction, rotated);
						ChaseCamera* camera = gCameraManager->GetChaseCamera();
						if (camera != 0)
						{
							camera->ResetFacing3D(&rotated, link.object->blendTime);
						}
					}
				}
				return false;
			}
			// ---- actions end

			template class fight::PropertyFloatConstRange<CameraResetTrack>;
			template class fight::PropertyVector<CameraResetTrack>;
			template class fight::TrackFactoryTemplate<CameraResetTrack>;
			template class fight::TrackFactoryCasterTemplate<CameraResetTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1035BC60
// FUNCTION: ENGINE 0x1035BC90
// FUNCTION: ENGINE 0x1035BCA0
// FUNCTION: ENGINE 0x1035BCD0
// FUNCTION: ENGINE 0x1035BD00
// FUNCTION: ENGINE 0x1035BD30
// FUNCTION: ENGINE 0x1035BD40
// FUNCTION: ENGINE 0x1035BD70
// FUNCTION: ENGINE 0x1035BD90
// FUNCTION: ENGINE 0x1035BF10
// FUNCTION: ENGINE 0x1035BF40
// FUNCTION: ENGINE 0x1035BF60
