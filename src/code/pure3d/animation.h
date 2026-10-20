// pure3d::Animation (RTTI name; bases pure3d::Entity, pure3d::RefCounted, core::IRefCount) and the memory manager that
// holds the data of the animations. Only what the animation unit and the choreo module read; names are guesses.
#ifndef PURE3D_ANIMATION_H
#define PURE3D_ANIMATION_H

#include "code/pure3d/entity.h"

namespace pure3d
{
	// pure3d::AnimationMemoryBlock (RTTI name; base pure3d::RefCounted): the memory an animation's data sits in
	class AnimationMemoryBlock : public RefCounted
	{
	public:
		unsigned char unknown8[8];
		// The animation data, a pointer into the block (zero while it is not loaded)
		void* mData;
	};

	// The manager of the animation memory (the global at 0x1127EDDC)
	class AnimationMemoryManager
	{
	public:
		// 0x106E76C0: marks the data as used (with the manager's lock held)
		void Touch(void* data);
	};

	class Animation : public Entity
	{
	public:
		enum CycleMode
		{
			CYCLE_MODE_0,
			CYCLE_MODE_1,
			CYCLE_MODE_2,
			CYCLE_MODE_3,
			CYCLE_MODE_4,
			CYCLE_MODE_5
		};

		// 0x106E7B20: touches the animation's data in the manager
		void Touch();
		// 0x106E7B50: releases the animation's data through the manager (name guess)
		void Unknown106E7B50();
		// 0x106E9310: keeps the data of mode in the manager's memory (name guess)
		void Unknown106E9310(int mode);

		float numFrames;
		float mFrameRate;
		bool mFlag0 : 1;
		unsigned char unknown18Bits : 7;
		unsigned char unknown19[7];
		float mUnknown20;
		unsigned char unknown24[0x14];
		AnimationMemoryBlock* mBlock;
	};

	// 0x1127EDDC
	extern AnimationMemoryManager* gAnimationMemoryManager;
}

#endif
