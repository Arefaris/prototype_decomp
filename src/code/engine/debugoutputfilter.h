// engine::DebugOutputFilter (RTTI name): an output handler that sits in front of the debug output chain and drops the
// messages whose tag the command line option DebugFilter does not let through. The option is a list of tags (up to
// five, separated by spaces, quotes or bars), or All (drop every message) or None (drop nothing); without the option
// only the tag Spam is dropped. Unit 0x108D6720 - 0x108D6A80 (no assert path; the file name is a guess). The member
// names are guesses.
#ifndef ENGINE_DEBUGOUTPUTFILTER_H
#define ENGINE_DEBUGOUTPUTFILTER_H

#include "code/core/crashrecord.h"

namespace engine
{
	class DebugOutputFilter : public core::IDebugOutputHandler
	{
	public:
		// 0x108D69E0: takes the filter from the command line
		DebugOutputFilter();
		// 0x108D6760 (the deleting destructor 0x108D6A10)
		virtual ~DebugOutputFilter();

		// vftable slot 0 (0x108D6870): passes the message on to the chain unless its tag is filtered
		virtual void OnOutput(core::DebugMessage* message);

		// 0x108D69A0: sets the filter text and reads it
		void SetFilter(const char* filter);
		// 0x108D6770: reads the tags of the filter text
		void ParseFilter();

		unsigned __int64 tags[5];  // +8: the hashes of the tags that pass
		int tagCount;  // +0x30
		bool dropAll;  // +0x34
		bool dropNone;  // +0x35
		char filter[0x80];  // +0x36
	};

	// The one filter (0x11318A24)
	extern DebugOutputFilter* gDebugOutputFilter;
	// 0x108D6A30 / 0x108D6720: make it in heap 0x6F and register it as the report user data, and take it down
	void CreateDebugOutputFilter();
	void DestroyDebugOutputFilter();
}

#endif
