// The fight conditions and tracks of the ragdoll (unit 0x108F7400 - 0x108F93D0; no assert path, file name guessed).
#include "code/engine/fight/ragdoll.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/physics/ragdollmessages.h"
#include "code/ravenphysics/collision/collisionobject.h"
#include "code/ravenphysics/context.h"

namespace engine
{
	extern content::ObjectName gRagdollPhysicsObjectAttributeName;
	GameObjectHandle GetObjectHandle(core::IRefCount* object);
	extern fight::EnumEntry gPowerRagdollByAnimationTrackCyclicTable[];
	extern const int gPowerRagdollByAnimationTrackCyclicCount;

	fight::Property** gRagdollEnabledConditionProperties;  // 0x1131B2D0

	// FUNCTION: ENGINE 0x108F7400
	bool RagdollEnabledCondition::SetEnabled(bool newValue)
	{
		enabled = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F75E0
	fight::Property* RagdollEnabledCondition::GetProperty(int index)
	{
		return gRagdollEnabledConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x108F75F0
	void RagdollEnabledCondition::ClearProperties()
	{
		fight::FreePropertyList(&gRagdollEnabledConditionProperties);
	}

	// FUNCTION: ENGINE 0x108F7600
	RagdollEnabledCondition::RagdollEnabledCondition() : fight::Condition(0), enabled(true)
	{
	}

	// FUNCTION: ENGINE 0x1092E6F0
	bool RagdollEnabledCondition::Evaluate(int a, int b, int c, int d)
	{
		GameObject* object = GetObjectHandle((core::IRefCount*)c).Get();
		if (object == 0)
		{
			return false;
		}
		RagdollGetEnabledMessage message;
		object->PostMessage(&message);
		return message.enabled == enabled;
	}

	// FUNCTION: ENGINE 0x108F7620
	RagdollEnabledCondition::~RagdollEnabledCondition()
	{
	}

	// FUNCTION: ENGINE 0x108F84F0
	fight::ConditionFactory* CreateRagdollEnabledConditionFactory(const char* name)
	{
		fight::ConditionFactoryCasterTemplate<RagdollEnabledCondition> caster;
		return fight::FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108F8650
	// EQUIVALENT: the engine saves the registers it uses in the entry block, before the guard's branch; ours sinks the pushes behind the branch and leaves the early exit without the pops; every other instruction is the engine's
	void RagdollEnabledCondition::RegisterProperties()
	{
		if (gRagdollEnabledConditionProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyBool<RagdollEnabledCondition>("enabled", &RagdollEnabledCondition::SetEnabled);
			properties[0] = property;
			fight::RegisterPropertyList(properties, &gRagdollEnabledConditionProperties);
		}
	}

	// FUNCTION: ENGINE 0x108F8B20
	void RegisterRagdollEnabledConditionFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::ConditionFactoryCasterTemplate<RagdollEnabledCondition> caster;
		registry->AddFactory(fight::FindConditionFactory(name, &caster));
	}

	template class fight::PropertyBool<RagdollEnabledCondition>;
	template class fight::ConditionFactoryTemplate<RagdollEnabledCondition>;
	template class fight::ConditionFactoryCasterTemplate<RagdollEnabledCondition>;


	fight::Property** gRagdollPossibleConditionProperties;  // 0x1131B2D4

	// FUNCTION: ENGINE 0x108F7410
	bool RagdollPossibleCondition::SetRagdollAlreadyCreated(bool newValue)
	{
		ragdollAlreadyCreated = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F7420
	bool RagdollPossibleCondition::SetPossible(bool newValue)
	{
		possible = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F7630
	fight::Property* RagdollPossibleCondition::GetProperty(int index)
	{
		return gRagdollPossibleConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x108F7640
	void RagdollPossibleCondition::ClearProperties()
	{
		fight::FreePropertyList(&gRagdollPossibleConditionProperties);
	}

	// FUNCTION: ENGINE 0x108F7650
	RagdollPossibleCondition::RagdollPossibleCondition() : fight::Condition(0), possible(true), ragdollAlreadyCreated(true)
	{
	}

	// FUNCTION: ENGINE 0x1092E780
	// EQUIVALENT: register allocation; the engine reads the handle's two words through the attribute's pointer and returns the comparison in the register it was made in, ours copies the handle and moves the result through edx; the operations, branches and data accesses are the engine's
	bool RagdollPossibleCondition::Evaluate(int a, int b, int c, int d)
	{
		GameObject* object = GetObjectHandle((core::IRefCount*)c).Get();
		if (object == 0)
		{
			return false;
		}
		BaseAttribute* attribute = object->FindAttribute(gRagdollPhysicsObjectAttributeName);
		ravenphysics::ObjectHandle* value = attribute != 0 ? &((Attribute<ravenphysics::ObjectHandle>*)attribute)->value : 0;
		bool exists = value != 0;
		if (ragdollAlreadyCreated)
		{
			if (exists)
			{
				ravenphysics::ObjectHandle physicsHandle = *value;
				exists = physicsHandle.IsValid();
			}
		}
		return exists == possible;
	}

	// FUNCTION: ENGINE 0x108F7670
	RagdollPossibleCondition::~RagdollPossibleCondition()
	{
	}

	// FUNCTION: ENGINE 0x108F8510
	fight::ConditionFactory* CreateRagdollPossibleConditionFactory(const char* name)
	{
		fight::ConditionFactoryCasterTemplate<RagdollPossibleCondition> caster;
		return fight::FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108F86D0
	// EQUIVALENT: the engine saves the registers it uses in the entry block, before the guard's branch; ours sinks the pushes behind the branch and leaves the early exit without the pops; every other instruction is the engine's
	void RagdollPossibleCondition::RegisterProperties()
	{
		if (gRagdollPossibleConditionProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyBool<RagdollPossibleCondition>("ragdollAlreadyCreated", &RagdollPossibleCondition::SetRagdollAlreadyCreated);
			properties[0] = property;
			property = new fight::PropertyBool<RagdollPossibleCondition>("possible", &RagdollPossibleCondition::SetPossible);
			properties[1] = property;
			fight::RegisterPropertyList(properties, &gRagdollPossibleConditionProperties);
		}
	}

	// FUNCTION: ENGINE 0x108F8B50
	void RegisterRagdollPossibleConditionFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::ConditionFactoryCasterTemplate<RagdollPossibleCondition> caster;
		registry->AddFactory(fight::FindConditionFactory(name, &caster));
	}

	template class fight::PropertyBool<RagdollPossibleCondition>;
	template class fight::ConditionFactoryTemplate<RagdollPossibleCondition>;
	template class fight::ConditionFactoryCasterTemplate<RagdollPossibleCondition>;


	fight::Property** gRagdollSetKeyframeUpdatedTrackProperties;  // 0x1131B2D8

	// FUNCTION: ENGINE 0x108F7430
	bool RagdollSetKeyframeUpdatedTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F7440
	bool RagdollSetKeyframeUpdatedTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F7450
	bool RagdollSetKeyframeUpdatedTrack::SetKeyframeUpdated(bool newValue)
	{
		keyframeUpdated = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F7680
	fight::Property* RagdollSetKeyframeUpdatedTrack::GetProperty(int index)
	{
		return gRagdollSetKeyframeUpdatedTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108F7690
	void RagdollSetKeyframeUpdatedTrack::ClearProperties()
	{
		fight::FreePropertyList(&gRagdollSetKeyframeUpdatedTrackProperties);
	}

	// FUNCTION: ENGINE 0x108F76A0
	RagdollSetKeyframeUpdatedTrack::RagdollSetKeyframeUpdatedTrack() : timeBegin(0.0f), timeEnd(-1.0f), keyframeUpdated(true)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x108F76E0
	float RagdollSetKeyframeUpdatedTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108F76F0
	float RagdollSetKeyframeUpdatedTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x108F7700
	RagdollSetKeyframeUpdatedTrack::~RagdollSetKeyframeUpdatedTrack()
	{
	}

	// FUNCTION: ENGINE 0x108F8530
	fight::TrackFactory* CreateRagdollSetKeyframeUpdatedTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<RagdollSetKeyframeUpdatedTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108F8780
	// EQUIVALENT: the engine saves the registers it uses in the entry block, before the guard's branch; ours sinks the pushes behind the branch and leaves the early exit without the pops; every other instruction is the engine's
	void RagdollSetKeyframeUpdatedTrack::RegisterProperties()
	{
		if (gRagdollSetKeyframeUpdatedTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<RagdollSetKeyframeUpdatedTrack>("timeBegin", &RagdollSetKeyframeUpdatedTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<RagdollSetKeyframeUpdatedTrack>("timeEnd", &RagdollSetKeyframeUpdatedTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyBool<RagdollSetKeyframeUpdatedTrack>("keyframeUpdated", &RagdollSetKeyframeUpdatedTrack::SetKeyframeUpdated);
			properties[2] = property;
			fight::RegisterPropertyList(properties, &gRagdollSetKeyframeUpdatedTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108F8B80
	void RegisterRagdollSetKeyframeUpdatedTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<RagdollSetKeyframeUpdatedTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyBool<RagdollSetKeyframeUpdatedTrack>;
	template class fight::PropertyFloatConstRange<RagdollSetKeyframeUpdatedTrack>;
	template class fight::TrackFactoryTemplate<RagdollSetKeyframeUpdatedTrack>;
	template class fight::TrackFactoryCasterTemplate<RagdollSetKeyframeUpdatedTrack>;


	fight::Property** gDeactivateRagdollTrackProperties;  // 0x1131B2DC

	// FUNCTION: ENGINE 0x108F7460
	bool DeactivateRagdollTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F7470
	bool DeactivateRagdollTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F7710
	fight::Property* DeactivateRagdollTrack::GetProperty(int index)
	{
		return gDeactivateRagdollTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108F7720
	void DeactivateRagdollTrack::ClearProperties()
	{
		fight::FreePropertyList(&gDeactivateRagdollTrackProperties);
	}

	// FUNCTION: ENGINE 0x108F7730
	DeactivateRagdollTrack::DeactivateRagdollTrack() : timeBegin(0.0f), timeEnd(-1.0f)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x108F7760
	float DeactivateRagdollTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108F7770
	float DeactivateRagdollTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x108F7780
	DeactivateRagdollTrack::~DeactivateRagdollTrack()
	{
	}

	// FUNCTION: ENGINE 0x108F8550
	fight::TrackFactory* CreateDeactivateRagdollTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<DeactivateRagdollTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108F8860
	// EQUIVALENT: the engine saves the registers it uses in the entry block, before the guard's branch; ours sinks the pushes behind the branch and leaves the early exit without the pops; every other instruction is the engine's
	void DeactivateRagdollTrack::RegisterProperties()
	{
		if (gDeactivateRagdollTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<DeactivateRagdollTrack>("timeBegin", &DeactivateRagdollTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<DeactivateRagdollTrack>("timeEnd", &DeactivateRagdollTrack::SetTimeEnd);
			properties[1] = property;
			fight::RegisterPropertyList(properties, &gDeactivateRagdollTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108F8BB0
	void RegisterDeactivateRagdollTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<DeactivateRagdollTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyFloatConstRange<DeactivateRagdollTrack>;
	template class fight::TrackFactoryTemplate<DeactivateRagdollTrack>;
	template class fight::TrackFactoryCasterTemplate<DeactivateRagdollTrack>;


	fight::Property** gRagdollStoreJointVelocitiesTrackProperties;  // 0x1131B2E4

	// FUNCTION: ENGINE 0x108F7490
	bool RagdollStoreJointVelocitiesTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F74A0
	bool RagdollStoreJointVelocitiesTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F77B0
	fight::Property* RagdollStoreJointVelocitiesTrack::GetProperty(int index)
	{
		return gRagdollStoreJointVelocitiesTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108F77C0
	void RagdollStoreJointVelocitiesTrack::ClearProperties()
	{
		fight::FreePropertyList(&gRagdollStoreJointVelocitiesTrackProperties);
	}

	// FUNCTION: ENGINE 0x108F77D0
	RagdollStoreJointVelocitiesTrack::RagdollStoreJointVelocitiesTrack() : timeBegin(0.0f), timeEnd(-1.0f)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x108F7800
	float RagdollStoreJointVelocitiesTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108F7810
	float RagdollStoreJointVelocitiesTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x108F7820
	RagdollStoreJointVelocitiesTrack::~RagdollStoreJointVelocitiesTrack()
	{
	}

	// FUNCTION: ENGINE 0x108F8590
	fight::TrackFactory* CreateRagdollStoreJointVelocitiesTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<RagdollStoreJointVelocitiesTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108F8910
	// EQUIVALENT: the engine saves the registers it uses in the entry block, before the guard's branch; ours sinks the pushes behind the branch and leaves the early exit without the pops; every other instruction is the engine's
	void RagdollStoreJointVelocitiesTrack::RegisterProperties()
	{
		if (gRagdollStoreJointVelocitiesTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<RagdollStoreJointVelocitiesTrack>("timeBegin", &RagdollStoreJointVelocitiesTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<RagdollStoreJointVelocitiesTrack>("timeEnd", &RagdollStoreJointVelocitiesTrack::SetTimeEnd);
			properties[1] = property;
			fight::RegisterPropertyList(properties, &gRagdollStoreJointVelocitiesTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108F8C10
	void RegisterRagdollStoreJointVelocitiesTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<RagdollStoreJointVelocitiesTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyFloatConstRange<RagdollStoreJointVelocitiesTrack>;
	template class fight::TrackFactoryTemplate<RagdollStoreJointVelocitiesTrack>;
	template class fight::TrackFactoryCasterTemplate<RagdollStoreJointVelocitiesTrack>;


	fight::Property** gUnpowerRagdollTrackProperties;  // 0x1131B2EC

	// FUNCTION: ENGINE 0x108F74D0
	bool UnpowerRagdollTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F7850
	fight::Property* UnpowerRagdollTrack::GetProperty(int index)
	{
		return gUnpowerRagdollTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108F7860
	void UnpowerRagdollTrack::ClearProperties()
	{
		fight::FreePropertyList(&gUnpowerRagdollTrackProperties);
	}

	// FUNCTION: ENGINE 0x108F7870
	UnpowerRagdollTrack::UnpowerRagdollTrack() : timeBegin(0.0f)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x108F78A0
	float UnpowerRagdollTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108F78B0
	float UnpowerRagdollTrack::Slot10() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x108F78C0
	UnpowerRagdollTrack::~UnpowerRagdollTrack()
	{
	}

	// FUNCTION: ENGINE 0x108F85D0
	fight::TrackFactory* CreateUnpowerRagdollTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<UnpowerRagdollTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108F89C0
	// EQUIVALENT: the engine saves the registers it uses in the entry block, before the guard's branch; ours sinks the pushes behind the branch and leaves the early exit without the pops; every other instruction is the engine's
	void UnpowerRagdollTrack::RegisterProperties()
	{
		if (gUnpowerRagdollTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<UnpowerRagdollTrack>("timeBegin", &UnpowerRagdollTrack::SetTimeBegin);
			properties[0] = property;
			fight::RegisterPropertyList(properties, &gUnpowerRagdollTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108F8C70
	void RegisterUnpowerRagdollTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<UnpowerRagdollTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyFloatConstRange<UnpowerRagdollTrack>;
	template class fight::TrackFactoryTemplate<UnpowerRagdollTrack>;
	template class fight::TrackFactoryCasterTemplate<UnpowerRagdollTrack>;


	fight::Property** gDisableRagdollTrackProperties;  // 0x1131B2F4

	// FUNCTION: ENGINE 0x108F7540
	bool DisableRagdollTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F7550
	bool DisableRagdollTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F7560
	bool DisableRagdollTrack::SetPhysicsBlendTime(float newValue)
	{
		physicsBlendTime = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F78F0
	fight::Property* DisableRagdollTrack::GetProperty(int index)
	{
		return gDisableRagdollTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108F7900
	void DisableRagdollTrack::ClearProperties()
	{
		fight::FreePropertyList(&gDisableRagdollTrackProperties);
	}

	// FUNCTION: ENGINE 0x108F7910
	DisableRagdollTrack::DisableRagdollTrack() : physicsBlendTime(0.0f), timeBegin(0.0f), timeEnd(-1.0f)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x108F7950
	float DisableRagdollTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108F7960
	float DisableRagdollTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x108F7970
	DisableRagdollTrack::~DisableRagdollTrack()
	{
	}

	// FUNCTION: ENGINE 0x108F8610
	fight::TrackFactory* CreateDisableRagdollTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<DisableRagdollTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108F8A40
	// EQUIVALENT: the engine saves the registers it uses in the entry block, before the guard's branch; ours sinks the pushes behind the branch and leaves the early exit without the pops; every other instruction is the engine's
	void DisableRagdollTrack::RegisterProperties()
	{
		if (gDisableRagdollTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<DisableRagdollTrack>("timeBegin", &DisableRagdollTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<DisableRagdollTrack>("timeEnd", &DisableRagdollTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyFloatConstRange<DisableRagdollTrack>("physicsBlendTime", &DisableRagdollTrack::SetPhysicsBlendTime);
			properties[2] = property;
			fight::RegisterPropertyList(properties, &gDisableRagdollTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108F8CD0
	void RegisterDisableRagdollTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<DisableRagdollTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyFloatConstRange<DisableRagdollTrack>;
	template class fight::TrackFactoryTemplate<DisableRagdollTrack>;
	template class fight::TrackFactoryCasterTemplate<DisableRagdollTrack>;


	fight::Property** gPowerRagdollByPuppetTrackProperties;  // 0x1131B2E0

	// FUNCTION: ENGINE 0x108F7480
	bool PowerRagdollByPuppetTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F7790
	fight::Property* PowerRagdollByPuppetTrack::GetProperty(int index)
	{
		return gPowerRagdollByPuppetTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108F77A0
	void PowerRagdollByPuppetTrack::ClearProperties()
	{
		fight::FreePropertyList(&gPowerRagdollByPuppetTrackProperties);
	}

	// FUNCTION: ENGINE 0x108F79A0
	bool PowerRagdollByPuppetTrack::SetConstraintPropertiesName(const fight::Name& newValue)
	{
		constraintPropertiesName = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F7AE0
	PowerRagdollByPuppetTrack::PowerRagdollByPuppetTrack() : timeBegin(0.0f)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x108F7B10
	float PowerRagdollByPuppetTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108F7B20
	float PowerRagdollByPuppetTrack::Slot10() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x108F7B30
	PowerRagdollByPuppetTrack::~PowerRagdollByPuppetTrack()
	{
	}

	// FUNCTION: ENGINE 0x108F8570
	fight::TrackFactory* CreatePowerRagdollByPuppetTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<PowerRagdollByPuppetTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108F8BE0
	void RegisterPowerRagdollByPuppetTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<PowerRagdollByPuppetTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	// FUNCTION: ENGINE 0x108F9070
	// EQUIVALENT: the engine saves the registers it uses in the entry block, before the guard's branch; ours sinks the pushes behind the branch and leaves the early exit without the pops; every other instruction is the engine's
	void PowerRagdollByPuppetTrack::RegisterProperties()
	{
		if (gPowerRagdollByPuppetTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<PowerRagdollByPuppetTrack>("timeBegin", &PowerRagdollByPuppetTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyName<PowerRagdollByPuppetTrack>("constraintPropertiesName", &PowerRagdollByPuppetTrack::SetConstraintPropertiesName);
			properties[1] = property;
			fight::RegisterPropertyList(properties, &gPowerRagdollByPuppetTrackProperties);
		}
	}

	template class fight::PropertyFloatConstRange<PowerRagdollByPuppetTrack>;
	template class fight::PropertyName<PowerRagdollByPuppetTrack>;
	template class fight::TrackFactoryTemplate<PowerRagdollByPuppetTrack>;
	template class fight::TrackFactoryCasterTemplate<PowerRagdollByPuppetTrack>;


	fight::Property** gPowerRagdollByPoseTrackProperties;  // 0x1131B2E8

	// FUNCTION: ENGINE 0x108F74B0
	bool PowerRagdollByPoseTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F74C0
	bool PowerRagdollByPoseTrack::SetAnimFrame(float newValue)
	{
		animFrame = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F7830
	fight::Property* PowerRagdollByPoseTrack::GetProperty(int index)
	{
		return gPowerRagdollByPoseTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108F7840
	void PowerRagdollByPoseTrack::ClearProperties()
	{
		fight::FreePropertyList(&gPowerRagdollByPoseTrackProperties);
	}

	// FUNCTION: ENGINE 0x108F79C0
	bool PowerRagdollByPoseTrack::SetPoseAnimName(const fight::Name& newValue)
	{
		poseAnimName = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F79E0
	bool PowerRagdollByPoseTrack::SetConstraintPropertiesName(const fight::Name& newValue)
	{
		constraintPropertiesName = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F7B60
	PowerRagdollByPoseTrack::PowerRagdollByPoseTrack() : animFrame(0.0f), timeBegin(0.0f)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x108F7BA0
	float PowerRagdollByPoseTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108F7BB0
	float PowerRagdollByPoseTrack::Slot10() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x108F7BC0
	PowerRagdollByPoseTrack::~PowerRagdollByPoseTrack()
	{
	}

	// FUNCTION: ENGINE 0x108F85B0
	fight::TrackFactory* CreatePowerRagdollByPoseTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<PowerRagdollByPoseTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108F8C40
	void RegisterPowerRagdollByPoseTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<PowerRagdollByPoseTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	// FUNCTION: ENGINE 0x108F9120
	// EQUIVALENT: the engine saves the registers it uses in the entry block, before the guard's branch; ours sinks the pushes behind the branch and leaves the early exit without the pops; every other instruction is the engine's
	void PowerRagdollByPoseTrack::RegisterProperties()
	{
		if (gPowerRagdollByPoseTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<PowerRagdollByPoseTrack>("timeBegin", &PowerRagdollByPoseTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyName<PowerRagdollByPoseTrack>("poseAnimName", &PowerRagdollByPoseTrack::SetPoseAnimName);
			properties[1] = property;
			property = new fight::PropertyFloatConstRange<PowerRagdollByPoseTrack>("animFrame", &PowerRagdollByPoseTrack::SetAnimFrame);
			properties[2] = property;
			property = new fight::PropertyName<PowerRagdollByPoseTrack>("constraintPropertiesName", &PowerRagdollByPoseTrack::SetConstraintPropertiesName);
			properties[3] = property;
			fight::RegisterPropertyList(properties, &gPowerRagdollByPoseTrackProperties);
		}
	}

	template class fight::PropertyFloatConstRange<PowerRagdollByPoseTrack>;
	template class fight::PropertyName<PowerRagdollByPoseTrack>;
	template class fight::TrackFactoryTemplate<PowerRagdollByPoseTrack>;
	template class fight::TrackFactoryCasterTemplate<PowerRagdollByPoseTrack>;


	fight::Property** gEnableRagdollTrackProperties;  // 0x1131B2F0

	// FUNCTION: ENGINE 0x108F74E0
	bool EnableRagdollTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F74F0
	bool EnableRagdollTrack::SetDisableSupportingLimb(bool newValue)
	{
		disableSupportingLimb = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F7500
	bool EnableRagdollTrack::SetInheritJointVelocities(bool newValue)
	{
		inheritJointVelocities = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F7510
	bool EnableRagdollTrack::SetUseNormalPhysicsObjectAsRagdoll(bool newValue)
	{
		useNormalPhysicsObjectAsRagdoll = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F7520
	bool EnableRagdollTrack::SetPhysicsTransitionDuration(float newValue)
	{
		physicsTransitionDuration = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F7530
	bool EnableRagdollTrack::SetIncludeRootJoint(bool newValue)
	{
		includeRootJoint = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F78D0
	fight::Property* EnableRagdollTrack::GetProperty(int index)
	{
		return gEnableRagdollTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108F78E0
	void EnableRagdollTrack::ClearProperties()
	{
		fight::FreePropertyList(&gEnableRagdollTrackProperties);
	}

	// FUNCTION: ENGINE 0x108F7A00
	bool EnableRagdollTrack::SetRootJoint(const fight::Name& newValue)
	{
		rootJoint = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F7BF0
	EnableRagdollTrack::EnableRagdollTrack() : physicsTransitionDuration(0.0f), timeBegin(0.0f), disableSupportingLimb(true), includeRootJoint(true), inheritJointVelocities(true), useNormalPhysicsObjectAsRagdoll(false)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x108F7C30
	float EnableRagdollTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108F7C40
	float EnableRagdollTrack::Slot10() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x108F7C50
	EnableRagdollTrack::~EnableRagdollTrack()
	{
	}

	// FUNCTION: ENGINE 0x108F85F0
	fight::TrackFactory* CreateEnableRagdollTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<EnableRagdollTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108F8CA0
	void RegisterEnableRagdollTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<EnableRagdollTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	// FUNCTION: ENGINE 0x108F9230
	// EQUIVALENT: the engine saves the registers it uses in the entry block, before the guard's branch; ours sinks the pushes behind the branch and leaves the early exit without the pops; every other instruction is the engine's
	void EnableRagdollTrack::RegisterProperties()
	{
		if (gEnableRagdollTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<EnableRagdollTrack>("timeBegin", &EnableRagdollTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyBool<EnableRagdollTrack>("disableSupportingLimb", &EnableRagdollTrack::SetDisableSupportingLimb);
			properties[1] = property;
			property = new fight::PropertyBool<EnableRagdollTrack>("inheritJointVelocities", &EnableRagdollTrack::SetInheritJointVelocities);
			properties[2] = property;
			property = new fight::PropertyBool<EnableRagdollTrack>("useNormalPhysicsObjectAsRagdoll", &EnableRagdollTrack::SetUseNormalPhysicsObjectAsRagdoll);
			properties[3] = property;
			property = new fight::PropertyFloatConstRange<EnableRagdollTrack>("physicsTransitionDuration", &EnableRagdollTrack::SetPhysicsTransitionDuration);
			properties[4] = property;
			property = new fight::PropertyNameList<EnableRagdollTrack>("rootJoint", &EnableRagdollTrack::SetRootJoint);
			properties[5] = property;
			property = new fight::PropertyBool<EnableRagdollTrack>("includeRootJoint", &EnableRagdollTrack::SetIncludeRootJoint);
			properties[6] = property;
			fight::RegisterPropertyList(properties, &gEnableRagdollTrackProperties);
		}
	}

	template class fight::PropertyBool<EnableRagdollTrack>;
	template class fight::PropertyFloatConstRange<EnableRagdollTrack>;
	template class fight::PropertyNameList<EnableRagdollTrack>;
	template class fight::TrackFactoryTemplate<EnableRagdollTrack>;
	template class fight::TrackFactoryCasterTemplate<EnableRagdollTrack>;


	fight::Property** gPowerRagdollByAnimationTrackProperties;  // 0x1131B2F8

	// FUNCTION: ENGINE 0x108F7570
	bool PowerRagdollByAnimationTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F7580
	bool PowerRagdollByAnimationTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F7590
	bool PowerRagdollByAnimationTrack::SetSpeed(float newValue)
	{
		speed = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F75A0
	bool PowerRagdollByAnimationTrack::SetInitFrame(float newValue)
	{
		initFrame = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F75B0
	bool PowerRagdollByAnimationTrack::SetStartFrame(float newValue)
	{
		startFrame = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F75C0
	bool PowerRagdollByAnimationTrack::SetEndFrame(float newValue)
	{
		endFrame = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F75D0
	bool PowerRagdollByAnimationTrack::SetCyclic(int newValue)
	{
		cyclic = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F7980
	fight::Property* PowerRagdollByAnimationTrack::GetProperty(int index)
	{
		return gPowerRagdollByAnimationTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108F7990
	void PowerRagdollByAnimationTrack::ClearProperties()
	{
		fight::FreePropertyList(&gPowerRagdollByAnimationTrackProperties);
	}

	// FUNCTION: ENGINE 0x108F7A20
	bool PowerRagdollByAnimationTrack::SetAnimation(const fight::Name& newValue)
	{
		animation = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F7A40
	bool PowerRagdollByAnimationTrack::SetConstraintPropertiesName(const fight::Name& newValue)
	{
		constraintPropertiesName = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F7C80
	PowerRagdollByAnimationTrack::PowerRagdollByAnimationTrack() : endFrame(-1.0f), initFrame(0.0f), speed(1.0f), startFrame(0.0f), timeBegin(0.0f), timeEnd(-1.0f), cyclic(0)
	{
	}

	// FUNCTION: ENGINE 0x108F7CE0
	float PowerRagdollByAnimationTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108F7CF0
	float PowerRagdollByAnimationTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x108F7D00
	PowerRagdollByAnimationTrack::~PowerRagdollByAnimationTrack()
	{
	}

	// FUNCTION: ENGINE 0x108F8630
	fight::TrackFactory* CreatePowerRagdollByAnimationTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<PowerRagdollByAnimationTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108F8D00
	void RegisterPowerRagdollByAnimationTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<PowerRagdollByAnimationTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	// FUNCTION: ENGINE 0x108F93D0
	// EQUIVALENT: the engine saves the registers it uses in the entry block, before the guard's branch; ours sinks the pushes behind the branch and leaves the early exit without the pops; every other instruction is the engine's
	void PowerRagdollByAnimationTrack::RegisterProperties()
	{
		if (gPowerRagdollByAnimationTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<PowerRagdollByAnimationTrack>("timeBegin", &PowerRagdollByAnimationTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<PowerRagdollByAnimationTrack>("timeEnd", &PowerRagdollByAnimationTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyName<PowerRagdollByAnimationTrack>("animation", &PowerRagdollByAnimationTrack::SetAnimation);
			properties[2] = property;
			property = new fight::PropertyFloatConstRange<PowerRagdollByAnimationTrack>("speed", &PowerRagdollByAnimationTrack::SetSpeed);
			properties[3] = property;
			property = new fight::PropertyFloatConstRange<PowerRagdollByAnimationTrack>("initFrame", &PowerRagdollByAnimationTrack::SetInitFrame);
			properties[4] = property;
			property = new fight::PropertyFloatConstRange<PowerRagdollByAnimationTrack>("startFrame", &PowerRagdollByAnimationTrack::SetStartFrame);
			properties[5] = property;
			property = new fight::PropertyFloatConstRange<PowerRagdollByAnimationTrack>("endFrame", &PowerRagdollByAnimationTrack::SetEndFrame);
			properties[6] = property;
			property = new fight::PropertyEnumConstList<PowerRagdollByAnimationTrack>("cyclic", gPowerRagdollByAnimationTrackCyclicTable, gPowerRagdollByAnimationTrackCyclicCount, &PowerRagdollByAnimationTrack::SetCyclic);
			properties[7] = property;
			property = new fight::PropertyName<PowerRagdollByAnimationTrack>("constraintPropertiesName", &PowerRagdollByAnimationTrack::SetConstraintPropertiesName);
			properties[8] = property;
			fight::RegisterPropertyList(properties, &gPowerRagdollByAnimationTrackProperties);
		}
	}

	template class fight::PropertyEnumConstList<PowerRagdollByAnimationTrack>;
	template class fight::PropertyFloatConstRange<PowerRagdollByAnimationTrack>;
	template class fight::PropertyName<PowerRagdollByAnimationTrack>;
	template class fight::TrackFactoryTemplate<PowerRagdollByAnimationTrack>;
	template class fight::TrackFactoryCasterTemplate<PowerRagdollByAnimationTrack>;

	// FUNCTION: ENGINE 0x1092DED0
	bool RagdollPossibleCondition::GetPossible() const
	{
		return possible;
	}

	// FUNCTION: ENGINE 0x1092DEE0
	bool RagdollPossibleCondition::GetRagdollAlreadyCreated() const
	{
		return ragdollAlreadyCreated;
	}

	// FUNCTION: ENGINE 0x1092DEF0
	bool RagdollEnabledCondition::GetEnabled() const
	{
		return enabled;
	}

	// FUNCTION: ENGINE 0x1092DF00
	bool RagdollSetKeyframeUpdatedTrack::GetKeyframeUpdated() const
	{
		return keyframeUpdated;
	}

	// FUNCTION: ENGINE 0x1092DF10
	const fight::Name* PowerRagdollByPoseTrack::GetConstraintPropertiesName() const
	{
		return &constraintPropertiesName;
	}

	// FUNCTION: ENGINE 0x1092DF20
	const fight::Name* PowerRagdollByPoseTrack::GetPoseAnimName() const
	{
		return &poseAnimName;
	}

	// FUNCTION: ENGINE 0x1092DF30
	float PowerRagdollByPoseTrack::GetAnimFrame() const
	{
		return animFrame;
	}

	// FUNCTION: ENGINE 0x1092DF40
	const fight::Name* PowerRagdollByPuppetTrack::GetConstraintPropertiesName() const
	{
		return &constraintPropertiesName;
	}

	// FUNCTION: ENGINE 0x1092DF50
	bool EnableRagdollTrack::GetDisableSupportingLimb() const
	{
		return disableSupportingLimb;
	}

	// FUNCTION: ENGINE 0x1092DF60
	bool EnableRagdollTrack::GetInheritJointVelocities() const
	{
		return inheritJointVelocities;
	}

	// FUNCTION: ENGINE 0x1092DF70
	bool EnableRagdollTrack::GetUseNormalPhysicsObjectAsRagdoll() const
	{
		return useNormalPhysicsObjectAsRagdoll;
	}

	// FUNCTION: ENGINE 0x1092DF80
	float EnableRagdollTrack::GetPhysicsTransitionDuration() const
	{
		return physicsTransitionDuration;
	}

	// FUNCTION: ENGINE 0x1092DF90
	const fight::Name* EnableRagdollTrack::GetRootJoint() const
	{
		return &rootJoint;
	}

	// FUNCTION: ENGINE 0x1092DFA0
	bool EnableRagdollTrack::GetIncludeRootJoint() const
	{
		return includeRootJoint;
	}

	// FUNCTION: ENGINE 0x1092DFB0
	float DisableRagdollTrack::GetPhysicsBlendTime() const
	{
		return physicsBlendTime;
	}

	// FUNCTION: ENGINE 0x1092DFC0
	const fight::Name* PowerRagdollByAnimationTrack::GetAnimation() const
	{
		return &animation;
	}

	// FUNCTION: ENGINE 0x1092DFD0
	float PowerRagdollByAnimationTrack::GetSpeed() const
	{
		return speed;
	}

	// FUNCTION: ENGINE 0x1092DFE0
	float PowerRagdollByAnimationTrack::GetInitFrame() const
	{
		return initFrame;
	}

	// FUNCTION: ENGINE 0x1092DFF0
	float PowerRagdollByAnimationTrack::GetStartFrame() const
	{
		return startFrame;
	}

	// FUNCTION: ENGINE 0x1092E000
	float PowerRagdollByAnimationTrack::GetEndFrame() const
	{
		return endFrame;
	}

	// FUNCTION: ENGINE 0x1092E010
	int PowerRagdollByAnimationTrack::GetCyclic() const
	{
		return cyclic;
	}

	// FUNCTION: ENGINE 0x1092E020
	const fight::Name* PowerRagdollByAnimationTrack::GetConstraintPropertiesName() const
	{
		return &constraintPropertiesName;
	}
}
