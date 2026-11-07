// pure3d::RenderOptions (RTTI name, a struct; ParameterHandler<RenderOptions> registers its switches by the names the
// members carry): the switches of a render, one bit each in a single word. Member names are the parameter names.
#ifndef PURE3D_RENDEROPTIONS_H
#define PURE3D_RENDEROPTIONS_H

namespace pure3d
{
	struct RenderOptions
	{
		// 0x1074DF40: every switch off but the debug overlays
		RenderOptions();

		// 0x1074DD40 - 0x1074DF20 (the setter of the first switch is 0x1074DD30)
		void SetEnableShaderSorting(bool value);
		void SetShowDebugLights(bool value);
		void SetShowDebugLightsLOD(bool value);
		void SetShowLightBoundingSphere(bool value);
		void SetShowDebugOverlays(bool value);
		void SetShowDebugPose(bool value);
		void SetShowDrawableAABB(bool value);
		void SetShowDrawableBoundingSphere(bool value);
		void SetShowNormals(bool value);
		void SetShowPrimitiveAABB(bool value);
		void SetShowPrimitiveBoundingSphere(bool value);
		void SetShowWireframeOverlay(bool value);
		void SetUseDebugLights(bool value);
		void SetIsInCapturePass(bool value);
		void SetEnableOcclusionQueryConditionalRendering(bool value);
		void SetEnableShaderLOD(bool value);

		unsigned int enableLightsLOD : 1;
		unsigned int enableShaderSorting : 1;
		unsigned int showDebugLights : 1;
		unsigned int showDebugLightsLOD : 1;
		unsigned int showLightBoundingSphere : 1;
		unsigned int showDebugOverlays : 1;
		unsigned int showDebugPose : 1;
		unsigned int showDrawableAABB : 1;
		unsigned int showDrawableBoundingSphere : 1;
		unsigned int showNormals : 1;
		unsigned int showPrimitiveAABB : 1;
		unsigned int showPrimitiveBoundingSphere : 1;
		unsigned int showWireframeOverlay : 1;
		unsigned int useDebugLights : 1;
		unsigned int isInCapturePass : 1;
		unsigned int enableOcclusionQueryConditionalRendering : 1;
		unsigned int enableShaderLOD : 1;
		unsigned int unused : 15;
	};
}

#endif
