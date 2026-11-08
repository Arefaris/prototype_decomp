// RTTI: engine::GameFlowManager::StateRequestCallback (one slot, 4 bytes): told when a state request was carried out
#ifndef ENGINE_GAMEFLOWMANAGER_H
#define ENGINE_GAMEFLOWMANAGER_H

namespace engine
{
	class GameFlowManager
	{
	public:
		class StateRequestCallback
		{
		public:
			virtual void OnFinished(int state, bool aborted) = 0;
		};
	};
}

#endif
