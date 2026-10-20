// engine::render::ParameterInterpolator (parameterinterpolator.cpp): the render parameters the game thread hands to
// the render thread are interpolated between the frames, out of a pool of a fixed number of them. This unit holds the
// pool (one 0x40-byte interpolator per slot, an "in use" byte per slot and a free list of the slots' addresses); the
// interpolators themselves are the template engine::render::ParameterInterpolator<T>, which the units that use them
// instantiate. Only the class names come from the RTTI, the members are named after what they do (guesses).
#ifndef ENGINE_RENDER_ASYNC_PRIVATE_PARAMETERINTERPOLATOR_H
#define ENGINE_RENDER_ASYNC_PRIVATE_PARAMETERINTERPOLATOR_H

#include "code/core/name.h"

namespace engine
{
	namespace render
	{
		// The base of the interpolators: the pool reaches them through the vtable and their name only
		// (RTTI: engine::render::ParameterInterpolatorTypeless, two virtual slots: the destructor and Update)
		class ParameterInterpolatorTypeless
		{
		public:
			// 0x10826E00 (a copy nothing calls; the derived constructors inline it): id is the render parameters the
			// interpolator writes to (a pointer), type the easing curve (0: smooth step, 1: sine, 2: cosine)
			ParameterInterpolatorTypeless(int id, const core::Name<core::CaseSensitiveKey>& name, float duration,
				int type) : mType(type), mDuration(duration), mTimeLeft(duration), mName(name), mId(id)
			{
			}
			// 0x10826DD0: sets the base's vftable
			virtual ~ParameterInterpolatorTypeless()
			{
			}
			// Called on every live interpolator with the time to interpolate to; false means the interpolator is
			// done and its slot goes back to the pool
			virtual bool Update(float time) = 0;

			// 0x108C0420: what the pool's Release compares with the name it is given
			core::Name<core::CaseSensitiveKey> GetName() const;
			// 0x10827980: the easing curve at t (0 - 1)
			float Ease(float t) const;

			unsigned int unknown4;                     // +0x04
			int mType;                                 // +0x08
			float mDuration;                           // +0x0C
			float mTimeLeft;                           // +0x10
			unsigned int unknown14;                    // +0x14
			core::Name<core::CaseSensitiveKey> mName;  // +0x18
			int mId;                                   // +0x20
			unsigned int unknown24;                    // +0x24
		};

		// The fixed pool of interpolators: one block holding the interpolators, their used flags and the free list
		class ParameterInterpolatorPool
		{
		public:
			// 0x108C02D0
			explicit ParameterInterpolatorPool(unsigned int capacity);
			// 0x108C0340
			~ParameterInterpolatorPool();

			// 0x108C03B0: a free interpolator, null when the pool is full (reports once)
			ParameterInterpolatorTypeless* Alloc();
			// 0x108C0440: gives the interpolator with this id and name back to the pool
			void Release(int id, const core::Name<core::CaseSensitiveKey>& name);
			// 0x108C0350: updates every live interpolator and gives the finished ones back
			void ReleaseAll(float time);

			// The block: the interpolators, then the free list, then the used flags (the block is one allocation, so
			// the members are byte-addressed rather than typed)
			char* mMemory;                           // +0x00
			int mCapacity;                           // +0x04
			int mUsed;                               // +0x08
			char* mUsedFlags;                        // +0x0C
			ParameterInterpolatorTypeless** mFree;   // +0x10
		};
	}
}

#endif
