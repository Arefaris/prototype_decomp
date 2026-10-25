// The online services' global files (engine::OLSStorage; 0x108C5950 - 0x108C6700).
#include "code/core/file/filepath.h"
#include "code/engine/online/olsstorage.h"

#pragma pointers_to_members(full_generality, multiple_inheritance)
#include "code/engine/function.h"
#include "code/engine/online/onlinemanager.h"

namespace engine
{
	// A global file the storage knows: its name and the most it holds (0x10E7E79C)
	struct GlobalFile
	{
		const char* name;
		int size;
	};

	// GLOBAL: ENGINE 0x10E7E79C
	static const GlobalFile sGlobalFiles[] =
	{
		{ "settings.txt", 5120 },
		{ "legal.txt", 10240 },
		{ "news.txt", 5120 },
		{ "faq.txt", 10240 }
	};

	// 0x1130DC60 (another unit)
	extern OLSGlobalFileUser* gGlobalFileUser;

	void OLSStorage::DownloadAll()
	{
		for (int i = 0; i < count; i++)
		{
			Download(i);
		}
	}

	void OLSStorage::Download(int index)
	{
		Queue(index, sGlobalFiles[index].name, sGlobalFiles[index].size);
	}

	void OLSStorage::LoadAndUploadAll()
	{
		for (int i = 0; i < count; i++)
		{
			LoadAndUpload(i);
		}
	}

	void OLSStorage::LoadAndUpload(int index)
	{
		LoadFile(index, sGlobalFiles[index].name, sGlobalFiles[index].size);
	}

	bool OLSStorage::IsAvailable(int index)
	{
		return entries[index].state == OLS_STORAGE_READY;
	}

	void OLSStorage::StartNext()
	{
		if (current < 0)
		{
			current = -1;
			for (int i = 0; i < count; i++)
			{
				if (entries[i].state == OLS_STORAGE_DOWNLOAD_WAITING || entries[i].state == OLS_STORAGE_UPLOAD_WAITING)
				{
					current = i;
					break;
				}
			}
			if (current >= 0)
			{
				if (entries[current].state == OLS_STORAGE_DOWNLOAD_WAITING)
				{
					handle = OpenRead(0, entries[current].name, entries[current].size);
					if (handle < 0)
					{
						goto fail;
					}
					entries[current].state = OLS_STORAGE_DOWNLOADING;
					return;
				}
				if (entries[current].state == OLS_STORAGE_UPLOAD_WAITING)
				{
					handle = OpenWrite(0, entries[current].name, entries[current].data, entries[current].size);
					if (handle < 0)
					{
					fail:
						current = -2;
						return;
					}
					entries[current].state = OLS_STORAGE_UPLOADING;
				}
			}
		}
	}

	void OLSStorage::Finish(int failed)
	{
		if (current >= 0)
		{
			OLSStorageMessage message(2);
			message.unknown10 = failed;
			message.user = current;
			entries[current].state = OLS_STORAGE_READY;
			if (message.unknown10 != 0)
			{
				entries[current].state = OLS_STORAGE_FAILED;
			}
			current = -1;
			StartNext();
			OLS::Get()->SendMessage(&message);
		}
	}

	void OLSStorage::OnReadable()
	{
		if (current >= 0)
		{
			int size = GetSize(handle);
			OLSStorageMessage message(1);
			message.user = current;
			if (size > 0)
			{
				entries[current].size = size;
				entries[current].data = (char*)AllocateManagerObject(size, 1, entries[current].name);
				Read(handle, entries[current].data, size);
				entries[current].state = OLS_STORAGE_READY;
				message.unknown10 = 0;
			}
			else
			{
				entries[current].state = OLS_STORAGE_FAILED;
				message.unknown10 = -1;
			}
			int finished = handle;
			current = -1;
			CloseHandle(finished);
			OLS::Get()->SendMessage(&message);
		}
	}

	void OLSStorage::ClearAll()
	{
		for (int i = 0; i < count; i++)
		{
			Clear(i);
		}
	}

	void OLSStorage::Clear(int index)
	{
		entries[index].state = OLS_STORAGE_EMPTY;
		if (entries[index].data != 0)
		{
			core::Free(entries[index].data);
			entries[index].data = 0;
		}
		if (lineEntry == index)
		{
			lineEntry = -1;
		}
	}

