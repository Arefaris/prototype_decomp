// pure3d::Context (code/pure3d/src/context.cpp; asserts "pure3d::context == 0" and "pure3d::context != 0"): the render
// context, one instance at pure3d::context (0x1127F350, 0x7C bytes, made by Context::Startup). It keeps the frame's
// times, the view, the passes' context and the wrapped drawable helper (the class is defined in the same file), and it
// drives a frame with BeginFrame / EndFrame. The layout was read off the constructor; the member names are guesses.
#ifndef PURE3D_CONTEXT_H
#define PURE3D_CONTEXT_H

#include "code/container/arraydynamicstatic.h"
#include "code/container/map.h"
#include "code/core/memory/imemoryallocator.h"
#include "code/core/name.h"
#include "code/core/time.h"

namespace content
{
	class LoadInventory;
	typedef core::Name<core::CaseSensitiveKey> ObjectName;
}

namespace pure3d
{
	class Context;
	class RenderTarget;
	class TargetParams;
	class pddiSurface;
	class Drawable;
	class PrimStream;
	class View;
	class dxIndexBuffer;
	class dxContext;
	class dxDevice;

	// The hook the engine's renderer installs on a pure3d drawable (engine::render::EngineWrappedDrawableHelper
	// derives from it); the context keeps one at +0x64 and hands it out through GetWrappedDrawableHelper. Vftable
	// 0x10E5B114 (two slots); the meaning of the slots is unknown.
	class WrappedDrawableHelper
	{
	public:
		// 0x1070EDA0
		WrappedDrawableHelper();
		// 0x1070ED90: the object a loaded drawable is handed out as (the drawable itself here; the engine's helper
		// wraps it)
		virtual core::IRefCount* Wrap(core::IRefCount* drawable);
		// 0x1070FC60: the drawable of that name in the inventory
		virtual Drawable* FindDrawable(content::LoadInventory* inventory, const content::ObjectName& name);
	};

	class RenderParams;
	class RenderContext;

	// A name as its 64-bit hash (the key of the context's tree starts with one; the word makes the key 8-byte
	// aligned, which sets the size of the tree's nodes, 0x28)
	struct ContextName
	{
		// 0x1007EE00 (another unit's copy)
		explicit ContextName(const unsigned __int64& newHash);
		// 0x1007EE20 (another unit's copy)
		const unsigned __int64& GetHash() const;

		unsigned __int64 hash;
	};

	// The name of a render context and the text it was made from (the key of the context's tree)
	struct ContextKey
	{
		// 0x1070F730: copies the name and the text (a text the other key owns is copied)
		ContextKey(const ContextKey& other);
		// 0x106E2AA0 (another unit): frees the text the key owns
		~ContextKey();
		// 0x1047BE40 (another unit): orders by name
		bool operator<(const ContextKey& other) const;
		// 0x104E1DB0 (another unit): keeps a copy of the text
		void SetText(const char* newText);

		ContextName name;
		const char* text;
		bool ownsText;
	};

