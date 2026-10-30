// The lighting of pure3d (code/pure3d/lighting/lightingscene.cpp and the light units around it). Only what the
// reconstructed code uses; layouts partial, class and member names guessed.
#ifndef PURE3D_LIGHTING_H
#define PURE3D_LIGHTING_H

#include "code/core/name.h"
#include "code/pure3d/entity.h"

namespace pure3d
{
	class Light;
	class LightingScene;

	// A growable array of lights (0x10756830 resizes it, filling new slots with fill)
	class LightArray
	{
	public:
		void Resize(unsigned int count, Light* const& fill);
		int Size() const
		{
			return end - begin;
		}

		Light** begin;
		Light** end;
		Light** capacity;
	};

	// What picks the lights that touch a region (0x1060FE00 expands the region's light mask into indices)
	class LightQuery
	{
	public:
		// region names a shared light bit set: the count of set light bits is its first word (the group count is
		// that >> 7). The count argument is not read.
		unsigned int Select(unsigned int* indices, unsigned int count, const unsigned int* region);
		// 0x1060FC30 (mapped, not reconstructed): copies the region's bit set into bits (its three words at
		// +0 / +4 / +8 are the caller's bit count, a spare word and the mask pointer)
		void SetRegionMask(unsigned int* bits, const unsigned int* region);

		unsigned char unknown0[0x3c];
		unsigned int bitCount;     // +0x3c: how many light bits the region has (the group count is this >> 7)
		unsigned int unknown40;    // +0x40
		unsigned int* mask;        // +0x44: the light mask words (128 bits per group)
	};

	// 0x1060F840: the indices of the set bits of the 128-bit groups of masks, in order
	unsigned int BuildLightIndices(unsigned int* out, unsigned int* masks, unsigned int count);

	// The named groups the scene's lights are filed in (the scene keeps it at +0xDC; the unit is 0x10757A00 -
	// 0x10758300, the names are guesses)
	class LightGroupTable
	{
	public:
		// 0x10758020 / 0x10758090: files the light under a group name / takes it out; false when there is no such
		// group
		bool Unknown10758020(const core::Name<core::CaseSensitiveKey>* name, Light* light);
		bool Unknown10758090(const core::Name<core::CaseSensitiveKey>* name, Light* light);
		// 0x10757A10: whether the light is in the scene's lists
		bool Contains(Light* light);
		// 0x10757AA0: how many lights the scene holds
		int GetLightCount();
		// 0x10757AC0: the group of that name (the last one found is tried first), null when there is none
		Entity* FindGroup(const core::Name<core::CaseSensitiveKey>* name);

		unsigned char unknown0[8];
		LightingScene* scene;
		unsigned char unknownC[0x14];
		Entity* groups[0x20];
	};

	// The lights of a lighting scene, selected by region
	class LightingScene
	{
	public:
		// 0x10756AA0: the lights the query selects for a region (the shared bit set), in its order
		void GetLights(LightArray* lights, const unsigned int* region);
		// 0x10756350: whether the light is in the scene's list
		bool Contains(Light* light);
		// 0x10757A80 / 0x10757A90: how many lights are in the first / the second list
		int GetBoundedCount();
		int GetUnboundedCount();
		// 0x10756890 / 0x10756500: takes a light into the scene / out of it (names guessed)
		void AddLight(Light* light);
		void RemoveLight(Light* light);

		unsigned char unknown0[8];
		// The lights with a decay range (the ones the visibility regions know) and the ones without; the light's
		// region index (0xFFFF for none) says which list holds it
		LightArray bounded;
		unsigned char unknown14[4];
		LightArray unbounded;
		unsigned char unknown24[0xC];
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

	// The light sets a light group object keeps (named by its pointer at +0x48): the sets that are merged
	struct LightSets
	{
		unsigned char unknown0[0x90];
		LightBits shared90;
		unsigned char unknown9C[0x54];
		LightBits merged0F0;
		unsigned char unknownFC[0x84];
		LightBits shared180;
	};

	// The bit ranges of the light groups: group i covers words first[i] ... first[i] + count[i] - 1
	struct LightGroups
	{
		unsigned char unknown0[0x48];
		LightSets* sets;
		unsigned char unknown4C[0x48];
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
		// 0x107A7400: takes the colour, position and direction of a light as the shader constants of the key light
		void SetLight(Light* light);
		// 0x107A8E20: takes the light's spot settings (the light may be null; hasShadow says whether the lit
		// passes sample a shadow map)
		void SetSpotLight(Light* light, bool hasShadow, int unknown);

		bool unknown4;
		bool enabled;
		float unknown8;
		float unknownC;
	};

	// 0x11280A28: the index of the constant SetShaderConstant writes
	extern int gLightingInputsConstant;

	// 0x11282AC0: the index of the group FindGroup found last (name guess)
	extern unsigned int gLastLightGroup;

	// The views and cameras a render pass uses (RTTI name pure3d::RenderParams; one virtual function)
	class RenderParams : public Entity
	{
	public:
		// 0x10751A00 (another unit): the context makes one per frame it can build (0x330 bytes)
		RenderParams();

		// 0x1074F3B0 / 0x1074F3C0: the view state (0x7C bytes each, from +0x78) and the camera data (0x140 bytes
		// each, at the pointer at +0x320) of a view
		void* GetViewState(int view);
		void* GetCameraData(int view);
		// 0x1074EE10: the word at +0x14 (1: the lit passes draw into the shadow map)
		int GetUnknown14();
		// 0x1074F290 (another unit): lays the frame's window over the views of the render parameters
		void Unknown1074F290();
		// The camera data are the light's shadow cascades: 0x1074ECE0 / 0x1074ED10 / 0x1074ED30 / 0x1074EE00 /
		// 0x1074EE50 / 0x1074F0C0 / 0x1074F110 / 0x1074F130 / 0x1074F4B0 (names unknown, the render thread's light
		// API calls them)
		void Unknown1074ECE0(float value);
		void Unknown1074ED10(float value);
		void Unknown1074ED30(int value);
		int Unknown1074EE00();
		float Unknown1074EE50();
		void Unknown1074F0C0(float value);
		void Unknown1074F110(unsigned int index, float value);
		float Unknown1074F130(unsigned int index);
		void Unknown1074F4B0(unsigned int count);

		int unknown10;
		int unknown14;
		unsigned char unknown18[0x1C];
		float unknown34;
		unsigned char unknown38[0x40];
		struct ViewState
		{
			unsigned char unknown0[0x10];
			// The name of the render context the view is drawn with, and the size of the picture
			core::Name<core::CaseSensitiveKey> contextName;
			int width;
			int height;
			unsigned char unknown20[0x5C];
		} views[5];
		unsigned char unknown2E4[0x18];
		float unknown2FC[6];
		float unknown314;
		float unknown318;
		float unknown31C;
		struct CameraData
		{
			unsigned char data[0x140];
		}* cameras;
		CameraData* camerasEnd;
		unsigned char unknown328[8];
	};
}

#endif
