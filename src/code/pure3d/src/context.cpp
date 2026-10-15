// pure3d::Context (code/pure3d/src/context.cpp, path from the asserts; unit 0x1070E7xx - 0x10710930). Names are
// guesses.
#include "code/core/debug.h"
#include "code/engine/display.h"
#include "code/pure3d/context.h"
#include "code/pure3d/lighting.h"
#include "code/pure3d/pddi.h"
#include "code/pure3d/primitive.h"

// The user32 imports, declared as the import-table slots (see core/src/platform.cpp)
extern "C"
{
	extern long (__stdcall* _imp__GetWindowLongA)(void* window, int index);
	extern long (__stdcall* _imp__SetWindowLongA)(void* window, int index, long value);
	extern long (__stdcall* _imp__CallWindowProcA)(long procedure, void* window, unsigned int message,
		unsigned int wParam, long lParam);
}

namespace pure3d
{
	// GLOBAL: ENGINE 0x11281390
	void* Context::sWindow;
	// GLOBAL: ENGINE 0x11281394
	void* Context::sPreviousWindowProc;

	// FUNCTION: ENGINE 0x1070ED50
	// The window procedure the context puts in place of the display's (it is the context's own, so it sees the
	// window's size changes)
	long __stdcall ContextWindowProc(void* window, unsigned int message, unsigned int wParam, long lParam)
	{
		if (message == 5)
		{
			engine::gDisplay->OnSize(window, message, wParam, lParam);
		}
		return _imp__CallWindowProcA((long)Context::sPreviousWindowProc, window, message, wParam, lParam);
	}

	// FUNCTION: ENGINE 0x107107F0
	void Context::Startup(const ContextSettings& settings)
	{
		OLD_ASSERT_TEXT_AT("..\\..\\..\\code\\pure3d\\src\\context.cpp", 0x5C, context == 0, "pure3d::context == 0");
		context = new Context(settings);
		sWindow = settings.window;
		sPreviousWindowProc = (void*)_imp__GetWindowLongA(sWindow, -4);
		_imp__SetWindowLongA(settings.window, -4, (long)ContextWindowProc);
	}

	// FUNCTION: ENGINE 0x107108A0
	// NONMATCHING: the engine keeps the context in esi across the destructor call and passes the assert's condition
	// register as the report's last argument; ours reloads the global and pushes a constant, 86 %
#ifdef NONMATCHING
	void Context::Shutdown()
	{
		_imp__SetWindowLongA(sWindow, -4, (long)sPreviousWindowProc);
		OLD_ASSERT_TEXT_AT("..\\..\\..\\code\\pure3d\\src\\context.cpp", 0x77, context != 0, "pure3d::context != 0");
		if (context != 0)
		{
			context->~Context();
			operator delete(context);
		}
		context = 0;
	}
#endif


	// FUNCTION: ENGINE 0x1070FEF0
	void Context::AdvanceFrame()
	{
		Unknown1070F850();
		frame++;
		unknown38 = true;
		pddi->Unknown27();
		pddi->SetWorldMatrix(&math::Matrix::IDENTITY);
		if (inFrame == 0)
		{
			gDisplay->SetSize(0, 0);
		}
		gDisplay->Unknown1073B450();
	}

	// FUNCTION: ENGINE 0x107103D0
	void Context::ClearEntries()
	{
		container::TreeBase::Clear(DeleteContextEntry, this);
	}

	// FUNCTION: ENGINE 0x1070EDF0
	void Context::UpdatePassChain()
	{
		if (passChain != 0)
		{
			passChain->Update();
		}
	}

	// FUNCTION: ENGINE 0x1070F1B0
	void Context::Unknown1070F1B0()
	{
		engine::gDisplay->Unknown106162D0();
		Unknown106F36C0();
	}

	// FUNCTION: ENGINE 0x1070F1C0
	void Context::AddFrameTime(core::Time time)
	{
		frameTime.Add(time.milliseconds, time.microseconds);
	}

	// FUNCTION: ENGINE 0x1070F590
	void Context::Unknown1070F590(bool value)
	{
		Unknown10714DF0();
		pddi->Unknown28();
		unknown38 = false;
		if (value)
		{
			Unknown1070F1B0();
		}
	}

