#include "code/proto/frontend/fehudtextlog.h"

#include "code/core/textconvert.h"
#include "code/engine/function.h"
#include "code/engine/luascriptmanager.h"

namespace engine
{
	// 0x10873F30: the localised text of an identifier
	const char* GetLocalizedText(const char* key);
}

namespace proto
{
	// 0x1126D8B0 / 0x1126D8A8: the log's text (UTF-16) and where it ends
	unsigned short gLogBuffer[0x200];
	unsigned short* gLogEnd;

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
		gLogEnd = gLogBuffer;
		gLogBuffer[0] = 0;
	}

	// FUNCTION: ENGINE 0x104D2D20
	void FEHudTextLog::Add(const char* newText, bool newline)
	{
		unsigned int room = 0x200 - (gLogEnd - gLogBuffer);
		room -= newline ? 2 : 1;
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
		core::Utf16Copy(gLogEnd, converted, room);
		gLogEnd += bytes >> 1;
		if (newline)
		{
			*gLogEnd = 10;
			gLogEnd++;
		}
		*gLogEnd = 0;
	}

	// FUNCTION: ENGINE 0x104D3090
	void FEHudTextLog::Close()
	{
		logVisible.Set(FlashValue(active));
		text.Set(FlashValue((const wchar_t*)gLogBuffer));
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

	// FUNCTION: ENGINE 0x104D38F0
	FEHudTextLog::FEHudTextLog() : text("_level0.mcAnchor.textlogHUD.mcText.htmlText"),
		logVisible("_level0.mcAnchor.textlogHUD._visible"), active(true),
		timerVisible("_level0.mcAnchor.timerHUD._visible"), timerTextVisible("_level0.mcAnchor.timerHUD.mcText._visible"),
		timerShadowVisible("_level0.mcAnchor.timerHUD.mcShadowText._visible"),
		timerBackgroundVisible("_level0.mcAnchor.timerHUD.mcBG._visible"),
		timerText("_level0.mcAnchor.timerHUD.mcText.text.htmlText"),
		timerShadowText("_level0.mcAnchor.timerHUD.mcShadowText.text.htmlText")
	{
		timerVisible.Set(FlashValue(true));
		timerTextVisible.Set(FlashValue(false));
		timerShadowVisible.Set(FlashValue(false));
		timerBackgroundVisible.Set(FlashValue(false));
		ClearTimerText();
		Hide();
		engine::LuaScriptManager* manager = engine::GetScriptManager();
		manager->SetOwner(this);
		manager->RegisterMethod("fehudtextlog_SetText", this, &FEHudTextLog::SetText);
		manager->RegisterMethod("fehudtextlog_Clear", this, &FEHudTextLog::Clear);
		manager->RegisterMethod("fehudtextlog_Add", this, &FEHudTextLog::Add);
		manager->RegisterMethod("fehudtextlog_Close", this, &FEHudTextLog::Close);
		manager->RegisterMethod("fehudtextlog_Hide", this, &FEHudTextLog::Hide);
		manager->RegisterMethod("fehudtimer_SetText", this, &FEHudTextLog::SetTimerText);
		manager->RegisterMethod("fehudtimer_ClearText", this, &FEHudTextLog::ClearTimerText);
		manager->ClearOwner();
	}
}
