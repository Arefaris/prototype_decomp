// The shader names and shader constants of the render passes (unit name guess: the engine's static initialisers
// 0x10D67160 - 0x10D71660 construct them in one run, the names of the vertex attributes, shader stages, particle
// keys and the p3d shader constants first, then the constant slots the passes fill in once from those names).
// Only the variables are defined here; the code that binds them is in other units.
#include "code/pure3d/shaderconstants.h"
#include "code/pure3d/pddi.h"
#include "code/core/namecopy.h"

namespace pure3d
{
	core::Name<core::CaseInsensitiveKey32> gShaderLit = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("lit", 0)));
	core::Name<core::CaseInsensitiveKey32> gLitBase = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("lit_base", 0)));
	core::Name<core::CaseInsensitiveKey32> gStandardLight = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("standard_light", 0)));
	core::Name<core::CaseInsensitiveKey32> gSpatialLight = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("spatial_light", 0)));
	core::Name<core::CaseInsensitiveKey32> gUnlit = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("unlit", 0)));
	core::Name<core::CaseInsensitiveKey32> gShaderZFill = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("zfill", 0)));
	core::Name<core::CaseInsensitiveKey32> gName1127F180 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("position", 0)));
	core::Name<core::CaseInsensitiveKey32> gName1127F130 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("colour0", 0)));
	core::Name<core::CaseInsensitiveKey32> gName1127F1B8 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("normal", 0)));
	core::Name<core::CaseInsensitiveKey32> gName1127F1BC = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("binormal", 0)));
	core::Name<core::CaseInsensitiveKey32> gName1127F1DC = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("tangent", 0)));
	core::Name<core::CaseInsensitiveKey32> gName1127F340 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("blendoffset", 0)));
	core::Name<core::CaseInsensitiveKey32> gName1127F31C = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("blendnormal", 0)));
	core::Name<core::CaseInsensitiveKey32> gName1127F0D0 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("hdrColour", 0)));
	core::Name<core::CaseInsensitiveKey32> gName1127F16C = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("weights", 0)));
	core::Name<core::CaseInsensitiveKey32> gName1127F0B4 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("indices", 0)));
	core::Name<core::CaseInsensitiveKey32> gDiffuseMap = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("diffuseMap", 0)));
	core::Name<core::CaseInsensitiveKey32> gOrthonormalbasis = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("orthonormalbasis", 0)));
	core::Name<core::CaseInsensitiveKey32> gLightcount = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("lightcount", 0)));
	core::Name<core::CaseInsensitiveKey32> gDepthMap = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("depthMap", 0)));
	core::Name<core::CaseInsensitiveKey32> gAccumDrag = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("accumDrag", 0)));
	core::Name<core::CaseInsensitiveKey32> gAccumGravity = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("accumGravity", 0)));
	core::Name<core::CaseInsensitiveKey32> gAdditiveAlphaDiffuse = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("additiveAlphaDiffuse", 0)));
	core::Name<core::CaseInsensitiveKey32> gParticleKey1127F144 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("alpha", 0)));
	core::Name<core::CaseInsensitiveKey32> gParticleKey1127F208 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("angle", 0)));
	core::Name<core::CaseInsensitiveKey32> gParticleKey1127F218 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("diffuse", 0)));
	core::Name<core::CaseInsensitiveKey32> gParticleKey1127F1CC = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("diffuseBlue", 0)));
	core::Name<core::CaseInsensitiveKey32> gParticleKey1127F284 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("diffuseGreen", 0)));
	core::Name<core::CaseInsensitiveKey32> gParticleKey1127F0B8 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("diffuseRed", 0)));
	core::Name<core::CaseInsensitiveKey32> gParticleKey1127F330 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("drag", 0)));
	core::Name<core::CaseInsensitiveKey32> gParticleKey1127F2C8 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("emissionRatePerMeter", 0)));
	core::Name<core::CaseInsensitiveKey32> gParticleKey1127F158 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("generatorHeight", 0)));
	core::Name<core::CaseInsensitiveKey32> gParticleKey1127F338 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("generatorWidth", 0)));
	core::Name<core::CaseInsensitiveKey32> gParticleKey1127F2AC = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("gravity", 0)));
	core::Name<core::CaseInsensitiveKey32> gParticleKey1127F2DC = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("initSize1D", 0)));
	core::Name<core::CaseInsensitiveKey32> gParticleKey1127F188 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("initSpin1D", 0)));
	core::Name<core::CaseInsensitiveKey32> gParticleKey1127F15C = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("lifeSpan", 0)));
	core::Name<core::CaseInsensitiveKey32> gPosition = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("position", 0)));
	core::Name<core::CaseInsensitiveKey32> gSize1D = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("size1D", 0)));
	core::Name<core::CaseInsensitiveKey32> gSize3D = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("size3D", 0)));
	core::Name<core::CaseInsensitiveKey32> gParticleKey1127F20C = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("speed", 0)));
	core::Name<core::CaseInsensitiveKey32> gSpin1D = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("spin1D", 0)));
	core::Name<core::CaseInsensitiveKey32> gSpin3D = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("spin3D", 0)));
	core::Name<core::CaseInsensitiveKey32> gSpin3DMask = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("spin3DMask", 0)));
	core::Name<core::CaseInsensitiveKey32> gTexFrameAnim = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("texFrameAnim", 0)));
	core::Name<core::CaseInsensitiveKey32> gTexFrameCountX = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("texFrameCountX", 0)));
	core::Name<core::CaseInsensitiveKey32> gTexFrameCountY = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("texFrameCountY", 0)));
	core::Name<core::CaseInsensitiveKey32> gTexFrameData = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("texFrameData", 0)));
	core::Name<core::CaseInsensitiveKey32> gTexFrameEnd = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("texFrameEnd", 0)));
	core::Name<core::CaseInsensitiveKey32> gTexFrameStart = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("texFrameStart", 0)));
	core::Name<core::CaseInsensitiveKey32> gTexFrameRate = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("texFrameRate", 0)));
	core::Name<core::CaseInsensitiveKey32> gTilt = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("tilt", 0)));
	core::Name<core::CaseInsensitiveKey32> gUvMin = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("uvMin", 0)));
	core::Name<core::CaseInsensitiveKey32> gUvMax = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("uvMax", 0)));
	core::Name<core::CaseInsensitiveKey32> gVelocity = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("velocity", 0)));
	core::Name<core::CaseInsensitiveKey32> gVertGridSpacing = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("vertGridSpacing", 0)));
	core::Name<core::CaseInsensitiveKey32> gVorticity = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("vorticity", 0)));
	core::Name<core::CaseInsensitiveKey32> gParticleKey1127F2BC = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("weight", 0)));
	core::Name<core::CaseInsensitiveKey32> gWidthScale = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("widthScale", 0)));
	core::Name<core::CaseInsensitiveKey32> gWindSpeed = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("windSpeed", 0)));
	core::Name<core::CaseInsensitiveKey32> gWindDirection = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("windDirection", 0)));
	core::Name<core::CaseInsensitiveKey32> gWindLocal = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("windLocal", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dViewMatrix = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dViewMatrix", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dWorldMatrix = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dWorldMatrix", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProjectionMatrix = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProjectionMatrix", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dWorldViewMatrix = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dWorldViewMatrix", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dViewProjectionMatrix = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dViewProjectionMatrix", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dWorldViewProjectionMatrix = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dWorldViewProjectionMatrix", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProjectionMatrixInverse = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProjectionMatrixInverse", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dWorldViewMatrixInverse = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dWorldViewMatrixInverse", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dViewMatrixInverse = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dViewMatrixInverse", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dWorldViewProjectionMatrixInverse = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dWorldViewProjectionMatrixInverse", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProjectionMatrixTranspose = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProjectionMatrixTranspose", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dWorldViewMatrixTranspose = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dWorldViewMatrixTranspose", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dWorldViewProjectionMatrixTranspose = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dWorldViewProjectionMatrixTranspose", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dWorldMatrixInverseTranspose = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dWorldMatrixInverseTranspose", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProjectionMatrixInverseTranspose = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProjectionMatrixInverseTranspose", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dWorldViewMatrixInverseTranspose = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dWorldViewMatrixInverseTranspose", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dWorldViewProjectionMatrixInverseTranspose = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dWorldViewProjectionMatrixInverseTranspose", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dEyePositionObjectSpace = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dEyePositionObjectSpace", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightEnabled = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_Enabled", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightInnerDecayRadius = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_InnerDecayRadius", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightOuterDecayRadius = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_OuterDecayRadius", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightSpotlightAngle = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_SpotlightAngle", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightRadialFalloff = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_RadialFalloff", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightRadius = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_Radius", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightUmbra = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_Umbra", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightPenumbra = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_Penumbra", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightDecayTexture = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_DecayTexture", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightProjectedTexture = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_ProjectedTexture", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightProjectedTextureMatrix = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_ProjectedTextureMatrix", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightHasProjectedTexture = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_HasProjectedTexture", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightOffsetVector1 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_OffsetVector1", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightScaledOffsetVector1 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_ScaledOffsetVector1", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightOffsetVector2 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_OffsetVector2", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightScaledOffsetVector2 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_ScaledOffsetVector2", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightZeroPosition = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_ZeroPosition", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightHasSH = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_hasSH", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightAmbient = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_Ambient", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightAttenuation = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_Attenuation", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightColour = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_Colour", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightPosition = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_Position", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightDirection = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_Direction", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightLightType = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_LightType", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightSpotlightTexture = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_SpotlightTexture", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightSpotlightConstant = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_SpotlightConstant", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightDecayConstant = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_DecayConstant", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightPositionObjectSpace = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_PositionObjectSpace", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightAmbient0 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_Ambient0", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightAttenuation0 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_Attenuation0", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightColour0 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_Colour0", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightPosition0 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_Position0", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightDirection0 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_Direction0", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightLightType0 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_LightType0", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightSpotlightTexture0 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_SpotlightTexture0", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightSpotlightConstant0 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_SpotlightConstant0", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightDecayConstant0 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_DecayConstant0", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightPositionObjectSpace0 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_PositionObjectSpace0", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightAmbient1 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_Ambient1", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightAttenuation1 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_Attenuation1", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightColour1 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_Colour1", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightPosition1 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_Position1", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightDirection1 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_Direction1", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightLightType1 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_LightType1", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightSpotlightTexture1 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_SpotlightTexture1", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightSpotlightConstant1 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_SpotlightConstant1", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightDecayConstant1 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_DecayConstant1", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightPositionObjectSpace1 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_PositionObjectSpace1", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightAmbient2 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_Ambient2", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightAttenuation2 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_Attenuation2", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightColour2 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_Colour2", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightPosition2 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_Position2", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightDirection2 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_Direction2", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightLightType2 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_LightType2", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightSpotlightTexture2 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_SpotlightTexture2", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightSpotlightConstant2 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_SpotlightConstant2", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightDecayConstant2 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_DecayConstant2", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightPositionObjectSpace2 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_PositionObjectSpace2", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightAmbient3 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_Ambient3", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightAttenuation3 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_Attenuation3", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightColour3 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_Colour3", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightPosition3 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_Position3", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightDirection3 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_Direction3", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightLightType3 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_LightType3", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightSpotlightTexture3 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_SpotlightTexture3", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightSpotlightConstant3 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_SpotlightConstant3", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightDecayConstant3 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_DecayConstant3", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightPositionObjectSpace3 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_PositionObjectSpace3", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightIsLitPass = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_IsLitPass", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightIsSpot = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_IsSpot", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightIsDirectional = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_IsDirectional", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightIsPoint = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_IsPoint", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightEnableSpotKill = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_EnableSpotKill", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightDirectionObjectSpace = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_DirectionObjectSpace", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightObjectSpaceLightBounds = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_ObjectSpaceLightBounds", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightHasCheapLights = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_HasCheapLights", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightLightMapScale = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_LightMapScale", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightSpecularScale = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_SpecularScale", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightIsLumPass = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLight_IsLumPass", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightScatterSunColour = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLightScatter_SunColour", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightScatterSunDir = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLightScatter_SunDir", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightScatterBdr = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLightScatter_Bdr", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightScatterBdm = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLightScatter_Bdm", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightScatterBrBm = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLightScatter_BrBm", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightScatterInvBrBm = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLightScatter_invBrBm", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightScatterG = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLightScatter_G", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightScatterInscatterMult = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLightScatter_InscatterMult", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightScatterDistAtten = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLightScatter_DistAtten", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightScatterDistAttenSky = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLightScatter_DistAttenSky", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dLightScatterMultipliers = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dLightScatter_Multipliers", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightPositionWorldSpace0 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_PositionWorldSpace0", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightPositionWorldSpace1 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_PositionWorldSpace1", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightPositionWorldSpace2 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_PositionWorldSpace2", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightPositionWorldSpace3 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_PositionWorldSpace3", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightPositionWorldSpace4 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_PositionWorldSpace4", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightPositionWorldSpace5 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_PositionWorldSpace5", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightPositionWorldSpace6 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_PositionWorldSpace6", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightPositionWorldSpace7 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_PositionWorldSpace7", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightPositionWorldSpace8 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_PositionWorldSpace8", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightPositionWorldSpace9 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_PositionWorldSpace9", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightColour0 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_Colour0", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightColour1 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_Colour1", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightColour2 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_Colour2", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightColour3 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_Colour3", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightColour4 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_Colour4", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightColour5 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_Colour5", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightColour6 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_Colour6", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightColour7 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_Colour7", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightColour8 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_Colour8", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightColour9 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_Colour9", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightAmbient0 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_Ambient0", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightAmbient1 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_Ambient1", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightAmbient2 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_Ambient2", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightAmbient3 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_Ambient3", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightAmbient4 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_Ambient4", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightAmbient5 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_Ambient5", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightAmbient6 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_Ambient6", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightAmbient7 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_Ambient7", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightAmbient8 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_Ambient8", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightAmbient9 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_Ambient9", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightAttenuation0 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_Attenuation0", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightAttenuation1 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_Attenuation1", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightAttenuation2 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_Attenuation2", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightAttenuation3 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_Attenuation3", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightAttenuation4 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_Attenuation4", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightAttenuation5 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_Attenuation5", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightAttenuation6 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_Attenuation6", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightAttenuation7 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_Attenuation7", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightAttenuation8 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_Attenuation8", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultiPhongLightAttenuation9 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultiPhongLight_Attenuation9", 0)));
	core::Name<core::CaseInsensitiveKey32> gColourChannel0 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("colourChannel0", 0)));
	core::Name<core::CaseInsensitiveKey32> gColourChannel1 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("colourChannel1", 0)));
	core::Name<core::CaseInsensitiveKey32> gColourChannel2 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("colourChannel2", 0)));
	core::Name<core::CaseInsensitiveKey32> gColourChannel3 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("colourChannel3", 0)));
	core::Name<core::CaseInsensitiveKey32> gColourChannel4 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("colourChannel4", 0)));
	core::Name<core::CaseInsensitiveKey32> gColourChannel5 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("colourChannel5", 0)));
	core::Name<core::CaseInsensitiveKey32> gColourChannel6 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("colourChannel6", 0)));
	core::Name<core::CaseInsensitiveKey32> gColourChannel7 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("colourChannel7", 0)));
	core::Name<core::CaseInsensitiveKey32> gLightPosObj = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("lightPosObj", 0)));
	core::Name<core::CaseInsensitiveKey32> gLightPos0 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("lightPos0", 0)));
	core::Name<core::CaseInsensitiveKey32> gLightPos1 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("lightPos1", 0)));
	core::Name<core::CaseInsensitiveKey32> gLightPos2 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("lightPos2", 0)));
	core::Name<core::CaseInsensitiveKey32> gLightPos3 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("lightPos3", 0)));
	core::Name<core::CaseInsensitiveKey32> gShadowFallOff = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("shadowFallOff", 0)));
	core::Name<core::CaseInsensitiveKey32> gDirLightFlag = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("dirLightFlag", 0)));
	core::Name<core::CaseInsensitiveKey32> gBlurFallOff = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("blurFallOff", 0)));
	core::Name<core::CaseInsensitiveKey32> gLightCountColor = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("lightCountColor", 0)));
	core::Name<core::CaseInsensitiveKey32> gPredicate = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("predicate", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dRenderTargetDimensionsRatio = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dRenderTargetDimensionsRatio", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPhongFade = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPhongFade", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dHalfPixel = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dHalfPixel", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dZScale = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dZScale", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dZNearFar = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dZNearFar", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dNaN = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dNaN", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dShaderLODBias = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dShader_LODBias", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dShaderLODGeo = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dShader_LODGeo", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dShadowEnabled = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dShadowEnabled", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dShadowEnabledSoft = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dShadowEnabledSoft", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dShadowEnabledChildren = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dShadowEnabledChildren", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dShadowEnabledCubeMap = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dShadowEnabledCubeMap", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dShadowIsLinearDepth = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dShadowIsLinearDepth", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dShadowMapChildBox00 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dShadowMapChildBox00", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dShadowMapChildBox01 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dShadowMapChildBox01", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dShadowMapChildBox02 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dShadowMapChildBox02", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dShadowMapChildBox03 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dShadowMapChildBox03", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dShadowMapChildBoxLow = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dShadowMapChildBoxLow", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dShadowMapChildInfo00 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dShadowMapChildInfo00", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dShadowMapChildInfo01 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dShadowMapChildInfo01", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dShadowMapChildInfo02 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dShadowMapChildInfo02", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dShadowMapChildInfo03 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dShadowMapChildInfo03", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dShadowMapChildInfo04 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dShadowMapChildInfo04", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dShadowMapChildInfo05 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dShadowMapChildInfo05", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dShadowZScale = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dShadowZScale", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dShadowCompareScaleBias = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dShadowCompareScaleBias", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dShadowBlur = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dShadowBlur", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dShadowMapInfo = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dShadowMapInfo", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dShadowMapAspect = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dShadowMapAspect", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dShadowMapMatrix = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dShadowMapMatrix", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dObjectToShadowMatrix = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dObjectToShadowMatrix", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dShadowMap = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dShadowMap", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dShadowMask = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dShadowMask", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dTime = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dTime", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dTimeCos = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dTimeCos", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dTimeElapsed = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dTimeElapsed", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPerlinNoiseTexture1D = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPerlinNoiseTexture1D", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPerlinNoiseTexture2D = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPerlinNoiseTexture2D", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPerlinNoiseTexture3D = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPerlinNoiseTexture3D", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultipleOctavePerlinNoiseTexture1D = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultipleOctavePerlinNoiseTexture1D", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultipleOctavePerlinNoiseTexture2D = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultipleOctavePerlinNoiseTexture2D", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dMultipleOctavePerlinNoiseTexture3D = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dMultipleOctavePerlinNoiseTexture3D", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dWhiteNoiseTexture2D = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dWhiteNoiseTexture2D", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHParam0 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_Param0", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHParam1 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_Param1", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHParam2 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_Param2", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHParam3 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_Param3", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHParam4 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_Param4", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHParam5 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_Param5", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHParam6 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_Param6", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHParam7 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_Param7", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHParam8 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_Param8", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCAr = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cAr", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCAg = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cAg", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCAb = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cAb", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCBr = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cBr", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCBg = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cBg", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCBb = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cBb", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCC = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cC", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCArGradX = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cArGradX", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCAgGradX = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cAgGradX", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCAbGradX = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cAbGradX", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCBrGradX = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cBrGradX", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCBgGradX = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cBgGradX", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCBbGradX = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cBbGradX", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCCGradX = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cCGradX", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCArGradY = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cArGradY", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCAgGradY = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cAgGradY", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCAbGradY = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cAbGradY", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCBrGradY = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cBrGradY", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCBgGradY = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cBgGradY", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCBbGradY = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cBbGradY", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCCGradY = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cCGradY", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCArGradZ = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cArGradZ", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCAgGradZ = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cAgGradZ", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCAbGradZ = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cAbGradZ", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCBrGradZ = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cBrGradZ", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCBgGradZ = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cBgGradZ", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCBbGradZ = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cBbGradZ", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCCGradZ = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cCGradZ", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHSamplePoint = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_SamplePoint", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHPosScale = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_PosScale", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCArTex = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cAr_Tex", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCAgTex = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cAg_Tex", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCAbTex = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cAb_Tex", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCBrTex = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cBr_Tex", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCBgTex = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cBg_Tex", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCBbTex = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cBb_Tex", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSHCCTex = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_cC_Tex", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dParticleFadeDist = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dParticleFadeDist", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dParticleFadeInvRange = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dParticleFadeInvRange", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dFrameBufferCurrent = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dFrameBufferCurrent", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dDepthBufferCurrent = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dDepthBufferCurrent", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dDecalColourBuffer = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dDecalColourBuffer", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dDecalNormalBuffer = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dDecalNormalBuffer", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dDecalLightBuffer = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dDecalLightBuffer", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dFringeMap = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dFringeMap", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dFrameBufferHalf = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dFrameBufferHalf", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dFrameBufferFull = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dFrameBufferFull", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dDepthBuffer = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dDepthBuffer", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dFloorReflection = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dFloorReflection", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dVertexInstanceTransform0 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dVertex_InstanceTransform0", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dVertexInstanceTransform1 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dVertex_InstanceTransform1", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dVertexInstanceTransform2 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dVertex_InstanceTransform2", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dSystemDiffuseMap = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSystemDiffuseMap", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPrototypeBuildingLights = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPrototype_BuildingLights", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPrototypeBuildingLightStr = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPrototype_BuildingLightStr", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPrototypeBuildingLightIntensity = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPrototype_BuildingLightIntensity", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPrototypeDayTransition = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPrototype_DayTransition", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPrototypeSignageIntensity = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPrototype_SignageIntensity", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPrototypeParticleTint = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPrototype_ParticleTint", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPrototypeHeadlightIntensity = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPrototype_HeadlightIntensity", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPrototypeMidgroundColour = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPrototype_MidgroundColour", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPrototypeMidgroundDesatStartDist = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPrototype_MidgroundDesatStartDist", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPrototypeMidgroundDesatRange = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPrototype_MidgroundDesatRange", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPrototypeMidgroundMinSaturation = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPrototype_MidgroundMinSaturation", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoSkySkyParams = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProtoSky_SkyParams", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoSkySunParams = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProtoSky_SunParams", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoSkySunDir = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProtoSky_SunDir", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoSkyFogColour = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProtoSky_FogColour", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoSkyFogDensity = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProtoSky_FogDensity", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoSkyFogHeight = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProtoSky_FogHeight", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoSkyDecayColour = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProtoSky_DecayColour", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoSkyDecayDensity = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProtoSky_DecayDensity", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoSkyDecayHeight = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProtoSky_DecayHeight", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoSkyHorizonParams = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProtoSky_HorizonParams", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoSkyStarStrength = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProtoSky_StarStrength", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoSkyGroundScatterColour = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProtoSky_GroundScatterColour", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoSkyGroundScatterDistance = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProtoSky_GroundScatterDistance", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoSkyGroundScatterHeightMod = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProtoSky_GroundScatterHeightMod", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoSkySunColour = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProtoSky_SunColour", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightColour1 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_Colour1", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightColour2 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_Colour2", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightColour3 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_Colour3", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightColour4 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_Colour4", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightColour5 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_Colour5", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightAmbient = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_Ambient", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightDirection1 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_Direction1", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightDirection2 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_Direction2", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightDirection3 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_Direction3", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightDirection4 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_Direction4", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightDirection5 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_Direction5", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightParams1 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_Params1", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightPointPos1 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_PointPos1", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightPointPos2 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_PointPos2", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightPointPos3 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_PointPos3", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightPointPos4 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_PointPos4", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightPointPos5 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_PointPos5", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightPointPos6 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_PointPos6", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightPointCol1 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_PointCol1", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightPointCol2 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_PointCol2", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightPointCol3 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_PointCol3", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightPointCol4 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_PointCol4", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightPointCol5 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_PointCol5", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightPointCol6 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_PointCol6", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightAmbParams1 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_AmbParams1", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightHemiLight1 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_HemiLight1", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightHemiLight2 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_HemiLight2", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightSpotPos1 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_SpotPos1", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightSpotPos2 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_SpotPos2", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightSpotPos3 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_SpotPos3", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightSpotPos4 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_SpotPos4", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightSpotPos5 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_SpotPos5", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightSpotPos6 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_SpotPos6", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightSpotDir1 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_SpotDir1", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightSpotDir2 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_SpotDir2", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightSpotDir3 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_SpotDir3", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightSpotDir4 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_SpotDir4", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightSpotDir5 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_SpotDir5", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightSpotDir6 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_SpotDir6", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightSpotCol1 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_SpotCol1", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightSpotCol2 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_SpotCol2", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightSpotCol3 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_SpotCol3", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightSpotCol4 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_SpotCol4", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightSpotCol5 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_SpotCol5", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightSpotCol6 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_SpotCol6", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightSpotDec1 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_SpotDec1", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightSpotDec2 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_SpotDec2", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightSpotDec3 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_SpotDec3", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightSpotDec4 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_SpotDec4", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightSpotDec5 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_SpotDec5", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightSpotDec6 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_SpotDec6", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoCloudLowScale = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_Cloud_LowScale", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoCloudHighScale = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_Cloud_HighScale", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoCloudLowDir = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_Cloud_LowDir", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoCloudHighDir = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_Cloud_HighDir", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoCloudDomeScale = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_Cloud_DomeScale", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoCloudLowOpacity = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_Cloud_LowOpacity", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoCloudHighOpacity = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_Cloud_HighOpacity", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoCloudUpperColour = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_Cloud_UpperColour", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoCloudLowerColour = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_Cloud_LowerColour", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoCloudSoftness = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_Cloud_Softness", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoCloudSunColour = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_Cloud_SunColour", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoDecayPos0 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_Decay_Pos0", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoDecayPos1 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_Decay_Pos1", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoDecayPos2 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_Decay_Pos2", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoDecayPos3 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_Decay_Pos3", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoDecayPos4 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_Decay_Pos4", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoDecayPos5 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_Decay_Pos5", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoCloudLightMatrix = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_Cloud_LightMatrix", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoCloudLightParams = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_Cloud_LightParams", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoCloudLightTexture = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_Cloud_LightTexture", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoFogBuffer = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_Fog_Buffer", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoFogDarkTint = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_Fog_DarkTint", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoFogLightTint = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_Fog_LightTint", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoFogFalloff = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_Fog_Falloff", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoFogFalloffModifier = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_Fog_FalloffModifier", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoFogNoiseStrength = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_Fog_NoiseStrength", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoFogStrength = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_Fog_Strength", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoFogOutput = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_Fog_Output", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightPointPos1Vertex = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_PointPos1_Vertex", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightPointPos2Vertex = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_PointPos2_Vertex", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightPointPos3Vertex = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_PointPos3_Vertex", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightPointPos4Vertex = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_PointPos4_Vertex", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightPointPos5Vertex = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_PointPos5_Vertex", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightPointPos6Vertex = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_PointPos6_Vertex", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightPointPos7Vertex = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_PointPos7_Vertex", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightPointPos8Vertex = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_PointPos8_Vertex", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightPointCol1Vertex = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_PointCol1_Vertex", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightPointCol2Vertex = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_PointCol2_Vertex", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightPointCol3Vertex = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_PointCol3_Vertex", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightPointCol4Vertex = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_PointCol4_Vertex", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightPointCol5Vertex = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_PointCol5_Vertex", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightPointCol6Vertex = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_PointCol6_Vertex", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightPointCol7Vertex = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_PointCol7_Vertex", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightPointCol8Vertex = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_PointCol8_Vertex", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightAmbParams1Vertex = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_AmbParams1_Vertex", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightHemiLight1Vertex = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_HemiLight1_Vertex", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightHemiLight2Vertex = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_HemiLight2_Vertex", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dPRLightAmbientVertex = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dPRLight_Ambient_Vertex", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoShaderLODVertex = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_ShaderLOD_Vertex", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoJointMatrix = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_Joint_Matrix", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoThermalLevel = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_Thermal_Level", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoInfectedLevel = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_Infected_Level", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoDistanceFieldAAWidth = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_DistanceField_AAWidth", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoDistanceFieldFadeStart = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_DistanceField_FadeStart", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoDistanceFieldFadeEnd = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_DistanceField_FadeEnd", 0)));
	core::Name<core::CaseInsensitiveKey32> gP3dProtoVehicleDespawnDist = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dProto_VehicleDespawnDist", 0)));
	ConstantSlot gConstantSlot11280CFC;
	ConstantSlot gConstantSlot11280FF4;
	ConstantSlot gConstantSlot11280DF0;
	ConstantSlot gConstantSlot11280C44;
	ConstantSlot gConstantSlot11280AC0;
	ConstantSlot gConstantSlot11280DD4;
	ConstantSlot gConstantSlot11280E00;
	ConstantSlot gConstantSlot11280C0C;
	ConstantSlot gConstantSlot11280BFC;
	ConstantSlot gConstantSlot11280DE0;
	ConstantSlot gConstantSlot11280BA8;
	ConstantSlot gConstantSlot11280DE4;
	ConstantSlot gConstantSlot11280C00;
	ConstantSlot gConstantSlot11280D00;
	ConstantSlot gConstantSlot11280DB0;
	ConstantSlot gConstantSlot11281024;
	ConstantSlot gConstantSlot11280AE0;
	ConstantSlot gConstantSlot1128100C;
	ConstantSlot gConstantSlot11280B84;
	ConstantSlot gConstantSlot112810D4;
	ConstantSlot gConstantSlot11281234;
	ConstantSlot gConstantSlot11281104;
	ConstantSlot gConstantSlot11280A54;
	ConstantSlot gConstantSlot11280C4C;
	ConstantSlot gConstantSlot11280C88;
	ConstantSlot gConstantSlot112810FC;
	ConstantSlot gConstantSlot1128117C;
	ConstantSlot gConstantSlot11280B30;
	ConstantSlot gConstantSlot11280D78;
	ConstantSlot gConstantSlot11280E24;
	ConstantSlot gConstantSlot11280CBC;
	ConstantSlot gConstantSlot11280BE4;
	ConstantSlot gConstantSlot112811B0;
	ConstantSlot gConstantSlot11280ACC;
	ConstantSlot gConstantSlot112812FC;
	ConstantSlot gConstantSlot11280A78;
	ConstantSlot gConstantSlot11280C94;
	ConstantSlot gConstantSlot11280CCC;
	ConstantSlot gConstantSlot11280B58;
	ConstantSlot gConstantSlot11280F44;
	ConstantSlot gConstantSlot112812C4;
	ConstantSlot gConstantSlot11280BEC;
	ConstantSlot gConstantSlot11281160;
	ConstantSlot gConstantSlot11281204;
	ConstantSlot gConstantSlot1128108C;
	ConstantSlot gConstantSlot11280AA4;
	ConstantSlot gConstantSlot11280F4C;
	ConstantSlot gConstantSlot11281054;
	ConstantSlot gConstantSlot11281314;
	ConstantSlot gConstantSlot1128116C;
	ConstantSlot gConstantSlot112810DC;
	ConstantSlot gConstantSlot1128119C;
	ConstantSlot gConstantSlot11280C3C;
	ConstantSlot gConstantSlot11280D28;
	ConstantSlot gConstantSlot1128106C;
	ConstantSlot gConstantSlot11280D58;
	ConstantSlot gConstantSlot11280B64;
	ConstantSlot gConstantSlot11280C1C;
	ConstantSlot gConstantSlot112812EC;
	ConstantSlot gConstantSlot11280BBC;
	ConstantSlot gConstantSlot11280C80;
	ConstantSlot gConstantSlot11280F04;
	ConstantSlot gConstantSlot11280B24;
	ConstantSlot gConstantSlot11280F98;
	ConstantSlot gConstantSlot11280A90;
	ConstantSlot gConstantSlot11280C5C;
	ConstantSlot gConstantSlot112812DC;
	ConstantSlot gConstantSlot11280EF8;
	ConstantSlot gConstantSlot11280AD0;
	ConstantSlot gConstantSlot11280D44;
	ConstantSlot gConstantSlot11281184;
	ConstantSlot gConstantSlot11280E54;
	ConstantSlot gConstantSlot11280D94;
	ConstantSlot gConstantSlot1128131C;
	ConstantSlot gConstantSlot11280B40;
	ConstantSlot gConstantSlot11281084;
	ConstantSlot gConstantSlot11280BD0;
	ConstantSlot gConstantSlot11280FFC;
	ConstantSlot gConstantSlot11280D2C;
	ConstantSlot gConstantSlot11280E2C;
	ConstantSlot gConstantSlot11280D5C;
	ConstantSlot gConstantSlot1128109C;
	ConstantSlot gConstantSlot11280BAC;
	ConstantSlot gConstantSlot11280D7C;
	ConstantSlot gConstantSlot1128130C;
	ConstantSlot gConstantSlot11280B38;
	ConstantSlot gConstantSlot11280D68;
	ConstantSlot gConstantSlot11280FBC;
	ConstantSlot gConstantSlot11280D74;
	ConstantSlot gConstantSlot11280A70;
	ConstantSlot gConstantSlot1128101C;
	ConstantSlot gConstantSlot11281240;
	ConstantSlot gConstantSlot11280C04;
	ConstantSlot gConstantSlot11280D48;
	ConstantSlot gConstantSlot11280D0C;
	ConstantSlot gConstantSlot11280C48;
	ConstantSlot gConstantSlot11280BF0;
	ConstantSlot gConstantSlot11280F6C;
	ConstantSlot gConstantSlot11280C6C;
	ConstantSlot gConstantSlot11281274;
	ConstantSlot gConstantSlot11280A9C;
	ConstantSlot gConstantSlot11280C40;
	ConstantSlot gConstantSlot11280C90;
	ConstantSlot gConstantSlot11280C28;
	ConstantSlot gConstantSlot11280AF8;
	ConstantSlot gConstantSlot1128107C;
	ConstantSlot gConstantSlot11280A60;
	ConstantSlot gConstantSlot11280AA0;
	ConstantSlot gConstantSlot11281154;
	ConstantSlot gConstantSlot11280A7C;
	ConstantSlot gConstantSlot112811C0;
	ConstantSlot gConstantSlot11280EC4;
	ConstantSlot gConstantSlot11280A6C;
	ConstantSlot gConstantSlot11280A4C;
	ConstantSlot gConstantSlot11280CE0;
	ConstantSlot gConstantSlot11280F34;
	ConstantSlot gConstantSlot11280BDC;
	ConstantSlot gConstantSlot112812BC;
	ConstantSlot gConstantSlot11280D30;
	ConstantSlot gConstantSlot11281144;
	ConstantSlot gConstantSlot11280B48;
	ConstantSlot gConstantSlot112812F4;
	ConstantSlot gConstantSlot11280BD8;
	ConstantSlot gConstantSlot11280F0C;
	ConstantSlot gConstantSlot11280AD8;
	ConstantSlot gConstantSlot11281044;
	ConstantSlot gConstantSlot11280C84;
	ConstantSlot gConstantSlot11280B9C;
	ConstantSlot gConstantSlot1128124C;
	ConstantSlot gConstantSlot11280B0C;
	ConstantSlot gConstantSlot112811E4;
	ConstantSlot gConstantSlot11280B1C;
	ConstantSlot gConstantSlot11280EE4;
	ConstantSlot gConstantSlot11280D20;
	ConstantSlot gConstantSlot11280CC4;
	ConstantSlot gConstantSlot11280C60;
	ConstantSlot gConstantSlot11280A48;
	ConstantSlot gConstantSlot11281074;
	ConstantSlot gConstantSlot11281194;
	ConstantSlot gConstantSlot11280E34;
	ConstantSlot gConstantSlot11280FCC;
	ConstantSlot gConstantSlot11280CD0;
	ConstantSlot gConstantSlot11280D18;
	ConstantSlot gConstantSlot11280A74;
	ConstantSlot gConstantSlot11280D08;
	ConstantSlot gConstantSlot1128104C;
	ConstantSlot gConstantSlot11281334;
	ConstantSlot gConstantSlot11281114;
	ConstantSlot gConstantSlot11281224;
	ConstantSlot gConstantSlot11280FB0;
	ConstantSlot gConstantSlot11280AC4;
	ConstantSlot gConstantSlot11280A94;
	ConstantSlot gConstantSlot11280C34;
	ConstantSlot gConstantSlot11280ABC;
	ConstantSlot gConstantSlot11280F20;
	ConstantSlot gConstantSlot11281284;
	ConstantSlot gConstantSlot1128132C;
	ConstantSlot gConstantSlot11280C78;
	ConstantSlot gConstantSlot112812A0;
	ConstantSlot gConstantSlot11280DBC;
	ConstantSlot gConstantSlot11280B60;
	ConstantSlot gConstantSlot11281134;
	ConstantSlot gConstantSlot112811FC;
	ConstantSlot gConstantSlot11280BD4;
	ConstantSlot gConstantSlot11280E04;
	ConstantSlot gConstantSlot11280C9C;
	ConstantSlot gConstantSlot11280B8C;
	ConstantSlot gConstantSlot11280CE8;
	ConstantSlot gConstantSlot112810F0;
	ConstantSlot gConstantSlot11280C24;
	ConstantSlot gConstantSlot11280AAC;
	ConstantSlot gConstantDecalColourBuffer;
	ConstantSlot gConstantDecalNormalBuffer;
	ConstantSlot gConstantSlot11280D10;
	ConstantSlot gConstantSlot11280C14;
	ConstantSlot gConstantSlot112810AC;
	ConstantSlot gConstantSlot11280ECC;
	ConstantSlot gConstantSlot11280AC8;
	ConstantSlot gConstantSlot11280F7C;
	ConstantSlot gConstantSlot11280BB0;
	ConstantSlot gConstantSlot11280BC0;
	ConstantSlot gConstantSlot1128125C;
	ConstantSlot gConstantSlot1128122C;
	ConstantSlot gConstantSlot112811B4;
	ConstantSlot gConstantSlot11280A80;
	ConstantSlot gConstantSlot11280D1C;
	ConstantSlot gConstantSlot11280BA4;
	ConstantSlot gConstantSlot11280D24;
	ConstantSlot gConstantSlot112812B0;
	ConstantSlot gConstantSlot11280EDC;
	ConstantSlot gConstantSlot11280CA8;
	ConstantSlot gConstantSlot11280AEC;
	ConstantSlot gConstantSlot11280CF8;
	ConstantSlot gConstantSlot11280E8C;
	ConstantSlot gConstantSlot11280E0C;
	ConstantSlot gConstantSlot11280A3C;
	ConstantSlot gConstantSlot11280C54;
	ConstantSlot gConstantSlot11280AD4;
	ConstantSlot gConstantSlot11281138;
	ConstantSlot gConstantSlot1128121C;
	ConstantSlot gConstantSlot11280DA8;
	ConstantSlot gConstantSlot112811DC;
	ConstantSlot gConstantSlot11280B28;
	ConstantSlot gConstantSlot11280B90;
	ConstantSlot gConstantSlot11280BF4;
	ConstantSlot gConstantSlot11280A84;
	ConstantSlot gConstantSlot11280A34;
	ConstantSlot gConstantSlot11280B20;
	ConstantSlot gConstantSlot11280DA0;
	ConstantSlot gConstantSlot11280DAC;
	ConstantSlot gConstantSlot11280AA8;
	ConstantSlot gConstantSlot11280D90;
	ConstantSlot gConstantSlot11280D38;
	ConstantSlot gConstantSlot11281214;
}

