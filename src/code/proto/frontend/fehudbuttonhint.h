// proto::FEHudButtonHint (RTTI name; bases proto::FEHudElement and engine::ISimulationTask): the hint of the head-up
// display that names the button of an action (two texts for the pad's button, one text for each of the two keyboard keys).
// While it is shown it runs as a simulation task. The movie paths are original, the member names are guessed. Unit
// 0x104CE400 - 0x104CEC98 (no assert path; the file name is a guess).
#ifndef PROTO_FRONTEND_FEHUDBUTTONHINT_H
#define PROTO_FRONTEND_FEHUDBUTTONHINT_H

#include "code/engine/online/replay.h"
#include "code/proto/frontend/fehudelement.h"

namespace proto
{
	class FEHudButtonHint : public FEHudElement, public engine::ISimulationTask
	{
	public:
		// 0x104CE960
		FEHudButtonHint();
		// 0x104CE570
		~FEHudButtonHint();

		// vftable slots 0 and 1 of the element (0x104CE430, 0x104CEC80) and slot 0 of the simulation task (0x104CEC30)
		virtual void Update(bool force);
		virtual void OnShow(bool shown);
		virtual void UpdateSimulation(engine::UpdateContext context);

		// 0x104CE5F0
		void SetVisible(bool newVisible);
		// 0x104CE4A0: puts the hint among the simulation tasks, or takes it out
		void SetTaskActive(bool active);
		// 0x104CE650: clears the texts and the button
		void Reset();
		// 0x104CE490: does nothing (the screen calls it every frame)
		void Unknown104CE490();

		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> frontText;  // +0x10
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> backText;  // +0xB8
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> keyboardUpText;  // +0x160
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> keyboardDownText;  // +0x208
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> visible;  // +0x2B0
		bool visibleFlag;  // +0x358
		int unknown35C;
		int unknown360;
		bool unknown364;
		bool unknown365;
		bool unknown366;
		bool taskActive;  // +0x367
	};
}

#endif
