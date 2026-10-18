// pure3d::Context (code/pure3d/src/context.cpp, path from the asserts; unit 0x1070E7xx - 0x10710930). Names are
// guesses.
#include "code/content/loadinventory.h"
#include "code/core/debug.h"
#include "code/engine/display.h"
#include "code/pure3d/context.h"
#include "code/pure3d/drawable.h"
#include "code/pure3d/pddi/dx9/dxcontext.h"
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
	extern int (__stdcall* _imp__GetClientRect)(void* window, void* rect);
	extern int (__stdcall* _imp__GetWindowRect)(void* window, void* rect);
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
