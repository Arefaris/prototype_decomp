// The effect level-of-detail records (see effectlod.h).
#include "code/engine/render/effectlod.h"
#include <string.h>

namespace engine
{
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
