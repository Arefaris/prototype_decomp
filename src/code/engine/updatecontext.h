// engine::UpdateContext: the frame's timing the update stages and the tasks take by value (12 bytes: it has the layout
// of core::Time; only the time step is known). Names are guesses.
#ifndef ENGINE_UPDATECONTEXT_H
#define ENGINE_UPDATECONTEXT_H

namespace engine
{
	struct UpdateContext
	{
		int unknown0;
		int unknown4;
		float dt;
	};
}

#endif
