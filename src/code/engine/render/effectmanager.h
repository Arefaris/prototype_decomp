// The manager of the effects the fight tracks start (the engine's global at 0x1130CCE0, read through 0x108193A0; no
// RTTI, so class and method names are guesses). It owns the effect drawables the effect and motion trail actions
// create and stops them again. Only the methods the fight tracks call are declared here; the class itself lives in
// the unit that starts at 0x10819430.
#ifndef ENGINE_RENDER_EFFECTMANAGER_H
#define ENGINE_RENDER_EFFECTMANAGER_H

#include "code/core/name.h"

namespace engine
{
	namespace render
	{
		class Drawable;

		class EffectManager
		{
		public:
			// 0x10819560: releases a drawable the manager made
			void ReleaseDrawable(Drawable* drawable);
			// 0x1081B730: fades out the effect of a handle over a time and stops it
			void StopEffect(int effect, float fadeTime);
			// 0x1081E260: stops the effects started on a slot, fading them out when allowed
			void AbortSlot(const core::Name<core::CaseSensitiveKey>* slot, bool allowFade, float fadeTime);
		};

		// 0x108193A0: the global manager
		EffectManager* GetEffectManager();
	}
}

#endif
