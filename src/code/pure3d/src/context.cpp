// pure3d::Context (code/pure3d/src/context.cpp, path from the asserts; unit 0x1070E7xx - 0x10710930). Names are
// guesses.
#include "code/container/string.h"
#include "code/content/chunkhandler.h"
#include "code/content/loadinventory.h"
#include "code/content/memorystream.h"
#include "code/core/heap.h"
#include "code/core/strings.h"
#include "code/core/debug.h"
#include "code/engine/display.h"
#include "code/pure3d/context.h"
#include "code/pure3d/drawable.h"
#include "code/pure3d/pddi/dx9/dxcontext.h"
#include "code/pure3d/shadows/shadowrendermanager.h"
#include "code/pure3d/lighting.h"
#include "code/pure3d/loaders/drawableloaders.h"
#include "code/pure3d/pddi.h"
#include "code/pure3d/primitive.h"
#include "code/pure3d/primstream.h"
#include "code/pure3d/protopass.h"
#include "code/pure3d/shaderconstants.h"
#include <math.h>

// The user32 imports, declared as the import-table slots (see core/src/platform.cpp)
extern "C"
{
	extern long (__stdcall* _imp__GetWindowLongA)(void* window, int index);
	extern long (__stdcall* _imp__SetWindowLongA)(void* window, int index, long value);
	extern long (__stdcall* _imp__CallWindowProcA)(long procedure, void* window, unsigned int message,
		unsigned int wParam, long lParam);
	extern int (__stdcall* _imp__GetClientRect)(void* window, void* rect);
	extern int (__stdcall* _imp__GetWindowRect)(void* window, void* rect);
}

// The loaders the debug font's file needs (pure3d::TextureLoader for the chunk 0x19000, 0x14 bytes, and
// pure3d::TextureFontLoader for the chunk 0x22000, 0x10 bytes), the load under way and the file the font is loaded out of
namespace content
{
	// A load under way
	class LoadJob : public core::IRefCount
	{
	public:
		// 0x106089E0: 3 once the load is done
		int GetStatus();
		// 0x106089D0: the inventory the load put its objects in
		LoadInventory* GetInventory();
	};

	// 0x106075F0: lets the loads under way go on
	void UpdateLoads();
}

namespace pure3d
{
	class TextureLoader : public content::SimpleChunkHandler
	{
	public:
		// 0x1072A120
		TextureLoader();
		virtual void LoadObject(core::IRefCount** object, content::ObjectName* name, content::ChunkReader* reader,
			content::LoadInventory* inventory);

		// The object that makes the textures (0x10 bytes)
		void* maker;
	};

	class TextureFontLoader : public content::SimpleChunkHandler
	{
	public:
		// 0x10753B30
		TextureFontLoader();
		virtual void LoadObject(core::IRefCount** object, content::ObjectName* name, content::ChunkReader* reader,
			content::LoadInventory* inventory);
	};

	// The 0x21F0 bytes of the P3D file the debug font is loaded out of (0x10E58E38)
	extern const unsigned char gDebugFontData[0x21F0];
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

	// FUNCTION: ENGINE 0x1070F730
	ContextKey::ContextKey(const ContextKey& other) : name(other.name.hash)
	{
		text = "";
		ownsText = false;
		if (other.ownsText)
		{
			SetText(other.text);
			return;
		}
		text = other.text;
		ownsText = false;
	}

	// FUNCTION: ENGINE 0x107107F0
	void Context::Startup(const ContextSettings& settings)
	{
		OLD_ASSERT_TEXT_AT("..\\..\\..\\code\\pure3d\\src\\context.cpp", 0x5C, context == 0, "pure3d::context == 0");
		context = new Context(settings);
		sWindow = settings.display.window;
		sPreviousWindowProc = (void*)_imp__GetWindowLongA(sWindow, -4);
		_imp__SetWindowLongA(settings.display.window, -4, (long)ContextWindowProc);
	}

	// FUNCTION: ENGINE 0x1070EDA0
	inline WrappedDrawableHelper::WrappedDrawableHelper()
	{
	}

