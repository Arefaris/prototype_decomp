// The fight tracks of the character limb IK and jump (unit 0x108FA5F0 - 0x108FB3F0; no assert path, file name guessed).
#include "code/engine/fight/characterik.h"

namespace engine
{
	extern fight::EnumEntry gCharacterEnableLimbIKTrackActionOnBeginTable[];
	extern fight::EnumEntry gCharacterEnableLimbIKTrackActionOnEndTable[];
	extern fight::EnumEntry gCharacterIKTrackTargetTypeTable[];

	fight::Property** gCharacterEnableLimbIKTrackProperties;  // 0x1131B30C

	// FUNCTION: ENGINE 0x108FA650
	bool CharacterEnableLimbIKTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FA660
	bool CharacterEnableLimbIKTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FA670
	bool CharacterEnableLimbIKTrack::SetActionOnBegin(int newValue)
	{
		actionOnBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FA680
	bool CharacterEnableLimbIKTrack::SetActionOnEnd(int newValue)
	{
		actionOnEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FA6B0
	fight::Property* CharacterEnableLimbIKTrack::GetProperty(int index)
	{
		return gCharacterEnableLimbIKTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108FA6C0
	void CharacterEnableLimbIKTrack::ClearProperties()
	{
		fight::FreePropertyList(&gCharacterEnableLimbIKTrackProperties);
	}

	// FUNCTION: ENGINE 0x108FA6D0
	CharacterEnableLimbIKTrack::CharacterEnableLimbIKTrack() : timeBegin(0.0f), timeEnd(0.0f), actionOnBegin(0), actionOnEnd(0)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x108FA700
	float CharacterEnableLimbIKTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108FA710
	float CharacterEnableLimbIKTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x108FA720
	CharacterEnableLimbIKTrack::~CharacterEnableLimbIKTrack()
	{
	}

	// FUNCTION: ENGINE 0x108FAB00
	fight::TrackFactory* CreateCharacterEnableLimbIKTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<CharacterEnableLimbIKTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108FAB20
	// EQUIVALENT: the engine saves the registers it uses in the entry block, before the guard's branch; ours sinks the pushes behind the branch and leaves the early exit without the pops; every other instruction is the engine's
	void CharacterEnableLimbIKTrack::RegisterProperties()
	{
		if (gCharacterEnableLimbIKTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<CharacterEnableLimbIKTrack>("timeBegin", &CharacterEnableLimbIKTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<CharacterEnableLimbIKTrack>("timeEnd", &CharacterEnableLimbIKTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyEnumConstList<CharacterEnableLimbIKTrack>("actionOnBegin", gCharacterEnableLimbIKTrackActionOnBeginTable, 0, &CharacterEnableLimbIKTrack::SetActionOnBegin);
			properties[2] = property;
			property = new fight::PropertyEnumConstList<CharacterEnableLimbIKTrack>("actionOnEnd", gCharacterEnableLimbIKTrackActionOnEndTable, 0, &CharacterEnableLimbIKTrack::SetActionOnEnd);
			properties[3] = property;
			fight::RegisterPropertyList(properties, &gCharacterEnableLimbIKTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108FAC80
	void RegisterCharacterEnableLimbIKTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<CharacterEnableLimbIKTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyEnumConstList<CharacterEnableLimbIKTrack>;
	template class fight::PropertyFloatConstRange<CharacterEnableLimbIKTrack>;
	template class fight::TrackFactoryTemplate<CharacterEnableLimbIKTrack>;
	template class fight::TrackFactoryCasterTemplate<CharacterEnableLimbIKTrack>;


	fight::Property** gCharacterIKTrackProperties;  // 0x1131B308

	// FUNCTION: ENGINE 0x108FA5F0
	bool CharacterIKTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FA600
	bool CharacterIKTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FA610
	bool CharacterIKTrack::SetTargetType(int newValue)
	{
		targetType = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FA620
	bool CharacterIKTrack::SetPriority(int newValue)
	{
		priority = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FA630
	bool CharacterIKTrack::SetBlendInTime(float newValue)
	{
		blendInTime = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FA640
	bool CharacterIKTrack::SetBlendOutTime(float newValue)
	{
		blendOutTime = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FA690
	fight::Property* CharacterIKTrack::GetProperty(int index)
	{
		return gCharacterIKTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108FA6A0
	void CharacterIKTrack::ClearProperties()
	{
		fight::FreePropertyList(&gCharacterIKTrackProperties);
	}

	// FUNCTION: ENGINE 0x108FA730
	bool CharacterIKTrack::SetRootJoint(const fight::Name& newValue)
	{
		rootJoint = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FA750
	bool CharacterIKTrack::SetMidJoint(const fight::Name& newValue)
	{
		midJoint = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FA770
	bool CharacterIKTrack::SetEndJoint(const fight::Name& newValue)
	{
		endJoint = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FA790
	CharacterIKTrack::CharacterIKTrack() : blendInTime(0.0f), blendOutTime(0.0f), timeBegin(0.0f), timeEnd(0.0f), priority(0), targetType(0)
	{
	}

	// FUNCTION: ENGINE 0x108FA7E0
	float CharacterIKTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108FA7F0
	float CharacterIKTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x108FA800
	CharacterIKTrack::~CharacterIKTrack()
	{
	}

	// FUNCTION: ENGINE 0x108FAAE0
	fight::TrackFactory* CreateCharacterIKTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<CharacterIKTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108FAC50
	void RegisterCharacterIKTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<CharacterIKTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	// FUNCTION: ENGINE 0x108FAD40
	// EQUIVALENT: the engine saves the registers it uses in the entry block, before the guard's branch; ours sinks the pushes behind the branch and leaves the early exit without the pops; every other instruction is the engine's
	void CharacterIKTrack::RegisterProperties()
	{
		if (gCharacterIKTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<CharacterIKTrack>("timeBegin", &CharacterIKTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<CharacterIKTrack>("timeEnd", &CharacterIKTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyName<CharacterIKTrack>("rootJoint", &CharacterIKTrack::SetRootJoint);
			properties[2] = property;
			property = new fight::PropertyName<CharacterIKTrack>("midJoint", &CharacterIKTrack::SetMidJoint);
			properties[3] = property;
			property = new fight::PropertyName<CharacterIKTrack>("endJoint", &CharacterIKTrack::SetEndJoint);
			properties[4] = property;
			property = new fight::PropertyEnumConstList<CharacterIKTrack>("targetType", gCharacterIKTrackTargetTypeTable, 0, &CharacterIKTrack::SetTargetType);
			properties[5] = property;
			property = new fight::PropertyIntConstRange<CharacterIKTrack>("priority", &CharacterIKTrack::SetPriority);
			properties[6] = property;
			property = new fight::PropertyFloatConstRange<CharacterIKTrack>("blendInTime", &CharacterIKTrack::SetBlendInTime);
			properties[7] = property;
			property = new fight::PropertyFloatConstRange<CharacterIKTrack>("blendOutTime", &CharacterIKTrack::SetBlendOutTime);
			properties[8] = property;
			fight::RegisterPropertyList(properties, &gCharacterIKTrackProperties);
		}
	}

	template class fight::PropertyEnumConstList<CharacterIKTrack>;
	template class fight::PropertyFloatConstRange<CharacterIKTrack>;
	template class fight::PropertyIntConstRange<CharacterIKTrack>;
	template class fight::PropertyName<CharacterIKTrack>;
	template class fight::TrackFactoryTemplate<CharacterIKTrack>;
	template class fight::TrackFactoryCasterTemplate<CharacterIKTrack>;


	fight::Property** gCharacterJumpTrackProperties;  // 0x1131B310

	// FUNCTION: ENGINE 0x108FB030
	bool CharacterJumpTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB040
	bool CharacterJumpTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB050
	bool CharacterJumpTrack::SetJumpHeight(float newValue)
	{
		jumpHeight = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB060
	bool CharacterJumpTrack::SetGravity(float newValue)
	{
		gravity = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB070
	bool CharacterJumpTrack::SetPriority(int newValue)
	{
		priority = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB080
	bool CharacterJumpTrack::SetBlendInTime(float newValue)
	{
		blendInTime = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB090
	bool CharacterJumpTrack::SetBlendOutTime(float newValue)
	{
		blendOutTime = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108FB0A0
	fight::Property* CharacterJumpTrack::GetProperty(int index)
	{
		return gCharacterJumpTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108FB0B0
	void CharacterJumpTrack::ClearProperties()
	{
		fight::FreePropertyList(&gCharacterJumpTrackProperties);
	}

	// FUNCTION: ENGINE 0x108FB0C0
	CharacterJumpTrack::CharacterJumpTrack() : blendInTime(0.0f), blendOutTime(0.0f), gravity(0.0f), jumpHeight(0.0f), timeBegin(0.0f), timeEnd(0.0f), priority(0)
	{
	}

	// FUNCTION: ENGINE 0x108FB100
	float CharacterJumpTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108FB110
	float CharacterJumpTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x108FB120
	CharacterJumpTrack::~CharacterJumpTrack()
	{
	}

	// FUNCTION: ENGINE 0x108FB230
	fight::TrackFactory* CreateCharacterJumpTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<CharacterJumpTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108FB250
	// EQUIVALENT: the engine saves the registers it uses in the entry block, before the guard's branch; ours sinks the pushes behind the branch and leaves the early exit without the pops; every other instruction is the engine's
	void CharacterJumpTrack::RegisterProperties()
	{
		if (gCharacterJumpTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<CharacterJumpTrack>("timeBegin", &CharacterJumpTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<CharacterJumpTrack>("timeEnd", &CharacterJumpTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyFloatConstRange<CharacterJumpTrack>("jumpHeight", &CharacterJumpTrack::SetJumpHeight);
			properties[2] = property;
			property = new fight::PropertyFloatConstRange<CharacterJumpTrack>("gravity", &CharacterJumpTrack::SetGravity);
			properties[3] = property;
			property = new fight::PropertyIntConstRange<CharacterJumpTrack>("priority", &CharacterJumpTrack::SetPriority);
			properties[4] = property;
			property = new fight::PropertyFloatConstRange<CharacterJumpTrack>("blendInTime", &CharacterJumpTrack::SetBlendInTime);
			properties[5] = property;
			property = new fight::PropertyFloatConstRange<CharacterJumpTrack>("blendOutTime", &CharacterJumpTrack::SetBlendOutTime);
			properties[6] = property;
			fight::RegisterPropertyList(properties, &gCharacterJumpTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108FB3F0
	void RegisterCharacterJumpTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<CharacterJumpTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyFloatConstRange<CharacterJumpTrack>;
	template class fight::PropertyIntConstRange<CharacterJumpTrack>;
	template class fight::TrackFactoryTemplate<CharacterJumpTrack>;
	template class fight::TrackFactoryCasterTemplate<CharacterJumpTrack>;

	// FUNCTION: ENGINE 0x109308E0
	const fight::Name* CharacterIKTrack::GetRootJoint() const
	{
		return &rootJoint;
	}

	// FUNCTION: ENGINE 0x109308F0
	const fight::Name* CharacterIKTrack::GetMidJoint() const
	{
		return &midJoint;
	}

	// FUNCTION: ENGINE 0x10930900
	const fight::Name* CharacterIKTrack::GetEndJoint() const
	{
		return &endJoint;
	}

	// FUNCTION: ENGINE 0x10930910
	int CharacterIKTrack::GetTargetType() const
	{
		return targetType;
	}

	// FUNCTION: ENGINE 0x10930920
	int CharacterIKTrack::GetPriority() const
	{
		return priority;
	}

	// FUNCTION: ENGINE 0x10930930
	float CharacterIKTrack::GetBlendInTime() const
	{
		return blendInTime;
	}

	// FUNCTION: ENGINE 0x10930940
	float CharacterIKTrack::GetBlendOutTime() const
	{
		return blendOutTime;
	}

	// FUNCTION: ENGINE 0x10930950
	int CharacterEnableLimbIKTrack::GetActionOnBegin() const
	{
		return actionOnBegin;
	}

	// FUNCTION: ENGINE 0x10930960
	int CharacterEnableLimbIKTrack::GetActionOnEnd() const
	{
		return actionOnEnd;
	}

	// FUNCTION: ENGINE 0x10931430
	float CharacterJumpTrack::GetJumpHeight() const
	{
		return jumpHeight;
	}

	// FUNCTION: ENGINE 0x10931440
	float CharacterJumpTrack::GetGravity() const
	{
		return gravity;
	}

	// FUNCTION: ENGINE 0x10931450
	int CharacterJumpTrack::GetPriority() const
	{
		return priority;
	}

	// FUNCTION: ENGINE 0x10931460
	float CharacterJumpTrack::GetBlendInTime() const
	{
		return blendInTime;
	}

	// FUNCTION: ENGINE 0x10931470
	float CharacterJumpTrack::GetBlendOutTime() const
	{
		return blendOutTime;
	}
}
