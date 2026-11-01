// The front end's Flash movies: the table of script callbacks (code/engine/frontend/femovie.cpp; the file name is a guess,
// the unit starts at 0x10872860).
#include "code/engine/frontend/femovie.h"
#include "code/core/strings.h"
#include "code/engine/frontend/frontend.h"
#include "code/core/strings.h"
#include "code/engine/system/enginememory.h"
#include "code/engine/updatecontext.h"

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

	// The front end's movie as the units that drive it see it (the object GetFrontend answers); Invoke forwards the call to
	// the Flash movie that sits at +0x2C (0x10872830, a jump into the render unit)
	class FrontendMovie
	{
	public:
		void Invoke(const char* function, const FEMovie::Value* arguments, int count);
	};

	// The front end as the game state sees it: the name of the state it plays (name guess for the class)
	class FrontEnd
	{
	public:
		// 0x10872920: remembers the name and tells the movie to forward to it
		void Unknown10872920(const char* newName);

		int unknown0;
		int unknown4;
		char name[0x20];  // +8
	};

	class FrontendUpdater
	{
	public:
		// 0x10872AD0: advances the movie by the frame's time
		void Unknown10872AD0(UpdateContext context);
	};

	// FUNCTION: ENGINE 0x10872920
	void FrontEnd::Unknown10872920(const char* newName)
	{
		core::StrNCpy(name, newName, 0x20u);
		FEMovie::Value argument;
		argument.type = 4;
		argument.string = newName;
		((FrontendMovie*)this)->Invoke("AS_AutoForward", &argument, 1);
	}

	// FUNCTION: ENGINE 0x10872AD0
	void FrontendUpdater::Unknown10872AD0(UpdateContext context)
	{
		FEMovie::Value argument;
		argument.type = 3;
		argument.number = context.dt;
		((FrontendMovie*)this)->Invoke("AS_Update", &argument, 1);
	}
}
