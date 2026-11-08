// proto::FEHudMeter (RTTI name; bases proto::FEHudElement and engine::ISimulationTask): the meter of the head-up display
// that shows a bar with a label, icons at both ends and webbing (the war meter of the scripts is the same element with other
// function names). The scripts show it, hide it, name its icons and texts, move its bars and recolour them; while it is
// shown it runs as a simulation task. The movie paths, script names and the three enumerations are original (RTTI), the
// member names are guessed. Unit 0x104CC0A0 - 0x104CE400 (no assert path; the file name is a guess).
#ifndef PROTO_FRONTEND_FEHUDMETER_H
#define PROTO_FRONTEND_FEHUDMETER_H

#include "code/engine/online/replay.h"
#include "code/proto/frontend/fehudelement.h"

struct lua_State;

namespace proto
{
	class FEHudMeter : public FEHudElement, public engine::ISimulationTask
	{
	public:
		enum EBarColors
		{
			EBarColorsFirst
		};
		enum EIcons
		{
			EIconsFirst
		};
		enum EPositions
		{
			EPositionsFirst
		};

		// 0x104CDE60
		FEHudMeter();
		// 0x104CC990
		~FEHudMeter();

		// vftable slots 0 and 1 of the element (0x104CC0F0, 0x104CCBC0) and slot 0 of the simulation task (0x104CCAD0)
		virtual void Update(bool force);
		virtual void OnShow(bool shown);
		virtual void UpdateSimulation(engine::UpdateContext context);

		// 0x104CD3A0: the scripts' fehudmeter_Show
		void ShowMeter(EIcons leftIcon, EIcons middleIcon, EIcons rightIcon, const char* leftText, const char* rightText,
			float percentage, EBarColors colour, EBarColors secondColour);
		// 0x104CC200: the scripts' fehudmeter_Hide and fehudwarmeter_Hide
		void Hide();
		// 0x104CC230 / 0x104CCB00: the scripts' ..._UpdateIcon and ..._UpdateText
		void UpdateIcon(EPositions position, EIcons icon);
		void UpdateText(EPositions position, const char* text);
		// 0x104CC2E0 / 0x104CC470: the scripts' fehudmeter_UpdatePercentage and fehudwarmeter_UpdatePercentage
		void UpdatePercentage(float percentage);
		void UpdateWarPercentage(EPositions position, float percentage);
		// 0x104CC5E0 / 0x104CC690: the scripts' ..._ToggleBars and ..._UpdateBarColor
		void ToggleBars(EPositions position, bool on);
		void UpdateBarColor(EPositions position, EBarColors colour);
		// 0x104CC6F0: the scripts' fehudmeter_TriggerAttentionGrab
		void TriggerAttentionGrab();
		// 0x104CC720: the scripts' fehudmeter_SetDrainEnabled
		void SetDrainEnabled(bool enabled);
		// 0x104CC750
		void SetVisible(bool newVisible);

		float unknown10;
		float unknown14;
		float unknown18;
		float unknown1C;
		bool drainEnabled;  // +0x20
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> visible;  // +0x28
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> capVisible[3];  // +0xD0
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> pulseText0;  // +0x2C8
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> pulseText2;  // +0x370
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> barsCombinedX;  // +0x418
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> cap1X;  // +0x4C0
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> bar0Visible;  // +0x568
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> bar0X;  // +0x610
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> bar0Width;  // +0x6B8
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> bar2Visible;  // +0x760
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> bar2Width;  // +0x808
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> webbing0Visible;  // +0x8B0
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> webbing2Visible;  // +0x958
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> flareX;  // +0xA00
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> drainMaskX;  // +0xAA8
		bool visibleFlag;  // +0xB50
		unsigned char unknownB51[0xB58 - 0xB51];
	};

	// 0x104CDAD0: the script native fehudwarmeter_Show (name guessed)
	int FEHudWarMeterShow(lua_State* state);
}

#endif