	// FUNCTION: ENGINE 0x107103E0
	// EQUIVALENT: same calls with the same arguments in the same order; the quad index loop keeps a zero-extended copy of its counter in another register and the block that empties the pool when its allocation fails sits after the filling loop, the original's after the construction loop (64.2%)
	Context::Context(const ContextSettings& settings) : ContextTree(0), passes(0), view(0), indexBuffer(0), indexCount(0),
		frame(0), unknown38(false), inFrame(false), frameTime(0, 0), unknown48(0, 0), unknown5C(false), helper(&ownHelper),
		passChain(0), unknown6C(false), frames(0)
	{
		Unknown106DDE80();
		gPddiDx = Unknown1061BBC0();
		gPddiDx->Initialize(&settings.display);
		engine::gDisplay = (engine::Display*)gPddiDx->GetUnknown8();
		if (settings.unknown8)
		{
			Unknown1073E1D0();
		}
		Unknown107063A0();
		Unknown1073E2C0();
		Unknown1073E2E0();
		Unknown1071F7D0();
		switch (settings.displayMode)
		{
		case 1:
			ShadowRenderManager::Create(3);
			break;
		case 2:
			ShadowRenderManager::Create(0);
			break;
		case 3:
			ShadowRenderManager::Create(1);
			break;
		case 4:
			ShadowRenderManager::Create(2);
			break;
		}
		primStream = new PrimStream;
		font = 0;
		LoadDebugFont();
		indexCount = 24000;
		IndexBufferDescription description(24000, 3, 1);
		indexBuffer = gPddiDx->NewIndexBuffer(&description);
		indexBuffer->AddRef();
		dxIndexBufferState state;
		indexBuffer->Lock(&state);
		unsigned short* indices = (unsigned short*)state.unknown10;
		int quads = indexCount / 6;
		for (int quad = 0; quad < quads; quad++)
		{
			int v = quad * 4 + 2;
			*indices++ = v - 2;
			*indices++ = v;
			*indices++ = v - 1;
			*indices++ = v - 2;
			*indices++ = v + 1;
			*indices++ = v;
		}
		indexBuffer->Unlock();
		Unknown1073B790(settings.unknown4);
		ContextRenderSettings renderSettings;
		renderSettings.unknown0 = settings.unknown0;
		renderSettings.unknown4 = settings.unknown150;
		Unknown10755120(&renderSettings);
		Unknown1074D770(this);
		Unknown1073E260(this);
		Unknown107265E0();
		unsigned char version[0x110];
		gPddiDx->GetVersion(version);
		frames.AllocateEmpty(settings.drawableCount);
		for (unsigned int i = 0; i < settings.drawableCount; i++)
		{
			frames[i].inUse = false;
			frames[i].params = new RenderParams;
			frames[i].params->AddRef();
		}
	}

	// FUNCTION: ENGINE 0x107106A0
	Context::~Context()
	{
		delete passChain;
		Unknown107265F0();
		Unknown107076C0(&indexBuffer);
		if (font != 0)
		{
			font->Release();
		}
		Unknown106F36C0();
		Unknown106F36C0();
		Unknown106F36C0();
		Unknown106F3B10();
		Unknown10715380();
		delete primStream;
		primStream = 0;
		Unknown10755EC0();
		Unknown1073A6F0();
		Unknown107168B0();
		Unknown1071B080();
		Unknown1073E2D0();
		Unknown106F4820();
		Unknown1073E2F0();
		Unknown10704B60();
		Unknown1073E1F0();
		passes->Unknown2();
		passes = 0;
		for (MapNode* node = (MapNode*)First(); node != 0; node = (MapNode*)Next(node))
		{
			delete node->pair.value;
			node->pair.value = 0;
		}
		for (unsigned int i = 0; i < frames.Size(); i++)
		{
			frames[i].params->Release();
		}
		engine::gDisplay = 0;
		pddi = 0;
		delete gPddiDx;
		gPddiDx = 0;
		Unknown106DDB60();
	}

	// FUNCTION: ENGINE 0x10710880
	void* Context::DeleteThis(unsigned int flags)
	{
		this->~Context();
		if (flags & 1)
		{
			operator delete(this);
		}
		return this;
	}

