// proto::MidgroundTextureManager: see the header. The file name, the layout and the names are guesses.
#include "code/proto/render/midgroundtexturemanager.h"
#include "code/content/memorystream.h"
#include "code/engine/luascriptmanager.h"
#include "code/engine/function.h"
#include "code/engine/render/async/renderevent.h"
#include "code/pure3d/texture/texture.h"
#include "code/pure3d/pddi/dx9/dxtexture.h"
#include "code/content/loadinventory.h"
#include "code/core/file/filepath.h"
#include "code/engine/render/effectmanager.h"
#include <new>

namespace engine
{
	namespace render
	{
		// 0x1128186A: passed to the texture uploader (another unit)
		extern bool gTextureLoadFlag;
	}
}

namespace core
{
	// 0x1063B990: SNPrintf that returns the count
	int SNPrintfCount(char* destination, int size, const char* format, ...);
}

namespace proto
{
	// FUNCTION: ENGINE 0x10567690
	void MidgroundTextureManager::SetEpisode(int newEpisode)
	{
		if (newEpisode != episode && (unsigned int)(newEpisode - 1) <= 6)
		{
			episode = newEpisode;
			state = 1;
		}
	}

	// FUNCTION: ENGINE 0x10567710
	void MidgroundTextureManager::UploadTexture(unsigned char* data, unsigned int size, pure3d::Texture* texture)
	{
		content::MemoryStream* stream = new content::MemoryStream(data, size);
		stream->AddRef();
		pure3d::DDSParser loader(texture, 0, 0);
		int usage = texture->info->description.usage;
		const char* name = texture->mName.GetText() ? texture->mName.GetText() : core::GetDefaultString();
		loader.Load(stream, name, usage, engine::render::gTextureLoadFlag, 0);
		stream->Release();
		texture->Release();
		delete[] data;
		state = 0;
	}

	// FUNCTION: ENGINE 0x10567A40
	void MidgroundTextureManager::LoadTexture()
	{
		if (engine::render::GetEffectManager()->IsFeatureEnabled(0x7D000))
		{
			char name[0x100];
			char path[0x204];
			core::SNPrintfCount(name, 0x100, "global_temp_512x512_diffuse.dds", episode);
			core::SNPrintfCount(path, 0x204, "art/midground_textures/midground_episode_%d.dds", episode);
			pure3d::Texture* texture = content::gRootInventory->Find<pure3d::Texture>(name);
			texture->AddRef();
			core::IFile* file;
			core::FileSystemOpenFileAsync(&file, core::FilePath(path), false, 0, 1, 0, 1, 1, 0);
			file->Wait();
			unsigned char* buffer = new (10) unsigned char[file->GetCurrentSize()];
			file->Read(buffer, file->GetCurrentSize(), 1);
			file->Wait();
			engine::render::QueueObjRenderEvent(this, &MidgroundTextureManager::UploadTexture, buffer,
				file->GetCurrentSize(), texture);
			file->Release();
			state = 2;
		}
	}

	// FUNCTION: ENGINE 0x10567C30
	void MidgroundTextureManager::Update(float deltaTime)
	{
		if (state == 1)
		{
			LoadTexture();
		}
	}

	// FUNCTION: ENGINE 0x10567C50
	void MidgroundTextureManager::RegisterScript()
	{
		engine::LuaScriptManager* manager = engine::GetScriptManager();
		manager->SetOwner(this);
		manager->RegisterMethod("world_SetMidgroundTexture", this, &MidgroundTextureManager::SetEpisode);
		manager->ClearOwner();
	}

	// FUNCTION: ENGINE 0x10567CB0
	MidgroundTextureManager::MidgroundTextureManager() : state(0), episode(0)
	{
		gMidgroundTextureManager = this;
		RegisterScript();
	}

	// FUNCTION: ENGINE 0x105676F0
	MidgroundTextureManager::~MidgroundTextureManager()
	{
		ReleaseScript();
		gMidgroundTextureManager = 0;
	}
}

// FUNCTION: ENGINE 0x10567920
// The compiler's scalar deleting destructor of proto::MidgroundTextureManager, emitted with the class above: it calls
// the destructor and then operator delete when bit 0 of its argument is set.
//
// ReleaseScript (0x10567670, the same unit: GetScriptManager()->Unregister(this)) is only declared; the engine's copy
// owns the object in esi across the GetScriptManager call, ours spills the object instead (57 %).

// The render thread event of the texture upload and the function that queues it (explicit instances)
template class engine::render::ObjRenderEvent3<proto::MidgroundTextureManager, unsigned char*, unsigned int,
	pure3d::Texture*>;
template void engine::render::QueueObjRenderEvent<proto::MidgroundTextureManager, unsigned char*, unsigned int,
	pure3d::Texture*>(proto::MidgroundTextureManager*, void (proto::MidgroundTextureManager::*)(unsigned char*,
	unsigned int, pure3d::Texture*), unsigned char*, unsigned int, pure3d::Texture*);

// Kept copies (template instances and wrappers of this unit):
// FUNCTION: ENGINE 0x10567800
// FUNCTION: ENGINE 0x10567850
// FUNCTION: ENGINE 0x10567950