	// FUNCTION: ENGINE 0x1070F5C0
	// NONMATCHING: the engine keeps the free entry's address in edx and the count signed (sar); ours walks with
	// an index and the entry accessor, 6 %
#ifdef NONMATCHING
	RenderParams* Context::AllocRenderParams()
	{
		unsigned int count = RenderParamsCount();
		unsigned int index = 0;
		if (count == 0)
		{
			return 0;
		}
		FrameEntry* entry = RenderParamsEntry(0);
		while (entry->inUse)
		{
			index++;
			entry++;
			if (index >= RenderParamsCount())
			{
				return 0;
			}
		}
		RenderParamsEntry(index)->inUse = true;
		return RenderParamsEntry(index)->params;
	}
#endif

	// FUNCTION: ENGINE 0x1070F600
	// NONMATCHING: as AllocRenderParams (the engine keeps the running entry pointer in edx and the count signed),
	// 6 %
#ifdef NONMATCHING
	void Context::FreeRenderParams(RenderParams* params)
	{
		unsigned int count = RenderParamsCount();
		if (count == 0)
		{
			return;
		}
		unsigned int index = 0;
		FrameEntry* entry = RenderParamsEntry(0);
		do
		{
			if (entry->params == params)
			{
				RenderParamsEntry(index)->inUse = false;
				return;
			}
			index++;
			entry++;
		}
		while (index < RenderParamsCount());
	}
#endif

	// FUNCTION: ENGINE 0x1070F650
	// NONMATCHING: the engine keeps the pool's begin in a register and the count signed, ours reloads them, 10 %
#ifdef NONMATCHING
	void Context::UpdateRenderParams()
	{
		for (unsigned int i = 0; i < RenderParamsCount(); i++)
		{
			RenderParamsEntry(i)->params->Unknown1074F290();
		}
	}
#endif

	// FUNCTION: ENGINE 0x1070EE50
	void Context::RunPasses(const RenderParams* params)
	{
		GetParticleManager()->Unknown106EE570();
		if (passes != 0)
		{
			passes->Run(params);
		}
	}

	// FUNCTION: ENGINE 0x1070EE70
	void Context::BeginFrame(unsigned int width, unsigned int height)
	{
		if (!inFrame)
		{
			bool state = pddi->IsUnknown14Set();
			if (state)
			{
				pddi->Unknown28();
				engine::gDisplay->Unknown106162D0();
			}
			gDisplay->SetSize(width, height);
			passes->Unknown2();
			passes->Unknown1();
			engine::gDisplay->Unknown106162D0();
			if (state)
			{
				pddi->Unknown27();
			}
			inFrame = true;
		}
	}

	// FUNCTION: ENGINE 0x1070EF00
	void Context::EndFrame()
	{
		if (inFrame)
		{
			bool state = pddi->IsUnknown14Set();
			if (state)
			{
				pddi->Unknown28();
				engine::gDisplay->Unknown106162D0();
			}
			gDisplay->SetSize(0, 0);
			passes->Unknown2();
			passes->Unknown1();
			engine::gDisplay->Unknown106162D0();
			if (state)
			{
				pddi->Unknown27();
			}
			inFrame = false;
		}
	}

	// FUNCTION: ENGINE 0x1070EDA0
	WrappedDrawableHelper::WrappedDrawableHelper()
	{
	}

	// FUNCTION: ENGINE 0x1070ED90
	int WrappedDrawableHelper::GetUnknown0(int value)
	{
		return value;
	}

	// The second slot: an empty function (the original's address is not known)
	void WrappedDrawableHelper::Unknown1()
	{
	}

	// FUNCTION: ENGINE 0x1070EE00
	void Context::SetView(View* value)
	{
		view = value;
	}

	// FUNCTION: ENGINE 0x1070EE10
	View* Context::GetView()
	{
		return view;
	}

	// FUNCTION: ENGINE 0x1070EE20
	WrappedDrawableHelper* Context::GetWrappedDrawableHelper()
	{
		return helper;
	}

	// FUNCTION: ENGINE 0x1070EE30
	void Context::SetWrappedDrawableHelper(WrappedDrawableHelper* value)
	{
		if (value == 0)
		{
			value = &ownHelper;
		}
		helper = value;
	}

	// FUNCTION: ENGINE 0x1070F170
	bool Context::GetUnknown5C()
	{
		return unknown5C;
	}

	// FUNCTION: ENGINE 0x1070F180
	void Context::SetUnknown5C(bool value)
	{
		unknown5C = value;
	}

	// FUNCTION: ENGINE 0x1070F190
	void* Context::GetUnknown54()
	{
		return &unknown54;
	}

	// FUNCTION: ENGINE 0x1070F1A0
	Context* Context::GetUnknown1070F1A0()
	{
		return this;
	}
}