	// FUNCTION: ENGINE 0x107108A0
	void Context::Shutdown()
	{
		_imp__SetWindowLongA(sWindow, -4, (long)sPreviousWindowProc);
		OLD_ASSERT_TEXT_AT("..\\..\\..\\code\\pure3d\\src\\context.cpp", 0x77, context != 0, "pure3d::context != 0");
		delete context;
		context = 0;
	}


	// FUNCTION: ENGINE 0x10710120
	ContextSettings::ContextSettings() : unknown0(10000), unknown4(gDefaultSettingsUnknown4), unknown8(true), displayMode(2)
	{
		unknown154 = false;
		unknown158 = 0;
		unknown15C = 0;
		unknown160 = 0;
		unknown164 = 0;
		unknown150 = -1;
		drawableCount = 8;
	}

	// FUNCTION: ENGINE 0x1070F1E0
	void Unknown1070F1E0()
	{
		gDisplay->Unknown1073AA10();
	}

	// FUNCTION: ENGINE 0x1070F1F0
	int Context::GetWindowClientRect(void* rect)
	{
		return _imp__GetClientRect(sWindow, rect);
	}

	// FUNCTION: ENGINE 0x1070F210
	int Context::GetWindowScreenRect(void* rect)
	{
		return _imp__GetWindowRect(sWindow, rect);
	}

