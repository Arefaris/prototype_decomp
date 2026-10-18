// pure3d::Scene (RTTI name; four virtual functions, vftable 0x10E5B358; unit code/pure3d/src/scene.cpp, 0x10710930 -
// 0x10714400, file name guessed from the class): the drawables the render thread draws, their visibility server and
// the asynchronous drawable and bounds updates ("AsyncDrawableUpdate", "AsyncBVUpdate"). The engine reaches the one
// scene through 0x10817B10. Layout partial; member names guessed.
#ifndef PURE3D_SCENE_H
#define PURE3D_SCENE_H

#include "code/container/arraydynamic.h"

namespace pure3d
{
	class Drawable;

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

	class Scene
	{
	public:
		// 0x10714760 (another unit) / 0x107143A0: the destructor is not virtual
		explicit Scene(const SceneSettings& settings);
		~Scene();

		// 0x10712410 / 0x10712540
		virtual void Add(Drawable* drawable, int unknown);
		virtual void Remove(Drawable* drawable);
		// 0x10711760, 0x107128D0
		virtual void Unknown2();
		virtual void Unknown3();

		// 0x10712300: puts a drawable of the scene on the list of drawables to refresh (once)
		void Refresh(Drawable* drawable);
		// 0x10711400: UpdateParts and UpdateBounds for every step-th drawable from first that was marked this frame
		// or is cyclic (the body of the "AsyncDrawableUpdate" tasks)
		void UpdateDrawables(unsigned int first, float dt, unsigned int step);
		// 0x10710B10 / 0x10710B40
		void* GetUnknownE0();
		void* GetUnknownD8();

		unsigned char unknown4[0x24];
		container::ArrayDynamic<Drawable*, container::AllocatorNew> drawables;
		unsigned char unknown34[0xA4];
		void* unknownD8;
		unsigned char unknownDC[4];
		void* unknownE0;
		unsigned char unknownE4[0x38];
		// The batches of the parts a shadow pass draws (room for as many as a pass finds)
		const void* batches[0x15B9];
	};
}

#endif
