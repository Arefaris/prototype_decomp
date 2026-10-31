// Fight items of the motion group: ReactionPushbackOrientTrack, ReactionPushbackTrack (unit 0x101A73A0 - 0x101A8000; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_reactionpushback.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gReactionPushbackOrientTrackProperties;  // 0x11254A04

			// FUNCTION: ENGINE 0x101A73A0
			bool ReactionPushbackOrientTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A73C0
			bool ReactionPushbackOrientTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A73E0
			bool ReactionPushbackOrientTrack::SetOrientation(float newValue)
			{
				orientation = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101A7400
			bool ReactionPushbackOrientTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A7410
			bool ReactionPushbackOrientTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A7430
			bool ReactionPushbackOrientTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A7550
			fight::Property* ReactionPushbackOrientTrack::GetProperty(int index)
			{
				return gReactionPushbackOrientTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101A7570
			void ReactionPushbackOrientTrack::ClearProperties()
			{
				fight::FreePropertyList(&gReactionPushbackOrientTrackProperties);
			}

			// FUNCTION: ENGINE 0x101A7580
			ReactionPushbackOrientTrack::ReactionPushbackOrientTrack() : blendInTime(0.0f), blendOutTime(0.0f), orientation(0.0f), timeBegin(0.0f), timeEnd(-1.0f), priority(-5)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101A75E0
			float ReactionPushbackOrientTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101A75F0
			float ReactionPushbackOrientTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101A7600
			ReactionPushbackOrientTrack::~ReactionPushbackOrientTrack()
			{
			}

			// FUNCTION: ENGINE 0x101A7A10
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionPushbackOrientTrack::RegisterProperties()
			{
				if (gReactionPushbackOrientTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ReactionPushbackOrientTrack>("timeBegin", &ReactionPushbackOrientTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ReactionPushbackOrientTrack>("timeEnd", &ReactionPushbackOrientTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<ReactionPushbackOrientTrack>("orientation", &ReactionPushbackOrientTrack::SetOrientation);
					properties[2] = property;
					property = new fight::PropertyIntConstRange<ReactionPushbackOrientTrack>("priority", &ReactionPushbackOrientTrack::SetPriority);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<ReactionPushbackOrientTrack>("blendInTime", &ReactionPushbackOrientTrack::SetBlendInTime);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<ReactionPushbackOrientTrack>("blendOutTime", &ReactionPushbackOrientTrack::SetBlendOutTime);
					properties[5] = property;
					fight::RegisterPropertyList(properties, &gReactionPushbackOrientTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A79B0
			fight::TrackFactory* CreateReactionPushbackOrientTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReactionPushbackOrientTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A7E60
			void RegisterReactionPushbackOrientTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReactionPushbackOrientTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gReactionPushbackTrackProperties;  // 0x11254A08

			// FUNCTION: ENGINE 0x101A7450
			bool ReactionPushbackTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A7470
			bool ReactionPushbackTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A7490
			bool ReactionPushbackTrack::SetMaxDistance(float newValue)
			{
				maxDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A74B0
			bool ReactionPushbackTrack::SetSnapToPushback(bool newValue)
			{
				snapToPushback = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A74C0
			bool ReactionPushbackTrack::SetOrientation(float newValue)
			{
				orientation = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101A74E0
			bool ReactionPushbackTrack::SetProneSpin(float newValue)
			{
				proneSpin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101A7500
			bool ReactionPushbackTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A7510
			bool ReactionPushbackTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A7530
			bool ReactionPushbackTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A7610
			fight::Property* ReactionPushbackTrack::GetProperty(int index)
			{
				return gReactionPushbackTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101A7630
			void ReactionPushbackTrack::ClearProperties()
			{
				fight::FreePropertyList(&gReactionPushbackTrackProperties);
			}

			// FUNCTION: ENGINE 0x101A7640
			ReactionPushbackTrack::ReactionPushbackTrack() : blendInTime(0.0f), blendOutTime(0.0f), maxDistance(-1.0f), orientation(0.0f), proneSpin(0.0f), timeBegin(0.0f), timeEnd(-1.0f), priority(-5), snapToPushback(false)
			{
			}

			// FUNCTION: ENGINE 0x101A76A0
			float ReactionPushbackTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101A76B0
			float ReactionPushbackTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101A76C0
			ReactionPushbackTrack::~ReactionPushbackTrack()
			{
			}

			// FUNCTION: ENGINE 0x101A7BE0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionPushbackTrack::RegisterProperties()
			{
				if (gReactionPushbackTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ReactionPushbackTrack>("timeBegin", &ReactionPushbackTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ReactionPushbackTrack>("timeEnd", &ReactionPushbackTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<ReactionPushbackTrack>("maxDistance", &ReactionPushbackTrack::SetMaxDistance);
					properties[2] = property;
					property = new fight::PropertyBool<ReactionPushbackTrack>("snapToPushback", &ReactionPushbackTrack::SetSnapToPushback);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<ReactionPushbackTrack>("orientation", &ReactionPushbackTrack::SetOrientation);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<ReactionPushbackTrack>("proneSpin", &ReactionPushbackTrack::SetProneSpin);
					properties[5] = property;
					property = new fight::PropertyIntConstRange<ReactionPushbackTrack>("priority", &ReactionPushbackTrack::SetPriority);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<ReactionPushbackTrack>("blendInTime", &ReactionPushbackTrack::SetBlendInTime);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<ReactionPushbackTrack>("blendOutTime", &ReactionPushbackTrack::SetBlendOutTime);
					properties[8] = property;
					fight::RegisterPropertyList(properties, &gReactionPushbackTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A79E0
			fight::TrackFactory* CreateReactionPushbackTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReactionPushbackTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A7E90
			void RegisterReactionPushbackTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReactionPushbackTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<ReactionPushbackOrientTrack>;
			template class fight::PropertyIntConstRange<ReactionPushbackOrientTrack>;
			template class fight::TrackFactoryTemplate<ReactionPushbackOrientTrack>;
			template class fight::TrackFactoryCasterTemplate<ReactionPushbackOrientTrack>;
			template class fight::PropertyFloatConstRange<ReactionPushbackTrack>;
			template class fight::PropertyBool<ReactionPushbackTrack>;
			template class fight::PropertyIntConstRange<ReactionPushbackTrack>;
			template class fight::TrackFactoryTemplate<ReactionPushbackTrack>;
			template class fight::TrackFactoryCasterTemplate<ReactionPushbackTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101A76D0
// FUNCTION: ENGINE 0x101A7700
// FUNCTION: ENGINE 0x101A7730
// FUNCTION: ENGINE 0x101A7740
// FUNCTION: ENGINE 0x101A7770
// FUNCTION: ENGINE 0x101A7780
// FUNCTION: ENGINE 0x101A77B0
// FUNCTION: ENGINE 0x101A77E0
// FUNCTION: ENGINE 0x101A7810
// FUNCTION: ENGINE 0x101A7820
// FUNCTION: ENGINE 0x101A7850
// FUNCTION: ENGINE 0x101A7870
// FUNCTION: ENGINE 0x101A7880
// FUNCTION: ENGINE 0x101A78B0
// FUNCTION: ENGINE 0x101A78E0
// FUNCTION: ENGINE 0x101A78F0
// FUNCTION: ENGINE 0x101A7920
// FUNCTION: ENGINE 0x101A7940
// FUNCTION: ENGINE 0x101A7950
// FUNCTION: ENGINE 0x101A7980
// FUNCTION: ENGINE 0x101A79A0
// FUNCTION: ENGINE 0x101A7EC0
// FUNCTION: ENGINE 0x101A7EF0
// FUNCTION: ENGINE 0x101A7F10
// FUNCTION: ENGINE 0x101A7F40
// FUNCTION: ENGINE 0x101A7F60
// FUNCTION: ENGINE 0x101A7FB0
