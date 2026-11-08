// proto::FrontEndState (RTTI name; bases engine::GameState, engine::IRealTimeTask and the exception manager's
// IExceptionHandler): the game state of the front end (the menus, the attract movies and the ambient movie behind them). It
// registers the front end's script natives (fe_QuitGame, fe_PlayAttractMovie, the language and movie calls ...) and fades the
// playing movie out while the exception manager shows a condition. The member names are guessed from the script names. Unit
// 0x104DCEC0 - 0x104DEBE9 (no assert path; the file name is a guess).
#ifndef PROTO_FRONTENDSTATE_H
#define PROTO_FRONTENDSTATE_H

#include "code/core/name.h"
#include "code/engine/gamestate.h"
#include "code/engine/system/exceptionmanager.h"

namespace proto
{
	class FrontEndState : public engine::GameState, public engine::IRealTimeTask, public engine::ExceptionManager::IExceptionHandler
	{
	public:
		// 0x104DE970
		FrontEndState();
		// 0x104DDA20
		~FrontEndState();

		// vftable slots 0 and 1 of the game state (0x104DD060, 0x104DD3C0), slot 0 of the real time task (0x104DD530) and slots
		// 0 and 1 of the exception handler (0x104DD800, 0x104DD830)
		virtual void Enter();
		virtual void Leave();
		virtual void Update(engine::UpdateContext context);
		virtual void OnRaised(int condition);
		virtual void OnCleared(int condition);

		// The script natives: 0x104DD860, 0x104DD880, 0x104DD8A0, 0x104DD8B0, 0x104DD8E0, 0x104DD910, 0x104DD920, 0x104DD8F0,
		// 0x104DD940, 0x104DCEC0, 0x104DCEE0, 0x104DD950, 0x104DCF40, 0x104DCF70, 0x104DCFA0, 0x104DCF80, 0x104DD870
		void QuitGame();
		void ExitGame();
		void BootUpIsDone();
		void SetStartUpFlowActive(bool active);
		void PlayAttractMovie();
		unsigned int GetNumSupportedLanguages();
		const char* GetSupportedLanguageAt(unsigned int index);
		const char* GetCurrentLanguage();
		bool IsNAOnlyRegion();
		void PlayAmbientMovie(bool start);
		void StopAmbientMovie();
		void UpdateRichPresence();
		void PlayTrailerMovie(const char* path);
		bool IsMoviePlaying();
		void SkipTrailerMovie();
		void StopCurrentMovie();
		void GotoInitialInteractiveScreen();

		bool bootUpDone;  // +0x5C
		bool unknown5D;
		bool startUpFlowActive;  // +0x5E
		int unknown60;
		bool unknown64;
		int unknown68;
		int unknown6C;
		bool attractMoviePlayed;  // +0x70
		bool unknown71;
		const char* ambientMovie;  // +0x74
		int unknown78;
		bool movieFading;  // +0x7C
		unsigned char unknown7D[0x88 - 0x7D];
		core::Name<core::CaseSensitiveKey> unknown88;
		unsigned char unknown90[0xA8 - 0x90];
	};
}

#endif
