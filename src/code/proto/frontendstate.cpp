#include "code/proto/frontendstate.h"

#include "code/core/language.h"
#include "code/engine/fmv/fmvplayer.h"
#include "code/engine/function.h"
#include "code/engine/luascriptmanager.h"
#include "code/engine/system/skuinfo.h"
#include <process.h>

namespace engine
{
	class FrontEnd;
	// 0x10864330
	FrontEnd* Unknown10864330();
	// 0x10872840: calls a function of the front end's movie with a format and the arguments it names (name unknown)
	void Unknown10872840(FrontEnd* frontEnd, const char* function, const char* format, ...);
	// 0x108391A0
	void RequestGameStateByIndex(int index, int mode);
	// 0x10890930 (another unit; name unknown)
	struct StateGate;
	StateGate* Unknown10890930();
	// 0x1082F990: the call with the fourth argument as a float (the same function as PlayMovie)
	void PlayMovie(const char* path, bool unknown12, int id, float unused, bool unknown13, bool unknown11, int unknown18,
		bool unknown19);
}

namespace proto
{
	// 0x104DF2C0
	void NotifyFreeRoamChanged();

	// 0x1109CA70 / 0x1109CA74: the movies behind the menu (the first plays once, the second loops)
	static const char* sAmbientMovieStart = "movies/fe_ambientMovie_start.bik";
	static const char* sAmbientMovieLoop = "movies/fe_ambientMovie_1.bik";
	// 0x1109CA80
	static int sTrailerMovieId = -1;
	// 0x1126E418: the front end state while one exists
	static FrontEndState* sFrontEndState = 0;

	// FUNCTION: ENGINE 0x104DE970
	FrontEndState::FrontEndState() : engine::GameState(0, 0x10000), bootUpDone(false), unknown5D(false),
		startUpFlowActive(true), unknown60(-1), unknown64(false), unknown68(0), unknown6C(0), attractMoviePlayed(false),
		unknown71(false), ambientMovie(0), unknown78(0), movieFading(false)
	{
		engine::LuaScriptManager* manager = engine::GetScriptManager();
		manager->RegisterMethod("fe_QuitGame", this, &FrontEndState::QuitGame);
		manager->RegisterMethod("fe_ExitGame", this, &FrontEndState::ExitGame);
		manager->RegisterMethod("fe_BootUpIsDone", this, &FrontEndState::BootUpIsDone);
		manager->RegisterMethod("fe_SetStartUpFlowActive", this, &FrontEndState::SetStartUpFlowActive);
		manager->RegisterMethod("fe_PlayAttractMovie", this, &FrontEndState::PlayAttractMovie);
		manager->RegisterMethod("fe_GetNumSupportedLanguages", this, &FrontEndState::GetNumSupportedLanguages);
		manager->RegisterMethod("fe_GetSupportedLanguageAt", this, &FrontEndState::GetSupportedLanguageAt);
		manager->RegisterMethod("fe_GetCurrentLanguage", this, &FrontEndState::GetCurrentLanguage);
		manager->RegisterMethod("fe_IsNAOnlyRegion", this, &FrontEndState::IsNAOnlyRegion);
		manager->RegisterMethod("fe_PlayAmbientMovie", this, &FrontEndState::PlayAmbientMovie);
		manager->RegisterMethod("fe_StopAmbientMovie", this, &FrontEndState::StopAmbientMovie);
		manager->RegisterMethod("fe_UpdateRichPresence", this, &FrontEndState::UpdateRichPresence);
		manager->RegisterMethod("fe_PlayTrailerMovie", this, &FrontEndState::PlayTrailerMovie);
		manager->RegisterMethod("fe_IsMoviePlaying", this, &FrontEndState::IsMoviePlaying);
		manager->RegisterMethod("fe_SkipTrailerMovie", this, &FrontEndState::SkipTrailerMovie);
		manager->RegisterMethod("fe_StopCurrentMovie", this, &FrontEndState::StopCurrentMovie);
		manager->RegisterMethod("fe_GotoInitialInteractiveScreen", this, &FrontEndState::GotoInitialInteractiveScreen);
		engine::ExceptionManager::AddHandler(this);
		sFrontEndState = this;
	}

