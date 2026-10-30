#include "code/proto/webofintrigue/woifight.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/fight/lodactions.h"
#include "code/proto/webofintrigue/webofintriguemanager.h"

namespace proto
{
	fight::Property** gIsWOITargetConditionProperties;  // 0x11273084
	fight::Property** gWOIShowTargetNameTrackProperties;  // 0x11273088
	fight::Property** gWOIFMVTrackProperties;  // 0x1127308C
	fight::Property** gWOISendEventTrackProperties;  // 0x11273090
	fight::Property** gWOIPlayReactionTrackProperties;  // 0x11273094

	// FUNCTION: ENGINE 0x10563630
	// EQUIVALENT: register allocation (the handle and the table pointer use eax and ecx the other way round, the result
	// is set through cl and copied; 69.8 %)
	bool IsWOITargetCondition::Evaluate(int a, int b, int c, int d)
	{
		engine::GameObjectHandle handle = engine::GetObjectHandle((core::IRefCount*)c);
		if (!handle.IsValid())
		{
			return false;
		}
		bool found = gWebOfIntrigueManager->FindNode(handle) != 0;
		return isWOITarget == found;
	}

	// FUNCTION: ENGINE 0x105643D0
	bool IsWOITargetCondition::SetIsWOITarget(bool value)
	{
		isWOITarget = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10564500
	fight::Property* IsWOITargetCondition::GetProperty(int index)
	{
		return gIsWOITargetConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x10564520
	void IsWOITargetCondition::ClearProperties()
	{
		fight::FreePropertyList(&gIsWOITargetConditionProperties);
	}

	// FUNCTION: ENGINE 0x10564530
	IsWOITargetCondition::IsWOITargetCondition() : fight::Condition(0), isWOITarget(true)
	{
	}

	// FUNCTION: ENGINE 0x10564550
	IsWOITargetCondition::~IsWOITargetCondition()
	{
	}

	// FUNCTION: ENGINE 0x10564F00
	// EQUIVALENT: shrink-wrap (the engine saves esi in the entry block, before the guard's branch; ours sinks the push
	// behind it)
	void IsWOITargetCondition::RegisterProperties()
	{
		if (gIsWOITargetConditionProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyBool<IsWOITargetCondition>("isWOITarget", &IsWOITargetCondition::SetIsWOITarget);
			properties[0] = property;
			fight::RegisterPropertyList(properties, &gIsWOITargetConditionProperties);
		}
	}

	// FUNCTION: ENGINE 0x10564E10
	fight::ConditionFactory* CreateIsWOITargetConditionFactory(const char* name)
	{
		fight::ConditionFactoryCasterTemplate<IsWOITargetCondition> caster;
		return fight::FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x10565200
	void RegisterIsWOITargetConditionFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::ConditionFactoryCasterTemplate<IsWOITargetCondition> caster;
		registry->AddFactory(fight::FindConditionFactory(name, &caster));
	}

	template class fight::PropertyBool<IsWOITargetCondition>;
	template class fight::ConditionFactoryTemplate<IsWOITargetCondition>;
	template class fight::ConditionFactoryCasterTemplate<IsWOITargetCondition>;

	// FUNCTION: ENGINE 0x10564420
	bool WOIFMVTrack::SetTimeBegin(float value)
	{
		timeBegin = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10564440
	bool WOIFMVTrack::SetTimeEnd(float value)
	{
		timeEnd = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10564460
	bool WOIFMVTrack::SetEndInBlack(bool value)
	{
		endInBlack = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10564470
	bool WOIFMVTrack::SetFadeUpToBlack(bool value)
	{
		fadeUpToBlack = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10564590
	fight::Property* WOIFMVTrack::GetProperty(int index)
	{
		return gWOIFMVTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x105645B0
	void WOIFMVTrack::ClearProperties()
	{
		fight::FreePropertyList(&gWOIFMVTrackProperties);
	}

	// FUNCTION: ENGINE 0x105645C0
	WOIFMVTrack::WOIFMVTrack() : timeBegin(0.0f), timeEnd(-1.0f), endInBlack(false), fadeUpToBlack(false)
	{
	}

	// FUNCTION: ENGINE 0x10564600
	float WOIFMVTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x10564610
	float WOIFMVTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x10564620
	WOIFMVTrack::~WOIFMVTrack()
	{
	}

	// FUNCTION: ENGINE 0x105642B0
	fight::Action* WOIFMVTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		return new WOIFMVAction(this, owner);
	}

	// FUNCTION: ENGINE 0x10564FA0
	// EQUIVALENT: shrink-wrap (the engine saves esi in the entry block, before the guard's branch; ours sinks the push
	// behind it)
	void WOIFMVTrack::RegisterProperties()
	{
		if (gWOIFMVTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<WOIFMVTrack>("timeBegin", &WOIFMVTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<WOIFMVTrack>("timeEnd", &WOIFMVTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyBool<WOIFMVTrack>("endInBlack", &WOIFMVTrack::SetEndInBlack);
			properties[2] = property;
			property = new fight::PropertyBool<WOIFMVTrack>("fadeUpToBlack", &WOIFMVTrack::SetFadeUpToBlack);
			properties[3] = property;
			fight::RegisterPropertyList(properties, &gWOIFMVTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x10564E70
	fight::TrackFactory* CreateWOIFMVTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<WOIFMVTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x10565260
	void RegisterWOIFMVTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<WOIFMVTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyBool<WOIFMVTrack>;
	template class fight::PropertyFloatConstRange<WOIFMVTrack>;
	template class fight::TrackFactoryTemplate<WOIFMVTrack>;
	template class fight::TrackFactoryCasterTemplate<WOIFMVTrack>;

	// FUNCTION: ENGINE 0x105639E0
	WOIFMVAction::WOIFMVAction(WOIFMVTrack* newTrack, core::IRefCount* newOwner) : fight::Action(0xE00), link(newTrack),
		owner(0), unknown70(false)
	{
		engine::AssignRefCounted(&owner, newOwner);
	}

	// FUNCTION: ENGINE 0x105636D0
	WOIFMVAction::~WOIFMVAction()
	{
		core::SafeReleaseRef(owner);
	}

	// FUNCTION: ENGINE 0x10564480
	bool WOISendEventTrack::SetTimeBegin(float value)
	{
		timeBegin = value;
		return true;
	}

	// FUNCTION: ENGINE 0x105644A0
	bool WOISendEventTrack::SetToScenario(bool value)
	{
		toScenario = value;
		return true;
	}

	// FUNCTION: ENGINE 0x105644B0
	bool WOISendEventTrack::SetToFrontend(bool value)
	{
		toFrontend = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10564630
	fight::Property* WOISendEventTrack::GetProperty(int index)
	{
		return gWOISendEventTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x10564650
	void WOISendEventTrack::ClearProperties()
	{
		fight::FreePropertyList(&gWOISendEventTrackProperties);
	}

	// FUNCTION: ENGINE 0x10564660
	WOISendEventTrack::WOISendEventTrack() : toFrontend(true), toScenario(true), timeBegin(0.0f)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x105646A0
	float WOISendEventTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x105646B0
	float WOISendEventTrack::Slot10() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x105646C0
	WOISendEventTrack::~WOISendEventTrack()
	{
	}

	// FUNCTION: ENGINE 0x105642F0
	fight::Action* WOISendEventTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		return new WOISendEventAction(this, owner);
	}

	// FUNCTION: ENGINE 0x105650F0
	// EQUIVALENT: shrink-wrap (the engine saves esi in the entry block, before the guard's branch; ours sinks the push
	// behind it)
	void WOISendEventTrack::RegisterProperties()
	{
		if (gWOISendEventTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<WOISendEventTrack>("timeBegin", &WOISendEventTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyBool<WOISendEventTrack>("toScenario", &WOISendEventTrack::SetToScenario);
			properties[1] = property;
			property = new fight::PropertyBool<WOISendEventTrack>("toFrontend", &WOISendEventTrack::SetToFrontend);
			properties[2] = property;
			fight::RegisterPropertyList(properties, &gWOISendEventTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x10564EA0
	fight::TrackFactory* CreateWOISendEventTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<WOISendEventTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x10565290
	void RegisterWOISendEventTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<WOISendEventTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyBool<WOISendEventTrack>;
	template class fight::PropertyFloatConstRange<WOISendEventTrack>;
	template class fight::TrackFactoryTemplate<WOISendEventTrack>;
	template class fight::TrackFactoryCasterTemplate<WOISendEventTrack>;

	// FUNCTION: ENGINE 0x10563BF0
	WOISendEventAction::WOISendEventAction(WOISendEventTrack* newTrack, core::IRefCount* newOwner) : fight::Action(0xE00),
		owner(0), link(newTrack)
	{
		engine::AssignRefCounted(&owner, newOwner);
	}

	// FUNCTION: ENGINE 0x10563740
	WOISendEventAction::~WOISendEventAction()
	{
		core::SafeReleaseRef(owner);
	}

	// FUNCTION: ENGINE 0x105643E0
	bool WOIShowTargetNameTrack::SetTimeBegin(float value)
	{
		timeBegin = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10564400
	bool WOIShowTargetNameTrack::SetTimeEnd(float value)
	{
		timeEnd = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10564700
	bool WOIShowTargetNameTrack::SetTargetGrabSlot(const fight::Name& value)
	{
		targetGrabSlot = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10564560
	fight::Property* WOIShowTargetNameTrack::GetProperty(int index)
	{
		return gWOIShowTargetNameTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x10564580
	void WOIShowTargetNameTrack::ClearProperties()
	{
		fight::FreePropertyList(&gWOIShowTargetNameTrackProperties);
	}

	// FUNCTION: ENGINE 0x10564770
	WOIShowTargetNameTrack::WOIShowTargetNameTrack() : timeBegin(0.0f), timeEnd(-1.0f)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x105647C0
	float WOIShowTargetNameTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x105647D0
	float WOIShowTargetNameTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x105647E0
	WOIShowTargetNameTrack::~WOIShowTargetNameTrack()
	{
	}

	// FUNCTION: ENGINE 0x10564380
	fight::Action* WOIShowTargetNameTrack::CreateAction(fight::Track* listener, core::IRefCount* effect,
		core::IRefCount* owner)
	{
		engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
		return new WOIShowTargetNameAction(handle, this, owner);
	}

	// FUNCTION: ENGINE 0x105654A0
	// EQUIVALENT: shrink-wrap (the engine saves esi in the entry block, before the guard's branch; ours sinks the push
	// behind it)
	void WOIShowTargetNameTrack::RegisterProperties()
	{
		if (gWOIShowTargetNameTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<WOIShowTargetNameTrack>("timeBegin",
				&WOIShowTargetNameTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<WOIShowTargetNameTrack>("timeEnd",
				&WOIShowTargetNameTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyNameList<WOIShowTargetNameTrack>("targetGrabSlot",
				&WOIShowTargetNameTrack::SetTargetGrabSlot);
			properties[2] = property;
			fight::RegisterPropertyList(properties, &gWOIShowTargetNameTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x10564E40
	fight::TrackFactory* CreateWOIShowTargetNameTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<WOIShowTargetNameTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x10565230
	void RegisterWOIShowTargetNameTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<WOIShowTargetNameTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyFloatConstRange<WOIShowTargetNameTrack>;
	template class fight::PropertyNameList<WOIShowTargetNameTrack>;
	template class fight::TrackFactoryTemplate<WOIShowTargetNameTrack>;
	template class fight::TrackFactoryCasterTemplate<WOIShowTargetNameTrack>;

	// FUNCTION: ENGINE 0x10564020
	WOIShowTargetNameAction::WOIShowTargetNameAction(engine::GameObjectHandle newTarget, WOIShowTargetNameTrack* newTrack,
		core::IRefCount* newListener) : fight::Action(0x600), target(newTarget), link(newTrack), listener(0)
	{
		engine::AssignRefCounted(&listener, newListener);
	}

	// FUNCTION: ENGINE 0x105637F0
	WOIShowTargetNameAction::~WOIShowTargetNameAction()
	{
		core::SafeReleaseRef(listener);
	}

	// FUNCTION: ENGINE 0x105644C0
	bool WOIPlayReactionTrack::SetTimeBegin(float value)
	{
		timeBegin = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10564720
	bool WOIPlayReactionTrack::SetTargetGrabSlot(const fight::Name& value)
	{
		targetGrabSlot = value;
		return true;
	}

	// FUNCTION: ENGINE 0x105644E0
	fight::BranchHolder* WOIPlayReactionTrack::GetWOIBranch()
	{
		return &woiBranch;
	}

	// FUNCTION: ENGINE 0x105644F0
	bool WOIPlayReactionTrack::SetPriority(int value)
	{
		priority = value;
		return true;
	}

	// FUNCTION: ENGINE 0x105646D0
	fight::Property* WOIPlayReactionTrack::GetProperty(int index)
	{
		return gWOIPlayReactionTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x105646F0
	void WOIPlayReactionTrack::ClearProperties()
	{
		fight::FreePropertyList(&gWOIPlayReactionTrackProperties);
	}

	// FUNCTION: ENGINE 0x10564850
	WOIPlayReactionTrack::WOIPlayReactionTrack() : woiBranch(0), timeBegin(0.0f), priority(-5)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x105648A0
	float WOIPlayReactionTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x105648B0
	float WOIPlayReactionTrack::Slot10() const
	{
		return -1.0f;
	}

	// FUNCTION: ENGINE 0x105648C0
	WOIPlayReactionTrack::~WOIPlayReactionTrack()
	{
	}

	// FUNCTION: ENGINE 0x10564330
	fight::Action* WOIPlayReactionTrack::CreateAction(fight::Track* listener, core::IRefCount* effect,
		core::IRefCount* owner)
	{
		engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
		return new WOIPlayReactionAction(handle, effect, this);
	}

	// FUNCTION: ENGINE 0x105655B0
	// EQUIVALENT: shrink-wrap (the engine saves esi in the entry block, before the guard's branch; ours sinks the push
	// behind it)
	void WOIPlayReactionTrack::RegisterProperties()
	{
		if (gWOIPlayReactionTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<WOIPlayReactionTrack>("timeBegin",
				&WOIPlayReactionTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyNameList<WOIPlayReactionTrack>("targetGrabSlot",
				&WOIPlayReactionTrack::SetTargetGrabSlot);
			properties[1] = property;
			property = new fight::PropertyBranch<WOIPlayReactionTrack>("woiBranch", &WOIPlayReactionTrack::GetWOIBranch);
			properties[2] = property;
			property = new fight::PropertyIntConstRange<WOIPlayReactionTrack>("priority", &WOIPlayReactionTrack::SetPriority);
			properties[3] = property;
			fight::RegisterPropertyList(properties, &gWOIPlayReactionTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x10564ED0
	fight::TrackFactory* CreateWOIPlayReactionTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<WOIPlayReactionTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x105652C0
	void RegisterWOIPlayReactionTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<WOIPlayReactionTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyBranch<WOIPlayReactionTrack>;
	template class fight::PropertyFloatConstRange<WOIPlayReactionTrack>;
	template class fight::PropertyIntConstRange<WOIPlayReactionTrack>;
	template class fight::PropertyNameList<WOIPlayReactionTrack>;
	template class fight::TrackFactoryTemplate<WOIPlayReactionTrack>;
	template class fight::TrackFactoryCasterTemplate<WOIPlayReactionTrack>;

	// FUNCTION: ENGINE 0x10563D30
	WOIPlayReactionAction::WOIPlayReactionAction(engine::GameObjectHandle newTarget, core::IRefCount* newEffect,
		WOIPlayReactionTrack* newTrack) : fight::Action(0x600), target(newTarget), effect(newEffect), link(newTrack),
		node(-1)
	{
	}

	// FUNCTION: ENGINE 0x105637A0
	WOIPlayReactionAction::~WOIPlayReactionAction()
	{
	}
}

// Kept copies (template instances and wrappers of this unit):
// FUNCTION: ENGINE 0x105636B0
// FUNCTION: ENGINE 0x10563720
// FUNCTION: ENGINE 0x10563780
// FUNCTION: ENGINE 0x105637D0
// FUNCTION: ENGINE 0x10563830
// FUNCTION: ENGINE 0x10563890
// FUNCTION: ENGINE 0x10563900
// FUNCTION: ENGINE 0x10563970
// FUNCTION: ENGINE 0x10563A60
// FUNCTION: ENGINE 0x10563C70
// FUNCTION: ENGINE 0x10563DB0
// FUNCTION: ENGINE 0x105640B0
// FUNCTION: ENGINE 0x10564740
// FUNCTION: ENGINE 0x105647F0
// FUNCTION: ENGINE 0x10564820
// FUNCTION: ENGINE 0x105648E0
// FUNCTION: ENGINE 0x105648F0
// FUNCTION: ENGINE 0x10564920
// FUNCTION: ENGINE 0x10564930
// FUNCTION: ENGINE 0x10564960
// FUNCTION: ENGINE 0x10564970
// FUNCTION: ENGINE 0x105649A0
// FUNCTION: ENGINE 0x105649B0
// FUNCTION: ENGINE 0x105649E0
// FUNCTION: ENGINE 0x105649F0
// FUNCTION: ENGINE 0x10564A20
// FUNCTION: ENGINE 0x10564A50
// FUNCTION: ENGINE 0x10564A80
// FUNCTION: ENGINE 0x10564AB0
// FUNCTION: ENGINE 0x10564AD0
// FUNCTION: ENGINE 0x10564AE0
// FUNCTION: ENGINE 0x10564B10
// FUNCTION: ENGINE 0x10564B40
// FUNCTION: ENGINE 0x10564B50
// FUNCTION: ENGINE 0x10564B80
// FUNCTION: ENGINE 0x10564BB0
// FUNCTION: ENGINE 0x10564BC0
// FUNCTION: ENGINE 0x10564BF0
// FUNCTION: ENGINE 0x10564C10
// FUNCTION: ENGINE 0x10564C20
// FUNCTION: ENGINE 0x10564C50
// FUNCTION: ENGINE 0x10564C80
// FUNCTION: ENGINE 0x10564C90
// FUNCTION: ENGINE 0x10564CC0
// FUNCTION: ENGINE 0x10564CE0
// FUNCTION: ENGINE 0x10564CF0
// FUNCTION: ENGINE 0x10564D20
// FUNCTION: ENGINE 0x10564D50
// FUNCTION: ENGINE 0x10564D60
// FUNCTION: ENGINE 0x10564D90
// FUNCTION: ENGINE 0x10564DB0
// FUNCTION: ENGINE 0x10564DE0
// FUNCTION: ENGINE 0x10564E00
// FUNCTION: ENGINE 0x105652F0
// FUNCTION: ENGINE 0x10565320
// FUNCTION: ENGINE 0x10565340
// FUNCTION: ENGINE 0x10565350
// FUNCTION: ENGINE 0x10565380
// FUNCTION: ENGINE 0x105653A0
// FUNCTION: ENGINE 0x105653B0
// FUNCTION: ENGINE 0x105653E0
// FUNCTION: ENGINE 0x10565400
// FUNCTION: ENGINE 0x10565430
// FUNCTION: ENGINE 0x10565450
// FUNCTION: ENGINE 0x10565480
// FUNCTION: ENGINE 0x10565700
// FUNCTION: ENGINE 0x10565750
// FUNCTION: ENGINE 0x105657A0
// FUNCTION: ENGINE 0x105657F0
// FUNCTION: ENGINE 0x10565820
// FUNCTION: ENGINE 0x10565840
// FUNCTION: ENGINE 0x10565870
// FUNCTION: ENGINE 0x10565890
// FUNCTION: ENGINE 0x105658E0
// FUNCTION: ENGINE 0x105659D0
