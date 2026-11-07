// proto::HitEffectManager::EffectTrack: the getters of the members the effect action reads (see the header).
#include "code/proto/hiteffects/hiteffect_effect.h"

namespace proto
{
	namespace HitEffectManager
	{
		// FUNCTION: ENGINE 0x104FC0E0
		float EffectTrack::GetTimeEnd() const
		{
			return timeEnd;
		}

		// FUNCTION: ENGINE 0x104FC0F0
		const fight::Name& EffectTrack::GetEffectName() const
		{
			return effectName;
		}

		// FUNCTION: ENGINE 0x104FC100
		int EffectTrack::GetEmitSpace() const
		{
			return emitSpace;
		}

		// FUNCTION: ENGINE 0x104FC110
		const fight::Name& EffectTrack::GetEmitJoint() const
		{
			return emitJoint;
		}

		// FUNCTION: ENGINE 0x104FC120
		float EffectTrack::GetBlendFromImpulseToHit() const
		{
			return blendFromImpulseToHit;
		}

		// FUNCTION: ENGINE 0x104FC130
		int EffectTrack::GetAttachTo() const
		{
			return attachTo;
		}

		// FUNCTION: ENGINE 0x104FC140
		int EffectTrack::GetAttachSpace() const
		{
			return attachSpace;
		}

		// FUNCTION: ENGINE 0x104FC150
		const fight::Name& EffectTrack::GetAttachJoint() const
		{
			return attachJoint;
		}

		// FUNCTION: ENGINE 0x104FC160
		const fight::Name& EffectTrack::GetSlot() const
		{
			return slot;
		}

		// FUNCTION: ENGINE 0x104FC170
		math::Vector EffectTrack::GetOffset() const
		{
			return offset;
		}

		// FUNCTION: ENGINE 0x104FC190
		math::Vector EffectTrack::GetOrientation() const
		{
			return orientation;
		}

		// FUNCTION: ENGINE 0x104FC1B0
		bool EffectTrack::GetRunTillEnd() const
		{
			return runTillEnd;
		}

		// FUNCTION: ENGINE 0x104FC1C0
		bool EffectTrack::GetRunTillInterrupted() const
		{
			return runTillInterrupted;
		}

		// FUNCTION: ENGINE 0x104FC1D0
		float EffectTrack::GetFadeTime() const
		{
			return fadeTime;
		}

		// FUNCTION: ENGINE 0x104FC1E0
		int EffectTrack::GetEffectStore() const
		{
			return effectStore;
		}

		// FUNCTION: ENGINE 0x104FC1F0
		float EffectTrack::GetScale() const
		{
			return scale;
		}

		// FUNCTION: ENGINE 0x104FC200
		bool EffectTrack::GetCollides() const
		{
			return collides;
		}

		// FUNCTION: ENGINE 0x104FC210
		float EffectTrack::GetRestitution() const
		{
			return restitution;
		}

		// FUNCTION: ENGINE 0x104FC220
		float EffectTrack::GetFriction() const
		{
			return friction;
		}

		// FUNCTION: ENGINE 0x104FC230
		float EffectTrack::GetRenderOffset() const
		{
			return renderOffset;
		}

		// FUNCTION: ENGINE 0x104FC240
		bool EffectTrack::GetBiases() const
		{
			return biases;
		}

		// FUNCTION: ENGINE 0x104FC250
		float EffectTrack::GetBiasesEmissionRate() const
		{
			return biasesEmissionRate;
		}

		// FUNCTION: ENGINE 0x104FC260
		float EffectTrack::GetBiasesLifeSpan() const
		{
			return biasesLifeSpan;
		}

		// FUNCTION: ENGINE 0x104FC270
		float EffectTrack::GetBiasesLifeSpanVariance() const
		{
			return biasesLifeSpanVariance;
		}

		// FUNCTION: ENGINE 0x104FC280
		float EffectTrack::GetBiasesSpeed() const
		{
			return biasesSpeed;
		}

		// FUNCTION: ENGINE 0x104FC290
		float EffectTrack::GetBiasesSpeedVariance() const
		{
			return biasesSpeedVariance;
		}

		// FUNCTION: ENGINE 0x104FC2A0
		float EffectTrack::GetBiasesSize1D() const
		{
			return biasesSize1D;
		}

