// Fight items of the motion group: PunchinCameraTrack (unit 0x1035DC50 - 0x1035E310; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_punchincamera.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gPunchinCameraTrackProperties;  // 0x11263884

			// FUNCTION: ENGINE 0x1035DC50
			bool PunchinCameraTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035DC70
			bool PunchinCameraTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035DC90
			bool PunchinCameraTrack::SetInTime(float newValue)
			{
				inTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035DCB0
			bool PunchinCameraTrack::SetOutTime(float newValue)
			{
				outTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035DCD0
			bool PunchinCameraTrack::SetDolly(float newValue)
			{
				dolly = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035DCF0
			bool PunchinCameraTrack::SetZoom(float newValue)
			{
				zoom = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035DD10
			bool PunchinCameraTrack::SetReAim(bool newValue)
			{
				reAim = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035DD20
			bool PunchinCameraTrack::SetAimPoint(const math::Vector& newValue)
			{
				aimPoint.x = newValue.x;
				aimPoint.y = newValue.y;
				aimPoint.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1035DD40
			fight::Property* PunchinCameraTrack::GetProperty(int index)
			{
				return gPunchinCameraTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1035DD60
			void PunchinCameraTrack::ClearProperties()
			{
				fight::FreePropertyList(&gPunchinCameraTrackProperties);
			}

			// FUNCTION: ENGINE 0x1035DD70
			PunchinCameraTrack::PunchinCameraTrack() : aimPoint(0.0f, 0.6f, 0.0f), dolly(1.0f), inTime(0.0f), outTime(0.0f), timeBegin(0.0f), timeEnd(-1.0f), zoom(1.0f), reAim(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1035DDF0
			float PunchinCameraTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1035DE00
			float PunchinCameraTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1035DE10
			PunchinCameraTrack::~PunchinCameraTrack()
			{
			}

			// FUNCTION: ENGINE 0x1035DFF0
			// NONMATCHING: shrink-wrap (the engine saves esi in the entry block before the guard's branch, the compiler places the push after it)
#ifdef NONMATCHING
			void PunchinCameraTrack::RegisterProperties()
			{
				if (gPunchinCameraTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<PunchinCameraTrack>("timeBegin", &PunchinCameraTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<PunchinCameraTrack>("timeEnd", &PunchinCameraTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<PunchinCameraTrack>("inTime", &PunchinCameraTrack::SetInTime);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<PunchinCameraTrack>("outTime", &PunchinCameraTrack::SetOutTime);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<PunchinCameraTrack>("dolly", &PunchinCameraTrack::SetDolly);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<PunchinCameraTrack>("zoom", &PunchinCameraTrack::SetZoom);
					properties[5] = property;
					property = new fight::PropertyBool<PunchinCameraTrack>("reAim", &PunchinCameraTrack::SetReAim);
					properties[6] = property;
					property = new fight::PropertyVector<PunchinCameraTrack>("aimPoint", &PunchinCameraTrack::SetAimPoint);
					properties[7] = property;
					fight::RegisterPropertyList(properties, &gPunchinCameraTrackProperties);
				}
			}
#endif

			// FUNCTION: ENGINE 0x1035DFC0
			fight::TrackFactory* CreatePunchinCameraTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<PunchinCameraTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1035E240
			void RegisterPunchinCameraTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<PunchinCameraTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<PunchinCameraTrack>;
			template class fight::PropertyBool<PunchinCameraTrack>;
			template class fight::PropertyVector<PunchinCameraTrack>;
			template class fight::TrackFactoryTemplate<PunchinCameraTrack>;
			template class fight::TrackFactoryCasterTemplate<PunchinCameraTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1035DE20
// FUNCTION: ENGINE 0x1035DE50
// FUNCTION: ENGINE 0x1035DE60
// FUNCTION: ENGINE 0x1035DE90
// FUNCTION: ENGINE 0x1035DEC0
// FUNCTION: ENGINE 0x1035DEF0
// FUNCTION: ENGINE 0x1035DF00
// FUNCTION: ENGINE 0x1035DF30
// FUNCTION: ENGINE 0x1035DF50
// FUNCTION: ENGINE 0x1035DF60
// FUNCTION: ENGINE 0x1035DF90
// FUNCTION: ENGINE 0x1035DFB0
// FUNCTION: ENGINE 0x1035E270
// FUNCTION: ENGINE 0x1035E2A0
// FUNCTION: ENGINE 0x1035E2C0
