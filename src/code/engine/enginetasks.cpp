// The per-frame tasks of the engine's main loop (unit around 0x1085DE20 - 0x1085E100; no assert path, file name and
// all function names are guesses): the update of the game objects, pass by pass.
#include "code/core/file/filesystem.h"
#include "code/engine/audio/audiomanager.h"
#include "code/engine/camera/director.h"
#include "code/engine/controller/inputsystem.h"
#include "code/engine/fmv/fmvplayer.h"
#include "code/engine/gamestate.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/luascriptmanager.h"
#include "code/engine/online/ols.h"
#include "code/engine/online/replay.h"
#include "code/engine/audio/audiomanager.h"
#include "code/engine/render/effectmanager.h"
#include "code/engine/system/exceptionmanager.h"
#include "code/engine/system/gamestatetable.h"
#include "code/engine/system/simulationdriver.h"
#include <stdlib.h>
#include "code/choreo/puppetmanager.h"

namespace content
{
	// 0x106075F0: runs what the content loaders have pending
	void UpdateLoads();
}

namespace engine
{
	// The tasks' callees in other units (all names guessed)
	void RestoreEffectSuspendCount();
	void Unknown1089A4E0();
	void Unknown1085B800(UpdateContext context);
	void Unknown108D6710(UpdateContext context);
	void Unknown1085D6E0();
	void Unknown107E75F0(UpdateContext context);
	void Unknown1082BA10();
	void Unknown10899F60();
	void Unknown107DEAD0();
	void Unknown1082C6D0();
	void UpdateFrontend(UpdateContext context);
	const char* GetCommandLineValue(const char* option);
	void RequestGameState(int state, int mode, SyncCommands::SyncCallback* callback);
	void Unknown10874250();
	// The game object frame the last frame task ran in (-1 before the first)
	int gLastFrameTaskFrame = -1;

	// FUNCTION: ENGINE 0x1085DE20
	void UpdateGameObjectsPass2(UpdateContext context)
	{
		UpdateGameObjects(context, 2);
	}

	// FUNCTION: ENGINE 0x1085DE50
	void UpdateGameObjectsPass4(UpdateContext context)
	{
		UpdateGameObjects(context, 4);
	}

	// FUNCTION: ENGINE 0x1085DE80
	void UpdateGameObjectsPass16(UpdateContext context)
	{
		UpdateGameObjects(context, 0x10);
	}

	// FUNCTION: ENGINE 0x1085DEB0
	void UpdateGameObjectsPass32(UpdateContext context)
	{
		UpdateGameObjects(context, 0x20);
	}

	// FUNCTION: ENGINE 0x1085DEE0
	void UpdateGameObjectsPass64(UpdateContext context)
	{
		UpdateGameObjects(context, 0x40);
	}

	// FUNCTION: ENGINE 0x1085DF10
	void UpdateGameObjectsPass256(UpdateContext context)
	{
		UpdateGameObjects(context, 0x100);
	}

	// FUNCTION: ENGINE 0x1085DF40
	// Runs pass 8 once per game object frame, with the time the simulation driver keeps at +0x28
	void UpdateGameObjectsPass8Once()
	{
		if (gLastFrameTaskFrame != GetGameObjectFrame())
		{
			gLastFrameTaskFrame = GetGameObjectFrame();
			ISimulationDriver* driver = GetSimulationDriver();
			UpdateGameObjects(*(UpdateContext*)&driver->time3, 8);
		}
	}

	// The online manager (another unit, the global at 0x11318530; the type name is the one the global is mapped with)
	struct OnlineManagerView
	{
		// 0x108BF430
		void Unknown108BF430();
	};
	extern OnlineManagerView* gOnlineManager;

	// FUNCTION: ENGINE 0x1085E770
	// Leaves the game once the time the command line option "TimedExit" names (in seconds) has passed
	void TimedExit(UpdateContext context)
	{
		const char* value = GetCommandLineValue("TimedExit");
		if (value != 0)
		{
			unsigned int seconds = atoi(value);
			ISimulationDriver* driver = GetSimulationDriver();
			core::Time time = driver->time6;
			if ((float)seconds < time.seconds)
			{
				RequestGameState(0, 0, 0);
			}
		}
	}

	// The simulation task the engine runs every step (RTTI: engine::EngineSimulationTask, base ISimulationTask)
	class EngineSimulationTask : public ISimulationTask
	{
	public:
		// vftable slot 0 (0x1085DF80): the steps of a simulation frame: the update passes of the game objects between
		// the cameras', the puppets, the effects and the scripts, and last the audio
		virtual void UpdateSimulation(UpdateContext context);
	};

	// FUNCTION: ENGINE 0x1085DF80
	void EngineSimulationTask::UpdateSimulation(UpdateContext context)
	{
		RestoreEffectSuspendCount();
		NextGameObjectFrame();
		Unknown1089A4E0();
		camera::Director::Get()->Update(context, 1);
		UpdateGameObjectsPass2(context);
		UpdateGameObjectsPass4(context);
		Unknown1085B800(context);
		Unknown108D6710(context);
		choreo::UpdatePuppetManager(context.dt);
		UpdateGameObjectsPass16(context);
		Unknown1085D6E0();
		UpdateGameObjectsPass32(context);
		Unknown107E75F0(context);
		UpdateGameObjectsPass8Once();
		UpdateGameObjectsPass64(context);
		camera::Director::Get()->Update(context, 0x80);
		UpdateGameObjectsPass256(context);
		FlushDeferredUpdates();
		render::GetEffectManager()->Update(context);
		GetScriptManager()->Update(*(core::Time*)&context);
		Unknown1082BA10();
		AudioManager::Get()->Unknown10844D40(context);
	}

	// The real time task the engine runs every frame (RTTI: engine::EngineRealTimeTask, base IRealTimeTask)
	class EngineRealTimeTask : public IRealTimeTask
	{
	public:
		// vftable slot 0 (0x1085E800): the controllers, the file system and the content loads, the cameras, the audio,
		// the online services and the frontend
		virtual void Update(UpdateContext context);
	};

	// FUNCTION: ENGINE 0x1085E800
	void EngineRealTimeTask::Update(UpdateContext context)
	{
		Unknown10899F60();
		controller::InputSystem::Get()->UpdatePlayers(context);
		Unknown107DEAD0();
		core::FileSystemUpdate();
		content::UpdateLoads();
		Unknown1082C6D0();
		TimedExit(context);
		camera::Director::Get()->Unknown107DDB80(context);
		AudioManager::Get()->Update(context);
		OLS::Get()->Update();
		gOnlineManager->Unknown108BF430();
		Unknown10874250();
		UpdateFrontend(context);
		UpdateExceptionManager(*(core::Time*)&context);
		UpdateMovieState();
	}
}
