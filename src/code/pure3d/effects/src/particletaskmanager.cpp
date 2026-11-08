// pure3d::ParticleTaskManager (unit around 0x1073B8F0 - 0x1073C1C0; file name guessed from the class). Names are guesses.
#include <new>

#include "code/core/criticalsection.h"
#include "code/pure3d/effects/particletaskmanager.h"
#include "code/pure3d/primitive.h"

namespace pure3d
{
	typedef char TaskSizeCheck[sizeof(ParticleTaskManager::Task) == 0x80 ? 1 : -1];
	typedef char ManagerSizeCheck[sizeof(ParticleTaskManager) == 0x4FEC ? 1 : -1];

	// FUNCTION: ENGINE 0x1073B950
	ParticleTaskManager::TaskCallback::TaskCallback()
	{
		manager = 0;
		enabled = true;
	}

	// FUNCTION: ENGINE 0x1073B970
	void ParticleTaskManager::TaskCallback::SetManager(ParticleTaskManager* newManager)
	{
		manager = newManager;
	}

	// FUNCTION: ENGINE 0x1073B980
	void ParticleTaskManager::TaskCallback::SetEnabled(bool newEnabled)
	{
		enabled = newEnabled;
	}

	// FUNCTION: ENGINE 0x1073B990
	ParticleTaskManager::Task::Task() : first(0), last(0)
	{
		unknown6C = -1;
		unknown70 = -1;
	}

	// FUNCTION: ENGINE 0x1073B9C0
	void ParticleTaskManager::Task::Clear(int unused)
	{
		first = 0;
		last = 0;
	}

	// FUNCTION: ENGINE 0x1073B9D0
	bool ParticleTaskManager::Task::IsEmpty()
	{
		return first == 0;
	}

	// FUNCTION: ENGINE 0x1073B9E0
	void ParticleTaskManager::Task::Append(Task* task)
	{
		if (task != 0)
		{
			task->next = 0;
		}
		if (first == 0)
		{
			first = task;
			job.SetData(task);
			last = task;
			return;
		}
		last->next = task;
		last = task;
	}

	// FUNCTION: ENGINE 0x1073B930
	void ParticleTaskManager::Task::Run()
	{
		job.RunHere();
	}

	// FUNCTION: ENGINE 0x1073B940
	int ParticleTaskManager::Task::GetUnknown70()
	{
		return unknown70;
	}

	// FUNCTION: ENGINE 0x1073BA20
	void ParticleTaskManager::Task::SetCallbackEnabled(bool enabled)
	{
		callback.SetEnabled(enabled);
	}

	// FUNCTION: ENGINE 0x1073BB60
	void ParticleTaskManager::Task::Setup(ParticleTaskManager* manager, void* unused, int kind)
	{
		callback.SetManager(manager);
		unknown6C = kind;
		unknown70 = GetParticleManager()->GetEntryNumber(kind);
		Append(0);
	}

	// FUNCTION: ENGINE 0x1073C180
	void ParticleTaskManager::TaskCallback::OnResult(int result)
	{
		if (enabled)
		{
			manager->TaskDone(result);
		}
	}

	// FUNCTION: ENGINE 0x1073BD60
	void ParticleTaskManager::Reset()
	{
		queue.Reset();
		for (int i = 0; i < 50; i++)
		{
			tasks[i].Clear(0);
		}
		pass = 0;
	}

	// FUNCTION: ENGINE 0x1073BDC0
	void ParticleTaskManager::Wait()
	{
		core::EventWait(done);
		Reset();
	}

	// FUNCTION: ENGINE 0x1073C110
	void ParticleTaskManager::TaskDone(int index)
	{
		core::CriticalSectionEnter(criticalSection);
		tasks[index].Clear(1);
		core::EventSignal(passes[pass], 1);
		if (core::AtomicRead((long volatile*)passes[pass]) == 0)
		{
			pass++;
			Submit();
		}
		core::CriticalSectionLeave(criticalSection);
	}

	// FUNCTION: ENGINE 0x1073BE50
	ParticleTaskManager::ParticleTaskManager()
	{
		unknown4FE4 = 0;
		pass = 0;
		core::CriticalSectionInit(criticalSection);
		core::EventInit(done, 0);
		for (int i = 0; i < 2; i++)
		{
			core::EventInit(passes[i], 0);
		}
		Reset();
	}

	// FUNCTION: ENGINE 0x1073BEE0
	ParticleTaskManager::~ParticleTaskManager()
	{
		Wait();
		for (int i = 0; i < 2; i++)
		{
			core::EventDestroy(passes[i]);
		}
		core::EventDestroy(done);
		core::CriticalSectionDelete(criticalSection);
	}

	// FUNCTION: ENGINE 0x1073BF50
	void ParticleTaskManager::RunAll()
	{
		core::EventWait(done);
		if (!queue.IsEmpty())
		{
			core::EventReset(done, 1);
			unknown4FE4 = 1;
			pass = 0;
			do
			{
				for (int i = 0; i < 50; i++)
				{
					if (!tasks[i].IsEmpty() && pass == tasks[i].unknown70)
					{
						tasks[i].SetCallbackEnabled(false);
						tasks[i].job.RunHere();
						tasks[i].Clear(0);
						tasks[i].SetCallbackEnabled(true);
					}
				}
				pass++;
			} while (pass <= 1);
			Finish();
		}
	}

	// FUNCTION: ENGINE 0x1073C000
	void ParticleTaskManager::Submit()
	{
		void* lock = criticalSection;
		core::CriticalSectionEnter(lock);
		while (pass <= 1)
		{
			long volatile* counter = (long volatile*)passes[pass];
			if (core::AtomicRead(counter) != 0)
			{
				break;
			}
			pass++;
		}
		if (pass > 1)
		{
			Finish();
			core::CriticalSectionLeave(lock);
			return;
		}
		container::ArrayFixed<Task*, 50> ready;
		for (int i = 0; i < 50; i++)
		{
			if (!tasks[i].IsEmpty() && pass == tasks[i].unknown70)
			{
				ready.PushBack(&tasks[i]);
			}
		}
		Task** last = ready.End();
		for (Task** task = ready.Begin(); task != last; task++)
		{
			(*task)->job.Submit(0);
		}
		core::CriticalSectionLeave(lock);
	}
}
