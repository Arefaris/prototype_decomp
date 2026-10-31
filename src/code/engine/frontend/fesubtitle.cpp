// engine::FESubtitle: see the header.
#include "code/engine/frontend/fesubtitle.h"

#include "code/core/strings.h"
#include "code/core/textconvert.h"
#include "code/core/time.h"
#include "code/engine/database/gamedatabase.h"
#include "code/engine/frontend/femovie.h"
#include "code/engine/frontend/frontend.h"

// The engine's allocation from a named heap (0x107DEF90)
void* operator new(unsigned int size, int heap);

namespace core
{
	// 0x1063B990 (the count returning form)
	int SNPrintfCount(char* buffer, int size, const char* format, ...);
}

namespace engine
{
	// The front end's movie as this unit uses it (the object GetFrontend answers; 0x10872830)
	class FrontendMovie
	{
	public:
		void Invoke(const char* name, const FEMovie::Value* arguments, int count);
	};

	// 0x10873F30 / 0x10873F60 (the text bible's unit): the text a key stands for / the name a speaker is shown as
	const char* GetLocalizedText(const char* key);
	const char* GetSpeakerText(const core::Name<core::CaseSensitiveKey>& name);

	// The speaker shown when none is known (0x11316A80) and the style of the lines without one (0x11316A88)
	core::Name<core::CaseSensitiveKey> gSubtitleDefaultSpeakerName("SpeakerNotFoundInTextBible", 0);
	core::Name<core::CaseSensitiveKey> gSubtitleDefaultStyleName("default", 0);

	// A value handed to the movie, laid out as FEMovie::Value without its constructor
	struct ScriptValue
	{
		int type;
		int unknown4;
		union
		{
			const char* string;
			bool flag;
			double number;
		};
	};

	// FUNCTION: ENGINE 0x10876DD0
	void FESubtitle::OnDBSlot0(int a, int b)
	{
		optionOff = *(int*)(b + 8) == 0;
		if (optionOff)
		{
			Clear();
		}
	}

	// FUNCTION: ENGINE 0x10876DF0
	void FESubtitle::OnDBSlot1(int a, int b)
	{
	}

	// FUNCTION: ENGINE 0x10876B70
	void FESubtitle::Stop(int handle)
	{
		for (SubtitleLine* line = first; line != 0; line = line->next)
		{
			if (line->handle == handle)
			{
				if (line->duration == 0)
				{
					unsigned int elapsed = core::GetMilliseconds() - line->time;
					line->duration = elapsed;
					if (elapsed < 1000)
					{
						line->duration = 1000;
					}
				}
				return;
			}
		}
	}

	// FUNCTION: ENGINE 0x10876BD0
	void FESubtitle::Clear()
	{
		while (first != 0)
		{
			SubtitleLine* line = first;
			first = line->next;
			delete line;
		}
		count = 0;
		if (showing)
		{
			showing = false;
			ScriptValue argument;
			argument.type = 2;
			argument.flag = false;
			((FrontendMovie*)GetFrontend())->Invoke("AS_SubtitleShow", (const FEMovie::Value*)&argument, 1);
		}
	}

	// FUNCTION: ENGINE 0x10876C40
	// EQUIVALENT: the engine keeps the two hide sequences apart (different registers), ours lets the compiler merge
	// their identical tails, and the registers differ in the rest, 40.9 %
	void FESubtitle::Update(UpdateContext context)
	{
		ScriptValue toggle;
		ScriptValue text;
		if (showing)
		{
			unsigned int duration = first->duration;
			if (duration == 0)
			{
				duration = 10000;
			}
			if (core::GetMilliseconds() - shownAt < duration)
			{
				return;
			}
			SubtitleLine* done = first;
			SubtitleLine* following = done->next;
			count--;
			first = following;
			delete done;
			if (first == 0)
			{
				showing = false;
				toggle.type = 2;
				toggle.flag = false;
				((FrontendMovie*)GetFrontend())->Invoke("AS_SubtitleShow", (const FEMovie::Value*)&toggle, 1);
				return;
			}
		}
		else
		{
			if (first == 0)
			{
				return;
			}
			showing = true;
			toggle.type = 2;
			toggle.flag = true;
			((FrontendMovie*)GetFrontend())->Invoke("AS_SubtitleShow", (const FEMovie::Value*)&toggle, 1);
		}
		unsigned int now = core::GetMilliseconds();
		SubtitleLine* line = first;
		while (line != 0)
		{
			if (now - line->time < 5000)
			{
				char formatted[1024];
				char converted[0x1000];
				const char* lineText = line->text;
				if (line->format != 0)
				{
					core::SNPrintfCount(formatted, 0x400, line->format, lineText);
					lineText = formatted;
				}
				core::ConvertText(converted, 2, lineText, 1, 0, 0x1000, 0, 0, 0);
				shownAt = core::GetMilliseconds();
				text.type = 5;
				text.string = converted;
				((FrontendMovie*)GetFrontend())->Invoke("AS_SetSubtitles", (const FEMovie::Value*)&text, 1);
				return;
			}
			SubtitleLine* following = line->next;
			count--;
			first = following;
			delete line;
			line = first;
		}
		showing = false;
		toggle.type = 2;
		toggle.flag = false;
		((FrontendMovie*)GetFrontend())->Invoke("AS_SubtitleShow", (const FEMovie::Value*)&toggle, 1);
	}

