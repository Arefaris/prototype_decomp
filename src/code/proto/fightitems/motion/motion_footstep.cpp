// Fight items of the motion group: FootstepTrack, JawFlapTrack (unit 0x101B3FC0 - 0x101B4CC0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_footstep.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gFootstepTrackProperties;  // 0x11254AE0

			// FUNCTION: ENGINE 0x101B3FC0
			bool FootstepTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B3FE0
			bool FootstepTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B4000
			bool FootstepTrack::SetPhase(float newValue)
			{
				phase = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B41B0
			bool FootstepTrack::SetFootstepMapName(const fight::Name& newValue)
			{
				footstepMapName = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B4150
			fight::Property* FootstepTrack::GetProperty(int index)
			{
				return gFootstepTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101B4170
			void FootstepTrack::ClearProperties()
			{
				fight::FreePropertyList(&gFootstepTrackProperties);
			}

			// FUNCTION: ENGINE 0x101B41F0
			FootstepTrack::FootstepTrack() : phase(0.0f), timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101B4240
			float FootstepTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101B4250
			float FootstepTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101B4260
			FootstepTrack::~FootstepTrack()
			{
			}

			// FUNCTION: ENGINE 0x101B4730
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FootstepTrack::RegisterProperties()
			{
				if (gFootstepTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<FootstepTrack>("timeBegin", &FootstepTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<FootstepTrack>("timeEnd", &FootstepTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<FootstepTrack>("phase", &FootstepTrack::SetPhase);
					properties[2] = property;
					property = new fight::PropertyName<FootstepTrack>("footstepMapName", &FootstepTrack::SetFootstepMapName);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gFootstepTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101B45C0
			fight::TrackFactory* CreateFootstepTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<FootstepTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101B4620
			void RegisterFootstepTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<FootstepTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gJawFlapTrackProperties;  // 0x11254AE4

			// FUNCTION: ENGINE 0x101B4020
			bool JawFlapTrack::SetAngleMin(float newValue)
			{
				angleMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101B4040
			bool JawFlapTrack::SetAngleMax(float newValue)
			{
				angleMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101B4060
			bool JawFlapTrack::SetThresholdMin(float newValue)
			{
				thresholdMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B4080
			bool JawFlapTrack::SetThresholdMax(float newValue)
			{
				thresholdMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B41D0
			bool JawFlapTrack::SetJoint(const fight::Name& newValue)
			{
				joint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B40A0
			bool JawFlapTrack::SetAxis(const math::Vector& newValue)
			{
				axis.x = newValue.x;
				axis.y = newValue.y;
				axis.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101B40C0
			bool JawFlapTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B40D0
			bool JawFlapTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B40F0
			bool JawFlapTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B4110
			bool JawFlapTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B4130
			bool JawFlapTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B4180
			fight::Property* JawFlapTrack::GetProperty(int index)
			{
				return gJawFlapTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101B41A0
			void JawFlapTrack::ClearProperties()
			{
				fight::FreePropertyList(&gJawFlapTrackProperties);
			}

			// FUNCTION: ENGINE 0x101B4270
			JawFlapTrack::JawFlapTrack() : axis(0.0f, 0.0f, -1.0f), angleMax(0.2617994f), angleMin(0.0f), blendInTime(0.1f), blendOutTime(0.1f), thresholdMax(0.1f), thresholdMin(0.0f), timeBegin(0.0f), timeEnd(0.0f), priority(-10)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101B4310
			float JawFlapTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101B4320
			float JawFlapTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101B4330
			JawFlapTrack::~JawFlapTrack()
			{
			}

			// FUNCTION: ENGINE 0x101B4880
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void JawFlapTrack::RegisterProperties()
			{
				if (gJawFlapTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<JawFlapTrack>("angleMin", &JawFlapTrack::SetAngleMin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<JawFlapTrack>("angleMax", &JawFlapTrack::SetAngleMax);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<JawFlapTrack>("thresholdMin", &JawFlapTrack::SetThresholdMin);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<JawFlapTrack>("thresholdMax", &JawFlapTrack::SetThresholdMax);
					properties[3] = property;
					property = new fight::PropertyNameList<JawFlapTrack>("joint", &JawFlapTrack::SetJoint);
					properties[4] = property;
					property = new fight::PropertyVector<JawFlapTrack>("axis", &JawFlapTrack::SetAxis);
					properties[5] = property;
					property = new fight::PropertyIntConstRange<JawFlapTrack>("priority", &JawFlapTrack::SetPriority);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<JawFlapTrack>("blendInTime", &JawFlapTrack::SetBlendInTime);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<JawFlapTrack>("blendOutTime", &JawFlapTrack::SetBlendOutTime);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<JawFlapTrack>("timeBegin", &JawFlapTrack::SetTimeBegin);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<JawFlapTrack>("timeEnd", &JawFlapTrack::SetTimeEnd);
					properties[10] = property;
					fight::RegisterPropertyList(properties, &gJawFlapTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101B45F0
			fight::TrackFactory* CreateJawFlapTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<JawFlapTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101B4650
			void RegisterJawFlapTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<JawFlapTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<FootstepTrack>;
			template class fight::PropertyName<FootstepTrack>;
			template class fight::TrackFactoryTemplate<FootstepTrack>;
			template class fight::TrackFactoryCasterTemplate<FootstepTrack>;
			template class fight::PropertyFloatConstRange<JawFlapTrack>;
			template class fight::PropertyNameList<JawFlapTrack>;
			template class fight::PropertyVector<JawFlapTrack>;
			template class fight::PropertyIntConstRange<JawFlapTrack>;
			template class fight::TrackFactoryTemplate<JawFlapTrack>;
			template class fight::TrackFactoryCasterTemplate<JawFlapTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101B4340
// FUNCTION: ENGINE 0x101B4350
// FUNCTION: ENGINE 0x101B4380
// FUNCTION: ENGINE 0x101B4390
// FUNCTION: ENGINE 0x101B43C0
// FUNCTION: ENGINE 0x101B43F0
// FUNCTION: ENGINE 0x101B4420
// FUNCTION: ENGINE 0x101B4450
// FUNCTION: ENGINE 0x101B4480
// FUNCTION: ENGINE 0x101B4490
// FUNCTION: ENGINE 0x101B44C0
// FUNCTION: ENGINE 0x101B44F0
// FUNCTION: ENGINE 0x101B4500
// FUNCTION: ENGINE 0x101B4530
// FUNCTION: ENGINE 0x101B4550
// FUNCTION: ENGINE 0x101B4560
// FUNCTION: ENGINE 0x101B4590
// FUNCTION: ENGINE 0x101B45B0
// FUNCTION: ENGINE 0x101B4680
// FUNCTION: ENGINE 0x101B46B0
// FUNCTION: ENGINE 0x101B46D0
// FUNCTION: ENGINE 0x101B4700
// FUNCTION: ENGINE 0x101B4720
// FUNCTION: ENGINE 0x101B4B80
// FUNCTION: ENGINE 0x101B4BB0
// FUNCTION: ENGINE 0x101B4BD0
// FUNCTION: ENGINE 0x101B4C00
// FUNCTION: ENGINE 0x101B4C20
// FUNCTION: ENGINE 0x101B4C70
