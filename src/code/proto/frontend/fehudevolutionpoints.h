// proto::FEHudEvolutionPoints (RTTI name; bases proto::FEHudElement, engine::DBObserver and engine::ISimulationTask): the
// evolution points counter of the head-up display. It shows the points the player owns and the gain of the last
// kill in the movie, follows the setting of the smart hints in the game database, and runs as a simulation task while it
// is shown. The movie paths are original, the member names are guessed. Unit 0x104CFE70 - 0x104D0B10 (no assert path;
// the file name is a guess).
#ifndef PROTO_FRONTEND_FEHUDEVOLUTIONPOINTS_H
#define PROTO_FRONTEND_FEHUDEVOLUTIONPOINTS_H

#include "code/engine/dbobserver.h"
#include "code/engine/online/replay.h"
#include "code/proto/frontend/fehudelement.h"

namespace proto
{
	class FEHudEvolutionPoints : public FEHudElement, public engine::DBObserver, public engine::ISimulationTask
	{
	public:
		// 0x104D0480
		FEHudEvolutionPoints();
		// 0x104D0020
		~FEHudEvolutionPoints();

		// vftable slots 0 and 1 of the element (0x104CFE70, 0x104D00C0), of the observer (0x104D0AE0, 0x104CFF30) and slot 0
		// of the simulation task (0x104D06E0)
		virtual void Update(bool force);
		virtual void OnShow(bool shown);
		virtual void OnDBSlot0(int a, int b);
		virtual void OnDBSlot1(int a, int b);
		virtual void UpdateSimulation(engine::UpdateContext context);

		// 0x104CFF40
		void SetVisible(bool newVisible);
		// 0x104CFF90: puts the counter among the simulation tasks, or takes it out
		void SetTaskActive(bool active);
		// 0x104CFEE0
		void SetFloats(float a, float b, float c, float d);
		// 0x104D0A90: takes the setting of the smart hints
		void Unknown104D0A90();
		// 0x104CFED0: does nothing (the screen calls it every frame)
		void Unknown104CFED0();
		// 0x104D00F0 / 0x104D0870 (not reconstructed)
		void Unknown104D00F0(int value);
		bool Unknown104D0870(int value, bool force);

		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> epText;  // +0x18
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> epShadowText;  // +0xC0
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> gainText;  // +0x168
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> gainShadowText;  // +0x210
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> visible;  // +0x2B8
		int unknown360;
		int unknown364;
		int unknown368;
		int unknown36C;
		int unknown370;
		int unknown374;
		int unknown378;
		int unknown37C;
		int unknown380;
		float unknown384;
		bool unknown388;
		bool unknown389;
		bool unknown38A;
		float unknown38C;
		float unknown390;
		float unknown394;
		float unknown398;
		float unknown39C;
		float unknown3A0;
		float unknown3A4;
		bool taskActive;  // +0x3A8
		unsigned char unknown3AC[0x4B0 - 0x3AC];
	};
}

#endif
