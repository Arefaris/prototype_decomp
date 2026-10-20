// CFLAGS: /arch:SSE
// pure3d::RenderTargetManager (code/pure3d/pass/src/rendertargetmanager.cpp, from the asserts): the display's colour
// and depth targets and the pool of targets the passes borrow. Names are guesses.
#include "code/core/debug.h"
#include "code/core/refptr.h"
#include "code/engine/display.h"
#include "code/pure3d/context.h"
#include "code/pure3d/pass/rendertargetmanager.h"
#include "code/pure3d/pddi.h"
#include "code/pure3d/pddi/dx9/dxcontext.h"
#include "code/pure3d/pddi/vertexdeclaration.h"
#include "code/pure3d/vertexstream.h"
#include "code/math/vector2.h"

#include <new>

// The file the unit's asserts carry
#define RENDERTARGETMANAGER_FILE "..\\..\\..\\code\\pure3d\\pass\\src\\rendertargetmanager.cpp"

namespace pure3d
{
	// 0x1127F358: the Direct3D 9 view of the pddi device (name guess)
	extern dxDevice* gPddiDx;

	// 0x112818C0
	RenderTargetManager* RenderTargetManager::sSingleton;

	// The sizes of the display divided by one, two and four, and the heights after them (the divider indexes them)
	struct TargetSizes
	{
		int values[6];
	};

