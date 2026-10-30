// pure3d::RenderTargetManager (RTTI name; base pure3d::RefCounted; code/pure3d/pass/src/rendertargetmanager.cpp from
// the asserts): the singleton that owns the colour and depth targets the passes draw into and a pool of other targets
// they borrow for a frame. Member and function names are guesses.
#ifndef PURE3D_PASS_RENDERTARGETMANAGER_H
#define PURE3D_PASS_RENDERTARGETMANAGER_H

#include "code/pure3d/entity.h"
#include "code/pure3d/pddi/dx9/dxtexture.h"
#include "code/pure3d/primitive.h"

namespace pure3d
{
	class dxVertexBuffer;

	// A growable list over a block of fixed size (begin, end and the end of the block; the block is taken with
	// operator new[] and never grows). The engine inlines its members.
	template<class T> struct TargetList
	{
		TargetList()
		{
			begin = 0;
			end = 0;
			capacity = 0;
		}

		// The number of items held
		unsigned int Size() const
		{
			return end - begin;
		}
		// The item at that index
		T& Get(unsigned int index)
		{
			return begin[index];
		}
		// Forgets the items (the block stays)
		void Clear()
		{
			end = begin;
		}

		T* begin;
		T* end;
		T* capacity;
	};

	// A target of the pool (12 bytes): the texture, which size it follows (0 the display's, 1 half, 2 quarter, 3 its
	// own) and a flag it was asked for
	struct PoolTarget
	{
		Texture* texture;
		int divider;
		bool flag;
	};

	// The class of the value the device's texture hands out as its handle (the engine calls a member of it)
	struct TextureHandle
	{
		// 0x1061F110
		int Unknown1061F110();
	};

	class RenderTargetManager : public RefCounted
	{
	public:
		// 0x1073B680 (0xC2 bytes): takes the display's size, makes the pools and the quad
		RenderTargetManager();
		// 0x1073B750; the scalar deleting destructor is 0x1073B8D0
		virtual ~RenderTargetManager();

		// 0x1073B790: makes the one manager (asserts there is none) with that format and its targets
		static bool Create(int format);

		// 0x1073A780, 0x1073A790: the size of the display the manager follows
		int GetWidth();
		int GetHeight();
		// 0x1073A720, 0x1073A740: the size of the colour target in use (0 without one)
		int GetColourWidth();
		int GetColourHeight();
		// 0x1073AA10: makes the two colour targets and the depth targets, answers whether it could
		bool CreateTargets();
		// 0x1073AB70: makes the pool's targets that follow the display's size over for a new size
		bool Resize(int width, int height);
		// 0x1073AD00: whether the texture is one of those lent out
		bool IsLent(Texture* texture);
		// 0x1073AD40: a target of its own, never pooled
		Texture* MakeTarget(int divider, int format, int unknown20, int unknown28);
		// 0x1073AE40: draws into the colour target at hand and the depth target
		void UseDefaultTargets();
		// 0x1073AEB0: draws into the given colour and depth targets (the depth one only while the sizes agree)
		void UseTargets(dxTexture* colour, dxTexture* depth, bool keepDepth);
		// 0x1073AFA0: gives the targets up and makes the one drawn into the next source
		void Finish(int a, int b);
		// 0x1075D550: the texture the next pass reads: the source, or the colour target at hand
		dxTexture* GetSource();
		// 0x1073B040: the texture the next pass reads (takes a reference)
		void SetSource(dxTexture* texture);
		// 0x1073B1A0: a target of that size, divider, format and flag that is not lent out (a new one when the pool has
		// none); it is lent out until the manager lets the targets go
		Texture* Borrow(int width, int height, int divider, int format, bool flag);
		// 0x1073B320: one of the display's size divided by divider
		Texture* BorrowDivided(int divider, int format, bool flag);
		// 0x1073B3A0: one of its own size
		Texture* BorrowSized(int width, int height, int format, bool flag);
		// 0x1073B3F0: lets the lent targets and the pool go
		void ReleaseAll();
		// 0x1073B460: fills the vertex buffer of the quad that covers the display
		void BuildQuad();
		// 0x1073B450: takes the lent list back to its start
		void Unknown1073B450();
		// 0x1073B850: the size of the display (0, 0: the engine's display's); false when the targets cannot be made
		bool SetSize(unsigned int newWidth, unsigned int newHeight);
		// 0x1073A9C0: lets go of the targets
		void ReleaseTargets();

		// 0x112818C0
		static RenderTargetManager* sSingleton;

		int format;
		dxTexture* depth;
		dxTexture* unknown10;
		dxTexture* colours[2];
		dxTexture* source;
		dxTexture* colour;
		dxTexture* currentDepth;
		int index;
		TargetList<PoolTarget> pool;
		unsigned char unknown38[4];
		TargetList<Texture*> lent;
		unsigned char unknown48[4];
		dxVertexBuffer* quad;
		unsigned int width;
		unsigned int height;
		bool unknown58;
	};
}

#endif
