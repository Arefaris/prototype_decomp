// Fight items of the motion group: ReactionHitAnimationTrack (unit 0x101A9500 - 0x101A9F10; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_reactionhitanimation.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gReactionHitAnimationTrackProperties;  // 0x11254A20

			// FUNCTION: ENGINE 0x101A9500
			bool ReactionHitAnimationTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A9520
			bool ReactionHitAnimationTrack::SetTimeScale(float newValue)
			{
				timeScale = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A9540
			bool ReactionHitAnimationTrack::SetTimeEndMin(float newValue)
			{
				timeEndMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A96B0
			bool ReactionHitAnimationTrack::SetAnimation(const fight::Name& newValue)
			{
				animation = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A9560
			bool ReactionHitAnimationTrack::SetSpeed(float newValue)
			{
				speed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A9580
			bool ReactionHitAnimationTrack::SetSpeedMax(float newValue)
			{
				speedMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A95A0
			bool ReactionHitAnimationTrack::SetInitFrame(float newValue)
			{
				initFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A95C0
			bool ReactionHitAnimationTrack::SetRandomFrame(float newValue)
			{
				randomFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A95E0
			bool ReactionHitAnimationTrack::SetStartFrame(float newValue)
			{
				startFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A9600
			bool ReactionHitAnimationTrack::SetEndFrame(float newValue)
			{
				endFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A9620
			bool ReactionHitAnimationTrack::SetCyclic(int newValue)
			{
				cyclic = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A96D0
			bool ReactionHitAnimationTrack::SetPartition(const fight::Name& newValue)
			{
				partition = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A9630
			bool ReactionHitAnimationTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A9640
			bool ReactionHitAnimationTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A9660
			bool ReactionHitAnimationTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A9680
			fight::Property* ReactionHitAnimationTrack::GetProperty(int index)
			{
				return gReactionHitAnimationTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101A96A0
			void ReactionHitAnimationTrack::ClearProperties()
			{
				fight::FreePropertyList(&gReactionHitAnimationTrackProperties);
			}

			// FUNCTION: ENGINE 0x101A96F0
			ReactionHitAnimationTrack::ReactionHitAnimationTrack() : blendInTime(0.0f), blendOutTime(0.0f), endFrame(-1.0f), initFrame(0.0f), randomFrame(0.0f), speed(1.0f), speedMax(0.0f), startFrame(0.0f), timeBegin(0.0f), timeEndMin(-1.0f), timeScale(1.0f), cyclic(0), priority(0)
			{
			}

			// FUNCTION: ENGINE 0x101A9790
			float ReactionHitAnimationTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101A97A0
			float ReactionHitAnimationTrack::Slot10() const
			{
				return -1.0f;
			}

			// FUNCTION: ENGINE 0x101A97B0
			ReactionHitAnimationTrack::~ReactionHitAnimationTrack()
			{
			}

			// FUNCTION: ENGINE 0x101A9A60
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionHitAnimationTrack::RegisterProperties()
			{
				if (gReactionHitAnimationTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ReactionHitAnimationTrack>("timeBegin", &ReactionHitAnimationTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ReactionHitAnimationTrack>("timeScale", &ReactionHitAnimationTrack::SetTimeScale);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<ReactionHitAnimationTrack>("timeEndMin", &ReactionHitAnimationTrack::SetTimeEndMin);
					properties[2] = property;
					property = new fight::PropertyName<ReactionHitAnimationTrack>("animation", &ReactionHitAnimationTrack::SetAnimation);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<ReactionHitAnimationTrack>("speed", &ReactionHitAnimationTrack::SetSpeed);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<ReactionHitAnimationTrack>("speedMax", &ReactionHitAnimationTrack::SetSpeedMax);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<ReactionHitAnimationTrack>("initFrame", &ReactionHitAnimationTrack::SetInitFrame);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<ReactionHitAnimationTrack>("randomFrame", &ReactionHitAnimationTrack::SetRandomFrame);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<ReactionHitAnimationTrack>("startFrame", &ReactionHitAnimationTrack::SetStartFrame);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<ReactionHitAnimationTrack>("endFrame", &ReactionHitAnimationTrack::SetEndFrame);
					properties[9] = property;
					property = new fight::PropertyEnumConstList<ReactionHitAnimationTrack>("cyclic", gReactionHitAnimationTrackCyclicTable, 4, &ReactionHitAnimationTrack::SetCyclic);
					properties[10] = property;
					property = new fight::PropertyName<ReactionHitAnimationTrack>("partition", &ReactionHitAnimationTrack::SetPartition);
					properties[11] = property;
					property = new fight::PropertyIntConstRange<ReactionHitAnimationTrack>("priority", &ReactionHitAnimationTrack::SetPriority);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<ReactionHitAnimationTrack>("blendInTime", &ReactionHitAnimationTrack::SetBlendInTime);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<ReactionHitAnimationTrack>("blendOutTime", &ReactionHitAnimationTrack::SetBlendOutTime);
					properties[14] = property;
					fight::RegisterPropertyList(properties, &gReactionHitAnimationTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A99B0
			fight::TrackFactory* CreateReactionHitAnimationTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReactionHitAnimationTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A99E0
			void RegisterReactionHitAnimationTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReactionHitAnimationTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin

			// ---- actions end
			template class fight::PropertyFloatConstRange<ReactionHitAnimationTrack>;
			template class fight::PropertyName<ReactionHitAnimationTrack>;
			template class fight::PropertyEnumConstList<ReactionHitAnimationTrack>;
			template class fight::PropertyIntConstRange<ReactionHitAnimationTrack>;
			template class fight::TrackFactoryTemplate<ReactionHitAnimationTrack>;
			template class fight::TrackFactoryCasterTemplate<ReactionHitAnimationTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101A97C0
// FUNCTION: ENGINE 0x101A97D0
// FUNCTION: ENGINE 0x101A9800
// FUNCTION: ENGINE 0x101A9830
// FUNCTION: ENGINE 0x101A9860
// FUNCTION: ENGINE 0x101A9890
// FUNCTION: ENGINE 0x101A98A0
// FUNCTION: ENGINE 0x101A98E0
// FUNCTION: ENGINE 0x101A98F0
// FUNCTION: ENGINE 0x101A9920
// FUNCTION: ENGINE 0x101A9940
// FUNCTION: ENGINE 0x101A9950
// FUNCTION: ENGINE 0x101A9980
// FUNCTION: ENGINE 0x101A99A0
// FUNCTION: ENGINE 0x101A9A10
// FUNCTION: ENGINE 0x101A9A40
// FUNCTION: ENGINE 0x101A9E70
// FUNCTION: ENGINE 0x101A9EA0
// FUNCTION: ENGINE 0x101A9EC0