	// FUNCTION: ENGINE 0x1073A720
	int RenderTargetManager::GetColourWidth()
	{
		if (colour != 0)
		{
			return colour->levelData->data->width;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1073A740
	int RenderTargetManager::GetColourHeight()
	{
		if (colour != 0)
		{
			return colour->levelData->data->height;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1073A780
	int RenderTargetManager::GetWidth()
	{
		return width;
	}

	// FUNCTION: ENGINE 0x1073A790
	int RenderTargetManager::GetHeight()
	{
		return height;
	}

	// FUNCTION: ENGINE 0x1073A9C0
	void RenderTargetManager::ReleaseTargets()
	{
		ReleaseRef(&unknown10);
		ReleaseRef(&depth);
		ReleaseRef(&source);
		for (int i = 0; i < 2; i++)
		{
			ReleaseRef(&colours[i]);
		}
	}

	// FUNCTION: ENGINE 0x1073AA10
	// EQUIVALENT: the engine keeps the answer for the depth target in a register (a set-if-not-equal and a compare)
	// where ours compares the member again (89.9 %)
	bool RenderTargetManager::CreateTargets()
	{
		ReleaseTargets();
		TextureDescription description;
		description.type = 1;
		description.levels = 1;
		description.depth = 1;
		description.width = GetWidth();
		description.height = GetHeight();
		description.format = format;
		description.usage = 2;
		description.flags = 0x30;
		description.unknown28 = 2;
		for (int i = 0; i < 2; i++)
		{
			description.unknown20 = 0;
			description.unknown24 = 0;
			colours[i] = gPddiDx->NewTexture(&description);
			description.unknown20 = ((TextureHandle*)((pddiSurface*)colours[i])->GetHandle())->Unknown1061F110();
		}
		if (engine::gDisplay->GetUnknown28() == 0)
		{
			depth = engine::gDisplay->GetBackBufferTexture();
		}
		else
		{
			description.flags = 0x20;
			description.format = 0x12;
			depth = gPddiDx->NewTexture(&description);
		}
		description.format = 9;
		unknown10 = gPddiDx->NewTexture(&description);
		for (int i = 0; i < 2; i++)
		{
			if (colours[i] != 0)
			{
				colours[i]->AddRef();
			}
		}
		if (unknown10 != 0)
		{
			unknown10->AddRef();
		}
		if (depth != 0)
		{
			depth->AddRef();
		}
		bool made = depth != 0;
		index = 0;
		source = 0;
		colour = 0;
		if (made && colours[0] != 0 && colours[1] != 0)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1073AB70
	bool RenderTargetManager::Resize(int newWidth, int newHeight)
	{
		bool ok = true;
		for (int i = 0; i < (int)pool.Size(); i++)
		{
			PoolTarget* target = &pool.Get(i);
			if (target->divider < 3)
			{
				int widths[3];
				int heights[3];
				widths[0] = newWidth;
				widths[1] = newWidth / 2;
				widths[2] = newWidth / 4;
				heights[0] = newHeight;
				heights[1] = newHeight / 2;
				heights[2] = newHeight / 4;
				int targetWidth = widths[target->divider];
				int targetHeight = heights[target->divider];
				if (targetWidth != target->texture->info->levelData->data->width
					|| targetHeight != target->texture->info->levelData->data->height)
				{
					unsigned int format = target->texture->info->description.format;
					target->texture->SetInfo(0);
					TextureDescription description;
					description.type = 1;
					description.depth = 1;
					description.levels = 1;
					description.width = targetWidth;
					description.height = targetHeight;
					description.format = format;
					description.usage = 2;
					if (target->flag)
					{
						description.flags = 0x20;
					}
					dxTexture* made = gPddiDx->NewTexture(&description);
					ok = ok && made != 0;
					target->texture->SetInfo(made);
				}
			}
		}
		return ok;
	}

	// FUNCTION: ENGINE 0x1073AD00
	bool RenderTargetManager::IsLent(Texture* texture)
	{
		for (unsigned int i = 0; i < lent.Size(); i++)
		{
			if (lent.Get(i) == texture)
			{
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1073AD40
	// EQUIVALENT: the engine keeps a zero in a register and stores the description's two zero words before the rest;
	// ours stores them after the others (75.9 %)
	Texture* RenderTargetManager::MakeTarget(int divider, int format, int unknown20, int unknown28)
	{
		int displayWidth = GetWidth();
		int displayHeight = GetHeight();
		int widths[3];
		int heights[3];
		widths[1] = displayWidth / 2;
		widths[2] = displayWidth / 4;
		heights[1] = displayHeight / 2;
		heights[2] = displayHeight / 4;
		TextureDescription description;
		description.unknown34 = true;
		description.type = 1;
		description.depth = 1;
		description.levels = 1;
		widths[0] = displayWidth;
		heights[0] = displayHeight;
		description.width = widths[divider];
		description.height = heights[divider];
		if (format == 0)
		{
			description.format = this->format;
		}
		else
		{
			description.format = format;
		}
		description.usage = 2;
		description.flags = 0x20;
		description.unknown20 = unknown20;
		description.unknown24 = 0;
		description.unknown28 = unknown28;
		description.unknown2C = 0;
		description.unknown30 = 0;
		Texture* texture = new Texture;
		texture->Create(&description, 0);
		return texture;
	}

	// FUNCTION: ENGINE 0x1073AE40
	void RenderTargetManager::UseDefaultTargets()
	{
		AssignRef(&colour, colours[index]);
		AssignRef(&currentDepth, depth);
		pddiRenderTargets targets = {0, 0, 0, 0, 0};
		targets.depth = ((pddiSurface*)depth)->GetHandle();
		targets.colour = ((pddiSurface*)colours[index])->GetHandle();
		pddi->SetRenderTargets(&targets);
	}

	// FUNCTION: ENGINE 0x1073AEB0
	// EQUIVALENT: the same calls, tests and stores in the same order; the engine keeps its zero and the size test's
	// answer in one callee-saved register, ours in two others (31.8 %)
	void RenderTargetManager::UseTargets(dxTexture* colourTarget, dxTexture* depthTarget, bool keepDepth)
	{
		pddiRenderTargets targets;
		targets.depth = 0;
		targets.colour = 0;
		targets.unknown8 = 0;
		targets.unknownC = 0;
		targets.unknown10 = 0;
		if (depthTarget == 0)
		{
			depthTarget = depth;
		}
		if (colourTarget != 0)
		{
			bool sameSize = false;
			if (depthTarget != 0)
			{
				TextureLevelData* depthSize = depthTarget->levelData->data;
				TextureLevelData* colourSize = colourTarget->levelData->data;
				sameSize = depthSize->width == colourSize->width && depthSize->height == colourSize->height;
			}
			targets.colour = ((pddiSurface*)colourTarget)->GetHandle();
			if (depthTarget != 0 && sameSize && !keepDepth)
			{
				targets.depth = ((pddiSurface*)depthTarget)->GetHandle();
			}
		}
		else
		{
			targets.colour = ((pddiSurface*)colours[index])->GetHandle();
			if (keepDepth)
			{
				targets.depth = 0;
			}
			else
			{
				targets.depth = ((pddiSurface*)depthTarget)->GetHandle();
			}
			colourTarget = colours[index];
		}
		pddi->SetRenderTargets(&targets);
		depthTarget = targets.depth != 0 ? depthTarget : 0;
		AssignRef(&currentDepth, depthTarget);
		AssignRef(&colour, colourTarget);
	}

	// FUNCTION: ENGINE 0x1073AFA0
	void RenderTargetManager::Finish(int a, int b)
	{
		pddi->Unknown7((int)currentDepth, (pddiSurface*)colour, 0, 0, 0, 0);
		pddi->SetRenderTargets(0);
		bool other = colour != colours[index];
		if (source != 0)
		{
			source->Release();
		}
		if (!other)
		{
			source = colours[index];
			index = (index + 1) % 2;
		}
		else
		{
			source = colour;
		}
		source->AddRef();
		ReleaseRef(&colour);
		ReleaseRef(&currentDepth);
	}

	// FUNCTION: ENGINE 0x1073B040
	void RenderTargetManager::SetSource(dxTexture* texture)
	{
		AssignRef(&source, texture);
	}

	// FUNCTION: ENGINE 0x1073B1A0
	Texture* RenderTargetManager::Borrow(int width, int height, int divider, int format, bool flag)
	{
		Texture* found = 0;
		unsigned int count = pool.Size();
		for (unsigned int i = 0; i < count; i++)
		{
			PoolTarget* target = &pool.Get(i);
			dxTexture* info = target->texture->info;
			TextureLevelData* size = info->levelData->data;
			if (size->width == width && size->height == height && (int)info->description.format == format
				&& target->flag == flag && !IsLent(target->texture))
			{
				found = target->texture;
				break;
			}
		}
		if (found == 0)
		{
			TextureDescription description;
			description.type = 1;
			description.depth = 1;
			description.levels = 1;
			description.width = width;
			description.height = height;
			description.format = format;
			description.usage = 2;
			description.flags = 0x10;
			if (flag)
			{
				description.flags = 0x30;
			}
			description.unknown34 = flag;
			description.unknown20 = 0;
			description.unknown24 = 0;
			dxTexture* made = gPddiDx->NewTexture(&description);
			if (made != 0)
			{
				Texture* texture = new Texture;
				texture->SetInfo(made);
				texture->AddRef();
				PoolTarget entry;
				entry.texture = texture;
				entry.divider = divider;
				entry.flag = flag;
				if (pool.end < pool.capacity)
				{
					PoolTarget* item = pool.end++;
					if (item != 0)
					{
						*item = entry;
					}
				}
				found = texture;
			}
		}
		if (lent.end < lent.capacity)
		{
			Texture** item = lent.end++;
			if (item != 0)
			{
				*item = found;
			}
		}
		return found;
	}

	// FUNCTION: ENGINE 0x1073B320
	// EQUIVALENT: the same operations; the registers of the borrowed size and format are swapped and one store of the
	// local size table is placed later (76.2 %)
	Texture* RenderTargetManager::BorrowDivided(int divider, int format, bool flag)
	{
		int displayWidth = GetWidth();
		int displayHeight = GetHeight();
		int widths[3];
		int heights[3];
		widths[1] = displayWidth / 2;
		widths[2] = displayWidth / 4;
		heights[1] = displayHeight / 2;
		heights[0] = displayHeight;
		heights[2] = displayHeight / 4;
		widths[0] = displayWidth;
		int targetWidth = widths[divider];
		int targetHeight = heights[divider];
		if (format == 0)
		{
			format = this->format;
		}
		return Borrow(targetWidth, targetHeight, divider, format, flag);
	}

	// FUNCTION: ENGINE 0x1073B3A0
	Texture* RenderTargetManager::BorrowSized(int width, int height, int format, bool flag)
	{
		if (format == 0)
		{
			format = this->format;
		}
		return Borrow(width, height, 3, format, flag);
	}

	// FUNCTION: ENGINE 0x1073B3F0
	void RenderTargetManager::ReleaseAll()
	{
		ReleaseTargets();
		unsigned int count = pool.Size();
		for (unsigned int i = 0; i < count; i++)
		{
			core::SafeRelease(pool.Get(i).texture);
		}
		pool.Clear();
		lent.Clear();
		core::SafeRelease(quad);
	}

	// FUNCTION: ENGINE 0x1073B450
	void RenderTargetManager::Unknown1073B450()
	{
		lent.end = lent.begin;
	}

	// FUNCTION: ENGINE 0x1073B460
	// EQUIVALENT: the same instructions; one load of the texture coordinate is scheduled earlier in the engine (97.1 %)
	void RenderTargetManager::BuildQuad()
	{
		VertexBufferDescription description(4, 0x2021, 3, false);
		core::RefAssign(quad, gPddiDx->NewVertexBuffer(&description));
		dxVertexDeclaration lock;
		lock.unknown110 = 0;
		float u = 0.5f / (float)width;
		float v = 0.5f / (float)height;
		float u1 = u + 1.0f;
		float v1 = v + 1.0f;
		quad->Lock(&lock, 0);
		VertexStream<math::Vector> positions(&lock, core::Name<core::CaseInsensitiveKey32>("position", 1));
		VertexStream<unsigned int> colours(&lock, core::Name<core::CaseInsensitiveKey32>("colour0", 1));
		VertexStream<math::Vector2> coordinates(&lock, core::Name<core::CaseInsensitiveKey32>("tex0", 1));
		positions.current->x = 1.0f;
		positions.current->y = 1.0f;
		positions.current->z = 1.0f;
		positions.Next();
		positions.current->x = 0.0f;
		positions.current->y = 1.0f;
		positions.current->z = 1.0f;
		positions.Next();
		positions.current->x = 1.0f;
		positions.current->y = 0.0f;
		positions.current->z = 1.0f;
		positions.Next();
		positions.current->x = 0.0f;
		positions.current->y = 0.0f;
		positions.current->z = 1.0f;
		positions.Next();
		*colours.current = 0xFFFFFFFF;
		colours.Next();
		*colours.current = 0xFFFFFFFF;
		colours.Next();
		*colours.current = 0xFFFFFFFF;
		colours.Next();
		*colours.current = 0xFFFFFFFF;
		colours.Next();
		coordinates.current->x = u1;
		coordinates.current->y = v1;
		coordinates.Next();
		coordinates.current->x = u;
		coordinates.current->y = v1;
		coordinates.Next();
		coordinates.current->x = u1;
		coordinates.current->y = v;
		coordinates.Next();
		coordinates.current->x = u;
		coordinates.current->y = v;
		coordinates.Next();
		quad->Unlock();
	}

	// FUNCTION: ENGINE 0x1073B680
	RenderTargetManager::RenderTargetManager() : RefCounted(NO_BARRIER), format(5), quad(0), unknown58(false)
	{
		pool.begin = new PoolTarget[128];
		if (pool.begin != 0)
		{
			pool.end = pool.begin;
			pool.capacity = pool.begin + 128;
		}
		else
		{
			pool.end = 0;
			pool.capacity = 0;
		}
		lent.begin = new Texture*[128];
		if (lent.begin != 0)
		{
			lent.end = lent.begin;
			lent.capacity = lent.begin + 128;
		}
		else
		{
			lent.end = 0;
			lent.capacity = 0;
		}
		colours[0] = 0;
		colours[1] = 0;
		unknown10 = 0;
		colour = 0;
		currentDepth = 0;
		depth = 0;
		source = 0;
		index = 0;
		width = engine::gDisplay->GetWidth();
		height = engine::gDisplay->GetUnknown8();
		BuildQuad();
	}

	// The scalar deleting destructor the compiler writes for the destructor below
	// FUNCTION: ENGINE 0x1073B8D0

	// FUNCTION: ENGINE 0x1073B750
	RenderTargetManager::~RenderTargetManager()
	{
		ReleaseAll();
		lent.end = lent.begin;
		if (lent.begin != 0)
		{
			delete[] lent.begin;
		}
		pool.end = pool.begin;
		if (pool.begin != 0)
		{
			delete[] pool.begin;
		}
	}

	// FUNCTION: ENGINE 0x1073B790
	bool RenderTargetManager::Create(int format)
	{
		OLD_ASSERT_TEXT_AT(RENDERTARGETMANAGER_FILE, 0xA3, sSingleton == 0, "0 == sSingleton");
		sSingleton = new RenderTargetManager;
		sSingleton->format = format;
		bool allocateSuccess = sSingleton->CreateTargets();
		OLD_ASSERT_TEXT_AT(RENDERTARGETMANAGER_FILE, 0xA8, allocateSuccess, "allocateSuccess");
		return sSingleton != 0;
	}

	// FUNCTION: ENGINE 0x1073B850
	bool RenderTargetManager::SetSize(unsigned int newWidth, unsigned int newHeight)
	{
		bool result = true;
		if (newWidth == 0 && newHeight == 0)
		{
			width = engine::gDisplay->GetWidth();
			height = engine::gDisplay->GetUnknown8();
		}
		else
		{
			width = newWidth;
			height = newHeight;
		}
		unsigned int wantedWidth = width;
		unsigned int wantedHeight = height;
		if (wantedWidth != (unsigned int)colours[0]->levelData->data->width
			|| wantedHeight != (unsigned int)colours[0]->levelData->data->height)
		{
			bool created = CreateTargets();
			if (created != true)
			{
				return created;
			}
			result = Resize(wantedWidth, wantedHeight);
			BuildQuad();
		}
		return result;
	}
}
