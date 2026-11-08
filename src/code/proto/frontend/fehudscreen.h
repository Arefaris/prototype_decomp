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
#include "code/proto/frontend/fehudcombatconclusion.h"
#include "code/proto/frontend/fehuddisguiseactions.h"
#include "code/proto/frontend/fehuddisguiseperception.h"
#include "code/proto/frontend/fehudelement.h"
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

	class FEHudHealth : public FEHudElement, public engine::ISimulationTask
	{
	public:
		// 0x104D4BF0
		FEHudHealth();
		// 0x104D4370
		~FEHudHealth();

		virtual void Update(bool force);
		virtual void OnShow(bool shown);
		virtual void UpdateSimulation(engine::UpdateContext context);

		// 0x104D3ED0 / 0x104D4EE0
		void Unknown104D3ED0();
		void Unknown104D4EE0();

		unsigned char unknown10[0x848 - 0x10];
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

	class FEHudPopup : public FEHudElement
	{
	public:
		// 0x104D25F0
		FEHudPopup();
		// 0x104D1660
		~FEHudPopup();

		virtual void Update(bool force);
		virtual void OnShow(bool shown);

		unsigned char unknownC[0x128 - 0xC];
	};

	class FEHudButtonHint : public FEHudElement, public engine::ISimulationTask
	{
	public:
		// 0x104CE960
		FEHudButtonHint();
		// 0x104CE570
		~FEHudButtonHint();

		virtual void Update(bool force);
		virtual void OnShow(bool shown);
		virtual void UpdateSimulation(engine::UpdateContext context);

		// 0x104CE490
		void Unknown104CE490();

		unsigned char unknown10[0x368 - 0x10];
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

	class FEHudEvolutionPoints : public FEHudElement, public engine::DBObserver, public engine::ISimulationTask
	{
	public:
		// 0x104D0480
		FEHudEvolutionPoints();
		// 0x104D0020
		~FEHudEvolutionPoints();

		virtual void Update(bool force);
		virtual void OnShow(bool shown);
		virtual void OnDBSlot0(int a, int b);
		virtual void UpdateSimulation(engine::UpdateContext context);

		// 0x104D0A90 / 0x104CFED0
		void Unknown104D0A90();
		void Unknown104CFED0();

		unsigned char unknown14[0x4B0 - 0x14];
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

	// The three pop-ups that run in the front end's dialog state: each keeps its dialog (at +0) and the flags the scripts set
	class FEHudEventPopup
	{
	public:
		// 0x104CFD70
		FEHudEventPopup();
		// 0x104CFB00
		~FEHudEventPopup();

		// 0x104CFB90
		void Unknown104CFB90();

		engine::DialogState* dialog;  // +0
		bool unknown4;
		bool unknown5;
		bool unknown6;
	};

	class FEHudMissionPopup
	{
	public:
		// 0x104D1130
		FEHudMissionPopup();
		// 0x104D0F00
		~FEHudMissionPopup();

		// 0x104D0F70
		void Unknown104D0F70();

		engine::DialogState* dialog;  // +0
		bool unknown4;
	};

	class FEHudOpportunityEventPopup
	{
	public:
		// 0x104D13A0
		FEHudOpportunityEventPopup();
		// 0x104D11D0
		~FEHudOpportunityEventPopup();

		engine::DialogState* dialog;  // +0
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
