// Fight items of the hit effects: EffectTrack (RTTI proto::HitEffectManager::EffectTrack, 16 vftable slots: starts a particle
// effect where the hit landed; the unit is 0x10508C90 - 0x1050DEE0 for the track and 0x104FF610 - 0x10501470 for its action;
// no assert path names it, so the file name is a guess). Of the class only the members the reflected properties write
// are laid out, with the property names; the size of the track is not known (the constructor 0x10508C90 is not reconstructed).
// The 26 half-float members of the overrides are read by the getters of 0x104FC450 + 0x1B0 * n.
#ifndef PROTO_HITEFFECTMANAGER_HITEFFECT_EFFECT_H
#define PROTO_HITEFFECTMANAGER_HITEFFECT_EFFECT_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/hiteffects/hiteffectdata.h"

namespace proto
{
	namespace HitEffectManager
	{
		class EffectTrack : public fight::Track
		{
		public:
			// The getters the effect action reads the track through (0x104FC0E0 - 0x104FC440; named after the properties)
			float GetTimeEnd() const;
			const fight::Name& GetEffectName() const;
			int GetEmitSpace() const;
			const fight::Name& GetEmitJoint() const;
			float GetBlendFromImpulseToHit() const;
			int GetAttachTo() const;
			int GetAttachSpace() const;
			const fight::Name& GetAttachJoint() const;
			const fight::Name& GetSlot() const;
			math::Vector GetOffset() const;
			math::Vector GetOrientation() const;
			bool GetRunTillEnd() const;
			bool GetRunTillInterrupted() const;
			float GetFadeTime() const;
			int GetEffectStore() const;
			float GetScale() const;
			bool GetCollides() const;
			float GetRestitution() const;
			float GetFriction() const;
			float GetRenderOffset() const;
			bool GetBiases() const;
			float GetBiasesEmissionRate() const;
			float GetBiasesLifeSpan() const;
			float GetBiasesLifeSpanVariance() const;
			float GetBiasesSpeed() const;
			float GetBiasesSpeedVariance() const;
			float GetBiasesSize1D() const;
			float GetBiasesSize1DVariance() const;
			float GetBiasesSpin1D() const;
			float GetBiasesSpin1DVariance() const;
			float GetBiasesWeight() const;
			float GetBiasesWeightVariance() const;
			float GetBiasesAngle() const;
			float GetBiasesAngleVariance() const;
			float GetBiasesGravity() const;
			float GetBiasesDrag() const;
			float GetBiasesColourRed() const;
			float GetBiasesColourGreen() const;
			float GetBiasesColourBlue() const;
			float GetBiasesAlpha() const;
			float GetBiasesColourOverLifeRed() const;
			float GetBiasesColourOverLifeGreen() const;
			float GetBiasesColourOverLifeBlue() const;
			float GetBiasesAlphaOverLife() const;
			float GetBiasesColourVariance() const;
			float GetBiasesAlphaVariance() const;
			float GetBiasesGeneratorRadius() const;
			float GetBiasesGeneratorRadial() const;
			float GetBiasesGeneratorHorizSpread() const;
			float GetBiasesGeneratorVertSpread() const;
			float GetBiasesGeneratorWidth() const;
			float GetBiasesGeneratorHeight() const;
			bool GetOverrides() const;

			unsigned char unknown10[0x8];  // +0x10
			fight::Name attachJoint;  // +0x18
			fight::Name effectController;  // +0x20
			fight::Name effectName;  // +0x28
			fight::Name emitJoint;  // +0x30
			fight::Name slot;  // +0x38
			math::Vector offset;  // +0x40
			math::Vector orientation;  // +0x4C
			unsigned char lods[0x4];  // +0x58
			float biasesAlpha;  // +0x5C
			float biasesAlphaOverLife;  // +0x60
			float biasesAlphaVariance;  // +0x64
			float biasesAngle;  // +0x68
			float biasesAngleVariance;  // +0x6C
			float biasesColourBlue;  // +0x70
			float biasesColourGreen;  // +0x74
			float biasesColourOverLifeBlue;  // +0x78
			float biasesColourOverLifeGreen;  // +0x7C
			float biasesColourOverLifeRed;  // +0x80
			float biasesColourRed;  // +0x84
			float biasesColourVariance;  // +0x88
			float biasesDrag;  // +0x8C
			float biasesEmissionRate;  // +0x90
			float biasesGeneratorHeight;  // +0x94
			float biasesGeneratorHorizSpread;  // +0x98
			float biasesGeneratorRadial;  // +0x9C
			float biasesGeneratorRadius;  // +0xA0
			float biasesGeneratorVertSpread;  // +0xA4
			float biasesGeneratorWidth;  // +0xA8
			float biasesGravity;  // +0xAC
			float biasesLifeSpan;  // +0xB0
			float biasesLifeSpanVariance;  // +0xB4
			float biasesSize1D;  // +0xB8
			float biasesSize1DVariance;  // +0xBC
			float biasesSpeed;  // +0xC0
			float biasesSpeedVariance;  // +0xC4
			float biasesSpin1D;  // +0xC8
			float biasesSpin1DVariance;  // +0xCC
			float biasesWeight;  // +0xD0
			float biasesWeightVariance;  // +0xD4
			float blendFromImpulseToHit;  // +0xD8
			float fadeTime;  // +0xDC
			float friction;  // +0xE0
			float renderOffset;  // +0xE4
			float restitution;  // +0xE8
			float scale;  // +0xEC
			float timeBegin;  // +0xF0
			float timeEnd;  // +0xF4
			int attachSpace;  // +0xF8
			int attachTo;  // +0xFC
			int effectStore;  // +0x100
			int emitSpace;  // +0x104
			unsigned short overridesAlpha;  // +0x108
			unsigned short overridesAlphaVariance;  // +0x10A
			unsigned short overridesAngle;  // +0x10C
			unsigned short overridesAngleVariance;  // +0x10E
			unsigned short overridesColourBlue;  // +0x110
			unsigned short overridesColourGreen;  // +0x112
			unsigned short overridesColourRed;  // +0x114
			unsigned short overridesColourVariance;  // +0x116
			unsigned short overridesDrag;  // +0x118
			unsigned short overridesEmissionRate;  // +0x11A
			unsigned short overridesEmissionRatePerMeter;  // +0x11C
			unsigned short overridesGeneratorHeight;  // +0x11E
			unsigned short overridesGeneratorWidth;  // +0x120
			unsigned short overridesGravity;  // +0x122
			unsigned short overridesLifeSpan;  // +0x124
			unsigned short overridesLifeSpanVariance;  // +0x126
			unsigned short overridesMaxParticles;  // +0x128
			unsigned short overridesParticleAllocation;  // +0x12A
			unsigned short overridesSize1D;  // +0x12C
			unsigned short overridesSize1DVariance;  // +0x12E
			unsigned short overridesSpeed;  // +0x130
			unsigned short overridesSpeedVariance;  // +0x132
			unsigned short overridesSpin1D;  // +0x134
			unsigned short overridesSpin1DVariance;  // +0x136
			unsigned short overridesWeight;  // +0x138
			unsigned short overridesWeightVariance;  // +0x13A
			bool biases;  // +0x13C
			bool collides;  // +0x13D
			bool highPriority;  // +0x13E
			bool overrides;  // +0x13F
			bool runTillEnd;  // +0x140
			bool runTillInterrupted;  // +0x141
		};
	}
}

#endif
