// pure3d::Scene (RTTI name; four virtual functions, vftable 0x10E5B358; unit code/pure3d/src/scene.cpp, 0x10710930 -
// 0x10714400, file name guessed from the class): the drawables the render thread draws, their visibility server and
// the asynchronous drawable and bounds updates ("AsyncDrawableUpdate", "AsyncBVUpdate"). The engine reaches the one
// scene through 0x10817B10. Layout partial; member names guessed.
#ifndef PURE3D_SCENE_H
#define PURE3D_SCENE_H

#include "code/container/arraydynamic.h"
#include "code/pure3d/visibility.h"

namespace pure3d
{
	class Drawable;
	class DrawablePart;
	class Light;
	class LightGroupTable;
	class LightingScene;
	struct PartList;
	class PassEntries;

	// What a scene is made from (0x54 bytes; the constructor 0x10711B90 sets the defaults, 0x80, 0x20, 0x400, 0x100 ...)
	struct SceneSettings
	{
		SceneSettings();

		int unknown0;
		int unknown4;
		// How many drawables the scene holds
		int drawableCount;
		int unknownC;
		float unknown10;
		unsigned char unknown14[0x30];
		int unknown44;
		unsigned char unknown48[0xC];
	};

	// A record of the scene's list of the parts it keeps a visibility client for (0x24 bytes; the client sits first)
	struct PartClient : public visibility::Client
	{
		unsigned char unknownC[0x10];
		DrawablePart* part;
		bool active;
		unsigned char unknown21[3];
	};

	class Scene
	{
	public:
		// 0x10714760 (another unit) / 0x107143A0: the destructor is not virtual
		explicit Scene(const SceneSettings& settings);
		~Scene();

		// 0x10712410 / 0x10712540
		virtual void Add(Drawable* drawable, bool unknown);
		virtual void Remove(Drawable* drawable);
		// 0x10711760, 0x107128D0
		virtual void Unknown2(Drawable* drawable);
		virtual void Unknown3(Drawable* drawable);

		// 0x10712300: puts a drawable of the scene on the list of drawables to refresh (once)
		void Refresh(Drawable* drawable);
		// 0x10711400: UpdateParts and UpdateBounds for every step-th drawable from first that was marked this frame
		// or is cyclic (the body of the "AsyncDrawableUpdate" tasks)
		void UpdateDrawables(unsigned int first, float dt, unsigned int step);
		// 0x10710AC0 / 0x10710AE0: the lighting scene's add and remove of a light (a jump each)
		void AddLight(Light* light);
		void RemoveLight(Light* light);
		// 0x10710B10 / 0x10710B00
		LightingScene* GetLightingScene();
		LightGroupTable* GetLightGroupTable();
		// 0x10710B40
		void* GetUnknownD8();
		// 0x10712760 (a root pass calls it before it runs its children)
		void Unknown10712760();
		// 0x107127E0: puts the drawables on the list while it has room (name guess)
		void GetDrawables(container::ArrayDynamicHeap<Drawable*>* list, int unused);
		// 0x10714560 (a jump into the part table the scene keeps at +0xD8): fills the list with the parts that pass the
		// filter
		void SelectParts(PartList* list, PassEntries* entries);

		unsigned char unknown4[4];
		// Every drawable the scene holds (Add appends, Refresh looks here)
		container::ArrayDynamicHeap<Drawable*> allDrawables;
		unsigned char unknown18[0x10];
		// The drawables UpdateDrawables looks at each frame: the cyclic ones, the ones marked "always" and the ones Add is
		// told to
		container::ArrayDynamicHeap<Drawable*> drawables;
		// The cyclic drawables
		container::ArrayDynamicHeap<Drawable*> cyclicDrawables;
		unsigned char unknown48[0x10];
		// The drawables whose first part is a particle system (the primitive of kind 0x10)
		container::ArrayDynamicHeap<Drawable*> particleDrawables;
		unsigned char unknown68[0x20];
		// The parts of the skinned drawables that have a client record
		container::ArrayDynamicHeap<PartClient> partClients;
		unsigned char unknown98[0x10];
		// Every drawable Add takes (name guess)
		container::ArrayDynamicHeap<Drawable*> addedDrawables;
		// The parts the scene follows (name guess)
		container::ArrayDynamicHeap<DrawablePart*> parts;
		// The drawables Refresh has put on the list to refresh (+0xC8)
		container::ArrayDynamicHeap<Drawable*> refreshList;
		void* unknownD8;
		LightGroupTable* lightGroupTable;
		LightingScene* lightingScene;
		unsigned char unknownE4[0x34];
		// Set when a drawable that is not cyclic is added or removed (name guess)
		bool unknown118;
		unsigned char unknown119[3];
		// The batches of the parts a shadow pass draws (room for as many as a pass finds)
		const void* batches[0x15B9];
	};
}

#endif
