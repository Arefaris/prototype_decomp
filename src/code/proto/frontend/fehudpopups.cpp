#include "code/proto/frontend/fehudpopups.h"

#include "code/core/heap.h"
#include "code/engine/function.h"
#include "code/engine/luascriptmanager.h"

namespace engine
{
	// 0x10837470 / 0x108374B0
	bool IsGameStateOnTop(int id);
	bool HasPendingStateChange();
}

namespace proto
{
	// FUNCTION: ENGINE 0x104CFD70
	FEHudEventPopup::FEHudEventPopup()
	{
		unknown4 = false;
		preEvent = false;
		hidePending = false;
		core::HeapScope scope(0x72);
		dialog = new engine::DialogState(0x10, 0x12, "EVENT", (int)"event_popup");
		engine::LuaScriptManager* manager = engine::GetScriptManager();
		manager->SetOwner(this);
		manager->RegisterMethod("feeventpopup_IsPreEvent", this, &FEHudEventPopup::IsPreEvent);
		manager->ClearOwner();
	}

	// FUNCTION: ENGINE 0x104CFAF0
	bool FEHudEventPopup::IsPreEvent()
	{
		return preEvent;
	}

	// FUNCTION: ENGINE 0x104CFB00
	FEHudEventPopup::~FEHudEventPopup()
	{
		engine::LuaScriptManager* manager = engine::GetScriptManager();
		manager->Unregister(this);
		delete dialog;
	}

	// FUNCTION: ENGINE 0x104CFB30
	// NONMATCHING: the engine loads the -1 of the request into eax (or eax, -1) after the stores, ours pushes it as an immediate (59 - 73 %)
#ifdef NONMATCHING
	void FEHudEventPopup::Hide(bool newPreEvent, bool newFlag)
	{
		if (engine::IsGameStateOnTop(2) && !engine::HasPendingStateChange())
		{
			hidePending = false;
			unknown4 = newPreEvent;
			preEvent = newFlag;
			dialog->Unknown10883D50(-1, false);
			return;
		}
		hidePending = true;
	}
#endif

	// FUNCTION: ENGINE 0x104CFB90
	// NONMATCHING: the engine loads the -1 of the request into eax (or eax, -1) after the stores, ours pushes it as an immediate (59 - 73 %)
#ifdef NONMATCHING
	void FEHudEventPopup::Update()
	{
		if (hidePending && engine::IsGameStateOnTop(2) && !engine::HasPendingStateChange())
		{
			hidePending = false;
			dialog->Unknown10883D50(-1, false);
		}
	}
#endif

	// FUNCTION: ENGINE 0x104D1130
	FEHudMissionPopup::FEHudMissionPopup()
	{
		showPending = false;
		core::HeapScope scope(0x72);
		dialog = new engine::DialogState(0xF, 0x11, "MISSION", (int)"mission_popup");
		engine::LuaScriptManager* manager = engine::GetScriptManager();
		manager->SetOwner(this);
		manager->RegisterMethod("femissionpopup_Show", this, &FEHudMissionPopup::Show);
		manager->ClearOwner();
	}

	// FUNCTION: ENGINE 0x104D0F00
	FEHudMissionPopup::~FEHudMissionPopup()
	{
		engine::LuaScriptManager* manager = engine::GetScriptManager();
		manager->Unregister(this);
		delete dialog;
	}

	// FUNCTION: ENGINE 0x104D0F30
	// NONMATCHING: the engine loads the -1 of the request into eax (or eax, -1) after the stores, ours pushes it as an immediate (59 - 73 %)
#ifdef NONMATCHING
	void FEHudMissionPopup::Show()
	{
		if (engine::IsGameStateOnTop(2) && !engine::HasPendingStateChange())
		{
			showPending = false;
			dialog->Unknown10883D50(-1, false);
			return;
		}
		showPending = true;
	}
#endif

	// FUNCTION: ENGINE 0x104D0F70
	// NONMATCHING: the engine loads the -1 of the request into eax (or eax, -1) after the stores, ours pushes it as an immediate (59 - 73 %)
#ifdef NONMATCHING
	void FEHudMissionPopup::Update()
	{
		if (showPending && engine::IsGameStateOnTop(2) && !engine::HasPendingStateChange())
		{
			showPending = false;
			dialog->Unknown10883D50(-1, false);
		}
	}
#endif

	// FUNCTION: ENGINE 0x104D13A0
	FEHudOpportunityEventPopup::FEHudOpportunityEventPopup()
	{
		core::HeapScope scope(0x72);
		dialog = new engine::DialogState(0x10, 0x12, "OPPORTUNITY_EVENT", (int)"opportunity_event_popup");
		engine::LuaScriptManager* manager = engine::GetScriptManager();
		manager->SetOwner(this);
		manager->RegisterMethod("feopportunityeventpopup_Show", this, &FEHudOpportunityEventPopup::Show);
		manager->ClearOwner();
	}

	// FUNCTION: ENGINE 0x104D11D0
	FEHudOpportunityEventPopup::~FEHudOpportunityEventPopup()
	{
		engine::LuaScriptManager* manager = engine::GetScriptManager();
		manager->Unregister(this);
		delete dialog;
	}

	// FUNCTION: ENGINE 0x104D1200
	// NONMATCHING: the engine loads the -1 of the request into eax (or eax, -1), ours pushes it as an immediate (50 %)
#ifdef NONMATCHING
	void FEHudOpportunityEventPopup::Show()
	{
		dialog->Unknown10883D50(-1, false);
	}
#endif
}
