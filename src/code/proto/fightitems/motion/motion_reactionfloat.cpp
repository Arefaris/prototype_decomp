// Fight items of the motion group: ReactionFloatTrack, TokenSetFloatDelayTrack (unit 0x101A69E0 - 0x101A73A0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_reactionfloat.h"
#include "code/proto/fightitems/motion/motionmessages4.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gReactionFloatTrackProperties;  // 0x112549F8

			// FUNCTION: ENGINE 0x101A69E0
			bool ReactionFloatTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A6A00
			bool ReactionFloatTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A6A20
			bool ReactionFloatTrack::SetSnapToPushback(bool newValue)
			{
				snapToPushback = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A6A30
			bool ReactionFloatTrack::SetOrientation(float newValue)
			{
				orientation = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101A6A50
			bool ReactionFloatTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A6A60
			bool ReactionFloatTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A6A80
			bool ReactionFloatTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A6AE0
			fight::Property* ReactionFloatTrack::GetProperty(int index)
			{
				return gReactionFloatTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101A6B00
			void ReactionFloatTrack::ClearProperties()
			{
				fight::FreePropertyList(&gReactionFloatTrackProperties);
			}

			// FUNCTION: ENGINE 0x101A6B10
			ReactionFloatTrack::ReactionFloatTrack() : blendInTime(0.0f), blendOutTime(0.0f), orientation(0.0f), timeBegin(0.0f), timeEnd(-1.0f), priority(-5), snapToPushback(false)
			{
			}

			// FUNCTION: ENGINE 0x101A6B70
			float ReactionFloatTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101A6B80
			float ReactionFloatTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101A6B90
			ReactionFloatTrack::~ReactionFloatTrack()
			{
			}

			// FUNCTION: ENGINE 0x101A6F10
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionFloatTrack::RegisterProperties()
			{
				if (gReactionFloatTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ReactionFloatTrack>("timeBegin", &ReactionFloatTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ReactionFloatTrack>("timeEnd", &ReactionFloatTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBool<ReactionFloatTrack>("snapToPushback", &ReactionFloatTrack::SetSnapToPushback);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<ReactionFloatTrack>("orientation", &ReactionFloatTrack::SetOrientation);
					properties[3] = property;
					property = new fight::PropertyIntConstRange<ReactionFloatTrack>("priority", &ReactionFloatTrack::SetPriority);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<ReactionFloatTrack>("blendInTime", &ReactionFloatTrack::SetBlendInTime);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<ReactionFloatTrack>("blendOutTime", &ReactionFloatTrack::SetBlendOutTime);
					properties[6] = property;
					fight::RegisterPropertyList(properties, &gReactionFloatTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A6EB0
			fight::TrackFactory* CreateReactionFloatTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReactionFloatTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A7200
			void RegisterReactionFloatTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReactionFloatTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gTokenSetFloatDelayTrackProperties;  // 0x112549FC

			// FUNCTION: ENGINE 0x101A6AA0
			bool TokenSetFloatDelayTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A6AC0
			bool TokenSetFloatDelayTrack::SetFloatDelay(float newValue)
			{
				floatDelay = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A6BA0
			fight::Property* TokenSetFloatDelayTrack::GetProperty(int index)
			{
				return gTokenSetFloatDelayTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101A6BC0
			void TokenSetFloatDelayTrack::ClearProperties()
			{
				fight::FreePropertyList(&gTokenSetFloatDelayTrackProperties);
			}

			// FUNCTION: ENGINE 0x101A6BD0
			TokenSetFloatDelayTrack::TokenSetFloatDelayTrack() : floatDelay(0.0f), timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101A6C00
			float TokenSetFloatDelayTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101A6C10
			float TokenSetFloatDelayTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101A6C20
			TokenSetFloatDelayTrack::~TokenSetFloatDelayTrack()
			{
			}

			// FUNCTION: ENGINE 0x101A7120
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TokenSetFloatDelayTrack::RegisterProperties()
			{
				if (gTokenSetFloatDelayTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<TokenSetFloatDelayTrack>("timeBegin", &TokenSetFloatDelayTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<TokenSetFloatDelayTrack>("floatDelay", &TokenSetFloatDelayTrack::SetFloatDelay);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gTokenSetFloatDelayTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A6EE0
			fight::TrackFactory* CreateTokenSetFloatDelayTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<TokenSetFloatDelayTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A7230
			void RegisterTokenSetFloatDelayTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<TokenSetFloatDelayTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x10107CF0
			// NONMATCHING: registers, the engine keeps the owner in ebx and the zero in ebp (best 86 %)
#ifdef NONMATCHING
			ReactionFloatAction::ReactionFloatAction(ReactionFloatTrack* newTrack, TrackOwner* owner) : fight::Action(0xE00), target(owner->handle), unknown20(0.0f), event(0), driver(0), unknown2C(0.0f), link(newTrack), unknown3C(0.0f), unknown40(0.0f), unknown44(0.0f)
			{
				engine::AssignRefCountedCopy3(&event, (owner->kind == 0x21001) ? owner : 0);
			}
#endif

			// FUNCTION: ENGINE 0x10107B00
			ReactionFloatAction::~ReactionFloatAction()
			{
				core::SafeReleaseRefCopy3(&event);
				engine::ReleaseDriverCopy2(&driver);
			}

			// FUNCTION: ENGINE 0x10107B50
			void ReactionFloatAction::Slot6()
			{
				engine::GameObject* object = target.Get();
				if (object != 0)
				{
					choreo::Puppet* puppet = engine::GetPuppet(object);
					if (puppet != 0)
					{
						puppet->RemoveDriver(driver, false);
					}
					engine::ReleaseDriverCopy2(&driver);
				}
			}

			// FUNCTION: ENGINE 0x101083D0
			fight::Action* ReactionFloatTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				TrackOwner* actionOwner = AsActionOwner(owner);
				return new ReactionFloatAction(this, actionOwner);
			}

			// FUNCTION: ENGINE 0x101082A0
			TokenSetFloatDelayAction::TokenSetFloatDelayAction(TokenSetFloatDelayTrack* newTrack, TrackOwner* owner) : fight::Action(0xE00), target(owner->handle), link(newTrack)
			{
			}

			// FUNCTION: ENGINE 0x10107BE0
			TokenSetFloatDelayAction::~TokenSetFloatDelayAction()
			{
			}

			// FUNCTION: ENGINE 0x10108340
			bool TokenSetFloatDelayAction::Slot5(int arg, float value)
			{
				if (link.object != 0)
				{
					engine::GameObject* object = target.Get();
					if (object != 0)
					{
						SetFloatDelayTokenMsg message(link.object->floatDelay);
						object->SendMessage(&message);
					}
				}
				return false;
			}

			// FUNCTION: ENGINE 0x10108430
			fight::Action* TokenSetFloatDelayTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				TrackOwner* actionOwner = AsActionOwner(owner);
				return new TokenSetFloatDelayAction(this, actionOwner);
			}

			// ---- actions end
			template class fight::PropertyFloatConstRange<ReactionFloatTrack>;
			template class fight::PropertyBool<ReactionFloatTrack>;
			template class fight::PropertyIntConstRange<ReactionFloatTrack>;
			template class fight::TrackFactoryTemplate<ReactionFloatTrack>;
			template class fight::TrackFactoryCasterTemplate<ReactionFloatTrack>;
			template class fight::PropertyFloatConstRange<TokenSetFloatDelayTrack>;
			template class fight::TrackFactoryTemplate<TokenSetFloatDelayTrack>;
			template class fight::TrackFactoryCasterTemplate<TokenSetFloatDelayTrack>;
		}
	}
}

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// FUNCTION: ENGINE 0x10107850
			bool ReactionFloatTrack::GetSnapToPushback() const
			{
				return snapToPushback;
			}

			// FUNCTION: ENGINE 0x10107870
			int ReactionFloatTrack::GetPriority() const
			{
				return priority;
			}

			// FUNCTION: ENGINE 0x10107880
			float ReactionFloatTrack::GetBlendInTime() const
			{
				return blendInTime;
			}

			// FUNCTION: ENGINE 0x10107890
			float ReactionFloatTrack::GetBlendOutTime() const
			{
				return blendOutTime;
			}
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101A6C30
// FUNCTION: ENGINE 0x101A6C60
// FUNCTION: ENGINE 0x101A6C90
// FUNCTION: ENGINE 0x101A6CA0
// FUNCTION: ENGINE 0x101A6CD0
// FUNCTION: ENGINE 0x101A6CE0
// FUNCTION: ENGINE 0x101A6D10
// FUNCTION: ENGINE 0x101A6D40
// FUNCTION: ENGINE 0x101A6D70
// FUNCTION: ENGINE 0x101A6D80
// FUNCTION: ENGINE 0x101A6DB0
// FUNCTION: ENGINE 0x101A6DD0
// FUNCTION: ENGINE 0x101A6DE0
// FUNCTION: ENGINE 0x101A6E10
// FUNCTION: ENGINE 0x101A6E30
// FUNCTION: ENGINE 0x101A6E40
// FUNCTION: ENGINE 0x101A6E70
// FUNCTION: ENGINE 0x101A6EA0
// FUNCTION: ENGINE 0x101A7260
// FUNCTION: ENGINE 0x101A7290
// FUNCTION: ENGINE 0x101A72B0
// FUNCTION: ENGINE 0x101A72E0
// FUNCTION: ENGINE 0x101A7300
// FUNCTION: ENGINE 0x101A7350
