// engine::RenderTask (RTTI name; bases IRealTimeTask and ISimulationTask, the singleton at 0x1130EFE0; the unit
// 0x10849090 - 0x1084CBAF): the task that runs the renderer's presentation tasks every frame and keeps the time of the
// simulation steps. The scripts reach it through GetDrawableRegistry (name guessed). Member names are guesses.
#ifndef ENGINE_DRAWABLEREGISTRY_H
#define ENGINE_DRAWABLEREGISTRY_H

#include "code/container/arrayfixed.h"
#include "code/core/time.h"
#include "code/engine/gamestate.h"
#include "code/engine/online/replay.h"
#include "code/engine/updatecontext.h"

namespace engine
{
	class RenderTask : public IRealTimeTask, public ISimulationTask
	{
	public:
		// What the task runs every frame (RTTI: engine::RenderTask::PresentationTask, one virtual function)
		class PresentationTask
		{
		public:
			virtual void Update(UpdateContext context, unsigned int unknown1, unsigned int unknown2) = 0;
		};

		// 0x108494E0
		RenderTask();
		// vftable slot 0 of IRealTimeTask (0x10849190; the engine's takes two words)
		virtual void Update(UpdateContext context);
		// vftable slot 0 of ISimulationTask (0x108490E0): counts the step and adds its time
		virtual void UpdateSimulation(UpdateContext context);
		// 0x10849540: puts a presentation task in the list (once)
		void Add(void* task);
		// 0x10849480: takes a presentation task out of the list
		void Remove(void* task);
		// 0x108490B0 / 0x108490C0: whether the drawables are updated apart from the main thread (the byte at +0x84)
		void SetDetachMainThread(bool value);
		bool GetDetachMainThread();

		int stepCount;  // +8
		core::Time time0;  // +0xC
		core::Time time1;  // +0x18
		core::Time time2;  // +0x24
		container::ArrayFixed<PresentationTask*, 16> tasks;  // +0x30
		int unknown74;
		int unknown78;
		int unknown7C;
		int unknown80;
		bool detachMainThread;  // +0x84
	};

	// 0x108490A0: the task (a global at 0x1130EFE0)
	RenderTask* GetDrawableRegistry();
}

#endif
