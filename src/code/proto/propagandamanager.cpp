// proto::PropagandaManager: see the header. The file name, the layout and the names are guesses.
#include "code/proto/propagandamanager.h"
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
	// FUNCTION: ENGINE 0x1056EEF0
	void PropagandaManager::SetLevel(int newLevel)
	{
		if (newLevel != level && (unsigned int)newLevel <= 2)
		{
			level = newLevel;
			state = 1;
		}
	}

	// FUNCTION: ENGINE 0x1056EF40
	void PropagandaManager::UploadTexture(unsigned char* data, unsigned int size, pure3d::Texture* texture)
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
		if (uploaded == textureCount)
		{
			state = 0;
			uploaded = 0;
		}
		else
		{
			state = 1;
		}
	}

	// FUNCTION: ENGINE 0x1056F2A0
	// NONMATCHING: scheduling of the member and frame stores before the first formatting call (77.7 %)
#ifdef NONMATCHING
	void PropagandaManager::LoadTextures()
	{
		if (engine::render::GetEffectManager()->IsFeatureEnabled(0xC0000))
		{
			char name[0x100];
			char path[0x204];
			char prefix[4];
			char letter = (char)(level + 'a');
			uploaded++;
			unknown14 = name;
			unknown18 = path;
			prefix[0] = letter;
			prefix[1] = '_';
			prefix[2] = 0;
			core::SNPrintfCount(name, 0x100, "billboards_1024x1024_0%u_diffuse.dds", uploaded);
			core::SNPrintfCount(path, 0x204, "art/billboards/billboards_1024x1024_0%u_%sdiffuse.dds", uploaded, prefix);
			pure3d::Texture* texture = content::gRootInventory->Find<pure3d::Texture>(unknown14);
			texture->AddRef();
			core::IFile* file;
			core::FileSystemOpenFileAsync(&file, core::FilePath(unknown18), false, 0, 1, 0, 1, 1, 0);
			file->Wait();
			unsigned char* buffer = new (10) unsigned char[file->GetCurrentSize()];
			file->Read(buffer, file->GetCurrentSize(), 1);
			file->Wait();
			engine::render::QueueObjRenderEvent(this, &PropagandaManager::UploadTexture, buffer,
				file->GetCurrentSize(), texture);
			file->Release();
			state = 2;
		}
	}
#endif

	// FUNCTION: ENGINE 0x1056F4C0
	void PropagandaManager::Update(float deltaTime)
	{
		if (state == 1)
		{
			LoadTextures();
		}
	}

	// FUNCTION: ENGINE 0x1056F4E0
	void PropagandaManager::RegisterScript()
	{
		engine::LuaScriptManager* manager = engine::GetScriptManager();
		manager->SetOwner(this);
		manager->RegisterMethod("world_SetPropagandaLevel", this, &PropagandaManager::SetLevel);
		manager->ClearOwner();
	}

	// FUNCTION: ENGINE 0x1056F540
	PropagandaManager::PropagandaManager() : level(0), state(0), textureCount(4), uploaded(0), unknown14(0), unknown18(0)
	{
		gPropagandaManager = this;
		RegisterScript();
	}

	// FUNCTION: ENGINE 0x1056EF20
	PropagandaManager::~PropagandaManager()
	{
		ReleaseScript();
		gPropagandaManager = 0;
	}
}

// The render thread event of the texture upload and the function that queues it (explicit instances)
template class engine::render::ObjRenderEvent3<proto::PropagandaManager, unsigned char*, unsigned int,
	pure3d::Texture*>;
template void engine::render::QueueObjRenderEvent<proto::PropagandaManager, unsigned char*, unsigned int,
	pure3d::Texture*>(proto::PropagandaManager*, void (proto::PropagandaManager::*)(unsigned char*,
	unsigned int, pure3d::Texture*), unsigned char*, unsigned int, pure3d::Texture*);

// Kept copies (template instances and wrappers of this unit):
// FUNCTION: ENGINE 0x1056F060
// FUNCTION: ENGINE 0x1056F0B0
// FUNCTION: ENGINE 0x1056F180
// FUNCTION: ENGINE 0x1056F1B0
