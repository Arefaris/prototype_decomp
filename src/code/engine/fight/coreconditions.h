// The conditions of the fight core itself: the sequencer conditions and the random, print, platform and logic
// conditions (RTTI namespace fight). Part of the unit 0x105A2440 - 0x105B3F00 (no assert path; file name guessed).
#ifndef ENGINE_FIGHT_CORECONDITIONS_H
#define ENGINE_FIGHT_CORECONDITIONS_H

#include "code/engine/fight/trackfactory.h"

namespace engine
{
	// The operator tables other units define: two values for equality, six for ordering
	extern fight::EnumEntry gEqualityOperatorTable[];
	extern const int gEqualityOperatorCount;
	extern fight::EnumEntry gCompareOperatorTable[];
	extern const int gCompareOperatorCount;
}

namespace fight
{
	// RTTI: fight::SequencerBranchCondition (10 vftable slots, 0x38 bytes): compares the state of a branch's sequencer
	class SequencerBranchCondition : public Condition
	{
	public:
		// 0x105ADBE0
		SequencerBranchCondition();
		virtual ~SequencerBranchCondition();

		// vftable slot 0
		virtual Property* GetProperty(int index);
		// vftable slot 9 (another unit)
		virtual bool Evaluate(int a, int b, int c, int d);

		// The members the properties write
		bool SetCompare(int value);
		BranchHolder* GetBranch();
		bool SetRecurse(bool value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		BranchHolder branch;  // +0xC
		int compare;  // +0x30
		bool recurse;  // +0x34
	};

	extern Property** gSequencerBranchConditionProperties;

	// RTTI: fight::SequencerIsBusyCondition (10 vftable slots, 0x10 bytes)
	class SequencerIsBusyCondition : public Condition
	{
	public:
		// 0x105ADC50
		SequencerIsBusyCondition();
		virtual ~SequencerIsBusyCondition();

		// vftable slot 0
		virtual Property* GetProperty(int index);
		// vftable slot 9 (another unit)
		virtual bool Evaluate(int a, int b, int c, int d);

		// The members the properties write
		bool SetMatch(bool value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		bool match;  // +0xC
	};

	extern Property** gSequencerIsBusyConditionProperties;

	// RTTI: fight::SequencerTimeCondition (10 vftable slots, 0x14 bytes)
	class SequencerTimeCondition : public Condition
	{
	public:
		// 0x105ADCA0
		SequencerTimeCondition();
		virtual ~SequencerTimeCondition();

		// vftable slot 0
		virtual Property* GetProperty(int index);
		// vftable slot 9 (another unit)
		virtual bool Evaluate(int a, int b, int c, int d);

		// The members the properties write
		bool SetCompare(int value);
		bool SetTime(float value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float time;  // +0xC
		int compare;  // +0x10
	};

	extern Property** gSequencerTimeConditionProperties;

	// 0x105AE040 / 0x105AE060 / 0x105AE080 and the registrations 0x105AE2D0 / 0x105AE300 / 0x105AE330
	ConditionFactory* CreateSequencerBranchConditionFactory(const char* name);
	ConditionFactory* CreateSequencerIsBusyConditionFactory(const char* name);
	ConditionFactory* CreateSequencerTimeConditionFactory(const char* name);
	void RegisterSequencerBranchConditionFactory(TrackRegistry* registry, const char* name);
	void RegisterSequencerIsBusyConditionFactory(TrackRegistry* registry, const char* name);
	void RegisterSequencerTimeConditionFactory(TrackRegistry* registry, const char* name);
}

namespace fight
{
	// Each of these is a condition or track of the fight core with the usual members (a constructor, a destructor, a
	// property list with its accessor and clear function, the setters the properties call); the slot 9 (Evaluate)
	// bodies belong to another unit.

	// RTTI: fight::RandomCondition (10 vftable slots, 0x10 bytes)
	class RandomCondition : public Condition
	{
	public:
		// 0x105AE550
		RandomCondition();
		virtual ~RandomCondition();

		virtual Property* GetProperty(int index);
		virtual bool Evaluate(int a, int b, int c, int d);

		bool SetWeight(float value);

		static void RegisterProperties();
		static void ClearProperties();

		float weight;  // +0xC
	};

	extern Property** gRandomConditionProperties;

	// RTTI: fight::MaybeCondition (10 vftable slots, 0x10 bytes)
	class MaybeCondition : public Condition
	{
	public:
		// 0x105AE5A0
		MaybeCondition();
		virtual ~MaybeCondition();

