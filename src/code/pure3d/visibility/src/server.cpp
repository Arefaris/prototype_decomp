// pure3d::visibility::Server (unit 0x10726540 - 0x10729AE0; the path is guessed from the namespace): the visibility
// server and the frustum tests its asynchronous tasks run. Names are guesses.
#include "code/core/asynctask.h"
#include "code/core/criticalsection.h"
#include "code/pure3d/visibility.h"

namespace pure3d
{
	namespace visibility
	{
		// FUNCTION: ENGINE 0x107283A0
		// EQUIVALENT: the engine keeps word * 32 in a stack slot and adds the bit for the count check, and loads the
		// -0.0 of the plane test per box; ours steps a combined index and keeps the constant in a register
		// The body of a frustum test task: every box whose input bit is set gets its output bit set when it is
		// valid, not too small and not entirely outside any of the planes (its corner nearest each plane's inside
		// is tested)
		void RunTest(Test* test, core::AsyncTask* task)
		{
			const unsigned int* inputBits = test->inputBits;
			unsigned int* outputBits = test->outputBits;
			unsigned int words = (((test->boxCount + 7) >> 3) + 3) >> 2;
			for (unsigned int word = 0; word < words; word++)
			{
				outputBits[word] = 0;
				unsigned int input = inputBits[word];
				unsigned int first = word * 32;
				for (unsigned int bit = 0; bit < 32; bit++)
				{
					if (first + bit >= test->boxCount)
					{
						break;
					}
					unsigned int mask = 1 << bit;
					if (input & mask)
					{
						const math::AABB& box = test->boxes[word * 32 + bit];
						if (!box.IsEmpty() &&
							!(test->minimumSize * test->minimumSize * 12.0f >
								(box.max.x - box.min.x) * (box.max.x - box.min.x) +
								(box.max.y - box.min.y) * (box.max.y - box.min.y) +
								(box.max.z - box.min.z) * (box.max.z - box.min.z)))
						{
							for (unsigned int plane = 0; plane < test->planeCount; plane++)
							{
								const Test::Plane& p = test->planes[plane];
								float x = p.normal.x >= 0.0f ? box.min.x : box.max.x;
								float y = p.normal.y >= 0.0f ? box.min.y : box.max.y;
								float z = p.normal.z >= 0.0f ? box.min.z : box.max.z;
								if (p.normal.y * y + p.normal.z * z + x * p.normal.x > -p.distance)
								{
									goto next;
								}
							}
							outputBits[word] |= mask;
						}
					}
				next:
					;
				}
			}
		}

		// 0x1128185C, 0x11281860: the ids the two task functions are registered under (name guesses)
		extern int gTestTaskId;
		extern int gOcclusionTestTaskId;
		// 0x10729A90: the occlusion test task (another unit's part of the same file)
		void RunOcclusionTestTask(Test* test, core::AsyncTaskCallback* callback);

		// FUNCTION: ENGINE 0x10726590
		unsigned int Server::GetFlagSetCount()
		{
			return flagSetCount;
		}

		// FUNCTION: ENGINE 0x10728350
		void Server::FinishTest(int slot)
		{
			if (slot != -1)
			{
				core::EventWait(events + slot * 0xC);
				core::CriticalSectionEnter(lock);
				slotBusy[slot] = 0;
				core::CriticalSectionLeave(lock);
			}
		}

		// FUNCTION: ENGINE 0x107285B0
		void RunTestTask(Test* test, core::AsyncTaskCallback* callback)
		{
			RunTest(test, (core::AsyncTask*)callback);
			callback->SetResult(test->slot);
		}

		// FUNCTION: ENGINE 0x10726540
		void RegisterTasks()
		{
			core::RegisterAsyncTaskFunction("pure3dVisibilityTest", (void (*)(void*, core::AsyncTaskCallback*))RunTestTask,
				&gTestTaskId);
			core::RegisterAsyncTaskFunction("pure3dVisibilityOcclusionTest",
				(void (*)(void*, core::AsyncTaskCallback*))RunOcclusionTestTask, &gOcclusionTestTaskId);
		}

		// FUNCTION: ENGINE 0x10726570
		void UnregisterTasks()
		{
			core::UnregisterAsyncTaskFunction(gTestTaskId);
			core::UnregisterAsyncTaskFunction(gOcclusionTestTaskId);
		}
	}


	// FUNCTION: ENGINE 0x107265E0
	void Unknown107265E0()
	{
	}

	// FUNCTION: ENGINE 0x107265F0
	void Unknown107265F0()
	{
	}
}
