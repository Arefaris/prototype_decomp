// The compression library: see compress.h. The unit is 0x106DBF00 - 0x106DC810 (file name guessed); zlib's own code
// (inflateInit_, inflate, inflateEnd) is library code in other units.
#include <new>

#include "code/compress/compress.h"
#include "code/core/criticalsection.h"
#include "code/core/heap.h"

// zlib 1.2.3 (library code of the engine)
extern "C" int inflateInit_(compress::ZStream* stream, const char* version, int size);
extern "C" int inflate(compress::ZStream* stream, int flush);
extern "C" int inflateEnd(compress::ZStream* stream);

// 0x1127EBC8: the id the task system gave the decompressor's step; 0x1127EBC4: whether the library is started
static int sTaskId;
static bool sStarted;

namespace compress
{
	// 0x106DC390 / 0x106DC7F0: registers the step with the task system; 0x106DC3A0 / 0x106DC740: removes it
	static int RegisterStep();
	static void UnregisterStep();

	static void StartTask();
	static void StopTask();

	// FUNCTION: ENGINE 0x106DBF00
	void Startup()
	{
		StartTask();
		sStarted = true;
	}

	// FUNCTION: ENGINE 0x106DBF10
	void Shutdown()
	{
		StopTask();
		sStarted = false;
	}

	// FUNCTION: ENGINE 0x106DBF20
	void* Stream::operator new(unsigned int size, int heap)
	{
		return core::HeapAlloc(heap, size);
	}

	// FUNCTION: ENGINE 0x106DBF40
	void Stream::operator delete(void* block)
	{
		core::Free(block);
	}

	// FUNCTION: ENGINE 0x106DBF50
	int Stream::GetLevel()
	{
		return level;
	}

	// FUNCTION: ENGINE 0x106DBF60
	int Stream::GetMode()
	{
		return mode;
	}

	// FUNCTION: ENGINE 0x106DBF70
	int Stream::GetStatus()
	{
		core::CriticalSectionEnter(lock);
		int value = status;
		core::CriticalSectionLeave(lock);
		return value;
	}

	// FUNCTION: ENGINE 0x106DBF90
	void Stream::Wait()
	{
		core::EventWait(event);
	}

	// FUNCTION: ENGINE 0x106DBFA0
	int Stream::GetUsedInput()
	{
		core::CriticalSectionEnter(lock);
		int value = usedInput;
		core::CriticalSectionLeave(lock);
		return value;
	}

	// FUNCTION: ENGINE 0x106DBFC0
	int Stream::GetUsedOutput()
	{
		core::CriticalSectionEnter(lock);
		int value = usedOutput;
		core::CriticalSectionLeave(lock);
		return value;
	}

	// FUNCTION: ENGINE 0x106DBFE0
	void Stream::Submit(const void* input, unsigned int inputSize, void* output, unsigned int outputSize, bool last)
	{
		core::CriticalSectionEnter(lock);
		status = 3;
		core::EventReset(event, 0xFFFF);
		core::CriticalSectionLeave(lock);
		compressor->Submit(input, inputSize, last, output, outputSize, &callback);
	}

