// The front end's Flash movies: the table of script callbacks (code/engine/frontend/femovie.cpp; the file name is a guess,
// the unit starts at 0x10872860).
#include "code/engine/frontend/femovie.h"
#include "code/core/strings.h"
#include "code/engine/frontend/frontend.h"
#include "code/engine/system/enginememory.h"

namespace engine
{
	// A callback bound to an ActionScript function name (the front end heap holds the list)
	struct FEMovieCallbackNode
	{
		FEMovie::Callback* callback;  // +0
		int unknown;  // +4
		char name[32];  // +8
		FEMovieCallbackNode* next;  // +0x28
	};

	FEMovieCallbackNode* gFEMovieCallbacks;  // 0x113166D8

	// FUNCTION: ENGINE 0x10872860
	void FEMovie::AddCallback(const char* name, Callback* callback, int unknown)
	{
		for (FEMovieCallbackNode* node = gFEMovieCallbacks; node != 0; node = node->next)
		{
			if (core::StrCmp(node->name, name) == 0)
			{
				return;
			}
		}
		FEMovieCallbackNode* added = new (GetFrontendHeap()) FEMovieCallbackNode;
		core::StrCpy(added->name, name);
		added->unknown = unknown;
		added->callback = callback;
		added->next = gFEMovieCallbacks;
		gFEMovieCallbacks = added;
	}

	// FUNCTION: ENGINE 0x108728D0
	void FEMovie::RemoveCallback(const char* name)
	{
		FEMovieCallbackNode** link = &gFEMovieCallbacks;
		while (*link != 0)
		{
			if (core::StrCmp((*link)->name, name) == 0)
			{
				FEMovieCallbackNode* removed = *link;
				*link = removed->next;
				delete removed;
				return;
			}
			link = &(*link)->next;
		}
	}
}
