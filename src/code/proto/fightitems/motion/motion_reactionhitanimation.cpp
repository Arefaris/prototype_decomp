// Fight items of the motion group: ReactionHitAnimationTrack (unit 0x101A9500 - 0x101A9F10; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_reactionhitanimation.h"
#include "code/proto/fightitems/motion/motioncommon.h"

namespace engine
{
	extern core::Name<core::CaseSensitiveKey> gPuppetAttributeName;
}

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
			// FUNCTION: ENGINE 0x1010D060
			ReactionHitAnimationAction::ReactionHitAnimationAction(ReactionHitAnimationTrack* newTrack, core::IRefCount* owner) : fight::Action(0x600), link(newTrack), target(engine::GetObjectHandle(owner)), event(0), driver(0)
			{
				engine::AssignRefCountedCopy3(&event, AsHitEventOwner(owner));
			}

			// FUNCTION: ENGINE 0x1010CE30
			ReactionHitAnimationAction::~ReactionHitAnimationAction()
			{
				engine::ReleaseDriver(driver);
				core::SafeReleaseRefCopy3(&event);
			}

			// FUNCTION: ENGINE 0x1010CF30
			void ReactionHitAnimationAction::Slot6()
			{
				core::SafeReleaseRefCopy3(&event);
				if (driver != 0 && target.IsValid())
				{
					engine::GameObject* object = target.Get();
					engine::Attribute<choreo::Puppet*>* attribute = (engine::Attribute<choreo::Puppet*>*)object->FindAttribute(engine::gPuppetAttributeName);
					if (attribute != 0)
					{
						choreo::Puppet** value = &attribute->value;
						if (value != 0 && *value != 0)
						{
							(*value)->SetEndlessLifetime(driver, false, choreo::gMinusOne);
							engine::ReleaseDriverCopy(driver);
						}
					}
				}
			}

			// FUNCTION: ENGINE 0x1010CE80
			// NONMATCHING: block order, the engine places the shared failure return before the body (best 24 %)
#ifdef NONMATCHING
			bool ReactionHitAnimationAction::Slot7(int arg, float value)
			{
				if (driver == 0 || !target.IsValid())
				{
					return false;
				}
				engine::GameObject* object = target.Get();
				engine::Attribute<choreo::Puppet*>* attribute = (engine::Attribute<choreo::Puppet*>*)object->FindAttribute(engine::gPuppetAttributeName);
				if (attribute != 0)
				{
					choreo::Puppet** slot = &attribute->value;
					if (slot != 0 && *slot != 0)
					{
						return !(*slot)->IsEnding(driver);
					}
				}
				return false;
			}
#endif

			// FUNCTION: ENGINE 0x1010D560
			fight::Action* ReactionHitAnimationTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				TrackOwner* actionOwner = AsActionOwner(owner);
				return new ReactionHitAnimationAction(this, actionOwner);
			}

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

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::EnumEntry gReactionHitAnimationTrackCyclicTable[4] =
				{
					{ fight::Name("From Animation", 0) },
					{ fight::Name("Not Cyclic", 0) },
					{ fight::Name("Cyclic", 0) },
					{ fight::Name("Hold End Frame", 0) }
				};
		}
	}
}

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// FUNCTION: ENGINE 0x1010CC50
			float ReactionHitAnimationTrack::GetTimeScale() const
			{
				return timeScale;
			}

			// FUNCTION: ENGINE 0x1010CC60
			float ReactionHitAnimationTrack::GetTimeEndMin() const
			{
				return timeEndMin;
			}

			// FUNCTION: ENGINE 0x1010CC80
			float ReactionHitAnimationTrack::GetSpeed() const
			{
				return speed;
			}

			// FUNCTION: ENGINE 0x1010CC90
			float ReactionHitAnimationTrack::GetSpeedMax() const
			{
				return speedMax;
			}

			// FUNCTION: ENGINE 0x1010CCA0
			float ReactionHitAnimationTrack::GetInitFrame() const
			{
				return initFrame;
			}

			// FUNCTION: ENGINE 0x1010CCB0
			float ReactionHitAnimationTrack::GetRandomFrame() const
			{
				return randomFrame;
			}

			// FUNCTION: ENGINE 0x1010CCC0
			float ReactionHitAnimationTrack::GetStartFrame() const
			{
				return startFrame;
			}

			// FUNCTION: ENGINE 0x1010CCD0
			float ReactionHitAnimationTrack::GetEndFrame() const
			{
				return endFrame;
			}

			// FUNCTION: ENGINE 0x1010CCE0
			int ReactionHitAnimationTrack::GetCyclic() const
			{
				return cyclic;
			}

			// FUNCTION: ENGINE 0x1010CD00
			int ReactionHitAnimationTrack::GetPriority() const
			{
				return priority;
			}

			// FUNCTION: ENGINE 0x1010CD10
			float ReactionHitAnimationTrack::GetBlendInTime() const
			{
				return blendInTime;
			}

			// FUNCTION: ENGINE 0x1010CD20
			float ReactionHitAnimationTrack::GetBlendOutTime() const
			{
				return blendOutTime;
			}
		}
	}
}

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// FUNCTION: ENGINE 0x1010CC70
			const fight::Name& ReactionHitAnimationTrack::GetAnimation() const
			{
				return animation;
			}

			// FUNCTION: ENGINE 0x1010CCF0
			const fight::Name& ReactionHitAnimationTrack::GetPartition() const
			{
				return partition;
			}
		}
	}
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D4FE70
// FUNCTION: ENGINE 0x10D81C10


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
