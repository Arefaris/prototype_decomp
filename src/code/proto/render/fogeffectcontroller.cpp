#include "code/proto/render/fogeffectcontroller.h"
#include "code/engine/render/effectmanager.h"

namespace proto
{
	// FUNCTION: ENGINE 0x102E9DA0
	FogEffectController::FogEffectController(const int* newOwner, const core::Name<core::CaseSensitiveKey>& newName) : engine::EffectController(newOwner, newName)
	{
		width = 0.0f;
		height = 0.0f;
		fade = engine::driving::gOne;
	}

	// FUNCTION: ENGINE 0x102E9DF0
	FogEffectController::~FogEffectController()
	{
	}

	// FUNCTION: ENGINE 0x102E9E80
	bool FogEffectController::AddEffect(const int* effect)
	{
		if (!engine::EffectController::AddEffect(effect))
		{
			return false;
		}
		engine::render::EffectManager* manager = engine::render::GetEffectManager();
		manager->SetParticleFloat(*effect, core::Name<core::CaseInsensitiveKey32>("generatorWidth", 1), width);
		manager->SetParticleFloat(*effect, core::Name<core::CaseInsensitiveKey32>("generatorHeight", 1), height);
		manager->SetEffectPosition(*effect, position);
		((const engine::render::Drawable*)effect)->SetUnknownBC(fade);
		return true;
	}

	// FUNCTION: ENGINE 0x102E9F70
	void FogEffectController::Slot4()
	{
		engine::render::EffectManager* manager = engine::render::GetEffectManager();
		engine::render::Drawable drawable;
		for (int* effect = list.begin; effect != list.end; effect++)
		{
			drawable.mHandle = *effect;
			manager->SetParticleFloat(drawable.mHandle, core::Name<core::CaseInsensitiveKey32>("generatorWidth", 1), width);
			manager->SetParticleFloat(drawable.mHandle, core::Name<core::CaseInsensitiveKey32>("generatorHeight", 1), height);
			manager->SetEffectPosition(drawable.mHandle, position);
			drawable.SetUnknownBC(fade);
		}
	}

	// FUNCTION: ENGINE 0x102E9E40
	void FogEffectController::StopAll()
	{
		engine::EffectController::StopAll();
	}

	// FUNCTION: ENGINE 0x102E9F30
	void FogEffectController::SetParams(const FogParams* params)
	{
		width = params->width;
		height = params->height;
		position.x = params->position.x;
		position.y = params->position.y;
		position.z = params->position.z;
		fade = params->fade;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102E9E50
