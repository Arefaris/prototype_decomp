// Fight items of the motion group: ChargeCondition, ChargeTrack, ChargeSetTrack, AnimationChargeTrack, ChargeClearTrack (unit 0x101479B0 - 0x10149690; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_charge.h"
#include "code/proto/fightitems/motion/motioncommon.h"
#include "code/proto/fightitems/motion/motionmessages.h"
#include "code/engine/fight/coreactions.h"

namespace engine
{
	// FUNCTION: ENGINE 0x100A0C40
	void ReleaseDriver(choreo::Driver*& driver)
	{
		if (driver != 0)
		{
			driver->Release();
			driver = 0;
		}
	}

	// FUNCTION: ENGINE 0x100A0C60
	void AssignDriver(choreo::Driver*& driver, choreo::Driver* newDriver)
	{
		if (newDriver != 0)
		{
			newDriver->AddRef();
		}
		if (driver != 0)
		{
			driver->Release();
		}
		driver = newDriver;
	}
}

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gChargeConditionProperties;  // 0x11254320

			// FUNCTION: ENGINE 0x101479B0
			bool ChargeCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101479C0
			bool ChargeCondition::SetCharge(float newValue)
			{
				charge = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101479E0
			bool ChargeCondition::SetType(int newValue)
			{
				type = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10147C40
			fight::Property* ChargeCondition::GetProperty(int index)
			{
				return gChargeConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10147C60
			void ChargeCondition::ClearProperties()
			{
				fight::FreePropertyList(&gChargeConditionProperties);
			}

			// FUNCTION: ENGINE 0x10147C70
			ChargeCondition::ChargeCondition() : fight::Condition(0), charge(0.0f), compare(0), type(0)
			{
			}

			// FUNCTION: ENGINE 0x10147CB0
			ChargeCondition::~ChargeCondition()
			{
			}

			// FUNCTION: ENGINE 0x10148970
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ChargeCondition::RegisterProperties()
			{
				if (gChargeConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<ChargeCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &ChargeCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ChargeCondition>("charge", &ChargeCondition::SetCharge);
					properties[1] = property;
					property = new fight::PropertyEnumConstList<ChargeCondition>("type", gChargeConditionTypeTable, gChargeConditionTypeCount, &ChargeCondition::SetType);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gChargeConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10148880
			fight::ConditionFactory* CreateChargeConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ChargeCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10148F10
			void RegisterChargeConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ChargeCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gChargeTrackProperties;  // 0x11254324

			// FUNCTION: ENGINE 0x101479F0
			bool ChargeTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10147A10
			bool ChargeTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10147A30
			bool ChargeTrack::SetType(int newValue)
			{
				type = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10147A40
			bool ChargeTrack::SetClearOnBegin(bool newValue)
			{
				clearOnBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10147A50
			bool ChargeTrack::SetFinalCharge(float newValue)
			{
				finalCharge = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10147A70
			bool ChargeTrack::SetRandomRange(float newValue)
			{
				randomRange = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10147CC0
			fight::Property* ChargeTrack::GetProperty(int index)
			{
				return gChargeTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10147CE0
			void ChargeTrack::ClearProperties()
			{
				fight::FreePropertyList(&gChargeTrackProperties);
			}

			// FUNCTION: ENGINE 0x10147CF0
			ChargeTrack::ChargeTrack() : finalCharge(1.0f), randomRange(0.0f), timeBegin(0.0f), timeEnd(-1.0f), type(0), clearOnBegin(true)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10147D50
			float ChargeTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10147D60
			float ChargeTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10147D70
			ChargeTrack::~ChargeTrack()
			{
			}

			// FUNCTION: ENGINE 0x10148AB0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ChargeTrack::RegisterProperties()
			{
				if (gChargeTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ChargeTrack>("timeBegin", &ChargeTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ChargeTrack>("timeEnd", &ChargeTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyEnumConstList<ChargeTrack>("type", gChargeConditionTypeTable, gChargeConditionTypeCount, &ChargeTrack::SetType);
					properties[2] = property;
					property = new fight::PropertyBool<ChargeTrack>("clearOnBegin", &ChargeTrack::SetClearOnBegin);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<ChargeTrack>("finalCharge", &ChargeTrack::SetFinalCharge);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<ChargeTrack>("randomRange", &ChargeTrack::SetRandomRange);
					properties[5] = property;
					fight::RegisterPropertyList(properties, &gChargeTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101488B0
			fight::TrackFactory* CreateChargeTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ChargeTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10148F40
			void RegisterChargeTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ChargeTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gChargeSetTrackProperties;  // 0x11254328

			// FUNCTION: ENGINE 0x10147A90
			bool ChargeSetTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10147AB0
			bool ChargeSetTrack::SetType(int newValue)
			{
				type = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10147AC0
			bool ChargeSetTrack::SetCharge(float newValue)
			{
				charge = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10147AE0
			bool ChargeSetTrack::SetRandomRange(float newValue)
			{
				randomRange = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10147D80
			fight::Property* ChargeSetTrack::GetProperty(int index)
			{
				return gChargeSetTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10147DA0
			void ChargeSetTrack::ClearProperties()
			{
				fight::FreePropertyList(&gChargeSetTrackProperties);
			}

			// FUNCTION: ENGINE 0x10147DB0
			ChargeSetTrack::ChargeSetTrack() : charge(1.0f), randomRange(0.0f), timeBegin(0.0f), type(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10147E00
			float ChargeSetTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10147E10
			float ChargeSetTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x10147E20
			ChargeSetTrack::~ChargeSetTrack()
			{
			}

			// FUNCTION: ENGINE 0x10148C90
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ChargeSetTrack::RegisterProperties()
			{
				if (gChargeSetTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ChargeSetTrack>("timeBegin", &ChargeSetTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<ChargeSetTrack>("type", gChargeConditionTypeTable, gChargeConditionTypeCount, &ChargeSetTrack::SetType);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<ChargeSetTrack>("charge", &ChargeSetTrack::SetCharge);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<ChargeSetTrack>("randomRange", &ChargeSetTrack::SetRandomRange);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gChargeSetTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101488E0
			fight::TrackFactory* CreateChargeSetTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ChargeSetTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10148F70
			void RegisterChargeSetTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ChargeSetTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gAnimationChargeTrackProperties;  // 0x1125432C

			// FUNCTION: ENGINE 0x10147B00
			bool AnimationChargeTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10147B20
			bool AnimationChargeTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10147F00
			bool AnimationChargeTrack::SetAnimation(const fight::Name& newValue)
			{
				animation = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10147B40
			bool AnimationChargeTrack::SetType(int newValue)
			{
				type = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10147B50
			bool AnimationChargeTrack::SetStartFrame(float newValue)
			{
				startFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10147B70
			bool AnimationChargeTrack::SetEndFrame(float newValue)
			{
				endFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10147B90
			bool AnimationChargeTrack::SetReverse(bool newValue)
			{
				reverse = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10147F20
			bool AnimationChargeTrack::SetPartition(const fight::Name& newValue)
			{
				partition = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10147BA0
			bool AnimationChargeTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10147BB0
			bool AnimationChargeTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10147BD0
			bool AnimationChargeTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10147E30
			fight::Property* AnimationChargeTrack::GetProperty(int index)
			{
				return gAnimationChargeTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10147E50
			void AnimationChargeTrack::ClearProperties()
			{
				fight::FreePropertyList(&gAnimationChargeTrackProperties);
			}

			// FUNCTION: ENGINE 0x10147FD0
			AnimationChargeTrack::AnimationChargeTrack() : blendInTime(0.0f), blendOutTime(0.0f), endFrame(-1.0f), startFrame(0.0f), timeBegin(0.0f), timeEnd(-1.0f), priority(0), type(0), reverse(false)
			{
			}

			// FUNCTION: ENGINE 0x10148040
			float AnimationChargeTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10148050
			float AnimationChargeTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10148060
			AnimationChargeTrack::~AnimationChargeTrack()
			{
			}

			// FUNCTION: ENGINE 0x10149190
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AnimationChargeTrack::RegisterProperties()
			{
				if (gAnimationChargeTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<AnimationChargeTrack>("timeBegin", &AnimationChargeTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<AnimationChargeTrack>("timeEnd", &AnimationChargeTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyName<AnimationChargeTrack>("animation", &AnimationChargeTrack::SetAnimation);
					properties[2] = property;
					property = new fight::PropertyEnumConstList<AnimationChargeTrack>("type", gChargeConditionTypeTable, gChargeConditionTypeCount, &AnimationChargeTrack::SetType);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<AnimationChargeTrack>("startFrame", &AnimationChargeTrack::SetStartFrame);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<AnimationChargeTrack>("endFrame", &AnimationChargeTrack::SetEndFrame);
					properties[5] = property;
					property = new fight::PropertyBool<AnimationChargeTrack>("reverse", &AnimationChargeTrack::SetReverse);
					properties[6] = property;
					property = new fight::PropertyName<AnimationChargeTrack>("partition", &AnimationChargeTrack::SetPartition);
					properties[7] = property;
					property = new fight::PropertyIntConstRange<AnimationChargeTrack>("priority", &AnimationChargeTrack::SetPriority);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<AnimationChargeTrack>("blendInTime", &AnimationChargeTrack::SetBlendInTime);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<AnimationChargeTrack>("blendOutTime", &AnimationChargeTrack::SetBlendOutTime);
					properties[10] = property;
					fight::RegisterPropertyList(properties, &gAnimationChargeTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10148910
			fight::TrackFactory* CreateAnimationChargeTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<AnimationChargeTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10148FA0
			void RegisterAnimationChargeTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<AnimationChargeTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gChargeClearTrackProperties;  // 0x11254330

			// FUNCTION: ENGINE 0x10147BF0
			bool ChargeClearTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10147C10
			bool ChargeClearTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10147C30
			bool ChargeClearTrack::SetClearOnBegin(bool newValue)
			{
				clearOnBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10147E60
			fight::Property* ChargeClearTrack::GetProperty(int index)
			{
				return gChargeClearTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10147E80
			void ChargeClearTrack::ClearProperties()
			{
				fight::FreePropertyList(&gChargeClearTrackProperties);
			}

			// FUNCTION: ENGINE 0x10147E90
			ChargeClearTrack::ChargeClearTrack() : timeBegin(0.0f), timeEnd(-1.0f), clearOnBegin(true)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10147ED0
			float ChargeClearTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10147EE0
			float ChargeClearTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10147EF0
			ChargeClearTrack::~ChargeClearTrack()
			{
			}

			// FUNCTION: ENGINE 0x10148E00
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ChargeClearTrack::RegisterProperties()
			{
				if (gChargeClearTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ChargeClearTrack>("timeBegin", &ChargeClearTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ChargeClearTrack>("timeEnd", &ChargeClearTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBool<ChargeClearTrack>("clearOnBegin", &ChargeClearTrack::SetClearOnBegin);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gChargeClearTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10148940
			fight::TrackFactory* CreateChargeClearTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ChargeClearTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10148FD0
			void RegisterChargeClearTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ChargeClearTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x100A1310
			ChargeAction::ChargeAction(ChargeTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xA00), target(newTarget), link(newTrack), unknown2C(0.0f)
			{
			}

			// FUNCTION: ENGINE 0x100A0FB0
			ChargeAction::~ChargeAction()
			{
			}

			// FUNCTION: ENGINE 0x100A1D90
			fight::Action* ChargeTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new ChargeAction(this, handle);
			}

			// FUNCTION: ENGINE 0x100A1600
			ChargeSetAction::ChargeSetAction(ChargeSetTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0x200), target(newTarget), link(newTrack)
			{
			}

			// FUNCTION: ENGINE 0x100A1000
			ChargeSetAction::~ChargeSetAction()
			{
			}

			// FUNCTION: ENGINE 0x100A1DE0
			fight::Action* ChargeSetTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new ChargeSetAction(this, handle);
			}

			// FUNCTION: ENGINE 0x100A1770
			ChargeClearAction::ChargeClearAction(ChargeClearTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0x600), target(newTarget), link(newTrack)
			{
			}

			// FUNCTION: ENGINE 0x100A1050
			ChargeClearAction::~ChargeClearAction()
			{
			}

			// FUNCTION: ENGINE 0x100A1E30
			fight::Action* ChargeClearTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new ChargeClearAction(this, handle);
			}

			// FUNCTION: ENGINE 0x100A1960
			AnimationChargeAction::AnimationChargeAction(AnimationChargeTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget), driver(0)
			{
			}

			// FUNCTION: ENGINE 0x100A10A0
			AnimationChargeAction::~AnimationChargeAction()
			{
				engine::ReleaseDriver(driver);
			}

			// FUNCTION: ENGINE 0x100A1E80
			fight::Action* AnimationChargeTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new AnimationChargeAction(this, handle);
			}

			// ---- actions end
			// FUNCTION: ENGINE 0x100A0EC0
			bool ChargeCondition::Evaluate(int a, int b, int c, int d)
			{
				engine::GameObject* object = engine::GetObjectHandle(AsOwner(c)).Get();
				if (object == 0)
				{
					return false;
				}
				ChargeGetMessage message(type);
				object->SendMessage(&message);
				float current = message.value;
				return fight::CompareFloats(compare, &current, &charge);
			}

			// FUNCTION: ENGINE 0x100A13C0
			bool ChargeAction::Slot5(int arg, float value)
			{
				if (link.object == 0)
				{
					return false;
				}
				engine::GameObject* object = target.Get();
				if (object == 0)
				{
					return false;
				}
				int type = link.object->type;
				ChargeGetMessage getMessage(type);
				object->SendMessage(&getMessage);
				float first = getMessage.value;
				float second = (first >= 0.0f) ? first : 0.0f;
				float charge = (0.0f <= second - engine::driving::gOne) ? engine::driving::gOne : second;
				if (link.object->clearOnBegin)
				{
					charge = 0.0f;
				}
				ChargeSetMessage setMessage(charge, type);
				object->SendMessage(&setMessage);
				float duration = link.object->Slot10();
				float goal = link.object->finalCharge;
				if (duration > 0.0f)
				{
					if (goal < engine::driving::gOne)
					{
						goal = goal - charge;
					}
					goal = goal / duration;
				}
				unknown2C = goal;
				return true;
			}

			// FUNCTION: ENGINE 0x100A1550
			bool ChargeAction::Slot7(int arg, float value)
			{
				if (link.object == 0)
				{
					return false;
				}
				if (arg != 0)
				{
					return true;
				}
				engine::GameObject* object = target.Get();
				if (object == 0)
				{
					return false;
				}
				ChargeAddMessage message(unknown2C * value, link.object->type);
				object->SendMessage(&message);
				return true;
			}

			// FUNCTION: ENGINE 0x100A10E0
			void AnimationChargeAction::Slot6()
			{
				engine::GameObject* object = target.Get();
				if (object != 0)
				{
					choreo::Puppet* puppet = engine::GetPuppet(object);
					if (puppet != 0)
					{
						puppet->RemoveDriver(driver, false);
						engine::ReleaseDriver(driver);
					}
				}
			}

			// FUNCTION: ENGINE 0x100A1C70
			bool AnimationChargeAction::Slot7(int arg, float value)
			{
				if (link.object == 0)
				{
					return false;
				}
				engine::GameObject* object = target.Get();
				if (object == 0)
				{
					return false;
				}
				ChargeGetMessage message(link.object->type);
				object->SendMessage(&message);
				float first = message.value;
				float second = (first >= 0.0f) ? first : 0.0f;
				float charge = (0.0f <= second - engine::driving::gOne) ? engine::driving::gOne : second;
				if (link.object->reverse)
				{
					charge = engine::driving::gOne - charge;
				}
				((choreo::AnimationDriver*)driver)->SetUnknownE4((link.object->endFrame - link.object->startFrame) * charge + link.object->startFrame);
				return true;
			}

			// FUNCTION: ENGINE 0x100A16A0
			bool ChargeSetAction::Slot5(int arg, float value)
			{
				if (link.object == 0)
				{
					return false;
				}
				engine::GameObject* object = target.Get();
				if (object == 0)
				{
					return false;
				}
				float charge = link.object->charge;
				int type = link.object->type;
				float range = link.object->randomRange;
				ChargeSetMessage message((fight::GetRandomValue(0) * 2.0f - engine::driving::gOne) * range + charge, type);
				object->SendMessage(&message);
				return false;
			}

			// FUNCTION: ENGINE 0x100A1810
			bool ChargeClearAction::Slot5(int arg, float value)
			{
				if (link.object != 0)
				{
					engine::GameObject* object = target.Get();
					if (object != 0)
					{
						if (link.object->clearOnBegin)
						{
							ChargeSetMessage message(0.0f, 0);
							object->SendMessage(&message);
							return false;
						}
						return true;
					}
				}
				return false;
			}

			// FUNCTION: ENGINE 0x100A18C0
			void ChargeClearAction::Slot6()
			{
				if (link.object != 0)
				{
					engine::GameObject* object = target.Get();
					if (object != 0 && !link.object->clearOnBegin)
					{
						ChargeSetMessage message(0.0f, 0);
						object->SendMessage(&message);
					}
				}
			}

			template class fight::PropertyEnumConstList<ChargeCondition>;
			template class fight::PropertyFloatConstRange<ChargeCondition>;
			template class fight::ConditionFactoryTemplate<ChargeCondition>;
			template class fight::ConditionFactoryCasterTemplate<ChargeCondition>;
			template class fight::PropertyFloatConstRange<ChargeTrack>;
			template class fight::PropertyEnumConstList<ChargeTrack>;
			template class fight::PropertyBool<ChargeTrack>;
			template class fight::TrackFactoryTemplate<ChargeTrack>;
			template class fight::TrackFactoryCasterTemplate<ChargeTrack>;
			template class fight::PropertyFloatConstRange<ChargeSetTrack>;
			template class fight::PropertyEnumConstList<ChargeSetTrack>;
			template class fight::TrackFactoryTemplate<ChargeSetTrack>;
			template class fight::TrackFactoryCasterTemplate<ChargeSetTrack>;
			template class fight::PropertyFloatConstRange<AnimationChargeTrack>;
			template class fight::PropertyName<AnimationChargeTrack>;
			template class fight::PropertyEnumConstList<AnimationChargeTrack>;
			template class fight::PropertyBool<AnimationChargeTrack>;
			template class fight::PropertyIntConstRange<AnimationChargeTrack>;
			template class fight::TrackFactoryTemplate<AnimationChargeTrack>;
			template class fight::TrackFactoryCasterTemplate<AnimationChargeTrack>;
			template class fight::PropertyFloatConstRange<ChargeClearTrack>;
			template class fight::PropertyBool<ChargeClearTrack>;
			template class fight::TrackFactoryTemplate<ChargeClearTrack>;
			template class fight::TrackFactoryCasterTemplate<ChargeClearTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x100A0BA0
// FUNCTION: ENGINE 0x100A0BE0
// FUNCTION: ENGINE 0x100A0C90
// FUNCTION: ENGINE 0x100A0CC0
// FUNCTION: ENGINE 0x100A0CE0
// FUNCTION: ENGINE 0x100A0D00
// FUNCTION: ENGINE 0x100A0D20
// FUNCTION: ENGINE 0x100A0D50
// FUNCTION: ENGINE 0x100A0DB0
// FUNCTION: ENGINE 0x100A0E10
// FUNCTION: ENGINE 0x100A0E70
// FUNCTION: ENGINE 0x100A1390
// FUNCTION: ENGINE 0x100A1670
// FUNCTION: ENGINE 0x100A17E0
// FUNCTION: ENGINE 0x100A19D0
