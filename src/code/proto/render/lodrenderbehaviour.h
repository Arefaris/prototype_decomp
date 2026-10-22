// proto::LODRenderBehaviour (RTTI 0x11075320, vftable 0x10DEA9F4, base engine::Behaviour): the behaviour that picks
// which level of detail of a drawable set is drawn, fades between two levels and drives the drawables of the level it
// chose. File name, member names and the layout are guesses; the RTTI member getters name the reflected fields
// (a bool, a DrawableArchetype reference and a pure3d::Animation reference).
#ifndef PROTO_RENDER_LODRENDERBEHAVIOUR_H
#define PROTO_RENDER_LODRENDERBEHAVIOUR_H

#include "code/container/arraydynamic.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/render/async/drawable.h"
#include "code/math/aabb.h"
#include "code/math/vector.h"
#include "code/proto/shaders/shaderpalette.h"

namespace pure3d
{
	class Animation;
	class Camera;
	class Pose;

	// 0x10708DB0 (another unit): memory for the joint data of a skeleton of that many joints; size gets the bytes
	void* AllocateBoneData(unsigned int joints, int* size, int kinds);
}

namespace engine
{
	namespace render
	{
		// A drawable's source (the rest of the class is unknown): its bounding box sits at +0xC
		class SourceDrawable
		{
		public:
			// 0x10825930
			const math::AABB* GetBounds() const;

			unsigned char unknown0[0xC];
			math::AABB bounds;
		};
	}
}

namespace proto
{
	// A level's fade range: the distance its drawables start to fade in at, the distance they are fully faded at
	// and the rate the fade runs at (name guess; the table is 0x1107517C, three 12-byte records)
	struct LODRange
	{
		float minimum;
		float maximum;
		float rate;
	};

	// The three distances that decide which range an object is in (0x11075114; name guess)
	extern float gLODDistances[3];

	// The three records (name guess)
	extern LODRange gLODRanges[3];
	// 0x11075120: a multiplier on every level's fade distance (name guess)
	extern float gLODDistanceScale;

	// 0x11263108: the object the behaviour asks for the detail scale of the camera in view (name guess). The
	// engine's method (0x1032C430) reads the float at the object's +0x68 and, without a camera, the pointer chain
	// +0x14 / +0x40; only the method is needed here.
	class LODDetailScale
	{
	public:
		// 0x1032C430: the scale the camera asks for, 1 when it has none
		float GetScale(const pure3d::Camera* camera) const;
	};

	extern LODDetailScale* gLODDetailScale;

	// One level of the object: the drawable shown for it (8 bytes; the two words after the handle are unknown)
	struct LODLevel
	{
		// 0x102D9470: gives the drawable the shader inputs of one entry of the shader palette
		void ApplyPalette(ShaderPaletteData* data);

		engine::render::Drawable drawable;
		unsigned short unknown4;
		unsigned short unknown6;
	};

	// One drawable that is ready to be shown (0x10 bytes: the source the instance is made from, then unknown words)
	struct LODReady
	{
		engine::render::SourceDrawable* source;
		unsigned char unknown4[0xC];
	};

	// The objects the behaviour reads its pose and its scale from (their first word is unknown)
	struct LODPoseSource
	{
		int unknown0;
		pure3d::Pose* pose;
	};

	struct LODScaleSource
	{
		int unknown0;
		math::Vector scale;
	};

	class LODRenderBehaviour : public engine::Behaviour
	{
	public:
		// The vftable (0x10DEA9F4): slots 0 and 2 are the base's. The destructor is 0x102DCF80, the vftable holds its
		// scalar deleting copy 0x102DD0D0.
		// vftable slot 1: the first update, which picks the shader palette entry and shows the levels
		virtual void Slot1();
		virtual void OnActiveChanged(bool active);
		virtual void Update(float dt, unsigned short mask);
		virtual void OnPostedMessage(engine::Message* message);
		virtual void OnMessage(engine::Message* message);
		virtual ~LODRenderBehaviour();

		// 0x102DA3A0: hands the drawables of the level range over to the game object and queues the transform
		void ChangeDrawableLevels(unsigned int previous, const LODLevel* first, const LODLevel* last);
		// 0x102DA700: picks the level the fade position asks for and tells the drawables when it changes
		void UpdateLevel();
		// 0x102DA540: the fade of the level drawn, from the distance to the camera and the level's range
		void UpdateFade();
		// 0x102D99A0 / 0x102D9BF0: the fade in and the forced level, advanced by the time of the frame
		void UpdateFadeIn(float dt);
		void UpdateForced(float dt);
		// 0x102DB9F0: makes the level of a ready drawable and adds it to the table
		void AddLevel(const LODReady* ready);

		// +0x0C: the source of the pose handed to the drawables
		LODPoseSource* poseSource;
		// +0x10: the scale the drawables are given
		LODScaleSource* scaleSource;
		unsigned char unknown14[0x1C - 0x14];
		// +0x1C / +0x24: the first and the last level shown now (name guess)
		LODLevel* shownFirst;
		// +0x20 / +0x28: the ones shown before the level was forced (name guess)
		LODLevel* forcedFirst;
		LODLevel* shownLast;
		LODLevel* forcedLast;
		// +0x2C: the animation the drawables play (name guess)
		pure3d::Animation* animation;
		// +0x30: the shader palette the entries come from, +0x34 the entry's index in it (-1: none)
		ShaderPalette* available;
		int availableIndex;
		// +0x38: which of the three distance ranges (gLODDistances) the object is in
		unsigned int distanceLevel;
		// +0x3C: the smallest number of levels that is ever handed over
		unsigned int minimumLevels;
		// +0x40: the drawables that are ready (begin, end, capacity and the heap; empty: none)
		container::ArrayDynamicHeap<LODReady> ready;
		// +0x50: the level table (8-byte records; the engine's inline code tests it for emptiness and walks it by index)
		container::ArrayDynamicHeap<LODLevel> levels;
		// +0x60: the level drawn now (-1: none yet)
		unsigned int level;
		// +0x64: how far the fade between two levels has run (0 - 1)
		float fade;
		// +0x68: the fade of a forced level
		float forcedFade;
		// +0x6C / +0x70: the fade in position and its target (both 1 once it is done)
		float fadeInPosition;
		float fadeInTarget;
		unsigned char unknown74[4];
		// +0x78: a multiplier on this behaviour's fade distance
		float fadeScale;
		unsigned char unknown7C[0x90 - 0x7C];
		// +0x90: the heap of the bone data, +0x94 the data, +0x98 its size (names guessed)
		int heap;
		void* boneData;
		int boneDataSize;
		// +0x9C: bit 0 the drawables are bound, bit 2 the level was forced
		unsigned char flags;
	};
}

#endif
