// The lighting of pure3d (code/pure3d/lighting/lightingscene.cpp and the light units around it). Only what the
// reconstructed code uses; layouts partial, class and member names guessed.
#ifndef PURE3D_LIGHTING_H
#define PURE3D_LIGHTING_H

namespace pure3d
{
	class Light;

	// A growable array of lights (0x10756830 resizes it, filling new slots with fill)
	class LightArray
	{
	public:
		void Resize(unsigned int count, Light* const& fill);

		Light** begin;
		Light** end;
		Light** capacity;
	};

	// What picks the lights that touch a region (0x1060FE00 sorts and counts the given light indices)
	class LightQuery
	{
	public:
		unsigned int Select(unsigned int* indices, unsigned int count, int region);
	};

	// The lights of a lighting scene, selected by region
	class LightingScene
	{
	public:
		// 0x10756AA0: the lights the query selects for region, in its order
		void GetLights(LightArray* lights, int region);

		unsigned char unknown0[0x30];
		Light** lights;
		unsigned char unknown34[8];
		unsigned int* indicesBegin;
		unsigned int* indicesEnd;
		unsigned char unknown44[4];
		LightQuery query;
	};

	// A set of bits (the words at +8)
	struct LightBits
	{
		int unknown0;
		int unknown4;
		unsigned int* words;
	};

	// The bit ranges of the light groups: group i covers words first[i] ... first[i] + count[i] - 1
	struct LightGroups
	{
		unsigned char unknown0[0x94];
		unsigned int* first;
		unsigned char unknown98[8];
		unsigned int* count;
	};

	// 0x1075C750: out = a | b over the groups whose bit is set in groups (14 groups)
	void MergeLightBits(LightBits* out, const LightBits* a, const LightBits* b, const LightGroups* layout,
		unsigned int groups);

	// The lighting inputs of a pass (RTTI name pure3d::LightingInputs; one virtual function)
	class LightingInputs
	{
	public:
		virtual ~LightingInputs();

		// 0x107A6B10: the shader constant (enabled, unknown8, unknownC, 0); without unknown4 the middle pair is
		// (0, 1)
		void SetShaderConstant();

		bool unknown4;
		bool enabled;
		float unknown8;
		float unknownC;
	};

	// 0x11280A28: the index of the constant SetShaderConstant writes
	extern int gLightingInputsConstant;

	// The views and cameras a render pass uses (RTTI name pure3d::RenderParams; one virtual function)
	class RenderParams
	{
	public:
		virtual ~RenderParams();

		// 0x1074F3B0 / 0x1074F3C0: the view state (0x7C bytes each, from +0x78) and the camera data (0x140 bytes
		// each, at the pointer at +0x320) of a view
		void* GetViewState(int view);
		void* GetCameraData(int view);

		unsigned char unknown4[0x74];
		struct ViewState
		{
			unsigned char data[0x7C];
		} views[5];
		unsigned char unknown2E4[0x3C];
		struct CameraData
		{
			unsigned char data[0x140];
		}* cameras;
	};
}

#endif
