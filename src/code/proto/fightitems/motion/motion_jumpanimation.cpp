// Fight items of the motion group: JumpAnimationTrack (unit 0x10184DF0 - 0x10185900; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_jumpanimation.h"
#include "code/engine/fight/supportingsurface.h"
#include "code/math/worldbounds.h"
#include <math.h>

namespace engine
{
	// The name of the puppet attribute of a game object (0x112834F0)
	extern content::ObjectName gPuppetAttributeName;

	// FUNCTION: ENGINE 0x100E0190
	void ReleaseDriverCopy(choreo::Driver*& driver)
	{
		if (driver != 0)
		{
			driver->Release();
			driver = 0;
		}
	}
}

namespace choreo
{
	extern const float gMinusOne;
}

namespace pure3d
{
	class Animation;
}

namespace engine
{
	// 0x1082BC10 (another unit; name guess): the animation of that name in the inventory, found as the inventory's DynamicCaster
	// does (keep: the engine marks the answer as used)
	pure3d::Animation* FindAnimation(const content::ObjectName& name, content::LoadInventory* inventory, bool keep, void* extra);
}

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

			// ---- actions begin
			// FUNCTION: ENGINE 0x100E00D0
			float JumpAnimationAction::GetVerticalVelocity(engine::GameObject* object)
			{
				math::Vector velocity;
				velocity.x = math::kZeroVector.x;
				velocity.y = math::kZeroVector.y;
				velocity.z = math::kZeroVector.z;
				engine::GetObjectVelocity(object, 0, &velocity);
				return velocity.y;
			}

			// FUNCTION: ENGINE 0x100E0130
			void JumpAnimationAction::SetRange(float duration, float start, float end)
			{
				((choreo::AnimationDriver*)driver)->SetRange(duration, 1.0f, start, end);
				((choreo::AnimationDriver*)driver)->SetUnknownE4(start);
			}

			// FUNCTION: ENGINE 0x100E0480
			void JumpAnimationAction::SetClimbRange(float height, float peak)
			{
				SetRange((height - peak) / link.object->gravity, link.object->startFrameClimb, link.object->GetEndFrameClimb());
			}

			// FUNCTION: ENGINE 0x100E04C0
			void JumpAnimationAction::SetPeakRange(float height, float peak)
			{
				SetRange((height - peak) / link.object->gravity, link.object->GetStartFramePeak(), link.object->GetEndFramePeak());
			}

			// FUNCTION: ENGINE 0x100E0500
			void JumpAnimationAction::SetFallRange()
			{
				float start = link.object->GetStartFrameFall();
				((choreo::AnimationDriver*)driver)->SetRange(0.0f, 1.0f, start, link.object->GetEndFrameFall());
				((choreo::AnimationDriver*)driver)->SetUnknownE4(start);
			}

			// FUNCTION: ENGINE 0x100E05B0
			float JumpAnimationAction::UpdatePhase(engine::GameObject* object)
			{
				float velocity = GetVerticalVelocity(object);
				float peak = (float)fabs(link.object->peakVerticalVelocity);
				float lower = math::WORLD_MIN - peak;
				if (lower > velocity)
				{
					if (phase != 3)
					{
						phase = 3;
						SetFallRange();
					}
				}
				else if (peak > velocity)
				{
					if (phase != 2)
					{
						phase = 2;
						SetPeakRange(velocity, lower);
					}
				}
				else if (phase != 1)
				{
					phase = 1;
					SetClimbRange(velocity, peak);
				}
				return velocity;
			}

			// FUNCTION: ENGINE 0x100E03B0
			JumpAnimationAction::JumpAnimationAction(fight::Track* listener, JumpAnimationTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), watch(listener), link(newTrack), target(newTarget), driver(0), unknown3C(0.0f), unknown44(0)
			{
			}

			// FUNCTION: ENGINE 0x100E0250
			JumpAnimationAction::~JumpAnimationAction()
			{
				engine::ReleaseDriver(driver);
			}

			// FUNCTION: ENGINE 0x100E0560
			fight::Action* JumpAnimationTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new JumpAnimationAction(listener, this, handle);
			}

			// FUNCTION: ENGINE 0x100E02A0
			void JumpAnimationAction::Slot6()
			{
				engine::GameObject* object = target.Get();
				if (object != 0)
				{
					choreo::Puppet* puppet = 0;
					engine::BaseAttribute* attribute = object->FindAttribute(engine::gPuppetAttributeName);
					if (attribute != 0)
					{
						choreo::Puppet** value = &((engine::Attribute<choreo::Puppet*>*)attribute)->value;
						if (value != 0 && *value != 0)
						{
							puppet = *value;
						}
					}
					if (driver != 0 && puppet != 0)
					{
						puppet->SetEndlessLifetime(driver, false, choreo::gMinusOne);
						engine::ReleaseDriverCopy(driver);
					}
				}
			}

			// FUNCTION: ENGINE 0x100E06B0
			// NONMATCHING: the engine keeps the object in ebx and the animation in ebp (ours the other way round), so its early exits pop fewer registers (24 %, every operation is the engine's)
