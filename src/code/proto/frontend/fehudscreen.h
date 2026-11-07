// proto::FEHudScreen (RTTI name): the owner of the head-up display's elements. Of the class only the element pointers
// that the compiler's deleting destructors of the elements need are declared here. Unit 0x104C0390 - 0x104C2170 (no assert
// path; the file name is a guess). The elements the screen keeps are listed in the order of their bit in the screen's masks.
#ifndef PROTO_FRONTEND_FEHUDSCREEN_H
#define PROTO_FRONTEND_FEHUDSCREEN_H

#include "code/engine/dbobserver.h"
#include "code/engine/gamestate.h"
#include "code/engine/online/replay.h"
#include "code/proto/frontend/fehudelement.h"

namespace engine
{
	// The base of the render tasks that draw the presentation (the head-up display's mini map is one)
	class RenderTask
	{
	public:
		class PresentationTask
		{
		public:
			virtual void Slot0() = 0;
		};
	};
}

namespace proto
{
	// The elements of the head-up display that are not reconstructed yet: their destructors are the engine's (mapped in
	// symbols.txt), the layouts are not needed to delete them
	class FEHudTargeting : public FEHudElement
	{
	public:
		// 0x104CB160
		~FEHudTargeting();
	};

	class FEHudPopup : public FEHudElement
	{
	public:
		// 0x104D1660
		~FEHudPopup();
	};

	class FEHudEventPopup
	{
	public:
		// 0x104CFB00
		~FEHudEventPopup();
	};

	class FEHudOpportunityEventPopup
	{
	public:
		// 0x104D0F00
		~FEHudOpportunityEventPopup();
	};

	class FEHudMissionPopup
	{
	public:
		// 0x104D11D0
		~FEHudMissionPopup();
	};

	class FEHudMiniMap : public engine::RenderTask::PresentationTask, public FEHudElement
	{
	public:
		// 0x104C38C0
		~FEHudMiniMap();
	};

	class FEHudHealth : public FEHudElement, public engine::ISimulationTask
	{
	public:
		// 0x104D4370
		~FEHudHealth();
	};

	class FEHudPowers : public FEHudElement, public engine::IRealTimeTask
	{
	public:
		// 0x104C75A0
		~FEHudPowers();
	};

	class FEHudButtonHint : public FEHudElement, public engine::ISimulationTask
	{
	public:
		// 0x104CE570
		~FEHudButtonHint();
	};

	class FEHudEvolutionPoints : public FEHudElement, public engine::DBObserver, public engine::ISimulationTask
	{
	public:
		// 0x104D0020
		~FEHudEvolutionPoints();
	};

	class FEHudMeter : public FEHudElement, public engine::ISimulationTask
	{
	public:
		// 0x104CC990
		~FEHudMeter();
	};

	class FEHUDTypewriter : public engine::IRealTimeTask
	{
	public:
		// 0x104DA160
		~FEHUDTypewriter();
	};

	class FEHudKeyCard;
	class FEHudCombatConclusion;
	class FEHudTextLog;

	class FEHudScreen
	{
	public:
		// The compiler's deleting destructors of the elements are emitted for the screen's delete expressions
		~FEHudScreen();

		FEHudMiniMap* miniMap;
		FEHudHealth* health;
		FEHudPowers* powers;
		FEHudButtonHint* buttonHint;
		FEHudEvolutionPoints* evolutionPoints;
		FEHudMeter* meter;
		FEHUDTypewriter* typewriter;
		FEHudTargeting* targeting;
		FEHudPopup* popup;
		FEHudEventPopup* eventPopup;
		FEHudOpportunityEventPopup* opportunityEventPopup;
		FEHudMissionPopup* missionPopup;
		FEHudKeyCard* keyCard;
		FEHudCombatConclusion* combatConclusion;
		FEHudTextLog* textLog;
	};
}

#endif