	// FUNCTION: ENGINE 0x108C5D50
	// EQUIVALENT: the engine saves all four registers in the entry block (ours saves them behind the early exit) and keeps the entry in edx, the line number in eax
	const char* OLSStorage::ReadLine(int index, int wanted)
	{
		OLSStorageEntry* entry = &entries[index];
		if (entry->state != OLS_STORAGE_READY)
		{
			return 0;
		}
		if (lineEntry != index || lineNumber > wanted)
		{
			lineEntry = index;
			lineNumber = -1;
			lineOffset = 0;
		}
		if (lineNumber != wanted)
		{
			if (lineOffset >= entry->size)
			{
				return 0;
			}
			while (lineNumber < wanted)
			{
				lineNumber++;
				int length = 0;
				do
				{
					OLSStorageEntry* source = &entries[index];
					if (lineOffset >= source->size || source->data[lineOffset] == '\n')
					{
						lineOffset++;
						line[length] = 0;
						break;
					}
					line[length] = source->data[lineOffset];
					lineOffset++;
					length++;
				}
				while (length < 0x4F);
				line[0x4F] = 0;
			}
		}
		return line;
	}

	char* OLSStorage::GetData(int index)
	{
		if (entries[index].state == OLS_STORAGE_READY)
		{
			return entries[index].data;
		}
		return 0;
	}

	void OLSStorage::OnMessage(OLSMessage* message)
	{
		if (current >= 0 && message->type == 7)
		{
			unsigned short id = message->id;
			if (id == 0)
			{
				if (message->user == handle)
				{
					OnReadable();
				}
			}
			else if (id == 1 || id == 2)
			{
				if (message->user == 0)
				{
					gGlobalFileUser->OnGlobalFile();
				}
			}
			else if (id == 3)
			{
				if (message->user == handle)
				{
					Finish(message->unknown10);
				}
			}
		}
		else if (message->type == 0 && message->id == 7)
		{
			Download(0);
		}
	}

	OLSStorage::~OLSStorage()
	{
		LuaScriptManager* scripts = GetScriptManager();
		scripts->Unregister(this);
		ClearAll();
		OLS::Get()->RemoveCallback(this);
		delete[] entries;
	}

	void OLSStorage::Register()
	{
		OLS::Get()->AddCallback(this);
	}

	void OLSStorage::CloseHandle(int closed)
	{
		StartNext();
	}

	void OLSStorage::Queue(int index, const char* name, int size)
	{
		if (entries[index].state != OLS_STORAGE_READY)
		{
			Clear(index);
			entries[index].name = name;
			entries[index].size = size;
			entries[index].state = OLS_STORAGE_DOWNLOAD_WAITING;
			StartNext();
		}
	}

	void OLSStorage::LoadFile(int index, const char* path, int maxSize)
	{
		core::IFile* file;
		core::FileSystemOpenFile(&file, core::FilePath(path), false, 0, 1, 0, 1, 1, 0);
		if (file->IsOpen())
		{
			unsigned int size = file->GetCurrentSize();
			if (maxSize < (int)size)
			{
				file->Release();
				return;
			}
			Clear(index);
			entries[index].name = path;
			entries[index].size = size;
			entries[index].state = OLS_STORAGE_UPLOAD_WAITING;
			entries[index].data = (char*)AllocateManagerObject(size, 1, entries[current].name);
			file->ReadWait(entries[index].data, size, 1);
			StartNext();
		}
		file->Release();
	}

	OLSStorage::OLSStorage(int newCount) :
		count(newCount),
		current(-1)
	{
		entries = new OLSStorageEntry[count];
		for (int i = 0; i < count; i++)
		{
			entries[i].data = 0;
			entries[i].size = 0;
			entries[i].state = 0;
		}
		lineEntry = -1;
		LuaScriptManager* scripts = GetScriptManager();
		scripts->SetOwner(this);
		scripts->RegisterMethod("ols_DownloadGlobalFile", this, &OLSStorage::Download);
		scripts->RegisterMethod("ols_LoadAndUploadAllGlobalFiles", this, &OLSStorage::LoadAndUploadAll);
		scripts->RegisterMethod("ols_LoadAndUploadGlobalFile", this, &OLSStorage::LoadAndUpload);
		scripts->RegisterMethod("ols_ClearGlobalFile", this, &OLSStorage::Clear);
		scripts->RegisterMethod("ols_ReadGlobalFileLine", this, &OLSStorage::ReadLine);
		scripts->RegisterMethod("ols_IsGlobalFileAvailable", this, &OLSStorage::IsAvailable);
		scripts->ClearOwner();
	}
}

