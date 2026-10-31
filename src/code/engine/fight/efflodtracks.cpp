// The fight tracks that set effect level-of-detail parameters (unit 0x10812FF0 - 0x10815900).
#include "code/engine/fight/efflodtracks.h"

namespace engine
{
	fight::Property** gEffectLODDisableTrackProperties;  // 0x11284BF4

	// FUNCTION: ENGINE 0x10812FC0
	bool EffectLODDisableTrack::SetLodStartDistance(float newValue)
	{
		lodStartDistance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10812FD0
	fight::Property* EffectLODDisableTrack::GetProperty(int index)
	{
		return gEffectLODDisableTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x10812FE0
	void EffectLODDisableTrack::ClearProperties()
	{
		fight::FreePropertyList(&gEffectLODDisableTrackProperties);
	}

	// FUNCTION: ENGINE 0x10812FF0
	// ctor stores: [('mov', 'dword', 0, '0x10e6d0cc'), ('movss', 'dword', 16, '0.0f')]
	EffectLODDisableTrack::EffectLODDisableTrack() : lodStartDistance(0.0f)
	{
	}

	// FUNCTION: ENGINE 0x10813010
	float EffectLODDisableTrack::GetTimeBegin() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x10813020
	float EffectLODDisableTrack::Slot10() const
	{
		return -1.0f;
	}

	// FUNCTION: ENGINE 0x10813030
	EffectLODDisableTrack::~EffectLODDisableTrack()
	{
	}

	// FUNCTION: ENGINE 0x10813110
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void EffectLODDisableTrack::RegisterProperties()
	{
		if (gEffectLODDisableTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<EffectLODDisableTrack>("lodStartDistance", &EffectLODDisableTrack::SetLodStartDistance);
			properties[0] = property;
			fight::RegisterPropertyList(properties, &gEffectLODDisableTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108130F0
	fight::TrackFactory* CreateEffectLODDisableTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<EffectLODDisableTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x10813190
	void RegisterEffectLODDisableTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<EffectLODDisableTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyFloatConstRange<EffectLODDisableTrack>;
	template class fight::TrackFactoryTemplate<EffectLODDisableTrack>;
	template class fight::TrackFactoryCasterTemplate<EffectLODDisableTrack>;

	fight::Property** gEffectLODSwitchTrackProperties;  // 0x11284BF8

	// FUNCTION: ENGINE 0x10813250
	bool EffectLODSwitchTrack::SetLodStartDistance(float newValue)
	{
		lodStartDistance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813260
	bool EffectLODSwitchTrack::SetLodUpdateRateMilliseconds(float newValue)
	{
		lodUpdateRateMilliseconds = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813270
	fight::TrackGroup* EffectLODSwitchTrack::GetEffect()
	{
		return &effect;
	}

	// FUNCTION: ENGINE 0x10813280
	fight::Property* EffectLODSwitchTrack::GetProperty(int index)
	{
		return gEffectLODSwitchTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x10813290
	void EffectLODSwitchTrack::ClearProperties()
	{
		fight::FreePropertyList(&gEffectLODSwitchTrackProperties);
	}

	// FUNCTION: ENGINE 0x108132A0
	// ctor stores: [('mov', 'dword', 0, '0x10e6d174'), ('movss', 'dword', 20, '0.0f'), ('movss', 'dword', 24, '0.0f')]
	EffectLODSwitchTrack::EffectLODSwitchTrack() : lodStartDistance(0.0f), lodUpdateRateMilliseconds(0.0f)
	{
	}

	// FUNCTION: ENGINE 0x108132D0
	float EffectLODSwitchTrack::GetTimeBegin() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x108132E0
	float EffectLODSwitchTrack::Slot10() const
	{
		return -1.0f;
	}

	// FUNCTION: ENGINE 0x108132F0
	EffectLODSwitchTrack::~EffectLODSwitchTrack()
	{
	}

	// FUNCTION: ENGINE 0x10813410
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void EffectLODSwitchTrack::RegisterProperties()
	{
		if (gEffectLODSwitchTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<EffectLODSwitchTrack>("lodStartDistance", &EffectLODSwitchTrack::SetLodStartDistance);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<EffectLODSwitchTrack>("lodUpdateRateMilliseconds", &EffectLODSwitchTrack::SetLodUpdateRateMilliseconds);
			properties[1] = property;
			property = new fight::PropertyTrackGroup<EffectLODSwitchTrack>("effect", &EffectLODSwitchTrack::GetEffect);
			properties[2] = property;
			fight::RegisterPropertyList(properties, &gEffectLODSwitchTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108133F0
	fight::TrackFactory* CreateEffectLODSwitchTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<EffectLODSwitchTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108134F0
	void RegisterEffectLODSwitchTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<EffectLODSwitchTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyFloatConstRange<EffectLODSwitchTrack>;
	template class fight::PropertyTrackGroup<EffectLODSwitchTrack>;
	template class fight::TrackFactoryTemplate<EffectLODSwitchTrack>;
	template class fight::TrackFactoryCasterTemplate<EffectLODSwitchTrack>;

	extern const int gLodBiasesGroupMembers[];
	extern fight::EnumEntry gEffectLODBiasTrackBiasesEmissionRateScaleFunctionTable[];
	extern const int gEffectLODBiasTrackBiasesEmissionRateScaleFunctionCount;
	fight::EnumEntry gEffectLODBiasTrackBiasesSize1DScaleFunctionTable[4] =
		{
			{ fight::Name("Linear", 0) },
			{ fight::Name("Exponential", 0) },
			{ fight::Name("Square root", 0) },
			{ fight::Name("Logarithmic", 0) }
		};
	extern const int gEffectLODBiasTrackBiasesSize1DScaleFunctionCount;
	extern const int gLodOverridesGroupMembers[];

	fight::Property** gEffectLODBiasTrackProperties;  // 0x11284BFC

	// FUNCTION: ENGINE 0x108135B0
	bool EffectLODBiasTrack::SetLodStartDistance(float newValue)
	{
		lodStartDistance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108135D0
	bool EffectLODBiasTrack::SetLodUpdateRateMilliseconds(float newValue)
	{
		lodUpdateRateMilliseconds = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108135F0
	bool EffectLODBiasTrack::SetBiasesEmissionRate(float newValue)
	{
		biasesEmissionRate = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813600
	bool EffectLODBiasTrack::SetBiasesEmissionRateAreaScale(float newValue)
	{
		biasesEmissionRateAreaScale = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813610
	bool EffectLODBiasTrack::SetBiasesEmissionRateScaleFunction(int newValue)
	{
		biasesEmissionRateScaleFunction = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813620
	bool EffectLODBiasTrack::SetBiasesLifeSpan(float newValue)
	{
		biasesLifeSpan = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813630
	bool EffectLODBiasTrack::SetBiasesLifeSpanVariance(float newValue)
	{
		biasesLifeSpanVariance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813650
	bool EffectLODBiasTrack::SetBiasesSpeed(float newValue)
	{
		biasesSpeed = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813670
	bool EffectLODBiasTrack::SetBiasesSpeedVariance(float newValue)
	{
		biasesSpeedVariance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813690
	bool EffectLODBiasTrack::SetBiasesSize1D(float newValue)
	{
		biasesSize1D = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108136B0
	bool EffectLODBiasTrack::SetBiasesSize1DVariance(float newValue)
	{
		biasesSize1DVariance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108136D0
	bool EffectLODBiasTrack::SetBiasesSize1DAreaScale(float newValue)
	{
		biasesSize1DAreaScale = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108136F0
	bool EffectLODBiasTrack::SetBiasesSize1DScaleFunction(int newValue)
	{
		biasesSize1DScaleFunction = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813700
	bool EffectLODBiasTrack::SetBiasesSpin1D(float newValue)
	{
		biasesSpin1D = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813720
	bool EffectLODBiasTrack::SetBiasesSpin1DVariance(float newValue)
	{
		biasesSpin1DVariance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813740
	bool EffectLODBiasTrack::SetBiasesWeight(float newValue)
	{
		biasesWeight = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813760
	bool EffectLODBiasTrack::SetBiasesWeightVariance(float newValue)
	{
		biasesWeightVariance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813780
	bool EffectLODBiasTrack::SetBiasesAngle(float newValue)
	{
		biasesAngle = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813790
	bool EffectLODBiasTrack::SetBiasesAngleVariance(float newValue)
	{
		biasesAngleVariance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108137A0
	bool EffectLODBiasTrack::SetBiasesGravity(float newValue)
	{
		biasesGravity = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108137B0
	bool EffectLODBiasTrack::SetBiasesDrag(float newValue)
	{
		biasesDrag = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108137C0
	bool EffectLODBiasTrack::SetBiasesColourRed(float newValue)
	{
		biasesColourRed = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108137D0
	bool EffectLODBiasTrack::SetBiasesColourGreen(float newValue)
	{
		biasesColourGreen = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108137E0
	bool EffectLODBiasTrack::SetBiasesColourBlue(float newValue)
	{
		biasesColourBlue = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108137F0
	bool EffectLODBiasTrack::SetBiasesAlpha(float newValue)
	{
		biasesAlpha = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813800
	bool EffectLODBiasTrack::SetBiasesColourOverLifeRed(float newValue)
	{
		biasesColourOverLifeRed = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813810
	bool EffectLODBiasTrack::SetBiasesColourOverLifeGreen(float newValue)
	{
		biasesColourOverLifeGreen = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813820
	bool EffectLODBiasTrack::SetBiasesColourOverLifeBlue(float newValue)
	{
		biasesColourOverLifeBlue = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813830
	bool EffectLODBiasTrack::SetBiasesAlphaOverLife(float newValue)
	{
		biasesAlphaOverLife = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813840
	bool EffectLODBiasTrack::SetBiasesColourVariance(float newValue)
	{
		biasesColourVariance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813850
	bool EffectLODBiasTrack::SetBiasesAlphaVariance(float newValue)
	{
		biasesAlphaVariance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813860
	bool EffectLODBiasTrack::SetBiasesGeneratorRadius(float newValue)
	{
		biasesGeneratorRadius = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813870
	bool EffectLODBiasTrack::SetBiasesGeneratorRadial(float newValue)
	{
		biasesGeneratorRadial = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813880
	bool EffectLODBiasTrack::SetBiasesGeneratorHorizSpread(float newValue)
	{
		biasesGeneratorHorizSpread = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813890
	bool EffectLODBiasTrack::SetBiasesGeneratorVertSpread(float newValue)
	{
		biasesGeneratorVertSpread = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108138A0
	bool EffectLODBiasTrack::SetBiasesGeneratorWidth(float newValue)
	{
		biasesGeneratorWidth = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108138B0
	bool EffectLODBiasTrack::SetBiasesGeneratorHeight(float newValue)
	{
		biasesGeneratorHeight = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108138C0
	bool EffectLODBiasTrack::SetBiasesMeshGeneratorScale(const math::Vector& newValue)
	{
		biasesMeshGeneratorScale.x = newValue.x;
		biasesMeshGeneratorScale.y = newValue.y;
		biasesMeshGeneratorScale.z = newValue.z;
		return true;
	}

	// FUNCTION: ENGINE 0x108138E0
	bool EffectLODBiasTrack::SetOverridesEmissionRate(float newValue)
	{
		overridesEmissionRate = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813900
	bool EffectLODBiasTrack::SetOverridesEmissionRatePerMeter(float newValue)
	{
		overridesEmissionRatePerMeter = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813920
	bool EffectLODBiasTrack::SetOverridesMaxParticles(float newValue)
	{
		overridesMaxParticles = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813940
	bool EffectLODBiasTrack::SetOverridesParticleAllocation(float newValue)
	{
		overridesParticleAllocation = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813960
	bool EffectLODBiasTrack::SetOverridesLifeSpan(float newValue)
	{
		overridesLifeSpan = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813980
	bool EffectLODBiasTrack::SetOverridesLifeSpanVariance(float newValue)
	{
		overridesLifeSpanVariance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108139A0
	bool EffectLODBiasTrack::SetOverridesSpeed(float newValue)
	{
		overridesSpeed = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108139C0
	bool EffectLODBiasTrack::SetOverridesSpeedVariance(float newValue)
	{
		overridesSpeedVariance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108139E0
	bool EffectLODBiasTrack::SetOverridesSize1D(float newValue)
	{
		overridesSize1D = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813A00
	bool EffectLODBiasTrack::SetOverridesSize1DVariance(float newValue)
	{
		overridesSize1DVariance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813A20
	bool EffectLODBiasTrack::SetOverridesSpin1D(float newValue)
	{
		overridesSpin1D = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813A40
	bool EffectLODBiasTrack::SetOverridesSpin1DVariance(float newValue)
	{
		overridesSpin1DVariance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813A60
	bool EffectLODBiasTrack::SetOverridesWeight(float newValue)
	{
		overridesWeight = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813A80
	bool EffectLODBiasTrack::SetOverridesWeightVariance(float newValue)
	{
		overridesWeightVariance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813AA0
	bool EffectLODBiasTrack::SetOverridesAngle(float newValue)
	{
		overridesAngle = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813AC0
	bool EffectLODBiasTrack::SetOverridesAngleVariance(float newValue)
	{
		overridesAngleVariance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813AE0
	bool EffectLODBiasTrack::SetOverridesGravity(float newValue)
	{
		overridesGravity = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813B00
	bool EffectLODBiasTrack::SetOverridesDrag(float newValue)
	{
		overridesDrag = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813B20
	bool EffectLODBiasTrack::SetOverridesColourRed(float newValue)
	{
		overridesColourRed = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813B40
	bool EffectLODBiasTrack::SetOverridesColourGreen(float newValue)
	{
		overridesColourGreen = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813B60
	bool EffectLODBiasTrack::SetOverridesColourBlue(float newValue)
	{
		overridesColourBlue = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813B80
	bool EffectLODBiasTrack::SetOverridesAlpha(float newValue)
	{
		overridesAlpha = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813BA0
	bool EffectLODBiasTrack::SetOverridesColourVariance(float newValue)
	{
		overridesColourVariance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813BC0
	bool EffectLODBiasTrack::SetOverridesAlphaVariance(float newValue)
	{
		overridesAlphaVariance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813BE0
	bool EffectLODBiasTrack::SetOverridesGeneratorWidth(float newValue)
	{
		overridesGeneratorWidth = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813C00
	bool EffectLODBiasTrack::SetOverridesGeneratorHeight(float newValue)
	{
		overridesGeneratorHeight = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10813F60
	bool EffectLODBiasTrack::SetBiases(bool newValue)
	{
		biases = newValue;
		ApplyGroup(0, newValue);
		return true;
	}

	// FUNCTION: ENGINE 0x10813F80
	bool EffectLODBiasTrack::SetOverrides(bool newValue)
	{
		overrides = newValue;
		ApplyGroup(1, newValue);
		return true;
	}

	// FUNCTION: ENGINE 0x10813C20
	fight::Property* EffectLODBiasTrack::GetProperty(int index)
	{
		return gEffectLODBiasTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x10813C30
	void EffectLODBiasTrack::ClearProperties()
	{
		fight::FreePropertyList(&gEffectLODBiasTrackProperties);
	}

	// FUNCTION: ENGINE 0x10813C40
	// ctor stores: [('mov', 'dword', 0, '0x10e6d24c'), ('movss', 'dword', 24, '1.0f'), ('movss', 'dword', 28, '1.0f'), ('movss', 'dword', 32, '1.0f'), ('movss', 'dword', 36, '1.0f'), ('movss', 'dword', 40, '1.0f'), ('movss', 'dword', 44, '1.0f'), ('movss', 'dword', 48, '1.0f'), ('movss', 'dword', 52, '1.0f'), ('movss', 'dword', 56, '1.0f'), ('movss', 'dword', 60, '1.0f'), ('movss', 'dword', 64, '1.0f'), ('movss', 'dword', 68, '1.0f'), ('movss', 'dword', 72, '1.0f'), ('movss', 'dword', 76, '1.0f'), ('movss', 'dword', 80, '1.0f'), ('movss', 'dword', 84, '1.0f'), ('movss', 'dword', 88, '1.0f'), ('movss', 'dword', 96, '1.0f'), ('movss', 'dword', 100, '1.0f'), ('movss', 'dword', 104, '1.0f'), ('movss', 'dword', 108, '1.0f'), ('movss', 'dword', 112, '1.0f'), ('movss', 'dword', 116, '1.0f'), ('movss', 'dword', 120, '1.0f'), ('movss', 'dword', 124, '1.0f'), ('movss', 'dword', 128, '1.0f'), ('movss', 'dword', 132, '1.0f'), ('movss', 'dword', 140, '1.0f'), ('movss', 'dword', 144, '1.0f'), ('movss', 'dword', 148, '1.0f'), ('movss', 'dword', 152, '1.0f'), ('movss', 'dword', 156, '1.0f'), ('movss', 'dword', 160, '1.0f'), ('movss', 'dword', 164, '1.0f'), ('mov', 'dword', 280, '0'), ('mov', 'dword', 284, '0'), ('mov', 'byte', 288, '0'), ('mov', 'byte', 289, '0'), ('movss', 'dword', 92, '0.0f'), ('movss', 'dword', 136, '0.0f'), ('movss', 'dword', 168, '0.0f'), ('movss', 'dword', 172, '0.0f'), ('movss', 'dword', 176, '-1.0f'), ('movss', 'dword', 180, '-1.0f'), ('movss', 'dword', 184, '-1.0f'), ('movss', 'dword', 188, '-1.0f'), ('movss', 'dword', 192, '-1.0f'), ('movss', 'dword', 196, '-1.0f'), ('movss', 'dword', 200, '-1.0f'), ('movss', 'dword', 204, '-1.0f'), ('movss', 'dword', 208, '-1.0f'), ('movss', 'dword', 212, '-1.0f'), ('movss', 'dword', 216, '-1.0f'), ('movss', 'dword', 220, '-1.0f'), ('movss', 'dword', 224, '-1.0f'), ('movss', 'dword', 228, '-1.0f'), ('movss', 'dword', 232, '-1.0f'), ('movss', 'dword', 236, '-1.0f'), ('movss', 'dword', 240, '-1.0f'), ('movss', 'dword', 244, '-1.0f'), ('movss', 'dword', 248, '-1.0f'), ('movss', 'dword', 252, '-1.0f'), ('movss', 'dword', 256, '-1.0f'), ('movss', 'dword', 260, '-1.0f'), ('movss', 'dword', 264, '-1.0f'), ('movss', 'dword', 268, '-1.0f'), ('movss', 'dword', 272, '-1.0f'), ('movss', 'dword', 276, '-1.0f')]
	EffectLODBiasTrack::EffectLODBiasTrack() : biasesMeshGeneratorScale(1.0f, 1.0f, 1.0f), biasesAlpha(1.0f), biasesAlphaOverLife(1.0f), biasesAlphaVariance(1.0f), biasesAngle(1.0f), biasesAngleVariance(1.0f), biasesColourBlue(1.0f), biasesColourGreen(1.0f), biasesColourOverLifeBlue(1.0f), biasesColourOverLifeGreen(1.0f), biasesColourOverLifeRed(1.0f), biasesColourRed(1.0f), biasesColourVariance(1.0f), biasesDrag(1.0f), biasesEmissionRate(1.0f), biasesEmissionRateAreaScale(0.0f), biasesGeneratorHeight(1.0f), biasesGeneratorHorizSpread(1.0f), biasesGeneratorRadial(1.0f), biasesGeneratorRadius(1.0f), biasesGeneratorVertSpread(1.0f), biasesGeneratorWidth(1.0f), biasesGravity(1.0f), biasesLifeSpan(1.0f), biasesLifeSpanVariance(1.0f), biasesSize1D(1.0f), biasesSize1DAreaScale(0.0f), biasesSize1DVariance(1.0f), biasesSpeed(1.0f), biasesSpeedVariance(1.0f), biasesSpin1D(1.0f), biasesSpin1DVariance(1.0f), biasesWeight(1.0f), biasesWeightVariance(1.0f), lodStartDistance(0.0f), lodUpdateRateMilliseconds(0.0f), overridesAlpha(-1.0f), overridesAlphaVariance(-1.0f), overridesAngle(-1.0f), overridesAngleVariance(-1.0f), overridesColourBlue(-1.0f), overridesColourGreen(-1.0f), overridesColourRed(-1.0f), overridesColourVariance(-1.0f), overridesDrag(-1.0f), overridesEmissionRate(-1.0f), overridesEmissionRatePerMeter(-1.0f), overridesGeneratorHeight(-1.0f), overridesGeneratorWidth(-1.0f), overridesGravity(-1.0f), overridesLifeSpan(-1.0f), overridesLifeSpanVariance(-1.0f), overridesMaxParticles(-1.0f), overridesParticleAllocation(-1.0f), overridesSize1D(-1.0f), overridesSize1DVariance(-1.0f), overridesSpeed(-1.0f), overridesSpeedVariance(-1.0f), overridesSpin1D(-1.0f), overridesSpin1DVariance(-1.0f), overridesWeight(-1.0f), overridesWeightVariance(-1.0f), biasesEmissionRateScaleFunction(0), biasesSize1DScaleFunction(0), biases(0), overrides(0)
	{
	}

	// FUNCTION: ENGINE 0x10813E40
	bool EffectLODBiasTrack::Slot16(int index)
	{
		return (overrideMask & (1ui64 << index)) != 0;
	}

	// FUNCTION: ENGINE 0x10813EA0
	void EffectLODBiasTrack::ApplyGroup(int group, bool value)
	{
		const int* members;
		switch (group)
		{
		case 0:
			members = gLodBiasesGroupMembers;
			value = value && biases;
			break;
		case 1:
			members = gLodOverridesGroupMembers;
			value = value && overrides;
			break;
		default:
			return;
		}
		for (int i = 0; members[i] != -1; i++)
		{
			const int* member = &members[i];
			unsigned __int64 bit = 1ui64 << *member;
			if (value)
			{
				overrideMask |= bit;
			}
			else
			{
				overrideMask &= ~bit;
			}
			ApplyGroup(*member, value);
		}
	}

	// FUNCTION: ENGINE 0x10813E70
	float EffectLODBiasTrack::GetTimeBegin() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x10813E80
	float EffectLODBiasTrack::Slot10() const
	{
		return -1.0f;
	}

	// FUNCTION: ENGINE 0x10813E90
	EffectLODBiasTrack::~EffectLODBiasTrack()
	{
	}

	// FUNCTION: ENGINE 0x108141A0
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void EffectLODBiasTrack::RegisterProperties()
	{
		if (gEffectLODBiasTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("lodStartDistance", &EffectLODBiasTrack::SetLodStartDistance);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("lodUpdateRateMilliseconds", &EffectLODBiasTrack::SetLodUpdateRateMilliseconds);
			properties[1] = property;
			property = new fight::PropertyGroup<EffectLODBiasTrack>("biases", &EffectLODBiasTrack::SetBiases, gLodBiasesGroupMembers);
			properties[2] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesEmissionRate", &EffectLODBiasTrack::SetBiasesEmissionRate);
			properties[3] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesEmissionRateAreaScale", &EffectLODBiasTrack::SetBiasesEmissionRateAreaScale);
			properties[4] = property;
			property = new fight::PropertyEnumConstList<EffectLODBiasTrack>("biasesEmissionRateScaleFunction", gEffectLODBiasTrackBiasesEmissionRateScaleFunctionTable, gEffectLODBiasTrackBiasesEmissionRateScaleFunctionCount, &EffectLODBiasTrack::SetBiasesEmissionRateScaleFunction);
			properties[5] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesLifeSpan", &EffectLODBiasTrack::SetBiasesLifeSpan);
			properties[6] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesLifeSpanVariance", &EffectLODBiasTrack::SetBiasesLifeSpanVariance);
			properties[7] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesSpeed", &EffectLODBiasTrack::SetBiasesSpeed);
			properties[8] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesSpeedVariance", &EffectLODBiasTrack::SetBiasesSpeedVariance);
			properties[9] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesSize1D", &EffectLODBiasTrack::SetBiasesSize1D);
			properties[10] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesSize1DVariance", &EffectLODBiasTrack::SetBiasesSize1DVariance);
			properties[11] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesSize1DAreaScale", &EffectLODBiasTrack::SetBiasesSize1DAreaScale);
			properties[12] = property;
			property = new fight::PropertyEnumConstList<EffectLODBiasTrack>("biasesSize1DScaleFunction", gEffectLODBiasTrackBiasesSize1DScaleFunctionTable, gEffectLODBiasTrackBiasesSize1DScaleFunctionCount, &EffectLODBiasTrack::SetBiasesSize1DScaleFunction);
			properties[13] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesSpin1D", &EffectLODBiasTrack::SetBiasesSpin1D);
			properties[14] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesSpin1DVariance", &EffectLODBiasTrack::SetBiasesSpin1DVariance);
			properties[15] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesWeight", &EffectLODBiasTrack::SetBiasesWeight);
			properties[16] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesWeightVariance", &EffectLODBiasTrack::SetBiasesWeightVariance);
			properties[17] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesAngle", &EffectLODBiasTrack::SetBiasesAngle);
			properties[18] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesAngleVariance", &EffectLODBiasTrack::SetBiasesAngleVariance);
			properties[19] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesGravity", &EffectLODBiasTrack::SetBiasesGravity);
			properties[20] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesDrag", &EffectLODBiasTrack::SetBiasesDrag);
			properties[21] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesColourRed", &EffectLODBiasTrack::SetBiasesColourRed);
			properties[22] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesColourGreen", &EffectLODBiasTrack::SetBiasesColourGreen);
			properties[23] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesColourBlue", &EffectLODBiasTrack::SetBiasesColourBlue);
			properties[24] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesAlpha", &EffectLODBiasTrack::SetBiasesAlpha);
			properties[25] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesColourOverLifeRed", &EffectLODBiasTrack::SetBiasesColourOverLifeRed);
			properties[26] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesColourOverLifeGreen", &EffectLODBiasTrack::SetBiasesColourOverLifeGreen);
			properties[27] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesColourOverLifeBlue", &EffectLODBiasTrack::SetBiasesColourOverLifeBlue);
			properties[28] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesAlphaOverLife", &EffectLODBiasTrack::SetBiasesAlphaOverLife);
			properties[29] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesColourVariance", &EffectLODBiasTrack::SetBiasesColourVariance);
			properties[30] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesAlphaVariance", &EffectLODBiasTrack::SetBiasesAlphaVariance);
			properties[31] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesGeneratorRadius", &EffectLODBiasTrack::SetBiasesGeneratorRadius);
			properties[32] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesGeneratorRadial", &EffectLODBiasTrack::SetBiasesGeneratorRadial);
			properties[33] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesGeneratorHorizSpread", &EffectLODBiasTrack::SetBiasesGeneratorHorizSpread);
			properties[34] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesGeneratorVertSpread", &EffectLODBiasTrack::SetBiasesGeneratorVertSpread);
			properties[35] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesGeneratorWidth", &EffectLODBiasTrack::SetBiasesGeneratorWidth);
			properties[36] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("biasesGeneratorHeight", &EffectLODBiasTrack::SetBiasesGeneratorHeight);
			properties[37] = property;
			property = new fight::PropertyVector<EffectLODBiasTrack>("biasesMeshGeneratorScale", &EffectLODBiasTrack::SetBiasesMeshGeneratorScale);
			properties[38] = property;
			property = new fight::PropertyGroup<EffectLODBiasTrack>("overrides", &EffectLODBiasTrack::SetOverrides, gLodOverridesGroupMembers);
			properties[39] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("overridesEmissionRate", &EffectLODBiasTrack::SetOverridesEmissionRate);
			properties[40] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("overridesEmissionRatePerMeter", &EffectLODBiasTrack::SetOverridesEmissionRatePerMeter);
			properties[41] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("overridesMaxParticles", &EffectLODBiasTrack::SetOverridesMaxParticles);
			properties[42] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("overridesParticleAllocation", &EffectLODBiasTrack::SetOverridesParticleAllocation);
			properties[43] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("overridesLifeSpan", &EffectLODBiasTrack::SetOverridesLifeSpan);
			properties[44] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("overridesLifeSpanVariance", &EffectLODBiasTrack::SetOverridesLifeSpanVariance);
			properties[45] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("overridesSpeed", &EffectLODBiasTrack::SetOverridesSpeed);
			properties[46] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("overridesSpeedVariance", &EffectLODBiasTrack::SetOverridesSpeedVariance);
			properties[47] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("overridesSize1D", &EffectLODBiasTrack::SetOverridesSize1D);
			properties[48] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("overridesSize1DVariance", &EffectLODBiasTrack::SetOverridesSize1DVariance);
			properties[49] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("overridesSpin1D", &EffectLODBiasTrack::SetOverridesSpin1D);
			properties[50] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("overridesSpin1DVariance", &EffectLODBiasTrack::SetOverridesSpin1DVariance);
			properties[51] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("overridesWeight", &EffectLODBiasTrack::SetOverridesWeight);
			properties[52] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("overridesWeightVariance", &EffectLODBiasTrack::SetOverridesWeightVariance);
			properties[53] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("overridesAngle", &EffectLODBiasTrack::SetOverridesAngle);
			properties[54] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("overridesAngleVariance", &EffectLODBiasTrack::SetOverridesAngleVariance);
			properties[55] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("overridesGravity", &EffectLODBiasTrack::SetOverridesGravity);
			properties[56] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("overridesDrag", &EffectLODBiasTrack::SetOverridesDrag);
			properties[57] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("overridesColourRed", &EffectLODBiasTrack::SetOverridesColourRed);
			properties[58] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("overridesColourGreen", &EffectLODBiasTrack::SetOverridesColourGreen);
			properties[59] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("overridesColourBlue", &EffectLODBiasTrack::SetOverridesColourBlue);
			properties[60] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("overridesAlpha", &EffectLODBiasTrack::SetOverridesAlpha);
			properties[61] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("overridesColourVariance", &EffectLODBiasTrack::SetOverridesColourVariance);
			properties[62] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("overridesAlphaVariance", &EffectLODBiasTrack::SetOverridesAlphaVariance);
			properties[63] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("overridesGeneratorWidth", &EffectLODBiasTrack::SetOverridesGeneratorWidth);
			properties[64] = property;
			property = new fight::PropertyFloatConstRange<EffectLODBiasTrack>("overridesGeneratorHeight", &EffectLODBiasTrack::SetOverridesGeneratorHeight);
			properties[65] = property;
			fight::RegisterPropertyList(properties, &gEffectLODBiasTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x10814180
	fight::TrackFactory* CreateEffectLODBiasTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<EffectLODBiasTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x10814F30
	void RegisterEffectLODBiasTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<EffectLODBiasTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyEnumConstList<EffectLODBiasTrack>;
	template class fight::PropertyFloatConstRange<EffectLODBiasTrack>;
	template class fight::PropertyGroup<EffectLODBiasTrack>;
	template class fight::PropertyVector<EffectLODBiasTrack>;
	template class fight::TrackFactoryTemplate<EffectLODBiasTrack>;
	template class fight::TrackFactoryCasterTemplate<EffectLODBiasTrack>;

}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D74A40
// FUNCTION: ENGINE 0x10D89FE0
