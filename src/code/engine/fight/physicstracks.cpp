// The fight tracks that switch physics and collision on objects (unit 0x1080F070 - 0x10810E00).
#include "code/engine/fight/physicstracks.h"

namespace engine
{
	fight::Property** gPhysicsSetKeyframedTrackProperties;  // 0x11284B84

	// FUNCTION: ENGINE 0x1080F220
	bool PhysicsSetKeyframedTrack::SetTimeBegin(float value)
	{
		timeBegin = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1080F230
	bool PhysicsSetKeyframedTrack::SetKeyframed(bool value)
	{
		keyframed = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1080F390
	fight::Property* PhysicsSetKeyframedTrack::GetProperty(int index)
	{
		return gPhysicsSetKeyframedTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x1080F3A0
	void PhysicsSetKeyframedTrack::ClearProperties()
	{
		fight::FreePropertyList(&gPhysicsSetKeyframedTrackProperties);
	}

	// FUNCTION: ENGINE 0x1080F3B0
	// ctor stores: [('mov', 'byte', 20, '1'), ('mov', 'dword', 12, '1'), ('mov', 'dword', 0, '0x10e6c364'), ('movss', 'dword', 16, '0.0f')]
	PhysicsSetKeyframedTrack::PhysicsSetKeyframedTrack() : keyframed(1), timeBegin(0.0f)
	{
		unknownC = 1;  // TODO base member
	}

	// FUNCTION: ENGINE 0x1080F3E0
	float PhysicsSetKeyframedTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x1080F3F0
	float PhysicsSetKeyframedTrack::Slot10() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x1080F400
	PhysicsSetKeyframedTrack::~PhysicsSetKeyframedTrack()
	{
	}

	// FUNCTION: ENGINE 0x10810040
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void PhysicsSetKeyframedTrack::RegisterProperties()
	{
		if (gPhysicsSetKeyframedTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<PhysicsSetKeyframedTrack>("timeBegin", &PhysicsSetKeyframedTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyBool<PhysicsSetKeyframedTrack>("keyframed", &PhysicsSetKeyframedTrack::SetKeyframed);
			properties[1] = property;
			fight::RegisterPropertyList(properties, &gPhysicsSetKeyframedTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x1080FF60
	fight::TrackFactory* CreatePhysicsSetKeyframedTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<PhysicsSetKeyframedTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108103B0
	void RegisterPhysicsSetKeyframedTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<PhysicsSetKeyframedTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyBool<PhysicsSetKeyframedTrack>;
	template class fight::PropertyFloatConstRange<PhysicsSetKeyframedTrack>;
	template class fight::TrackFactoryTemplate<PhysicsSetKeyframedTrack>;
	template class fight::TrackFactoryCasterTemplate<PhysicsSetKeyframedTrack>;

	fight::EnumEntry gPhysicsActionOnBeginTable[3] =
		{
			{ fight::Name("Do nothing", 0) },
			{ fight::Name("Enable physics", 0) },
			{ fight::Name("Disable physics", 0) }
		};
	extern const int gPhysicsActionOnBeginCount;
	fight::EnumEntry gPhysicsActionOnEndTable[4] =
		{
			{ fight::Name("Do nothing", 0) },
			{ fight::Name("Restore to previous", 0) },
			{ fight::Name("Enable physics", 0) },
			{ fight::Name("Disable physics", 0) }
		};
	extern const int gPhysicsActionOnEndCount;

	fight::Property** gPhysicsEnableTrackProperties;  // 0x11284B88

	// FUNCTION: ENGINE 0x1080F240
	bool PhysicsEnableTrack::SetTimeBegin(float value)
	{
		timeBegin = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1080F250
	bool PhysicsEnableTrack::SetTimeEnd(float value)
	{
		timeEnd = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1080F260
	bool PhysicsEnableTrack::SetActionOnBegin(int value)
	{
		actionOnBegin = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1080F270
	bool PhysicsEnableTrack::SetActionOnEnd(int value)
	{
		actionOnEnd = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1080F410
	fight::Property* PhysicsEnableTrack::GetProperty(int index)
	{
		return gPhysicsEnableTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x1080F420
	void PhysicsEnableTrack::ClearProperties()
	{
		fight::FreePropertyList(&gPhysicsEnableTrackProperties);
	}

	// FUNCTION: ENGINE 0x1080F430
	// ctor stores: [('mov', 'dword', 24, '0'), ('mov', 'dword', 28, '0'), ('mov', 'dword', 0, '0x10e6c3ac'), ('movss', 'dword', 16, '0.0f'), ('movss', 'dword', 20, '0.0f'), ('mov', 'dword', 12, '1')]
	PhysicsEnableTrack::PhysicsEnableTrack() : actionOnBegin(0), actionOnEnd(0), timeBegin(0.0f), timeEnd(0.0f)
	{
		unknownC = 1;  // TODO base member
	}

	// FUNCTION: ENGINE 0x1080F460
	float PhysicsEnableTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x1080F470
	float PhysicsEnableTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x1080F480
	PhysicsEnableTrack::~PhysicsEnableTrack()
	{
	}

	// FUNCTION: ENGINE 0x108100F0
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void PhysicsEnableTrack::RegisterProperties()
	{
		if (gPhysicsEnableTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<PhysicsEnableTrack>("timeBegin", &PhysicsEnableTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<PhysicsEnableTrack>("timeEnd", &PhysicsEnableTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyEnumConstList<PhysicsEnableTrack>("actionOnBegin", gPhysicsActionOnBeginTable, gPhysicsActionOnBeginCount, &PhysicsEnableTrack::SetActionOnBegin);
			properties[2] = property;
			property = new fight::PropertyEnumConstList<PhysicsEnableTrack>("actionOnEnd", gPhysicsActionOnEndTable, gPhysicsActionOnEndCount, &PhysicsEnableTrack::SetActionOnEnd);
			properties[3] = property;
			fight::RegisterPropertyList(properties, &gPhysicsEnableTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x1080FF80
	fight::TrackFactory* CreatePhysicsEnableTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<PhysicsEnableTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108103E0
	void RegisterPhysicsEnableTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<PhysicsEnableTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyEnumConstList<PhysicsEnableTrack>;
	template class fight::PropertyFloatConstRange<PhysicsEnableTrack>;
	template class fight::TrackFactoryTemplate<PhysicsEnableTrack>;
	template class fight::TrackFactoryCasterTemplate<PhysicsEnableTrack>;

	fight::Property** gPhysicsDisallowSleepingTrackProperties;  // 0x11284B94

	// FUNCTION: ENGINE 0x1080F300
	bool PhysicsDisallowSleepingTrack::SetTimeBegin(float value)
	{
		timeBegin = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1080F310
	bool PhysicsDisallowSleepingTrack::SetTimeEnd(float value)
	{
		timeEnd = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1080F320
	bool PhysicsDisallowSleepingTrack::SetKeepPhysicsObjectAwake(bool value)
	{
		keepPhysicsObjectAwake = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1080F4D0
	fight::Property* PhysicsDisallowSleepingTrack::GetProperty(int index)
	{
		return gPhysicsDisallowSleepingTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x1080F4E0
	void PhysicsDisallowSleepingTrack::ClearProperties()
	{
		fight::FreePropertyList(&gPhysicsDisallowSleepingTrackProperties);
	}

	// FUNCTION: ENGINE 0x1080F4F0
	// ctor stores: [('movss', 'dword', 16, '0.0f'), ('mov', 'byte', 24, '1'), ('mov', 'dword', 12, '1'), ('mov', 'dword', 0, '0x10e6c3f4'), ('movss', 'dword', 20, '-1.0f')]
	PhysicsDisallowSleepingTrack::PhysicsDisallowSleepingTrack() : timeBegin(0.0f), keepPhysicsObjectAwake(1), timeEnd(-1.0f)
	{
		unknownC = 1;  // TODO base member
	}

	// FUNCTION: ENGINE 0x1080F530
	float PhysicsDisallowSleepingTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x1080F540
	float PhysicsDisallowSleepingTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x1080F550
	PhysicsDisallowSleepingTrack::~PhysicsDisallowSleepingTrack()
	{
	}

	// FUNCTION: ENGINE 0x10810220
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void PhysicsDisallowSleepingTrack::RegisterProperties()
	{
		if (gPhysicsDisallowSleepingTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<PhysicsDisallowSleepingTrack>("timeBegin", &PhysicsDisallowSleepingTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<PhysicsDisallowSleepingTrack>("timeEnd", &PhysicsDisallowSleepingTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyBool<PhysicsDisallowSleepingTrack>("keepPhysicsObjectAwake", &PhysicsDisallowSleepingTrack::SetKeepPhysicsObjectAwake);
			properties[2] = property;
			fight::RegisterPropertyList(properties, &gPhysicsDisallowSleepingTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x1080FFE0
	fight::TrackFactory* CreatePhysicsDisallowSleepingTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<PhysicsDisallowSleepingTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x10810470
	void RegisterPhysicsDisallowSleepingTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<PhysicsDisallowSleepingTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyBool<PhysicsDisallowSleepingTrack>;
	template class fight::PropertyFloatConstRange<PhysicsDisallowSleepingTrack>;
	template class fight::TrackFactoryTemplate<PhysicsDisallowSleepingTrack>;
	template class fight::TrackFactoryCasterTemplate<PhysicsDisallowSleepingTrack>;

	fight::Property** gPhysicsKeyframedEnableTrackProperties;  // 0x11284B9C

	// FUNCTION: ENGINE 0x1080F370
	bool PhysicsKeyframedEnableTrack::SetTimeBegin(float value)
	{
		timeBegin = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1080F380
	bool PhysicsKeyframedEnableTrack::SetTimeEnd(float value)
	{
		timeEnd = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1080F580
	fight::Property* PhysicsKeyframedEnableTrack::GetProperty(int index)
	{
		return gPhysicsKeyframedEnableTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x1080F590
	void PhysicsKeyframedEnableTrack::ClearProperties()
	{
		fight::FreePropertyList(&gPhysicsKeyframedEnableTrackProperties);
	}

	// FUNCTION: ENGINE 0x1080F5A0
	// ctor stores: [('movss', 'dword', 16, '0.0f'), ('mov', 'dword', 0, '0x10e6c43c'), ('movss', 'dword', 20, '-1.0f'), ('mov', 'dword', 12, '1')]
	PhysicsKeyframedEnableTrack::PhysicsKeyframedEnableTrack() : timeBegin(0.0f), timeEnd(-1.0f)
	{
		unknownC = 1;  // TODO base member
	}

	// FUNCTION: ENGINE 0x1080F5D0
	float PhysicsKeyframedEnableTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x1080F5E0
	float PhysicsKeyframedEnableTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x1080F5F0
	PhysicsKeyframedEnableTrack::~PhysicsKeyframedEnableTrack()
	{
	}

	// FUNCTION: ENGINE 0x10810300
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void PhysicsKeyframedEnableTrack::RegisterProperties()
	{
		if (gPhysicsKeyframedEnableTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<PhysicsKeyframedEnableTrack>("timeBegin", &PhysicsKeyframedEnableTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<PhysicsKeyframedEnableTrack>("timeEnd", &PhysicsKeyframedEnableTrack::SetTimeEnd);
			properties[1] = property;
			fight::RegisterPropertyList(properties, &gPhysicsKeyframedEnableTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x10810020
	fight::TrackFactory* CreatePhysicsKeyframedEnableTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<PhysicsKeyframedEnableTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108104D0
	void RegisterPhysicsKeyframedEnableTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<PhysicsKeyframedEnableTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyFloatConstRange<PhysicsKeyframedEnableTrack>;
	template class fight::TrackFactoryTemplate<PhysicsKeyframedEnableTrack>;
	template class fight::TrackFactoryCasterTemplate<PhysicsKeyframedEnableTrack>;

	extern fight::EnumEntry gCollisionActionOnBeginTable[];
	extern const int gCollisionActionOnBeginCount;
	fight::EnumEntry gCollisionActionOnEndTable[4] =
		{
			{ fight::Name("Do nothing", 0) },
			{ fight::Name("Restore to previous", 0) },
			{ fight::Name("Enable collision", 0) },
			{ fight::Name("Disable collision", 0) }
		};
	extern const int gCollisionActionOnEndCount;

	fight::Property** gCollisionEnableOnJointTrackProperties;  // 0x11284B8C

	// FUNCTION: ENGINE 0x1080F280
	bool CollisionEnableOnJointTrack::SetTimeBegin(float value)
	{
		timeBegin = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1080F290
	bool CollisionEnableOnJointTrack::SetTimeEnd(float value)
	{
		timeEnd = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1080F2A0
	bool CollisionEnableOnJointTrack::SetActionOnBegin(int value)
	{
		actionOnBegin = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1080F2B0
	bool CollisionEnableOnJointTrack::SetActionOnEnd(int value)
	{
		actionOnEnd = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1080F600
	bool CollisionEnableOnJointTrack::SetSimulatedJoint(const fight::Name& value)
	{
		simulatedJoint = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1080F490
	fight::Property* CollisionEnableOnJointTrack::GetProperty(int index)
	{
		return gCollisionEnableOnJointTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x1080F4A0
	void CollisionEnableOnJointTrack::ClearProperties()
	{
		fight::FreePropertyList(&gCollisionEnableOnJointTrackProperties);
	}

	// FUNCTION: ENGINE 0x1080F6A0
	// ctor stores: [('mov', 'dword', 0, '0x10e6c484'), ('mov', 'dword', 32, '0'), ('mov', 'dword', 36, '0'), ('movss', 'dword', 24, '0.0f'), ('movss', 'dword', 28, '0.0f'), ('mov', 'dword', 12, '1')]
	CollisionEnableOnJointTrack::CollisionEnableOnJointTrack() : actionOnBegin(0), actionOnEnd(0), timeBegin(0.0f), timeEnd(0.0f)
	{
		unknownC = 1;  // TODO base member
	}

	// FUNCTION: ENGINE 0x1080F6E0
	float CollisionEnableOnJointTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x1080F6F0
	float CollisionEnableOnJointTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x1080F700
	CollisionEnableOnJointTrack::~CollisionEnableOnJointTrack()
	{
	}

	// FUNCTION: ENGINE 0x10810730
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void CollisionEnableOnJointTrack::RegisterProperties()
	{
		if (gCollisionEnableOnJointTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<CollisionEnableOnJointTrack>("timeBegin", &CollisionEnableOnJointTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<CollisionEnableOnJointTrack>("timeEnd", &CollisionEnableOnJointTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyNameList<CollisionEnableOnJointTrack>("simulatedJoint", &CollisionEnableOnJointTrack::SetSimulatedJoint);
			properties[2] = property;
			property = new fight::PropertyEnumConstList<CollisionEnableOnJointTrack>("actionOnBegin", gCollisionActionOnBeginTable, gCollisionActionOnBeginCount, &CollisionEnableOnJointTrack::SetActionOnBegin);
			properties[3] = property;
			property = new fight::PropertyEnumConstList<CollisionEnableOnJointTrack>("actionOnEnd", gCollisionActionOnEndTable, gCollisionActionOnEndCount, &CollisionEnableOnJointTrack::SetActionOnEnd);
			properties[4] = property;
			fight::RegisterPropertyList(properties, &gCollisionEnableOnJointTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x1080FFA0
	fight::TrackFactory* CreateCollisionEnableOnJointTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<CollisionEnableOnJointTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x10810410
	void RegisterCollisionEnableOnJointTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<CollisionEnableOnJointTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyEnumConstList<CollisionEnableOnJointTrack>;
	template class fight::PropertyFloatConstRange<CollisionEnableOnJointTrack>;
	template class fight::PropertyNameList<CollisionEnableOnJointTrack>;
	template class fight::TrackFactoryTemplate<CollisionEnableOnJointTrack>;
	template class fight::TrackFactoryCasterTemplate<CollisionEnableOnJointTrack>;

	extern fight::EnumEntry gCollisionActionOnBeginTable[];
	extern const int gCollisionActionOnBeginCount;
	extern fight::EnumEntry gCollisionActionOnEndTable[];
	extern const int gCollisionActionOnEndCount;

	fight::Property** gCollisionEnableFromRootJointTrackProperties;  // 0x11284B90

	// FUNCTION: ENGINE 0x1080F2C0
	bool CollisionEnableFromRootJointTrack::SetTimeBegin(float value)
	{
		timeBegin = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1080F2D0
	bool CollisionEnableFromRootJointTrack::SetTimeEnd(float value)
	{
		timeEnd = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1080F2E0
	bool CollisionEnableFromRootJointTrack::SetActionOnBegin(int value)
	{
		actionOnBegin = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1080F2F0
	bool CollisionEnableFromRootJointTrack::SetActionOnEnd(int value)
	{
		actionOnEnd = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1080F620
	bool CollisionEnableFromRootJointTrack::SetRootJoint(const fight::Name& value)
	{
		rootJoint = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1080F4B0
	fight::Property* CollisionEnableFromRootJointTrack::GetProperty(int index)
	{
		return gCollisionEnableFromRootJointTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x1080F4C0
	void CollisionEnableFromRootJointTrack::ClearProperties()
	{
		fight::FreePropertyList(&gCollisionEnableFromRootJointTrackProperties);
	}

	// FUNCTION: ENGINE 0x1080F710
	// ctor stores: [('mov', 'dword', 0, '0x10e6c4cc'), ('movss', 'dword', 24, '0.0f'), ('mov', 'dword', 32, '0'), ('mov', 'dword', 36, '0'), ('movss', 'dword', 28, '-1.0f'), ('mov', 'dword', 12, '1')]
	CollisionEnableFromRootJointTrack::CollisionEnableFromRootJointTrack() : timeBegin(0.0f), actionOnBegin(0), actionOnEnd(0), timeEnd(-1.0f)
	{
		unknownC = 1;  // TODO base member
	}

	// FUNCTION: ENGINE 0x1080F750
	float CollisionEnableFromRootJointTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x1080F760
	float CollisionEnableFromRootJointTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x1080F770
	CollisionEnableFromRootJointTrack::~CollisionEnableFromRootJointTrack()
	{
	}

	// FUNCTION: ENGINE 0x10810890
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void CollisionEnableFromRootJointTrack::RegisterProperties()
	{
		if (gCollisionEnableFromRootJointTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<CollisionEnableFromRootJointTrack>("timeBegin", &CollisionEnableFromRootJointTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<CollisionEnableFromRootJointTrack>("timeEnd", &CollisionEnableFromRootJointTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyNameList<CollisionEnableFromRootJointTrack>("rootJoint", &CollisionEnableFromRootJointTrack::SetRootJoint);
			properties[2] = property;
			property = new fight::PropertyEnumConstList<CollisionEnableFromRootJointTrack>("actionOnBegin", gCollisionActionOnBeginTable, gCollisionActionOnBeginCount, &CollisionEnableFromRootJointTrack::SetActionOnBegin);
			properties[3] = property;
			property = new fight::PropertyEnumConstList<CollisionEnableFromRootJointTrack>("actionOnEnd", gCollisionActionOnEndTable, gCollisionActionOnEndCount, &CollisionEnableFromRootJointTrack::SetActionOnEnd);
			properties[4] = property;
			fight::RegisterPropertyList(properties, &gCollisionEnableFromRootJointTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x1080FFC0
	fight::TrackFactory* CreateCollisionEnableFromRootJointTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<CollisionEnableFromRootJointTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x10810440
	void RegisterCollisionEnableFromRootJointTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<CollisionEnableFromRootJointTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyEnumConstList<CollisionEnableFromRootJointTrack>;
	template class fight::PropertyFloatConstRange<CollisionEnableFromRootJointTrack>;
	template class fight::PropertyNameList<CollisionEnableFromRootJointTrack>;
	template class fight::TrackFactoryTemplate<CollisionEnableFromRootJointTrack>;
	template class fight::TrackFactoryCasterTemplate<CollisionEnableFromRootJointTrack>;

	extern fight::EnumEntry gCollisionActionOnBeginTable[];
	extern const int gCollisionActionOnBeginCount;
	extern fight::EnumEntry gCollisionActionOnEndTable[];
	extern const int gCollisionActionOnEndCount;

	fight::Property** gCollisionEnableByNameTrackProperties;  // 0x11284B98

	// FUNCTION: ENGINE 0x1080F330
	bool CollisionEnableByNameTrack::SetTimeBegin(float value)
	{
		timeBegin = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1080F340
	bool CollisionEnableByNameTrack::SetTimeEnd(float value)
	{
		timeEnd = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1080F350
	bool CollisionEnableByNameTrack::SetActionOnBegin(int value)
	{
		actionOnBegin = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1080F360
	bool CollisionEnableByNameTrack::SetActionOnEnd(int value)
	{
		actionOnEnd = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1080F640
	bool CollisionEnableByNameTrack::SetCollisionObject(const fight::Name& value)
	{
		collisionObject = value;
		return true;
	}

	// FUNCTION: ENGINE 0x1080F560
	fight::Property* CollisionEnableByNameTrack::GetProperty(int index)
	{
		return gCollisionEnableByNameTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x1080F570
	void CollisionEnableByNameTrack::ClearProperties()
	{
		fight::FreePropertyList(&gCollisionEnableByNameTrackProperties);
	}

	// FUNCTION: ENGINE 0x1080F7A0
	// ctor stores: [('mov', 'dword', 0, '0x10e6c514'), ('mov', 'dword', 32, '0'), ('mov', 'dword', 36, '0'), ('movss', 'dword', 24, '0.0f'), ('movss', 'dword', 28, '0.0f'), ('mov', 'dword', 12, '1')]
	CollisionEnableByNameTrack::CollisionEnableByNameTrack() : actionOnBegin(0), actionOnEnd(0), timeBegin(0.0f), timeEnd(0.0f)
	{
		unknownC = 1;  // TODO base member
	}

	// FUNCTION: ENGINE 0x1080F7E0
	float CollisionEnableByNameTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x1080F7F0
	float CollisionEnableByNameTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x1080F800
	CollisionEnableByNameTrack::~CollisionEnableByNameTrack()
	{
	}

	// FUNCTION: ENGINE 0x108109F0
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void CollisionEnableByNameTrack::RegisterProperties()
	{
		if (gCollisionEnableByNameTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<CollisionEnableByNameTrack>("timeBegin", &CollisionEnableByNameTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<CollisionEnableByNameTrack>("timeEnd", &CollisionEnableByNameTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyNameList<CollisionEnableByNameTrack>("collisionObject", &CollisionEnableByNameTrack::SetCollisionObject);
			properties[2] = property;
			property = new fight::PropertyEnumConstList<CollisionEnableByNameTrack>("actionOnBegin", gCollisionActionOnBeginTable, gCollisionActionOnBeginCount, &CollisionEnableByNameTrack::SetActionOnBegin);
			properties[3] = property;
			property = new fight::PropertyEnumConstList<CollisionEnableByNameTrack>("actionOnEnd", gCollisionActionOnEndTable, gCollisionActionOnEndCount, &CollisionEnableByNameTrack::SetActionOnEnd);
			properties[4] = property;
			fight::RegisterPropertyList(properties, &gCollisionEnableByNameTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x10810000
	fight::TrackFactory* CreateCollisionEnableByNameTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<CollisionEnableByNameTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108104A0
	void RegisterCollisionEnableByNameTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<CollisionEnableByNameTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyEnumConstList<CollisionEnableByNameTrack>;
	template class fight::PropertyFloatConstRange<CollisionEnableByNameTrack>;
	template class fight::PropertyNameList<CollisionEnableByNameTrack>;
	template class fight::TrackFactoryTemplate<CollisionEnableByNameTrack>;
	template class fight::TrackFactoryCasterTemplate<CollisionEnableByNameTrack>;

}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D77C30
// FUNCTION: ENGINE 0x10D77C70
// FUNCTION: ENGINE 0x10D77D00
// FUNCTION: ENGINE 0x10D8AD60
// FUNCTION: ENGINE 0x10D8AD70
// FUNCTION: ENGINE 0x10D8AD90