template class Method0<engine::OLSStorage, void>;
template class Method1<engine::OLSStorage, void, int>;
template class Method2<engine::OLSStorage, const char*, int, int>;
template class Method1<engine::OLSStorage, bool, int>;
template class Closure0<engine::OLSStorage, void>;
template class Closure1<engine::OLSStorage, void, int>;
template class Closure2<engine::OLSStorage, const char*, int, int>;
template class Closure1<engine::OLSStorage, bool, int>;
template void engine::LuaScriptManager::RegisterMethod<engine::OLSStorage, void>(const char*, engine::OLSStorage*,
	void (engine::OLSStorage::*)());
template void engine::LuaScriptManager::RegisterMethod<engine::OLSStorage, void, int>(const char*,
	engine::OLSStorage*, void (engine::OLSStorage::*)(int));
template void engine::LuaScriptManager::RegisterMethod<engine::OLSStorage, const char*, int, int>(const char*,
	engine::OLSStorage*, const char* (engine::OLSStorage::*)(int, int));
template void engine::LuaScriptManager::RegisterMethod<engine::OLSStorage, bool, int>(const char*,
	engine::OLSStorage*, bool (engine::OLSStorage::*)(int));

// FUNCTION: ENGINE 0x108C59A0 @ public: virtual void __thiscall engine::OLSStorage::DownloadAll(void)
// FUNCTION: ENGINE 0x108C5A00 @ public: virtual void __thiscall engine::OLSStorage::LoadAndUploadAll(void)
// FUNCTION: ENGINE 0x108C5CD0 @ public: virtual void __thiscall engine::OLSStorage::ClearAll(void)
// FUNCTION: ENGINE 0x108C5E20 @ public: virtual void __thiscall engine::OLSStorage::OnMessage(struct engine::OLSMessage *)
// FUNCTION: ENGINE 0x108C5FF0 @ public: virtual void __thiscall engine::OLSStorage::LoadFile(int,char const *,int)

// ---- annotations of the functions mapped in symbols.txt (generated) ----

