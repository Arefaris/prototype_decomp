#include "code/proto/frontend/fehudtypewriter.h"

#include "code/core/textconvert.h"
#include "code/engine/frontend/femovie.h"
#include "code/engine/function.h"
#include "code/engine/luascriptmanager.h"

namespace engine
{
	class FrontEnd;
	// 0x10864330
	FrontEnd* Unknown10864330();
	// 0x10872840: calls a function of the front end's movie with a format and the arguments it names (name unknown)
	void Unknown10872840(FrontEnd* frontEnd, const char* function, const char* format, ...);
	// 0x10883920 (valueformat.cpp)
	bool TranslateValue(const FEMovie::Value* value, int unused, FEMovie::Value* result, char* target, int size);
	// 0x108388A0 / 0x10837A50
	void AddRealTimeTask(IRealTimeTask* task, unsigned int mask, int priority, unsigned int data);
	void RemoveRealTimeTask(IRealTimeTask* task);
}

namespace choreo
{
	// 0x10D94FF8
	extern const float gMinusOne;
}

namespace proto
{
	// 0x1109B434: the movie clip of the typewriter
	static const char* sTypewriterClip = "mcAnchor.typewriterHUD";
	// 0x1126E168
	static int sUnknown1126E168 = 0;

	// FUNCTION: ENGINE 0x104DA760
	// NONMATCHING: the engine loads the minus one before the argument of SetTaskActive and the stores follow in the declaration order (583 bytes against 581)
#ifdef NONMATCHING
	FEHUDTypewriter::FEHUDTypewriter() : text("_level0.mcAnchor.typewriterHUD.mcTextWrapper.typeTxt.text"),
		shadowText("_level0.mcAnchor.typewriterHUD.mcShadowText.typeTxt.text"),
		visible("_level0.mcAnchor.typewriterHUD._visible"), unknown380(0.0f), unknown384(0.0f), unknown388(0.0f), state(4),
		taskActive(false), characterCount(0), unknown1398(0), unknown139C(false), unknown13A4(choreo::gMinusOne), unknown13A8(choreo::gMinusOne),
		unknown13B0(false), unknown13B1(true)
	{
		SetTaskActive(true);
		unknown13A0 = 0.025f;
		unknown13A4 = 2.0f;
		state = 4;
		unknown13AC = 0.4f;
		engine::LuaScriptManager* manager = engine::GetScriptManager();
		manager->SetOwner(this);
		manager->RegisterMethod("fe_StartTypeWriter", this, &FEHUDTypewriter::Start);
		manager->RegisterMethod("fe_SetTypeWriterSpeeds", this, &FEHUDTypewriter::SetSpeeds);
		manager->RegisterMethod("fe_TypeWriterOutroComplete", this, &FEHUDTypewriter::OutroComplete);
		manager->RegisterMethod("fe_StopTypeWriter", this, &FEHUDTypewriter::Stop);
		manager->RegisterMethod("fe_GetIsTypeWriterActive", this, &FEHUDTypewriter::IsActive);
		manager->ClearOwner();
		visible.Set(FlashValue(false));
	}
#endif

	// FUNCTION: ENGINE 0x104DA160
	FEHUDTypewriter::~FEHUDTypewriter()
	{
		engine::LuaScriptManager* manager = engine::GetScriptManager();
		manager->Unregister(this);
		SetTaskActive(false);
		sUnknown1126E168 = 0;
	}

	// FUNCTION: ENGINE 0x104D9740
	void FEHUDTypewriter::Update(bool force)
	{
		text.Flush(force);
		shadowText.Flush(force);
		visible.Flush(force);
	}

	// FUNCTION: ENGINE 0x104D9A90
	void FEHUDTypewriter::SetTaskActive(bool active)
	{
		if (active)
		{
			if (!taskActive)
			{
				engine::AddRealTimeTask(this, 1, 1, (unsigned int)"FEHudPowers Task");
				taskActive = true;
			}
		}
		else
		{
			if (taskActive)
			{
				engine::RemoveRealTimeTask(this);
				taskActive = false;
			}
			if (state == 3)
			{
				OutroComplete();
			}
		}
	}

	// FUNCTION: ENGINE 0x104D9790
	void FEHUDTypewriter::Start(const char* key, float new13A8, float new13A4, float unused1, const char* unused2,
		float unused3, const char* unused4)
	{
		unknown13A4 = new13A4;
		unknown13A8 = new13A8;
		engine::FEMovie::Value input;
		engine::FEMovie::Value output;
		input.type = 4;
		input.string = key;
		if (engine::TranslateValue(&input, 1, &output, (char*)buffer, 0x400))
		{
			unsigned int bytes;
			characterCount = core::Utf16Count(buffer, &bytes);
			engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s", sTypewriterClip, "StartTypeWriter");
			unknown1398 = 0;
			state = 0;
			unknown388 = 0.0f;
			unknown380 = 0.0f;
			unknown384 = 0.0f;
			unknown13B1 = true;
		}
	}

	// FUNCTION: ENGINE 0x104D98A0
	void FEHUDTypewriter::StartText(const char* key, float new13A8, float new13A4, bool newUnknown13B1)
	{
		Start(key, new13A8, new13A4, 0.0f, "", 0.0f, "");
		unknown13B1 = newUnknown13B1;
	}

	// FUNCTION: ENGINE 0x104D9900
	void FEHUDTypewriter::Stop()
	{
		if (state != 4)
		{
			if (unknown13B1)
			{
				state = 3;
				engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s", sTypewriterClip, "StopTypeWriter");
			}
			else
			{
				state = 4;
			}
			state = (unknown13B1 ? -1 : 0) + 4;
		}
	}

	// FUNCTION: ENGINE 0x104D99C0
	void FEHUDTypewriter::OutroComplete()
	{
		if (state == 3)
		{
			state = 4;
			visible.Set(FlashValue(false));
			visible.Flush(true);
		}
	}

	// FUNCTION: ENGINE 0x104D9990
	void FEHUDTypewriter::SetSpeeds(float new13A0, float new13AC)
	{
		unknown13A0 = new13A0;
		unknown13AC = new13AC;
	}

	// FUNCTION: ENGINE 0x104D9980
	bool FEHUDTypewriter::IsActive()
	{
		return state != 4;
	}

	// FUNCTION: ENGINE 0x104D9780
	void FEHUDTypewriter::SetUnknown13B0(bool value)
	{
		unknown13B0 = value;
	}
}
