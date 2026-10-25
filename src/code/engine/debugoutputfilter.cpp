// The debug output filter (engine::DebugOutputFilter; 0x108D6720 - 0x108D6A80).
#include "code/core/hash.h"
#include "code/core/heap.h"
#include "code/core/report.h"
#include "code/core/strings.h"
#include "code/engine/debugoutputfilter.h"

namespace engine
{
	// 0x108D6720's neighbours in the command line unit
	const char* GetCommandLineValue(const char* option);

	DebugOutputFilter* gDebugOutputFilter;  // 0x11318A24

	void DestroyDebugOutputFilter()
	{
		if (gDebugOutputFilter != 0)
		{
			core::SetReportUserData(0);
			delete gDebugOutputFilter;
			gDebugOutputFilter = 0;
		}
	}

	DebugOutputFilter::~DebugOutputFilter()
	{
	}

	void DebugOutputFilter::ParseFilter()
	{
		dropNone = false;
		dropAll = false;
		tagCount = 0;
		if (filter[0] == 0)
		{
			tags[0] = core::Hash64("Spam", 0);
			return;
		}
		char text[0x80];
		char delimiters[] = " \"|";
		core::StrNCpy(text, filter, 0x80u);
		char* tag = core::StrTok(text, delimiters);
		if (core::StrNCmp(tag, "All", 0x80) == 0)
		{
			dropAll = true;
			return;
		}
		if (core::StrNCmp(tag, "None", 0x80) == 0)
		{
			dropNone = true;
			return;
		}
		while (tag != 0 && tagCount < 5)
		{
			tags[tagCount++] = core::Hash64(tag, 0);
			tag = core::StrTok(0, delimiters);
		}
	}

	void DebugOutputFilter::OnOutput(core::DebugMessage* message)
	{
		char text[0x80];
		core::IDebugOutputHandler* next = core::GetOutputHandler();
		if (next != 0)
		{
			if (message->kind == 0 && !dropNone)
			{
				if (dropAll)
				{
					return;
				}
				char separator[] = " ";
				core::StrNCpy(text, message->tag, 0x80u);
				char* tag = core::StrTok(text, separator);
				if (tagCount > 0)
				{
					while (tag != 0)
					{
						unsigned __int64 hash = core::Hash64(tag, 0);
						for (int i = 0; i < tagCount; i++)
						{
							if (hash == tags[i])
							{
								next->OnOutput(message);
								return;
							}
						}
						tag = core::StrTok(0, separator);
					}
					return;
				}
				while (tag != 0)
				{
					if (core::Hash64(tag, 0) == tags[0])
					{
						return;
					}
					tag = core::StrTok(0, separator);
				}
			}
			next->OnOutput(message);
		}
	}

	void DebugOutputFilter::SetFilter(const char* newFilter)
	{
		if (newFilter != 0)
		{
			core::StrNCpy(filter, newFilter, 0x80u);
		}
		else
		{
			filter[0] = 0;
		}
		ParseFilter();
	}

	DebugOutputFilter::DebugOutputFilter() :
		tagCount(0),
		dropAll(false),
		dropNone(false)
	{
		SetFilter(GetCommandLineValue("DebugFilter"));
	}

	void CreateDebugOutputFilter()
	{
		if (gDebugOutputFilter == 0)
		{
			core::HeapScope scope(0x6F);
			gDebugOutputFilter = new DebugOutputFilter();
			core::SetReportUserData((int)gDebugOutputFilter);
		}
	}
}

// ---- annotations of the functions mapped in symbols.txt (generated) ----

// FUNCTION: ENGINE 0x108D6720 @ void engine::DestroyDebugOutputFilter(void)
// FUNCTION: ENGINE 0x108D6760 @ engine::DebugOutputFilter::~DebugOutputFilter(void)
// FUNCTION: ENGINE 0x108D6770 @ void engine::DebugOutputFilter::ParseFilter(void)
// FUNCTION: ENGINE 0x108D69A0 @ void engine::DebugOutputFilter::SetFilter(char const *)
// FUNCTION: ENGINE 0x108D69E0 @ engine::DebugOutputFilter::DebugOutputFilter(void)
// FUNCTION: ENGINE 0x108D6A10 @ void * engine::DebugOutputFilter::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108D6A30 @ void engine::CreateDebugOutputFilter(void)
