// pure3d::ParticleTaskManager (RTTI: only its TaskCallback, a core::AsyncTaskCallback): the 50 tasks the particle update
// runs its kernels in, the queue of the tasks that are ready, and the events that tell when a pass is done. The
// unit is code/pure3d/effects/src/particletasks.cpp's neighbour (0x1073B8F0 - 0x1073C1B0); names are guesses.
#ifndef PURE3D_EFFECTS_PARTICLETASKMANAGER_H
#define PURE3D_EFFECTS_PARTICLETASKMANAGER_H

#include "code/container/arrayfixed.h"
#include "code/core/asynctask.h"

namespace pure3d
{
	struct ParticleEntry;

	class ParticleTaskManager
	{
	public:
		class TaskCallback : public core::AsyncTaskCallback
		{
		public:
			// 0x1073B950
			TaskCallback();
			// Slot 0 (0x1073C180): the task that is done tells the manager
			virtual void OnResult(int result);
			// 0x1073B970 / 0x1073B980
			void SetManager(ParticleTaskManager* newManager);
			void SetEnabled(bool newEnabled);

			ParticleTaskManager* manager;
			bool enabled;
		};

		// One task of the manager (0x80 bytes): a chain of the tasks that run after it, the job and its callback
		struct Task
		{
			// 0x1073B990
			Task();
			// 0x1073B9C0: forgets the chain
			void Clear(int unused);
			// 0x1073B9D0
			bool IsEmpty();
			// 0x1073B9E0: puts a task at the end of the chain
			void Append(Task* task);
			// 0x1073B930: runs the job on the calling thread
			void Run();
			// 0x1073B940
			int GetUnknown70();
			// 0x1073BA20: turns the callback on or off
			void SetCallbackEnabled(bool enabled);
			// 0x1073BB60: sets the task up for the manager and the kind of system
			void Setup(ParticleTaskManager* manager, void* unused, int kind);

			Task* first;
			Task* last;
			unsigned char unknown8[8];
			core::AsyncTaskJob job;
			Task* next;
			unsigned char unknown5C[4];
			TaskCallback callback;
			int unknown6C;
			int unknown70;
			unsigned char unknown74[0xC];
		};

		// 0x1073BE50 / 0x1073BEE0: the tasks, the lock and the events are made and unmade
		ParticleTaskManager();
		~ParticleTaskManager();
		// 0x1073BBD0: sets the tasks of an entry of the particle module up (name guess)
		void AddEntry(ParticleEntry* entry);
		// 0x1073BD60: forgets the queue and every chain
		void Reset();
		// 0x1073BDC0: waits until the pass is done, then forgets the queue and every chain
		void Wait();
		// 0x1073BDE0: hands every queued task its end, forgets the queue and lets the waiting threads go on
		void Finish();
		// 0x1073BF50: runs the queued tasks on the calling thread, pass by pass
		void RunAll();
		// 0x1073C000: submits the tasks of the pass that are ready
		void Submit();
		// 0x1073C110: the task of that number is done
		void TaskDone(int index);

		Task tasks[50];
		// The tasks that are ready to run (3500 of them)
		container::ArrayFixed<Task*, 3500> queue;
		unsigned char criticalSection[0x18];
		unsigned char done[8];
		unsigned char passes[2][8];
		int unknown4FE4;
		unsigned int pass;
		// Only the module's allocation shows this word (0x4FF0 bytes)
		unsigned int unknown4FEC;
	};
}

#endif
