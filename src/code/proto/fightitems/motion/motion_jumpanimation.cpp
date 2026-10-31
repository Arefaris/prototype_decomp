// Fight items of the motion group: JumpAnimationTrack (unit 0x10184DF0 - 0x10185900; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_jumpanimation.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gJumpAnimationTrackProperties;  // 0x1125479C

			// FUNCTION: ENGINE 0x10184DF0
			bool JumpAnimationTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10184E10
			bool JumpAnimationTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10184FE0
			bool JumpAnimationTrack::SetAnimation(const fight::Name& newValue)
			{
				animation = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10184E30
			bool JumpAnimationTrack::SetGravity(float newValue)
			{
				gravity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10184E50
			bool JumpAnimationTrack::SetPeakVerticalVelocity(float newValue)
			{
				peakVerticalVelocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10184E70
			bool JumpAnimationTrack::SetStartFrameClimb(float newValue)
			{
				startFrameClimb = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10184E90
			bool JumpAnimationTrack::SetEndFrameClimb(float newValue)
			{
				endFrameClimb = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10184EB0
			bool JumpAnimationTrack::SetStartFramePeak(float newValue)
			{
				startFramePeak = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10184ED0
			bool JumpAnimationTrack::SetEndFramePeak(float newValue)
			{
				endFramePeak = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10184EF0
			bool JumpAnimationTrack::SetStartFrameFall(float newValue)
			{
				startFrameFall = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10184F10
			bool JumpAnimationTrack::SetEndFrameFall(float newValue)
			{
				endFrameFall = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10184F30
			bool JumpAnimationTrack::SetSpew(bool newValue)
			{
				spew = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10184F40
			bool JumpAnimationTrack::SetHasRootTranslation(bool newValue)
			{
				hasRootTranslation = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10184F50
			bool JumpAnimationTrack::SetHasRootRotation(bool newValue)
			{
				hasRootRotation = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10185000
			bool JumpAnimationTrack::SetPartition(const fight::Name& newValue)
			{
				partition = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10184F60
			bool JumpAnimationTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10184F70
			bool JumpAnimationTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10184F90
			bool JumpAnimationTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10184FB0
			fight::Property* JumpAnimationTrack::GetProperty(int index)
			{
				return gJumpAnimationTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10184FD0
			void JumpAnimationTrack::ClearProperties()
			{
				fight::FreePropertyList(&gJumpAnimationTrackProperties);
			}

			// FUNCTION: ENGINE 0x10185020
			JumpAnimationTrack::JumpAnimationTrack() : blendInTime(0.0f), blendOutTime(0.0f), endFrameClimb(-1.0f), endFrameFall(-1.0f), endFramePeak(-1.0f), gravity(9.8f), peakVerticalVelocity(3.0f), startFrameClimb(0.0f), startFrameFall(0.0f), startFramePeak(0.0f), timeBegin(0.0f), timeEnd(-1.0f), priority(0), hasRootRotation(false), hasRootTranslation(false), spew(false)
			{
			}

			// FUNCTION: ENGINE 0x101850D0
			float JumpAnimationTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101850E0
			float JumpAnimationTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101850F0
			JumpAnimationTrack::~JumpAnimationTrack()
			{
			}

			// FUNCTION: ENGINE 0x101853B0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void JumpAnimationTrack::RegisterProperties()
			{
				if (gJumpAnimationTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<JumpAnimationTrack>("timeBegin", &JumpAnimationTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<JumpAnimationTrack>("timeEnd", &JumpAnimationTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyName<JumpAnimationTrack>("animation", &JumpAnimationTrack::SetAnimation);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<JumpAnimationTrack>("gravity", &JumpAnimationTrack::SetGravity);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<JumpAnimationTrack>("peakVerticalVelocity", &JumpAnimationTrack::SetPeakVerticalVelocity);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<JumpAnimationTrack>("startFrameClimb", &JumpAnimationTrack::SetStartFrameClimb);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<JumpAnimationTrack>("endFrameClimb", &JumpAnimationTrack::SetEndFrameClimb);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<JumpAnimationTrack>("startFramePeak", &JumpAnimationTrack::SetStartFramePeak);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<JumpAnimationTrack>("endFramePeak", &JumpAnimationTrack::SetEndFramePeak);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<JumpAnimationTrack>("startFrameFall", &JumpAnimationTrack::SetStartFrameFall);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<JumpAnimationTrack>("endFrameFall", &JumpAnimationTrack::SetEndFrameFall);
					properties[10] = property;
					property = new fight::PropertyBool<JumpAnimationTrack>("spew", &JumpAnimationTrack::SetSpew);
					properties[11] = property;
					property = new fight::PropertyBool<JumpAnimationTrack>("hasRootTranslation", &JumpAnimationTrack::SetHasRootTranslation);
					properties[12] = property;
					property = new fight::PropertyBool<JumpAnimationTrack>("hasRootRotation", &JumpAnimationTrack::SetHasRootRotation);
					properties[13] = property;
					property = new fight::PropertyNameList<JumpAnimationTrack>("partition", &JumpAnimationTrack::SetPartition);
					properties[14] = property;
					property = new fight::PropertyIntConstRange<JumpAnimationTrack>("priority", &JumpAnimationTrack::SetPriority);
					properties[15] = property;
					property = new fight::PropertyFloatConstRange<JumpAnimationTrack>("blendInTime", &JumpAnimationTrack::SetBlendInTime);
					properties[16] = property;
					property = new fight::PropertyFloatConstRange<JumpAnimationTrack>("blendOutTime", &JumpAnimationTrack::SetBlendOutTime);
					properties[17] = property;
					fight::RegisterPropertyList(properties, &gJumpAnimationTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101852A0
			fight::TrackFactory* CreateJumpAnimationTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<JumpAnimationTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101852D0
			void RegisterJumpAnimationTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<JumpAnimationTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<JumpAnimationTrack>;
			template class fight::PropertyName<JumpAnimationTrack>;
			template class fight::PropertyBool<JumpAnimationTrack>;
			template class fight::PropertyNameList<JumpAnimationTrack>;
			template class fight::PropertyIntConstRange<JumpAnimationTrack>;
			template class fight::TrackFactoryTemplate<JumpAnimationTrack>;
			template class fight::TrackFactoryCasterTemplate<JumpAnimationTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10185100
// FUNCTION: ENGINE 0x10185110
// FUNCTION: ENGINE 0x10185140
// FUNCTION: ENGINE 0x10185170
// FUNCTION: ENGINE 0x101851A0
// FUNCTION: ENGINE 0x101851D0
// FUNCTION: ENGINE 0x101851E0
// FUNCTION: ENGINE 0x10185210
// FUNCTION: ENGINE 0x10185230
// FUNCTION: ENGINE 0x10185240
// FUNCTION: ENGINE 0x10185270
// FUNCTION: ENGINE 0x10185290
// FUNCTION: ENGINE 0x10185300
// FUNCTION: ENGINE 0x10185330
// FUNCTION: ENGINE 0x10185350
// FUNCTION: ENGINE 0x10185380
// FUNCTION: ENGINE 0x101853A0
// FUNCTION: ENGINE 0x10185860
// FUNCTION: ENGINE 0x10185890
// FUNCTION: ENGINE 0x101858B0