// FUNCTION: ENGINE 0x108C5950 @ engine::OLSStorageMessage::OLSStorageMessage(short)
// FUNCTION: ENGINE 0x108C5990 @ engine::OLSMessage::~OLSMessage(void) (name guess; identical copies)
// FUNCTION: ENGINE 0x108C59D0 @ void engine::OLSStorage::Download(int)
// FUNCTION: ENGINE 0x108C5A30 @ void engine::OLSStorage::LoadAndUpload(int)
// FUNCTION: ENGINE 0x108C5A60 @ bool engine::OLSStorage::IsAvailable(int)
// FUNCTION: ENGINE 0x108C5A80 @ void engine::OLSStorage::StartNext(void)
// FUNCTION: ENGINE 0x108C5B40 @ void engine::OLSStorage::Finish(int)
// FUNCTION: ENGINE 0x108C5BD0 @ void engine::OLSStorage::OnReadable(void)
// FUNCTION: ENGINE 0x108C5D00 @ void engine::OLSStorage::Clear(int)
// FUNCTION: ENGINE 0x108C5E00 @ char * engine::OLSStorage::GetData(int)
// FUNCTION: ENGINE 0x108C5EB0 @ Method0<engine::OLSStorage,void>::Method0<engine::OLSStorage,void>(char const *,void (engine::OLSStorage::*)())
// FUNCTION: ENGINE 0x108C5EF0 @ Method0<OLSStorage, void>::Call
// FUNCTION: ENGINE 0x108C5F00 @ [thunk]: engine::OLSStorage::`vcall'{52,{flat}}' }'
// FUNCTION: ENGINE 0x108C5F10 @ [thunk]: engine::OLSStorage::`vcall'{40,{flat}}' }'
// FUNCTION: ENGINE 0x108C5F20 @ [thunk]: engine::OLSStorage::`vcall'{56,{flat}}' }'
// FUNCTION: ENGINE 0x108C5F30 @ [thunk]: engine::OLSStorage::`vcall'{44,{flat}}' }'
// FUNCTION: ENGINE 0x108C5F40 @ void * engine::OLSStorageMessage::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108C5F60 @ engine::OLSStorage::~OLSStorage(void)
// FUNCTION: ENGINE 0x108C5FA0 @ void engine::OLSStorage::operator delete(void *)
// FUNCTION: ENGINE 0x108C5FB0 @ void engine::OLSStorage::Register(void)
// FUNCTION: ENGINE 0x108C5FE0 @ void engine::OLSStorage::CloseHandle(int)
// FUNCTION: ENGINE 0x108C60D0 @ void engine::OLSStorage::Queue(int,char const *,int)
// FUNCTION: ENGINE 0x108C6120 @ Closure0<engine::OLSStorage,void>::Closure0<engine::OLSStorage,void>(char const *,engine::OLSStorage *,void (engine::OLSStorage::*)())
// FUNCTION: ENGINE 0x108C6170 @ void Method0<engine::OLSStorage,void>::Invoke(void *,union engine::FunctionArgument const *,void *)
// FUNCTION: ENGINE 0x108C6190 @ Method1<engine::OLSStorage,void,int>::Method1<engine::OLSStorage,void,int>(char const *,void (engine::OLSStorage::*)(int))
// FUNCTION: ENGINE 0x108C61E0 @ void Method1<engine::OLSStorage,void,int>::Call(engine::OLSStorage *,union engine::FunctionArgument const *,void *,void (engine::OLSStorage::*)(int))
// FUNCTION: ENGINE 0x108C6200 @ void Method1<engine::OLSStorage,void,int>::Invoke(void *,union engine::FunctionArgument const *,void *)
// FUNCTION: ENGINE 0x108C6220 @ Method2<engine::OLSStorage,char const *,int,int>::Method2<engine::OLSStorage,char const *,int,int>(char const *,char const * (engine::OLSStorage::*)(int,int))
// FUNCTION: ENGINE 0x108C6280 @ void Method2<engine::OLSStorage,char const *,int,int>::Call(engine::OLSStorage *,union engine::FunctionArgument const *,void *,char const * (engine::OLSStorage::*)(int,in
// FUNCTION: ENGINE 0x108C62B0 @ void Method2<engine::OLSStorage,char const *,int,int>::Invoke(void *,union engine::FunctionArgument const *,void *)
// FUNCTION: ENGINE 0x108C62E0 @ Method1<engine::OLSStorage,bool,int>::Method1<engine::OLSStorage,bool,int>(char const *,bool (engine::OLSStorage::*)(int))
// FUNCTION: ENGINE 0x108C6330 @ void Method1<engine::OLSStorage,bool,int>::Call(engine::OLSStorage *,union engine::FunctionArgument const *,void *,bool (engine::OLSStorage::*)(int))
// FUNCTION: ENGINE 0x108C6350 @ void Method1<engine::OLSStorage,bool,int>::Invoke(void *,union engine::FunctionArgument const *,void *)
// FUNCTION: ENGINE 0x108C6380 @ void * engine::OLSStorage::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108C63A0 @ void engine::LuaScriptManager::RegisterMethod<engine::OLSStorage,void>(char const *,engine::OLSStorage *,void (engine::OLSStorage::*)())
// FUNCTION: ENGINE 0x108C6420 @ Closure1<engine::OLSStorage,void,int>::Closure1<engine::OLSStorage,void,int>(char const *,engine::OLSStorage *,void (engine::OLSStorage::*)(int))
// FUNCTION: ENGINE 0x108C6480 @ void Closure1<engine::OLSStorage,void,int>::Invoke(void *,union engine::FunctionArgument const *,void *)
// FUNCTION: ENGINE 0x108C64A0 @ void Closure0<engine::OLSStorage,void>::Invoke(void *,union engine::FunctionArgument const *,void *)
// FUNCTION: ENGINE 0x108C64E0 @ void Closure2<engine::OLSStorage,char const *,int,int>::Invoke(void *,union engine::FunctionArgument const *,void *)
// FUNCTION: ENGINE 0x108C6510 @ Closure1<engine::OLSStorage,bool,int>::Closure1<engine::OLSStorage,bool,int>(char const *,engine::OLSStorage *,bool (engine::OLSStorage::*)(int))
// FUNCTION: ENGINE 0x108C6570 @ void Closure1<engine::OLSStorage,bool,int>::Invoke(void *,union engine::FunctionArgument const *,void *)
// FUNCTION: ENGINE 0x108C65A0 @ void engine::LuaScriptManager::RegisterMethod<engine::OLSStorage,void,int>(char const *,engine::OLSStorage *,void (engine::OLSStorage::*)(int))
// FUNCTION: ENGINE 0x108C65F0 @ void engine::LuaScriptManager::RegisterMethod<engine::OLSStorage,char const *,int,int>(char const *,engine::OLSStorage *,char const * (engine::OLSStorage::*)(int,int))
// FUNCTION: ENGINE 0x108C6650 @ void engine::LuaScriptManager::RegisterMethod<engine::OLSStorage,bool,int>(char const *,engine::OLSStorage *,bool (engine::OLSStorage::*)(int))
// FUNCTION: ENGINE 0x108C66A0 @ engine::OLSStorage::OLSStorage(int)
