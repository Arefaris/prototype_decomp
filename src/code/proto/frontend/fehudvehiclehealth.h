// proto::FEHudVehicleHealth (RTTI name; base proto::FEHudElement): the health bar of the vehicle the player drives. Its
// variables show the element and slide the health and the damage masks of the bar. The movie paths are original, the
// member names are guessed. Unit 0x104D5420 - 0x104D5830 (no assert path; the file name is a guess).
#ifndef PROTO_FRONTEND_FEHUDVEHICLEHEALTH_H
#define PROTO_FRONTEND_FEHUDVEHICLEHEALTH_H

#include "code/proto/frontend/fehudelement.h"

namespace engine
{
	class GameObject;
}

namespace proto
{
	class FEHudVehicleHealth : public FEHudElement
	{
	public:
		// 0x104D54C0
		FEHudVehicleHealth();

		// vftable slots 0 and 1 (0x104D5420, 0x104D54B0, which jumps to SetActive)
		virtual void Update(bool force);
		virtual void OnShow(bool shown);

		// 0x104D5460
		void SetActive(bool newActive);
		// 0x104D5680: moves the masks to the vehicle's health
		void UpdateHealth();

		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> visible;  // +0x10
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> healthMask;  // +0xB8
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> damageMask;  // +0x160
		bool active;  // +0x208
	};
}

#endif
