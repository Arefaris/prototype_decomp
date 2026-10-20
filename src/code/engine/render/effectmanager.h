// The manager of the effects the fight tracks start (the engine's global at 0x1130CCE0, read through 0x108193A0; no
// RTTI, so class and method names are guesses). It owns the effect drawables the effect and motion trail actions
// create and stops them again. Only the methods the fight tracks call are declared here; the class itself lives in
// the unit that starts at 0x10819430.
#ifndef ENGINE_RENDER_EFFECTMANAGER_H
#define ENGINE_RENDER_EFFECTMANAGER_H

#include "code/core/name.h"
#include "code/engine/render/async/drawable.h"
#include "code/math/vector.h"

namespace proto
{
	struct PartLookup;
}

namespace engine
{
	namespace render
	{

		class EffectManager
		{
		public:
			// 0x10819560: releases a drawable the manager made
			void ReleaseDrawable(Drawable* drawable);
			// 0x1081B730: fades out the effect of a handle over a time and stops it
			void StopEffect(int effect, float fadeTime);
			// 0x1081E260: stops the effects started on a slot, fading them out when allowed
			// 0x1081BA90: starts a motion trail on a drawable between the joints of its part lookup; the trail comes back
			// as a drawable (the object's drawable and part lookup, the times, the names of the joints and the offsets
			// on them, the shrink and the texture values)
			Drawable CreateMotionTrail(Drawable drawable, proto::PartLookup* lookup, float generateTime, float fadeInTime,
				float fadeOutTime, const core::Name<core::CaseSensitiveKey>* shader, const core::Name<core::CaseSensitiveKey>* joints,
				const math::Vector* offsets, int numJoints, const core::Name<core::CaseSensitiveKey>* shrinkJoint,
				math::Vector shrinkOffset, float shrinkTime, float fadeTime, float fadeInTrailTime, float textureTime, bool dragged);
			void AbortSlot(const core::Name<core::CaseSensitiveKey>* slot, bool allowFade, float fadeTime);
		};

		// 0x108193A0: the global manager
		EffectManager* GetEffectManager();
	}
}

#endif
