// The names of the post-process effect parameters (brightness, contrast, fog, radial blur, ...) the render passes
// set by name (unit name guess: the engine's static initialisers 0x10D72D00 - 0x10D73360 construct them in one run).
#include "code/core/name.h"

namespace pure3d
{
	core::Name<core::CaseSensitiveKey> gBrightness("brightness", 0);
	core::Name<core::CaseSensitiveKey> gContrast("contrast", 0);
	core::Name<core::CaseSensitiveKey> gMidpoint("midpoint", 0);
	core::Name<core::CaseSensitiveKey> gSaturation("saturation", 0);
	core::Name<core::CaseSensitiveKey> gHue("hue", 0);
	core::Name<core::CaseSensitiveKey> gTint("tint", 0);
	core::Name<core::CaseSensitiveKey> gTint2("tint2", 0);
	core::Name<core::CaseSensitiveKey> gBloomStrength("bloomStrength", 0);
	core::Name<core::CaseSensitiveKey> gBackBufferStrength("backBufferStrength", 0);
	core::Name<core::CaseSensitiveKey> gColour2("colour", 0);
	core::Name<core::CaseSensitiveKey> gWeights("weights", 0);
	core::Name<core::CaseSensitiveKey> gRadiusX("radiusX", 0);
	core::Name<core::CaseSensitiveKey> gRadiusY("radiusY", 0);
	core::Name<core::CaseSensitiveKey> gRadius2("radius", 0);
	core::Name<core::CaseSensitiveKey> gAdaptRate("adaptRate", 0);
	core::Name<core::CaseSensitiveKey> gMin("min", 0);
	core::Name<core::CaseSensitiveKey> gMax("max", 0);
	core::Name<core::CaseSensitiveKey> gPower("power", 0);
	core::Name<core::CaseSensitiveKey> gCmy("cmy", 0);
	core::Name<core::CaseSensitiveKey> gCmyScaleBias("cmyScaleBias", 0);
	core::Name<core::CaseSensitiveKey> gOverlay("overlay", 0);
	core::Name<core::CaseSensitiveKey> gOverlayOpacity("overlayOpacity", 0);
	core::Name<core::CaseSensitiveKey> gOverlaySaturation("overlaySaturation", 0);
	core::Name<core::CaseSensitiveKey> gGrain("grain", 0);
	core::Name<core::CaseSensitiveKey> gGrainSpeed("grainSpeed", 0);
	core::Name<core::CaseSensitiveKey> gGrainIntensity("grainIntensity", 0);
	core::Name<core::CaseSensitiveKey> gLuminanceCutoff("luminanceCutoff", 0);
	core::Name<core::CaseSensitiveKey> gAverageLuminance("averageLuminance", 0);
	core::Name<core::CaseSensitiveKey> gInnerSaturationDistance2("innerSaturationDistance", 0);
	core::Name<core::CaseSensitiveKey> gOuterSaturationDistance2("outerSaturationDistance", 0);
	core::Name<core::CaseSensitiveKey> gInnerContrastDistance2("innerContrastDistance", 0);
	core::Name<core::CaseSensitiveKey> gOuterContrastDistance2("outerContrastDistance", 0);
	core::Name<core::CaseSensitiveKey> gInnerBrightnessDistance2("innerBrightnessDistance", 0);
	core::Name<core::CaseSensitiveKey> gOuterBrightnessDistance2("outerBrightnessDistance", 0);
	core::Name<core::CaseSensitiveKey> gInnerTintDistance2("innerTintDistance", 0);
	core::Name<core::CaseSensitiveKey> gOuterTintDistance2("outerTintDistance", 0);
	core::Name<core::CaseSensitiveKey> gBrightnessFalloff2("brightnessFalloff", 0);
	core::Name<core::CaseSensitiveKey> gContrastFalloff2("contrastFalloff", 0);
	core::Name<core::CaseSensitiveKey> gFogFalloff("fogFalloff", 0);
	core::Name<core::CaseSensitiveKey> gFogVariation("fogVariation", 0);
	core::Name<core::CaseSensitiveKey> gFogThickness("fogThickness", 0);
	core::Name<core::CaseSensitiveKey> gSpeed("speed", 0);
	core::Name<core::CaseSensitiveKey> gTestValue("testValue", 0);
	core::Name<core::CaseSensitiveKey> gFogTiling("fogTiling", 0);
	core::Name<core::CaseSensitiveKey> gGlobalFog("globalFog", 0);
	core::Name<core::CaseSensitiveKey> gNoiseStrength("noiseStrength", 0);
	core::Name<core::CaseSensitiveKey> gFogStrength("fogStrength", 0);
	core::Name<core::CaseSensitiveKey> gFogMoveDir("fogMoveDir", 0);
	core::Name<core::CaseSensitiveKey> gRadialBlurIntensity("radialBlurIntensity", 0);
	core::Name<core::CaseSensitiveKey> gRadialBlurSource("radialBlurSource", 0);
	core::Name<core::CaseSensitiveKey> gRadialBlurSize("radialBlurSize", 0);
	core::Name<core::CaseSensitiveKey> gRadialBlurFalloff("radialBlurFalloff", 0);
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D72D00
// FUNCTION: ENGINE 0x10D72D20
// FUNCTION: ENGINE 0x10D72D40
// FUNCTION: ENGINE 0x10D72D60
// FUNCTION: ENGINE 0x10D72D80
// FUNCTION: ENGINE 0x10D72DA0
// FUNCTION: ENGINE 0x10D72DC0
// FUNCTION: ENGINE 0x10D72DE0
// FUNCTION: ENGINE 0x10D72E00
// FUNCTION: ENGINE 0x10D72E20
// FUNCTION: ENGINE 0x10D72E40
// FUNCTION: ENGINE 0x10D72E60
// FUNCTION: ENGINE 0x10D72E80
// FUNCTION: ENGINE 0x10D72EA0
// FUNCTION: ENGINE 0x10D72EC0
// FUNCTION: ENGINE 0x10D72EE0
// FUNCTION: ENGINE 0x10D72F00
// FUNCTION: ENGINE 0x10D72F20
// FUNCTION: ENGINE 0x10D72F40
// FUNCTION: ENGINE 0x10D72F60
// FUNCTION: ENGINE 0x10D72F80
// FUNCTION: ENGINE 0x10D72FA0
// FUNCTION: ENGINE 0x10D72FC0
// FUNCTION: ENGINE 0x10D72FE0
// FUNCTION: ENGINE 0x10D73000
// FUNCTION: ENGINE 0x10D73020
// FUNCTION: ENGINE 0x10D73040
// FUNCTION: ENGINE 0x10D73060
// FUNCTION: ENGINE 0x10D73080
// FUNCTION: ENGINE 0x10D730A0
// FUNCTION: ENGINE 0x10D730C0
// FUNCTION: ENGINE 0x10D730E0
// FUNCTION: ENGINE 0x10D73100
// FUNCTION: ENGINE 0x10D73120
// FUNCTION: ENGINE 0x10D73140
// FUNCTION: ENGINE 0x10D73160
// FUNCTION: ENGINE 0x10D73180
// FUNCTION: ENGINE 0x10D731A0
// FUNCTION: ENGINE 0x10D731C0
// FUNCTION: ENGINE 0x10D731E0
// FUNCTION: ENGINE 0x10D73200
// FUNCTION: ENGINE 0x10D73220
// FUNCTION: ENGINE 0x10D73240
// FUNCTION: ENGINE 0x10D73260
// FUNCTION: ENGINE 0x10D73280
// FUNCTION: ENGINE 0x10D732A0
// FUNCTION: ENGINE 0x10D732C0
// FUNCTION: ENGINE 0x10D732E0
// FUNCTION: ENGINE 0x10D73300
// FUNCTION: ENGINE 0x10D73320
// FUNCTION: ENGINE 0x10D73340
// FUNCTION: ENGINE 0x10D73360
// FUNCTION: ENGINE 0x10D896F0
// FUNCTION: ENGINE 0x10D89700
// FUNCTION: ENGINE 0x10D89710
// FUNCTION: ENGINE 0x10D89720
// FUNCTION: ENGINE 0x10D89730
// FUNCTION: ENGINE 0x10D89740
// FUNCTION: ENGINE 0x10D89750
// FUNCTION: ENGINE 0x10D89760
// FUNCTION: ENGINE 0x10D89770
// FUNCTION: ENGINE 0x10D89780
// FUNCTION: ENGINE 0x10D89790
// FUNCTION: ENGINE 0x10D897A0
// FUNCTION: ENGINE 0x10D897B0
// FUNCTION: ENGINE 0x10D897C0
// FUNCTION: ENGINE 0x10D897D0
// FUNCTION: ENGINE 0x10D897E0
// FUNCTION: ENGINE 0x10D897F0
// FUNCTION: ENGINE 0x10D89800
// FUNCTION: ENGINE 0x10D89810
// FUNCTION: ENGINE 0x10D89820
// FUNCTION: ENGINE 0x10D89830
// FUNCTION: ENGINE 0x10D89840
// FUNCTION: ENGINE 0x10D89850
// FUNCTION: ENGINE 0x10D89860
// FUNCTION: ENGINE 0x10D89870
// FUNCTION: ENGINE 0x10D89880
// FUNCTION: ENGINE 0x10D89890
// FUNCTION: ENGINE 0x10D898A0
// FUNCTION: ENGINE 0x10D898B0
// FUNCTION: ENGINE 0x10D898C0
// FUNCTION: ENGINE 0x10D898D0
// FUNCTION: ENGINE 0x10D898E0
// FUNCTION: ENGINE 0x10D898F0
// FUNCTION: ENGINE 0x10D89900
// FUNCTION: ENGINE 0x10D89910
// FUNCTION: ENGINE 0x10D89920
// FUNCTION: ENGINE 0x10D89930
// FUNCTION: ENGINE 0x10D89940
// FUNCTION: ENGINE 0x10D89950
// FUNCTION: ENGINE 0x10D89960
// FUNCTION: ENGINE 0x10D89970
// FUNCTION: ENGINE 0x10D89980
// FUNCTION: ENGINE 0x10D89990
// FUNCTION: ENGINE 0x10D899A0
// FUNCTION: ENGINE 0x10D899B0
// FUNCTION: ENGINE 0x10D899C0
// FUNCTION: ENGINE 0x10D899D0
// FUNCTION: ENGINE 0x10D899E0
// FUNCTION: ENGINE 0x10D899F0
// FUNCTION: ENGINE 0x10D89A00
// FUNCTION: ENGINE 0x10D89A10
// FUNCTION: ENGINE 0x10D89A20
