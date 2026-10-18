// The shader constants and shader names the render passes use. A constant is an index into the device's constant
// table (pddiBaseContext::constants), looked up once from the constant's name by the static initialisers
// (0x10D6C000 - 0x10D70000, bound by 0x106FC9D0 - 0x10701E80); the variables are named after the shader constant
// they hold, without the p3d prefix. A shader name is a core::Name made from the text in the comment.
#ifndef PURE3D_SHADERCONSTANTS_H
#define PURE3D_SHADERCONSTANTS_H

#include "code/core/name.h"

namespace pure3d
{
	// Shader names ("lit", "zfill", "shadowDepth", "lit_PR")
	extern core::Name<core::CaseInsensitiveKey32> gShaderLit; // 0x1127F220
	extern core::Name<core::CaseInsensitiveKey32> gShaderZFill; // 0x1127F24C
	extern core::Name<core::CaseInsensitiveKey32> gShaderShadowDepth; // 0x1127F1AC
	extern core::Name<core::CaseInsensitiveKey32> gShaderLitPR; // 0x11281758

	// Single floats, float pairs, vectors and flags
	extern int gConstantShaderLODGeo; // 0x11280A2C p3dShader_LODGeo
	extern int gConstantHalfPixel; // 0x112810EC p3dHalfPixel
	extern int gConstantTime; // 0x11281004 p3dTime
	extern int gConstantLightEnableSpotKill; // 0x11280FD4 p3dLight_EnableSpotKill
	extern int gConstantLightIsLitPass; // 0x11280D54 p3dLight_IsLitPass (a flag)
	extern int gConstantLightColour; // 0x11281094 p3dLight_Colour
	extern int gConstantLightAmbient; // 0x11280FEC p3dLight_Ambient
	extern int gConstantLightObjectSpaceLightBounds; // 0x11280F8C p3dLight_ObjectSpaceLightBounds
	extern int gConstantPRLightParams1; // 0x11280AE4 p3dPRLight_Params1
	extern int gConstantPRLightAmbient; // 0x11280AF4 p3dPRLight_Ambient
	extern int gConstantPRLightAmbientVertex; // 0x112811D4 p3dPRLight_Ambient_Vertex
	extern int gConstantPRLightColour1; // 0x11280BE0 p3dPRLight_Colour1
	extern int gConstantPRLightColour2; // 0x11280A64 p3dPRLight_Colour2
	extern int gConstantPRLightColour3; // 0x112811D0 p3dPRLight_Colour3
	extern int gConstantPRLightColour4; // 0x11280B98 p3dPRLight_Colour4
	extern int gConstantPRLightColour5; // 0x11280AFC p3dPRLight_Colour5
	extern int gConstantPRLightDirection1; // 0x11280D6C p3dPRLight_Direction1
	extern int gConstantPRLightDirection2; // 0x11280C64 p3dPRLight_Direction2
	extern int gConstantPRLightDirection3; // 0x1128114C p3dPRLight_Direction3
	extern int gConstantPRLightDirection4; // 0x11280B68 p3dPRLight_Direction4
	extern int gConstantPRLightDirection5; // 0x11280DC4 p3dPRLight_Direction5
	// The joint matrix of the part being drawn
	extern int gConstantProtoJointMatrix; // 0x11280A50 p3dProto_Joint_Matrix
	// Textures
	extern int gConstantDecalColourBuffer; // 0x11280B10 p3dDecalColourBuffer
	extern int gConstantDecalNormalBuffer; // 0x11280D70 p3dDecalNormalBuffer
	extern int gConstantShadowMap; // 0x11280BB8 p3dShadowMap
}

#endif