		virtual Property* GetProperty(int index);
		virtual bool Evaluate(int a, int b, int c, int d);

		bool SetPercent(float value);

		static void RegisterProperties();
		static void ClearProperties();

		float percent;  // +0xC
	};

	extern Property** gMaybeConditionProperties;

	// RTTI: fight::PrintCondition (10 vftable slots, 0x14 bytes)
	class PrintCondition : public Condition
	{
	public:
		// 0x105AEA20
		PrintCondition();
		virtual ~PrintCondition();

		virtual Property* GetProperty(int index);
		virtual bool Evaluate(int a, int b, int c, int d);

		bool SetChannel(const char* value);
		bool SetText(const char* value);

		static void RegisterProperties();
		static void ClearProperties();

		char* channel;  // +0xC
		char* text;  // +0x10
	};

	extern Property** gPrintConditionProperties;

	// RTTI: fight::PrintTrack (16 vftable slots, 0x1C bytes)
	class PrintTrack : public Track
	{
	public:
		// 0x105AEAE0
		PrintTrack();
		virtual ~PrintTrack();

		virtual Property* GetProperty(int index);
		virtual float GetTimeBegin() const;
		virtual float Slot10() const;
		virtual Action* CreateAction(Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		bool SetTimeBegin(float value);
		bool SetChannel(const char* value);
		bool SetText(const char* value);

		static void RegisterProperties();
		static void ClearProperties();

		char* channel;  // +0x10
		char* text;  // +0x14
		float timeBegin;  // +0x18
	};

	extern Property** gPrintTrackProperties;

	// RTTI: fight::PlatformCondition (10 vftable slots, 0x14 bytes): which platforms the condition holds on
	class PlatformCondition : public Condition
	{
	public:
		// 0x105AF120
		PlatformCondition();
		virtual ~PlatformCondition();

		virtual Property* GetProperty(int index);
		virtual bool Evaluate(int a, int b, int c, int d);

		bool SetPS2(bool value);
		bool SetXBox(bool value);
		bool SetGameCube(bool value);
		bool SetWin32(bool value);
		bool SetXenon(bool value);
		bool SetPS3(bool value);

		static void RegisterProperties();
		static void ClearProperties();

		bool gameCube;  // +0xC
		bool pS2;  // +0xD
		bool pS3;  // +0xE
		bool win32;  // +0xF
		bool xBox;  // +0x10
		bool xenon;  // +0x11
	};

	extern Property** gPlatformConditionProperties;

	// RTTI: fight::NotCondition (10 vftable slots, 0xC bytes): the operator of a condition group
	class NotCondition : public Condition
	{
	public:
		// 0x105AF520
		NotCondition();
		virtual ~NotCondition();

		virtual Property* GetProperty(int index);
		virtual bool Evaluate(int a, int b, int c, int d);

		static void RegisterProperties();
		static void ClearProperties();
	};

	extern Property** gNotConditionProperties;

	// RTTI: fight::OrCondition (10 vftable slots, 0xC bytes)
	class OrCondition : public Condition
	{
	public:
		// 0x105AF5C0
		OrCondition();
		virtual ~OrCondition();

		virtual Property* GetProperty(int index);
		virtual bool Evaluate(int a, int b, int c, int d);

		static void RegisterProperties();
		static void ClearProperties();
	};

	extern Property** gOrConditionProperties;

	// RTTI: fight::ConditionGroupCondition (10 vftable slots, 0x10 bytes)
	class ConditionGroupCondition : public Condition
	{
	public:
		// 0x105AF610
		ConditionGroupCondition();
		virtual ~ConditionGroupCondition();

		virtual Property* GetProperty(int index);
		virtual bool Evaluate(int a, int b, int c, int d);

		ConditionList* GetConditions();

		static void RegisterProperties();
		static void ClearProperties();

		ConditionList conditions;  // +0xC
	};

	extern Property** gConditionGroupConditionProperties;

	// RTTI: fight::TrackGroupTrack (16 vftable slots, 0x28 bytes): a named group of tracks
	class TrackGroupTrack : public Track
	{
	public:
		// 0x105AF6F0
		TrackGroupTrack();
		virtual ~TrackGroupTrack();

