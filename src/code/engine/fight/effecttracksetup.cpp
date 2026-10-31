// The effect tracks' reflected properties, constructors and factories (see effecttrack.h). The unit runs
// 0x1080B9E0 - 0x1080F070 (no assert path; file name guessed).
#include "code/engine/fight/effecttrack.h"

namespace engine
{
	fight::Property** gAbortEffectTrackProperties;  // 0x11284B78

	// FUNCTION: ENGINE 0x1080B9E0
	bool AbortEffectTrack::SetAllowFade(bool newValue)
	{
		allowFade = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080B9F0
	bool AbortEffectTrack::SetFadeTime(float newValue)
	{
		fadeTime = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BA00
	bool AbortEffectTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BA10
	bool AbortEffectTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C740
	bool AbortEffectTrack::SetSlot(const fight::Name& newValue)
	{
		slot = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C640
	fight::Property* AbortEffectTrack::GetProperty(int index)
	{
		return gAbortEffectTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x1080C650
	void AbortEffectTrack::ClearProperties()
	{
		fight::FreePropertyList(&gAbortEffectTrackProperties);
	}

	// FUNCTION: ENGINE 0x1080C940
	// ctor stores: [('mov', 'dword', 0, '0x10e6bdcc'), ('movss', 'dword', 24, '0.0f'), ('movss', 'dword', 28, '0.0f'), ('movss', 'dword', 32, '0.0f'), ('mov', 'byte', 36, '0')]
	AbortEffectTrack::AbortEffectTrack() : fadeTime(0.0f), timeBegin(0.0f), timeEnd(0.0f), allowFade(false)
	{
	}

	// FUNCTION: ENGINE 0x1080C970
	float AbortEffectTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x1080C980
	float AbortEffectTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x1080C990
	AbortEffectTrack::~AbortEffectTrack()
	{
	}

	// FUNCTION: ENGINE 0x1080D6B0
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void AbortEffectTrack::RegisterProperties()
	{
		if (gAbortEffectTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyName<AbortEffectTrack>("slot", &AbortEffectTrack::SetSlot);
			properties[0] = property;
			property = new fight::PropertyBool<AbortEffectTrack>("allowFade", &AbortEffectTrack::SetAllowFade);
			properties[1] = property;
			property = new fight::PropertyFloatConstRange<AbortEffectTrack>("fadeTime", &AbortEffectTrack::SetFadeTime);
			properties[2] = property;
			property = new fight::PropertyFloatConstRange<AbortEffectTrack>("timeBegin", &AbortEffectTrack::SetTimeBegin);
			properties[3] = property;
			property = new fight::PropertyFloatConstRange<AbortEffectTrack>("timeEnd", &AbortEffectTrack::SetTimeEnd);
			properties[4] = property;
			fight::RegisterPropertyList(properties, &gAbortEffectTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x1080D460
	fight::TrackFactory* CreateAbortEffectTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<AbortEffectTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x1080D4C0
	void RegisterAbortEffectTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<AbortEffectTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyBool<AbortEffectTrack>;
	template class fight::PropertyFloatConstRange<AbortEffectTrack>;
	template class fight::PropertyName<AbortEffectTrack>;
	template class fight::TrackFactoryTemplate<AbortEffectTrack>;
	template class fight::TrackFactoryCasterTemplate<AbortEffectTrack>;

	fight::EnumEntry gEffectTrackEmitSpaceTable[6] =
		{
			{ fight::Name("World Space", 0) },
			{ fight::Name("Game Object Space", 0) },
			{ fight::Name("Game Object Start With Global Up Space", 0) },
			{ fight::Name("Joint Space", 0) },
			{ fight::Name("Collision Space", 0) },
			{ fight::Name("Surface Space", 0) }
		};
	extern const int gEffectTrackEmitSpaceCount;
	fight::EnumEntry gEffectTrackAttachSpaceTable[3] =
		{
			{ fight::Name("World Space", 0) },
			{ fight::Name("Game Object Space", 0) },
			{ fight::Name("Joint Space", 0) }
		};
	extern const int gEffectTrackAttachSpaceCount;
	extern fight::EnumEntry gEffectTrackEffectStoreTable[];
	extern const int gEffectTrackEffectStoreCount;
	extern const int gEffectTrackBiasesMembers[];
	extern fight::EnumEntry gEffectTrackBiasesEmissionRateScaleFunctionTable[];
	extern const int gEffectTrackBiasesEmissionRateScaleFunctionCount;
	extern fight::EnumEntry gEffectTrackBiasesSize1DScaleFunctionTable[];
	extern const int gEffectTrackBiasesSize1DScaleFunctionCount;
	extern const int gEffectTrackOverridesMembers[];

	fight::Property** gEffectTrackProperties;  // 0x11284B7C

	// FUNCTION: ENGINE 0x1080BA20
	bool EffectTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BA40
	bool EffectTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BA60
	bool EffectTrack::SetEmitSpace(int newValue)
	{
		emitSpace = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BA70
	bool EffectTrack::SetOffset(const math::Vector& newValue)
	{
		offset.x = newValue.x;
		offset.y = newValue.y;
		offset.z = newValue.z;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BA90
	bool EffectTrack::SetOrientation(const math::Vector& newValue)
	{
		// Degrees in the property, radians in the track
		math::Vector v(newValue.x, newValue.y, newValue.z);
		v.Scale(0.017453292f);
		orientation.x = v.x;
		orientation.y = v.y;
		orientation.z = v.z;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BAD0
	bool EffectTrack::SetAttachSpace(int newValue)
	{
		attachSpace = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BAE0
	bool EffectTrack::SetAbortWhenInterrupted(bool newValue)
	{
		abortWhenInterrupted = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BAF0
	bool EffectTrack::SetAbortBelowJointScale(float newValue)
	{
		abortBelowJointScale = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BB10
	bool EffectTrack::SetFadeTime(float newValue)
	{
		fadeTime = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BB30
	bool EffectTrack::SetEffectStore(int newValue)
	{
		effectStore = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BB40
	bool EffectTrack::SetHighPriority(bool newValue)
	{
		highPriority = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BB50
	bool EffectTrack::SetScale(float newValue)
	{
		scale = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BB70
	bool EffectTrack::SetCollides(bool newValue)
	{
		collides = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BB80
	bool EffectTrack::SetRestitution(float newValue)
	{
		restitution = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BBA0
	bool EffectTrack::SetFriction(float newValue)
	{
		friction = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BBC0
	bool EffectTrack::SetRenderOffset(float newValue)
	{
		renderOffset = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BBE0
	bool EffectTrack::SetUsePropScaling(bool newValue)
	{
		usePropScaling = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BBF0
	bool EffectTrack::SetCloneTint(const math::Colour128& newValue)
	{
		cloneTint = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BC10
	bool EffectTrack::SetBiasesEmissionRate(float newValue)
	{
		biasesEmissionRate = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BC30
	bool EffectTrack::SetBiasesEmissionRateAreaScale(float newValue)
	{
		biasesEmissionRateAreaScale = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BC50
	bool EffectTrack::SetBiasesEmissionRateScaleFunction(int newValue)
	{
		biasesEmissionRateScaleFunction = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BC60
	bool EffectTrack::SetBiasesLifeSpan(float newValue)
	{
		biasesLifeSpan = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BC80
	bool EffectTrack::SetBiasesLifeSpanVariance(float newValue)
	{
		biasesLifeSpanVariance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BCA0
	bool EffectTrack::SetBiasesSpeed(float newValue)
	{
		biasesSpeed = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BCC0
	bool EffectTrack::SetBiasesSpeedVariance(float newValue)
	{
		biasesSpeedVariance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BCE0
	bool EffectTrack::SetBiasesSize1D(float newValue)
	{
		biasesSize1D = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BD00
	bool EffectTrack::SetBiasesSize1DVariance(float newValue)
	{
		biasesSize1DVariance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BD20
	bool EffectTrack::SetBiasesSize1DAreaScale(float newValue)
	{
		biasesSize1DAreaScale = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BD40
	bool EffectTrack::SetBiasesSize1DScaleFunction(int newValue)
	{
		biasesSize1DScaleFunction = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BD50
	bool EffectTrack::SetBiasesSpin1D(float newValue)
	{
		biasesSpin1D = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BD70
	bool EffectTrack::SetBiasesSpin1DVariance(float newValue)
	{
		biasesSpin1DVariance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BD90
	bool EffectTrack::SetBiasesWeight(float newValue)
	{
		biasesWeight = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BDB0
	bool EffectTrack::SetBiasesWeightVariance(float newValue)
	{
		biasesWeightVariance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BDD0
	bool EffectTrack::SetBiasesAngle(float newValue)
	{
		biasesAngle = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BDF0
	bool EffectTrack::SetBiasesAngleVariance(float newValue)
	{
		biasesAngleVariance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BE10
	bool EffectTrack::SetBiasesGravity(float newValue)
	{
		biasesGravity = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BE30
	bool EffectTrack::SetBiasesDrag(float newValue)
	{
		biasesDrag = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BE50
	bool EffectTrack::SetBiasesColourRed(float newValue)
	{
		biasesColourRed = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BE70
	bool EffectTrack::SetBiasesColourGreen(float newValue)
	{
		biasesColourGreen = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BE90
	bool EffectTrack::SetBiasesColourBlue(float newValue)
	{
		biasesColourBlue = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BEB0
	bool EffectTrack::SetBiasesAlpha(float newValue)
	{
		biasesAlpha = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BED0
	bool EffectTrack::SetBiasesColourOverLifeRed(float newValue)
	{
		biasesColourOverLifeRed = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BEF0
	bool EffectTrack::SetBiasesColourOverLifeGreen(float newValue)
	{
		biasesColourOverLifeGreen = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BF10
	bool EffectTrack::SetBiasesColourOverLifeBlue(float newValue)
	{
		biasesColourOverLifeBlue = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BF30
	bool EffectTrack::SetBiasesAlphaOverLife(float newValue)
	{
		biasesAlphaOverLife = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BF50
	bool EffectTrack::SetBiasesColourVariance(float newValue)
	{
		biasesColourVariance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BF70
	bool EffectTrack::SetBiasesAlphaVariance(float newValue)
	{
		biasesAlphaVariance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BF90
	bool EffectTrack::SetBiasesGeneratorRadius(float newValue)
	{
		biasesGeneratorRadius = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BFB0
	bool EffectTrack::SetBiasesGeneratorRadial(float newValue)
	{
		biasesGeneratorRadial = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BFD0
	bool EffectTrack::SetBiasesGeneratorHorizSpread(float newValue)
	{
		biasesGeneratorHorizSpread = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080BFF0
	bool EffectTrack::SetBiasesGeneratorVertSpread(float newValue)
	{
		biasesGeneratorVertSpread = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C010
	bool EffectTrack::SetBiasesGeneratorWidth(float newValue)
	{
		biasesGeneratorWidth = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C030
	bool EffectTrack::SetBiasesGeneratorHeight(float newValue)
	{
		biasesGeneratorHeight = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C050
	bool EffectTrack::SetBiasesMeshGeneratorScale(const math::Vector& newValue)
	{
		biasesMeshGeneratorScale.x = newValue.x;
		biasesMeshGeneratorScale.y = newValue.y;
		biasesMeshGeneratorScale.z = newValue.z;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C070
	bool EffectTrack::SetOverridesEmissionRate(float newValue)
	{
		overridesEmissionRate = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C090
	bool EffectTrack::SetOverridesEmissionRatePerMeter(float newValue)
	{
		overridesEmissionRatePerMeter = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C0B0
	bool EffectTrack::SetOverridesMaxParticles(float newValue)
	{
		overridesMaxParticles = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C0D0
	bool EffectTrack::SetOverridesParticleAllocation(float newValue)
	{
		overridesParticleAllocation = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C0F0
	bool EffectTrack::SetOverridesLifeSpan(float newValue)
	{
		overridesLifeSpan = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C110
	bool EffectTrack::SetOverridesLifeSpanVariance(float newValue)
	{
		overridesLifeSpanVariance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C130
	bool EffectTrack::SetOverridesSpeed(float newValue)
	{
		overridesSpeed = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C150
	bool EffectTrack::SetOverridesSpeedVariance(float newValue)
	{
		overridesSpeedVariance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C170
	bool EffectTrack::SetOverridesSize1D(float newValue)
	{
		overridesSize1D = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C190
	bool EffectTrack::SetOverridesSize1DVariance(float newValue)
	{
		overridesSize1DVariance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C1B0
	bool EffectTrack::SetOverridesSpin1D(float newValue)
	{
		overridesSpin1D = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C1D0
	bool EffectTrack::SetOverridesSpin1DVariance(float newValue)
	{
		overridesSpin1DVariance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C1F0
	bool EffectTrack::SetOverridesWeight(float newValue)
	{
		overridesWeight = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C210
	bool EffectTrack::SetOverridesWeightVariance(float newValue)
	{
		overridesWeightVariance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C230
	bool EffectTrack::SetOverridesAngle(float newValue)
	{
		overridesAngle = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C250
	bool EffectTrack::SetOverridesAngleVariance(float newValue)
	{
		overridesAngleVariance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C270
	bool EffectTrack::SetOverridesGravity(float newValue)
	{
		overridesGravity = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C290
	bool EffectTrack::SetOverridesDrag(float newValue)
	{
		overridesDrag = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C2B0
	bool EffectTrack::SetOverridesColourRed(float newValue)
	{
		overridesColourRed = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C2D0
	bool EffectTrack::SetOverridesColourGreen(float newValue)
	{
		overridesColourGreen = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C2F0
	bool EffectTrack::SetOverridesColourBlue(float newValue)
	{
		overridesColourBlue = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C310
	bool EffectTrack::SetOverridesAlpha(float newValue)
	{
		overridesAlpha = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C330
	bool EffectTrack::SetOverridesColourVariance(float newValue)
	{
		overridesColourVariance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C350
	bool EffectTrack::SetOverridesAlphaVariance(float newValue)
	{
		overridesAlphaVariance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C370
	bool EffectTrack::SetOverridesGeneratorWidth(float newValue)
	{
		overridesGeneratorWidth = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C390
	bool EffectTrack::SetOverridesGeneratorHeight(float newValue)
	{
		overridesGeneratorHeight = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C3B0
	fight::TrackGroup* EffectTrack::GetLods()
	{
		return &lods;
	}

	// FUNCTION: ENGINE 0x1080C760
	bool EffectTrack::SetEffectName(const fight::Name& newValue)
	{
		effectName = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C780
	bool EffectTrack::SetParentObjectName(const fight::Name& newValue)
	{
		parentObjectName = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C7A0
	bool EffectTrack::SetEmitJoint(const fight::Name& newValue)
	{
		emitJoint = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C7C0
	bool EffectTrack::SetAttachJoint(const fight::Name& newValue)
	{
		attachJoint = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C7E0
	bool EffectTrack::SetSlot(const fight::Name& newValue)
	{
		slot = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C800
	bool EffectTrack::SetEffectController(const fight::Name& newValue)
	{
		effectController = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C820
	bool EffectTrack::SetCloneName(const fight::Name& newValue)
	{
		cloneName = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080CD30
	bool EffectTrack::SetBiases(bool newValue)
	{
		biases = newValue;
		ApplyGroup(0, newValue);
		return true;
	}

	// FUNCTION: ENGINE 0x1080CD50
	bool EffectTrack::SetOverrides(bool newValue)
	{
		overrides = newValue;
		ApplyGroup(1, newValue);
		return true;
	}

	// FUNCTION: ENGINE 0x1080C660
	fight::Property* EffectTrack::GetProperty(int index)
	{
		return gEffectTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x1080C670
	void EffectTrack::ClearProperties()
	{
		fight::FreePropertyList(&gEffectTrackProperties);
	}

	// FUNCTION: ENGINE 0x1080C9A0
	// ctor stores: [('mov', 'dword', 0, '0x10e6be14'), ('movss', 'dword', 80, '1.0f'), ('movss', 'dword', 84, '1.0f'), ('movss', 'dword', 88, '1.0f'), ('movss', 'dword', 92, '1.0f'), ('movss', 'dword', 96, '1.0f'), ('movss', 'dword', 100, '1.0f'), ('movss', 'dword', 104, '1.0f'), ('movss', 'dword', 108, '0.0f'), ('movss', 'dword', 112, '0.0f'), ('movss', 'dword', 116, '0.0f'), ('movss', 'dword', 120, '0.0f'), ('movss', 'dword', 124, '0.0f'), ('movss', 'dword', 128, '0.0f'), ('movss', 'dword', 136, '-1.0f'), ('movss', 'dword', 140, '1.0f'), ('movss', 'dword', 144, '1.0f'), ('movss', 'dword', 148, '1.0f'), ('movss', 'dword', 152, '1.0f'), ('movss', 'dword', 156, '1.0f'), ('movss', 'dword', 160, '1.0f'), ('movss', 'dword', 164, '1.0f'), ('movss', 'dword', 168, '1.0f'), ('movss', 'dword', 172, '1.0f'), ('movss', 'dword', 176, '1.0f'), ('movss', 'dword', 180, '1.0f'), ('movss', 'dword', 184, '1.0f'), ('movss', 'dword', 188, '1.0f'), ('movss', 'dword', 192, '1.0f'), ('movss', 'dword', 196, '0.0f'), ('movss', 'dword', 200, '1.0f'), ('movss', 'dword', 204, '1.0f'), ('movss', 'dword', 208, '1.0f'), ('movss', 'dword', 212, '1.0f'), ('movss', 'dword', 216, '1.0f'), ('movss', 'dword', 220, '1.0f'), ('movss', 'dword', 224, '1.0f'), ('movss', 'dword', 228, '1.0f'), ('movss', 'dword', 232, '1.0f'), ('movss', 'dword', 236, '1.0f'), ('movss', 'dword', 240, '0.0f'), ('movss', 'dword', 244, '1.0f'), ('movss', 'dword', 248, '1.0f'), ('movss', 'dword', 252, '1.0f'), ('movss', 'dword', 256, '1.0f'), ('movss', 'dword', 260, '1.0f'), ('movss', 'dword', 264, '1.0f'), ('movss', 'dword', 268, '1.0f'), ('movss', 'dword', 272, '0.0f'), ('movss', 'dword', 276, '1.0f'), ('movss', 'dword', 280, '-1.0f'), ('movss', 'dword', 284, '-1.0f'), ('movss', 'dword', 288, '-1.0f'), ('movss', 'dword', 292, '-1.0f'), ('movss', 'dword', 296, '-1.0f'), ('movss', 'dword', 300, '-1.0f'), ('movss', 'dword', 304, '-1.0f'), ('movss', 'dword', 308, '-1.0f'), ('movss', 'dword', 312, '-1.0f'), ('movss', 'dword', 316, '-1.0f'), ('movss', 'dword', 320, '-1.0f'), ('movss', 'dword', 324, '-1.0f'), ('movss', 'dword', 328, '-1.0f'), ('movss', 'dword', 332, '-1.0f'), ('movss', 'dword', 336, '-1.0f'), ('movss', 'dword', 340, '-1.0f'), ('movss', 'dword', 344, '-1.0f'), ('movss', 'dword', 348, '-1.0f'), ('movss', 'dword', 352, '-1.0f'), ('movss', 'dword', 356, '-1.0f'), ('movss', 'dword', 360, '-1.0f'), ('movss', 'dword', 364, '-1.0f'), ('movss', 'dword', 368, '-1.0f'), ('movss', 'dword', 372, '-1.0f'), ('movss', 'dword', 376, '-1.0f'), ('movss', 'dword', 380, '-1.0f'), ('mov', 'dword', 408, '0'), ('mov', 'dword', 412, '0'), ('mov', 'dword', 416, '0'), ('mov', 'byte', 424, '0'), ('mov', 'byte', 426, '0'), ('mov', 'byte', 427, '0'), ('movss', 'dword', 384, '0.0f'), ('movss', 'dword', 388, '0.5f'), ('movss', 'dword', 392, '1.0f'), ('movss', 'dword', 396, '0.0f'), ('movss', 'dword', 400, '0.0f'), ('mov', 'dword', 404, '1'), ('mov', 'dword', 420, '1'), ('mov', 'byte', 425, '1'), ('mov', 'byte', 428, '1'), ('mov', 'byte', 429, '1')]
	EffectTrack::EffectTrack() : cloneTint(1.0f, 1.0f, 1.0f, 1.0f), biasesMeshGeneratorScale(1.0f, 1.0f, 1.0f), offset(0.0f, 0.0f, 0.0f), orientation(0.0f, 0.0f, 0.0f), abortBelowJointScale(-1.0f), biasesAlpha(1.0f), biasesAlphaOverLife(1.0f), biasesAlphaVariance(1.0f), biasesAngle(1.0f), biasesAngleVariance(1.0f), biasesColourBlue(1.0f), biasesColourGreen(1.0f), biasesColourOverLifeBlue(1.0f), biasesColourOverLifeGreen(1.0f), biasesColourOverLifeRed(1.0f), biasesColourRed(1.0f), biasesColourVariance(1.0f), biasesDrag(1.0f), biasesEmissionRate(1.0f), biasesEmissionRateAreaScale(0.0f), biasesGeneratorHeight(1.0f), biasesGeneratorHorizSpread(1.0f), biasesGeneratorRadial(1.0f), biasesGeneratorRadius(1.0f), biasesGeneratorVertSpread(1.0f), biasesGeneratorWidth(1.0f), biasesGravity(1.0f), biasesLifeSpan(1.0f), biasesLifeSpanVariance(1.0f), biasesSize1D(1.0f), biasesSize1DAreaScale(0.0f), biasesSize1DVariance(1.0f), biasesSpeed(1.0f), biasesSpeedVariance(1.0f), biasesSpin1D(1.0f), biasesSpin1DVariance(1.0f), biasesWeight(1.0f), biasesWeightVariance(1.0f), fadeTime(0.0f), friction(1.0f), overridesAlpha(-1.0f), overridesAlphaVariance(-1.0f), overridesAngle(-1.0f), overridesAngleVariance(-1.0f), overridesColourBlue(-1.0f), overridesColourGreen(-1.0f), overridesColourRed(-1.0f), overridesColourVariance(-1.0f), overridesDrag(-1.0f), overridesEmissionRate(-1.0f), overridesEmissionRatePerMeter(-1.0f), overridesGeneratorHeight(-1.0f), overridesGeneratorWidth(-1.0f), overridesGravity(-1.0f), overridesLifeSpan(-1.0f), overridesLifeSpanVariance(-1.0f), overridesMaxParticles(-1.0f), overridesParticleAllocation(-1.0f), overridesSize1D(-1.0f), overridesSize1DVariance(-1.0f), overridesSpeed(-1.0f), overridesSpeedVariance(-1.0f), overridesSpin1D(-1.0f), overridesSpin1DVariance(-1.0f), overridesWeight(-1.0f), overridesWeightVariance(-1.0f), renderOffset(0.0f), restitution(0.5f), scale(1.0f), timeBegin(0.0f), timeEnd(0.0f), attachSpace(1), biasesEmissionRateScaleFunction(0), biasesSize1DScaleFunction(0), effectStore(0), emitSpace(1), abortWhenInterrupted(false), biases(1), collides(false), highPriority(false), overrides(1), usePropScaling(1)
	{
	}

	// FUNCTION: ENGINE 0x1080CCC0
	float EffectTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x1080CCD0
	bool EffectTrack::Slot16(int index)
	{
		return (overrideMask & (1ui64 << index)) != 0;
	}

	// FUNCTION: ENGINE 0x1080C680
	void EffectTrack::ApplyGroup(int group, bool value)
	{
		const int* members;
		switch (group)
		{
		case 0:
			members = gEffectTrackBiasesMembers;
			value = value && biases;
			break;
		case 1:
			members = gEffectTrackOverridesMembers;
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

	// FUNCTION: ENGINE 0x1080CD00
	float EffectTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x1080CD10
	EffectTrack::~EffectTrack()
	{
	}

	// FUNCTION: ENGINE 0x1080D7F0
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void EffectTrack::RegisterProperties()
	{
		if (gEffectTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<EffectTrack>("timeBegin", &EffectTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("timeEnd", &EffectTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyName<EffectTrack>("effectName", &EffectTrack::SetEffectName);
			properties[2] = property;
			property = new fight::PropertyName<EffectTrack>("parentObjectName", &EffectTrack::SetParentObjectName);
			properties[3] = property;
			property = new fight::PropertyEnumConstList<EffectTrack>("emitSpace", gEffectTrackEmitSpaceTable, gEffectTrackEmitSpaceCount, &EffectTrack::SetEmitSpace);
			properties[4] = property;
			property = new fight::PropertyNameList<EffectTrack>("emitJoint", &EffectTrack::SetEmitJoint);
			properties[5] = property;
			property = new fight::PropertyVector<EffectTrack>("offset", &EffectTrack::SetOffset);
			properties[6] = property;
			property = new fight::PropertyVector<EffectTrack>("orientation", &EffectTrack::SetOrientation);
			properties[7] = property;
			property = new fight::PropertyEnumConstList<EffectTrack>("attachSpace", gEffectTrackAttachSpaceTable, gEffectTrackAttachSpaceCount, &EffectTrack::SetAttachSpace);
			properties[8] = property;
			property = new fight::PropertyNameList<EffectTrack>("attachJoint", &EffectTrack::SetAttachJoint);
			properties[9] = property;
			property = new fight::PropertyBool<EffectTrack>("abortWhenInterrupted", &EffectTrack::SetAbortWhenInterrupted);
			properties[10] = property;
			property = new fight::PropertyName<EffectTrack>("slot", &EffectTrack::SetSlot);
			properties[11] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("abortBelowJointScale", &EffectTrack::SetAbortBelowJointScale);
			properties[12] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("fadeTime", &EffectTrack::SetFadeTime);
			properties[13] = property;
			property = new fight::PropertyName<EffectTrack>("effectController", &EffectTrack::SetEffectController);
			properties[14] = property;
			property = new fight::PropertyEnumConstList<EffectTrack>("effectStore", gEffectTrackEffectStoreTable, gEffectTrackEffectStoreCount, &EffectTrack::SetEffectStore);
			properties[15] = property;
			property = new fight::PropertyBool<EffectTrack>("highPriority", &EffectTrack::SetHighPriority);
			properties[16] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("scale", &EffectTrack::SetScale);
			properties[17] = property;
			property = new fight::PropertyBool<EffectTrack>("collides", &EffectTrack::SetCollides);
			properties[18] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("restitution", &EffectTrack::SetRestitution);
			properties[19] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("friction", &EffectTrack::SetFriction);
			properties[20] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("renderOffset", &EffectTrack::SetRenderOffset);
			properties[21] = property;
			property = new fight::PropertyBool<EffectTrack>("usePropScaling", &EffectTrack::SetUsePropScaling);
			properties[22] = property;
			property = new fight::PropertyName<EffectTrack>("cloneName", &EffectTrack::SetCloneName);
			properties[23] = property;
			property = new fight::PropertyColour<EffectTrack>("cloneTint", &EffectTrack::SetCloneTint);
			properties[24] = property;
			property = new fight::PropertyGroup<EffectTrack>("biases", &EffectTrack::SetBiases, gEffectTrackBiasesMembers);
			properties[25] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesEmissionRate", &EffectTrack::SetBiasesEmissionRate);
			properties[26] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesEmissionRateAreaScale", &EffectTrack::SetBiasesEmissionRateAreaScale);
			properties[27] = property;
			property = new fight::PropertyEnumConstList<EffectTrack>("biasesEmissionRateScaleFunction", gEffectTrackBiasesEmissionRateScaleFunctionTable, gEffectTrackBiasesEmissionRateScaleFunctionCount, &EffectTrack::SetBiasesEmissionRateScaleFunction);
			properties[28] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesLifeSpan", &EffectTrack::SetBiasesLifeSpan);
			properties[29] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesLifeSpanVariance", &EffectTrack::SetBiasesLifeSpanVariance);
			properties[30] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesSpeed", &EffectTrack::SetBiasesSpeed);
			properties[31] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesSpeedVariance", &EffectTrack::SetBiasesSpeedVariance);
			properties[32] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesSize1D", &EffectTrack::SetBiasesSize1D);
			properties[33] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesSize1DVariance", &EffectTrack::SetBiasesSize1DVariance);
			properties[34] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesSize1DAreaScale", &EffectTrack::SetBiasesSize1DAreaScale);
			properties[35] = property;
			property = new fight::PropertyEnumConstList<EffectTrack>("biasesSize1DScaleFunction", gEffectTrackBiasesSize1DScaleFunctionTable, gEffectTrackBiasesSize1DScaleFunctionCount, &EffectTrack::SetBiasesSize1DScaleFunction);
			properties[36] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesSpin1D", &EffectTrack::SetBiasesSpin1D);
			properties[37] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesSpin1DVariance", &EffectTrack::SetBiasesSpin1DVariance);
			properties[38] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesWeight", &EffectTrack::SetBiasesWeight);
			properties[39] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesWeightVariance", &EffectTrack::SetBiasesWeightVariance);
			properties[40] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesAngle", &EffectTrack::SetBiasesAngle);
			properties[41] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesAngleVariance", &EffectTrack::SetBiasesAngleVariance);
			properties[42] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesGravity", &EffectTrack::SetBiasesGravity);
			properties[43] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesDrag", &EffectTrack::SetBiasesDrag);
			properties[44] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesColourRed", &EffectTrack::SetBiasesColourRed);
			properties[45] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesColourGreen", &EffectTrack::SetBiasesColourGreen);
			properties[46] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesColourBlue", &EffectTrack::SetBiasesColourBlue);
			properties[47] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesAlpha", &EffectTrack::SetBiasesAlpha);
			properties[48] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesColourOverLifeRed", &EffectTrack::SetBiasesColourOverLifeRed);
			properties[49] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesColourOverLifeGreen", &EffectTrack::SetBiasesColourOverLifeGreen);
			properties[50] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesColourOverLifeBlue", &EffectTrack::SetBiasesColourOverLifeBlue);
			properties[51] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesAlphaOverLife", &EffectTrack::SetBiasesAlphaOverLife);
			properties[52] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesColourVariance", &EffectTrack::SetBiasesColourVariance);
			properties[53] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesAlphaVariance", &EffectTrack::SetBiasesAlphaVariance);
			properties[54] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesGeneratorRadius", &EffectTrack::SetBiasesGeneratorRadius);
			properties[55] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesGeneratorRadial", &EffectTrack::SetBiasesGeneratorRadial);
			properties[56] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesGeneratorHorizSpread", &EffectTrack::SetBiasesGeneratorHorizSpread);
			properties[57] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesGeneratorVertSpread", &EffectTrack::SetBiasesGeneratorVertSpread);
			properties[58] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesGeneratorWidth", &EffectTrack::SetBiasesGeneratorWidth);
			properties[59] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("biasesGeneratorHeight", &EffectTrack::SetBiasesGeneratorHeight);
			properties[60] = property;
			property = new fight::PropertyVector<EffectTrack>("biasesMeshGeneratorScale", &EffectTrack::SetBiasesMeshGeneratorScale);
			properties[61] = property;
			property = new fight::PropertyGroup<EffectTrack>("overrides", &EffectTrack::SetOverrides, gEffectTrackOverridesMembers);
			properties[62] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("overridesEmissionRate", &EffectTrack::SetOverridesEmissionRate);
			properties[63] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("overridesEmissionRatePerMeter", &EffectTrack::SetOverridesEmissionRatePerMeter);
			properties[64] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("overridesMaxParticles", &EffectTrack::SetOverridesMaxParticles);
			properties[65] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("overridesParticleAllocation", &EffectTrack::SetOverridesParticleAllocation);
			properties[66] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("overridesLifeSpan", &EffectTrack::SetOverridesLifeSpan);
			properties[67] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("overridesLifeSpanVariance", &EffectTrack::SetOverridesLifeSpanVariance);
			properties[68] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("overridesSpeed", &EffectTrack::SetOverridesSpeed);
			properties[69] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("overridesSpeedVariance", &EffectTrack::SetOverridesSpeedVariance);
			properties[70] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("overridesSize1D", &EffectTrack::SetOverridesSize1D);
			properties[71] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("overridesSize1DVariance", &EffectTrack::SetOverridesSize1DVariance);
			properties[72] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("overridesSpin1D", &EffectTrack::SetOverridesSpin1D);
			properties[73] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("overridesSpin1DVariance", &EffectTrack::SetOverridesSpin1DVariance);
			properties[74] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("overridesWeight", &EffectTrack::SetOverridesWeight);
			properties[75] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("overridesWeightVariance", &EffectTrack::SetOverridesWeightVariance);
			properties[76] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("overridesAngle", &EffectTrack::SetOverridesAngle);
			properties[77] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("overridesAngleVariance", &EffectTrack::SetOverridesAngleVariance);
			properties[78] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("overridesGravity", &EffectTrack::SetOverridesGravity);
			properties[79] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("overridesDrag", &EffectTrack::SetOverridesDrag);
			properties[80] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("overridesColourRed", &EffectTrack::SetOverridesColourRed);
			properties[81] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("overridesColourGreen", &EffectTrack::SetOverridesColourGreen);
			properties[82] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("overridesColourBlue", &EffectTrack::SetOverridesColourBlue);
			properties[83] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("overridesAlpha", &EffectTrack::SetOverridesAlpha);
			properties[84] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("overridesColourVariance", &EffectTrack::SetOverridesColourVariance);
			properties[85] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("overridesAlphaVariance", &EffectTrack::SetOverridesAlphaVariance);
			properties[86] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("overridesGeneratorWidth", &EffectTrack::SetOverridesGeneratorWidth);
			properties[87] = property;
			property = new fight::PropertyFloatConstRange<EffectTrack>("overridesGeneratorHeight", &EffectTrack::SetOverridesGeneratorHeight);
			properties[88] = property;
			property = new fight::PropertyTrackGroup<EffectTrack>("lods", &EffectTrack::GetLods);
			properties[89] = property;
			fight::RegisterPropertyList(properties, &gEffectTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x1080D480
	fight::TrackFactory* CreateEffectTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<EffectTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x1080D4F0
	void RegisterEffectTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<EffectTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyBool<EffectTrack>;
	template class fight::PropertyColour<EffectTrack>;
	template class fight::PropertyEnumConstList<EffectTrack>;
	template class fight::PropertyFloatConstRange<EffectTrack>;
	template class fight::PropertyGroup<EffectTrack>;
	template class fight::PropertyName<EffectTrack>;
	template class fight::PropertyNameList<EffectTrack>;
	template class fight::PropertyTrackGroup<EffectTrack>;
	template class fight::PropertyVector<EffectTrack>;
	template class fight::TrackFactoryTemplate<EffectTrack>;
	template class fight::TrackFactoryCasterTemplate<EffectTrack>;

	fight::Property** gMotionTrailTrackProperties;  // 0x11284B80

	// FUNCTION: ENGINE 0x1080C3C0
	bool MotionTrailTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C3E0
	bool MotionTrailTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C400
	bool MotionTrailTrack::SetGenerateTime(float newValue)
	{
		generateTime = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C420
	bool MotionTrailTrack::SetFadeInTime(float newValue)
	{
		fadeInTime = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C440
	bool MotionTrailTrack::SetFadeOutTime(float newValue)
	{
		fadeOutTime = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C460
	bool MotionTrailTrack::SetTextureTime(float newValue)
	{
		textureTime = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C480
	bool MotionTrailTrack::SetFadeTime(float newValue)
	{
		fadeTime = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C4A0
	bool MotionTrailTrack::SetFadeInTrailTime(float newValue)
	{
		fadeInTrailTime = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C4C0
	bool MotionTrailTrack::SetShrinkTime(float newValue)
	{
		shrinkTime = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C4E0
	bool MotionTrailTrack::SetDragged(bool newValue)
	{
		dragged = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C4F0
	bool MotionTrailTrack::SetShrinkOffset(const math::Vector& newValue)
	{
		shrinkOffset.x = newValue.x;
		shrinkOffset.y = newValue.y;
		shrinkOffset.z = newValue.z;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C520
	bool MotionTrailTrack::SetNumJoints(int newValue)
	{
		numJoints = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C530
	bool MotionTrailTrack::SetJointOffset1(const math::Vector& newValue)
	{
		jointOffset1.x = newValue.x;
		jointOffset1.y = newValue.y;
		jointOffset1.z = newValue.z;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C550
	bool MotionTrailTrack::SetJointOffset2(const math::Vector& newValue)
	{
		jointOffset2.x = newValue.x;
		jointOffset2.y = newValue.y;
		jointOffset2.z = newValue.z;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C570
	bool MotionTrailTrack::SetJointOffset3(const math::Vector& newValue)
	{
		jointOffset3.x = newValue.x;
		jointOffset3.y = newValue.y;
		jointOffset3.z = newValue.z;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C590
	bool MotionTrailTrack::SetJointOffset4(const math::Vector& newValue)
	{
		jointOffset4.x = newValue.x;
		jointOffset4.y = newValue.y;
		jointOffset4.z = newValue.z;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C5B0
	bool MotionTrailTrack::SetJointOffset5(const math::Vector& newValue)
	{
		jointOffset5.x = newValue.x;
		jointOffset5.y = newValue.y;
		jointOffset5.z = newValue.z;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C5E0
	bool MotionTrailTrack::SetJointOffset6(const math::Vector& newValue)
	{
		jointOffset6.x = newValue.x;
		jointOffset6.y = newValue.y;
		jointOffset6.z = newValue.z;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C610
	bool MotionTrailTrack::SetAbortWhenInterrupted(bool newValue)
	{
		abortWhenInterrupted = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C620
	bool MotionTrailTrack::SetRunTillStop(bool newValue)
	{
		runTillStop = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C630
	bool MotionTrailTrack::SetSlot(int newValue)
	{
		slot = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C840
	bool MotionTrailTrack::SetShader(const fight::Name& newValue)
	{
		shader = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C860
	bool MotionTrailTrack::SetShrinkJoint(const fight::Name& newValue)
	{
		shrinkJoint = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C880
	bool MotionTrailTrack::SetJoint1(const fight::Name& newValue)
	{
		joint1 = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C8A0
	bool MotionTrailTrack::SetJoint2(const fight::Name& newValue)
	{
		joint2 = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C8C0
	bool MotionTrailTrack::SetJoint3(const fight::Name& newValue)
	{
		joint3 = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C8E0
	bool MotionTrailTrack::SetJoint4(const fight::Name& newValue)
	{
		joint4 = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C900
	bool MotionTrailTrack::SetJoint5(const fight::Name& newValue)
	{
		joint5 = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C920
	bool MotionTrailTrack::SetJoint6(const fight::Name& newValue)
	{
		joint6 = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1080C720
	fight::Property* MotionTrailTrack::GetProperty(int index)
	{
		return gMotionTrailTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x1080C730
	void MotionTrailTrack::ClearProperties()
	{
		fight::FreePropertyList(&gMotionTrailTrackProperties);
	}

	// FUNCTION: ENGINE 0x1080CD70
	// ctor stores: [('mov', 'dword', 0, '0x10e6be5c'), ('movss', 'dword', 80, '0.0f'), ('movss', 'dword', 84, '0.0f'), ('movss', 'dword', 88, '0.0f'), ('movss', 'dword', 92, '0.0f'), ('movss', 'dword', 96, '0.0f'), ('movss', 'dword', 100, '0.0f'), ('movss', 'dword', 104, '0.0f'), ('movss', 'dword', 108, '0.0f'), ('movss', 'dword', 112, '0.0f'), ('movss', 'dword', 116, '0.0f'), ('movss', 'dword', 120, '0.0f'), ('movss', 'dword', 124, '0.0f'), ('movss', 'dword', 128, '0.0f'), ('movss', 'dword', 132, '0.0f'), ('movss', 'dword', 136, '0.0f'), ('movss', 'dword', 140, '0.0f'), ('movss', 'dword', 144, '0.0f'), ('movss', 'dword', 148, '0.0f'), ('movss', 'dword', 152, '0.0f'), ('movss', 'dword', 156, '0.0f'), ('movss', 'dword', 160, '0.0f'), ('mov', 'dword', 204, '0'), ('mov', 'byte', 208, '0'), ('mov', 'byte', 209, '0'), ('mov', 'byte', 210, '0'), ('movss', 'dword', 164, '0.0f'), ('movss', 'dword', 168, '0.0f'), ('movss', 'dword', 172, '0.0f'), ('movss', 'dword', 176, '0.0f'), ('movss', 'dword', 180, '0.0f'), ('movss', 'dword', 184, '0.0f'), ('movss', 'dword', 188, '0.0f'), ('movss', 'dword', 192, '0.0f'), ('movss', 'dword', 196, '0.0f'), ('mov', 'dword', 200, '2')]
	MotionTrailTrack::MotionTrailTrack() : jointOffset1(0.0f, 0.0f, 0.0f), jointOffset2(0.0f, 0.0f, 0.0f), jointOffset3(0.0f, 0.0f, 0.0f), jointOffset4(0.0f, 0.0f, 0.0f), jointOffset5(0.0f, 0.0f, 0.0f), jointOffset6(0.0f, 0.0f, 0.0f), shrinkOffset(0.0f, 0.0f, 0.0f), fadeInTime(0.0f), fadeInTrailTime(0.0f), fadeOutTime(0.0f), fadeTime(0.0f), generateTime(0.0f), shrinkTime(0.0f), textureTime(0.0f), timeBegin(0.0f), timeEnd(0.0f), numJoints(2), slot(0), abortWhenInterrupted(false), dragged(false), runTillStop(false)
	{
	}

	// FUNCTION: ENGINE 0x1080CEC0
	float MotionTrailTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x1080CED0
	float MotionTrailTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x1080CEE0
	MotionTrailTrack::~MotionTrailTrack()
	{
	}

	// FUNCTION: ENGINE 0x1080EA90
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void MotionTrailTrack::RegisterProperties()
	{
		if (gMotionTrailTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<MotionTrailTrack>("timeBegin", &MotionTrailTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<MotionTrailTrack>("timeEnd", &MotionTrailTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyName<MotionTrailTrack>("shader", &MotionTrailTrack::SetShader);
			properties[2] = property;
			property = new fight::PropertyFloatConstRange<MotionTrailTrack>("generateTime", &MotionTrailTrack::SetGenerateTime);
			properties[3] = property;
			property = new fight::PropertyFloatConstRange<MotionTrailTrack>("fadeInTime", &MotionTrailTrack::SetFadeInTime);
			properties[4] = property;
			property = new fight::PropertyFloatConstRange<MotionTrailTrack>("fadeOutTime", &MotionTrailTrack::SetFadeOutTime);
			properties[5] = property;
			property = new fight::PropertyFloatConstRange<MotionTrailTrack>("textureTime", &MotionTrailTrack::SetTextureTime);
			properties[6] = property;
			property = new fight::PropertyFloatConstRange<MotionTrailTrack>("fadeTime", &MotionTrailTrack::SetFadeTime);
			properties[7] = property;
			property = new fight::PropertyFloatConstRange<MotionTrailTrack>("fadeInTrailTime", &MotionTrailTrack::SetFadeInTrailTime);
			properties[8] = property;
			property = new fight::PropertyFloatConstRange<MotionTrailTrack>("shrinkTime", &MotionTrailTrack::SetShrinkTime);
			properties[9] = property;
			property = new fight::PropertyBool<MotionTrailTrack>("dragged", &MotionTrailTrack::SetDragged);
			properties[10] = property;
			property = new fight::PropertyNameList<MotionTrailTrack>("shrinkJoint", &MotionTrailTrack::SetShrinkJoint);
			properties[11] = property;
			property = new fight::PropertyVector<MotionTrailTrack>("shrinkOffset", &MotionTrailTrack::SetShrinkOffset);
			properties[12] = property;
			property = new fight::PropertyIntConstRange<MotionTrailTrack>("numJoints", &MotionTrailTrack::SetNumJoints);
			properties[13] = property;
			property = new fight::PropertyNameList<MotionTrailTrack>("joint1", &MotionTrailTrack::SetJoint1);
			properties[14] = property;
			property = new fight::PropertyVector<MotionTrailTrack>("jointOffset1", &MotionTrailTrack::SetJointOffset1);
			properties[15] = property;
			property = new fight::PropertyNameList<MotionTrailTrack>("joint2", &MotionTrailTrack::SetJoint2);
			properties[16] = property;
			property = new fight::PropertyVector<MotionTrailTrack>("jointOffset2", &MotionTrailTrack::SetJointOffset2);
			properties[17] = property;
			property = new fight::PropertyNameList<MotionTrailTrack>("joint3", &MotionTrailTrack::SetJoint3);
			properties[18] = property;
			property = new fight::PropertyVector<MotionTrailTrack>("jointOffset3", &MotionTrailTrack::SetJointOffset3);
			properties[19] = property;
			property = new fight::PropertyNameList<MotionTrailTrack>("joint4", &MotionTrailTrack::SetJoint4);
			properties[20] = property;
			property = new fight::PropertyVector<MotionTrailTrack>("jointOffset4", &MotionTrailTrack::SetJointOffset4);
			properties[21] = property;
			property = new fight::PropertyNameList<MotionTrailTrack>("joint5", &MotionTrailTrack::SetJoint5);
			properties[22] = property;
			property = new fight::PropertyVector<MotionTrailTrack>("jointOffset5", &MotionTrailTrack::SetJointOffset5);
			properties[23] = property;
			property = new fight::PropertyNameList<MotionTrailTrack>("joint6", &MotionTrailTrack::SetJoint6);
			properties[24] = property;
			property = new fight::PropertyVector<MotionTrailTrack>("jointOffset6", &MotionTrailTrack::SetJointOffset6);
			properties[25] = property;
			property = new fight::PropertyBool<MotionTrailTrack>("abortWhenInterrupted", &MotionTrailTrack::SetAbortWhenInterrupted);
			properties[26] = property;
			property = new fight::PropertyBool<MotionTrailTrack>("runTillStop", &MotionTrailTrack::SetRunTillStop);
			properties[27] = property;
			property = new fight::PropertyIntConstRange<MotionTrailTrack>("slot", &MotionTrailTrack::SetSlot);
			properties[28] = property;
			fight::RegisterPropertyList(properties, &gMotionTrailTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x1080D4A0
	fight::TrackFactory* CreateMotionTrailTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<MotionTrailTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x1080D520
	void RegisterMotionTrailTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<MotionTrailTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyBool<MotionTrailTrack>;
	template class fight::PropertyFloatConstRange<MotionTrailTrack>;
	template class fight::PropertyIntConstRange<MotionTrailTrack>;
	template class fight::PropertyName<MotionTrailTrack>;
	template class fight::PropertyNameList<MotionTrailTrack>;
	template class fight::PropertyVector<MotionTrailTrack>;
	template class fight::TrackFactoryTemplate<MotionTrailTrack>;
	template class fight::TrackFactoryCasterTemplate<MotionTrailTrack>;
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D74980
// FUNCTION: ENGINE 0x10D749C0
// FUNCTION: ENGINE 0x10D89FC0
// FUNCTION: ENGINE 0x10D89FD0
