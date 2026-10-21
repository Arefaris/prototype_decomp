// The fight tracks that control the root, adjust a strafe, steer a character and test the choreography (unit 0x108FB4B0 - 0x108FCA50; no assert path, file name guessed).
#include "code/engine/fight/rootcontrol.h"

namespace engine
{
	fight::Property** gControlRootTrackProperties;  // 0x1131B318

	// FUNCTION: ENGINE 0x108FB540
	bool ControlRootTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB550
	bool ControlRootTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB560
	bool ControlRootTrack::SetMovementEnabled(bool newValue)
	{
		movementEnabled = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB570
	bool ControlRootTrack::SetMaxSpeed(float newValue)
	{
		maxSpeed = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB580
	bool ControlRootTrack::SetGravity(float newValue)
	{
		gravity = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB590
	bool ControlRootTrack::SetSteeringEnabled(bool newValue)
	{
		steeringEnabled = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB5A0
	bool ControlRootTrack::SetMaxTurnSpeed(float newValue)
	{
		maxTurnSpeed = newValue * 0.0174532924f;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB5C0
	bool ControlRootTrack::SetPriority(int newValue)
	{
		priority = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB5D0
	bool ControlRootTrack::SetBlendInTime(float newValue)
	{
		blendInTime = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB5E0
	bool ControlRootTrack::SetBlendOutTime(float newValue)
	{
		blendOutTime = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB770
	fight::Property* ControlRootTrack::GetProperty(int index)
	{
		return gControlRootTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108FB780
	void ControlRootTrack::ClearProperties()
	{
		fight::FreePropertyList(&gControlRootTrackProperties);
	}

	// FUNCTION: ENGINE 0x108FB790
	ControlRootTrack::ControlRootTrack() : blendInTime(0.0f), blendOutTime(0.0f), gravity(10.0f), maxSpeed(0.0f), maxTurnSpeed(0.0f), timeBegin(0.0f), timeEnd(-1.0f), priority(0), movementEnabled(true), steeringEnabled(true)
	{
	}

	// FUNCTION: ENGINE 0x108FB7F0
	float ControlRootTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108FB800
	float ControlRootTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x108FB810
	ControlRootTrack::~ControlRootTrack()
	{
	}

	// FUNCTION: ENGINE 0x108FC070
	fight::TrackFactory* CreateControlRootTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<ControlRootTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108FC0D0
	// EQUIVALENT: the engine saves the registers it uses in the entry block, before the guard's branch; ours sinks the pushes behind the branch and leaves the early exit without the pops; every other instruction is the engine's
	void ControlRootTrack::RegisterProperties()
	{
		if (gControlRootTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<ControlRootTrack>("timeBegin", &ControlRootTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<ControlRootTrack>("timeEnd", &ControlRootTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyBool<ControlRootTrack>("movementEnabled", &ControlRootTrack::SetMovementEnabled);
			properties[2] = property;
			property = new fight::PropertyFloatConstRange<ControlRootTrack>("maxSpeed", &ControlRootTrack::SetMaxSpeed);
			properties[3] = property;
			property = new fight::PropertyFloatConstRange<ControlRootTrack>("gravity", &ControlRootTrack::SetGravity);
			properties[4] = property;
			property = new fight::PropertyBool<ControlRootTrack>("steeringEnabled", &ControlRootTrack::SetSteeringEnabled);
			properties[5] = property;
			property = new fight::PropertyFloatConstRange<ControlRootTrack>("maxTurnSpeed", &ControlRootTrack::SetMaxTurnSpeed);
			properties[6] = property;
			property = new fight::PropertyIntConstRange<ControlRootTrack>("priority", &ControlRootTrack::SetPriority);
			properties[7] = property;
			property = new fight::PropertyFloatConstRange<ControlRootTrack>("blendInTime", &ControlRootTrack::SetBlendInTime);
			properties[8] = property;
			property = new fight::PropertyFloatConstRange<ControlRootTrack>("blendOutTime", &ControlRootTrack::SetBlendOutTime);
			properties[9] = property;
			fight::RegisterPropertyList(properties, &gControlRootTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108FC340
	void RegisterControlRootTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<ControlRootTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyBool<ControlRootTrack>;
	template class fight::PropertyFloatConstRange<ControlRootTrack>;
	template class fight::PropertyIntConstRange<ControlRootTrack>;
	template class fight::TrackFactoryTemplate<ControlRootTrack>;
	template class fight::TrackFactoryCasterTemplate<ControlRootTrack>;


	fight::Property** gStrafeAdjustRootTrackProperties;  // 0x1131B314

	// FUNCTION: ENGINE 0x108FB4B0
	bool StrafeAdjustRootTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB4C0
	bool StrafeAdjustRootTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB4D0
	bool StrafeAdjustRootTrack::SetOriginalDirection(const math::Vector& newValue)
	{
		originalDirection.x = newValue.x;
		originalDirection.y = newValue.y;
		originalDirection.z = newValue.z;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB4F0
	bool StrafeAdjustRootTrack::SetAngleAdjustRate(float newValue)
	{
		angleAdjustRate = newValue * 0.0174532924f;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB510
	bool StrafeAdjustRootTrack::SetPriority(int newValue)
	{
		priority = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB520
	bool StrafeAdjustRootTrack::SetBlendInTime(float newValue)
	{
		blendInTime = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB530
	bool StrafeAdjustRootTrack::SetBlendOutTime(float newValue)
	{
		blendOutTime = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB750
	fight::Property* StrafeAdjustRootTrack::GetProperty(int index)
	{
		return gStrafeAdjustRootTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108FB760
	void StrafeAdjustRootTrack::ClearProperties()
	{
		fight::FreePropertyList(&gStrafeAdjustRootTrackProperties);
	}

	// FUNCTION: ENGINE 0x108FB860
	bool StrafeAdjustRootTrack::SetAdjustJoint(const fight::Name& newValue)
	{
		adjustJoint = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB940
	StrafeAdjustRootTrack::StrafeAdjustRootTrack() : originalDirection(0.0f, 0.0f, -1.0f), angleAdjustRate(3.14159274f), blendInTime(0.0f), blendOutTime(0.0f), timeBegin(0.0f), timeEnd(-1.0f), priority(0)
	{
	}

	// FUNCTION: ENGINE 0x108FB9A0
	float StrafeAdjustRootTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108FB9B0
	float StrafeAdjustRootTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x108FB9C0
	StrafeAdjustRootTrack::~StrafeAdjustRootTrack()
	{
	}

	// FUNCTION: ENGINE 0x108FC050
	fight::TrackFactory* CreateStrafeAdjustRootTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<StrafeAdjustRootTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108FC310
	void RegisterStrafeAdjustRootTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<StrafeAdjustRootTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	// FUNCTION: ENGINE 0x108FC4F0
	// EQUIVALENT: the engine saves the registers it uses in the entry block, before the guard's branch; ours sinks the pushes behind the branch and leaves the early exit without the pops; every other instruction is the engine's
	void StrafeAdjustRootTrack::RegisterProperties()
	{
		if (gStrafeAdjustRootTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<StrafeAdjustRootTrack>("timeBegin", &StrafeAdjustRootTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<StrafeAdjustRootTrack>("timeEnd", &StrafeAdjustRootTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyNameList<StrafeAdjustRootTrack>("adjustJoint", &StrafeAdjustRootTrack::SetAdjustJoint);
			properties[2] = property;
			property = new fight::PropertyVector<StrafeAdjustRootTrack>("originalDirection", &StrafeAdjustRootTrack::SetOriginalDirection);
			properties[3] = property;
			property = new fight::PropertyFloatConstRange<StrafeAdjustRootTrack>("angleAdjustRate", &StrafeAdjustRootTrack::SetAngleAdjustRate);
			properties[4] = property;
			property = new fight::PropertyIntConstRange<StrafeAdjustRootTrack>("priority", &StrafeAdjustRootTrack::SetPriority);
			properties[5] = property;
			property = new fight::PropertyFloatConstRange<StrafeAdjustRootTrack>("blendInTime", &StrafeAdjustRootTrack::SetBlendInTime);
			properties[6] = property;
			property = new fight::PropertyFloatConstRange<StrafeAdjustRootTrack>("blendOutTime", &StrafeAdjustRootTrack::SetBlendOutTime);
			properties[7] = property;
			fight::RegisterPropertyList(properties, &gStrafeAdjustRootTrackProperties);
		}
	}

	template class fight::PropertyFloatConstRange<StrafeAdjustRootTrack>;
	template class fight::PropertyIntConstRange<StrafeAdjustRootTrack>;
	template class fight::PropertyNameList<StrafeAdjustRootTrack>;
	template class fight::PropertyVector<StrafeAdjustRootTrack>;
	template class fight::TrackFactoryTemplate<StrafeAdjustRootTrack>;
	template class fight::TrackFactoryCasterTemplate<StrafeAdjustRootTrack>;


	fight::Property** gCharacterSteerTrackProperties;  // 0x1131B31C

	// FUNCTION: ENGINE 0x108FB5F0
	bool CharacterSteerTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB600
	bool CharacterSteerTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB610
	bool CharacterSteerTrack::SetAcceleration(float newValue)
	{
		acceleration = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB620
	bool CharacterSteerTrack::SetTurningVelocity(float newValue)
	{
		turningVelocity = newValue * 0.0174532924f;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB640
	bool CharacterSteerTrack::SetVelocityWalk(float newValue)
	{
		velocityWalk = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB650
	bool CharacterSteerTrack::SetVelocityRun(float newValue)
	{
		velocityRun = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB660
	bool CharacterSteerTrack::SetGravity(float newValue)
	{
		gravity = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB670
	bool CharacterSteerTrack::SetPhase(float newValue)
	{
		phase = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB680
	bool CharacterSteerTrack::SetPriority(int newValue)
	{
		priority = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB690
	bool CharacterSteerTrack::SetBlendInTime(float newValue)
	{
		blendInTime = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB6A0
	bool CharacterSteerTrack::SetBlendOutTime(float newValue)
	{
		blendOutTime = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB6B0
	bool CharacterSteerTrack::SetDisableRootMotion(bool newValue)
	{
		disableRootMotion = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB820
	fight::Property* CharacterSteerTrack::GetProperty(int index)
	{
		return gCharacterSteerTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108FB830
	void CharacterSteerTrack::ClearProperties()
	{
		fight::FreePropertyList(&gCharacterSteerTrackProperties);
	}

	// FUNCTION: ENGINE 0x108FB880
	bool CharacterSteerTrack::SetLocomotion(const fight::Name& newValue)
	{
		locomotion = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB8A0
	bool CharacterSteerTrack::SetAnimIdle(const fight::Name& newValue)
	{
		animIdle = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB8C0
	bool CharacterSteerTrack::SetAnimWalk(const fight::Name& newValue)
	{
		animWalk = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB8E0
	bool CharacterSteerTrack::SetAnimRun(const fight::Name& newValue)
	{
		animRun = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB900
	bool CharacterSteerTrack::SetPartition(const fight::Name& newValue)
	{
		partition = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB9F0
	CharacterSteerTrack::CharacterSteerTrack() : acceleration(0.0f), blendInTime(0.0f), blendOutTime(0.0f), gravity(0.0f), phase(0.0f), timeBegin(0.0f), timeEnd(0.0f), turningVelocity(0.0f), velocityRun(0.0f), velocityWalk(0.0f), priority(0), disableRootMotion(false)
	{
	}

	// FUNCTION: ENGINE 0x108FBA70
	float CharacterSteerTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108FBA80
	float CharacterSteerTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x108FBA90
	CharacterSteerTrack::~CharacterSteerTrack()
	{
	}

	// FUNCTION: ENGINE 0x108FC090
	fight::TrackFactory* CreateCharacterSteerTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<CharacterSteerTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108FC370
	void RegisterCharacterSteerTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<CharacterSteerTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	// FUNCTION: ENGINE 0x108FC6C0
	// EQUIVALENT: the engine saves the registers it uses in the entry block, before the guard's branch; ours sinks the pushes behind the branch and leaves the early exit without the pops; every other instruction is the engine's
	void CharacterSteerTrack::RegisterProperties()
	{
		if (gCharacterSteerTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<CharacterSteerTrack>("timeBegin", &CharacterSteerTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<CharacterSteerTrack>("timeEnd", &CharacterSteerTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyFloatConstRange<CharacterSteerTrack>("acceleration", &CharacterSteerTrack::SetAcceleration);
			properties[2] = property;
			property = new fight::PropertyFloatConstRange<CharacterSteerTrack>("turningVelocity", &CharacterSteerTrack::SetTurningVelocity);
			properties[3] = property;
			property = new fight::PropertyFloatConstRange<CharacterSteerTrack>("velocityWalk", &CharacterSteerTrack::SetVelocityWalk);
			properties[4] = property;
			property = new fight::PropertyFloatConstRange<CharacterSteerTrack>("velocityRun", &CharacterSteerTrack::SetVelocityRun);
			properties[5] = property;
			property = new fight::PropertyFloatConstRange<CharacterSteerTrack>("gravity", &CharacterSteerTrack::SetGravity);
			properties[6] = property;
			property = new fight::PropertyFloatConstRange<CharacterSteerTrack>("phase", &CharacterSteerTrack::SetPhase);
			properties[7] = property;
			property = new fight::PropertyName<CharacterSteerTrack>("locomotion", &CharacterSteerTrack::SetLocomotion);
			properties[8] = property;
			property = new fight::PropertyName<CharacterSteerTrack>("animIdle", &CharacterSteerTrack::SetAnimIdle);
			properties[9] = property;
			property = new fight::PropertyName<CharacterSteerTrack>("animWalk", &CharacterSteerTrack::SetAnimWalk);
			properties[10] = property;
			property = new fight::PropertyName<CharacterSteerTrack>("animRun", &CharacterSteerTrack::SetAnimRun);
			properties[11] = property;
			property = new fight::PropertyName<CharacterSteerTrack>("partition", &CharacterSteerTrack::SetPartition);
			properties[12] = property;
			property = new fight::PropertyIntConstRange<CharacterSteerTrack>("priority", &CharacterSteerTrack::SetPriority);
			properties[13] = property;
			property = new fight::PropertyFloatConstRange<CharacterSteerTrack>("blendInTime", &CharacterSteerTrack::SetBlendInTime);
			properties[14] = property;
			property = new fight::PropertyFloatConstRange<CharacterSteerTrack>("blendOutTime", &CharacterSteerTrack::SetBlendOutTime);
			properties[15] = property;
			property = new fight::PropertyBool<CharacterSteerTrack>("disableRootMotion", &CharacterSteerTrack::SetDisableRootMotion);
			properties[16] = property;
			fight::RegisterPropertyList(properties, &gCharacterSteerTrackProperties);
		}
	}

	template class fight::PropertyBool<CharacterSteerTrack>;
	template class fight::PropertyFloatConstRange<CharacterSteerTrack>;
	template class fight::PropertyIntConstRange<CharacterSteerTrack>;
	template class fight::PropertyName<CharacterSteerTrack>;
	template class fight::TrackFactoryTemplate<CharacterSteerTrack>;
	template class fight::TrackFactoryCasterTemplate<CharacterSteerTrack>;


	fight::Property** gChoreoTestsTrackProperties;  // 0x1131B320

	// FUNCTION: ENGINE 0x108FB6C0
	bool ChoreoTestsTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB6D0
	bool ChoreoTestsTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB6E0
	bool ChoreoTestsTrack::SetTestRandomSteer(bool newValue)
	{
		testRandomSteer = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB6F0
	bool ChoreoTestsTrack::SetTestPoseDriver(bool newValue)
	{
		testPoseDriver = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB700
	bool ChoreoTestsTrack::SetTestRestPoseDriver(bool newValue)
	{
		testRestPoseDriver = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB710
	bool ChoreoTestsTrack::SetTestDriverCopy(bool newValue)
	{
		testDriverCopy = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB720
	bool ChoreoTestsTrack::SetPriority(int newValue)
	{
		priority = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB730
	bool ChoreoTestsTrack::SetBlendInTime(float newValue)
	{
		blendInTime = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB740
	bool ChoreoTestsTrack::SetBlendOutTime(float newValue)
	{
		blendOutTime = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB840
	fight::Property* ChoreoTestsTrack::GetProperty(int index)
	{
		return gChoreoTestsTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108FB850
	void ChoreoTestsTrack::ClearProperties()
	{
		fight::FreePropertyList(&gChoreoTestsTrackProperties);
	}

	// FUNCTION: ENGINE 0x108FB920
	bool ChoreoTestsTrack::SetTestDriverCopySource(const fight::Name& newValue)
	{
		testDriverCopySource = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FBAA0
	ChoreoTestsTrack::ChoreoTestsTrack() : blendInTime(0.0f), blendOutTime(0.0f), timeBegin(0.0f), timeEnd(-1.0f), priority(0), testDriverCopy(false), testPoseDriver(false), testRandomSteer(false), testRestPoseDriver(false)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x108FBB00
	float ChoreoTestsTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108FBB10
	float ChoreoTestsTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x108FBB20
	ChoreoTestsTrack::~ChoreoTestsTrack()
	{
	}

	// FUNCTION: ENGINE 0x108FC0B0
	fight::TrackFactory* CreateChoreoTestsTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<ChoreoTestsTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108FC3A0
	void RegisterChoreoTestsTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<ChoreoTestsTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	// FUNCTION: ENGINE 0x108FCA50
	// EQUIVALENT: the engine saves the registers it uses in the entry block, before the guard's branch; ours sinks the pushes behind the branch and leaves the early exit without the pops; every other instruction is the engine's
	void ChoreoTestsTrack::RegisterProperties()
	{
		if (gChoreoTestsTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<ChoreoTestsTrack>("timeBegin", &ChoreoTestsTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<ChoreoTestsTrack>("timeEnd", &ChoreoTestsTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyBool<ChoreoTestsTrack>("testRandomSteer", &ChoreoTestsTrack::SetTestRandomSteer);
			properties[2] = property;
			property = new fight::PropertyBool<ChoreoTestsTrack>("testPoseDriver", &ChoreoTestsTrack::SetTestPoseDriver);
			properties[3] = property;
			property = new fight::PropertyBool<ChoreoTestsTrack>("testRestPoseDriver", &ChoreoTestsTrack::SetTestRestPoseDriver);
			properties[4] = property;
			property = new fight::PropertyBool<ChoreoTestsTrack>("testDriverCopy", &ChoreoTestsTrack::SetTestDriverCopy);
			properties[5] = property;
			property = new fight::PropertyName<ChoreoTestsTrack>("testDriverCopySource", &ChoreoTestsTrack::SetTestDriverCopySource);
			properties[6] = property;
			property = new fight::PropertyIntConstRange<ChoreoTestsTrack>("priority", &ChoreoTestsTrack::SetPriority);
			properties[7] = property;
			property = new fight::PropertyFloatConstRange<ChoreoTestsTrack>("blendInTime", &ChoreoTestsTrack::SetBlendInTime);
			properties[8] = property;
			property = new fight::PropertyFloatConstRange<ChoreoTestsTrack>("blendOutTime", &ChoreoTestsTrack::SetBlendOutTime);
			properties[9] = property;
			fight::RegisterPropertyList(properties, &gChoreoTestsTrackProperties);
		}
	}

	template class fight::PropertyBool<ChoreoTestsTrack>;
	template class fight::PropertyFloatConstRange<ChoreoTestsTrack>;
	template class fight::PropertyIntConstRange<ChoreoTestsTrack>;
	template class fight::PropertyName<ChoreoTestsTrack>;
	template class fight::TrackFactoryTemplate<ChoreoTestsTrack>;
	template class fight::TrackFactoryCasterTemplate<ChoreoTestsTrack>;

	// FUNCTION: ENGINE 0x109319D0
	const fight::Name* StrafeAdjustRootTrack::GetAdjustJoint() const
	{
		return &adjustJoint;
	}

	// FUNCTION: ENGINE 0x109319E0
	math::Vector StrafeAdjustRootTrack::GetOriginalDirection() const
	{
		return originalDirection;
	}

	// FUNCTION: ENGINE 0x10931A00
	float StrafeAdjustRootTrack::GetAngleAdjustRate() const
	{
		return angleAdjustRate;
	}

	// FUNCTION: ENGINE 0x10931A10
	int StrafeAdjustRootTrack::GetPriority() const
	{
		return priority;
	}

	// FUNCTION: ENGINE 0x10931A20
	float StrafeAdjustRootTrack::GetBlendInTime() const
	{
		return blendInTime;
	}

	// FUNCTION: ENGINE 0x10931A30
	float StrafeAdjustRootTrack::GetBlendOutTime() const
	{
		return blendOutTime;
	}

	// FUNCTION: ENGINE 0x10931A40
	bool ControlRootTrack::GetMovementEnabled() const
	{
		return movementEnabled;
	}

	// FUNCTION: ENGINE 0x10931A50
	float ControlRootTrack::GetMaxSpeed() const
	{
		return maxSpeed;
	}

	// FUNCTION: ENGINE 0x10931A60
	float ControlRootTrack::GetGravity() const
	{
		return gravity;
	}

	// FUNCTION: ENGINE 0x10931A70
	bool ControlRootTrack::GetSteeringEnabled() const
	{
		return steeringEnabled;
	}

	// FUNCTION: ENGINE 0x10931A80
	float ControlRootTrack::GetMaxTurnSpeed() const
	{
		return maxTurnSpeed;
	}

	// FUNCTION: ENGINE 0x10931A90
	int ControlRootTrack::GetPriority() const
	{
		return priority;
	}

	// FUNCTION: ENGINE 0x10931AA0
	float ControlRootTrack::GetBlendInTime() const
	{
		return blendInTime;
	}

	// FUNCTION: ENGINE 0x10931AB0
	float ControlRootTrack::GetBlendOutTime() const
	{
		return blendOutTime;
	}

	// FUNCTION: ENGINE 0x10931AC0
	float CharacterSteerTrack::GetAcceleration() const
	{
		return acceleration;
	}

	// FUNCTION: ENGINE 0x10931AD0
	float CharacterSteerTrack::GetTurningVelocity() const
	{
		return turningVelocity;
	}

	// FUNCTION: ENGINE 0x10931AE0
	float CharacterSteerTrack::GetVelocityWalk() const
	{
		return velocityWalk;
	}

	// FUNCTION: ENGINE 0x10931AF0
	float CharacterSteerTrack::GetVelocityRun() const
	{
		return velocityRun;
	}

	// FUNCTION: ENGINE 0x10931B00
	float CharacterSteerTrack::GetGravity() const
	{
		return gravity;
	}

	// FUNCTION: ENGINE 0x10931B10
	float CharacterSteerTrack::GetPhase() const
	{
		return phase;
	}

	// FUNCTION: ENGINE 0x10931B20
	const fight::Name* CharacterSteerTrack::GetLocomotion() const
	{
		return &locomotion;
	}

	// FUNCTION: ENGINE 0x10931B30
	const fight::Name* CharacterSteerTrack::GetAnimIdle() const
	{
		return &animIdle;
	}

	// FUNCTION: ENGINE 0x10931B40
	const fight::Name* CharacterSteerTrack::GetAnimWalk() const
	{
		return &animWalk;
	}

	// FUNCTION: ENGINE 0x10931B50
	const fight::Name* CharacterSteerTrack::GetAnimRun() const
	{
		return &animRun;
	}

	// FUNCTION: ENGINE 0x10931B60
	const fight::Name* CharacterSteerTrack::GetPartition() const
	{
		return &partition;
	}

	// FUNCTION: ENGINE 0x10931B70
	int CharacterSteerTrack::GetPriority() const
	{
		return priority;
	}

	// FUNCTION: ENGINE 0x10931B80
	float CharacterSteerTrack::GetBlendInTime() const
	{
		return blendInTime;
	}

	// FUNCTION: ENGINE 0x10931B90
	float CharacterSteerTrack::GetBlendOutTime() const
	{
		return blendOutTime;
	}

	// FUNCTION: ENGINE 0x10931BA0
	bool CharacterSteerTrack::GetDisableRootMotion() const
	{
		return disableRootMotion;
	}

	// FUNCTION: ENGINE 0x10931BB0
	bool ChoreoTestsTrack::GetTestRandomSteer() const
	{
		return testRandomSteer;
	}

	// FUNCTION: ENGINE 0x10931BC0
	bool ChoreoTestsTrack::GetTestPoseDriver() const
	{
		return testPoseDriver;
	}

	// FUNCTION: ENGINE 0x10931BD0
	bool ChoreoTestsTrack::GetTestRestPoseDriver() const
	{
		return testRestPoseDriver;
	}

	// FUNCTION: ENGINE 0x10931BE0
	bool ChoreoTestsTrack::GetTestDriverCopy() const
	{
		return testDriverCopy;
	}

	// FUNCTION: ENGINE 0x10931BF0
	const fight::Name* ChoreoTestsTrack::GetTestDriverCopySource() const
	{
		return &testDriverCopySource;
	}

	// FUNCTION: ENGINE 0x10931C00
	int ChoreoTestsTrack::GetPriority() const
	{
		return priority;
	}

	// FUNCTION: ENGINE 0x10931C10
	float ChoreoTestsTrack::GetBlendInTime() const
	{
		return blendInTime;
	}

	// FUNCTION: ENGINE 0x10931C20
	float ChoreoTestsTrack::GetBlendOutTime() const
	{
		return blendOutTime;
	}
}