		virtual Property* GetProperty(int index);
		virtual float GetTimeBegin() const;
		virtual float Slot10() const;
		virtual Action* CreateAction(Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		bool SetGroupName(const Name& value);
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		ConditionList* GetConditions();
		TrackGroup* GetTracks();

		static void RegisterProperties();
		static void ClearProperties();

		Name groupName;  // +0x10
		ConditionList conditions;  // +0x18
		TrackGroup tracks;  // +0x1C
		float timeBegin;  // +0x20
		float timeEnd;  // +0x24
	};

	extern Property** gTrackGroupTrackProperties;

	// RTTI: fight::FalseCondition (10 vftable slots, 0xC bytes)
	class FalseCondition : public Condition
	{
	public:
		// 0x105AFF70
		FalseCondition();
		virtual ~FalseCondition();

		virtual Property* GetProperty(int index);
		virtual bool Evaluate(int a, int b, int c, int d);

		static void RegisterProperties();
		static void ClearProperties();
	};

	extern Property** gFalseConditionProperties;

	// RTTI: fight::DebugCondition (10 vftable slots, 0x14 bytes)
	class DebugCondition : public Condition
	{
	public:
		// 0x105B0120
		DebugCondition();
		virtual ~DebugCondition();

		virtual Property* GetProperty(int index);
		virtual bool Evaluate(int a, int b, int c, int d);

		bool SetCompare(int value);
		bool SetMode(int value);
		// 0x105B2760 / 0x105B2770 (the editor's getters)
		int GetCompare() const;
		int GetMode() const;

		static void RegisterProperties();
		static void ClearProperties();

		int compare;  // +0xC
		int mode;  // +0x10
	};

	extern Property** gDebugConditionProperties;
	extern EnumEntry gDebugConditionModeTable[];
	extern const int gDebugConditionModeCount;

	// RTTI: fight::CommentCondition (10 vftable slots, 0x10 bytes)
	class CommentCondition : public Condition
	{
	public:
		// 0x105B0420
		CommentCondition();
		virtual ~CommentCondition();

		virtual Property* GetProperty(int index);
		virtual bool Evaluate(int a, int b, int c, int d);

		bool SetText(const char* value);

		static void RegisterProperties();
		static void ClearProperties();

		char* text;  // +0xC
	};

	extern Property** gCommentConditionProperties;

	// RTTI: fight::CommentTrack (16 vftable slots, 0x14 bytes)
	class CommentTrack : public Track
	{
	public:
		// 0x105B04A0
		CommentTrack();
		virtual ~CommentTrack();

		virtual Property* GetProperty(int index);
		virtual float GetTimeBegin() const;
		virtual float Slot10() const;
		virtual Action* CreateAction(Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		bool SetText(const char* value);

		static void RegisterProperties();
		static void ClearProperties();

		char* text;  // +0x10
	};

	extern Property** gCommentTrackProperties;

	// RTTI: fight::StopTrack (16 vftable slots, 0x1C bytes)
	class StopTrack : public Track
	{
	public:
		// 0x105B0990
		StopTrack();
		virtual ~StopTrack();

		virtual Property* GetProperty(int index);
		virtual float GetTimeBegin() const;
		virtual float Slot10() const;
		virtual Action* CreateAction(Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		ConditionList* GetConditions();

		static void RegisterProperties();
		static void ClearProperties();

		ConditionList conditions;  // +0x10
		float timeBegin;  // +0x14
		float timeEnd;  // +0x18
	};

	extern Property** gStopTrackProperties;

	// RTTI: fight::SequenceTrack (16 vftable slots, 0x40 bytes)
	class SequenceTrack : public Track
	{
	public:
		// 0x105B0D10
		SequenceTrack();
		virtual ~SequenceTrack();

		virtual Property* GetProperty(int index);
		virtual float GetTimeBegin() const;
		virtual float Slot10() const;
		virtual Action* CreateAction(Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		bool SetTimeBegin(float value);
		BranchHolder* GetBranch();
		bool SetPriority(int value);
		ConditionList* GetConditions();

		static void RegisterProperties();
		static void ClearProperties();

		BranchHolder branch;  // +0x10
		ConditionList conditions;  // +0x34
		float timeBegin;  // +0x38
		int priority;  // +0x3C
	};

	extern Property** gSequenceTrackProperties;

	// 0x105B27A0 / 0x105B27D0 / 0x105B2800 / 0x105B2830: whether a condition or a track is a comment and its text (the editor)
	bool IsCommentCondition(Condition* condition);
	const char* GetCommentConditionText(Condition* condition);
	bool IsCommentTrack(Track* track);
	const char* GetCommentTrackText(Track* track);

