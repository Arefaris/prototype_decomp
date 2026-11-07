// pure3d::ProtoRenderScheme (unit around 0x10718DD0 - 0x1071A000; file name guessed from the class). Names are guesses.
#include "code/pure3d/postprocesspass.h"
#include "code/pure3d/protopass.h"
#include "code/pure3d/protorenderscheme.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10719390
	ViewPassDesc::ViewPassDesc(const void* name) : PassDesc(name, 1)
	{
		clearColour.bits = gViewClearColour;
		clearMask = 0xFFFFFFFF;
		viewLevel = 0;
		shadowView = true;
		unknown25 = true;
	}

	// FUNCTION: ENGINE 0x107191B0
	RootPass* ProtoRenderScheme::CreateRootPass(const RootPassConfig* config)
	{
		RootPass* newPass = new RootPass(config);
		if (!RegisterRootPass(newPass))
		{
			delete newPass;
			return 0;
		}
		return newPass;
	}
}

// The passes of the tree, one function each
// FUNCTION: ENGINE 0x10719680
template pure3d::ProtoShadowPass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ProtoShadowPass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719700
template pure3d::LetterBoxPass* pure3d::ProtoRenderScheme::CreatePass<pure3d::LetterBoxPass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719780
template pure3d::ViewPass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ViewPass, pure3d::ViewPassDesc>(
	const pure3d::ViewPassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719800
template pure3d::ProtoFogPass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ProtoFogPass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719880
template pure3d::ProtoLitRootPass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ProtoLitRootPass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719900
template pure3d::ProtoCapturePass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ProtoCapturePass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719980
template pure3d::ProtoZPass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ProtoZPass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719A00
template pure3d::ProtoDecalPass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ProtoDecalPass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719A80
template pure3d::ProtoLightDecalPass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ProtoLightDecalPass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719B00
template pure3d::ProtoOpaquePass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ProtoOpaquePass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719B80
template pure3d::ProtoMidgroundPass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ProtoMidgroundPass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719C00
template pure3d::ProtoWireframePass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ProtoWireframePass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719C80
template pure3d::ProtoBloodPass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ProtoBloodPass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719D00
template pure3d::ProtoShaderLODDebugPass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ProtoShaderLODDebugPass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719D80
template pure3d::ProtoTranslucentPass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ProtoTranslucentPass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719E00
template pure3d::ProtoRadialBlurPass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ProtoRadialBlurPass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719E80
template pure3d::DepthOfFieldPass* pure3d::ProtoRenderScheme::CreatePass<pure3d::DepthOfFieldPass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719F00
template pure3d::ProtoFBPass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ProtoFBPass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719F80
template pure3d::ProtoHUDPass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ProtoHUDPass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);
