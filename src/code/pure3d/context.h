// pure3d::Context (code/pure3d/src/context.cpp; asserts "pure3d::context == 0" and "pure3d::context != 0"): the render
// context, one instance at pure3d::context (0x1127F350, 0x7C bytes, made by Context::Startup). It keeps the frame's
// times, the view, the passes' context and the wrapped drawable helper (the class is defined in the same file), and it
// drives a frame with BeginFrame / EndFrame. The layout was read off the constructor; the member names are guesses.
#ifndef PURE3D_CONTEXT_H
#define PURE3D_CONTEXT_H

#include "code/container/map.h"
#include "code/core/time.h"

namespace pure3d
{
	class PrimStream;
	class View;

	// The hook the engine's renderer installs on a pure3d drawable (engine::render::EngineWrappedDrawableHelper
	// derives from it); the context keeps one at +0x64 and hands it out through GetWrappedDrawableHelper. Vftable
	// 0x10E5B114 (two slots); the meaning of the slots is unknown.
	class WrappedDrawableHelper
	{
	public:
		// 0x1070EDA0
		WrappedDrawableHelper();
		// 0x1070ED90
		virtual int GetUnknown0(int value);
		virtual void Unknown1();
	};

	class RenderParams;

	// What Context::Startup is given: the display's mode at +0xC, the window the display is created on at +0x10 and
	// the number of the scene's drawables at +0x16C (only the members this unit reads are named, and they are
	// guesses).
	struct ContextSettings
	{
		int unknown0;
		int unknown4;
		bool unknown8;
		unsigned char unknown9[3];
		// 1 - 4: selects one of the four settings of the render device
		int displayMode;
		void* window;
		unsigned char unknown14[0x13C];
		int unknown150;
		unsigned char unknown154[0x18];
		int drawableCount;
	};

	// The passes' runner at +0x1C: the frame is opened and closed through it and the passes themselves run with the
	// frame's render parameters (0x1074D880). Only what this unit calls is reconstructed.
	class RenderContext
	{
	public:
		virtual void Unknown0();
		virtual void Unknown1();
		virtual void Unknown2();
		// 0x1074D880
		void Run(const RenderParams* params);
	};

	// The chain of render passes the context's frame runs (the object at +0x68); 0x1074D650 walks the passes of
	// the chain. Only what this unit calls is reconstructed and the name is a guess.
	class RenderPassChain
	{
	public:
		// 0x1074D650
		void Update();
	};

	class Context : public container::TreeBase
	{
	public:
		// One entry of the frame pool: the object it hands out and whether the entry is in use
		struct FrameEntry
		{
			bool inUse;
			unsigned char unknown1[3];
			RenderParams* params;
		};

		// 0x1070F5C0 / 0x1070F600 / 0x1070F650: the frame pool at +0x70
		RenderParams* AllocRenderParams();
		void FreeRenderParams(RenderParams* params);
		void UpdateRenderParams();
		// The pool is kept as bytes, eight per entry (the entries' construction in the constructor)
		unsigned int RenderParamsCount() const
		{
			return (unsigned int)(framesEnd - frames) >> 3;
		}
		FrameEntry* RenderParamsEntry(unsigned int index) const
		{
			return (FrameEntry*)(frames + index * 8);
		}
		// 0x1070FEF0: advances the frame (the frame number, the device's matrices and the display)
		void AdvanceFrame();
		// 0x1070F850 (not reconstructed yet): prepares the frame's state
		void Unknown1070F850();
		// 0x107103D0: takes every entry out of the context's tree
		void ClearEntries();
		// 0x1070EDF0: updates the passes' chain (nothing when there is none)
		void UpdatePassChain();
		// 0x10714DF0 (another unit): starts the frame's state
		void Unknown10714DF0();
		// 0x1070F1B0 / 0x1070F590 / 0x1070F1C0
		void Unknown1070F1B0();
		void Unknown1070F590(bool value);
		void AddFrameTime(core::Time time);
		// 0x107103E0 / 0x107106A0
		explicit Context(const ContextSettings& settings);
		~Context();
		// 0x107107F0 / 0x107108A0: makes / releases the one context and puts the window procedure in place
		static void Startup(const ContextSettings& settings);
		static void Shutdown();
		// 0x1070EE70 / 0x1070EF00: opens and closes a frame (the size of the display), if it is not already open
		void BeginFrame(unsigned int width, unsigned int height);
		void EndFrame();
		// 0x1070EE50: runs the passes with the frame's render parameters
		void RunPasses(const RenderParams* params);
		// 0x1070EE00 / 0x1070EE10: the view at +0x28
		void SetView(View* value);
		View* GetView();
		// 0x1070EE20 / 0x1070EE30: the helper at +0x60, the context's own one when the argument is null
		WrappedDrawableHelper* GetWrappedDrawableHelper();
		void SetWrappedDrawableHelper(WrappedDrawableHelper* value);
		// 0x1070F170 / 0x1070F180
		bool GetUnknown5C();
		void SetUnknown5C(bool value);
		// 0x1070F190: the address of the 8-byte member at +0x54
		void* GetUnknown54();
		// 0x1070F1A0
		Context* GetUnknown1070F1A0();

		unsigned char unknown18[4];
		// The render passes' context (+0x1C), the primitive stream (+0x20) and the state of the frame being built
		RenderContext* passes;
		PrimStream* primStream;
		void* unknown24;
		View* view;
		void* unknown2C;
		// The maximum frame time, 24000 (milliseconds)
		unsigned int unknown30;
		// The number of the frame being built
		unsigned int frame;
		bool unknown38;
		// Set while the frame is being built (0x1070EE70 / 0x1070EF00)
		bool inFrame;
		// The time of the frame and its second half (a second time for the frame's start)
		core::Time frameTime;
		core::Time unknown48;
		unsigned char unknown54[8];
		bool unknown5C;
		WrappedDrawableHelper* helper;
		// The context's own helper, installed by the constructor
		WrappedDrawableHelper ownHelper;
		// The passes' chain (0x1070EDF0 / the destructor)
		RenderPassChain* passChain;
		bool unknown6C;
		// The frame pool: 8-byte entries, one per frame the passes draw (the flag at +0, the parameters at +4)
		unsigned char* frames;
		unsigned char* framesEnd;
		// Nothing in the unit reads the last word (the class is 0x7C bytes)
		unsigned char unknown78[4];

		// 0x11281390: the window the context was started on
		static void* sWindow;
		// 0x11281394: the window procedure the context replaced
		static void* sPreviousWindowProc;
	};

	// 0x106F36C0 (another unit): counts a frame the display drew
	void Unknown106F36C0();
	// 0x107102B0 (another unit): destroys an entry of the context's tree and frees it (the TreeBase::Clear deleter)
	bool DeleteContextEntry(container::TreeBase::Node* node, void* context);

	// 0x1127F350
	extern Context* context;
}

#endif