	// FUNCTION: ENGINE 0x10876E00
	FESubtitle::FESubtitle(const SubtitleStyle* newStyles, unsigned int newStyleCount)
	{
		styles = newStyles;
		styleCount = newStyleCount;
		first = 0;
		count = 0;
		nextHandle = 1;
		shownAt = 0;
		showing = false;
		hidden = false;
		disabled = false;
		optionOff = true;
		gSubtitleOptions = this;
		if (HasCommandLineOption("NoSubtitle") || (char)ShouldHideHUD() != 0)
		{
			hidden = true;
		}
		GameDatabase* database = gGameDatabase;
		DBSubject* subject = database->AddObserver(core::Name<core::CaseSensitiveKey>("SettingAudioSubtitlesEnabled", 0),
			this, 0, 0);
		optionOff = subject->GetDefaultInt() == 0;
	}

	// FUNCTION: ENGINE 0x10876EA0
	FESubtitle::~FESubtitle()
	{
		GameDatabase* database = gGameDatabase;
		database->RemoveObserver(core::Name<core::CaseSensitiveKey>("SettingAudioSubtitlesEnabled", 0), this);
		Clear();
		gSubtitleOptions = 0;
	}

	// FUNCTION: ENGINE 0x10876EF0
	void FESubtitle::SetEnabled(bool enabled)
	{
		disabled = !enabled;
		if (!enabled)
		{
			Clear();
		}
	}

	// FUNCTION: ENGINE 0x10876F10
	// EQUIVALENT: the engine reserves a stack slot that nothing uses and ours does not, one register differs, 55.1 %
	const char* FESubtitle::FindFormat(const core::Name<core::CaseSensitiveKey>& name)
	{
		if (name == gSubtitleFirstName)
		{
			return 0;
		}
		unsigned int total = styleCount;
		unsigned int i = 0;
		if (total > 0)
		{
			const SubtitleStyle* style = styles;
			do
			{
				if (*style->name == name)
				{
					return styles[i].format;
				}
				i++;
				style++;
			}
			while (i < total);
		}
		i = 0;
		if (total > 0)
		{
			const SubtitleStyle* all = styles;
			const SubtitleStyle* style = all;
			do
			{
				if (*style->name == gSubtitleDefaultStyleName)
				{
					return all[i].format;
				}
				i++;
				style++;
			}
			while (i < total);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10876FB0
	int FESubtitle::Add(const char* text, const core::Name<core::CaseSensitiveKey>& type,
		const core::Name<core::CaseSensitiveKey>& speaker, unsigned int duration)
	{
		if ((char)ShouldHideHUD() != 0 || hidden || disabled || optionOff)
		{
			return 0;
		}
		const char* speakerText = 0;
		if (speaker != gSubtitleSecondName)
		{
			speakerText = GetSpeakerText(speaker);
			if (speakerText == 0)
			{
				speakerText = gSubtitleDefaultSpeakerName.GetText();
			}
		}
		const char* format = FindFormat(type);
		SubtitleLine** link = &first;
		while (*link != 0)
		{
			link = &(*link)->next;
		}
		SubtitleLine* line = new (GetFrontendHeap()) SubtitleLine();
		count++;
		*link = line;
		if (duration != 0 && duration < 1000)
		{
			duration = 1000;
		}
		line->format = format;
		line->time = core::GetMilliseconds();
		line->duration = duration;
		line->handle = nextHandle;
		nextHandle++;
		if (nextHandle == 0)
		{
			nextHandle = 1;
		}
		unsigned int room = 0x118;
		char* cursor = line->text;
		if (speakerText != 0)
		{
			int written = core::Utf8Copy(line->text, speakerText, room);
			room -= written;
			cursor = line->text + written;
			int separator = core::Utf8Copy(cursor, " : ", room);
			cursor += separator;
			room -= separator;
		}
		core::Utf8Copy(cursor, text, room);
		return line->handle;
	}

	// FUNCTION: ENGINE 0x10877110
	int FESubtitle::Show(const char* text, const core::Name<core::CaseSensitiveKey>& type,
		const core::Name<core::CaseSensitiveKey>& speaker, unsigned int duration)
	{
		const char* localized = GetLocalizedText(text);
		if (localized == 0)
		{
			localized = text;
		}
		return Add(localized, type, speaker, duration);
	}
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D75E00
// FUNCTION: ENGINE 0x10D75E40
// FUNCTION: ENGINE 0x10D8A7C0
// FUNCTION: ENGINE 0x10D8A7E0


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10876B60
