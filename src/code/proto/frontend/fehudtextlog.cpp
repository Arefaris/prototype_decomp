#include "code/proto/frontend/fehudtextlog.h"

#include "code/core/textconvert.h"
#include "code/engine/luascriptmanager.h"

namespace engine
{
	// 0x10873F30: the localised text of an identifier
	const char* GetLocalizedText(const char* key);
}

namespace proto
{
	// 0x1126D8B0 / 0x1126D8A8: the log's text (UTF-16) and where it ends
	static unsigned short sLogBuffer[0x200];
	static unsigned short* sLogEnd;

	// FUNCTION: ENGINE 0x104D2F60
	FEHudTextLog::~FEHudTextLog()
	{
		engine::LuaScriptManager* manager = engine::GetScriptManager();
		manager->Unregister(this);
	}

	// FUNCTION: ENGINE 0x104D2C70
	void FEHudTextLog::Update(bool force)
	{
		text.Flush(force);
		logVisible.Flush(force);
		timerText.Flush(force);
		timerShadowText.Flush(force);
		timerVisible.Flush(force);
		timerTextVisible.Flush(force);
		timerShadowVisible.Flush(force);
		timerBackgroundVisible.Flush(force);
	}

	// FUNCTION: ENGINE 0x104D3110
	void FEHudTextLog::OnShow(bool shown)
	{
		SetActive(shown);
	}

	// FUNCTION: ENGINE 0x104D2E50
	void FEHudTextLog::SetActive(bool newActive)
	{
		active = newActive;
		if (!newActive)
		{
			logVisible.Set(FlashValue(newActive));
			logVisible.Flush(true);
		}
		timerVisible.Set(FlashValue(newActive));
	}

	// FUNCTION: ENGINE 0x104D3000
	void FEHudTextLog::SetText(const char* newText)
	{
		logVisible.Set(FlashValue(active));
		text.Set(FlashValue(newText));
	}

	// FUNCTION: ENGINE 0x104D2D00
	void FEHudTextLog::Clear()
	{
		sLogEnd = sLogBuffer;
		sLogBuffer[0] = 0;
	}

	// FUNCTION: ENGINE 0x104D2D20
	// NONMATCHING: the engine does not fold the reserved characters into the constant (0x200 - used - (newline + 1)), 44 %
#ifdef NONMATCHING
	void FEHudTextLog::Add(const char* newText, bool newline)
	{
		unsigned int room = 0x200 - (sLogEnd - sLogBuffer);
		unsigned int reserved = (newline != false) + 1;
		room -= reserved;
		if (*newText == '$')
		{
			newText = engine::GetLocalizedText(newText + 1);
			if (newText == 0)
			{
				newText = "<BAD>";
			}
		}
		unsigned short converted[0x200];
		core::ConvertText(converted, core::ENCODING_UTF16, newText, core::ENCODING_UTF8, 0, room, 0, 0, 0);
		unsigned int bytes;
		core::Utf16Count(converted, &bytes);
		core::Utf16Copy(sLogEnd, converted, room);
		sLogEnd += bytes >> 1;
		if (newline)
		{
			*sLogEnd = 10;
			sLogEnd++;
		}
		*sLogEnd = 0;
	}
#endif

	// FUNCTION: ENGINE 0x104D3090
	void FEHudTextLog::Close()
	{
		logVisible.Set(FlashValue(active));
		text.Set(FlashValue((const wchar_t*)sLogBuffer));
		text.Flush(true);
	}

	// FUNCTION: ENGINE 0x104D2E20
	void FEHudTextLog::Hide()
	{
		logVisible.Set(FlashValue(false));
	}

	// FUNCTION: ENGINE 0x104D3120
	void FEHudTextLog::SetTimerText(char* newText, char* newShadowText)
	{
		timerText.Set(FlashValue(newText));
		timerShadowText.Set(FlashValue(newShadowText));
		timerTextVisible.Set(FlashValue(true));
		timerShadowVisible.Set(FlashValue(true));
		timerBackgroundVisible.Set(FlashValue(true));
	}

	// FUNCTION: ENGINE 0x104D3240
	void FEHudTextLog::ClearTimerText()
	{
		timerText.Set(FlashValue(" "));
		timerShadowText.Set(FlashValue(" "));
		timerTextVisible.Set(FlashValue(false));
		timerShadowVisible.Set(FlashValue(false));
		timerBackgroundVisible.Set(FlashValue(false));
	}
}