	// FUNCTION: ENGINE 0x104DDA20
	FrontEndState::~FrontEndState()
	{
		sFrontEndState = 0;
		engine::ExceptionManager::RemoveHandler(this);
		engine::GetScriptManager()->Unregister(this);
	}

	// FUNCTION: ENGINE 0x104DD800
	void FrontEndState::OnRaised(int condition)
	{
		if (condition == 0)
		{
			movieFading = true;
			if (engine::IsMoviePlaying())
			{
				engine::FadeMovieOut();
			}
		}
	}

	// FUNCTION: ENGINE 0x104DD830
	void FrontEndState::OnCleared(int condition)
	{
		if (condition == 0)
		{
			movieFading = false;
			if (engine::IsMovieUnknown())
			{
				engine::ResumeMovie();
			}
		}
	}

	// FUNCTION: ENGINE 0x104DD860
	void FrontEndState::QuitGame()
	{
		engine::RequestGameStateByIndex(5, 2);
	}

	// FUNCTION: ENGINE 0x104DD870
	void FrontEndState::GotoInitialInteractiveScreen()
	{
		engine::RequestGameStateByIndex(4, 2);
	}

	// FUNCTION: ENGINE 0x104DD880
	void FrontEndState::ExitGame()
	{
		if (engine::Unknown10890930() == 0)
		{
			_exit(0);
		}
	}

	// FUNCTION: ENGINE 0x104DD8A0
	void FrontEndState::BootUpIsDone()
	{
		bootUpDone = true;
	}

	// FUNCTION: ENGINE 0x104DD8B0
	void FrontEndState::SetStartUpFlowActive(bool active)
	{
		startUpFlowActive = active;
	}

	// FUNCTION: ENGINE 0x104DD8E0
	void FrontEndState::PlayAttractMovie()
	{
		attractMoviePlayed = true;
		StopAmbientMovie();
	}

	// FUNCTION: ENGINE 0x104DD8F0
	const char* FrontEndState::GetCurrentLanguage()
	{
		return core::GetLanguageName(core::LanguageGet());
	}

	// FUNCTION: ENGINE 0x104DD910
	unsigned int FrontEndState::GetNumSupportedLanguages()
	{
		return engine::SkuInfo::GetCurrent()->GetLanguageCount();
	}

	// FUNCTION: ENGINE 0x104DD920
	const char* FrontEndState::GetSupportedLanguageAt(unsigned int index)
	{
		return engine::SkuInfo::GetCurrent()->GetLanguage(index)->language;
	}

	// FUNCTION: ENGINE 0x104DD940
	bool FrontEndState::IsNAOnlyRegion()
	{
		return false;
	}

	// FUNCTION: ENGINE 0x104DD950
	void FrontEndState::UpdateRichPresence()
	{
		NotifyFreeRoamChanged();
	}

	// FUNCTION: ENGINE 0x104DCEC0
	void FrontEndState::PlayAmbientMovie(bool start)
	{
		ambientMovie = start ? sAmbientMovieStart : sAmbientMovieLoop;
	}

	// FUNCTION: ENGINE 0x104DCEE0
	void FrontEndState::StopAmbientMovie()
	{
		if (ambientMovie != 0)
		{
			ambientMovie = 0;
			engine::StopMovie();
			engine::Unknown10872840(engine::Unknown10864330(), "AS_Event", "%s%s%s%d%s", "PFE", "AmbientMovie", "Complete", 0, "");
		}
	}

	// FUNCTION: ENGINE 0x104DCF40
	void FrontEndState::PlayTrailerMovie(const char* path)
	{
		engine::PlayMovie(path, true, sTrailerMovieId, 0.0f, false, false, 0, false);
	}

	// FUNCTION: ENGINE 0x104DCF70
	bool FrontEndState::IsMoviePlaying()
	{
		return engine::IsMoviePlaying();
	}

	// FUNCTION: ENGINE 0x104DCF80
	void FrontEndState::StopCurrentMovie()
	{
		if (engine::IsMoviePlaying())
		{
			engine::StopMovie();
		}
	}

	// FUNCTION: ENGINE 0x104DCFA0
	void FrontEndState::SkipTrailerMovie()
	{
		engine::SkipMovie();
	}
}
