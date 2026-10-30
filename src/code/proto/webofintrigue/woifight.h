// The fight condition and tracks of the web of intrigue (RTTI proto::IsWOITargetCondition, proto::WOIFMVTrack,
// proto::WOISendEventTrack, proto::WOIShowTargetNameTrack and proto::WOIPlayReactionTrack with their actions). Unit
// 0x10563630 - 0x10565930 (no assert path; the file name is a guess). The class names are original, the members are
// guessed from what the actions use.
#ifndef PROTO_WEBOFINTRIGUE_WOIFIGHT_H
#define PROTO_WEBOFINTRIGUE_WOIFIGHT_H

#include "code/container/string.h"
#include "code/core/linklist.h"
#include "code/engine/fight/effecttrack.h"
#include "code/engine/fight/trackfactory.h"
#include "code/engine/gameobject/gameobjecthandle.h"

namespace proto
{
	// The condition: whether the object the condition is evaluated for is a target of the web of intrigue
	class IsWOITargetCondition : public fight::Condition
	{
	public:
		// 0x10564530
		IsWOITargetCondition();
		virtual ~IsWOITargetCondition();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual bool Evaluate(int a, int b, int c, int d);

		// The member the property writes
		bool SetIsWOITarget(bool value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		bool isWOITarget;  // +0xC
	};

	extern fight::Property** gIsWOITargetConditionProperties;
	fight::ConditionFactory* CreateIsWOITargetConditionFactory(const char* name);
	void RegisterIsWOITargetConditionFactory(fight::TrackRegistry* registry, const char* name);

	// Plays the movie of a node of the web of intrigue
	class WOIFMVTrack : public fight::Track
	{
	public:
		// 0x105645C0
		WOIFMVTrack();
		virtual ~WOIFMVTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetEndInBlack(bool value);
		bool SetFadeUpToBlack(bool value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float timeBegin;  // +0x10
		float timeEnd;  // +0x14
		bool endInBlack;  // +0x18
		bool fadeUpToBlack;  // +0x19
	};

	extern fight::Property** gWOIFMVTrackProperties;
	fight::TrackFactory* CreateWOIFMVTrackFactory(const char* name);
	void RegisterWOIFMVTrackFactory(fight::TrackRegistry* registry, const char* name);

	// The action of the movie track: plays the movie of the node the owner stands for
	class WOIFMVAction : public fight::Action
	{
	public:
		// 0x105639E0
		WOIFMVAction(WOIFMVTrack* newTrack, core::IRefCount* newOwner);
		virtual ~WOIFMVAction();

		// vftable slot 5 (0x10563A90), 6 (0x10563380) and 7 (0x10563350)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();
		virtual bool Slot7(int arg, float value);

		core::Link<WOIFMVTrack> link;  // +0x1C
		core::IRefCount* owner;  // +0x28
		container::StringC<64> path;  // +0x2C
		bool unknown70;
	};

	// Sends the scenario and front end events of a node
	class WOISendEventTrack : public fight::Track
	{
	public:
		// 0x10564660
		WOISendEventTrack();
		virtual ~WOISendEventTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetToScenario(bool value);
		bool SetToFrontend(bool value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float timeBegin;  // +0x10
		bool toFrontend;  // +0x14
		bool toScenario;  // +0x15
	};

	extern fight::Property** gWOISendEventTrackProperties;
	fight::TrackFactory* CreateWOISendEventTrackFactory(const char* name);
	void RegisterWOISendEventTrackFactory(fight::TrackRegistry* registry, const char* name);

	class WOISendEventAction : public fight::Action
	{
	public:
		// 0x10563BF0
		WOISendEventAction(WOISendEventTrack* newTrack, core::IRefCount* newOwner);
		virtual ~WOISendEventAction();

		// vftable slot 5 (0x10563CA0)
		virtual bool Slot5(int arg, float value);

		core::IRefCount* owner;  // +0x1C
		core::Link<WOISendEventTrack> link;  // +0x20
	};

	// Shows the name of a target of the web of intrigue
	class WOIShowTargetNameTrack : public fight::Track
	{
	public:
		// 0x10564770
		WOIShowTargetNameTrack();
		virtual ~WOIShowTargetNameTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetTargetGrabSlot(const fight::Name& value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name targetGrabSlot;  // +0x10
		float timeBegin;  // +0x18
		float timeEnd;  // +0x1C
	};

	extern fight::Property** gWOIShowTargetNameTrackProperties;
	fight::TrackFactory* CreateWOIShowTargetNameTrackFactory(const char* name);
	void RegisterWOIShowTargetNameTrackFactory(fight::TrackRegistry* registry, const char* name);

	class WOIShowTargetNameAction : public fight::Action
	{
	public:
		// 0x10564020
		WOIShowTargetNameAction(engine::GameObjectHandle newTarget, WOIShowTargetNameTrack* newTrack,
			core::IRefCount* newListener);
		virtual ~WOIShowTargetNameAction();

		// vftable slot 5 (0x105640E0) and 6 (0x105633A0)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();

		engine::GameObjectHandle target;  // +0x1C
		core::Link<WOIShowTargetNameTrack> link;  // +0x20
		core::IRefCount* listener;  // +0x2C
	};

	// Plays the reaction of a target of the web of intrigue
	class WOIPlayReactionTrack : public fight::Track
	{
	public:
		// 0x10564850
		WOIPlayReactionTrack();
		virtual ~WOIPlayReactionTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTargetGrabSlot(const fight::Name& value);
		fight::BranchHolder* GetWOIBranch();
		bool SetPriority(int value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::BranchHolder woiBranch;  // +0x10
		int unknown34;
		fight::Name targetGrabSlot;  // +0x38
		float timeBegin;  // +0x40
		int priority;  // +0x44
	};

	extern fight::Property** gWOIPlayReactionTrackProperties;
	fight::TrackFactory* CreateWOIPlayReactionTrackFactory(const char* name);
	void RegisterWOIPlayReactionTrackFactory(fight::TrackRegistry* registry, const char* name);

	class WOIPlayReactionAction : public fight::Action
	{
	public:
		// 0x10563D30
		WOIPlayReactionAction(engine::GameObjectHandle newTarget, core::IRefCount* newEffect,
			WOIPlayReactionTrack* newTrack);
		virtual ~WOIPlayReactionAction();

		// vftable slot 5 (0x10563DE0) and 6 (0x10563EE0)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();

		engine::GameObjectHandle target;  // +0x1C
		core::IRefCount* effect;  // +0x20
		core::Link<WOIPlayReactionTrack> link;  // +0x24
		int node;  // +0x30
	};
}

#endif