		// FUNCTION: ENGINE 0x104FC2B0
		float EffectTrack::GetBiasesSize1DVariance() const
		{
			return biasesSize1DVariance;
		}

		// FUNCTION: ENGINE 0x104FC2C0
		float EffectTrack::GetBiasesSpin1D() const
		{
			return biasesSpin1D;
		}

		// FUNCTION: ENGINE 0x104FC2D0
		float EffectTrack::GetBiasesSpin1DVariance() const
		{
			return biasesSpin1DVariance;
		}

		// FUNCTION: ENGINE 0x104FC2E0
		float EffectTrack::GetBiasesWeight() const
		{
			return biasesWeight;
		}

		// FUNCTION: ENGINE 0x104FC2F0
		float EffectTrack::GetBiasesWeightVariance() const
		{
			return biasesWeightVariance;
		}

		// FUNCTION: ENGINE 0x104FC300
		float EffectTrack::GetBiasesAngle() const
		{
			return biasesAngle;
		}

		// FUNCTION: ENGINE 0x104FC310
		float EffectTrack::GetBiasesAngleVariance() const
		{
			return biasesAngleVariance;
		}

		// FUNCTION: ENGINE 0x104FC320
		float EffectTrack::GetBiasesGravity() const
		{
			return biasesGravity;
		}

		// FUNCTION: ENGINE 0x104FC330
		float EffectTrack::GetBiasesDrag() const
		{
			return biasesDrag;
		}

		// FUNCTION: ENGINE 0x104FC340
		float EffectTrack::GetBiasesColourRed() const
		{
			return biasesColourRed;
		}

		// FUNCTION: ENGINE 0x104FC350
		float EffectTrack::GetBiasesColourGreen() const
		{
			return biasesColourGreen;
		}

		// FUNCTION: ENGINE 0x104FC360
		float EffectTrack::GetBiasesColourBlue() const
		{
			return biasesColourBlue;
		}

		// FUNCTION: ENGINE 0x104FC370
		float EffectTrack::GetBiasesAlpha() const
		{
			return biasesAlpha;
		}

		// FUNCTION: ENGINE 0x104FC380
		float EffectTrack::GetBiasesColourOverLifeRed() const
		{
			return biasesColourOverLifeRed;
		}

		// FUNCTION: ENGINE 0x104FC390
		float EffectTrack::GetBiasesColourOverLifeGreen() const
		{
			return biasesColourOverLifeGreen;
		}

		// FUNCTION: ENGINE 0x104FC3A0
		float EffectTrack::GetBiasesColourOverLifeBlue() const
		{
			return biasesColourOverLifeBlue;
		}

		// FUNCTION: ENGINE 0x104FC3B0
		float EffectTrack::GetBiasesAlphaOverLife() const
		{
			return biasesAlphaOverLife;
		}

		// FUNCTION: ENGINE 0x104FC3C0
		float EffectTrack::GetBiasesColourVariance() const
		{
			return biasesColourVariance;
		}

		// FUNCTION: ENGINE 0x104FC3D0
		float EffectTrack::GetBiasesAlphaVariance() const
		{
			return biasesAlphaVariance;
		}

		// FUNCTION: ENGINE 0x104FC3E0
		float EffectTrack::GetBiasesGeneratorRadius() const
		{
			return biasesGeneratorRadius;
		}

		// FUNCTION: ENGINE 0x104FC3F0
		float EffectTrack::GetBiasesGeneratorRadial() const
		{
			return biasesGeneratorRadial;
		}

		// FUNCTION: ENGINE 0x104FC400
		float EffectTrack::GetBiasesGeneratorHorizSpread() const
		{
			return biasesGeneratorHorizSpread;
		}

		// FUNCTION: ENGINE 0x104FC410
		float EffectTrack::GetBiasesGeneratorVertSpread() const
		{
			return biasesGeneratorVertSpread;
		}

		// FUNCTION: ENGINE 0x104FC420
		float EffectTrack::GetBiasesGeneratorWidth() const
		{
			return biasesGeneratorWidth;
		}

		// FUNCTION: ENGINE 0x104FC430
		float EffectTrack::GetBiasesGeneratorHeight() const
		{
			return biasesGeneratorHeight;
		}

		// FUNCTION: ENGINE 0x104FC440
		bool EffectTrack::GetOverrides() const
		{
			return overrides;
		}
	}
}