namespace pure3d
{
	ConstantSlot gConstantSlot11276BE4;
	ConstantSlot gConstantSlot11276BE0;
	ConstantSlot gConstantLightAmbient;
	ConstantSlot gConstantSlot11280CAC;
	ConstantSlot gConstantLightColour;
	ConstantSlot gConstantSlot11280AB4;
	ConstantSlot gConstantSlot11281124;
	ConstantSlot gConstantSlot11280A44;
	ConstantSlot gConstantSlot11281324;
	ConstantSlot gConstantSlot11280DF4;
	ConstantSlot gConstantSlot11280FE4;
	ConstantSlot gConstantSlot11280A98;
	ConstantSlot gConstantSlot11280E28;
	ConstantSlot gConstantSlot11281304;
	ConstantSlot gConstantSlot11280F88;
	ConstantSlot gConstantSlot11280EA4;
	ConstantSlot gConstantSlot11280B04;
	ConstantSlot gConstantSlot11280F5C;
	ConstantSlot gConstantSlot112810B4;
	ConstantSlot gConstantSlot11281258;
	ConstantSlot gConstantSlot112811A4;
	ConstantSlot gConstantSlot11280CB8;
	ConstantSlot gConstantSlot11280FC4;
	ConstantSlot gConstantSlot11280ADC;
	ConstantSlot gConstantSlot11280B08;
	ConstantSlot gConstantSlot11280C74;
	ConstantSlot gConstantSlot11280EEC;
	ConstantSlot gConstantSlot11280E94;
	ConstantSlot gConstantSlot11280C30;
	ConstantSlot gConstantSlot11280CDC;
	ConstantSlot gConstantSlot11280D50;
	ConstantSlot gConstantSlot11280C70;
	ConstantSlot gConstantSlot112812E4;
	ConstantSlot gConstantSlot11280E9C;
	ConstantSlot gConstantSlot11280D64;
	ConstantSlot gConstantSlot11280E64;
	ConstantSlot gConstantSlot11280BE8;
	ConstantSlot gConstantSlot11281280;
	ConstantSlot gConstantSlot11280C8C;
	ConstantSlot gConstantSlot112811F0;
	ConstantSlot gConstantSlot11280A38;
	ConstantSlot gConstantSlot11280A30;
	ConstantSlot gConstantSlot11280B94;
	ConstantSlot gConstantSlot11280AB8;
	ConstantSlot gConstantSlot11280B34;
	ConstantSlot gConstantSlot11280BF8;
	ConstantSlot gConstantSlot11280C68;
	ConstantSlot gConstantSlot11280B74;
	ConstantSlot gConstantSlot11280DA4;
	ConstantSlot gConstantSlot11280F2C;
	ConstantSlot gConstantSlot11280AE8;
	ConstantSlot gConstantSlot11281060;
	ConstantSlot gConstantLightIsLitPass;
	ConstantSlot gConstantSlot11280C7C;
	ConstantSlot gConstantSlot1128102C;
	ConstantSlot gConstantSlot11280CA4;
	ConstantSlot gConstantLightEnableSpotKill;
	ConstantSlot gConstantSlot11280F78;
	ConstantSlot gConstantLightObjectSpaceLightBounds;
	ConstantSlot gConstantHalfPixel;
	ConstantSlot gConstantSlot1128126C;
	ConstantSlot gConstantSlot11280C2C;
	ConstantSlot gConstantSlot11280A5C;
	ConstantSlot gConstantSlot112811C4;
	ConstantSlot gConstantShaderLODGeo;
	ConstantSlot gConstantSlot11281110;
	ConstantSlot gConstantSlot11280B54;
	ConstantSlot gConstantSlot1128129C;
	ConstantSlot gConstantSlot11280A68;
	ConstantSlot gConstantSlot112812D4;
	ConstantSlot gConstantSlot11280F1C;
	ConstantSlot gConstantSlot11280D4C;
	ConstantSlot gConstantSlot11280D88;
	ConstantSlot gConstantSlot11280DB4;
	ConstantSlot gConstantSlot112810A4;
	ConstantSlot gConstantSlot112810BC;
	ConstantSlot gConstantSlot11281190;
	ConstantSlot gConstantSlot1128111C;
	ConstantSlot gConstantSlot11280D04;
	ConstantSlot gConstantSlot11280E78;
	ConstantSlot gConstantSlot11280CC0;
	ConstantSlot gConstantSlot11280CB4;
	ConstantSlot gConstantSlot11280F64;
	ConstantSlot gConstantSlot11280B78;
	ConstantSlot gConstantSlot11280E40;
	ConstantSlot gConstantSlot11280B88;
	ConstantSlot gConstantSlot11280BA0;
	ConstantSlot gConstantSlot112811F4;
	ConstantSlot gConstantShadowMap;
	ConstantSlot gConstantTime;
	ConstantSlot gConstantLightDecalBuffer;
	ConstantSlot gConstantPRLightColour1;
	ConstantSlot gConstantPRLightColour2;
	ConstantSlot gConstantPRLightColour3;
	ConstantSlot gConstantPRLightColour4;
	ConstantSlot gConstantPRLightColour5;
	ConstantSlot gConstantPRLightAmbient;
	ConstantSlot gConstantPRLightDirection1;
	ConstantSlot gConstantPRLightDirection2;
	ConstantSlot gConstantPRLightDirection3;
	ConstantSlot gConstantPRLightDirection4;
	ConstantSlot gConstantPRLightDirection5;
	ConstantSlot gConstantPRLightParams1;
	ConstantSlot gConstantSlot11280B70;
	ConstantSlot gConstantSlot11280C10;
	ConstantSlot gConstantSlot112810C4;
	ConstantSlot gConstantSlot11280B7C;
	ConstantSlot gConstantSlot11281034;
	ConstantSlot gConstantSlot11280B5C;
	ConstantSlot gConstantSlot11280FB4;
	ConstantSlot gConstantSlot11280B18;
	ConstantSlot gConstantSlot11280D80;
	ConstantSlot gConstantSlot11280C38;
	ConstantSlot gConstantSlot11280B44;
	ConstantSlot gConstantSlot11280F54;
	ConstantSlot gConstantSlot11280CD4;
	ConstantSlot gConstantSlot11280E4C;
	ConstantSlot gConstantSlot11280D3C;
	ConstantSlot gConstantSlot11280ED4;
	ConstantSlot gConstantSlot11280F9C;
	ConstantSlot gConstantSlot11280A58;
	ConstantSlot gConstantSlot11280D84;
	ConstantSlot gConstantSlot11280E5C;
	ConstantSlot gConstantSlot11280B50;
	ConstantSlot gConstantSlot1128113C;
	ConstantSlot gConstantSlot11280D40;
	ConstantSlot gConstantSlot11280BB4;
	ConstantSlot gConstantSlot11280B3C;
	ConstantSlot gConstantSlot112812B4;
	ConstantSlot gConstantSlot11280DB8;
	ConstantSlot gConstantSlot1128120C;
	ConstantSlot gConstantSlot11280E44;
	ConstantSlot gConstantSlot11280EFC;
	ConstantSlot gConstantSlot11280BC4;
	ConstantSlot gConstantSlot11280B4C;
	ConstantSlot gConstantSlot11280C08;
	ConstantSlot gConstantSlot11280BC8;
	ConstantSlot gConstantSlot11280B6C;
	ConstantSlot gConstantSlot11280B2C;
	ConstantSlot gConstantSlot112812A4;
	ConstantSlot gConstantSlot11280B14;
	ConstantSlot gConstantSlot11280CC8;
	ConstantSlot gConstantSlot11280CE4;
	ConstantSlot gConstantSlot11280A88;
	ConstantSlot gConstantSlot1128103C;
	ConstantSlot gConstantSlot11280C50;
	ConstantSlot gConstantSlot11280A40;
	ConstantSlot gConstantSlot1128128C;
	ConstantSlot gConstantSlot11280CEC;
	ConstantSlot gConstantSlot11280B00;
	ConstantSlot gConstantSlot11280EAC;
	ConstantSlot gConstantSlot11280F24;
	ConstantSlot gConstantSlot11280AB0;
	ConstantSlot gConstantSlot11280BCC;
	ConstantSlot gConstantSlot11280D34;
	ConstantSlot gConstantSlot112810CC;
	ConstantSlot gConstantSlot11281174;
	ConstantSlot gConstantSlot11280CB0;
	ConstantSlot gConstantSlot11280E7C;
	ConstantSlot gConstantSlot11280C98;
	ConstantSlot gConstantSlot112812CC;
	ConstantSlot gConstantSlot11281064;
	ConstantSlot gConstantSlot112810F4;
	ConstantSlot gConstantSlot11280AF0;
	ConstantSlot gConstantSlot11280C18;
	ConstantSlot gConstantSlot11280EB4;
	ConstantSlot gConstantSlot11280C58;
	ConstantSlot gConstantSlot11281014;
	ConstantSlot gConstantSlot11280E14;
	ConstantSlot gConstantSlot11281164;
	ConstantSlot gConstantSlot11280D9C;
	ConstantSlot gConstantSlot11280A8C;
	ConstantSlot gConstantSlot11280FA4;
	ConstantSlot gConstantSlot11281244;
	ConstantSlot gConstantSlot11281264;
	ConstantSlot gConstantSlot11280DCC;
	ConstantSlot gConstantSlot11280D14;
	ConstantSlot gConstantSlot11280CF4;
	ConstantSlot gConstantSlot11280D8C;
	ConstantSlot gConstantSlot11280CD8;
	ConstantSlot gConstantSlot11280CF0;
	ConstantSlot gConstantSlot11280C20;
	ConstantSlot gConstantSlot11280E80;
	ConstantSlot gConstantSlot11280E84;
	ConstantSlot gConstantSlot11280B80;
	ConstantSlot gConstantSlot11280F3C;
	ConstantSlot gConstantSlot11280CA0;
	ConstantSlot gConstantSlot11280EBC;
	ConstantSlot gConstantSlot11280D60;
	ConstantSlot gConstantPRLightAmbientVertex;
	ConstantSlot gConstantSlot11280FDC;
	ConstantSlot gConstantProtoJointMatrix;
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D66720
// FUNCTION: ENGINE 0x10D66730
// FUNCTION: ENGINE 0x10D6FF70
// FUNCTION: ENGINE 0x10D6FF80
// FUNCTION: ENGINE 0x10D6FF90
// FUNCTION: ENGINE 0x10D6FFA0
// FUNCTION: ENGINE 0x10D6FFB0
// FUNCTION: ENGINE 0x10D6FFC0
// FUNCTION: ENGINE 0x10D6FFD0
// FUNCTION: ENGINE 0x10D6FFE0
// FUNCTION: ENGINE 0x10D6FFF0
// FUNCTION: ENGINE 0x10D70000
// FUNCTION: ENGINE 0x10D70010
// FUNCTION: ENGINE 0x10D70020
// FUNCTION: ENGINE 0x10D70030
// FUNCTION: ENGINE 0x10D70040
// FUNCTION: ENGINE 0x10D70050
// FUNCTION: ENGINE 0x10D70060
// FUNCTION: ENGINE 0x10D70070
// FUNCTION: ENGINE 0x10D70080
// FUNCTION: ENGINE 0x10D70090
// FUNCTION: ENGINE 0x10D700A0
// FUNCTION: ENGINE 0x10D700B0
// FUNCTION: ENGINE 0x10D700C0
// FUNCTION: ENGINE 0x10D700D0
// FUNCTION: ENGINE 0x10D700E0
// FUNCTION: ENGINE 0x10D700F0
// FUNCTION: ENGINE 0x10D70100
// FUNCTION: ENGINE 0x10D70110
// FUNCTION: ENGINE 0x10D70120
// FUNCTION: ENGINE 0x10D70130
// FUNCTION: ENGINE 0x10D70140
// FUNCTION: ENGINE 0x10D70150
// FUNCTION: ENGINE 0x10D70160
// FUNCTION: ENGINE 0x10D70170
// FUNCTION: ENGINE 0x10D70180
// FUNCTION: ENGINE 0x10D70190
// FUNCTION: ENGINE 0x10D701A0
// FUNCTION: ENGINE 0x10D701B0
// FUNCTION: ENGINE 0x10D701C0
// FUNCTION: ENGINE 0x10D701D0
// FUNCTION: ENGINE 0x10D701E0
// FUNCTION: ENGINE 0x10D701F0
// FUNCTION: ENGINE 0x10D70200
// FUNCTION: ENGINE 0x10D70210
// FUNCTION: ENGINE 0x10D70220
// FUNCTION: ENGINE 0x10D70230
// FUNCTION: ENGINE 0x10D70240
// FUNCTION: ENGINE 0x10D70250
// FUNCTION: ENGINE 0x10D70260
// FUNCTION: ENGINE 0x10D70270
// FUNCTION: ENGINE 0x10D70280
// FUNCTION: ENGINE 0x10D70290
// FUNCTION: ENGINE 0x10D702A0
// FUNCTION: ENGINE 0x10D702B0
// FUNCTION: ENGINE 0x10D702C0
// FUNCTION: ENGINE 0x10D702D0
// FUNCTION: ENGINE 0x10D702E0
// FUNCTION: ENGINE 0x10D702F0
// FUNCTION: ENGINE 0x10D707B0
// FUNCTION: ENGINE 0x10D707C0
// FUNCTION: ENGINE 0x10D707D0
// FUNCTION: ENGINE 0x10D707E0
// FUNCTION: ENGINE 0x10D707F0
// FUNCTION: ENGINE 0x10D70800
// FUNCTION: ENGINE 0x10D70810
// FUNCTION: ENGINE 0x10D70820
// FUNCTION: ENGINE 0x10D70830
// FUNCTION: ENGINE 0x10D70840
// FUNCTION: ENGINE 0x10D70850
// FUNCTION: ENGINE 0x10D70860
// FUNCTION: ENGINE 0x10D70870
// FUNCTION: ENGINE 0x10D70880
// FUNCTION: ENGINE 0x10D70890
// FUNCTION: ENGINE 0x10D708A0
// FUNCTION: ENGINE 0x10D708B0
// FUNCTION: ENGINE 0x10D708C0
// FUNCTION: ENGINE 0x10D708D0
// FUNCTION: ENGINE 0x10D708E0
// FUNCTION: ENGINE 0x10D708F0
// FUNCTION: ENGINE 0x10D70900
// FUNCTION: ENGINE 0x10D70910
// FUNCTION: ENGINE 0x10D70920
// FUNCTION: ENGINE 0x10D70930
// FUNCTION: ENGINE 0x10D70940
// FUNCTION: ENGINE 0x10D70950
// FUNCTION: ENGINE 0x10D70960
// FUNCTION: ENGINE 0x10D70970
// FUNCTION: ENGINE 0x10D70980
// FUNCTION: ENGINE 0x10D709A0
// FUNCTION: ENGINE 0x10D70D80
// FUNCTION: ENGINE 0x10D70FC0
// FUNCTION: ENGINE 0x10D70FD0
// FUNCTION: ENGINE 0x10D70FE0
// FUNCTION: ENGINE 0x10D70FF0
// FUNCTION: ENGINE 0x10D71000
// FUNCTION: ENGINE 0x10D71010
// FUNCTION: ENGINE 0x10D71020
// FUNCTION: ENGINE 0x10D71030
// FUNCTION: ENGINE 0x10D71040
// FUNCTION: ENGINE 0x10D71050
// FUNCTION: ENGINE 0x10D71060
// FUNCTION: ENGINE 0x10D71070
// FUNCTION: ENGINE 0x10D71080
// FUNCTION: ENGINE 0x10D71090
// FUNCTION: ENGINE 0x10D710A0
// FUNCTION: ENGINE 0x10D710B0
// FUNCTION: ENGINE 0x10D710C0
// FUNCTION: ENGINE 0x10D710D0
// FUNCTION: ENGINE 0x10D710E0
// FUNCTION: ENGINE 0x10D710F0
// FUNCTION: ENGINE 0x10D71100
// FUNCTION: ENGINE 0x10D71110
// FUNCTION: ENGINE 0x10D71120
// FUNCTION: ENGINE 0x10D71130
// FUNCTION: ENGINE 0x10D71140
// FUNCTION: ENGINE 0x10D71150
// FUNCTION: ENGINE 0x10D71160
// FUNCTION: ENGINE 0x10D71170
// FUNCTION: ENGINE 0x10D71180
// FUNCTION: ENGINE 0x10D71190
// FUNCTION: ENGINE 0x10D711A0
// FUNCTION: ENGINE 0x10D711B0
// FUNCTION: ENGINE 0x10D711C0
// FUNCTION: ENGINE 0x10D711D0
// FUNCTION: ENGINE 0x10D711E0
// FUNCTION: ENGINE 0x10D711F0
// FUNCTION: ENGINE 0x10D71200
// FUNCTION: ENGINE 0x10D71210
// FUNCTION: ENGINE 0x10D71220
// FUNCTION: ENGINE 0x10D71230
// FUNCTION: ENGINE 0x10D71240
// FUNCTION: ENGINE 0x10D71250
// FUNCTION: ENGINE 0x10D71260
// FUNCTION: ENGINE 0x10D71270
// FUNCTION: ENGINE 0x10D71280
// FUNCTION: ENGINE 0x10D71290
// FUNCTION: ENGINE 0x10D712A0
// FUNCTION: ENGINE 0x10D712B0
// FUNCTION: ENGINE 0x10D712C0
// FUNCTION: ENGINE 0x10D712D0
// FUNCTION: ENGINE 0x10D712E0
// FUNCTION: ENGINE 0x10D712F0
// FUNCTION: ENGINE 0x10D71300
// FUNCTION: ENGINE 0x10D71310
// FUNCTION: ENGINE 0x10D71320
// FUNCTION: ENGINE 0x10D71330
// FUNCTION: ENGINE 0x10D71340
// FUNCTION: ENGINE 0x10D71350
// FUNCTION: ENGINE 0x10D71360
// FUNCTION: ENGINE 0x10D71370
// FUNCTION: ENGINE 0x10D71380
// FUNCTION: ENGINE 0x10D71390
// FUNCTION: ENGINE 0x10D713A0
// FUNCTION: ENGINE 0x10D713B0
// FUNCTION: ENGINE 0x10D713C0
// FUNCTION: ENGINE 0x10D713D0
// FUNCTION: ENGINE 0x10D713E0
// FUNCTION: ENGINE 0x10D713F0
// FUNCTION: ENGINE 0x10D71400
// FUNCTION: ENGINE 0x10D71410
// FUNCTION: ENGINE 0x10D71420
// FUNCTION: ENGINE 0x10D71430
// FUNCTION: ENGINE 0x10D71440
// FUNCTION: ENGINE 0x10D71450
// FUNCTION: ENGINE 0x10D71460
// FUNCTION: ENGINE 0x10D71470
// FUNCTION: ENGINE 0x10D71480
// FUNCTION: ENGINE 0x10D71490
// FUNCTION: ENGINE 0x10D714A0
// FUNCTION: ENGINE 0x10D714B0
// FUNCTION: ENGINE 0x10D714C0
// FUNCTION: ENGINE 0x10D714D0
// FUNCTION: ENGINE 0x10D714E0
// FUNCTION: ENGINE 0x10D714F0
// FUNCTION: ENGINE 0x10D71500
// FUNCTION: ENGINE 0x10D71510
// FUNCTION: ENGINE 0x10D71520
// FUNCTION: ENGINE 0x10D71530
// FUNCTION: ENGINE 0x10D71540
// FUNCTION: ENGINE 0x10D71550
// FUNCTION: ENGINE 0x10D71560
// FUNCTION: ENGINE 0x10D71570
// FUNCTION: ENGINE 0x10D71580
// FUNCTION: ENGINE 0x10D71590
// FUNCTION: ENGINE 0x10D715A0
// FUNCTION: ENGINE 0x10D715B0
// FUNCTION: ENGINE 0x10D715C0
// FUNCTION: ENGINE 0x10D715D0
// FUNCTION: ENGINE 0x10D715E0
// FUNCTION: ENGINE 0x10D715F0
// FUNCTION: ENGINE 0x10D71600


// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D671A0
// FUNCTION: ENGINE 0x10D671E0
// FUNCTION: ENGINE 0x10D67220
// FUNCTION: ENGINE 0x10D67260
// FUNCTION: ENGINE 0x10D67420
// FUNCTION: ENGINE 0x10D67460
// FUNCTION: ENGINE 0x10D674E0
// FUNCTION: ENGINE 0x10D67560
// FUNCTION: ENGINE 0x10D675E0
// FUNCTION: ENGINE 0x10D67620
// FUNCTION: ENGINE 0x10D67660
// FUNCTION: ENGINE 0x10D676E0
// FUNCTION: ENGINE 0x10D67720
// FUNCTION: ENGINE 0x10D67760
// FUNCTION: ENGINE 0x10D67AA0
// FUNCTION: ENGINE 0x10D67B20
// FUNCTION: ENGINE 0x10D67B60
// FUNCTION: ENGINE 0x10D68380
// FUNCTION: ENGINE 0x10D683C0
// FUNCTION: ENGINE 0x10D68400
// FUNCTION: ENGINE 0x10D68440
// FUNCTION: ENGINE 0x10D68480
// FUNCTION: ENGINE 0x10D684C0
// FUNCTION: ENGINE 0x10D68500
// FUNCTION: ENGINE 0x10D685C0
// FUNCTION: ENGINE 0x10D68880
// FUNCTION: ENGINE 0x10D688C0
// FUNCTION: ENGINE 0x10D68900
// FUNCTION: ENGINE 0x10D68940
// FUNCTION: ENGINE 0x10D68A80
// FUNCTION: ENGINE 0x10D68B00
// FUNCTION: ENGINE 0x10D68B40
// FUNCTION: ENGINE 0x10D68D00
// FUNCTION: ENGINE 0x10D68D40
// FUNCTION: ENGINE 0x10D68E40
// FUNCTION: ENGINE 0x10D68F40
// FUNCTION: ENGINE 0x10D69040
// FUNCTION: ENGINE 0x10D69100
// FUNCTION: ENGINE 0x10D69140
// FUNCTION: ENGINE 0x10D69180
// FUNCTION: ENGINE 0x10D691C0
// FUNCTION: ENGINE 0x10D69200
// FUNCTION: ENGINE 0x10D69240
// FUNCTION: ENGINE 0x10D69280
// FUNCTION: ENGINE 0x10D692C0
// FUNCTION: ENGINE 0x10D69300
// FUNCTION: ENGINE 0x10D69340
// FUNCTION: ENGINE 0x10D69380
// FUNCTION: ENGINE 0x10D693C0
// FUNCTION: ENGINE 0x10D69400
// FUNCTION: ENGINE 0x10D69440
// FUNCTION: ENGINE 0x10D69480
// FUNCTION: ENGINE 0x10D694C0
// FUNCTION: ENGINE 0x10D69500
// FUNCTION: ENGINE 0x10D69540
// FUNCTION: ENGINE 0x10D69580
// FUNCTION: ENGINE 0x10D695C0
// FUNCTION: ENGINE 0x10D69600
// FUNCTION: ENGINE 0x10D69640
// FUNCTION: ENGINE 0x10D69680
// FUNCTION: ENGINE 0x10D696C0
// FUNCTION: ENGINE 0x10D69700
// FUNCTION: ENGINE 0x10D697E0
// FUNCTION: ENGINE 0x10D69820
// FUNCTION: ENGINE 0x10D69860
// FUNCTION: ENGINE 0x10D698A0
// FUNCTION: ENGINE 0x10D698E0
// FUNCTION: ENGINE 0x10D69920
// FUNCTION: ENGINE 0x10D69960
// FUNCTION: ENGINE 0x10D699A0
// FUNCTION: ENGINE 0x10D699E0
// FUNCTION: ENGINE 0x10D69A20
// FUNCTION: ENGINE 0x10D69A60
// FUNCTION: ENGINE 0x10D69AA0
// FUNCTION: ENGINE 0x10D69AE0
// FUNCTION: ENGINE 0x10D69B20
// FUNCTION: ENGINE 0x10D69B60
// FUNCTION: ENGINE 0x10D69BA0
// FUNCTION: ENGINE 0x10D69BE0
// FUNCTION: ENGINE 0x10D69C20
// FUNCTION: ENGINE 0x10D69C60
// FUNCTION: ENGINE 0x10D69CA0
// FUNCTION: ENGINE 0x10D69CE0
// FUNCTION: ENGINE 0x10D69D20
// FUNCTION: ENGINE 0x10D69D60
// FUNCTION: ENGINE 0x10D69DA0
// FUNCTION: ENGINE 0x10D69DE0
// FUNCTION: ENGINE 0x10D69E20
// FUNCTION: ENGINE 0x10D69E60
// FUNCTION: ENGINE 0x10D69EA0
// FUNCTION: ENGINE 0x10D69EE0
// FUNCTION: ENGINE 0x10D69F20
// FUNCTION: ENGINE 0x10D69F60
// FUNCTION: ENGINE 0x10D69FA0
// FUNCTION: ENGINE 0x10D69FE0
// FUNCTION: ENGINE 0x10D6A020
// FUNCTION: ENGINE 0x10D6A060
// FUNCTION: ENGINE 0x10D6A0E0
// FUNCTION: ENGINE 0x10D6A120
// FUNCTION: ENGINE 0x10D6A160
// FUNCTION: ENGINE 0x10D6A1A0
// FUNCTION: ENGINE 0x10D6A1E0
// FUNCTION: ENGINE 0x10D6A220
// FUNCTION: ENGINE 0x10D6A260
// FUNCTION: ENGINE 0x10D6A2A0
// FUNCTION: ENGINE 0x10D6A2E0
// FUNCTION: ENGINE 0x10D6A320
// FUNCTION: ENGINE 0x10D6A360
// FUNCTION: ENGINE 0x10D6A3A0
// FUNCTION: ENGINE 0x10D6A3E0
// FUNCTION: ENGINE 0x10D6A420
// FUNCTION: ENGINE 0x10D6A460
// FUNCTION: ENGINE 0x10D6A4A0
// FUNCTION: ENGINE 0x10D6A4E0
// FUNCTION: ENGINE 0x10D6A520
// FUNCTION: ENGINE 0x10D6A560
// FUNCTION: ENGINE 0x10D6A5A0
// FUNCTION: ENGINE 0x10D6A5E0
// FUNCTION: ENGINE 0x10D6A620
// FUNCTION: ENGINE 0x10D6A660
// FUNCTION: ENGINE 0x10D6A6A0
// FUNCTION: ENGINE 0x10D6A6E0
// FUNCTION: ENGINE 0x10D6A720
// FUNCTION: ENGINE 0x10D6A760
// FUNCTION: ENGINE 0x10D6A7A0
// FUNCTION: ENGINE 0x10D6A7E0
// FUNCTION: ENGINE 0x10D6A820
// FUNCTION: ENGINE 0x10D6A860
// FUNCTION: ENGINE 0x10D6A8A0
// FUNCTION: ENGINE 0x10D6A8E0
// FUNCTION: ENGINE 0x10D6A920
// FUNCTION: ENGINE 0x10D6A960
// FUNCTION: ENGINE 0x10D6A9A0
// FUNCTION: ENGINE 0x10D6A9E0
// FUNCTION: ENGINE 0x10D6AA20
// FUNCTION: ENGINE 0x10D6AA60
// FUNCTION: ENGINE 0x10D6AAA0
// FUNCTION: ENGINE 0x10D6AAE0
// FUNCTION: ENGINE 0x10D6AB20
// FUNCTION: ENGINE 0x10D6AB60
// FUNCTION: ENGINE 0x10D6ABA0
// FUNCTION: ENGINE 0x10D6ABE0
// FUNCTION: ENGINE 0x10D6AC20
// FUNCTION: ENGINE 0x10D6AC60
// FUNCTION: ENGINE 0x10D6ACA0
// FUNCTION: ENGINE 0x10D6ACE0
// FUNCTION: ENGINE 0x10D6AD20
// FUNCTION: ENGINE 0x10D6AD60
// FUNCTION: ENGINE 0x10D6ADA0
// FUNCTION: ENGINE 0x10D6ADE0
// FUNCTION: ENGINE 0x10D6AE20
// FUNCTION: ENGINE 0x10D6AE60
// FUNCTION: ENGINE 0x10D6AEA0
// FUNCTION: ENGINE 0x10D6AEE0
// FUNCTION: ENGINE 0x10D6AF20
// FUNCTION: ENGINE 0x10D6AF60
// FUNCTION: ENGINE 0x10D6AFA0
// FUNCTION: ENGINE 0x10D6AFE0
// FUNCTION: ENGINE 0x10D6B020
// FUNCTION: ENGINE 0x10D6B060
// FUNCTION: ENGINE 0x10D6B0A0
// FUNCTION: ENGINE 0x10D6B0E0
// FUNCTION: ENGINE 0x10D6B120
// FUNCTION: ENGINE 0x10D6B160
// FUNCTION: ENGINE 0x10D6B1A0
// FUNCTION: ENGINE 0x10D6B1E0
// FUNCTION: ENGINE 0x10D6B220
// FUNCTION: ENGINE 0x10D6B260
// FUNCTION: ENGINE 0x10D6B2A0
// FUNCTION: ENGINE 0x10D6B2E0
// FUNCTION: ENGINE 0x10D6B320
// FUNCTION: ENGINE 0x10D6B360
// FUNCTION: ENGINE 0x10D6B3A0
// FUNCTION: ENGINE 0x10D6B3E0
// FUNCTION: ENGINE 0x10D6B420
// FUNCTION: ENGINE 0x10D6B460
// FUNCTION: ENGINE 0x10D6B4A0
// FUNCTION: ENGINE 0x10D6B4E0
// FUNCTION: ENGINE 0x10D6B520
// FUNCTION: ENGINE 0x10D6B560
// FUNCTION: ENGINE 0x10D6B5A0
// FUNCTION: ENGINE 0x10D6B5E0
// FUNCTION: ENGINE 0x10D6B620
// FUNCTION: ENGINE 0x10D6B660
// FUNCTION: ENGINE 0x10D6B6A0
// FUNCTION: ENGINE 0x10D6B6E0
// FUNCTION: ENGINE 0x10D6B720
// FUNCTION: ENGINE 0x10D6B760
// FUNCTION: ENGINE 0x10D6B7A0
// FUNCTION: ENGINE 0x10D6B7E0
// FUNCTION: ENGINE 0x10D6B820
// FUNCTION: ENGINE 0x10D6B860
// FUNCTION: ENGINE 0x10D6B8A0
// FUNCTION: ENGINE 0x10D6B8E0
// FUNCTION: ENGINE 0x10D6B920
// FUNCTION: ENGINE 0x10D6B960
// FUNCTION: ENGINE 0x10D6B9A0
// FUNCTION: ENGINE 0x10D6B9E0
// FUNCTION: ENGINE 0x10D6BA20
// FUNCTION: ENGINE 0x10D6BA60
// FUNCTION: ENGINE 0x10D6BAA0
// FUNCTION: ENGINE 0x10D6BAE0
// FUNCTION: ENGINE 0x10D6BB20
// FUNCTION: ENGINE 0x10D6BB60
// FUNCTION: ENGINE 0x10D6BBA0
// FUNCTION: ENGINE 0x10D6BBE0
// FUNCTION: ENGINE 0x10D6BC20
// FUNCTION: ENGINE 0x10D6BC60
// FUNCTION: ENGINE 0x10D6BCA0
// FUNCTION: ENGINE 0x10D6BCE0
// FUNCTION: ENGINE 0x10D6BD20
// FUNCTION: ENGINE 0x10D6BD60
// FUNCTION: ENGINE 0x10D6BDA0
// FUNCTION: ENGINE 0x10D6BDE0
// FUNCTION: ENGINE 0x10D6BE20
// FUNCTION: ENGINE 0x10D6BE60
// FUNCTION: ENGINE 0x10D6BEA0
// FUNCTION: ENGINE 0x10D6BEE0
// FUNCTION: ENGINE 0x10D6BF20
// FUNCTION: ENGINE 0x10D6BF60
// FUNCTION: ENGINE 0x10D6BFA0
// FUNCTION: ENGINE 0x10D6BFE0
// FUNCTION: ENGINE 0x10D6C020
// FUNCTION: ENGINE 0x10D6C060
// FUNCTION: ENGINE 0x10D6C0A0
// FUNCTION: ENGINE 0x10D6C0E0
// FUNCTION: ENGINE 0x10D6C120
// FUNCTION: ENGINE 0x10D6C160
// FUNCTION: ENGINE 0x10D6C1A0
// FUNCTION: ENGINE 0x10D6C1E0
// FUNCTION: ENGINE 0x10D6C220
// FUNCTION: ENGINE 0x10D6C260
// FUNCTION: ENGINE 0x10D6C2A0
// FUNCTION: ENGINE 0x10D6C2E0
// FUNCTION: ENGINE 0x10D6C320
// FUNCTION: ENGINE 0x10D6C360
// FUNCTION: ENGINE 0x10D6C3A0
// FUNCTION: ENGINE 0x10D6C3E0
// FUNCTION: ENGINE 0x10D6C420
// FUNCTION: ENGINE 0x10D6C460
// FUNCTION: ENGINE 0x10D6C4A0
// FUNCTION: ENGINE 0x10D6C4E0
// FUNCTION: ENGINE 0x10D6C520
// FUNCTION: ENGINE 0x10D6C560
// FUNCTION: ENGINE 0x10D6C5A0
// FUNCTION: ENGINE 0x10D6C5E0
// FUNCTION: ENGINE 0x10D6C620
// FUNCTION: ENGINE 0x10D6C660
// FUNCTION: ENGINE 0x10D6C6A0
// FUNCTION: ENGINE 0x10D6C6E0
// FUNCTION: ENGINE 0x10D6C720
// FUNCTION: ENGINE 0x10D6C760
// FUNCTION: ENGINE 0x10D6C7A0
// FUNCTION: ENGINE 0x10D6C7E0
// FUNCTION: ENGINE 0x10D6C820
// FUNCTION: ENGINE 0x10D6C860
// FUNCTION: ENGINE 0x10D6C8A0
// FUNCTION: ENGINE 0x10D6C8E0
// FUNCTION: ENGINE 0x10D6C920
// FUNCTION: ENGINE 0x10D6C960
// FUNCTION: ENGINE 0x10D6C9A0
// FUNCTION: ENGINE 0x10D6C9E0
// FUNCTION: ENGINE 0x10D6CA20
// FUNCTION: ENGINE 0x10D6CA60
// FUNCTION: ENGINE 0x10D6CAA0
// FUNCTION: ENGINE 0x10D6CAE0
// FUNCTION: ENGINE 0x10D6CB20
// FUNCTION: ENGINE 0x10D6CB60
// FUNCTION: ENGINE 0x10D6CBA0
// FUNCTION: ENGINE 0x10D6CBE0
// FUNCTION: ENGINE 0x10D6CC20
// FUNCTION: ENGINE 0x10D6CC60
// FUNCTION: ENGINE 0x10D6CCA0
// FUNCTION: ENGINE 0x10D6CCE0
// FUNCTION: ENGINE 0x10D6CD20
// FUNCTION: ENGINE 0x10D6CD60
// FUNCTION: ENGINE 0x10D6CDA0
// FUNCTION: ENGINE 0x10D6CDE0
// FUNCTION: ENGINE 0x10D6CE20
// FUNCTION: ENGINE 0x10D6CE60
// FUNCTION: ENGINE 0x10D6CEA0
// FUNCTION: ENGINE 0x10D6CEE0
// FUNCTION: ENGINE 0x10D6CF20
// FUNCTION: ENGINE 0x10D6CF60
// FUNCTION: ENGINE 0x10D6CFA0
// FUNCTION: ENGINE 0x10D6CFE0
// FUNCTION: ENGINE 0x10D6D020
// FUNCTION: ENGINE 0x10D6D060
// FUNCTION: ENGINE 0x10D6D0A0
// FUNCTION: ENGINE 0x10D6D0E0
// FUNCTION: ENGINE 0x10D6D120
// FUNCTION: ENGINE 0x10D6D160
// FUNCTION: ENGINE 0x10D6D1A0
// FUNCTION: ENGINE 0x10D6D1E0
// FUNCTION: ENGINE 0x10D6D220
// FUNCTION: ENGINE 0x10D6D260
// FUNCTION: ENGINE 0x10D6D2A0
// FUNCTION: ENGINE 0x10D6D2E0
// FUNCTION: ENGINE 0x10D6D320
// FUNCTION: ENGINE 0x10D6D360
// FUNCTION: ENGINE 0x10D6D3A0
// FUNCTION: ENGINE 0x10D6D3E0
// FUNCTION: ENGINE 0x10D6D420
// FUNCTION: ENGINE 0x10D6D460
// FUNCTION: ENGINE 0x10D6D4A0
// FUNCTION: ENGINE 0x10D6D4E0
// FUNCTION: ENGINE 0x10D6D520
// FUNCTION: ENGINE 0x10D6D560
// FUNCTION: ENGINE 0x10D6D5A0
// FUNCTION: ENGINE 0x10D6D5E0
// FUNCTION: ENGINE 0x10D6D620
// FUNCTION: ENGINE 0x10D6D660
// FUNCTION: ENGINE 0x10D6D6A0
// FUNCTION: ENGINE 0x10D6D6E0
// FUNCTION: ENGINE 0x10D6D720
// FUNCTION: ENGINE 0x10D6D760
// FUNCTION: ENGINE 0x10D6D7A0
// FUNCTION: ENGINE 0x10D6D7E0
// FUNCTION: ENGINE 0x10D6D820
// FUNCTION: ENGINE 0x10D6D860
// FUNCTION: ENGINE 0x10D6D8A0
// FUNCTION: ENGINE 0x10D6D8E0
// FUNCTION: ENGINE 0x10D6D920
// FUNCTION: ENGINE 0x10D6D960
// FUNCTION: ENGINE 0x10D6D9A0
// FUNCTION: ENGINE 0x10D6D9E0
// FUNCTION: ENGINE 0x10D6DA20
// FUNCTION: ENGINE 0x10D6DA60
// FUNCTION: ENGINE 0x10D6DAA0
// FUNCTION: ENGINE 0x10D6DAE0
// FUNCTION: ENGINE 0x10D6DB20
// FUNCTION: ENGINE 0x10D6DB60
// FUNCTION: ENGINE 0x10D6DBA0
// FUNCTION: ENGINE 0x10D6DBE0
// FUNCTION: ENGINE 0x10D6DC20
// FUNCTION: ENGINE 0x10D6DC60
// FUNCTION: ENGINE 0x10D6DCA0
// FUNCTION: ENGINE 0x10D6DCE0
// FUNCTION: ENGINE 0x10D6DD20
// FUNCTION: ENGINE 0x10D6DD60
// FUNCTION: ENGINE 0x10D6DDA0
// FUNCTION: ENGINE 0x10D6DDE0
// FUNCTION: ENGINE 0x10D6DE20
// FUNCTION: ENGINE 0x10D6DE60
// FUNCTION: ENGINE 0x10D6DEA0
// FUNCTION: ENGINE 0x10D6DEE0
// FUNCTION: ENGINE 0x10D6DF20
// FUNCTION: ENGINE 0x10D6DF60
// FUNCTION: ENGINE 0x10D6DFA0
// FUNCTION: ENGINE 0x10D6DFE0
// FUNCTION: ENGINE 0x10D6E020
// FUNCTION: ENGINE 0x10D6E060
// FUNCTION: ENGINE 0x10D6E0A0
// FUNCTION: ENGINE 0x10D6E0E0
// FUNCTION: ENGINE 0x10D6E120
// FUNCTION: ENGINE 0x10D6E160
// FUNCTION: ENGINE 0x10D6E1A0
// FUNCTION: ENGINE 0x10D6E1E0
// FUNCTION: ENGINE 0x10D6E220
// FUNCTION: ENGINE 0x10D6E260
// FUNCTION: ENGINE 0x10D6E2A0
// FUNCTION: ENGINE 0x10D6E2E0
// FUNCTION: ENGINE 0x10D6E320
// FUNCTION: ENGINE 0x10D6E360
// FUNCTION: ENGINE 0x10D6E3A0
// FUNCTION: ENGINE 0x10D6E3E0
// FUNCTION: ENGINE 0x10D6E420
// FUNCTION: ENGINE 0x10D6E460
// FUNCTION: ENGINE 0x10D6E4A0
// FUNCTION: ENGINE 0x10D6E4E0
// FUNCTION: ENGINE 0x10D6E520
// FUNCTION: ENGINE 0x10D6E560
// FUNCTION: ENGINE 0x10D6E5A0
// FUNCTION: ENGINE 0x10D6E5E0
// FUNCTION: ENGINE 0x10D6E620
// FUNCTION: ENGINE 0x10D6E660
// FUNCTION: ENGINE 0x10D6E6A0
// FUNCTION: ENGINE 0x10D6E6E0
// FUNCTION: ENGINE 0x10D6E720
// FUNCTION: ENGINE 0x10D6E760
// FUNCTION: ENGINE 0x10D6E7A0
// FUNCTION: ENGINE 0x10D6E7E0
// FUNCTION: ENGINE 0x10D6E820
// FUNCTION: ENGINE 0x10D6E860
// FUNCTION: ENGINE 0x10D6E8A0
// FUNCTION: ENGINE 0x10D6E8E0
// FUNCTION: ENGINE 0x10D6E920
// FUNCTION: ENGINE 0x10D6E960
// FUNCTION: ENGINE 0x10D6E9A0
// FUNCTION: ENGINE 0x10D6E9E0
// FUNCTION: ENGINE 0x10D6EA20
// FUNCTION: ENGINE 0x10D6EA60
// FUNCTION: ENGINE 0x10D6EAA0
// FUNCTION: ENGINE 0x10D6EAE0
// FUNCTION: ENGINE 0x10D6EB20
// FUNCTION: ENGINE 0x10D6EB60
// FUNCTION: ENGINE 0x10D6EBA0
// FUNCTION: ENGINE 0x10D6EBE0
// FUNCTION: ENGINE 0x10D6EC20
// FUNCTION: ENGINE 0x10D6EC60
// FUNCTION: ENGINE 0x10D6ECA0
// FUNCTION: ENGINE 0x10D6ECE0
// FUNCTION: ENGINE 0x10D6ED20
// FUNCTION: ENGINE 0x10D6ED60
// FUNCTION: ENGINE 0x10D6EDA0
// FUNCTION: ENGINE 0x10D6EDE0
// FUNCTION: ENGINE 0x10D6EE20
// FUNCTION: ENGINE 0x10D6EE60
// FUNCTION: ENGINE 0x10D6EEA0
// FUNCTION: ENGINE 0x10D6EEE0
// FUNCTION: ENGINE 0x10D6EF20
// FUNCTION: ENGINE 0x10D6EF60
// FUNCTION: ENGINE 0x10D6EFA0
// FUNCTION: ENGINE 0x10D6EFE0
// FUNCTION: ENGINE 0x10D6F020
// FUNCTION: ENGINE 0x10D6F060
// FUNCTION: ENGINE 0x10D6F0A0
// FUNCTION: ENGINE 0x10D6F0E0
// FUNCTION: ENGINE 0x10D6F120
// FUNCTION: ENGINE 0x10D6F160
// FUNCTION: ENGINE 0x10D6F1A0
// FUNCTION: ENGINE 0x10D6F1E0
// FUNCTION: ENGINE 0x10D6F220
// FUNCTION: ENGINE 0x10D6F260
// FUNCTION: ENGINE 0x10D6F2A0
// FUNCTION: ENGINE 0x10D6F2E0
// FUNCTION: ENGINE 0x10D6F320
// FUNCTION: ENGINE 0x10D6F360
// FUNCTION: ENGINE 0x10D6F3A0
// FUNCTION: ENGINE 0x10D6F3E0
// FUNCTION: ENGINE 0x10D6F420
// FUNCTION: ENGINE 0x10D6F460
// FUNCTION: ENGINE 0x10D6F4A0
// FUNCTION: ENGINE 0x10D6F4E0
// FUNCTION: ENGINE 0x10D6F520
// FUNCTION: ENGINE 0x10D6F560
// FUNCTION: ENGINE 0x10D6F5A0
// FUNCTION: ENGINE 0x10D6F5E0
// FUNCTION: ENGINE 0x10D6F620
// FUNCTION: ENGINE 0x10D6F660
// FUNCTION: ENGINE 0x10D6F6A0
// FUNCTION: ENGINE 0x10D6F6E0
// FUNCTION: ENGINE 0x10D6F720
// FUNCTION: ENGINE 0x10D6F760
// FUNCTION: ENGINE 0x10D6F7A0
// FUNCTION: ENGINE 0x10D6F7E0
// FUNCTION: ENGINE 0x10D6F820
// FUNCTION: ENGINE 0x10D6F860
// FUNCTION: ENGINE 0x10D6F8A0
// FUNCTION: ENGINE 0x10D6F8E0
// FUNCTION: ENGINE 0x10D6F920
// FUNCTION: ENGINE 0x10D6F960
// FUNCTION: ENGINE 0x10D6F9A0
// FUNCTION: ENGINE 0x10D6F9E0
// FUNCTION: ENGINE 0x10D6FA20
// FUNCTION: ENGINE 0x10D6FA60
// FUNCTION: ENGINE 0x10D6FAA0
// FUNCTION: ENGINE 0x10D6FAE0
// FUNCTION: ENGINE 0x10D6FB20
// FUNCTION: ENGINE 0x10D6FB60
// FUNCTION: ENGINE 0x10D6FBA0
// FUNCTION: ENGINE 0x10D6FBE0
// FUNCTION: ENGINE 0x10D6FC20
// FUNCTION: ENGINE 0x10D6FC60
// FUNCTION: ENGINE 0x10D6FCA0
// FUNCTION: ENGINE 0x10D6FCE0
// FUNCTION: ENGINE 0x10D6FD20
// FUNCTION: ENGINE 0x10D6FD30
// FUNCTION: ENGINE 0x10D6FD40
// FUNCTION: ENGINE 0x10D6FD50
// FUNCTION: ENGINE 0x10D6FD60
// FUNCTION: ENGINE 0x10D6FD70
// FUNCTION: ENGINE 0x10D6FD80
// FUNCTION: ENGINE 0x10D6FD90
// FUNCTION: ENGINE 0x10D6FDA0
// FUNCTION: ENGINE 0x10D6FDB0
// FUNCTION: ENGINE 0x10D6FDC0
// FUNCTION: ENGINE 0x10D6FDD0
// FUNCTION: ENGINE 0x10D6FDE0
// FUNCTION: ENGINE 0x10D6FDF0
// FUNCTION: ENGINE 0x10D6FE00
// FUNCTION: ENGINE 0x10D6FE10
// FUNCTION: ENGINE 0x10D6FE20
// FUNCTION: ENGINE 0x10D6FE30
// FUNCTION: ENGINE 0x10D6FE40
// FUNCTION: ENGINE 0x10D6FE50
// FUNCTION: ENGINE 0x10D6FE60
// FUNCTION: ENGINE 0x10D6FE70
// FUNCTION: ENGINE 0x10D6FE80
// FUNCTION: ENGINE 0x10D6FE90
// FUNCTION: ENGINE 0x10D6FEA0
// FUNCTION: ENGINE 0x10D6FEB0
// FUNCTION: ENGINE 0x10D6FEC0
// FUNCTION: ENGINE 0x10D6FED0
// FUNCTION: ENGINE 0x10D6FEE0
// FUNCTION: ENGINE 0x10D6FEF0
// FUNCTION: ENGINE 0x10D6FF00
// FUNCTION: ENGINE 0x10D6FF10
// FUNCTION: ENGINE 0x10D6FF20
// FUNCTION: ENGINE 0x10D6FF30
// FUNCTION: ENGINE 0x10D6FF40
// FUNCTION: ENGINE 0x10D6FF50
// FUNCTION: ENGINE 0x10D6FF60
// FUNCTION: ENGINE 0x10D70300
// FUNCTION: ENGINE 0x10D70320
// FUNCTION: ENGINE 0x10D70330
// FUNCTION: ENGINE 0x10D70340
// FUNCTION: ENGINE 0x10D70350
// FUNCTION: ENGINE 0x10D70360
// FUNCTION: ENGINE 0x10D70370
// FUNCTION: ENGINE 0x10D70380
// FUNCTION: ENGINE 0x10D70390
// FUNCTION: ENGINE 0x10D703A0
// FUNCTION: ENGINE 0x10D703B0
// FUNCTION: ENGINE 0x10D703C0
// FUNCTION: ENGINE 0x10D703D0
// FUNCTION: ENGINE 0x10D703E0
// FUNCTION: ENGINE 0x10D703F0
// FUNCTION: ENGINE 0x10D70400
// FUNCTION: ENGINE 0x10D70410
// FUNCTION: ENGINE 0x10D70420
// FUNCTION: ENGINE 0x10D70430
// FUNCTION: ENGINE 0x10D70440
// FUNCTION: ENGINE 0x10D70450
// FUNCTION: ENGINE 0x10D70460
// FUNCTION: ENGINE 0x10D70470
// FUNCTION: ENGINE 0x10D70480
// FUNCTION: ENGINE 0x10D70490
// FUNCTION: ENGINE 0x10D704A0
// FUNCTION: ENGINE 0x10D704B0
// FUNCTION: ENGINE 0x10D704C0
// FUNCTION: ENGINE 0x10D704D0
// FUNCTION: ENGINE 0x10D704E0
// FUNCTION: ENGINE 0x10D704F0
// FUNCTION: ENGINE 0x10D70500
// FUNCTION: ENGINE 0x10D70510
// FUNCTION: ENGINE 0x10D70520
// FUNCTION: ENGINE 0x10D70530
// FUNCTION: ENGINE 0x10D70540
// FUNCTION: ENGINE 0x10D70550
// FUNCTION: ENGINE 0x10D70560
// FUNCTION: ENGINE 0x10D70570
// FUNCTION: ENGINE 0x10D70580
// FUNCTION: ENGINE 0x10D70590
// FUNCTION: ENGINE 0x10D705A0
// FUNCTION: ENGINE 0x10D705B0
// FUNCTION: ENGINE 0x10D705C0
// FUNCTION: ENGINE 0x10D705D0
// FUNCTION: ENGINE 0x10D705E0
// FUNCTION: ENGINE 0x10D705F0
// FUNCTION: ENGINE 0x10D70600
// FUNCTION: ENGINE 0x10D70610
// FUNCTION: ENGINE 0x10D70620
// FUNCTION: ENGINE 0x10D70630
// FUNCTION: ENGINE 0x10D70640
// FUNCTION: ENGINE 0x10D70650
// FUNCTION: ENGINE 0x10D70660
// FUNCTION: ENGINE 0x10D70670
// FUNCTION: ENGINE 0x10D70680
// FUNCTION: ENGINE 0x10D70690
// FUNCTION: ENGINE 0x10D706A0
// FUNCTION: ENGINE 0x10D706B0
// FUNCTION: ENGINE 0x10D706C0
// FUNCTION: ENGINE 0x10D706D0
// FUNCTION: ENGINE 0x10D706E0
// FUNCTION: ENGINE 0x10D706F0
// FUNCTION: ENGINE 0x10D70700
// FUNCTION: ENGINE 0x10D70710
// FUNCTION: ENGINE 0x10D70720
// FUNCTION: ENGINE 0x10D70730
// FUNCTION: ENGINE 0x10D70740
// FUNCTION: ENGINE 0x10D70750
// FUNCTION: ENGINE 0x10D70760
// FUNCTION: ENGINE 0x10D70770
// FUNCTION: ENGINE 0x10D70780
// FUNCTION: ENGINE 0x10D70790
// FUNCTION: ENGINE 0x10D707A0
// FUNCTION: ENGINE 0x10D70990
// FUNCTION: ENGINE 0x10D709B0
// FUNCTION: ENGINE 0x10D709C0
// FUNCTION: ENGINE 0x10D709D0
// FUNCTION: ENGINE 0x10D709E0
// FUNCTION: ENGINE 0x10D709F0
// FUNCTION: ENGINE 0x10D70A00
// FUNCTION: ENGINE 0x10D70A10
// FUNCTION: ENGINE 0x10D70A20
// FUNCTION: ENGINE 0x10D70A30
// FUNCTION: ENGINE 0x10D70A40
// FUNCTION: ENGINE 0x10D70A50
// FUNCTION: ENGINE 0x10D70A60
// FUNCTION: ENGINE 0x10D70A70
// FUNCTION: ENGINE 0x10D70A80
// FUNCTION: ENGINE 0x10D70A90
// FUNCTION: ENGINE 0x10D70AA0
// FUNCTION: ENGINE 0x10D70AB0
// FUNCTION: ENGINE 0x10D70AC0
// FUNCTION: ENGINE 0x10D70AD0
// FUNCTION: ENGINE 0x10D70AE0
// FUNCTION: ENGINE 0x10D70AF0
// FUNCTION: ENGINE 0x10D70B00
// FUNCTION: ENGINE 0x10D70B10
// FUNCTION: ENGINE 0x10D70B20
// FUNCTION: ENGINE 0x10D70B30
// FUNCTION: ENGINE 0x10D70B40
// FUNCTION: ENGINE 0x10D70B50
// FUNCTION: ENGINE 0x10D70B60
// FUNCTION: ENGINE 0x10D70B70
// FUNCTION: ENGINE 0x10D70B80
// FUNCTION: ENGINE 0x10D70B90
// FUNCTION: ENGINE 0x10D70BA0
// FUNCTION: ENGINE 0x10D70BB0
// FUNCTION: ENGINE 0x10D70BC0
// FUNCTION: ENGINE 0x10D70BD0
// FUNCTION: ENGINE 0x10D70BE0
// FUNCTION: ENGINE 0x10D70BF0
// FUNCTION: ENGINE 0x10D70C00
// FUNCTION: ENGINE 0x10D70C10
// FUNCTION: ENGINE 0x10D70C20
// FUNCTION: ENGINE 0x10D70C30
// FUNCTION: ENGINE 0x10D70C40
// FUNCTION: ENGINE 0x10D70C50
// FUNCTION: ENGINE 0x10D70C60
// FUNCTION: ENGINE 0x10D70C70
// FUNCTION: ENGINE 0x10D70C80
// FUNCTION: ENGINE 0x10D70C90
// FUNCTION: ENGINE 0x10D70CA0
// FUNCTION: ENGINE 0x10D70CB0
// FUNCTION: ENGINE 0x10D70CC0
// FUNCTION: ENGINE 0x10D70CD0
// FUNCTION: ENGINE 0x10D70CE0
// FUNCTION: ENGINE 0x10D70CF0
// FUNCTION: ENGINE 0x10D70D00
// FUNCTION: ENGINE 0x10D70D10
// FUNCTION: ENGINE 0x10D70D20
// FUNCTION: ENGINE 0x10D70D30
// FUNCTION: ENGINE 0x10D70D40
// FUNCTION: ENGINE 0x10D70D50
// FUNCTION: ENGINE 0x10D70D60
// FUNCTION: ENGINE 0x10D70D70
// FUNCTION: ENGINE 0x10D70D90
// FUNCTION: ENGINE 0x10D70DA0
// FUNCTION: ENGINE 0x10D70DB0
// FUNCTION: ENGINE 0x10D70DC0
// FUNCTION: ENGINE 0x10D70DD0
// FUNCTION: ENGINE 0x10D70DE0
// FUNCTION: ENGINE 0x10D70DF0
// FUNCTION: ENGINE 0x10D70E00
// FUNCTION: ENGINE 0x10D70E10
// FUNCTION: ENGINE 0x10D70E20
// FUNCTION: ENGINE 0x10D70E30
// FUNCTION: ENGINE 0x10D70E40
// FUNCTION: ENGINE 0x10D70E50
// FUNCTION: ENGINE 0x10D70E60
// FUNCTION: ENGINE 0x10D70E70
// FUNCTION: ENGINE 0x10D70E80
// FUNCTION: ENGINE 0x10D70E90
// FUNCTION: ENGINE 0x10D70EA0
// FUNCTION: ENGINE 0x10D70EB0
// FUNCTION: ENGINE 0x10D70EC0
// FUNCTION: ENGINE 0x10D70ED0
// FUNCTION: ENGINE 0x10D70EE0
// FUNCTION: ENGINE 0x10D70EF0
// FUNCTION: ENGINE 0x10D70F00
// FUNCTION: ENGINE 0x10D70F10
// FUNCTION: ENGINE 0x10D70F20
// FUNCTION: ENGINE 0x10D70F30
// FUNCTION: ENGINE 0x10D70F40
// FUNCTION: ENGINE 0x10D70F50
// FUNCTION: ENGINE 0x10D70F60
// FUNCTION: ENGINE 0x10D70F70
// FUNCTION: ENGINE 0x10D70F80
// FUNCTION: ENGINE 0x10D70F90
// FUNCTION: ENGINE 0x10D70FA0
// FUNCTION: ENGINE 0x10D70FB0
// FUNCTION: ENGINE 0x10D71610
// FUNCTION: ENGINE 0x10D71620
// FUNCTION: ENGINE 0x10D71630
// FUNCTION: ENGINE 0x10D71640
// FUNCTION: ENGINE 0x10D71650
// FUNCTION: ENGINE 0x10D71660
// FUNCTION: ENGINE 0x10D86D50
// FUNCTION: ENGINE 0x10D86D60
// FUNCTION: ENGINE 0x10D86D70
// FUNCTION: ENGINE 0x10D86D80
// FUNCTION: ENGINE 0x10D86DA0
// FUNCTION: ENGINE 0x10D86DB0
// FUNCTION: ENGINE 0x10D86DD0
// FUNCTION: ENGINE 0x10D86DF0
// FUNCTION: ENGINE 0x10D86E10
// FUNCTION: ENGINE 0x10D86E20
// FUNCTION: ENGINE 0x10D86E30
// FUNCTION: ENGINE 0x10D86E50
// FUNCTION: ENGINE 0x10D86E60
// FUNCTION: ENGINE 0x10D86E70
// FUNCTION: ENGINE 0x10D86EC0
// FUNCTION: ENGINE 0x10D86EE0
// FUNCTION: ENGINE 0x10D86EF0
// FUNCTION: ENGINE 0x10D86F60
// FUNCTION: ENGINE 0x10D86F70
// FUNCTION: ENGINE 0x10D86F80
// FUNCTION: ENGINE 0x10D86F90
// FUNCTION: ENGINE 0x10D86FA0
// FUNCTION: ENGINE 0x10D86FB0
// FUNCTION: ENGINE 0x10D86FC0
// FUNCTION: ENGINE 0x10D86FF0
// FUNCTION: ENGINE 0x10D870A0
// FUNCTION: ENGINE 0x10D870B0
// FUNCTION: ENGINE 0x10D870C0
// FUNCTION: ENGINE 0x10D870D0
// FUNCTION: ENGINE 0x10D87120
// FUNCTION: ENGINE 0x10D87140
// FUNCTION: ENGINE 0x10D87150
// FUNCTION: ENGINE 0x10D871C0
// FUNCTION: ENGINE 0x10D871D0
// FUNCTION: ENGINE 0x10D87210
// FUNCTION: ENGINE 0x10D87250
// FUNCTION: ENGINE 0x10D87290
// FUNCTION: ENGINE 0x10D872C0
// FUNCTION: ENGINE 0x10D872D0
// FUNCTION: ENGINE 0x10D872E0
// FUNCTION: ENGINE 0x10D872F0
// FUNCTION: ENGINE 0x10D87300
// FUNCTION: ENGINE 0x10D87310
// FUNCTION: ENGINE 0x10D87320
// FUNCTION: ENGINE 0x10D87330
// FUNCTION: ENGINE 0x10D87340
// FUNCTION: ENGINE 0x10D87350
// FUNCTION: ENGINE 0x10D87360
// FUNCTION: ENGINE 0x10D87370
// FUNCTION: ENGINE 0x10D87380
// FUNCTION: ENGINE 0x10D87390
// FUNCTION: ENGINE 0x10D873A0
// FUNCTION: ENGINE 0x10D873B0
// FUNCTION: ENGINE 0x10D873C0
// FUNCTION: ENGINE 0x10D873D0
// FUNCTION: ENGINE 0x10D873E0
// FUNCTION: ENGINE 0x10D873F0
// FUNCTION: ENGINE 0x10D87400
// FUNCTION: ENGINE 0x10D87410
// FUNCTION: ENGINE 0x10D87420
// FUNCTION: ENGINE 0x10D87430
// FUNCTION: ENGINE 0x10D87440
// FUNCTION: ENGINE 0x10D87460
// FUNCTION: ENGINE 0x10D87470
// FUNCTION: ENGINE 0x10D87480
// FUNCTION: ENGINE 0x10D87490
// FUNCTION: ENGINE 0x10D874A0
// FUNCTION: ENGINE 0x10D874B0
// FUNCTION: ENGINE 0x10D874C0
// FUNCTION: ENGINE 0x10D874D0
// FUNCTION: ENGINE 0x10D874E0
// FUNCTION: ENGINE 0x10D874F0
// FUNCTION: ENGINE 0x10D87500
// FUNCTION: ENGINE 0x10D87510
// FUNCTION: ENGINE 0x10D87520
// FUNCTION: ENGINE 0x10D87530
// FUNCTION: ENGINE 0x10D87540
// FUNCTION: ENGINE 0x10D87550
// FUNCTION: ENGINE 0x10D87560
// FUNCTION: ENGINE 0x10D87570
// FUNCTION: ENGINE 0x10D87580
// FUNCTION: ENGINE 0x10D87590
// FUNCTION: ENGINE 0x10D875A0
// FUNCTION: ENGINE 0x10D875B0
// FUNCTION: ENGINE 0x10D875C0
// FUNCTION: ENGINE 0x10D875D0
// FUNCTION: ENGINE 0x10D875E0
// FUNCTION: ENGINE 0x10D875F0
// FUNCTION: ENGINE 0x10D87600
// FUNCTION: ENGINE 0x10D87610
// FUNCTION: ENGINE 0x10D87620
// FUNCTION: ENGINE 0x10D87630
// FUNCTION: ENGINE 0x10D87640
// FUNCTION: ENGINE 0x10D87650
// FUNCTION: ENGINE 0x10D87660
// FUNCTION: ENGINE 0x10D87670
// FUNCTION: ENGINE 0x10D87680
// FUNCTION: ENGINE 0x10D876A0
// FUNCTION: ENGINE 0x10D876B0
// FUNCTION: ENGINE 0x10D876C0
// FUNCTION: ENGINE 0x10D876D0
// FUNCTION: ENGINE 0x10D876E0
// FUNCTION: ENGINE 0x10D876F0
// FUNCTION: ENGINE 0x10D87700
// FUNCTION: ENGINE 0x10D87710
// FUNCTION: ENGINE 0x10D87720
// FUNCTION: ENGINE 0x10D87730
// FUNCTION: ENGINE 0x10D87740
// FUNCTION: ENGINE 0x10D87750
// FUNCTION: ENGINE 0x10D87760
// FUNCTION: ENGINE 0x10D87770
// FUNCTION: ENGINE 0x10D87780
// FUNCTION: ENGINE 0x10D87790
// FUNCTION: ENGINE 0x10D877A0
// FUNCTION: ENGINE 0x10D877B0
// FUNCTION: ENGINE 0x10D877C0
// FUNCTION: ENGINE 0x10D877D0
// FUNCTION: ENGINE 0x10D877E0
// FUNCTION: ENGINE 0x10D877F0
// FUNCTION: ENGINE 0x10D87800
// FUNCTION: ENGINE 0x10D87810
// FUNCTION: ENGINE 0x10D87820
// FUNCTION: ENGINE 0x10D87830
// FUNCTION: ENGINE 0x10D87840
// FUNCTION: ENGINE 0x10D87850
// FUNCTION: ENGINE 0x10D87860
// FUNCTION: ENGINE 0x10D87870
// FUNCTION: ENGINE 0x10D87880
// FUNCTION: ENGINE 0x10D87890
// FUNCTION: ENGINE 0x10D878A0
// FUNCTION: ENGINE 0x10D878B0
// FUNCTION: ENGINE 0x10D878C0
// FUNCTION: ENGINE 0x10D878D0
// FUNCTION: ENGINE 0x10D878E0
// FUNCTION: ENGINE 0x10D878F0
// FUNCTION: ENGINE 0x10D87900
// FUNCTION: ENGINE 0x10D87910
// FUNCTION: ENGINE 0x10D87920
// FUNCTION: ENGINE 0x10D87930
// FUNCTION: ENGINE 0x10D87940
// FUNCTION: ENGINE 0x10D87950
// FUNCTION: ENGINE 0x10D87960
// FUNCTION: ENGINE 0x10D87970
// FUNCTION: ENGINE 0x10D87980
// FUNCTION: ENGINE 0x10D87990
// FUNCTION: ENGINE 0x10D879A0
// FUNCTION: ENGINE 0x10D879B0
// FUNCTION: ENGINE 0x10D879C0
// FUNCTION: ENGINE 0x10D879D0
// FUNCTION: ENGINE 0x10D879E0
// FUNCTION: ENGINE 0x10D879F0
// FUNCTION: ENGINE 0x10D87A00
// FUNCTION: ENGINE 0x10D87A10
// FUNCTION: ENGINE 0x10D87A20
// FUNCTION: ENGINE 0x10D87A30
// FUNCTION: ENGINE 0x10D87A40
// FUNCTION: ENGINE 0x10D87A50
// FUNCTION: ENGINE 0x10D87A60
// FUNCTION: ENGINE 0x10D87A70
// FUNCTION: ENGINE 0x10D87A80
// FUNCTION: ENGINE 0x10D87A90
// FUNCTION: ENGINE 0x10D87AA0
// FUNCTION: ENGINE 0x10D87AB0
// FUNCTION: ENGINE 0x10D87AC0
// FUNCTION: ENGINE 0x10D87AD0
// FUNCTION: ENGINE 0x10D87AE0
// FUNCTION: ENGINE 0x10D87AF0
// FUNCTION: ENGINE 0x10D87B00
// FUNCTION: ENGINE 0x10D87B10
// FUNCTION: ENGINE 0x10D87B20
// FUNCTION: ENGINE 0x10D87B30
// FUNCTION: ENGINE 0x10D87B40
// FUNCTION: ENGINE 0x10D87B50
// FUNCTION: ENGINE 0x10D87B60
// FUNCTION: ENGINE 0x10D87B70
// FUNCTION: ENGINE 0x10D87B80
// FUNCTION: ENGINE 0x10D87B90
// FUNCTION: ENGINE 0x10D87BA0
// FUNCTION: ENGINE 0x10D87BB0
// FUNCTION: ENGINE 0x10D87BC0
// FUNCTION: ENGINE 0x10D87BD0
// FUNCTION: ENGINE 0x10D87BE0
// FUNCTION: ENGINE 0x10D87BF0
// FUNCTION: ENGINE 0x10D87C00
// FUNCTION: ENGINE 0x10D87C10
// FUNCTION: ENGINE 0x10D87C20
// FUNCTION: ENGINE 0x10D87C30
// FUNCTION: ENGINE 0x10D87C40
// FUNCTION: ENGINE 0x10D87C50
// FUNCTION: ENGINE 0x10D87C60
// FUNCTION: ENGINE 0x10D87C70
// FUNCTION: ENGINE 0x10D87C80
// FUNCTION: ENGINE 0x10D87C90
// FUNCTION: ENGINE 0x10D87CA0
// FUNCTION: ENGINE 0x10D87CB0
// FUNCTION: ENGINE 0x10D87CC0
// FUNCTION: ENGINE 0x10D87CD0
// FUNCTION: ENGINE 0x10D87CE0
// FUNCTION: ENGINE 0x10D87CF0
// FUNCTION: ENGINE 0x10D87D00
// FUNCTION: ENGINE 0x10D87D10
// FUNCTION: ENGINE 0x10D87D20
// FUNCTION: ENGINE 0x10D87D30
// FUNCTION: ENGINE 0x10D87D40
// FUNCTION: ENGINE 0x10D87D50
// FUNCTION: ENGINE 0x10D87D60
// FUNCTION: ENGINE 0x10D87D70
// FUNCTION: ENGINE 0x10D87D80
// FUNCTION: ENGINE 0x10D87D90
// FUNCTION: ENGINE 0x10D87DA0
// FUNCTION: ENGINE 0x10D87DB0
// FUNCTION: ENGINE 0x10D87DC0
// FUNCTION: ENGINE 0x10D87DD0
// FUNCTION: ENGINE 0x10D87DE0
// FUNCTION: ENGINE 0x10D87DF0
// FUNCTION: ENGINE 0x10D87E00
// FUNCTION: ENGINE 0x10D87E10
// FUNCTION: ENGINE 0x10D87E20
// FUNCTION: ENGINE 0x10D87E30
// FUNCTION: ENGINE 0x10D87E40
// FUNCTION: ENGINE 0x10D87E50
// FUNCTION: ENGINE 0x10D87E60
// FUNCTION: ENGINE 0x10D87E70
// FUNCTION: ENGINE 0x10D87E80
// FUNCTION: ENGINE 0x10D87E90
// FUNCTION: ENGINE 0x10D87EA0
// FUNCTION: ENGINE 0x10D87EB0
// FUNCTION: ENGINE 0x10D87EC0
// FUNCTION: ENGINE 0x10D87ED0
// FUNCTION: ENGINE 0x10D87EE0
// FUNCTION: ENGINE 0x10D87EF0
// FUNCTION: ENGINE 0x10D87F00
// FUNCTION: ENGINE 0x10D87F10
// FUNCTION: ENGINE 0x10D87F20
// FUNCTION: ENGINE 0x10D87F30
// FUNCTION: ENGINE 0x10D87F40
// FUNCTION: ENGINE 0x10D87F50
// FUNCTION: ENGINE 0x10D87F60
// FUNCTION: ENGINE 0x10D87F70
// FUNCTION: ENGINE 0x10D87F80
// FUNCTION: ENGINE 0x10D87F90
// FUNCTION: ENGINE 0x10D87FA0
// FUNCTION: ENGINE 0x10D87FB0
// FUNCTION: ENGINE 0x10D87FC0
// FUNCTION: ENGINE 0x10D87FD0
// FUNCTION: ENGINE 0x10D87FE0
// FUNCTION: ENGINE 0x10D87FF0
// FUNCTION: ENGINE 0x10D88000
// FUNCTION: ENGINE 0x10D88010
// FUNCTION: ENGINE 0x10D88020
// FUNCTION: ENGINE 0x10D88030
// FUNCTION: ENGINE 0x10D88040
// FUNCTION: ENGINE 0x10D88050
// FUNCTION: ENGINE 0x10D88060
// FUNCTION: ENGINE 0x10D88070
// FUNCTION: ENGINE 0x10D88080
// FUNCTION: ENGINE 0x10D88090
// FUNCTION: ENGINE 0x10D880A0
// FUNCTION: ENGINE 0x10D880B0
// FUNCTION: ENGINE 0x10D880C0
// FUNCTION: ENGINE 0x10D880D0
// FUNCTION: ENGINE 0x10D880E0
// FUNCTION: ENGINE 0x10D880F0
// FUNCTION: ENGINE 0x10D88100
// FUNCTION: ENGINE 0x10D88110
// FUNCTION: ENGINE 0x10D88120
// FUNCTION: ENGINE 0x10D88130
// FUNCTION: ENGINE 0x10D88140
// FUNCTION: ENGINE 0x10D88150
// FUNCTION: ENGINE 0x10D88160
// FUNCTION: ENGINE 0x10D88170
// FUNCTION: ENGINE 0x10D88180
// FUNCTION: ENGINE 0x10D88190
// FUNCTION: ENGINE 0x10D881A0
// FUNCTION: ENGINE 0x10D881B0
// FUNCTION: ENGINE 0x10D881C0
// FUNCTION: ENGINE 0x10D881D0
// FUNCTION: ENGINE 0x10D881E0
// FUNCTION: ENGINE 0x10D881F0
// FUNCTION: ENGINE 0x10D88200
// FUNCTION: ENGINE 0x10D88210
// FUNCTION: ENGINE 0x10D88220
// FUNCTION: ENGINE 0x10D88230
// FUNCTION: ENGINE 0x10D88240
// FUNCTION: ENGINE 0x10D88250
// FUNCTION: ENGINE 0x10D88260
// FUNCTION: ENGINE 0x10D88270
// FUNCTION: ENGINE 0x10D88280
// FUNCTION: ENGINE 0x10D88290
// FUNCTION: ENGINE 0x10D882A0
// FUNCTION: ENGINE 0x10D882B0
// FUNCTION: ENGINE 0x10D882C0
// FUNCTION: ENGINE 0x10D882D0
// FUNCTION: ENGINE 0x10D882E0
// FUNCTION: ENGINE 0x10D882F0
// FUNCTION: ENGINE 0x10D88300
// FUNCTION: ENGINE 0x10D88310
// FUNCTION: ENGINE 0x10D88320
// FUNCTION: ENGINE 0x10D88330
// FUNCTION: ENGINE 0x10D88340
// FUNCTION: ENGINE 0x10D88350
// FUNCTION: ENGINE 0x10D88360
// FUNCTION: ENGINE 0x10D88370
// FUNCTION: ENGINE 0x10D88380
// FUNCTION: ENGINE 0x10D88390
// FUNCTION: ENGINE 0x10D883A0
// FUNCTION: ENGINE 0x10D883B0
// FUNCTION: ENGINE 0x10D883C0
// FUNCTION: ENGINE 0x10D883D0
// FUNCTION: ENGINE 0x10D883E0
// FUNCTION: ENGINE 0x10D883F0
// FUNCTION: ENGINE 0x10D88400
// FUNCTION: ENGINE 0x10D88410
// FUNCTION: ENGINE 0x10D88420
// FUNCTION: ENGINE 0x10D88430
// FUNCTION: ENGINE 0x10D88440
// FUNCTION: ENGINE 0x10D88450
// FUNCTION: ENGINE 0x10D88460
// FUNCTION: ENGINE 0x10D88470
// FUNCTION: ENGINE 0x10D88480
// FUNCTION: ENGINE 0x10D88490
// FUNCTION: ENGINE 0x10D884A0
// FUNCTION: ENGINE 0x10D884B0
// FUNCTION: ENGINE 0x10D884C0
// FUNCTION: ENGINE 0x10D884D0
// FUNCTION: ENGINE 0x10D884E0
// FUNCTION: ENGINE 0x10D884F0
// FUNCTION: ENGINE 0x10D88500
// FUNCTION: ENGINE 0x10D88510
// FUNCTION: ENGINE 0x10D88520
// FUNCTION: ENGINE 0x10D88530
// FUNCTION: ENGINE 0x10D88540
// FUNCTION: ENGINE 0x10D88550
// FUNCTION: ENGINE 0x10D88560
// FUNCTION: ENGINE 0x10D88570
// FUNCTION: ENGINE 0x10D88580
// FUNCTION: ENGINE 0x10D88590
// FUNCTION: ENGINE 0x10D885A0
// FUNCTION: ENGINE 0x10D885B0
// FUNCTION: ENGINE 0x10D885C0
// FUNCTION: ENGINE 0x10D885D0
// FUNCTION: ENGINE 0x10D885E0
// FUNCTION: ENGINE 0x10D885F0
// FUNCTION: ENGINE 0x10D88600
// FUNCTION: ENGINE 0x10D88610
// FUNCTION: ENGINE 0x10D88620
// FUNCTION: ENGINE 0x10D88630
// FUNCTION: ENGINE 0x10D88640
// FUNCTION: ENGINE 0x10D88650
// FUNCTION: ENGINE 0x10D88660
// FUNCTION: ENGINE 0x10D88670
// FUNCTION: ENGINE 0x10D88680
// FUNCTION: ENGINE 0x10D88690
// FUNCTION: ENGINE 0x10D886A0
// FUNCTION: ENGINE 0x10D886B0
// FUNCTION: ENGINE 0x10D886C0
// FUNCTION: ENGINE 0x10D886D0
// FUNCTION: ENGINE 0x10D886E0
// FUNCTION: ENGINE 0x10D886F0
// FUNCTION: ENGINE 0x10D88700
// FUNCTION: ENGINE 0x10D88710
// FUNCTION: ENGINE 0x10D88720
// FUNCTION: ENGINE 0x10D88730
// FUNCTION: ENGINE 0x10D88740
// FUNCTION: ENGINE 0x10D88750
// FUNCTION: ENGINE 0x10D88760
// FUNCTION: ENGINE 0x10D88770
// FUNCTION: ENGINE 0x10D88780
// FUNCTION: ENGINE 0x10D88790
// FUNCTION: ENGINE 0x10D887A0
// FUNCTION: ENGINE 0x10D887B0
// FUNCTION: ENGINE 0x10D887C0
// FUNCTION: ENGINE 0x10D887D0
// FUNCTION: ENGINE 0x10D887E0
// FUNCTION: ENGINE 0x10D887F0
// FUNCTION: ENGINE 0x10D88800
// FUNCTION: ENGINE 0x10D88810
// FUNCTION: ENGINE 0x10D88820
// FUNCTION: ENGINE 0x10D88830
// FUNCTION: ENGINE 0x10D88840
// FUNCTION: ENGINE 0x10D88850
// FUNCTION: ENGINE 0x10D88860
// FUNCTION: ENGINE 0x10D88870
// FUNCTION: ENGINE 0x10D88880
// FUNCTION: ENGINE 0x10D88890
// FUNCTION: ENGINE 0x10D888A0
// FUNCTION: ENGINE 0x10D888B0
// FUNCTION: ENGINE 0x10D888C0
// FUNCTION: ENGINE 0x10D888D0
// FUNCTION: ENGINE 0x10D888E0
// FUNCTION: ENGINE 0x10D888F0
// FUNCTION: ENGINE 0x10D88900
// FUNCTION: ENGINE 0x10D88910
// FUNCTION: ENGINE 0x10D88920
// FUNCTION: ENGINE 0x10D88930
// FUNCTION: ENGINE 0x10D88940
// FUNCTION: ENGINE 0x10D88950
// FUNCTION: ENGINE 0x10D88960
// FUNCTION: ENGINE 0x10D88970
// FUNCTION: ENGINE 0x10D88980
// FUNCTION: ENGINE 0x10D88990
// FUNCTION: ENGINE 0x10D889A0
// FUNCTION: ENGINE 0x10D889B0
// FUNCTION: ENGINE 0x10D889C0
// FUNCTION: ENGINE 0x10D889D0
// FUNCTION: ENGINE 0x10D889E0
// FUNCTION: ENGINE 0x10D889F0
// FUNCTION: ENGINE 0x10D88A00
// FUNCTION: ENGINE 0x10D88A10
// FUNCTION: ENGINE 0x10D88A20
// FUNCTION: ENGINE 0x10D88A30
// FUNCTION: ENGINE 0x10D88A40
// FUNCTION: ENGINE 0x10D88A50
// FUNCTION: ENGINE 0x10D88A60
// FUNCTION: ENGINE 0x10D88A70
// FUNCTION: ENGINE 0x10D88A80
// FUNCTION: ENGINE 0x10D88A90
// FUNCTION: ENGINE 0x10D88AA0
// FUNCTION: ENGINE 0x10D88AB0
// FUNCTION: ENGINE 0x10D88AC0
// FUNCTION: ENGINE 0x10D88AD0
// FUNCTION: ENGINE 0x10D88AE0
// FUNCTION: ENGINE 0x10D88AF0
// FUNCTION: ENGINE 0x10D88B00
// FUNCTION: ENGINE 0x10D88B10
// FUNCTION: ENGINE 0x10D88B20
// FUNCTION: ENGINE 0x10D88B30
// FUNCTION: ENGINE 0x10D88B40
// FUNCTION: ENGINE 0x10D88B50
// FUNCTION: ENGINE 0x10D88B60
// FUNCTION: ENGINE 0x10D88B70
// FUNCTION: ENGINE 0x10D88B80
// FUNCTION: ENGINE 0x10D88B90
// FUNCTION: ENGINE 0x10D88BA0
// FUNCTION: ENGINE 0x10D88BB0
// FUNCTION: ENGINE 0x10D88BC0
// FUNCTION: ENGINE 0x10D88BD0
// FUNCTION: ENGINE 0x10D88BE0
// FUNCTION: ENGINE 0x10D88BF0
// FUNCTION: ENGINE 0x10D88C00
// FUNCTION: ENGINE 0x10D88C10
// FUNCTION: ENGINE 0x10D88C20
// FUNCTION: ENGINE 0x10D88C30
// FUNCTION: ENGINE 0x10D88C40
// FUNCTION: ENGINE 0x10D88C50
// FUNCTION: ENGINE 0x10D88C60
// FUNCTION: ENGINE 0x10D88C70
// FUNCTION: ENGINE 0x10D88C80
// FUNCTION: ENGINE 0x10D88C90
// FUNCTION: ENGINE 0x10D88CA0
// FUNCTION: ENGINE 0x10D88CB0
// FUNCTION: ENGINE 0x10D88CC0
// FUNCTION: ENGINE 0x10D88CD0
// FUNCTION: ENGINE 0x10D88CE0
// FUNCTION: ENGINE 0x10D88CF0
// FUNCTION: ENGINE 0x10D88D00
// FUNCTION: ENGINE 0x10D88D10
// FUNCTION: ENGINE 0x10D88D20
// FUNCTION: ENGINE 0x10D88D30
// FUNCTION: ENGINE 0x10D88D40
// FUNCTION: ENGINE 0x10D88D50
// FUNCTION: ENGINE 0x10D88D60
// FUNCTION: ENGINE 0x10D88D70
// FUNCTION: ENGINE 0x10D88D80
// FUNCTION: ENGINE 0x10D88D90
// FUNCTION: ENGINE 0x10D88DA0
