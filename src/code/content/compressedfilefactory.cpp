// content::CompressedFileFactory: the thread that unpacks compressed files (unit 0x1060BBD0 - 0x1060BF00; see
// compressedfile.h; the file name is guessed, no assert path survives).
#include "code/content/compressedfile.h"
#include "code/container/string.h"
#include "code/core/criticalsection.h"
#include "code/core/thread.h"
#include <new>

namespace content
{
	// The extension compressed files have: the number the factory passes on to the file it makes
	// (the path in eax: file-local in the original)
	static int GetPassthrough(const char* path)
	{
		container::StringLiteral literal(path);
		int dot = literal.FindLast('.', -1, true);
		if (dot < 0)
		{
			return 0;
		}
		container::StringC<32> extension;
		extension.Mid(literal, dot + 1, 0x7FFFFFFF);
		return MatchesCompressedExtension(extension.buffer);
	}

	// FUNCTION: ENGINE 0x1060BBD0
	bool IsCompressedExtension(const char* extension)
	{
		return MatchesCompressedExtension(extension) != 0;
	}

	// FUNCTION: ENGINE 0x1060BBF0
	CompressedFileFactory::CompressedFileFactory()
	{
		pending = 0;
		stopRequested = false;
		started = false;
	}

	// FUNCTION: ENGINE 0x1060BC20
	void CompressedFileFactory::Stop()
	{
		stopRequested = true;
		core::SemaphoreRelease(&semaphore, 1);
		core::WaitThread(&thread);
		core::DestroyThread(&thread);
		core::SemaphoreDestroy(&semaphore);
		core::CriticalSectionDelete(lock);
		started = false;
	}

	// FUNCTION: ENGINE 0x1060BC70
	void CompressedFileFactory::Create(core::IFile** result, core::IFile* file, int level, unsigned int unpacked,
		unsigned int start, unsigned int size, int heap)
	{
		CompressedFile* compressed = new (heap) CompressedFile(file, level, unpacked, start, size, heap, this);
		compressed->AddRef();
		*result = compressed;
	}

	// FUNCTION: ENGINE 0x1060BCE0
	void CompressedFileFactory::Queue(DecompressRequest* newRequest)
	{
		core::CriticalSectionEnter(lock);
		request = *newRequest;
		pending++;
		core::CriticalSectionLeave(lock);
		core::SemaphoreRelease(&semaphore, 1);
	}

	// FUNCTION: ENGINE 0x1060BD40
	void CompressedFileFactory::Run()
	{
		core::SemaphoreWait(&semaphore);
		while (!stopRequested)
		{
			core::CriticalSectionEnter(lock);
			DecompressRequest current = request;
			pending--;
			core::CriticalSectionLeave(lock);
			current.file->Unpack(current.buffer, current.size);
			core::SemaphoreWait(&semaphore);
		}
	}

	// FUNCTION: ENGINE 0x1060BE20
	bool IsCompressedName(const char* path)
	{
		return GetPassthrough(path) != 0;
	}

	// FUNCTION: ENGINE 0x1060BE30
	int CompressedFileFactory::ThreadMain(void* argument)
	{
		((CompressedFileFactory*)argument)->Run();
		return 0;
	}

	// FUNCTION: ENGINE 0x1060BE40
	void CompressedFileFactory::Start(int heap)
	{
		pending = 0;
		stopRequested = false;
		core::CriticalSectionInit(lock);
		core::SemaphoreCreate(&semaphore, 0);
		core::CreateThread(&thread, ThreadMain, this, 3, 0x2000, 0, "CompressedFileFactory");
		started = true;
	}

	// FUNCTION: ENGINE 0x1060BEA0
	void CompressedFileFactory::Create(core::IFile** result, core::IFile* file, unsigned int start, unsigned int size,
		int heap)
	{
		*result = 0;
		const char* path = file->GetName();
		int passthrough = GetPassthrough(path);
		if (passthrough != 0)
		{
			CompressedFile* compressed = new (heap) CompressedFile(file, passthrough, start, size, heap, this);
			compressed->AddRef();
			*result = compressed;
		}
	}

	// FUNCTION: ENGINE 0x1060DD90
	int MatchesCompressedExtension(const char* extension)
	{
		if (*extension == '.')
		{
			extension++;
		}
		return core::StrICmp(extension, "rz") == 0;
	}
}
