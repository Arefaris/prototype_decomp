// pure3d::RenderOptions: the switches of a render (see the header). The file name is a guess.
#include "code/pure3d/renderoptions.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x1074DF40
	RenderOptions::RenderOptions()
	{
		enableLightsLOD = 0;
		enableShaderSorting = 0;
		showDebugLights = 0;
		showDebugLightsLOD = 0;
		showLightBoundingSphere = 0;
		showDebugOverlays = 1;
		showDebugPose = 0;
		showDrawableAABB = 0;
		showDrawableBoundingSphere = 0;
		showNormals = 0;
		showPrimitiveAABB = 0;
		showPrimitiveBoundingSphere = 0;
		showWireframeOverlay = 0;
		useDebugLights = 0;
		isInCapturePass = 0;
		enableOcclusionQueryConditionalRendering = 0;
		enableShaderLOD = 0;
	}

	// FUNCTION: ENGINE 0x1074DD40
	void RenderOptions::SetEnableShaderSorting(bool value)
	{
		enableShaderSorting = value;
	}

	// FUNCTION: ENGINE 0x1074DD60
	void RenderOptions::SetShowDebugLights(bool value)
	{
		showDebugLights = value;
	}

	// FUNCTION: ENGINE 0x1074DD80
	void RenderOptions::SetShowDebugLightsLOD(bool value)
	{
		showDebugLightsLOD = value;
	}

	// FUNCTION: ENGINE 0x1074DDA0
	void RenderOptions::SetShowLightBoundingSphere(bool value)
	{
		showLightBoundingSphere = value;
	}

	// FUNCTION: ENGINE 0x1074DDC0
	void RenderOptions::SetShowDebugOverlays(bool value)
	{
		showDebugOverlays = value;
	}

	// FUNCTION: ENGINE 0x1074DDE0
	void RenderOptions::SetShowDebugPose(bool value)
	{
		showDebugPose = value;
	}

	// FUNCTION: ENGINE 0x1074DE00
	void RenderOptions::SetShowDrawableAABB(bool value)
	{
		showDrawableAABB = value;
	}

	// FUNCTION: ENGINE 0x1074DE20
	void RenderOptions::SetShowDrawableBoundingSphere(bool value)
	{
		showDrawableBoundingSphere = value;
	}

	// FUNCTION: ENGINE 0x1074DE40
	void RenderOptions::SetShowNormals(bool value)
	{
		showNormals = value;
	}

	// FUNCTION: ENGINE 0x1074DE60
	void RenderOptions::SetShowPrimitiveAABB(bool value)
	{
		showPrimitiveAABB = value;
	}

	// FUNCTION: ENGINE 0x1074DE80
	void RenderOptions::SetShowPrimitiveBoundingSphere(bool value)
	{
		showPrimitiveBoundingSphere = value;
	}

	// FUNCTION: ENGINE 0x1074DEA0
	void RenderOptions::SetShowWireframeOverlay(bool value)
	{
		showWireframeOverlay = value;
	}

	// FUNCTION: ENGINE 0x1074DEC0
	void RenderOptions::SetUseDebugLights(bool value)
	{
		useDebugLights = value;
	}

	// FUNCTION: ENGINE 0x1074DEE0
	void RenderOptions::SetIsInCapturePass(bool value)
	{
		isInCapturePass = value;
	}

	// FUNCTION: ENGINE 0x1074DF00
	void RenderOptions::SetEnableOcclusionQueryConditionalRendering(bool value)
	{
		enableOcclusionQueryConditionalRendering = value;
	}

	// FUNCTION: ENGINE 0x1074DF20
	void RenderOptions::SetEnableShaderLOD(bool value)
	{
		enableShaderLOD = value;
	}
}