	// The factory makers, each followed by the registration into a registry
	ConditionFactory* CreateRandomConditionFactory(const char* name);
	ConditionFactory* CreateMaybeConditionFactory(const char* name);
	ConditionFactory* CreatePrintConditionFactory(const char* name);
	TrackFactory* CreatePrintTrackFactory(const char* name);
	ConditionFactory* CreatePlatformConditionFactory(const char* name);
	ConditionFactory* CreateNotConditionFactory(const char* name);
	ConditionFactory* CreateOrConditionFactory(const char* name);
	ConditionFactory* CreateConditionGroupConditionFactory(const char* name);
	TrackFactory* CreateTrackGroupTrackFactory(const char* name);
	ConditionFactory* CreateFalseConditionFactory(const char* name);
	ConditionFactory* CreateDebugConditionFactory(const char* name);
	ConditionFactory* CreateCommentConditionFactory(const char* name);
	TrackFactory* CreateCommentTrackFactory(const char* name);
	TrackFactory* CreateStopTrackFactory(const char* name);
	TrackFactory* CreateSequenceTrackFactory(const char* name);
	void RegisterRandomConditionFactory(TrackRegistry* registry, const char* name);
	void RegisterMaybeConditionFactory(TrackRegistry* registry, const char* name);
	void RegisterPrintConditionFactory(TrackRegistry* registry, const char* name);
	void RegisterPrintTrackFactory(TrackRegistry* registry, const char* name);
	void RegisterPlatformConditionFactory(TrackRegistry* registry, const char* name);
	void RegisterNotConditionFactory(TrackRegistry* registry, const char* name);
	void RegisterOrConditionFactory(TrackRegistry* registry, const char* name);
	void RegisterConditionGroupConditionFactory(TrackRegistry* registry, const char* name);
	void RegisterTrackGroupTrackFactory(TrackRegistry* registry, const char* name);
	void RegisterFalseConditionFactory(TrackRegistry* registry, const char* name);
	void RegisterDebugConditionFactory(TrackRegistry* registry, const char* name);
	void RegisterCommentConditionFactory(TrackRegistry* registry, const char* name);
	void RegisterCommentTrackFactory(TrackRegistry* registry, const char* name);
	void RegisterStopTrackFactory(TrackRegistry* registry, const char* name);
	void RegisterSequenceTrackFactory(TrackRegistry* registry, const char* name);

	// RTTI: fight::OpportunityTrack (16 vftable slots, 0x48 bytes)
	class OpportunityTrack : public Track
	{
	public:
		// 0x105B1170
		OpportunityTrack();
		virtual ~OpportunityTrack();

		virtual Property* GetProperty(int index);
		virtual float GetTimeBegin() const;
		virtual float Slot10() const;
		virtual Action* CreateAction(Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		bool SetTimeHook(float value);
		BranchHolder* GetBranch();
		bool SetPriority(int value);
		ConditionList* GetConditions();

		static void RegisterProperties();
		static void ClearProperties();

		BranchHolder branch;  // +0x10
		ConditionList conditions;  // +0x34
		float timeBegin;  // +0x38
		float timeEnd;  // +0x3C
		float timeHook;  // +0x40
		int priority;  // +0x44
	};

	extern Property** gOpportunityTrackProperties;

	// RTTI: fight::ExecuteTrack (16 vftable slots, 0x40 bytes)
	class ExecuteTrack : public Track
	{
	public:
		// 0x105B1620
		ExecuteTrack();
		virtual ~ExecuteTrack();

		virtual Property* GetProperty(int index);
		virtual float GetTimeBegin() const;
		virtual float Slot10() const;
		virtual Action* CreateAction(Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		BranchHolder* GetBranch();
		ConditionList* GetConditions();

		static void RegisterProperties();
		static void ClearProperties();

		BranchHolder branch;  // +0x10
		ConditionList conditions;  // +0x34
		float timeBegin;  // +0x38
		float timeEnd;  // +0x3C
	};

	extern Property** gExecuteTrackProperties;

	// 0x105B1370 / 0x105B1500 and 0x105B17C0 / 0x105B18F0
	TrackFactory* CreateOpportunityTrackFactory(const char* name);
	void RegisterOpportunityTrackFactory(TrackRegistry* registry, const char* name);
	TrackFactory* CreateExecuteTrackFactory(const char* name);
	void RegisterExecuteTrackFactory(TrackRegistry* registry, const char* name);
}

#endif
