// proto::FEHudScreen (RTTI name): the owner of the head-up display's elements. It makes the nineteen elements (the
// pointers are in the order of the engine's table; the bit of an element in the masks of Show and GetEnabledElements is
// its place in the head-up display, not its place in the table), shows and hides them by mask, updates them and
// registers the scripts' fe_ functions. Unit 0x104C00D0 - 0x104C2170 (no assert path; the file name is a guess). The
// elements that are not reconstructed yet are declared here with the layout the screen needs (their size and the
// members of the screen's calls); their destructors and the members the screen calls are the engine's (mapped in
// symbols.txt).
#ifndef PROTO_FRONTEND_FEHUDSCREEN_H
#define PROTO_FRONTEND_FEHUDSCREEN_H

#include "code/engine/dbobserver.h"
#include "code/engine/drawableregistry.h"
#include "code/engine/frontend/dialogstate.h"
#include "code/engine/gamestate.h"
#include "code/engine/online/replay.h"
#include "code/math/vector.h"
#include "code/proto/frontend/fehudawareness.h"
#include "code/proto/frontend/fehudbuttonhint.h"
#include "code/proto/frontend/fehudcombatconclusion.h"
#include "code/proto/frontend/fehuddisguiseactions.h"
#include "code/proto/frontend/fehuddisguiseperception.h"
#include "code/proto/frontend/fehudpopup.h"
#include "code/proto/frontend/fehudpopups.h"
#include "code/proto/frontend/fehudelement.h"
#include "code/proto/frontend/fehudevolutionpoints.h"
#include "code/proto/frontend/fehudhealth.h"
#include "code/proto/frontend/fehudkeycard.h"
#include "code/proto/frontend/fehudtextlog.h"
#include "code/proto/frontend/fehudvehiclehealth.h"

namespace proto
{
	// Three floats passed by value (the position the mini map and the head-up display follow; the engine copies them as plain
	// words, unlike math::Vector; name guessed)
	struct FEHudPoint
	{
		float x;
		float y;
		float z;
	};

	class FEHudMiniMap : public engine::RenderTask::PresentationTask, public FEHudElement
	{
	public:
		// 0x104C4800
		FEHudMiniMap();
		// 0x104C38C0
		~FEHudMiniMap();

		// vftable slots 0 and 1 of the element (0x104C31B0, 0x104C3D80) and slot 0 of the presentation task (0x104C3300)
		virtual void Update(bool force);
		virtual void OnShow(bool shown);
		virtual void Update(engine::UpdateContext context, unsigned int unknown1, unsigned int unknown2);

		// 0x104C4630
		void Unknown104C4630(FEHudPoint position);

		unsigned char unknown10[0x35D8 - 0x10];
	};

	class FEHudPowers : public FEHudElement, public engine::IRealTimeTask
	{
	public:
		// 0x104C6F10
		FEHudPowers();
		// 0x104C75A0
		~FEHudPowers();

		virtual void Update(bool force);
		virtual void OnShow(bool shown);
		virtual void Update(engine::UpdateContext context);

		// 0x104C58C0 / 0x104C5870 / 0x104C6420
		void Unknown104C58C0();
		void Unknown104C5870();
		void Unknown104C6420();

		unsigned char unknown10[0x1448 - 0x10];
	};

	class FEHudTargeting : public FEHudElement
	{
	public:
		// 0x104CB3E0
		FEHudTargeting();
		// 0x104CB160
		~FEHudTargeting();

		virtual void Update(bool force);
		virtual void OnShow(bool shown);

		// 0x104CAEA0
		void Unknown104CAEA0();

		unsigned char unknownC[0x2538 - 0xC];
	};

	class FEHudMeter : public FEHudElement, public engine::ISimulationTask
	{
	public:
		// 0x104CDE60
		FEHudMeter();
		// 0x104CC990
		~FEHudMeter();

		virtual void Update(bool force);
		virtual void OnShow(bool shown);
		virtual void UpdateSimulation(engine::UpdateContext context);

		unsigned char unknown10[0xB58 - 0x10];
	};

	// The typewriter of the subtitles and texts of the head-up display (not an element)
	class FEHUDTypewriter : public engine::IRealTimeTask
	{
	public:
		// 0x104DA760
		FEHUDTypewriter();
		// 0x104DA160
		~FEHUDTypewriter();

		virtual void Update(engine::UpdateContext context);

		// 0x104D9740 / 0x104D9A90
		void Update(bool force);
		void Unknown104D9A90(bool flag);

		unsigned char unknown4[0x13B8 - 4];
	};

	class FEHudScreen
	{
	public:
		// 0x104C1C40: no element exists yet; registers fe_GetEnabledHudElements, fe_ForceShowPopups,
		// fe_GetHideHudElementRefCount and fe_SetHideHudElementRefCount
		FEHudScreen();

		// 0x104C1400: makes the elements that do not exist yet
		void Create();
		// 0x104C1EA0: deletes the elements (the mini map only when it is not kept)
		void Destroy(bool keepMiniMap);
		// 0x104C04D0: updates the elements that update their variables
		void Update(bool force);
		// 0x104C0920: shows or hides the elements of the mask
		void Show(bool show, unsigned int mask);
		// 0x104C0F90
		void ShowAll(bool show);
		// 0x104C0A70: the scripts' fe_ForceShowPopups
		void ForceShowPopups();
		// 0x104C0AB0: the scripts' fe_GetEnabledHudElements; the mask of the elements that are shown
		int GetEnabledElements();
		// 0x104C0C10: the element of one bit of the masks
		FEHudElement* GetElement(unsigned int mask);
		// 0x104C0FB0 / 0x104C0FD0: the scripts' fe_GetHideHudElementRefCount and fe_SetHideHudElementRefCount
		int GetHideCount(unsigned int mask);
		void SetHideCount(unsigned int count, unsigned int mask);
		// 0x104C05C0 / 0x104C05F0
		void Unknown104C05C0();
		void Unknown104C05F0();
		// 0x104C0F00
		void Unknown104C0F00(FEHudPoint position);

		FEHudMiniMap* miniMap;  // +0
		FEHudHealth* health;  // +4
		FEHudPowers* powers;  // +8
		FEHudPopup* popup;  // +0xC
		FEHudDisguisePerception* disguisePerception;  // +0x10
		FEHudButtonHint* buttonHint;  // +0x14
		FEHudTargeting* targeting;  // +0x18
		FEHudEvolutionPoints* evolutionPoints;  // +0x1C
		FEHudDisguiseActions* disguiseActions;  // +0x20
		FEHudMeter* meter;  // +0x24
		FEHudTextLog* textLog;  // +0x28
		FEHudVehicleHealth* vehicleHealth;  // +0x2C
		FEHudEventPopup* eventPopup;  // +0x30
		FEHudMissionPopup* missionPopup;  // +0x34
		FEHudOpportunityEventPopup* opportunityEventPopup;  // +0x38
		FEHUDTypewriter* typewriter;  // +0x3C
		FEHudKeyCard* keyCard;  // +0x40
		FEHudAwareness* awareness;  // +0x44
		FEHudCombatConclusion* combatConclusion;  // +0x48
		bool created;  // +0x4C
	};
}

#endif
