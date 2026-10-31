// The names (core::Name, case sensitive) the render passes register their parameters under and are made with;
// the engine's static initialisers hash the strings in the comments. Names are guesses.
#ifndef PURE3D_PASSNAMES_H
#define PURE3D_PASSNAMES_H

#include "code/core/name.h"

namespace pure3d
{
	extern core::Name<core::CaseSensitiveKey> gPassNamePrototypeTonemap; // 0x1127ECF8 "Prototype Tonemap"
	extern core::Name<core::CaseSensitiveKey> gPassNamePrototypeBloom; // 0x1127EC00 "Prototype Bloom"
	extern core::Name<core::CaseSensitiveKey> gPassNamePrototypeColourMatrix; // 0x1127EC20 "Prototype ColourMatrix"
	extern core::Name<core::CaseSensitiveKey> gPassNamePrototypeThermalVision; // 0x1127EC10 "Prototype Thermal Vision"
	extern core::Name<core::CaseSensitiveKey> gPassNamePrototypeMotherVision; // 0x1127ED38 "Prototype Mother Vision"
	extern core::Name<core::CaseSensitiveKey> gPassNameCopyPass; // 0x112813D8 "Copy Pass"
	extern core::Name<core::CaseSensitiveKey> gPassNameBlurPass; // 0x112813B8 "Blur Pass"
	extern core::Name<core::CaseSensitiveKey> gParamPrototypeChameleonicColourMix; // 0x1127ECC8 "Prototype Chameleonic Colour Mix"
	extern core::Name<core::CaseSensitiveKey> gParamPrototypeChameleonicAlexColour; // 0x1127ED88 "Prototype Chameleonic Alex Colour"
	extern core::Name<core::CaseSensitiveKey> gParamPrototypeChameleonicInfecedColour; // 0x1127ED68 "Prototype Chameleonic Infeced Colour"
	extern core::Name<core::CaseSensitiveKey> gParamPrototypeVisionMode; // 0x1127ECA8 "Prototype Vision Mode"
	extern core::Name<core::CaseSensitiveKey> gParamPrototypeVisionModeStrength; // 0x1127ED98 "Prototype Vision Mode Strength"
	extern core::Name<core::CaseSensitiveKey> gParamBackbufferstrength; // 0x11281420 "backbufferstrength"
	extern core::Name<core::CaseSensitiveKey> gParamBloomstrength; // 0x112816B0 "bloomstrength"
	extern core::Name<core::CaseSensitiveKey> gParamBrightness; // 0x11281678 "Brightness"
	extern core::Name<core::CaseSensitiveKey> gParamConstrast; // 0x112814B0 "Constrast"
	extern core::Name<core::CaseSensitiveKey> gParamHue; // 0x11281418 "hue"
	extern core::Name<core::CaseSensitiveKey> gParamLuminanceCutoff; // 0x11281630 "luminance_cutoff"
	extern core::Name<core::CaseSensitiveKey> gParamPower; // 0x11281460 "power"
	extern core::Name<core::CaseSensitiveKey> gParamMidpoint; // 0x112814E0 "Midpoint"
	extern core::Name<core::CaseSensitiveKey> gParamRadiusx; // 0x11281500 "radiusx"
	extern core::Name<core::CaseSensitiveKey> gParamRadiusy; // 0x112815C8 "radiusy"
	extern core::Name<core::CaseSensitiveKey> gParamSaturation; // 0x112816B8 "Saturation"
	extern core::Name<core::CaseSensitiveKey> gParamTint; // 0x11281450 "tint"
	extern core::Name<core::CaseSensitiveKey> gParamWeights; // 0x11281638 "weights"
}

#endif