	// FUNCTION: ENGINE 0x106DC040
	ICompressor* Stream::CreateCompressor(int newLevel, int heap)
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x106DC050
	ICompressor* Stream::CreateDecompressor(int unused, int heap)
	{
		ICompressor* result = 0;
		if (level == 0)
		{
			result = new (heap) Decompressor_Zlib;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x106DC080
	void Stream::SetResult(const StepResult* newResult)
	{
		core::CriticalSectionEnter(lock);
		usedInput = newResult->usedInput;
		usedOutput = newResult->usedOutput;
		status = newResult->status;
		core::CriticalSectionLeave(lock);
		core::EventSignal(event, 0xFFFF);
	}

	// FUNCTION: ENGINE 0x106DC0C0
	Stream::AsyncCallback::AsyncCallback()
	{
		stream = 0;
	}

	// FUNCTION: ENGINE 0x106DC0E0
	Stream::AsyncCallback::~AsyncCallback()
	{
	}

	// FUNCTION: ENGINE 0x106DC0F0
	void Stream::AsyncCallback::SetStream(Stream* newStream)
	{
		stream = newStream;
	}

	// FUNCTION: ENGINE 0x106DC100
	void Stream::AsyncCallback::OnResult(int result)
	{
		stream->SetResult(stream->compressor->GetResult());
	}

	// FUNCTION: ENGINE 0x106DC120
	void Stream::Run(const void* input, unsigned int inputSize, void* output, unsigned int outputSize, bool last)
	{
		core::CriticalSectionEnter(lock);
		status = 3;
		core::EventReset(event, 0xFFFF);
		core::CriticalSectionLeave(lock);
		StepResult step;
		step.status = compressor->Process(input, inputSize, last, output, outputSize, &step.usedInput, &step.usedOutput);
		SetResult(&step);
	}

	// FUNCTION: ENGINE 0x106DC1A0
	Stream::Stream(int newLevel, int newMode, int heap)
		: status(1), usedInput(0), usedOutput(0), level(newLevel), mode(newMode), compressor(0)
	{
		callback.SetStream(this);
		core::CriticalSectionInit(lock);
		core::EventInit(event, 0);
		switch (mode)
		{
		case 0:
			compressor = CreateCompressor(level, heap);
			break;
		case 1:
			compressor = CreateDecompressor(level, heap);
			break;
		}
	}

	// FUNCTION: ENGINE 0x106DC230
	Stream::~Stream()
	{
		if (compressor)
		{
			delete compressor;
		}
		core::EventDestroy(event);
		core::CriticalSectionDelete(lock);
	}
}

namespace content
{
	// FUNCTION: ENGINE 0x106DC260
	compress::Stream* CreateDecompressor(int level, int mode, int heap)
	{
		return new (heap) compress::Stream(level, mode, heap);
	}

	// FUNCTION: ENGINE 0x106DC2B0
	void DestroyDecompressor(compress::Stream* stream)
	{
		if (stream)
		{
			delete stream;
		}
	}
}

namespace compress
{
	// The zlib allocator of the decompressor: the two pieces zlib asks for sit in the object itself (the inflate state
	// and the window), every other request fails
	// FUNCTION: ENGINE 0x106DC320
	static void* AllocateInObject(void* object, unsigned int items, unsigned int size)
	{
		if (items * size == 0x2530)
		{
			return (char*)object + 0xE0;
		}
		if (items * size == 0x8000)
		{
			return (char*)object + 0x2610;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x106DC350
	static void FreeInObject(void* object, void* address)
	{
	}

	// FUNCTION: ENGINE 0x106DC360
	void* Decompressor_Zlib::operator new(unsigned int size, int heap)
	{
		return core::HeapAllocAligned(heap, (size + 15) & ~15u, 16);
	}

	// FUNCTION: ENGINE 0x106DC380
	void Decompressor_Zlib::operator delete(void* block)
	{
		core::FreeAligned(block);
	}

	// FUNCTION: ENGINE 0x106DC390
	static void StartTask()
	{
		sTaskId = RegisterStep();
	}

	// FUNCTION: ENGINE 0x106DC3A0
	static void StopTask()
	{
		UnregisterStep();
	}

	// FUNCTION: ENGINE 0x106DC3C0
	Decompressor_Zlib::~Decompressor_Zlib()
	{
		inflateEnd(&stream);
	}

	// FUNCTION: ENGINE 0x106DC3F0
	// NONMATCHING: the engine keeps the constant 4 in ebp across the function; ours uses immediates (about 90 % of the instructions)
#ifdef NONMATCHING
	int Decompressor_Zlib::Process(const void* newInput, unsigned int newInputSize, bool newLast, void* newOutput,
		unsigned int newOutputSize, int* usedInput, int* usedOutput)
	{
		const int failed = 4;
		if (state == 0 || state == failed)
		{
			return state;
		}
		if (newInput == 0 || newInputSize == 0)
		{
			if (newLast)
			{
				state = mode != 1 ? failed : 0;
				return state;
			}
			state = 1;
			return state;
		}
		if (mode == 1)
		{
			state = failed;
			return failed;
		}
		if (newOutput == 0 || newOutputSize == 0)
		{
			state = 2;
			return 2;
		}
		stream.availIn = newInputSize;
		stream.nextIn = (const unsigned char*)newInput;
		stream.availOut = newOutputSize;
		stream.nextOut = (unsigned char*)newOutput;
		int code = inflate(&stream, 0);
		if (code == 0)
		{
			if (stream.availIn == 0)
			{
				state = newLast ? failed : 1;
			}
			else
			{
				state = (stream.availOut != 0) * 2 + 2;
			}
		}
		else if (code == 1 && stream.availIn == 0)
		{
			state = !newLast;
		}
		else
		{
			state = failed;
		}
		if (state != failed)
		{
			*usedInput = newInputSize - stream.availIn;
			*usedOutput = newOutputSize - stream.availOut;
		}
		return state;
	}
#endif

	// FUNCTION: ENGINE 0x106DC560
	const StepResult* Decompressor_Zlib::GetResult()
	{
		return &result;
	}

	// FUNCTION: ENGINE 0x106DC5D0
	Decompressor_Zlib::Decompressor_Zlib()
	{
		input = 0;
		inputSize = 0;
		last = true;
		output = 0;
		outputSize = 0;
		mode = 0;
		state = 1;
		stream.zalloc = AllocateInObject;
		stream.zfree = FreeInObject;
		stream.opaque = this;
		stream.availIn = 0;
		stream.nextIn = 0;
		inflateInit_(&stream, "1.2.3.0-ATG", sizeof(ZStream));
		result.usedInput = 0;
		result.usedOutput = 0;
		result.status = 1;
	}

	// What the relocation of the decompressor reaches in zlib's inflate state: the window, the two decoding tables and
	// the code buffer
	struct InflateCode;
	struct InflateState
	{
		unsigned char unknown0[0x34];
		unsigned char* window;
		unsigned char unknown38[0x4C - 0x38];
		const InflateCode* lengthCodes;
		const InflateCode* distanceCodes;
		unsigned char unknown54[0x6C - 0x54];
		unsigned short* next;
	};

	// A pointer into the block, moved with the block (the engine has one copy per pointer type)
	template<class T> static T* Move(T* pointer, int distance)
	{
		if (pointer == 0)
		{
			return pointer;
		}
		return (T*)((char*)pointer + distance);
	}

	// The five copies of the helper the engine keeps, one per pointer type
	// FUNCTION: ENGINE 0x106DC580
	template InflateState* Move<InflateState>(InflateState*, int);
	// FUNCTION: ENGINE 0x106DC590
	template unsigned char* Move<unsigned char>(unsigned char*, int);
	// FUNCTION: ENGINE 0x106DC5A0
	template const InflateCode* Move<const InflateCode>(const InflateCode*, int);
	// FUNCTION: ENGINE 0x106DC5B0
	template unsigned short* Move<unsigned short>(unsigned short*, int);
	// FUNCTION: ENGINE 0x106DC5C0
	template void* Move<void>(void*, int);

	// FUNCTION: ENGINE 0x106DC680
	// The object moved from one address to another: every pointer zlib keeps inside the block follows
	void RelocateDecompressor(Decompressor_Zlib* object, char* newBase, char* oldBase,
		void* (*allocate)(void*, unsigned int, unsigned int), void (*release)(void*, void*), void* opaque, bool keepState)
	{
		int distance = newBase - oldBase;
		InflateState* state = (InflateState*)object->stream.state;
		if (!keepState)
		{
			state = Move(state, distance);
		}
		state->window = Move(state->window, distance);
		state->lengthCodes = Move(state->lengthCodes, distance);
		state->distanceCodes = Move(state->distanceCodes, distance);
		state->next = Move(state->next, distance);
		object->stream.state = Move(object->stream.state, distance);
		object->stream.zalloc = allocate;
		object->stream.zfree = release;
		object->stream.opaque = opaque;
	}

	// FUNCTION: ENGINE 0x106DC700
	Decompressor_Zlib::Decompressor_Zlib(Decompressor_Zlib* from)
	{
		RelocateDecompressor(this, (char*)this, (char*)from, AllocateInObject, FreeInObject, this, false);
	}

	// FUNCTION: ENGINE 0x106DC740
	static void UnregisterStep()
	{
		core::UnregisterAsyncTaskFunction(sTaskId);
	}

	// FUNCTION: ENGINE 0x106DC750
	void Decompressor_Zlib::RunStep(void* data, core::AsyncTaskCallback* callback)
	{
		Decompressor_Zlib* object = (Decompressor_Zlib*)data;
		object->result.status = object->Process(object->input, object->inputSize, object->last, object->output,
			object->outputSize, &object->result.usedInput, &object->result.usedOutput);
		if (callback)
		{
			callback->SetResult(0);
		}
	}

	// FUNCTION: ENGINE 0x106DC7A0
	// NONMATCHING: the engine loads the first two arguments in the other registers (83.1 %)
#ifdef NONMATCHING
	void Decompressor_Zlib::Submit(const void* newInput, unsigned int newInputSize, bool newLast, void* newOutput,
		unsigned int newOutputSize, core::AsyncTaskCallback* callback)
	{
		inputSize = newInputSize;
		input = newInput;
		output = newOutput;
		last = newLast;
		outputSize = newOutputSize;
		job.Set(sTaskId, this, callback);
		job.Submit(0);
	}
#endif

	// FUNCTION: ENGINE 0x106DC7F0
	static int RegisterStep()
	{
		int id;
		core::RegisterAsyncTaskFunction("Decompressor_Zlib", Decompressor_Zlib::RunStep, &id);
		return id;
	}
}