	// The tree of the render contexts a frame can run, by name (container::Map's shape over ContextKey; the
	// allocation is operator new[] / delete[]). The tree itself is container::TreeBase (0x10610990 - 0x10610DD0).
	template<class Key, class Value> class ContextTree : public container::TreeBase
	{
	public:
		struct Pair
		{
			// 0x1070FBA0
			Pair(const Pair& other) : key(other.key)
			{
				value = other.value;
			}
			// 0x1070FB40
			Pair(const Key& newKey, const Value& newValue) : key(newKey)
			{
				value = newValue;
			}
			// 0x1070F6D0 (a jump to the key's destructor)
			~Pair()
			{
			}

			Key key;
			Value value;
		};

		struct MapNode : public container::TreeBase::Node
		{
			// 0x107100E0
			MapNode(const Pair& newPair) : pair(newPair)
			{
			}
			// 0x1070F840
			~MapNode()
			{
			}

			Pair pair;
		};

		class Iterator
		{
		public:
			// 0x1070F6E0
			Iterator(MapNode* newNode, ContextTree* newMap)
			{
				node = newNode;
				map = newMap;
			}
			// 0x1070F690 / 0x1070F2B0
			Pair* operator->() const
			{
				return &node->pair;
			}
			Pair& operator*() const
			{
				return node->pair;
			}
			// 0x1070F2C0 / 0x1070F6A0
			Iterator& operator++()
			{
				node = (MapNode*)map->Next(node);
				return *this;
			}
			Iterator operator++(int)
			{
				Iterator old = *this;
				node = (MapNode*)map->Next(node);
				return old;
			}
			// 0x1070F270 / 0x1070F290
			bool operator==(const Iterator& other) const
			{
				return node == other.node;
			}
			bool operator!=(const Iterator& other) const
			{
				return node != other.node;
			}

			MapNode* node;
			ContextTree* map;
		};

		// 0x1070FAB0 / 0x1070FB60: the orders the tree functions take
		static int Compare(const Key& a, const Key& b)
		{
			if (a < b)
			{
				return -1;
			}
			if (b < a)
			{
				return 1;
			}
			return 0;
		}
		static int CompareKey(const void* key, const container::TreeBase::Node* node)
		{
			return Compare(*(const Key*)key, ((const MapNode*)node)->pair.key);
		}
		static int CompareNodes(const container::TreeBase::Node* a, const container::TreeBase::Node* b)
		{
			return Compare(((const MapNode*)a)->pair.key, ((const MapNode*)b)->pair.key);
		}

		// 0x1070F680 (the argument is the empty allocator)
		explicit ContextTree(int unused)
		{
		}
		~ContextTree()
		{
			Clear();
		}
		// 0x107102B0: takes a node out of the tree for Clear (destroys its key and frees it)
		static bool DeleteNode(container::TreeBase::Node* node, void* context)
		{
			((MapNode*)node)->~MapNode();
			operator delete[](node);
			return true;
		}
		void Clear()
		{
			container::TreeBase::Clear(DeleteNode, this);
		}

		// 0x1070FA60 / 0x1070FA80 / 0x10710090 / 0x10710230 / 0x10710040
		Iterator Begin()
		{
			return Iterator((MapNode*)First(), this);
		}
		Iterator End()
		{
			return Iterator(0, 0);
		}
		Iterator Find(const Key& key)
		{
			return Iterator((MapNode*)container::TreeBase::Find(CompareKey, &key), this);
		}
		Iterator Insert(const Pair& pair)
		{
			container::TreeBase::Node* parent = FindParent(CompareKey, &pair.key);
			if (parent == 0)
			{
				return Iterator(0, 0);
			}
			MapNode* node = new (operator new[](sizeof(MapNode))) MapNode(pair);
			container::TreeBase::Insert(node, CompareNodes, parent);
			return Iterator(node, this);
		}
		Iterator Erase(Iterator position)
		{
			Iterator next = position;
			++next;
			Remove(position.node);
			position.node->~MapNode();
			operator delete[](position.node);
			return next;
		}
		// 0x107102D0: the value of key, made empty when the key is new
		Value& operator[](const Key& key)
		{
			MapNode* node = (MapNode*)container::TreeBase::Find(CompareKey, &key);
			if (node != 0)
			{
				return node->pair.value;
			}
			Pair pair(key, Value());
			return Insert(pair)->value;
		}
	};

	// The frame pool's array: begin and end pointers over operator new[] (names guessed)
	template<class T> inline T* FillCopies(T* dest, unsigned int count, const T& value)
	{
		while (count != 0)
		{
			count--;
			if (dest != 0)
			{
				new (dest) T(value);
			}
			dest++;
		}
		return dest;
	}

	template<class T> class ContextArray
	{
	public:
		// 0x1070F230 (the argument is the empty allocator)
		explicit ContextArray(int unused)
		{
			begin = 0;
			end = 0;
		}
		// 0x1070F330
		ContextArray(T* first, T* last)
		{
			begin = first;
			end = last;
		}
		// 0x1070FAA0
		~ContextArray()
		{
			if (begin != 0)
			{
				operator delete[](begin);
			}
		}
		// 0x1070F250 / 0x1070F260
		int Size() const
		{
			return (int)(end - begin);
		}
		T& operator[](int index)
		{
			return begin[index];
		}
		// 0x1070F2E0: count uninitialised elements (an empty array when count is 0 or the allocation fails)
		bool Allocate(unsigned int count)
		{
			if (count > 0)
			{
				begin = (T*)operator new[](count * sizeof(T));
				if (begin != 0)
				{
					end = begin + count;
					return true;
				}
			}
			begin = 0;
			end = 0;
			return false;
		}
		// 0x1070FAE0: count copies of value (nothing when the array has its storage already)
		bool Allocate(unsigned int count, const T& value)
		{
			if (begin != 0)
			{
				return false;
			}
			if (count > 0)
			{
				begin = (T*)operator new[](count * sizeof(T));
				if (begin != 0)
				{
					end = begin + count;
					FillCopies(begin, count, value);
					return true;
				}
			}
			begin = 0;
			end = 0;
			return false;
		}
		// 0x107100C0: count empty elements
		bool AllocateEmpty(unsigned int count)
		{
			return Allocate(count, T());
		}

		T* begin;
		T* end;
	};

	// The default of the second setting (0x10E5DA34, a constant in the image)
	extern const int gDefaultSettingsUnknown4;

	// The settings of the display (0x138 bytes): the window it is created on first
	struct DisplaySettings
	{
		// 0x106179B0 (another unit)
		DisplaySettings();

		void* window;
		unsigned char unknown4[0x134];
	};

