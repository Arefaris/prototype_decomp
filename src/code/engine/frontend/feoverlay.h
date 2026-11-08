// engine::FEOverlay (RTTI name of its callback struct): an overlay of the front end's movie. The movie keeps the overlays
// in a list; each overlay has a name, the name of the overlay movie and a priority, answers the calls the overlay's script
// makes by function name through the callbacks registered with it and calls script functions of the overlay itself.
// Unit 0x108E2100 - 0x108E2630 (no assert path; file name and member names guessed).
#ifndef ENGINE_FRONTEND_FEOVERLAY_H
#define ENGINE_FRONTEND_FEOVERLAY_H

#include "code/engine/frontend/femovie.h"

namespace engine
{
	// The front end's movie (another unit): 0x10872830 calls a function of the movie's script
	class FrontendMovie
	{
	public:
		void Invoke(const char* function, const FEMovie::Value* arguments, int count);

		unsigned char unknown0[0x30];
		// The overlays of the movie (their link is FEOverlay::next)
		class FEOverlay* overlays;  // +0x30
	};

	class FEOverlay;

	// The front end as the dialogs reach it (Unknown10864330 answers it; another unit)
	class FrontEnd
	{
	public:
		// 0x10872A60: the overlay with the names, made when there is none
		FEOverlay* CreateOverlay(const char* name, const char* overlayName, int priority);
	};
	FrontEnd* Unknown10864330();

	// RTTI: engine::FEOverlay::Callback (a struct with one slot): what the overlay's movie calls the engine back with
	class FEOverlay
	{
	public:
		struct Callback
		{
			// 0x108E3E00 (the engine's copy of the constructor)
			Callback()
			{
			}
			virtual void OnCall(int call, int a, int b, int c) = 0;
		};

		// A callback registered under the name of a script function (0x2C bytes)
		struct CallbackEntry
		{
			Callback* callback;  // +0
			int call;  // +4
			char name[0x20];  // +8
			CallbackEntry* next;  // +0x28
		};

		// 0x108E2200: makes the overlay in the movie
		FEOverlay(FrontendMovie* newMovie, const char* newName, const char* newOverlayName, unsigned int newPriority);
		// 0x108E22F0: takes the overlay out of the movie
		~FEOverlay();

		// 0x108E2100: registers the callback under the name of a script function unless there is one
		void AddCallback(const char* function, Callback* callback, int call);
		// 0x108E2160
		void RemoveCallback(const char* function);
		// 0x108E21B0: hands a call of the script to the callback registered for it
		void Dispatch(const char* function, int a, int b, int c);

		char* name;  // +0
		char* overlayName;  // +4
		unsigned int priority;  // +8
		FEOverlay* next;  // +0xC
		CallbackEntry* callbacks;  // +0x10
		FrontendMovie* movie;  // +0x14
	};
}

#endif
