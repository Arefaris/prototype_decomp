// The level-of-detail records a playing effect keeps (RTTI engine::EffectLOD and its three kinds, base NonCopyable, which
// is a reference counted core::IRefCount). The effect tracks make them; the effect manager asks them to change the
// effect when the camera is far enough. Member and method names are guesses. The unit runs from 0x1081EA00 to 0x1081FFE0
// and is shared with the playing effect's own methods (effectmanager.cpp).
#ifndef ENGINE_RENDER_EFFECTLOD_H
#define ENGINE_RENDER_EFFECTLOD_H

#include "code/core/memory/imemoryallocator.h"
#include "code/engine/render/async/drawable.h"
#include "code/engine/render/async/private/drawableimpl.h"

// RTTI name NonCopyable (no namespace): the reference count of the records below (vftable 0x10E6DED4). The members are
// inline; the engine keeps copies at 0x1081EA00 (constructor), 0x1081EA10, 0x1081EA20, 0x1081EA40 and 0x1081EA50.
class NonCopyable : public core::IRefCount
{
public:
	NonCopyable()
		: count(0)
	{
	}
	virtual void AddRef()
	{
		count++;
	}
	// Below one reference the object deletes itself
	virtual void Release()
	{
		count--;
		if (count < 1)
		{
			delete this;
		}
	}
	virtual ~NonCopyable()
	{
	}

	int count;  // +0x04
};

namespace engine
{
	namespace render
	{
		// What a record does to the effect
		enum EffectLODKind
		{
			EFFECT_LOD_BIAS = 0,
			EFFECT_LOD_SWITCH = 1,
			EFFECT_LOD_DISABLE = 2
		};
	}

	// RTTI: engine::EffectLOD (3 vftable slots, 0x18 bytes without the derived members): the kind of record, the effect
	// it belongs to and the distances it works between
	class EffectLOD : public NonCopyable
	{
	public:
		// 0x1081EC30
		EffectLOD(int newKind, float newStartDistance, float newEndDistance);
		// 0x1081EC70 / 0x1081EF70
		virtual ~EffectLOD();

		// 0x1081EA70 / 0x1081EA80
		float GetStartDistance() const;
		float GetEndDistance() const;
		// 0x1081EA90: the drawable of the effect the record applies to (a handle)
		void SetDrawable(unsigned int newDrawable);

		int kind;  // +0x08
		render::Drawable drawable;  // +0x0C
		float startDistance;  // +0x10
		float endDistance;  // +0x14
	};

	// 0x1081EAF0: whether the first record starts nearer than the second (the order the effect keeps them in)
	bool CompareEffectLODs(EffectLOD* const* first, EffectLOD* const* second);

	// RTTI: engine::EffectLODBias: sets biases and overrides on the effect's particle systems (0x1A0 bytes)
	class EffectLODBias : public EffectLOD
	{
	public:
		// 0x1081EF90
		EffectLODBias(float newStartDistance, float newEndDistance);
		// 0x1081EC90 / 0x1081EFF0
		virtual ~EffectLODBias();

		// 0x1081F070: sets the effect's biases and overrides to a mix of this record's and another's (amount 0 is this one)
		void Blend(const EffectLODBias* other, float amount);
		// 0x1081F010: hands the biases and the overrides that are set to the effect's drawable
		void Apply();

		render::EffectBiases biases;  // +0x18
		render::EffectOverrides overrides;  // +0xA0
		bool hasBiases;  // +0x100
		bool hasOverrides;  // +0x101
	};

	// RTTI: engine::EffectLODSwitch: switches to another effect
	class EffectLODSwitch : public EffectLOD
	{
	public:
		// 0x1081FEC0
		EffectLODSwitch(int newEffect, float newStartDistance, float newEndDistance);
		// 0x1081ECA0 / 0x1081FEF0
		virtual ~EffectLODSwitch();

		// 0x1081EAA0
		void GetEffect(int* result) const;

		int effect;  // +0x18
	};

	// RTTI: engine::EffectLODDisable: switches the effect off
	class EffectLODDisable : public EffectLOD
	{
	public:
		// 0x1081FF10
		explicit EffectLODDisable(float newStartDistance);
		// 0x1081ECB0 / 0x1081FF40
		virtual ~EffectLODDisable();
	};
}

#endif