	// What Context::Startup is given: the display's mode at +0xC, the window the display is created on at +0x10 and
	// the number of the scene's drawables at +0x16C (only the members this unit reads are named, and they are
	// guesses).
	struct ContextSettings
	{
		// 8 bytes with a constructor of their own (0x10714D60, another unit)
		struct Unknown148
		{
			Unknown148();

			int unknown0;
			int unknown4;
		};

		// 0x10710120: 10000, the default, 2 (the second display mode), room for 8 drawables
		ContextSettings();

		int unknown0;
		int unknown4;
		bool unknown8;
		unsigned char unknown9[3];
		// 1 - 4: selects one of the four settings of the render device
		int displayMode;
		DisplaySettings display;
		Unknown148 unknown148;
		int unknown150;
		bool unknown154;
		int unknown158;
		int unknown15C;
		int unknown160;
		int unknown164;
		unsigned char unknown168[4];
		int drawableCount;
	};

	// The passes' runner at +0x1C: one render context of the context's tree (it knows its name, at +8, and the
	// frame is opened and closed through it); the passes themselves run with the frame's render parameters
	// (0x1074D880). Only what this unit calls is reconstructed.
	class RenderContext
	{
	public:
		virtual ~RenderContext();
		// Makes the context the current one / takes it out again
		virtual void Unknown1();
		virtual void Unknown2();
		virtual void Unknown3();
		virtual void Unknown4();
		virtual void Unknown5();
		virtual void Unknown6();
		// 0x1074D880
		void Run(const RenderParams* params);
		// 0x1074DB10 (another unit): the render parameters of the child context of that name, null when there is
		// none
		RenderParams* Unknown1074DB10(const core::Name<core::CaseSensitiveKey>* name);
		// Sets the parameter of the child context to the value (the render events' unit, 0x10826970 - 0x10826CE0)
		template<class T> bool SetParameter(const core::Name<core::CaseSensitiveKey>* context,
			const core::Name<core::CaseSensitiveKey>* parameter, const T* value);

		ContextKey key;
	};

	// The debug font (RTTI name pure3d::TextureFont); the context keeps one at +0x24
	class TextureFont : public core::IRefCount
	{
	public:
		// 0x1070EC40 (another unit): widens a text into the buffer (as much as fits, ended); the length
		int ToWide(const char* text, unsigned short* buffer, int capacity);
		// 0x1070EC90: draws an 8-bit text (widened into a buffer of 0x200 characters first; name guess)
		void DrawAnsi(const char* text, int unknown);

		virtual void Unknown3();
		virtual void Unknown4();
		virtual float Unknown5();
		// The height of a line
		virtual float Unknown6();
		virtual void Unknown7();
		virtual void Unknown8();
		virtual void Unknown9();
		virtual void Unknown10();
		// Draws the wide text
		virtual void Draw(const unsigned short* text, int unknown);
		virtual void Unknown12();
		virtual void Unknown13();
		virtual void Unknown14();
		virtual void Unknown15();
		virtual void Unknown16();
		virtual void SetColour(unsigned int colour);
	};

	// The chain of render passes the context's frame runs (the object at +0x68); 0x1074D650 walks the passes of
	// the chain. Only what this unit calls is reconstructed and the name is a guess.
	class RenderPassChain
	{
	public:
		// 0x1074D730 (another unit): the destructor; 0x1070EDB0: its scalar deleting form
		~RenderPassChain();
		void* DeleteThis(unsigned int flags);
		// 0x1074D650
		void Update();
	};

	// One entry of the frame pool: the object it hands out and whether the entry is in use
	struct FrameEntry
	{
		bool inUse;
		unsigned char unknown1[3];
		RenderParams* params;
	};

	class Context : public ContextTree<ContextKey, RenderContext*>
	{
	public:
		typedef pure3d::FrameEntry FrameEntry;

