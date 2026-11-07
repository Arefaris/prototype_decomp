// Fight items of the motion group: CameraHintTrack (unit 0x1035B690 - 0x1035BB50; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_camerahint.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gCameraHintTrackProperties;  // 0x11263870

			// FUNCTION: ENGINE 0x1035B690
			bool CameraHintTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035B6B0
			bool CameraHintTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035B6D0
			bool CameraHintTrack::SetHint(int newValue)
			{
				hint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035B6E0
			fight::Property* CameraHintTrack::GetProperty(int index)
			{
				return gCameraHintTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1035B700
			void CameraHintTrack::ClearProperties()
			{
				fight::FreePropertyList(&gCameraHintTrackProperties);
			}

			// FUNCTION: ENGINE 0x1035B710
			CameraHintTrack::CameraHintTrack() : timeBegin(0.0f), timeEnd(-1.0f), hint(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1035B760
			float CameraHintTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1035B770
			float CameraHintTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1035B780
			CameraHintTrack::~CameraHintTrack()
			{
			}

			// FUNCTION: ENGINE 0x1035B950
			// NONMATCHING: shrink-wrap (the engine saves esi in the entry block before the guard's branch, the compiler places the push after it)
#ifdef NONMATCHING
			void CameraHintTrack::RegisterProperties()
			{
				if (gCameraHintTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<CameraHintTrack>("timeBegin", &CameraHintTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<CameraHintTrack>("timeEnd", &CameraHintTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyEnumConstList<CameraHintTrack>("hint", gCameraHintTrackHintTable, gCameraHintTrackHintCount, &CameraHintTrack::SetHint);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gCameraHintTrackProperties);
				}
			}
#endif

			// FUNCTION: ENGINE 0x1035B920
			fight::TrackFactory* CreateCameraHintTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<CameraHintTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1035BA80
			void RegisterCameraHintTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<CameraHintTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// FUNCTION: ENGINE 0x10358BE0
			int CameraHintTrack::GetHint() const
			{
				return hint;
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x10358D40
			CameraHintAction::CameraHintAction(CameraHintTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0x800), target(newTarget), link(newTrack)
			{
			}

			// FUNCTION: ENGINE 0x10358CA0
			CameraHintAction::~CameraHintAction()
			{
			}

			// FUNCTION: ENGINE 0x10358E10
			fight::Action* CameraHintTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new CameraHintAction(this, handle);
			}

			// FUNCTION: ENGINE 0x10358DE0
			bool CameraHintAction::Slot7(int arg, float value)
			{
				if (arg == 0 && link.object != 0)
				{
					gCameraManager->SendCameraHint(target, link.object->hint);
				}
				return true;
			}

			// ---- actions end

			template class fight::PropertyFloatConstRange<CameraHintTrack>;
			template class fight::PropertyEnumConstList<CameraHintTrack>;
			template class fight::TrackFactoryTemplate<CameraHintTrack>;
			template class fight::TrackFactoryCasterTemplate<CameraHintTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1035B790
// FUNCTION: ENGINE 0x1035B7C0
// FUNCTION: ENGINE 0x1035B7D0
// FUNCTION: ENGINE 0x1035B800
// FUNCTION: ENGINE 0x1035B830
// FUNCTION: ENGINE 0x1035B860
// FUNCTION: ENGINE 0x1035B870
// FUNCTION: ENGINE 0x1035B8B0
// FUNCTION: ENGINE 0x1035B8C0
// FUNCTION: ENGINE 0x1035B8F0
// FUNCTION: ENGINE 0x1035B910
// FUNCTION: ENGINE 0x1035BAB0
// FUNCTION: ENGINE 0x1035BAE0
// FUNCTION: ENGINE 0x1035BB00
