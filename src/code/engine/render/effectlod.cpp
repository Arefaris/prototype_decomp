// The effect level-of-detail records (see effectlod.h).
#include "code/engine/render/effectlod.h"
#include <string.h>
#include "code/pure3d/primitive.h"

namespace engine
{
	// FUNCTION: ENGINE 0x1081EAF0
	bool CompareEffectLODs(EffectLOD* const* first, EffectLOD* const* second)
	{
		EffectLOD* a = *first;
		EffectLOD* b = *second;
		return a->startDistance < b->startDistance;
	}

	// FUNCTION: ENGINE 0x1081EC30
	EffectLOD::EffectLOD(int newKind, float newStartDistance, float newEndDistance)
		: kind(newKind), startDistance(newStartDistance), endDistance(newEndDistance)
	{
	}

	// FUNCTION: ENGINE 0x1081EC70
	EffectLOD::~EffectLOD()
	{
	}

	// FUNCTION: ENGINE 0x1081EA70
	float EffectLOD::GetStartDistance() const
	{
		return startDistance;
	}

	// FUNCTION: ENGINE 0x1081EA80
	float EffectLOD::GetEndDistance() const
	{
		return endDistance;
	}

	// FUNCTION: ENGINE 0x1081EA90
	void EffectLOD::SetDrawable(unsigned int newDrawable)
	{
		drawable.mHandle = newDrawable;
	}

	// FUNCTION: ENGINE 0x1081EF90
	EffectLODBias::EffectLODBias(float newStartDistance, float newEndDistance)
		: EffectLOD(render::EFFECT_LOD_BIAS, newStartDistance, newEndDistance), hasBiases(false), hasOverrides(false)
	{
		memset(&biases, 0, sizeof(biases));
		memset(&overrides, 0, sizeof(overrides));
	}

	// FUNCTION: ENGINE 0x1081EC90
	EffectLODBias::~EffectLODBias()
	{
	}

	// FUNCTION: ENGINE 0x1081F010
	void EffectLODBias::Apply()
	{
		render::Drawable target = drawable;
		if (hasBiases)
		{
			target.SetEffectBiases(biases);
		}
		if (hasOverrides)
		{
			target.SetEffectOverrides(overrides);
		}
	}