		// 0x1070F5C0 / 0x1070F600 / 0x1070F650: the frame pool at +0x70
		RenderParams* AllocRenderParams();
		void FreeRenderParams(RenderParams* params);
		void UpdateRenderParams();
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
		// 0x1070EF80: runs the passes with the colour and the depth target (they must be the same size)
		void RunPassesInto(const TargetParams* params, RenderTarget* colour, RenderTarget* depth);
		// 0x1070F380: draws a text with the debug font at the position (the font's colour first)
		void DrawDebugText(const char* text, float x, float y, unsigned int colour);
		// 0x1070F540: the same for a line of text below the position (whole pixels)
		void DrawDebugTextLine(const char* text, int x, int y, unsigned int colour);
		// 0x1070FC90: loads the debug font (dummy.p3d, "pure3d_debug_font") and keeps it
		void LoadDebugFont();
		// 0x1070FF50: the render context of a name's hash (null when there is none)
		RenderContext* FindContext(const unsigned __int64& hash);
		// 0x1070FFA0: draws with the render context the parameters name and keeps the size of the picture
		void RunContext(const RenderParams* params);
		// 0x107101F0 / 0x10710370: make the context of a name's hash / of a key the current one (false when there
		// is none, or the tree does not have it)
		bool SetCurrentContext(const unsigned __int64& hash);
		bool SetCurrentContext(const ContextKey& key);
		// 0x10710340 / 0x10710190: add a render context under its own key / take the one of a key out again
		void AddContext(RenderContext* context);
		void RemoveContext(const ContextKey& key);
		// 0x1070F1F0 / 0x1070F210: the size and the place of the window the context was started on
		int GetWindowClientRect(void* rect);
		int GetWindowScreenRect(void* rect);
		// 0x10710880: the scalar deleting destructor
		void* DeleteThis(unsigned int flags);
		// 0x1070F190: the address of the 8-byte member at +0x54
		void* GetUnknown54();
		// 0x1070F1A0
		Context* GetUnknown1070F1A0();

		unsigned char unknown18[4];
		// The render passes' context (+0x1C), the primitive stream (+0x20) and the state of the frame being built
		RenderContext* passes;
		PrimStream* primStream;
		TextureFont* font;
		View* view;
		// The index buffer of the quads the debug drawing uses
		dxIndexBuffer* indexBuffer;
		// How many indices the quad index buffer holds, 24000 (six per quad)
		unsigned int indexCount;
		// The number of the frame being built
		unsigned int frame;
		bool unknown38;
		// Set while the frame is being built (0x1070EE70 / 0x1070EF00)
		bool inFrame;
		// The time of the frame and its second half (a second time for the frame's start)
		core::Time frameTime;
		core::Time unknown48;
		// The size of the picture the last render context drew (width, height)
		float unknown54[2];
		bool unknown5C;
		WrappedDrawableHelper* helper;
		// The context's own helper, installed by the constructor
		WrappedDrawableHelper ownHelper;
		// The passes' chain (0x1070EDF0 / the destructor)
		RenderPassChain* passChain;
		bool unknown6C;
		// The frame pool: 8-byte entries, one per frame the passes draw (the flag at +0, the parameters at +4)
		ContextArray<FrameEntry> frames;
		// Nothing in the unit reads the last word (the class is 0x7C bytes)
		unsigned char unknown78[4];

		// 0x11281390: the window the context was started on
		static void* sWindow;
		// 0x11281394: the window procedure the context replaced
		static void* sPreviousWindowProc;
		// 0x11281398 / 0x1128139C: the half pixel the debug text is moved by
		static float sTextOffsetX;
		static float sTextOffsetY;
	};

	// 0x1070F1E0: tells the display (0x112818C0) to go back to its state
	void Unknown1070F1E0();
	// What the lighting is started with (0x10754560 makes it: 0 and -1)
	struct ContextRenderSettings
	{
		ContextRenderSettings();

		int unknown0;
		int unknown4;
	};

	// The parameters a render into targets runs the passes with: a copy of the ones it was given, with the colour and
	// depth surfaces and the size of the picture set (0x88 bytes; the constructor is 0x1074E5A0, the destructor
	// 0x1074E590; the name is a guess)
	class TargetParams
	{
	public:
		TargetParams(const TargetParams* source);
		virtual ~TargetParams();

		unsigned char unknown4[0xC];
		pddiSurface* colour;
		pddiSurface* depth;
		unsigned int flags;
		unsigned int width;
		unsigned int height;
		unsigned char unknown24[0x88 - 0x24];
	};

	// The subsystems the context starts (the constructor) and stops (the destructor), named after their addresses
	void Unknown106DDB60();
	void Unknown106DDE80();
	dxDevice* Unknown1061BBC0();
	void Unknown1073E1D0();
	void Unknown107063A0();
	void Unknown1073E2C0();
	void Unknown1073E2E0();
	void Unknown1071F7D0();
	void Unknown10755120(const ContextRenderSettings* settings);
	void Unknown1074D770(Context* context);
	void Unknown1073E260(Context* context);
	void Unknown107265E0();
	void Unknown107265F0();
	void Unknown107076C0(dxIndexBuffer** buffer);
	void Unknown106F3B10();
	void Unknown10715380();
	void Unknown10755EC0();
	void Unknown1073A6F0();
	void Unknown107168B0();
	void Unknown1071B080();
	void Unknown1073E2D0();
	void Unknown106F4820();
	void Unknown1073E2F0();
	void Unknown10704B60();
	void Unknown1073E1F0();
	// 0x1127F358: the Direct3D 9 context the display is made on
	extern dxDevice* gPddiDx;
	// 0x106F36C0 (another unit): counts a frame the display drew
	void Unknown106F36C0();

	// 0x1127F350
	extern Context* context;
}

#endif
