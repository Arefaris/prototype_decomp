// The fight tracks that give an object a velocity, set its transform or rotation attribute, send it a message and play puppet animations (unit 0x108AD0B0 - 0x108AEE20; no assert path, file name guessed).
#include "code/engine/fight/objectstatetracks.h"

namespace engine
{
	fight::EnumEntry gVelocityLinearTrackOperationTable[2] =
		{
			{ fight::Name("Set", 0) },
			{ fight::Name("Add", 0) }
		};

	fight::Property** gVelocityLinearTrackProperties;  // 0x11318230

	// FUNCTION: ENGINE 0x108AD0B0
	bool VelocityLinearTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AD0C0
	bool VelocityLinearTrack::SetOperation(int newValue)
	{
		operation = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AD0D0
	bool VelocityLinearTrack::SetLinearVelocity(const math::Vector& newValue)
	{
		linearVelocity.x = newValue.x;
		linearVelocity.y = newValue.y;
		linearVelocity.z = newValue.z;
		return true;
	}

	// FUNCTION: ENGINE 0x108AD150
	fight::Property* VelocityLinearTrack::GetProperty(int index)
	{
		return gVelocityLinearTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108AD160
	void VelocityLinearTrack::ClearProperties()
	{
		fight::FreePropertyList(&gVelocityLinearTrackProperties);
	}

	// FUNCTION: ENGINE 0x108AD170
	// ctor stores: [('mov', 'dword', 0, '0x10e7a4cc'), ('movss', 'dword', 16, '0.0f'), ('movss', 'dword', 20, '0.0f'), ('movss', 'dword', 24, '0.0f'), ('movss', 'dword', 28, '0.0f'), ('mov', 'dword', 32, '1')]
	VelocityLinearTrack::VelocityLinearTrack() : linearVelocity(0.0f, 0.0f, 0.0f), timeBegin(0.0f), operation(1)
	{
	}

	// FUNCTION: ENGINE 0x108AD1A0
	float VelocityLinearTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108AD1B0
	float VelocityLinearTrack::Slot10() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x108AD1C0
	VelocityLinearTrack::~VelocityLinearTrack()
	{
	}

	// FUNCTION: ENGINE 0x108AD5B0
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void VelocityLinearTrack::RegisterProperties()
	{
		if (gVelocityLinearTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<VelocityLinearTrack>("timeBegin", &VelocityLinearTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyEnumConstList<VelocityLinearTrack>("operation", gVelocityLinearTrackOperationTable, 2, &VelocityLinearTrack::SetOperation);
			properties[1] = property;
			property = new fight::PropertyVector<VelocityLinearTrack>("linearVelocity", &VelocityLinearTrack::SetLinearVelocity);
			properties[2] = property;
			fight::RegisterPropertyList(properties, &gVelocityLinearTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108AD570
	fight::TrackFactory* CreateVelocityLinearTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<VelocityLinearTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108AD790
	void RegisterVelocityLinearTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<VelocityLinearTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyEnumConstList<VelocityLinearTrack>;
	template class fight::PropertyFloatConstRange<VelocityLinearTrack>;
	template class fight::PropertyVector<VelocityLinearTrack>;
	template class fight::TrackFactoryTemplate<VelocityLinearTrack>;
	template class fight::TrackFactoryCasterTemplate<VelocityLinearTrack>;

	fight::EnumEntry gVelocityAngularTrackOperationTable[2] =
		{
			{ fight::Name("Set", 0) },
			{ fight::Name("Add", 0) }
		};

	fight::Property** gVelocityAngularTrackProperties;  // 0x11318234

	// FUNCTION: ENGINE 0x108AD0F0
	bool VelocityAngularTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AD100
	bool VelocityAngularTrack::SetOperation(int newValue)
	{
		operation = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AD110
	bool VelocityAngularTrack::SetAngularVelocity(const math::Vector& newValue)
	{
		// Degrees in the property, radians in the track
		math::Vector v(newValue.x, newValue.y, newValue.z);
		v.Scale(0.01745329238474369f);
		angularVelocity.x = v.x;
		angularVelocity.y = v.y;
		angularVelocity.z = v.z;
		return true;
	}

	// FUNCTION: ENGINE 0x108AD1D0
	fight::Property* VelocityAngularTrack::GetProperty(int index)
	{
		return gVelocityAngularTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108AD1E0
	void VelocityAngularTrack::ClearProperties()
	{
		fight::FreePropertyList(&gVelocityAngularTrackProperties);
	}

	// FUNCTION: ENGINE 0x108AD1F0
	// ctor stores: [('mov', 'dword', 0, '0x10e7a514'), ('movss', 'dword', 16, '0.0f'), ('movss', 'dword', 20, '0.0f'), ('movss', 'dword', 24, '0.0f'), ('movss', 'dword', 28, '0.0f'), ('mov', 'dword', 32, '1')]
	VelocityAngularTrack::VelocityAngularTrack() : angularVelocity(0.0f, 0.0f, 0.0f), timeBegin(0.0f), operation(1)
	{
	}

	// FUNCTION: ENGINE 0x108AD220
	float VelocityAngularTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108AD230
	float VelocityAngularTrack::Slot10() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x108AD240
	VelocityAngularTrack::~VelocityAngularTrack()
	{
	}

	// FUNCTION: ENGINE 0x108AD6A0
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void VelocityAngularTrack::RegisterProperties()
	{
		if (gVelocityAngularTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<VelocityAngularTrack>("timeBegin", &VelocityAngularTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyEnumConstList<VelocityAngularTrack>("operation", gVelocityAngularTrackOperationTable, 2, &VelocityAngularTrack::SetOperation);
			properties[1] = property;
			property = new fight::PropertyVector<VelocityAngularTrack>("angularVelocity", &VelocityAngularTrack::SetAngularVelocity);
			properties[2] = property;
			fight::RegisterPropertyList(properties, &gVelocityAngularTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108AD590
	fight::TrackFactory* CreateVelocityAngularTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<VelocityAngularTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108AD7C0
	void RegisterVelocityAngularTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<VelocityAngularTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyEnumConstList<VelocityAngularTrack>;
	template class fight::PropertyFloatConstRange<VelocityAngularTrack>;
	template class fight::PropertyVector<VelocityAngularTrack>;
	template class fight::TrackFactoryTemplate<VelocityAngularTrack>;
	template class fight::TrackFactoryCasterTemplate<VelocityAngularTrack>;

	fight::EnumEntry gSimpleMessageTrackMessageTable[7] =
		{
			{ fight::Name("None", 0) },
			{ fight::Name("Reset", 0) },
			{ fight::Name("Show Debug", 0) },
			{ fight::Name("Hide Debug", 0) },
			{ fight::Name("Start Animation", 0) },
			{ fight::Name("Stop Animation", 0) },
			{ fight::Name("Force Query Tree", 0) }
		};
	extern const int gSimpleMessageTrackMessageCount;

	fight::Property** gSimpleMessageTrackProperties;  // 0x11318258

	// FUNCTION: ENGINE 0x108AD910
	bool SimpleMessageTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AD920
	bool SimpleMessageTrack::SetMessage(int newValue)
	{
		message = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AD930
	fight::Property* SimpleMessageTrack::GetProperty(int index)
	{
		return gSimpleMessageTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108AD940
	void SimpleMessageTrack::ClearProperties()
	{
		fight::FreePropertyList(&gSimpleMessageTrackProperties);
	}

	// FUNCTION: ENGINE 0x108AD950
	// ctor stores: [('mov', 'dword', 0, '0x10e7a684'), ('movss', 'dword', 16, '0.0f'), ('mov', 'dword', 20, '0')]
	SimpleMessageTrack::SimpleMessageTrack() : timeBegin(0.0f), message(0)
	{
	}

	// FUNCTION: ENGINE 0x108AD980
	float SimpleMessageTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108AD990
	float SimpleMessageTrack::Slot10() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x108AD9A0
	SimpleMessageTrack::~SimpleMessageTrack()
	{
	}

	// FUNCTION: ENGINE 0x108ADB10
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void SimpleMessageTrack::RegisterProperties()
	{
		if (gSimpleMessageTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<SimpleMessageTrack>("timeBegin", &SimpleMessageTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyEnumConstList<SimpleMessageTrack>("message", gSimpleMessageTrackMessageTable, gSimpleMessageTrackMessageCount, &SimpleMessageTrack::SetMessage);
			properties[1] = property;
			fight::RegisterPropertyList(properties, &gSimpleMessageTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108ADAF0
	fight::TrackFactory* CreateSimpleMessageTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<SimpleMessageTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108ADBD0
	void RegisterSimpleMessageTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<SimpleMessageTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyEnumConstList<SimpleMessageTrack>;
	template class fight::PropertyFloatConstRange<SimpleMessageTrack>;
	template class fight::TrackFactoryTemplate<SimpleMessageTrack>;
	template class fight::TrackFactoryCasterTemplate<SimpleMessageTrack>;

	fight::Property** gSetTransformAttributeTrackProperties;  // 0x1131825C

	// FUNCTION: ENGINE 0x108ADC90
	bool SetTransformAttributeTrack::SetTransform(const math::Vector& newValue)
	{
		transform.x = newValue.x;
		transform.y = newValue.y;
		transform.z = newValue.z;
		return true;
	}

	// FUNCTION: ENGINE 0x108ADCB0
	bool SetTransformAttributeTrack::SetRotationEulerAnglesXYZ(const math::Vector& newValue)
	{
		// Degrees in the property, radians in the track
		math::Vector v(newValue.x, newValue.y, newValue.z);
		v.Scale(0.01745329238474369f);
		rotationEulerAnglesXYZ.x = v.x;
		rotationEulerAnglesXYZ.y = v.y;
		rotationEulerAnglesXYZ.z = v.z;
		return true;
	}

	// FUNCTION: ENGINE 0x108ADD30
	fight::Property* SetTransformAttributeTrack::GetProperty(int index)
	{
		return gSetTransformAttributeTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108ADD40
	void SetTransformAttributeTrack::ClearProperties()
	{
		fight::FreePropertyList(&gSetTransformAttributeTrackProperties);
	}

	// FUNCTION: ENGINE 0x108ADD50
	// ctor stores: [('mov', 'dword', 0, '0x10e7a744'), ('movss', 'dword', 16, '0.0f'), ('movss', 'dword', 20, '0.0f'), ('movss', 'dword', 24, '0.0f'), ('movss', 'dword', 28, '0.0f'), ('movss', 'dword', 32, '0.0f'), ('movss', 'dword', 36, '0.0f')]
	SetTransformAttributeTrack::SetTransformAttributeTrack() : rotationEulerAnglesXYZ(0.0f, 0.0f, 0.0f), transform(0.0f, 0.0f, 0.0f)
	{
	}

	// FUNCTION: ENGINE 0x108ADD90
	float SetTransformAttributeTrack::GetTimeBegin() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x108ADDA0
	float SetTransformAttributeTrack::Slot10() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x108ADDB0
	SetTransformAttributeTrack::~SetTransformAttributeTrack()
	{
	}

	// FUNCTION: ENGINE 0x108AE030
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void SetTransformAttributeTrack::RegisterProperties()
	{
		if (gSetTransformAttributeTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyVector<SetTransformAttributeTrack>("transform", &SetTransformAttributeTrack::SetTransform);
			properties[0] = property;
			property = new fight::PropertyVector<SetTransformAttributeTrack>("rotationEulerAnglesXYZ", &SetTransformAttributeTrack::SetRotationEulerAnglesXYZ);
			properties[1] = property;
			fight::RegisterPropertyList(properties, &gSetTransformAttributeTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108ADFF0
	fight::TrackFactory* CreateSetTransformAttributeTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<SetTransformAttributeTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108AE190
	void RegisterSetTransformAttributeTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<SetTransformAttributeTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyVector<SetTransformAttributeTrack>;
	template class fight::TrackFactoryTemplate<SetTransformAttributeTrack>;
	template class fight::TrackFactoryCasterTemplate<SetTransformAttributeTrack>;

	fight::Property** gSetRotationAttributeTrackProperties;  // 0x11318260

	// FUNCTION: ENGINE 0x108ADCF0
	bool SetRotationAttributeTrack::SetRotationAxis(const math::Vector& newValue)
	{
		rotationAxis.x = newValue.x;
		rotationAxis.y = newValue.y;
		rotationAxis.z = newValue.z;
		return true;
	}

	// FUNCTION: ENGINE 0x108ADD10
	bool SetRotationAttributeTrack::SetRotationDegrees(float newValue)
	{
		rotationDegrees = newValue * 0.01745329238474369f;
		return true;
	}

	// FUNCTION: ENGINE 0x108ADDC0
	fight::Property* SetRotationAttributeTrack::GetProperty(int index)
	{
		return gSetRotationAttributeTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108ADDD0
	void SetRotationAttributeTrack::ClearProperties()
	{
		fight::FreePropertyList(&gSetRotationAttributeTrackProperties);
	}

	// FUNCTION: ENGINE 0x108ADDE0
	// ctor stores: [('mov', 'dword', 0, '0x10e7a78c'), ('movss', 'dword', 16, '0.0f'), ('movss', 'dword', 20, '0.0f'), ('movss', 'dword', 24, '0.0f'), ('movss', 'dword', 28, '0.0f')]
	SetRotationAttributeTrack::SetRotationAttributeTrack() : rotationAxis(0.0f, 0.0f, 0.0f), rotationDegrees(0.0f)
	{
	}

	// FUNCTION: ENGINE 0x108ADE10
	float SetRotationAttributeTrack::GetTimeBegin() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x108ADE20
	float SetRotationAttributeTrack::Slot10() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x108ADE30
	SetRotationAttributeTrack::~SetRotationAttributeTrack()
	{
	}

	// FUNCTION: ENGINE 0x108AE0E0
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void SetRotationAttributeTrack::RegisterProperties()
	{
		if (gSetRotationAttributeTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyVector<SetRotationAttributeTrack>("rotationAxis", &SetRotationAttributeTrack::SetRotationAxis);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<SetRotationAttributeTrack>("rotationDegrees", &SetRotationAttributeTrack::SetRotationDegrees);
			properties[1] = property;
			fight::RegisterPropertyList(properties, &gSetRotationAttributeTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108AE010
	fight::TrackFactory* CreateSetRotationAttributeTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<SetRotationAttributeTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108AE1C0
	void RegisterSetRotationAttributeTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<SetRotationAttributeTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyFloatConstRange<SetRotationAttributeTrack>;
	template class fight::PropertyVector<SetRotationAttributeTrack>;
	template class fight::TrackFactoryTemplate<SetRotationAttributeTrack>;
	template class fight::TrackFactoryCasterTemplate<SetRotationAttributeTrack>;

	fight::EnumEntry gPuppetAnimationTrackCyclicTable[6] =
		{
			{ fight::Name("From Animation", 0) },
			{ fight::Name("Not Cyclic", 0) },
			{ fight::Name("Cyclic", 0) },
			{ fight::Name("Hold End Frame", 0) },
			{ fight::Name("Not Cyclic - Backward", 0) },
			{ fight::Name("Cyclic - Backward", 0) }
		};
	fight::EnumEntry gPuppetAnimationTrackSyncPhaseTable[2] =
		{
			{ fight::Name("Legacy", 0) },
			{ fight::Name("From Puppet Phase", 0) }
		};

	fight::Property** gPuppetAnimationTrackProperties;  // 0x11318268

	// FUNCTION: ENGINE 0x108AE310
	bool PuppetAnimationTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AE320
	bool PuppetAnimationTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AE330
	bool PuppetAnimationTrack::SetSpeed(float newValue)
	{
		speed = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AE340
	bool PuppetAnimationTrack::SetRandomSpeedVariation(float newValue)
	{
		randomSpeedVariation = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AE350
	bool PuppetAnimationTrack::SetInitFrame(float newValue)
	{
		initFrame = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AE360
	bool PuppetAnimationTrack::SetStartFrame(float newValue)
	{
		startFrame = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AE370
	bool PuppetAnimationTrack::SetEndFrame(float newValue)
	{
		endFrame = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AE380
	bool PuppetAnimationTrack::SetCyclic(int newValue)
	{
		cyclic = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AE390
	bool PuppetAnimationTrack::SetSyncFrame(bool newValue)
	{
		syncFrame = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AE3B0
	bool PuppetAnimationTrack::SetPhaseMatch(bool newValue)
	{
		phaseMatch = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AE3D0
	bool PuppetAnimationTrack::SetReuseExistingDriver(bool newValue)
	{
		reuseExistingDriver = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AE3F0
	bool PuppetAnimationTrack::SetSyncPhase(int newValue)
	{
		syncPhase = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AE400
	bool PuppetAnimationTrack::SetSyncPhaseMinFrame(float newValue)
	{
		syncPhaseMinFrame = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AE410
	bool PuppetAnimationTrack::SetSyncPhaseMaxFrame(float newValue)
	{
		syncPhaseMaxFrame = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AE420
	bool PuppetAnimationTrack::SetHasRootTranslation(bool newValue)
	{
		hasRootTranslation = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AE440
	bool PuppetAnimationTrack::SetHasRootRotation(bool newValue)
	{
		hasRootRotation = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AE460
	bool PuppetAnimationTrack::SetWeight(float newValue)
	{
		weight = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AE470
	bool PuppetAnimationTrack::SetPriority(int newValue)
	{
		priority = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AE480
	bool PuppetAnimationTrack::SetBlendInTime(float newValue)
	{
		blendInTime = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AE490
	bool PuppetAnimationTrack::SetBlendOutTime(float newValue)
	{
		blendOutTime = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AE4C0
	bool PuppetAnimationTrack::SetAnimation(const fight::Name& newValue)
	{
		animation = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AE4E0
	bool PuppetAnimationTrack::SetPartition(const fight::Name& newValue)
	{
		partition = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108AE4A0
	fight::Property* PuppetAnimationTrack::GetProperty(int index)
	{
		return gPuppetAnimationTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108AE4B0
	void PuppetAnimationTrack::ClearProperties()
	{
		fight::FreePropertyList(&gPuppetAnimationTrackProperties);
	}

	// FUNCTION: ENGINE 0x108AE500
	// ctor stores: [('mov', 'dword', 0, '0x10e7a8b4'), ('mov', 'dword', 80, '0'), ('mov', 'dword', 84, '0'), ('mov', 'dword', 88, '0'), ('mov', 'byte', 92, '0'), ('movss', 'dword', 32, '0.0f'), ('movss', 'dword', 36, '0.0f'), ('movss', 'dword', 40, '-1.0f'), ('movss', 'dword', 44, '0.0f'), ('movss', 'dword', 48, '0.0f'), ('movss', 'dword', 52, '1.0f'), ('movss', 'dword', 56, '0.0f'), ('movss', 'dword', 60, '-1.0f'), ('movss', 'dword', 64, '0.0f'), ('movss', 'dword', 68, '0.0f'), ('movss', 'dword', 72, '-1.0f'), ('movss', 'dword', 76, '1.0f')]
	PuppetAnimationTrack::PuppetAnimationTrack() : blendInTime(0.0f), blendOutTime(0.0f), endFrame(-1.0f), initFrame(0.0f), randomSpeedVariation(0.0f), speed(1.0f), startFrame(0.0f), syncPhaseMaxFrame(-1.0f), syncPhaseMinFrame(0.0f), timeBegin(0.0f), timeEnd(-1.0f), weight(1.0f), cyclic(0), priority(0), syncPhase(0), hasRootRotation(true), hasRootTranslation(true), phaseMatch(false), reuseExistingDriver(false), syncFrame(false)
	{
	}

	// FUNCTION: ENGINE 0x108AE590
	float PuppetAnimationTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108AE5A0
	float PuppetAnimationTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x108AE5B0
	PuppetAnimationTrack::~PuppetAnimationTrack()
	{
	}

	// FUNCTION: ENGINE 0x108AE880
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void PuppetAnimationTrack::RegisterProperties()
	{
		if (gPuppetAnimationTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<PuppetAnimationTrack>("timeBegin", &PuppetAnimationTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<PuppetAnimationTrack>("timeEnd", &PuppetAnimationTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyName<PuppetAnimationTrack>("animation", &PuppetAnimationTrack::SetAnimation);
			properties[2] = property;
			property = new fight::PropertyFloatConstRange<PuppetAnimationTrack>("speed", &PuppetAnimationTrack::SetSpeed);
			properties[3] = property;
			property = new fight::PropertyFloatConstRange<PuppetAnimationTrack>("randomSpeedVariation", &PuppetAnimationTrack::SetRandomSpeedVariation);
			properties[4] = property;
			property = new fight::PropertyFloatConstRange<PuppetAnimationTrack>("initFrame", &PuppetAnimationTrack::SetInitFrame);
			properties[5] = property;
			property = new fight::PropertyFloatConstRange<PuppetAnimationTrack>("startFrame", &PuppetAnimationTrack::SetStartFrame);
			properties[6] = property;
			property = new fight::PropertyFloatConstRange<PuppetAnimationTrack>("endFrame", &PuppetAnimationTrack::SetEndFrame);
			properties[7] = property;
			property = new fight::PropertyEnumConstList<PuppetAnimationTrack>("cyclic", gPuppetAnimationTrackCyclicTable, 6, &PuppetAnimationTrack::SetCyclic);
			properties[8] = property;
			property = new fight::PropertyBool<PuppetAnimationTrack>("syncFrame", &PuppetAnimationTrack::SetSyncFrame);
			properties[9] = property;
			property = new fight::PropertyBool<PuppetAnimationTrack>("phaseMatch", &PuppetAnimationTrack::SetPhaseMatch);
			properties[10] = property;
			property = new fight::PropertyBool<PuppetAnimationTrack>("reuseExistingDriver", &PuppetAnimationTrack::SetReuseExistingDriver);
			properties[11] = property;
			property = new fight::PropertyEnumConstList<PuppetAnimationTrack>("syncPhase", gPuppetAnimationTrackSyncPhaseTable, 2, &PuppetAnimationTrack::SetSyncPhase);
			properties[12] = property;
			property = new fight::PropertyFloatConstRange<PuppetAnimationTrack>("syncPhaseMinFrame", &PuppetAnimationTrack::SetSyncPhaseMinFrame);
			properties[13] = property;
			property = new fight::PropertyFloatConstRange<PuppetAnimationTrack>("syncPhaseMaxFrame", &PuppetAnimationTrack::SetSyncPhaseMaxFrame);
			properties[14] = property;
			property = new fight::PropertyBool<PuppetAnimationTrack>("hasRootTranslation", &PuppetAnimationTrack::SetHasRootTranslation);
			properties[15] = property;
			property = new fight::PropertyBool<PuppetAnimationTrack>("hasRootRotation", &PuppetAnimationTrack::SetHasRootRotation);
			properties[16] = property;
			property = new fight::PropertyNameList<PuppetAnimationTrack>("partition", &PuppetAnimationTrack::SetPartition);
			properties[17] = property;
			property = new fight::PropertyFloatConstRange<PuppetAnimationTrack>("weight", &PuppetAnimationTrack::SetWeight);
			properties[18] = property;
			property = new fight::PropertyIntConstRange<PuppetAnimationTrack>("priority", &PuppetAnimationTrack::SetPriority);
			properties[19] = property;
			property = new fight::PropertyFloatConstRange<PuppetAnimationTrack>("blendInTime", &PuppetAnimationTrack::SetBlendInTime);
			properties[20] = property;
			property = new fight::PropertyFloatConstRange<PuppetAnimationTrack>("blendOutTime", &PuppetAnimationTrack::SetBlendOutTime);
			properties[21] = property;
			fight::RegisterPropertyList(properties, &gPuppetAnimationTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108AE7A0
	fight::TrackFactory* CreatePuppetAnimationTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<PuppetAnimationTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108AE7C0
	void RegisterPuppetAnimationTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<PuppetAnimationTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyBool<PuppetAnimationTrack>;
	template class fight::PropertyEnumConstList<PuppetAnimationTrack>;
	template class fight::PropertyFloatConstRange<PuppetAnimationTrack>;
	template class fight::PropertyIntConstRange<PuppetAnimationTrack>;
	template class fight::PropertyName<PuppetAnimationTrack>;
	template class fight::PropertyNameList<PuppetAnimationTrack>;
	template class fight::TrackFactoryTemplate<PuppetAnimationTrack>;
	template class fight::TrackFactoryCasterTemplate<PuppetAnimationTrack>;

}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D77D90
// FUNCTION: ENGINE 0x10D77DC0
// FUNCTION: ENGINE 0x10D77DF0
// FUNCTION: ENGINE 0x10D77E70
// FUNCTION: ENGINE 0x10D78A20
// FUNCTION: ENGINE 0x10D8ADC0
// FUNCTION: ENGINE 0x10D8ADD0
// FUNCTION: ENGINE 0x10D8ADE0
// FUNCTION: ENGINE 0x10D8ADF0
// FUNCTION: ENGINE 0x10D8B130
