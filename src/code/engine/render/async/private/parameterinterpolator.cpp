// engine::render::ParameterInterpolator (assert path ..\..\..\code\engine\render\async\private\
// parameterinterpolator.cpp): the pool the renderer's parameters to interpolate are handed out of. The used slots sit
// at the front of the pool and the free list is a stack of their addresses: Alloc pops one, Release and the update
// walk push the finished ones back, and a pool that runs out reports once and answers with a null interpolator.
#include <new>
#include <string.h>

#include "code/core/report.h"
#include "code/engine/render/async/private/parameterinterpolator.h"

#define PARAMETERINTERPOLATOR_FILE "..\\..\\..\\code\\engine\\render\\async\\private\\parameterinterpolator.cpp"

namespace engine
{
	namespace render
	{
		// The size of an interpolator, which is also the pool's slot size
		enum { PARAMETERINTERPOLATOR_SIZE = 0x40 };

		// FUNCTION: ENGINE 0x108C02D0
		ParameterInterpolatorPool::ParameterInterpolatorPool(unsigned int capacity)
		{
			mMemory = 0;
			mCapacity = capacity;
			mUsed = 0;
			mUsedFlags = 0;
			mFree = 0;
			mMemory = new char[capacity * (PARAMETERINTERPOLATOR_SIZE + 5)];
			mFree = (ParameterInterpolatorTypeless**)(mMemory + capacity * PARAMETERINTERPOLATOR_SIZE);
			mUsedFlags = (char*)(mFree + capacity);
			memset(mUsedFlags, 0, capacity);
			for (int i = 0; i < (int)capacity; i++)
			{
				mFree[i] = (ParameterInterpolatorTypeless*)(mMemory + i * PARAMETERINTERPOLATOR_SIZE);
			}
		}

		// FUNCTION: ENGINE 0x108C0340
		ParameterInterpolatorPool::~ParameterInterpolatorPool()
		{
			delete[] mMemory;
		}

		// FUNCTION: ENGINE 0x108C0350
		void ParameterInterpolatorPool::ReleaseAll(float time)
		{
			for (int i = 0; i < mCapacity; i++)
			{
				if (mUsedFlags[i] != 0)
				{
					ParameterInterpolatorTypeless* interpolator =
						(ParameterInterpolatorTypeless*)(mMemory + i * PARAMETERINTERPOLATOR_SIZE);
					if (!interpolator->Update(time))
					{
						mUsed--;
						mFree[mUsed] = interpolator;
						mUsedFlags[i] = 0;
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x108C03B0
		ParameterInterpolatorTypeless* ParameterInterpolatorPool::Alloc()
		{
			ParameterInterpolatorTypeless* interpolator = mFree[mUsed];
			int index = (int)((char*)interpolator - mMemory) / PARAMETERINTERPOLATOR_SIZE;
			if (index >= mCapacity)
			{
				static bool sReported = true;
				if (sReported)
				{
					if (core::Report(1, "Engine", PARAMETERINTERPOLATOR_FILE, 0x5f, 0,
						"The number of rendering parameters to be interpolated in the engine is too small. Please bump "
						"this up (probably somewhere in engine/init.cpp).", 0) == 3)
					{
						sReported = false;
					}
				}
				return 0;
			}
			mUsed++;
			mUsedFlags[index] = 1;
			return interpolator;
		}

		// FUNCTION: ENGINE 0x108C0420
		core::Name<core::CaseSensitiveKey> ParameterInterpolatorTypeless::GetName() const
		{
			return mName;
		}

		// FUNCTION: ENGINE 0x108C0440
		// NONMATCHING: register allocation, 96 % (the original keeps the id in eax and the name copy's source in
		// ecx, ours uses ecx and edx; every instruction is otherwise identical)
#ifdef NONMATCHING
		void ParameterInterpolatorPool::Release(int id, const core::Name<core::CaseSensitiveKey>& name)
		{
			for (int i = 0; i < mCapacity; i++)
			{
				if (mUsedFlags[i] != 0)
				{
					ParameterInterpolatorTypeless* interpolator =
						(ParameterInterpolatorTypeless*)(mMemory + i * PARAMETERINTERPOLATOR_SIZE);
					if (interpolator->mId == id && interpolator->GetName() == name)
					{
						mUsed--;
						mFree[mUsed] = interpolator;
						mUsedFlags[i] = 0;
						return;
					}
				}
			}
		}
#endif
	}
}
