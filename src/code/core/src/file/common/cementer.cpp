#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <string.h>

#include "code/core/criticalsection.h"
#include "code/core/file/cementlibrary.h"
#include "code/core/file/filesystem.h"
#include "code/core/file/request.h"
#include "code/core/memory/align.h"
#include "code/core/report.h"

#define CEMENTER_FILE "..\\..\\..\\code\\core\\src\\file\\common\\cementer.cpp"

namespace core
{
	const char* CoreName();

	// FUNCTION: ENGINE 0x106502A0
	inline unsigned int GetEntrySize(const CementHeader* header)
	{
		unsigned int size = 0xC;
		if (!header->compact)
		{
			size = 0x14;
		}
		return size;
	}

	// Binary search of the directory
	// FUNCTION: ENGINE 0x106502C0
	CementEntry* FindEntry(void* entries, unsigned int count, unsigned int key, unsigned int size)
	{
		unsigned int low = 0;
		unsigned int high = count - 1;
		if (count < 1)
		{
			return 0;
		}
		while (low <= high)
		{
			unsigned int middle = (high >> 1) + (low >> 1);
			if ((low & 1) && (high & 1))
			{
				middle++;
			}
			CementEntry* entry = (CementEntry*)((char*)entries + middle * size);
			if (entry->key == key)
			{
				return entry;
			}
			if (entry->key < key)
			{
				low = middle + 1;
			}
			else
			{
				if (middle == 0)
				{
					return 0;
				}
				high = middle - 1;
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10650330
	void CementLibrary::Lock()
	{
		file->Lock();
	}

	// FUNCTION: ENGINE 0x10650340
	void CementLibrary::Unlock()
	{
		file->Unlock();
	}

	// FUNCTION: ENGINE 0x10650350
	int CementLibrary::GetState()
	{
		return state;
	}

	// FUNCTION: ENGINE 0x10650360
	void CementLibrary::Wait()
	{
		while (state == 0)
		{
			FileSystemUpdate();
			ThreadSleep(0);
		}
	}

	// FUNCTION: ENGINE 0x10650390
	bool CementLibrary::IsOpen()
	{
		return state == 1;
	}

	// FUNCTION: ENGINE 0x106503A0
	void CementLibrary::SetCallback(IFileCompletionCallback* function, void* data)
	{
		callback = function;
		userData = data;
		callback->AddRef();
	}

	// FUNCTION: ENGINE 0x106503C0
	bool CementLibrary::IsValid()
	{
		bool valid = true;
		if (strcmp(header.magic, "ATG CORE CEMENT LIBRARY") != 0)
		{
			valid = false;
		}
		if (header.version != 2 || header.unknown23 == 0)
		{
			valid = false;
		}
		if (header.compact >= 2)
		{
			valid = false;
		}
		if (header.compact == 0 && m_pRegistrationDrive != m_pDrive)
		{
			valid = false;
		}
		if (header.unknown22 != 0)
		{
			valid = false;
		}
		return valid;
	}

	// FUNCTION: ENGINE 0x10650410
	void CementLibrary::Finish(int value)
	{
		state = value;
		if (callback != 0)
		{
			callback->OnComplete(userData);
			callback->Release();
			callback = 0;
			userData = 0;
		}
	}

	// FUNCTION: ENGINE 0x10650450
	int CementLibrary::GetPass()
	{
		return pass;
	}

	// FUNCTION: ENGINE 0x10650460
	void CementLibrary::OpenFile(IFile** opened, unsigned int hash, int key, int unused1, int unused2, int unused3)
	{
		char name[16];
		sprintf(name, "0x%X", hash);
		File* entry = new File(m_pDrive, name, false, 0, key, unused1, unused2, unused3, false, 0);
		*opened = entry;
		m_pDrive->Submit(new FileOpenByKeyRequest(entry, hash, this), key, false);
	}

	// FUNCTION: ENGINE 0x10650500
	void CementLibrary::OpenFileWait(IFile** opened, unsigned int hash, int key, int unused1, int unused2,
		int unused3)
	{
		OpenFile(opened, hash, key, unused1, unused2, unused3);
		if (*opened != 0)
		{
			(*opened)->Wait();
		}
	}

	// FUNCTION: ENGINE 0x10650540
	CementLibraryList::~CementLibraryList()
	{
		for (unsigned int i = 0; i < 2; i++)
		{
			CementLibrary* library = heads[i];
			while (library != 0)
			{
				CementLibrary* current = library;
				library = library->next;
				current->Release();
			}
		}
		CriticalSectionDelete(section);
	}

	// FUNCTION: ENGINE 0x10650580
	void CementLibraryList::Add(CementLibrary* library)
	{
		CriticalSectionEnter(section);
		int pass = library->GetPass();
		if (heads[pass] == 0)
		{
			heads[pass] = library;
		}
		else
		{
			tails[pass]->next = library;
		}
		library->next = 0;
		tails[pass] = library;
		CriticalSectionLeave(section);
	}

	// FUNCTION: ENGINE 0x106505D0
	void CementLibraryList::Remove(CementLibrary* library)
	{
		CriticalSectionEnter(section);
		int pass = library->GetPass();
		CementLibrary** link = &heads[pass];
		CementLibrary* previous = 0;
		while (*link != 0)
		{
			if (*link == library)
			{
				if (library == cursor)
				{
					cursor = cursor->next;
				}
				*link = (*link)->next;
				break;
			}
			previous = *link;
			link = &(*link)->next;
		}
		if (*link == 0)
		{
			tails[pass] = previous;
		}
		CriticalSectionLeave(section);
	}

	// FUNCTION: ENGINE 0x10650640
	void CementLibraryList::Begin(int pass)
	{
		CriticalSectionEnter(section);
		cursor = heads[pass];
	}

	// FUNCTION: ENGINE 0x10650660
	CementLibrary* CementLibraryList::Next()
	{
		CementLibrary* library = cursor;
		if (library != 0)
		{
			cursor = library->next;
		}
		return library;
	}

	// FUNCTION: ENGINE 0x10650670
	void CementLibraryList::End()
	{
		cursor = 0;
		CriticalSectionLeave(section);
	}

	// FUNCTION: ENGINE 0x10650690
	void CementLibraryList::GetBuffer(void** data, unsigned int* size)
	{
		*data = buffer;
		*size = bufferSize;
	}

	// FUNCTION: ENGINE 0x106506B0
	void CementLibraryList::AcquireBuffer(int heap, unsigned int align, unsigned int round)
	{
		if (bufferRefs == 0)
		{
			bufferHeap = heap;
			bufferSize = RoundUp(GetMountsValue(), round);
			buffer = HeapAllocAligned(bufferHeap, bufferSize, align);
		}
		bufferRefs++;
	}

	// FUNCTION: ENGINE 0x106506F0
	void CementLibraryList::ReleaseBuffer()
	{
		if (bufferRefs == 1)
		{
			HeapFreeAligned(bufferHeap, buffer);
			buffer = 0;
			bufferSize = 0;
		}
		bufferRefs--;
	}

	// FUNCTION: ENGINE 0x10650730
	CementLibrary::~CementLibrary()
	{
		if (state == 0)
		{
			file->Cancel();
		}
		else if (state == 1)
		{
			if (header.packed > 0)
			{
				static bool sAssertDrive = true;
				if (sAssertDrive && m_pRegistrationDrive != m_pDrive
					&& Report(1, " oldassert ", CEMENTER_FILE, 224, "m_pRegistrationDrive == m_pDrive", 0) == 3)
				{
					sAssertDrive = false;
				}
				m_pRegistrationDrive->GetLibraries()->ReleaseBuffer();
			}
			m_pRegistrationDrive->RemoveLibrary(this);
		}
		file->Release();
		file = 0;
		m_pDrive->Release();
		m_pDrive = 0;
		m_pRegistrationDrive->Release();
		m_pRegistrationDrive = 0;
		if (directory != 0)
		{
			HeapFreeAligned(directoryHeap, directory);
		}
	}

	// FUNCTION: ENGINE 0x10650830
	void CementLibrary::AddRef()
	{
		SafeRefCount::AddRef();
	}

	// FUNCTION: ENGINE 0x10650850
	void CementLibrary::Release()
	{
		SafeRefCount::Release();
	}

	// FUNCTION: ENGINE 0x106508E0
	void CementLibrary::OnComplete(void* data)
	{
		if (state == 1)
		{
			Finish(2);
			return;
		}
		int step = (int)data;
		if (step == 0)
		{
			if (!file->IsOpen())
			{
				Finish(2);
				return;
			}
			file->SetField12C(1);
			file->SetPosition(0);
			file->Read(&header, sizeof(header), 1);
			file->Notify(this, (void*)1);
			return;
		}
		if (step == 1)
		{
			if (file->GetError() != 0)
			{
				return;
			}
			if (!IsValid())
			{
				Finish(2);
				return;
			}
			directory = HeapAllocAligned(directoryHeap, header.directorySize, 0x10);
			file->SetPosition(header.directoryOffset);
			file->Read(directory, header.directorySize, 1);
			file->Notify(this, (void*)2);
			return;
		}
		if (step == 2)
		{
			if (preloaded)
			{
				if (!file->IsOpen())
				{
					Finish(2);
					return;
				}
				if (!IsValid())
				{
					Finish(2);
					return;
				}
			}
			else if (file->GetError() != 0)
			{
				Finish(2);
				return;
			}
			file->SetField12C(0);
			if (header.packed > 0)
			{
				static bool sAssertDrive = true;
				if (sAssertDrive && m_pRegistrationDrive != m_pDrive
					&& Report(1, " oldassert ", CEMENTER_FILE, 560, "m_pRegistrationDrive == m_pDrive", 0) == 3)
				{
					sAssertDrive = false;
				}
				int objectHeap = heap;
				m_pRegistrationDrive->GetLibraries()->AcquireBuffer(objectHeap, file->GetGranularity(), 0x10);
			}
			m_pRegistrationDrive->AddLibrary(this);
			Finish(1);
		}
	}

	// FUNCTION: ENGINE 0x10650AB0
	bool CementLibrary::Find(int key, FileCache* cache)
	{
		if (state == 1)
		{
			CementEntry* entry = FindEntry(directory, header.count, key, GetEntrySize(&header));
			if (entry != 0)
			{
				unsigned int size = entry->size;
				int mode = 0;
				if (!header.compact)
				{
					mode = entry->mode;
					size = entry->unpackedSize;
				}
				void* buffer;
				unsigned int bufferSize;
				m_pDrive->GetLibraries()->GetBuffer(&buffer, &bufferSize);
				cache->Open(file, entry->offset, size, entry->size, mode, buffer, bufferSize, header.packed);
				return true;
			}
			return false;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10650B60
	CementLibraryList::CementLibraryList()
		: cursor(0), buffer(0), bufferSize(0), bufferRefs(0), bufferHeap(0)
	{
		CoreName();
		for (unsigned int i = 0; i < 2; i++)
		{
			heads[i] = 0;
			tails[i] = 0;
		}
		CriticalSectionInit(section);
	}

	// FUNCTION: ENGINE 0x10650BA0
	CementLibrary::CementLibrary(Drive* drive, File* archive, int index, CementPreload* preload,
		Drive* registrationDrive)
		: SafeRefCount(1), m_pDrive(drive), m_pRegistrationDrive(registrationDrive), file(archive), state(0),
		directory(0), next(0), pass(index), callback(0), userData(0), preloaded(preload != 0)
	{
		CoreName();
		m_pDrive->AddRef();
		m_pRegistrationDrive->AddRef();
		file->AddRef();
		if (preloaded)
		{
			header = *preload->header;
			directory = preload->directory;
			directoryHeap = preload->heap;
			file->Notify(this, (void*)2);
		}
		else
		{
			directoryHeap = heap;
			file->Notify(this, (void*)0);
		}
	}

	// FUNCTION: ENGINE 0x10650CF0
	bool CementLibrary::Matches(const char* path, FileCache* cache)
	{
		if (*path == '\\')
		{
			path++;
		}
		int key = FileSystemHashPath(path);
		return Find(key, cache);
	}

	// FUNCTION: ENGINE 0x10650D20
	void CreateCementLibrary(ICementLibrary** library, Drive* drive, const char* path, int pass, int heap, int preload,
		Drive* registrationDrive)
	{
		File* file = new File(drive, path, false, 0, 1, 0, 0, 0, true, 0);
		CementLibrary* created = new (heap) CementLibrary(drive, file, pass, (CementPreload*)preload,
			registrationDrive);
		file->Release();
		*library = created;
	}
}