	// FUNCTION: ENGINE 0x1081F070
	// EQUIVALENT: the same 34 mixes, 23 tests and calls in the same order; the engine multiplies the other record's term
	// first in the last biases and loads the three last ones early, and reloads the amount before the sentinel (87.3 %)
	void EffectLODBias::Blend(const EffectLODBias* other, float amount)
	{
		render::Drawable target = drawable;
		float remaining = 1.0f - amount;
		if (hasBiases && other->hasBiases)
		{
			render::EffectBiases blended;
			blended.values[0] = biases.values[0] * remaining + other->biases.values[0] * amount;
			blended.values[1] = biases.values[1] * remaining + other->biases.values[1] * amount;
			blended.values[2] = biases.values[2] * remaining + other->biases.values[2] * amount;
			blended.values[3] = biases.values[3] * remaining + other->biases.values[3] * amount;
			blended.values[4] = biases.values[4] * remaining + other->biases.values[4] * amount;
			blended.values[5] = biases.values[5] * remaining + other->biases.values[5] * amount;
			blended.values[6] = biases.values[6] * remaining + other->biases.values[6] * amount;
			blended.values[7] = biases.values[7] * remaining + other->biases.values[7] * amount;
			blended.values[8] = biases.values[8] * remaining + other->biases.values[8] * amount;
			blended.values[9] = biases.values[9] * remaining + other->biases.values[9] * amount;
			blended.values[10] = biases.values[10] * remaining + other->biases.values[10] * amount;
			blended.values[11] = biases.values[11] * remaining + other->biases.values[11] * amount;
			blended.values[12] = biases.values[12] * remaining + other->biases.values[12] * amount;
			blended.values[13] = biases.values[13] * remaining + other->biases.values[13] * amount;
			blended.values[14] = biases.values[14] * remaining + other->biases.values[14] * amount;
			blended.values[15] = biases.values[15] * remaining + other->biases.values[15] * amount;
			blended.values[16] = biases.values[16] * remaining + other->biases.values[16] * amount;
			blended.values[17] = biases.values[17] * remaining + other->biases.values[17] * amount;
			blended.values[18] = biases.values[18] * remaining + other->biases.values[18] * amount;
			blended.values[19] = biases.values[19] * remaining + other->biases.values[19] * amount;
			blended.values[20] = biases.values[20] * remaining + other->biases.values[20] * amount;
			blended.values[21] = biases.values[21] * remaining + other->biases.values[21] * amount;
			blended.values[22] = biases.values[22] * remaining + other->biases.values[22] * amount;
			blended.values[23] = biases.values[23] * remaining + other->biases.values[23] * amount;
			blended.values[24] = biases.values[24] * remaining + other->biases.values[24] * amount;
			blended.values[25] = biases.values[25] * remaining + other->biases.values[25] * amount;
			blended.values[26] = biases.values[26] * remaining + other->biases.values[26] * amount;
			blended.values[27] = biases.values[27] * remaining + other->biases.values[27] * amount;
			blended.values[28] = biases.values[28] * remaining + other->biases.values[28] * amount;
			blended.values[29] = biases.values[29] * remaining + other->biases.values[29] * amount;
			blended.values[30] = biases.values[30] * remaining + other->biases.values[30] * amount;
			blended.values[31] = biases.values[31] * remaining + other->biases.values[31] * amount;
			blended.values[32] = biases.values[32] * remaining + other->biases.values[32] * amount;
			blended.values[33] = biases.values[33] * remaining + other->biases.values[33] * amount;
			target.SetEffectBiases(blended);
		}
		if (hasOverrides && other->hasOverrides)
		{
			if (overrides.values[1] != -1.0f && other->overrides.values[1] != -1.0f && overrides.values[1] != other->overrides.values[1])
			{
				target.SetParticleFloat(pure3d::gParticleKey1127F2C8, other->overrides.values[1] * amount + overrides.values[1] * remaining);
			}
			if (overrides.values[2] != -1.0f && other->overrides.values[2] != -1.0f && overrides.values[2] != other->overrides.values[2])
			{
				target.SetParticleFloat(pure3d::gParticleKey1127F15C, other->overrides.values[2] * amount + overrides.values[2] * remaining);
			}
			if (overrides.values[3] != -1.0f && other->overrides.values[3] != -1.0f && overrides.values[3] != other->overrides.values[3])
			{
				target.SetParticleFloat(pure3d::gParticleKey1127F20C, other->overrides.values[3] * amount + overrides.values[3] * remaining);
			}
			if (overrides.values[4] != -1.0f && other->overrides.values[4] != -1.0f && overrides.values[4] != other->overrides.values[4])
			{
				target.SetParticleFloat(pure3d::gParticleKey1127F2DC, other->overrides.values[4] * amount + overrides.values[4] * remaining);
			}
			if (overrides.values[5] != -1.0f && other->overrides.values[5] != -1.0f && overrides.values[5] != other->overrides.values[5])
			{
				target.SetParticleFloat(pure3d::gParticleKey1127F188, other->overrides.values[5] * amount + overrides.values[5] * remaining);
			}
			if (overrides.values[6] != -1.0f && other->overrides.values[6] != -1.0f && overrides.values[6] != other->overrides.values[6])
			{
				target.SetParticleFloat(pure3d::gParticleKey1127F2BC, other->overrides.values[6] * amount + overrides.values[6] * remaining);
			}
			if (overrides.values[7] != -1.0f && other->overrides.values[7] != -1.0f && overrides.values[7] != other->overrides.values[7])
			{
				target.SetParticleFloat(pure3d::gParticleKey1127F208, other->overrides.values[7] * amount + overrides.values[7] * remaining);
			}
			if (overrides.values[8] != -1.0f && other->overrides.values[8] != -1.0f && overrides.values[8] != other->overrides.values[8])
			{
				target.SetParticleFloat(pure3d::gParticleKey1127F2AC, other->overrides.values[8] * amount + overrides.values[8] * remaining);
			}
			if (overrides.values[9] != -1.0f && other->overrides.values[9] != -1.0f && overrides.values[9] != other->overrides.values[9])
			{
				target.SetParticleFloat(pure3d::gParticleKey1127F330, other->overrides.values[9] * amount + overrides.values[9] * remaining);
			}
			if (overrides.values[10] != -1.0f && other->overrides.values[10] != -1.0f && overrides.values[10] != other->overrides.values[10])
			{
				target.SetParticleFloat(pure3d::gParticleKey1127F0B8, other->overrides.values[10] * amount + overrides.values[10] * remaining);
			}
			if (overrides.values[11] != -1.0f && other->overrides.values[11] != -1.0f && overrides.values[11] != other->overrides.values[11])
			{
				target.SetParticleFloat(pure3d::gParticleKey1127F284, other->overrides.values[11] * amount + overrides.values[11] * remaining);
			}
			if (overrides.values[12] != -1.0f && other->overrides.values[12] != -1.0f && overrides.values[12] != other->overrides.values[12])
			{
				target.SetParticleFloat(pure3d::gParticleKey1127F1CC, other->overrides.values[12] * amount + overrides.values[12] * remaining);
			}
			if (overrides.values[13] != -1.0f && other->overrides.values[13] != -1.0f && overrides.values[13] != other->overrides.values[13])
			{
				target.SetParticleFloat(pure3d::gParticleKey1127F144, other->overrides.values[13] * amount + overrides.values[13] * remaining);
			}
			if (overrides.values[14] != -1.0f && other->overrides.values[14] != -1.0f && overrides.values[14] != other->overrides.values[14])
			{
				target.SetParticleFloat(pure3d::gParticleKey1127F338, other->overrides.values[14] * amount + overrides.values[14] * remaining);
			}
			if (overrides.values[15] != -1.0f && other->overrides.values[15] != -1.0f && overrides.values[15] != other->overrides.values[15])
			{
				target.SetParticleFloat(pure3d::gParticleKey1127F158, other->overrides.values[15] * amount + overrides.values[15] * remaining);
			}
			if (overrides.values[16] != -1.0f && other->overrides.values[16] != -1.0f && overrides.values[16] != other->overrides.values[16])
			{
				target.SetParticleFloat(pure3d::gParticleKey1127F15C, other->overrides.values[16] * amount + overrides.values[16] * remaining);
			}
			if (overrides.values[17] != -1.0f && other->overrides.values[17] != -1.0f && overrides.values[17] != other->overrides.values[17])
			{
				target.SetParticleFloat(pure3d::gParticleKey1127F20C, other->overrides.values[17] * amount + overrides.values[17] * remaining);
			}
			if (overrides.values[18] != -1.0f && other->overrides.values[18] != -1.0f && overrides.values[18] != other->overrides.values[18])
			{
				target.SetParticleFloat(pure3d::gParticleKey1127F2DC, other->overrides.values[18] * amount + overrides.values[18] * remaining);
			}
			if (overrides.values[19] != -1.0f && other->overrides.values[19] != -1.0f && overrides.values[19] != other->overrides.values[19])
			{
				target.SetParticleFloat(pure3d::gParticleKey1127F188, other->overrides.values[19] * amount + overrides.values[19] * remaining);
			}
			if (overrides.values[20] != -1.0f && other->overrides.values[20] != -1.0f && overrides.values[20] != other->overrides.values[20])
			{
				target.SetParticleFloat(pure3d::gParticleKey1127F2BC, other->overrides.values[20] * amount + overrides.values[20] * remaining);
			}
			if (overrides.values[21] != -1.0f && other->overrides.values[21] != -1.0f && overrides.values[21] != other->overrides.values[21])
			{
				target.SetParticleFloat(pure3d::gParticleKey1127F208, other->overrides.values[21] * amount + overrides.values[21] * remaining);
			}
			if (overrides.values[22] != -1.0f && other->overrides.values[22] != -1.0f && overrides.values[22] != other->overrides.values[22])
			{
				target.SetParticleFloat(pure3d::gParticleKey1127F218, other->overrides.values[22] * amount + overrides.values[22] * remaining);
			}
			if (overrides.values[23] != -1.0f && other->overrides.values[23] != -1.0f && overrides.values[23] != other->overrides.values[23])
			{
				target.SetParticleFloat(pure3d::gParticleKey1127F144, other->overrides.values[23] * amount + overrides.values[23] * remaining);
			}
		}
	}

	// FUNCTION: ENGINE 0x1081FEC0
	EffectLODSwitch::EffectLODSwitch(int newEffect, float newStartDistance, float newEndDistance)
		: EffectLOD(render::EFFECT_LOD_SWITCH, newStartDistance, newEndDistance), effect(newEffect)
	{
	}

	// FUNCTION: ENGINE 0x1081ECA0
	EffectLODSwitch::~EffectLODSwitch()
	{
	}

	// FUNCTION: ENGINE 0x1081EAA0
	// EQUIVALENT: the engine loads the member into ecx and the out pointer into eax, ours the other way round (75 %)
	void EffectLODSwitch::GetEffect(int* result) const
	{
		*result = effect;
	}

	// FUNCTION: ENGINE 0x1081FF10
	EffectLODDisable::EffectLODDisable(float newStartDistance)
		: EffectLOD(render::EFFECT_LOD_DISABLE, newStartDistance, 0.0f)
	{
	}

	// FUNCTION: ENGINE 0x1081ECB0
	EffectLODDisable::~EffectLODDisable()
	{
	}
}