	// FUNCTION: ENGINE 0x1070FF50
	RenderContext* Context::FindContext(const unsigned __int64& hash)
	{
		for (MapNode* node = (MapNode*)First(); node != 0; node = (MapNode*)Next(node))
		{
			if (node->pair.key.name.GetHash() == hash)
			{
				return node->pair.value;
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1070FFA0
	void Context::RunContext(const RenderParams* params)
	{
		RenderContext* renderContext = FindContext(params->views[0].contextName.GetHash());
		bool state = pddi->IsUnknown14Set();
		if (!state)
		{
			pddi->Unknown27();
		}
		renderContext->Unknown1();
		renderContext->Run(params);
		renderContext->Unknown2();
		if (!state)
		{
			pddi->Unknown28();
		}
		unknown5C = true;
		float* size = unknown54;
		float width = (float)params->views[0].width;
		float height = (float)params->views[0].height;
		size[0] = width;
		size[1] = height;
		renderContext->Unknown6();
	}

	// FUNCTION: ENGINE 0x10710190
	void Context::RemoveContext(const ContextKey& key)
	{
		Iterator position = Find(key);
		if (position.node != 0)
		{
			RenderContext* renderContext = position->value;
			renderContext->Unknown2();
			delete renderContext;
			Erase(position);
		}
	}

	// FUNCTION: ENGINE 0x107101F0
	bool Context::SetCurrentContext(const unsigned __int64& hash)
	{
		RenderContext* renderContext = FindContext(hash);
		if (renderContext != 0 && passes != renderContext)
		{
			if (passes != 0)
			{
				passes->Unknown2();
			}
			passes = renderContext;
			renderContext->Unknown1();
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10710340
	void Context::AddContext(RenderContext* context)
	{
		if (Find(context->key).node == 0)
		{
			(*this)[context->key] = context;
		}
	}

	// FUNCTION: ENGINE 0x10710370
	bool Context::SetCurrentContext(const ContextKey& key)
	{
		if (Find(key).node == 0)
		{
			return false;
		}
		if (passes != (*this)[key])
		{
			if (passes != 0)
			{
				passes->Unknown2();
			}
			passes = (*this)[key];
			passes->Unknown1();
		}
		return true;
	}

	// The time in microseconds
	inline unsigned __int64 TimeMicroseconds(const core::Time& time)
	{
		return (unsigned __int64)time.milliseconds * 1000 + time.microseconds;
	}

	// The slot of the constant of that name
	inline ConstantSlot FindConstant(const char* text)
	{
		core::Name<core::CaseInsensitiveKey32> name(text, 0);
		core::Name<core::CaseInsensitiveKey32> key(name);
		return ConstantSlot(1, &key);
	}

	// FUNCTION: ENGINE 0x1070F850
	// Hands the shaders the time: the total, the time since the last call and the cosine of the total
	void Context::Unknown1070F850()
	{
		unsigned __int64 total = TimeMicroseconds(frameTime);
		__int64 delta = ((__int64)frameTime.milliseconds - (__int64)unknown48.milliseconds) * 1000 - unknown48.microseconds + frameTime.microseconds;
		float totalSeconds = (float)(total / 1000000) + (float)(total % 1000000) * 0.000001f;
		ConstantSlot elapsedSlot = FindConstant("p3dTimeElapsed");
		ConstantSlot cosSlot = FindConstant("p3dTimeCos");
		*pddi->GetConstant(gConstantTime, pddiBaseContext::CONSTANT_FLOAT) = totalSeconds;
		float deltaSeconds = (float)((unsigned __int64)delta / 1000000) + (float)((unsigned __int64)delta % 1000000) * 0.000001f;
		*pddi->GetConstant(elapsedSlot.index, pddiBaseContext::CONSTANT_FLOAT) = deltaSeconds;
		*pddi->GetConstant(cosSlot.index, pddiBaseContext::CONSTANT_FLOAT) = cosf(totalSeconds);
		unknown48 = frameTime;
	}

	// GLOBAL: ENGINE 0x11281398
	float Context::sTextOffsetX;
	// GLOBAL: ENGINE 0x1128139C
	float Context::sTextOffsetY;

	// FUNCTION: ENGINE 0x1070F380
	// EQUIVALENT: same operations in the same order; the loads of the font and of the constant 0.5 are scheduled differently around the two stores of it (93.1%)
	void Context::DrawDebugText(const char* text, float x, float y, unsigned int colour)
	{
		if (font != 0)
		{
			RenderStateBackup states(pddi, 7, 0);
			ViewMatrixBackup viewMatrix;
			pddi->SetViewUnknown10(2);
			pddi->SetCullMode(0);
			pddi->EnableZBuffer(false);
			sTextOffsetY = 0.5f;
			sTextOffsetX = 0.5f;
			float left = x + sTextOffsetX;
			float top = font->Unknown6() + sTextOffsetY + y;
			math::Matrix matrix;
			matrix.m[0][0] = 1.0f;
			matrix.m[0][1] = 0.0f;
			matrix.m[0][2] = 0.0f;
			matrix.m[0][3] = 0.0f;
			matrix.m[1][0] = 0.0f;
			matrix.m[1][1] = -1.0f;
			matrix.m[1][2] = 0.0f;
			matrix.m[1][3] = 0.0f;
			matrix.m[2][0] = 0.0f;
			matrix.m[2][1] = 0.0f;
			matrix.m[2][2] = 1.0f;
			matrix.m[2][3] = 0.0f;
			matrix.m[3][0] = left;
			matrix.m[3][1] = top;
			matrix.m[3][2] = 1.0f;
			matrix.m[3][3] = 1.0f;
			pddi->SetWorldMatrix(&math::Matrix::IDENTITY);
			pddi->SetViewMatrix(&matrix);
			font->SetColour(colour);
			TextureFont* textFont = font;
			if (text != 0)
			{
				unsigned short wide[0x200];
				textFont->ToWide(text, wide, 0x200);
				textFont->Draw(wide, 0);
			}
		}
	}

	// FUNCTION: ENGINE 0x1070F540
	void Context::DrawDebugTextLine(const char* text, int x, int y, unsigned int colour)
	{
		if (font != 0)
		{
			DrawDebugText(text, (float)x, font->Unknown5() + y - font->Unknown6(), colour);
		}
	}

	// What a load of the debug font's file is asked with: a name over the 256 characters of a string, the stream
	// the file is read from and a few words (0x120 bytes; the engine's constructor is expanded in place)
	struct FontLoadRequest
	{
		FontLoadRequest() : stream(0), unknown108(0), heap(0), unknown110(0), flags(0x400), unknown118(false),
			unknown119(false), unknown11A(0xFFFF), unknown11C(0)
		{
		}

		container::StringC<256> name;
		content::MemoryStream* stream;
		int unknown108;
		int heap;
		int unknown110;
		int flags;
		bool unknown118;
		bool unknown119;
		unsigned short unknown11A;
		int unknown11C;
	};

	// FUNCTION: ENGINE 0x1070FC90
	void Context::LoadDebugFont()
	{
		if (font != 0)
		{
			font->Release();
			font = 0;
		}
		TextureLoader* textureLoader = 0;
		if (content::gLoadManager->GetLoader(0x19000) == 0)
		{
			textureLoader = new (1) TextureLoader;
			content::gLoadManager->AddLoader(textureLoader, 0x19000);
		}
		TextureFontLoader* fontLoader = 0;
		if (content::gLoadManager->GetLoader(0x22000) == 0)
		{
			fontLoader = new (1) TextureFontLoader;
			content::gLoadManager->AddLoader(fontLoader, 0x22000);
		}
		content::MemoryStream* stream = new (1) content::MemoryStream(gDebugFontData, 0x21F0);
		stream->AddRef();
		FontLoadRequest request;
		int length = core::StrLen("dummy.p3d") + 1;
		if (length > 0x100)
		{
			length = 0x100;
		}
		core::StrNCpy(request.name.buffer, "dummy.p3d", (unsigned int)length);
		request.stream = stream;
		request.unknown118 = false;
		request.heap = core::GetCurrentHeap();
		content::LoadJob* job;
		content::gLoadManager->Load(&request.name, &job, true);
		if (job != 0)
		{
			while (job->GetStatus() != 3)
			{
				content::UpdateLoads();
			}
			content::LoadInventory* inventory = job->GetInventory();
			font = inventory->Find<TextureFont>("pure3d_debug_font");
			if (font != 0)
			{
				font->AddRef();
			}
			job->Release();
		}
		stream->Release();
		if (textureLoader != 0)
		{
			content::gLoadManager->RemoveLoader(0x19000);
		}
		if (fontLoader != 0)
		{
			content::gLoadManager->RemoveLoader(0x22000);
		}
	}

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
		Clear();
	}

	// FUNCTION: ENGINE 0x1070EDB0
	void* RenderPassChain::DeleteThis(unsigned int flags)
	{
		this->~RenderPassChain();
		if (flags & 1)
		{
			operator delete(this);
		}
		return this;
	}

	// FUNCTION: ENGINE 0x1070EDD0
	void* dxContext::DeleteThis(unsigned int flags)
	{
		this->~dxContext();
		if (flags & 1)
		{
			operator delete(this);
		}
		return this;
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
	RenderParams* Context::AllocRenderParams()
	{
		for (unsigned int i = 0; i < frames.Size(); i++)
		{
			if (!frames[i].inUse)
			{
				frames[i].inUse = true;
				return frames[i].params;
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1070F600
	void Context::FreeRenderParams(RenderParams* params)
	{
		for (unsigned int i = 0; i < frames.Size(); i++)
		{
			if (frames[i].params == params)
			{
				frames[i].inUse = false;
				return;
			}
		}
	}

	// FUNCTION: ENGINE 0x1070F650
	void Context::UpdateRenderParams()
	{
		for (unsigned int i = 0; i < frames.Size(); i++)
		{
			frames[i].params->Unknown1074F290();
		}
	}

	// FUNCTION: ENGINE 0x1070EE50
	void Context::RunPasses(const RenderParams* params)
	{
		GetParticleManager()->Unknown106EE570();
		if (passes != 0)
		{
			passes->Run(params);
		}
	}

	// The size of the picture a surface holds
	inline unsigned int SurfaceWidth(pddiSurface* surface)
	{
		return surface->info->size->width;
	}

	inline unsigned int SurfaceHeight(pddiSurface* surface)
	{
		return surface->info->size->height;
	}

	// FUNCTION: ENGINE 0x1070EF80
	void Context::RunPassesInto(const TargetParams* params, RenderTarget* colour, RenderTarget* depth)
	{
		OLD_ASSERT_TEXT_AT("..\\..\\..\\code\\pure3d\\src\\context.cpp", 0x316, colour != 0 && colour->surface != 0 && depth != 0 && depth->surface != 0 && colour->surface->info->size->width == depth->surface->info->size->width, "0 != colour && 0 != colour->GetTexture() && 0 != depth && 0 != depth->GetTexture() && colour->GetWidth() == depth->GetWidth()");
		bool state = pddi->IsUnknown14Set();
		if (state)
		{
			pddi->Unknown28();
			engine::gDisplay->Unknown106162D0();
		}
		bool wasInFrame = inFrame;
		if (!wasInFrame)
		{
			pddiSize* size = colour->surface->info->size;
			BeginFrame(size->width, size->height);
		}
		TargetParams targetParams(params);
		targetParams.width = SurfaceWidth(colour->surface);
		targetParams.height = SurfaceHeight(colour->surface);
		targetParams.flags &= ~0x20;
		targetParams.colour = colour->surface;
		targetParams.depth = depth->surface;
		pddi->Unknown27();
		pddiRenderTargets targets = {0, 0, 0, 0, 0};
		targets.depth = depth->surface->GetHandle();
		targets.colour = colour->surface->GetHandle();
		pddi->SetRenderTargets(&targets);
		pddi->Clear(-1);
		pddi->Unknown28();
		engine::gDisplay->Unknown106162D0();
		pddi->Unknown27();
		pddi->Clear(-1);
		RunPasses((const RenderParams*)&targetParams);
		pddi->Unknown28();
		engine::gDisplay->Unknown106162D0();
		if (!wasInFrame)
		{
			EndFrame();
		}
		if (state)
		{
			pddi->Unknown27();
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

	// FUNCTION: ENGINE 0x1070ED90
	core::IRefCount* WrappedDrawableHelper::Wrap(core::IRefCount* drawable)
	{
		return drawable;
	}

	// FUNCTION: ENGINE 0x1070FC60
	// The drawable the name holds in the inventory (the lookup is made with a caster of the drawable type)
	Drawable* WrappedDrawableHelper::FindDrawable(content::LoadInventory* inventory, const content::ObjectName& name)
	{
		content::LoadInventory::DynamicCaster<Drawable> caster;
		return (Drawable*)inventory->FindObject(&caster, name, true);
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

	// The members of the tree and the pool the original keeps out of line
	typedef ContextTree<ContextKey, RenderContext*> EntryTree;
	// FUNCTION: ENGINE 0x1070F680
	template EntryTree::ContextTree(int unused);
	// FUNCTION: ENGINE 0x1070FBA0
	template EntryTree::Pair::Pair(const Pair& other);
	// FUNCTION: ENGINE 0x1070FB40
	template EntryTree::Pair::Pair(const ContextKey& newKey, RenderContext* const& newValue);
	// FUNCTION: ENGINE 0x107102B0
	template bool EntryTree::DeleteNode(container::TreeBase::Node* node, void* context);
	// FUNCTION: ENGINE 0x1070F6D0
	template EntryTree::Pair::~Pair();
	// FUNCTION: ENGINE 0x107100E0
	template EntryTree::MapNode::MapNode(const Pair& newPair);
	// FUNCTION: ENGINE 0x1070F840
	template EntryTree::MapNode::~MapNode();
	// FUNCTION: ENGINE 0x1070F6E0
	template EntryTree::Iterator::Iterator(MapNode* newNode, EntryTree* newMap);
	// FUNCTION: ENGINE 0x1070F690
	template EntryTree::Pair* EntryTree::Iterator::operator->() const;
	// FUNCTION: ENGINE 0x1070F2B0
	template EntryTree::Pair& EntryTree::Iterator::operator*() const;
	// FUNCTION: ENGINE 0x1070F2C0
	template EntryTree::Iterator& EntryTree::Iterator::operator++();
	// FUNCTION: ENGINE 0x1070F6A0
	template EntryTree::Iterator EntryTree::Iterator::operator++(int);
	// FUNCTION: ENGINE 0x1070F270
	template bool EntryTree::Iterator::operator==(const Iterator& other) const;
	// FUNCTION: ENGINE 0x1070F290
	template bool EntryTree::Iterator::operator!=(const Iterator& other) const;
	// FUNCTION: ENGINE 0x1070FAB0
	template int EntryTree::CompareKey(const void* key, const container::TreeBase::Node* node);
	// FUNCTION: ENGINE 0x1070FB60
	template int EntryTree::CompareNodes(const container::TreeBase::Node* a, const container::TreeBase::Node* b);
	// FUNCTION: ENGINE 0x1070FA60
	template EntryTree::Iterator EntryTree::Begin();
	// FUNCTION: ENGINE 0x1070FA80
	template EntryTree::Iterator EntryTree::End();
	// FUNCTION: ENGINE 0x10710090
	template EntryTree::Iterator EntryTree::Find(const ContextKey& key);
	// FUNCTION: ENGINE 0x10710230
	template EntryTree::Iterator EntryTree::Insert(const Pair& pair);
	// FUNCTION: ENGINE 0x10710040
	template EntryTree::Iterator EntryTree::Erase(Iterator position);
	// FUNCTION: ENGINE 0x107102D0
	template RenderContext*& EntryTree::operator[](const ContextKey& key);

	// FUNCTION: ENGINE 0x1070F230
	template ContextArray<FrameEntry>::ContextArray(int unused);
	// FUNCTION: ENGINE 0x1070F330
	template ContextArray<FrameEntry>::ContextArray(FrameEntry* first, FrameEntry* last);
	// FUNCTION: ENGINE 0x1070FAA0
	template ContextArray<FrameEntry>::~ContextArray();
	// FUNCTION: ENGINE 0x1070F250
	template int ContextArray<FrameEntry>::Size() const;
	// FUNCTION: ENGINE 0x1070F260
	template FrameEntry& ContextArray<FrameEntry>::operator[](int index);
	// FUNCTION: ENGINE 0x1070F2E0
	template bool ContextArray<FrameEntry>::Allocate(unsigned int count);
	// FUNCTION: ENGINE 0x1070FAE0
	template bool ContextArray<FrameEntry>::Allocate(unsigned int count, const FrameEntry& value);
	// FUNCTION: ENGINE 0x107100C0
	template bool ContextArray<FrameEntry>::AllocateEmpty(unsigned int count);
	// FUNCTION: ENGINE 0x1070F790
	template FrameEntry* container::ConstructFill<FrameEntry>(FrameEntry* dest, unsigned int count, const FrameEntry& value);
	// FUNCTION: ENGINE 0x1070F360
	template void container::ConstructCopyAt<FrameEntry>(FrameEntry* p, const FrameEntry& value);
	// FUNCTION: ENGINE 0x1070F700
	template int EntryTree::Compare(const ContextKey& a, const ContextKey& b);
	// FUNCTION: ENGINE 0x1070F780
	template void container::Destroy<FrameEntry>(FrameEntry* first, FrameEntry* last);
	// FUNCTION: ENGINE 0x1070F350
	template void container::Destroy<FrameEntry>(FrameEntry* p);
	// FUNCTION: ENGINE 0x1070FC20
	template void container::Destroy<ContextKey>(ContextKey* p);
	// FUNCTION: ENGINE 0x10710110
	template void container::Destroy<EntryTree::MapNode>(EntryTree::MapNode* p);
}

// The members of the lookups of the debug font and of drawables
// FUNCTION: ENGINE 0x1070F7C0
// FUNCTION: ENGINE 0x1070F7D0
template class content::LoadInventory::DynamicCaster<pure3d::Drawable>;
// FUNCTION: ENGINE 0x1070F7F0
// FUNCTION: ENGINE 0x1070F800
template class content::LoadInventory::DynamicCaster<pure3d::TextureFont>;
// FUNCTION: ENGINE 0x1070FBC0
template pure3d::Drawable* content::LoadInventory::Find<pure3d::Drawable>(const content::ObjectName& name);
// FUNCTION: ENGINE 0x1070FBE0
template pure3d::TextureFont* content::LoadInventory::Find<pure3d::TextureFont>(const char* name);
