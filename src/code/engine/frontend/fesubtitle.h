// engine::FESubtitle (RTTI name, vftable 0x10E748E0, 2 slots, base engine::DBObserver; 0x20 bytes): the subtitles of the
// front end. Lines wait in a list (each is formatted with the style its type names, and with its speaker in front) and
// are handed to the movie one at a time with AS_SetSubtitles while AS_SubtitleShow is on. The object watches the
// "SettingAudioSubtitlesEnabled" option, and the command line (NoSubtitle) and the HideHUD option keep it silent. The
// one instance is gSubtitleOptions (0x11316A58). Unit 0x10876B60 - 0x10877140 (no assert path; the directory and file
// name are guesses). The names are guessed except the RTTI one and the movie's functions.
#ifndef ENGINE_FRONTEND_FESUBTITLE_H
#define ENGINE_FRONTEND_FESUBTITLE_H

#include "code/core/name.h"
#include "code/engine/dbobserver.h"
#include "code/engine/gameobject/gameobjectsystem.h"

namespace engine
{
	// A subtitle waiting or showing (0x12C bytes): its text, the format of its style, when it was added and how long it
	// stays (0: the default), its handle and the next one
	struct SubtitleLine
	{
		// 0x10876B60
		SubtitleLine()
		{
			next = 0;
		}

		char text[0x118];
		const char* format;  // +0x118
		unsigned int time;  // +0x11C
		unsigned int duration;  // +0x120
		int handle;  // +0x124
		SubtitleLine* next;  // +0x128
	};

	// The format a line type is shown with (the table the object is made with)
	struct SubtitleStyle
	{
		const core::Name<core::CaseSensitiveKey>* name;
		const char* format;
	};

	class FESubtitle : public DBObserver
	{
	public:
		// 0x10876E00
		FESubtitle(const SubtitleStyle* newStyles, unsigned int newStyleCount);
		// 0x10876EA0
		~FESubtitle();

		// vftable slot 0 (0x10876DD0): the option changed
		virtual void OnDBSlot0(int a, int b);
		// slot 1 (0x10876DF0)
		virtual void OnDBSlot1(int a, int b);

		// 0x10876B70: ends the line that Show answered with the handle
		void Stop(int handle);
		// 0x10876BD0: drops every line and hides the movie's subtitle
		void Clear();
		// 0x10876C40: shows the line that is up, or the next one
		void Update(UpdateContext context);
		// 0x10876EF0
		void SetEnabled(bool enabled);
		// 0x10876F10: the format of the style of that name (the default style's when there is none)
		const char* FindFormat(const core::Name<core::CaseSensitiveKey>& name);
		// 0x10876FB0: puts a line on the list and answers its handle (0 when the subtitles are off)
		int Add(const char* text, const core::Name<core::CaseSensitiveKey>& type,
			const core::Name<core::CaseSensitiveKey>& speaker, unsigned int duration);
		// 0x10877110: the same for a text that may be a key of the text bible
		int Show(const char* text, const core::Name<core::CaseSensitiveKey>& type,
			const core::Name<core::CaseSensitiveKey>& speaker, unsigned int duration);

		const SubtitleStyle* styles;  // +4
		unsigned int styleCount;  // +8
		SubtitleLine* first;  // +0xC
		int count;  // +0x10
		int nextHandle;  // +0x14
		unsigned int shownAt;  // +0x18
		bool showing;  // +0x1C
		bool hidden;  // +0x1D
		bool disabled;  // +0x1E
		bool optionOff;  // +0x1F
	};

	// The type and speaker names the movie subtitle manager passes to Show (0x11316A70 / 0x11316A78, made by another
	// unit's initialiser)
	extern core::Name<core::CaseSensitiveKey> gSubtitleFirstName;
	extern core::Name<core::CaseSensitiveKey> gSubtitleSecondName;
	// The instance (0x11316A58)
	extern FESubtitle* gSubtitleOptions;
}

#endif