#ifdef NONMATCHING
			bool JumpAnimationAction::Slot5(int arg, float value)
			{
				engine::GameObject* object = target.Get();
				if (link.object == 0 || object == 0 || link.object->gravity < 0.00001f)
				{
					return false;
				}
				pure3d::Animation* animation = engine::FindAnimation(link.object->animation, content::gRootInventory, true, 0);
				if (animation == 0)
				{
					char buffer[0x400] = { 0 };
					if (watch.track != 0)
					{
						watch.track->GetPath(buffer, 0x400, 0);
					}
					return false;
				}
				engine::AttributePtr<choreo::Puppet*> attribute = object->GetAttributePtr<choreo::Puppet*>(engine::gPuppetAttributeName);
				if (attribute.value == 0 || *attribute.value == 0)
				{
					return false;
				}
				unknown44 = arg;
				SetIndexedFlag(arg - 1, true);
				choreo::Puppet* puppet = *attribute.value;
				pure3d::Skeleton* skeleton = puppet->GetSkeleton();
				engine::AssignDriver(driver, new choreo::AnimationDriver(skeleton, animation));
				driver->SetName(animation->mName);
				((choreo::AnimationDriver*)driver)->SetUnknown64(link.object->GetHasRootTranslation());
				((choreo::AnimationDriver*)driver)->SetUnknown65(link.object->GetHasRootRotation());
				((choreo::AnimationDriver*)driver)->mUnknown54 = false;
				((choreo::AnimationDriver*)driver)->mUnknown55 = false;
				((choreo::PartitionDriver*)driver)->SetPartitionByName(link.object->GetPartition());
				phase = 0;
				UpdatePhase(object);
				float blendIn = link.object->GetBlendInTime();
				float blendOut = link.object->GetBlendOutTime();
				bool endless = link.object->Slot10() < 0.0f;
				float lifetime;
				if (endless)
				{
					lifetime = choreo::gMinusOne;
				}
				else
				{
					lifetime = link.object->Slot10();
				}
				if (blendIn < 0.0f)
				{
					((choreo::AnimationDriver*)driver)->mUnknownF0 = true;
					blendIn = math::WORLD_MIN - blendIn;
					((choreo::AnimationDriver*)driver)->mUnknownF4 = blendIn;
					if (!endless)
					{
						lifetime = lifetime + blendIn;
						if (lifetime <= 0.0f)
						{
							lifetime = 0.0f;
						}
					}
				}
				if (!endless && blendOut < 0.0f)
				{
					lifetime = lifetime + blendOut;
					if (lifetime <= 0.0f)
					{
						lifetime = 0.0f;
					}
					blendOut = math::WORLD_MIN - blendOut;
				}
				float end = link.object->endFrameFall;
				if (end <= 0.0f)
				{
					end = ((choreo::AnimationDriver*)driver)->mBinding.mClip.GetDuration() - link.object->endFrameFall;
				}
				unknown3C = end - 0.00001f;
				puppet->SetDriver(driver, lifetime, link.object->GetPriority(), 1.0f, blendIn, blendOut, choreo::gMinusOne);
				return true;
			}
#endif

			// FUNCTION: ENGINE 0x100E0A50
			// NONMATCHING: the engine tests the puppet pointer with cmp [eax], 0 and loads it again for IsEnding, ours loads it once into ecx (99 %)
#ifdef NONMATCHING
			bool JumpAnimationAction::Slot7(int arg, float value)
			{
				engine::GameObject* object = target.Get();
				if (object != 0 && link.object != 0 && driver != 0)
				{
					if (arg == 0)
					{
						UpdatePhase(object);
					}
					if (arg == unknown44 - 1)
					{
						engine::AttributePtr<choreo::Puppet*> attribute = object->GetAttributePtr<choreo::Puppet*>(engine::gPuppetAttributeName);
						choreo::Puppet** value = attribute.value;
						if (value == 0 || *value == 0)
						{
							return false;
						}
						choreo::Puppet* puppet = *value;
						if (phase == 3)
						{
							bool stopped = puppet->IsEnding(driver) || ((choreo::AnimationDriver*)driver)->mUnknownE4 > unknown3C;
							return !stopped;
						}
					}
					return true;
				}
				return false;
			}
#endif

			// ---- actions end
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
// FUNCTION: ENGINE 0x100E0000
// FUNCTION: ENGINE 0x100E0010
// FUNCTION: ENGINE 0x100E0020
// FUNCTION: ENGINE 0x100E0030
// FUNCTION: ENGINE 0x100E0040
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
