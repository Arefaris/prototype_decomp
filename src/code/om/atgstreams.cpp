// The streams that stand on another object (0x10B6A130 - 0x10B6A5F0).
#include "code/om/atgstreams.h"

namespace om
{
	const char* AtgCoreFileStream::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x10B6A130
	bool AtgCoreFileStream::Write(const void* data, unsigned int size)
	{
		file->Write(data, 1, 1);
		file->WaitSignal();
		return file->GetError() == 0;
	}

	// FUNCTION: ENGINE 0x10B6A170
	bool AtgCoreFileStream::Read(void* data, unsigned int size)
	{
		unsigned int position;
		file->GetPosition(&position);
		file->WaitSignal();
		if (position + size <= file->GetCurrentSize())
		{
			file->Read(data, size, 1);
			file->WaitSignal();
			return file->GetError() == 0;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10B6A1E0
	bool AtgCoreFileStream::GetSize(unsigned int* size)
	{
		*size = file->GetCurrentSize();
		return true;
	}

	// FUNCTION: ENGINE 0x10B6A200
	bool AtgCoreFileStream::GetPosition(unsigned int* position)
	{
		unsigned int current;
		file->GetPosition(&current);
		file->WaitSignal();
		*position = current;
		return file->GetError() == 0;
	}

	// FUNCTION: ENGINE 0x10B6A240
	bool AtgCoreFileStream::Seek(unsigned int position)
	{
		file->SetPosition(position);
		file->WaitSignal();
		return file->GetError() == 0;
	}

	// FUNCTION: ENGINE 0x10B6A2D0
	String AtgCoreFileStream::GetName()
	{
		const char* text = file->GetName();
		String name(text, 1);
		return String(name);
	}

	// FUNCTION: ENGINE 0x10B6A280
	AtgCoreFileStream::~AtgCoreFileStream()
	{
		if (file != 0)
		{
			file->Release();
		}
	}

	// FUNCTION: ENGINE 0x10B6A310
	ErrorLoggingStream::ErrorLoggingStream(Stream* newTarget, Stream** newLog) :
		target(newTarget),
		log(newLog)
	{
	}

	// FUNCTION: ENGINE 0x10B6A3C0
	bool ErrorLoggingStream::Write(const void* data, unsigned int size)
	{
		if (!target->Write(data, size))
		{
			StreamPrintf(*log, "", size, target->GetName().GetText());
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10B6A430
	bool ErrorLoggingStream::Read(void* data, unsigned int size)
	{
		if (!target->Read(data, size))
		{
			StreamPrintf(*log, "", size, target->GetName().GetText());
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10B6A4A0
	bool ErrorLoggingStream::GetSize(unsigned int* size)
	{
		if (!target->GetSize(size))
		{
			StreamPrintf(*log, "", target->GetName().GetText());
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10B6A510
	bool ErrorLoggingStream::GetPosition(unsigned int* position)
	{
		if (!target->GetPosition(position))
		{
			StreamPrintf(*log, "", target->GetName().GetText());
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10B6A580
	bool ErrorLoggingStream::Seek(unsigned int position)
	{
		if (!target->Seek(position))
		{
			StreamPrintf(*log, "", target->GetName().GetText());
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10B6A340
	String ErrorLoggingStream::GetDescription()
	{
		return target->GetName() + String("(ErrorLogging)", 0);
	}
}
