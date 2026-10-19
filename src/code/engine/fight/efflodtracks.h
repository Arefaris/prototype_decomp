// The fight tracks that set effect level-of-detail parameters (unit 0x10812FF0 - 0x10815900).
#ifndef ENGINE_FIGHT_EFFLODTRACKS_H
#define ENGINE_FIGHT_EFFLODTRACKS_H

#include "code/engine/fight/trackfactory.h"

namespace engine
{
	// RTTI: engine::EffectLODDisableTrack (16 vftable slots, 0x14 bytes)
	class EffectLODDisableTrack : public fight::Track
	{
	public:
		// 0x10812FF0
		EffectLODDisableTrack();
		virtual ~EffectLODDisableTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108B9850)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetLodStartDistance(float value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float lodStartDistance;  // +0x10
	};

	extern fight::Property** gEffectLODDisableTrackProperties;
	// 0x108130F0
	// 0x10813190
	fight::TrackFactory* CreateEffectLODDisableTrackFactory(const char* name);
	void RegisterEffectLODDisableTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::EffectLODSwitchTrack (16 vftable slots, 0x1C bytes)
	class EffectLODSwitchTrack : public fight::Track
	{
	public:
		// 0x108132A0
		EffectLODSwitchTrack();
		virtual ~EffectLODSwitchTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108B9BA0)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetLodStartDistance(float value);
		bool SetLodUpdateRateMilliseconds(float value);
		fight::TrackGroup* GetEffect();

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::TrackGroup effect;  // +0x10
		float lodStartDistance;  // +0x14
		float lodUpdateRateMilliseconds;  // +0x18
	};

	extern fight::Property** gEffectLODSwitchTrackProperties;
	// 0x108133F0
	// 0x108134F0
	fight::TrackFactory* CreateEffectLODSwitchTrackFactory(const char* name);
	void RegisterEffectLODSwitchTrackFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::EffectLODBiasTrack (17 vftable slots, 0x128 bytes)
	class EffectLODBiasTrack : public fight::Track
	{
	public:
		// 0x10813C40
		EffectLODBiasTrack();
		virtual ~EffectLODBiasTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108BA500)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);
		// vftable slot 16 (0x10813E40)
		// vftable slot 16 (0x10813E40): whether the override bit of a property is set
		virtual bool Slot16(int index);

		// The members the properties write
		bool SetLodStartDistance(float value);
		bool SetLodUpdateRateMilliseconds(float value);
		bool SetBiases(bool value);
		bool SetBiasesEmissionRate(float value);
		bool SetBiasesEmissionRateAreaScale(float value);
		bool SetBiasesEmissionRateScaleFunction(int value);
		bool SetBiasesLifeSpan(float value);
		bool SetBiasesLifeSpanVariance(float value);
		bool SetBiasesSpeed(float value);
		bool SetBiasesSpeedVariance(float value);
		bool SetBiasesSize1D(float value);
		bool SetBiasesSize1DVariance(float value);
		bool SetBiasesSize1DAreaScale(float value);
		bool SetBiasesSize1DScaleFunction(int value);
		bool SetBiasesSpin1D(float value);
		bool SetBiasesSpin1DVariance(float value);
		bool SetBiasesWeight(float value);
		bool SetBiasesWeightVariance(float value);
		bool SetBiasesAngle(float value);
		bool SetBiasesAngleVariance(float value);
		bool SetBiasesGravity(float value);
		bool SetBiasesDrag(float value);
		bool SetBiasesColourRed(float value);
		bool SetBiasesColourGreen(float value);
		bool SetBiasesColourBlue(float value);
		bool SetBiasesAlpha(float value);
		bool SetBiasesColourOverLifeRed(float value);
		bool SetBiasesColourOverLifeGreen(float value);
		bool SetBiasesColourOverLifeBlue(float value);
		bool SetBiasesAlphaOverLife(float value);
		bool SetBiasesColourVariance(float value);
		bool SetBiasesAlphaVariance(float value);
		bool SetBiasesGeneratorRadius(float value);
		bool SetBiasesGeneratorRadial(float value);
		bool SetBiasesGeneratorHorizSpread(float value);
		bool SetBiasesGeneratorVertSpread(float value);
		bool SetBiasesGeneratorWidth(float value);
		bool SetBiasesGeneratorHeight(float value);
		bool SetBiasesMeshGeneratorScale(const math::Vector& value);
		bool SetOverrides(bool value);
		bool SetOverridesEmissionRate(float value);
		bool SetOverridesEmissionRatePerMeter(float value);
		bool SetOverridesMaxParticles(float value);
		bool SetOverridesParticleAllocation(float value);
		bool SetOverridesLifeSpan(float value);
		bool SetOverridesLifeSpanVariance(float value);
		bool SetOverridesSpeed(float value);
		bool SetOverridesSpeedVariance(float value);
		bool SetOverridesSize1D(float value);
		bool SetOverridesSize1DVariance(float value);
		bool SetOverridesSpin1D(float value);
		bool SetOverridesSpin1DVariance(float value);
		bool SetOverridesWeight(float value);
		bool SetOverridesWeightVariance(float value);
		bool SetOverridesAngle(float value);
		bool SetOverridesAngleVariance(float value);
		bool SetOverridesGravity(float value);
		bool SetOverridesDrag(float value);
		bool SetOverridesColourRed(float value);
		bool SetOverridesColourGreen(float value);
		bool SetOverridesColourBlue(float value);
		bool SetOverridesAlpha(float value);
		bool SetOverridesColourVariance(float value);
		bool SetOverridesAlphaVariance(float value);
		bool SetOverridesGeneratorWidth(float value);
		bool SetOverridesGeneratorHeight(float value);

		// 0x10813EA0: sets or clears the override bits of a group's properties (and of the groups inside it)
		void ApplyGroup(int group, bool value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		// The bits of the properties the track overrides (0x10813E40 tests one, 0x10813EA0 sets a group's)
		unsigned __int64 overrideMask;  // +0x10
		math::Vector biasesMeshGeneratorScale;  // +0x18
		float biasesAlpha;  // +0x24
		float biasesAlphaOverLife;  // +0x28
		float biasesAlphaVariance;  // +0x2C
		float biasesAngle;  // +0x30
		float biasesAngleVariance;  // +0x34
		float biasesColourBlue;  // +0x38
		float biasesColourGreen;  // +0x3C
		float biasesColourOverLifeBlue;  // +0x40
		float biasesColourOverLifeGreen;  // +0x44
		float biasesColourOverLifeRed;  // +0x48
		float biasesColourRed;  // +0x4C
		float biasesColourVariance;  // +0x50
		float biasesDrag;  // +0x54
		float biasesEmissionRate;  // +0x58
		float biasesEmissionRateAreaScale;  // +0x5C
		float biasesGeneratorHeight;  // +0x60
		float biasesGeneratorHorizSpread;  // +0x64
		float biasesGeneratorRadial;  // +0x68
		float biasesGeneratorRadius;  // +0x6C
		float biasesGeneratorVertSpread;  // +0x70
		float biasesGeneratorWidth;  // +0x74
		float biasesGravity;  // +0x78
		float biasesLifeSpan;  // +0x7C
		float biasesLifeSpanVariance;  // +0x80
		float biasesSize1D;  // +0x84
		float biasesSize1DAreaScale;  // +0x88
		float biasesSize1DVariance;  // +0x8C
		float biasesSpeed;  // +0x90
		float biasesSpeedVariance;  // +0x94
		float biasesSpin1D;  // +0x98
		float biasesSpin1DVariance;  // +0x9C
		float biasesWeight;  // +0xA0
		float biasesWeightVariance;  // +0xA4
		float lodStartDistance;  // +0xA8
		float lodUpdateRateMilliseconds;  // +0xAC
		float overridesAlpha;  // +0xB0
		float overridesAlphaVariance;  // +0xB4
		float overridesAngle;  // +0xB8
		float overridesAngleVariance;  // +0xBC
		float overridesColourBlue;  // +0xC0
		float overridesColourGreen;  // +0xC4
		float overridesColourRed;  // +0xC8
		float overridesColourVariance;  // +0xCC
		float overridesDrag;  // +0xD0
		float overridesEmissionRate;  // +0xD4
		float overridesEmissionRatePerMeter;  // +0xD8
		float overridesGeneratorHeight;  // +0xDC
		float overridesGeneratorWidth;  // +0xE0
		float overridesGravity;  // +0xE4
		float overridesLifeSpan;  // +0xE8
		float overridesLifeSpanVariance;  // +0xEC
		float overridesMaxParticles;  // +0xF0
		float overridesParticleAllocation;  // +0xF4
		float overridesSize1D;  // +0xF8
		float overridesSize1DVariance;  // +0xFC
		float overridesSpeed;  // +0x100
		float overridesSpeedVariance;  // +0x104
		float overridesSpin1D;  // +0x108
		float overridesSpin1DVariance;  // +0x10C
		float overridesWeight;  // +0x110
		float overridesWeightVariance;  // +0x114
		int biasesEmissionRateScaleFunction;  // +0x118
		int biasesSize1DScaleFunction;  // +0x11C
		bool biases;  // +0x120
		bool overrides;  // +0x121
		int unknown124;
	};

	extern fight::Property** gEffectLODBiasTrackProperties;
	// 0x10814180
	// 0x10814F30
	fight::TrackFactory* CreateEffectLODBiasTrackFactory(const char* name);
	void RegisterEffectLODBiasTrackFactory(fight::TrackRegistry* registry, const char* name);

}

#endif
