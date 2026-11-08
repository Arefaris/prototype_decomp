// The overlays of the front end's movie (unit 0x108E2100 - 0x108E2630; no assert path, file name guessed).
#include "code/engine/frontend/feoverlay.h"
#include "code/engine/frontend/frontend.h"
#include "code/core/strings.h"
#include <string.h>
#include "code/engine/system/enginememory.h"

namespace engine
{
	// A value handed to the movie, laid out as FEMovie::Value without its constructor
	struct OverlayValue
	{
		int type;
		int unknown4;
		union
		{
			const char* string;
			double number;
		};
	};

	// FUNCTION: ENGINE 0x108E2100
	void FEOverlay::AddCallback(const char* function, Callback* callback, int call)
	{
		for (CallbackEntry* entry = callbacks; entry != 0; entry = entry->next)
		{
			if (core::StrCmp(entry->name, function) == 0)
			{
				return;
			}
		}
		CallbackEntry* entry = (CallbackEntry*)operator new(sizeof(CallbackEntry), GetFrontendHeap());
		core::StrCpy(entry->name, function);
		entry->call = call;
		entry->callback = callback;
		entry->next = callbacks;
		callbacks = entry;
	}

	// FUNCTION: ENGINE 0x108E2160
	void FEOverlay::RemoveCallback(const char* function)
	{
		for (CallbackEntry** link = &callbacks; *link != 0; link = &(*link)->next)
		{
			if (core::StrCmp((*link)->name, function) == 0)
			{
				CallbackEntry* entry = *link;
				*link = entry->next;
				operator delete(entry);
				return;
			}
		}
	}

	// FUNCTION: ENGINE 0x108E21B0
	void FEOverlay::Dispatch(const char* function, int a, int b, int c)
	{
		for (CallbackEntry* entry = callbacks; entry != 0; entry = entry->next)
		{
			if (core::StrCmp(entry->name, function) == 0)
			{
				entry->callback->OnCall(entry->call, a, b, c);
				return;
			}
		}
	}

	// FUNCTION: ENGINE 0x108E2200
	FEOverlay::FEOverlay(FrontendMovie* newMovie, const char* newName, const char* newOverlayName,
		unsigned int newPriority)
	{
		priority = newPriority;
		next = 0;
		callbacks = 0;
		movie = newMovie;
		name = new (GetFrontendHeap()) char[strlen(newName) + 1];
		core::StrCpy(name, newName);
		overlayName = new (GetFrontendHeap()) char[strlen(newOverlayName) + 1];
		core::StrCpy(overlayName, newOverlayName);
		next = movie->overlays;
		movie->overlays = this;
		OverlayValue arguments[3];
		arguments[0].type = 4;
		arguments[0].string = name;
		arguments[1].type = 4;
		arguments[1].string = overlayName;
		arguments[2].type = 3;
		arguments[2].number = priority;
		movie->Invoke("AS_CreateOverlay", (const FEMovie::Value*)arguments, 3);
	}

	// FUNCTION: ENGINE 0x108E22F0
	FEOverlay::~FEOverlay()
	{
		FEOverlay** link = &movie->overlays;
		while (*link != this)
		{
			link = &(*link)->next;
		}
		*link = (*link)->next;
		OverlayValue arguments[2];
		arguments[0].type = 4;
		arguments[0].string = name;
		arguments[1].type = 4;
		arguments[1].string = overlayName;
		movie->Invoke("AS_DestroyOverlay", (const FEMovie::Value*)arguments, 2);
		operator delete[](name);
		operator delete[](overlayName);
	}
}
