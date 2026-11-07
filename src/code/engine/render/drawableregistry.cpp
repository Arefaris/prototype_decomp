// The renderer's task (the unit 0x10849090 - 0x1084CBAF; no assert path, the file name is a guess): the registry of
// the drawables the renderer works on and the switches around it.
#include "code/engine/drawableregistry.h"

namespace engine
{
	// The task (0x1130EFE0) and the sub-frame interpolation switch in front of it (0x1130EFD8; names guessed)
	extern RenderTask gDrawableRegistry;
	extern bool gSubframeInterpolation;

	// FUNCTION: ENGINE 0x108490A0
	RenderTask* GetDrawableRegistry()
	{
		return &gDrawableRegistry;
	}

	// FUNCTION: ENGINE 0x108490B0
	void RenderTask::SetDetachMainThread(bool value)
	{
		detachMainThread = value;
	}

	// FUNCTION: ENGINE 0x108490C0
	bool RenderTask::GetDetachMainThread()
	{
		return detachMainThread;
	}

	// FUNCTION: ENGINE 0x108490D0
	void SetSubframeInterpolation(bool value)
	{
		gSubframeInterpolation = value;
	}

	// FUNCTION: ENGINE 0x108490E0
	void RenderTask::UpdateSimulation(UpdateContext context)
	{
		stepCount++;
		time0.AddMicroseconds((unsigned __int64)(unsigned int)context.unknown4 * 1000 + (unsigned int)context.unknown0);
	}

	// FUNCTION: ENGINE 0x10849480
	void RenderTask::Remove(void* task)
	{
		for (PresentationTask** it = tasks.Begin(); it != tasks.End(); it++)
		{
			if (*it == task)
			{
				tasks.EraseFast(it);
				return;
			}
		}
	}

	// FUNCTION: ENGINE 0x10849540
	void RenderTask::Add(void* task)
	{
		Remove(task);
		tasks.PushBack((PresentationTask*)task);
	}

	// FUNCTION: ENGINE 0x108494E0
	RenderTask::RenderTask() :
		stepCount(0),
		time0(0, 0),
		time1(0, 0),
		time2(0, 0)
	{
		unknown78 = 0;
		unknown7C = 0;
		unknown80 = 0;
		detachMainThread = false;
	}
}

// The kept copies of the members of the list of presentation tasks
typedef container::ArrayFixed<engine::RenderTask::PresentationTask*, 16> PresentationTaskList;
// FUNCTION: ENGINE 0x10849110
template PresentationTaskList::ArrayFixed();
// FUNCTION: ENGINE 0x10849120
template engine::RenderTask::PresentationTask** PresentationTaskList::Data();
// FUNCTION: ENGINE 0x10849130
template engine::RenderTask::PresentationTask** PresentationTaskList::End();
// FUNCTION: ENGINE 0x10849140
template int PresentationTaskList::Size() const;
// FUNCTION: ENGINE 0x10849150
template void container::Construct(engine::RenderTask::PresentationTask**, engine::RenderTask::PresentationTask* const&);
// FUNCTION: ENGINE 0x10849170
template void container::Destroy(engine::RenderTask::PresentationTask**);
// FUNCTION: ENGINE 0x10849180
template void container::Destroy(engine::RenderTask::PresentationTask**, engine::RenderTask::PresentationTask**);
// FUNCTION: ENGINE 0x10849420
template bool PresentationTaskList::PushBack(engine::RenderTask::PresentationTask* const&);
// FUNCTION: ENGINE 0x10849450
template void PresentationTaskList::EraseFast(engine::RenderTask::PresentationTask**);
// FUNCTION: ENGINE 0x10849470
template void PresentationTaskList::Clear();
// FUNCTION: ENGINE 0x108494C0
template void PresentationTaskList::Reset();
