// pure3d::Animation (RTTI name; bases pure3d::Entity, pure3d::RefCounted, core::IRefCount) and the memory manager that
// holds the data of the animations. Only what the animation unit and the choreo module read; names are guesses.
#ifndef PURE3D_ANIMATION_H
#define PURE3D_ANIMATION_H

#include "code/pure3d/entity.h"

namespace pure3d
{
	class AnimationMemoryBlock;
	class Channel;

	// A group of channels of an animation, found by a name (RTTI: vftable 0x10E55A78, 2 slots)
	class AnimationGroup
	{
	public:
		// 0x106E8550: an empty group
		AnimationGroup();
		// 0x106E91E0 (it lets the channels go through Clear); the scalar deleting destructor is 0x106E97D0
		virtual ~AnimationGroup();
		// 0x106E8C80: deletes the channels of a group made on the heap, or lets the channels of one made in a
		// memory block go and releases the block
		virtual void Clear();
		// 0x106E8240: the hash of the name
		unsigned __int64 GetNameHash();
		// 0x106E7910: the channel of the group by its type and the type of its values
		void* FindChannel(unsigned int type, unsigned int format);

		unsigned char unknown4[4];
		core::Name<core::CaseSensitiveKey> mName;
		// The id the group is found by in an animation sorted by id (the overall groups)
		int mId;
		unsigned int mChannelCount;
		Channel** mChannels;
		AnimationMemoryBlock* mBlock;
	};

	// pure3d::AnimationMemoryBlock (RTTI name; base pure3d::RefCounted, vftable 0x10E559E0): the memory the data of an
	// animation sits in, two pools: one for the objects and one for the arrays
	class AnimationMemoryBlock : public RefCounted
	{
	public:
		// 0x106E7820: the sizes of the two pools (objects, arrays); a pool of no bytes has no memory
		explicit AnimationMemoryBlock(const unsigned int* sizes);
		// 0x106E7890; the scalar deleting destructor is 0x106E8530
		virtual ~AnimationMemoryBlock();
		// 0x106E78C0: size bytes from one of the two pools (the one of the 7 mask for objects, the other for
		// arrays), aligned by the mask; null for no bytes (name guess)
		void* Allocate(unsigned int size, unsigned int alignmentMask);

		unsigned int mSizes[2];
		// How much of each pool is taken
		unsigned int mUsed[2];
		char* mPools[2];
	};

	// What an animation keeps of its data (+0x3C of the animation; names guessed)
	struct AnimationData
	{
		unsigned char unknown0[4];
		int mStart;
		int mEnd;
		void* mArray;
		// The data itself (zero while it is not loaded)
		void* mData;
	};

	// A track of events of an animation (0x30 bytes; the name is the one it is found by)
	struct AnimationEventTrack
	{
		~AnimationEventTrack()
		{
		}

		core::Name<core::CaseSensitiveKey> name;
		unsigned char unknown8[0x28];
	};

	// The manager of the animation memory (the global at 0x1127EDDC)
	class AnimationMemoryManager
	{
	public:
		// 0x106E76C0: marks the data as used (with the manager's lock held)
		void Touch(void* data);
		// 0x106E77E0: gives the data of an animation back (name guess)
		void FreeData(void* data);

		unsigned char unknown0[0x68];
		// How many bytes of animation data have been given back (name guess)
		int mFreed;
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

		// 0x106E7960: an empty animation of 30 frames a second
		Animation();
		// 0x106E91F0 (frees the groups, the events and the data); the scalar deleting destructor is 0x106E97F0
		virtual ~Animation();
		// Slots 3 and 4 (0x106E79B0, 0x106E79C0): the base answers false and itself
		virtual bool Unknown3();
		virtual Animation* Unknown4();
		// 0x106E7B20: touches the animation's data in the manager
		void Touch();
		// 0x106E7B50: releases the animation's data through the manager (name guess)
		void Unknown106E7B50();
		// 0x106E9310: keeps the data of mode in the manager's memory (name guess)
		void Unknown106E9310(int mode);
		// 0x106E8590 / 0x106E79E0: the group of the animation for a name, and the group of the whole animation
		AnimationGroup* FindGroup(const core::Name<core::CaseSensitiveKey>* name);
		// 0x106E8D30 / 0x106E8D60 / 0x106E8690: the group of a name given as text, and the index of a group by text and by name
		AnimationGroup* FindGroup(const char* name);
		int FindGroupIndex(const char* name);
		int FindGroupIndex(const core::Name<core::CaseSensitiveKey>* name);
		// 0x106E8770: moves a frame on by dt (scaled by the frame rate) inside the range the way the cycle mode says;
		// remaining is the time left to play and forward the direction the frame moves in (name guess)
		float AdvanceFrame(float* remaining, bool* forward, float frame, float dt, float start, float end, bool unlimited,
			int mode);
		// 0x106E79D0: the group at an index
		AnimationGroup* GetGroup(int index);
		AnimationGroup* FindOverallGroup(int mode);
		// 0x106E7A90: the index of the group of that id (-1 for none)
		int FindOverallGroupIndex(int id);

		float numFrames;
		float mFrameRate;
		bool mFlag0;
		unsigned char unknown19[3];
		// The four characters of the kind of animation (the frame controllers test it); the number of groups
		unsigned int mType;
		float mUnknown20;
		// How the groups are kept: 1 sorted by id, 0 sorted by name
		int mSortMode;
		int mGroupCount;
		AnimationGroup** mGroups;
		// The block the groups and the events are made in (none for an animation made on the heap), how many tracks of
		// events there are and the tracks
		AnimationMemoryBlock* mGroupBlock;
		unsigned int mEventCount;
		AnimationEventTrack* mEvents;
		AnimationData* mBlock;
	};

	// 0x1127EDDC
	extern AnimationMemoryManager* gAnimationMemoryManager;
}

#endif
