// proto::FEHudHealth (RTTI name; bases proto::FEHudElement and engine::ISimulationTask): the health meter of the head-up
// display. It follows the player's health, the damage and gain it just took (the masks of the meter), the critical mass
// and the poison, and runs as a simulation task while it is shown. The movie paths and function names are original, the
// member names are guessed. Unit 0x104D3D20 - 0x104D5200 (no assert path; the file name is a guess).
#ifndef PROTO_FRONTEND_FEHUDHEALTH_H
#define PROTO_FRONTEND_FEHUDHEALTH_H

#include "code/engine/online/replay.h"
#include "code/proto/frontend/fehudelement.h"

namespace proto
{
	class FEHudHealth : public FEHudElement, public engine::ISimulationTask
	{
	public:
		// 0x104D4BF0
		FEHudHealth();
		// 0x104D4370
		~FEHudHealth();

		// vftable slots 0 and 1 of the element (0x104D3E10, 0x104D5150) and slot 0 of the simulation task (0x104D5180)
		virtual void Update(bool force);
		virtual void OnShow(bool shown);
		virtual void UpdateSimulation(engine::UpdateContext context);

		// 0x104D4B90
		void SetVisible(bool newVisible);
		// 0x104D4280: puts the meter among the simulation tasks, or takes it out
		void SetTaskActive(bool active);
		// 0x104D4230: shows or hides the poison effect
		void ShowPoison(bool poisoned);
		// 0x104D4160: tells the movie which devastator display to show
		void SetDevastatorState(int newState);
		// 0x104D3EE0 / 0x104D3EF0
		void SetUnknown64(bool value);
		bool GetUnknown64();
		// 0x104D3F00 / 0x104D3F10
		float GetUnknown5C();
		void ClearUnknown5C();
		// 0x104D3ED0: does nothing (the screen calls it every frame)
		void Unknown104D3ED0();
		// 0x104D4EE0 (not reconstructed)
		void Unknown104D4EE0();

		float unknown10;
		float unknown14;
		float unknown18;
		float unknown1C;
		float unknown20;
		float unknown24;
		float unknown28;
		float unknown2C;
		bool visible;  // +0x30
		bool unknown31;
		bool unknown32;
		bool unknown33;
		bool taskActive;  // +0x34
		int devastatorState;  // +0x38
		float unknown3C;
		float unknown40;
		float unknown44;
		float unknown48;
		float unknown4C;
		float unknown50;
		float unknown54;
		bool unknown58;
		float unknown5C;
		float unknown60;
		bool unknown64;
		bool unknown65;
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> visibleVariable;  // +0x68
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> normHealthMask;  // +0x110
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> damageMask;  // +0x1B8
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> backgroundMask;  // +0x260
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> criticalMassMask;  // +0x308
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> criticalMass;  // +0x3B0
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> gainMask;  // +0x458
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> gain;  // +0x500
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> criticalMassIndicator;  // +0x5A8
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> criticalMassBottomMask;  // +0x650
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> ekgMask;  // +0x6F8
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> scanlines;  // +0x7A0
	};
}

#endif
