// proto::LODRenderBehaviour (RTTI 0x11075320, vftable 0x10DEA9F4, base engine::Behaviour): the behaviour that picks
// which level of detail of a drawable set is drawn, fades between two levels and drives the drawables of the level it
// chose. File name, member names and the layout are guesses; the RTTI member getters name the reflected fields
// (a bool, a DrawableArchetype reference and a pure3d::Animation reference).
#ifndef PROTO_RENDER_LODRENDERBEHAVIOUR_H
#define PROTO_RENDER_LODRENDERBEHAVIOUR_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/arrayhelpercount.h"
#include "code/core/name.h"
#include "code/core/refptr.h"
#include "code/content/metatype.h"
#include "code/engine/render/drawablearchetype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/render/async/drawable.h"
#include "code/math/aabb.h"
#include "code/math/vector.h"
#include "code/proto/camera/cameramanager.h"
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

	// One level of the object: the drawable shown for it (8 bytes). The two counts say how many times the level is used as
	// the first and as the last one of the range that is shown (the level is on screen while either is not zero)
	struct LODLevel
	{
		// 0x102D9250 (a level of a drawable that is not used yet), 0x102D9980 (a copy), 0x102D9270 (the assignment)
		explicit LODLevel(engine::render::Drawable newDrawable);
		LODLevel(const LODLevel& other);
		LODLevel& operator=(const LODLevel& other);
		// 0x102D9450: lets the drawable go off the screen and forgets the uses
		void Hide();
		// 0x102D92A0: destroys the drawable
		void Destroy();
		// 0x102D92D0 / 0x102D93A0: a use as the first and/or as the last level of the range begins / ends; the drawable is
		// registered with the first use and unregistered with the last one
		void Acquire(bool asFirst, bool asLast);
		void Release(bool asFirst, bool asLast);
		// 0x102D9470: gives the drawable the shader inputs of one entry of the shader palette
		void ApplyPalette(ShaderPaletteData* data);

		engine::render::Drawable drawable;
		unsigned short firstUses;
		unsigned short lastUses;
	};

	// One level of detail as the content describes it (RTTI LODRenderData; reflected: "drawable", the archetype and the
	// name it was found by). 0x10 bytes: the archetype, a word the copies leave alone, the name
	struct LODRenderData
	{
		// 0x102D9870, 0x102DAB40 (a copy), 0x102DAB10 (the assignment: the archetype is taken without a reference), 0x102D9890
		LODRenderData() : source(0)
		{
		}
		explicit LODRenderData(core::IRefCount* newSource)
		{
			source = newSource;
		}
		LODRenderData(const LODRenderData& other);
		LODRenderData& operator=(const LODRenderData& other);
		~LODRenderData()
		{
			core::SafeRelease(source);
		}
		// 0x102D90A0 / 0x102D90B0 / 0x102D98A0: the reflected "drawable"
		engine::render::DrawableArchetype* GetArchetype() const;
		const content::ObjectName* GetArchetypeName() const;
		void SetArchetype(engine::render::DrawableArchetype* newArchetype, const content::ObjectName& newName);
		// The archetype as the drawable instances are made from it
		engine::render::SourceDrawable* GetSource() const
		{
			return (engine::render::SourceDrawable*)source;
		}
		// 0x102D91B0
		static content::ClassInfo* GetClassInfo();
		// 0x102DB940
		static content::MemberList* GetMembers();

		core::IRefCount* source;
		int unknown4;
		content::ObjectName name;
	};

	typedef container::ArrayDynamic<LODRenderData, container::AllocatorNew> LODRenderDataArray;

	// The objects the behaviour reads its pose and its scale from (their first word is unknown)
	struct LODPoseSource
	{
		int unknown0;
		pure3d::Pose* pose;
	};

	// The attribute that names the palette entry the object asks for (its first word is unknown)
	struct LODIndexSource
	{
		int unknown0;
		int value;
	};

	struct LODScaleSource
	{
		int unknown0;
		math::Vector scale;
	};

	class LODRenderBehaviour : public engine::Behaviour
	{
	public:
		// 0x102DCD20
		explicit LODRenderBehaviour(engine::GameObject* newOwner);
		// 0x102D91F0 (reflected as "LODRenderBehaviour")
		static content::ClassInfo* GetClassInfo();
		// 0x102DC390
		static content::MemberList* GetMembers();

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
		void AddLevel(const LODRenderData* data);
		// 0x102D9ED0 / 0x102DA090: the messages of type 8 and 10 are handed to every level's drawable
		void OnSegmentMessage(engine::Message* message);
		void OnPlaybackMessage(engine::Message* message);
		// 0x102DB2E0: an attribute of the object changed (the scale, the index of the palette entry)
		void OnAttributeUpdated(engine::Message* message);
		// 0x102D9B50: picks the palette entry from the attribute that asks for one (name guess)
		void PickPaletteEntry();
		// 0x102DB450: the drawables are bound or not (bit 0 of the flags)
		void SetBound(bool bound);
		// 0x102DB3B0: the drawables of a package go (the package named at +0x88 is not the empty one) or wait for it (bit 3)
		void ReleaseLevelsForPackage();
		// 0x102D9AB0: gives every level the shader inputs of one entry of the palette; 0x102D9B10: the entry that was picked
		void ApplyPaletteToLevels(ShaderPaletteData* data);
		void ApplyAvailablePalette();
		// 0x102DA7E0: lets the pose and the drawables of the levels go; 0x102DA850: puts every level off the screen and
		// forgets the range that is shown
		void DestroyLevels();
		void ResetLevels();
		// 0x102DA910
		void SetAnimation(pure3d::Animation* newAnimation);
		// The reflected members: "enableGeoLOD" 0x102D90E0 / 0x102DB450 (SetBound), "enableGeoFade" 0x102D90F0 / 0x102D94A0,
		// "drawableSource" 0x102D94C0 (always null) / 0x102D94D0 / 0x102DBF90, "animSource" 0x102D90C0 (always null) /
		// 0x102DA910 (SetAnimation)
		bool GetEnableGeoLOD() const;
		bool GetEnableGeoFade() const;
		void SetEnableGeoFade(bool enable);
		engine::render::DrawableArchetype* GetSource() const;
		const content::ObjectName* GetSourceName() const;
		void SetSource(engine::render::DrawableArchetype* archetype, const content::ObjectName& name);
		pure3d::Animation* GetAnimation() const;
		// 0x102D9500 / 0x102D9540: the levels from the first to the last begin / stop being used (the behaviour is not read)
		void ShowLevels(const LODLevel* first, const LODLevel* last);
		void HideLevels(const LODLevel* first, const LODLevel* last);

		// +0x0C: the source of the pose handed to the drawables
		LODPoseSource* poseSource;
		// +0x10: the scale the drawables are given
		LODScaleSource* scaleSource;
		unsigned char unknown14[4];
		// +0x18: the attribute of the entry asked for
		LODIndexSource* paletteIndexSource;
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
		// +0x40: the levels of detail the content describes (reflected as "lod"), then a word
		LODRenderDataArray lod;
		int unknown4C;
		// +0x50: the level table (8-byte records; the engine's inline code tests it for emptiness and walks it by index),
		// then a word
		container::ArrayDynamic<LODLevel, container::AllocatorNew> levels;
		int unknown5C;
		// +0x60: the level drawn now (-1: none yet)
		unsigned int level;
		// +0x64: how far the fade between two levels has run (0 - 1)
		float fade;
		// +0x68: the fade of a forced level
		float forcedFade;
		// +0x6C / +0x70: the fade in position and its target (both 1 once it is done)
		float fadeInPosition;
		float fadeInTarget;
		float fadeInScale;
		// +0x78: a multiplier on this behaviour's fade distance
		float fadeScale;
		unsigned char unknown7C[0x80 - 0x7C];
		// +0x80: the name of the archetype the drawables were made from (reflected with "drawableSource")
		content::ObjectName sourceName;
		// +0x88: the package the drawables come from (the empty name: none)
		core::Name<core::CaseSensitiveKey> packageName;
		// +0x90: the heap of the bone data, +0x94 the data, +0x98 its size (names guessed)
		int heap;
		void* boneData;
		int boneDataSize;
		// +0x9C: bit 0 the drawables are bound ("enableGeoLOD"), bit 1 they fade ("enableGeoFade"), bit 2 the level was
		// forced, bit 3 the archetype waits for its package
		union
		{
			unsigned char flags;
			struct
			{
				unsigned char bound : 1;
				unsigned char geoFade : 1;
				unsigned char forced : 1;
				unsigned char deferred : 1;
			} bits;
		};
	};
}

namespace container
{
	// The engine moves the elements down in Erase with a call of AssignRange
	template<> struct ArrayEraseInline<proto::LODRenderData>
	{
		enum
		{
			value = 0
		};
	};
}

namespace content
{
	CONTENT_ARRAY_HELPER_COUNT_INSERT(proto::LODRenderDataArray);
}

#endif
