// The compression library (RTTI names compress::ICompressor, compress::Decompressor_Zlib and
// compress::Stream::AsyncCallback; the other names are guesses): a stream that runs a compressor on a worker thread
// and keeps the outcome of the last step for the thread that asked (content::CompressedFile uses it through
// content::CreateDecompressor). The decompressor is zlib 1.2.3 ("1.2.3.0-ATG") with its state in the object itself.
#ifndef COMPRESS_COMPRESS_H
#define COMPRESS_COMPRESS_H

#include "code/core/asynctask.h"

namespace compress
{
	// What a step of a compressor reports: how much of the input and of the output it used and how it ended
	struct StepResult
	{
		int usedInput;
		int usedOutput;
		int status;
	};

	// 4 vftable slots; the last three are pure
	class ICompressor
	{
	public:
		// 0x106DC3B0 / 0x106DC2F0 (the deleting form is 0x106DC300)
		ICompressor()
		{
		}
		virtual ~ICompressor()
		{
		}
		// Runs one step over the input and the room for output; the used amounts go to the last two arguments. Returns
		// the status (0 done, 1 needs input, 2 needs output, 4 failed; names guessed)
		virtual int Process(const void* input, unsigned int inputSize, bool last, void* output, unsigned int outputSize,
			int* usedInput, int* usedOutput) = 0;
		// Runs a step on a worker thread; the callback is told when it has finished
		virtual void Submit(const void* input, unsigned int inputSize, bool last, void* output, unsigned int outputSize,
			core::AsyncTaskCallback* callback) = 0;
		// The outcome of the last step
		virtual const StepResult* GetResult() = 0;
	};

	// zlib's z_stream (the fields past the pointers are the allocator and the type)
	struct ZStream
	{
		const unsigned char* nextIn;
		unsigned int availIn;
		unsigned int totalIn;
		unsigned char* nextOut;
		unsigned int availOut;
		unsigned int totalOut;
		char* msg;
		void* state;
		void* (*zalloc)(void* opaque, unsigned int items, unsigned int size);
		void (*zfree)(void* opaque, void* address);
		void* opaque;
		int dataType;
		unsigned int adler;
		unsigned int reserved;
	};

	// 0xA610 bytes: the object, the zlib state (0xE0) and the window (0x2610) follow each other in one block that is
	// handed to zlib piece by piece
	class Decompressor_Zlib : public ICompressor
	{
	public:
		// 0x106DC5D0
		Decompressor_Zlib();
		// 0x106DC700: the object copied to another address (the pointers zlib keeps inside it are moved by the
		// difference of the two)
		explicit Decompressor_Zlib(Decompressor_Zlib* from);
		// 0x106DC3C0 (the deleting form is 0x106DC660)
		virtual ~Decompressor_Zlib();
		// 0x106DC3F0
		virtual int Process(const void* input, unsigned int inputSize, bool last, void* output, unsigned int outputSize,
			int* usedInput, int* usedOutput);
		// 0x106DC7A0
		virtual void Submit(const void* input, unsigned int inputSize, bool last, void* output, unsigned int outputSize,
			core::AsyncTaskCallback* callback);
		// 0x106DC560
		virtual const StepResult* GetResult();

		// 0x106DC360 / 0x106DC380: 16-byte aligned blocks from the heap
		static void* operator new(unsigned int size, int heap);
		static void operator delete(void* block);

		// The step the worker thread runs (0x106DC750)
		static void RunStep(void* data, core::AsyncTaskCallback* callback);

		unsigned char unknown4[0xC];
		core::AsyncTaskJob job;
		unsigned char unknown58[8];
		// The arguments of the submitted step
		const void* input;
		unsigned int inputSize;
		bool last;
		void* output;
		unsigned int outputSize;
		unsigned char unknown74[0xC];
		int mode;
		int state;
		StepResult result;
		unsigned char unknown94[0xC];
		ZStream stream;
		unsigned char unknownD8[0xA610 - 0xD8];
	};

	class Stream
	{
	public:
		// The callback the worker thread tells when a step has finished: it hands the compressor's result to the stream
		class AsyncCallback : public core::AsyncTaskCallback
		{
		public:
			// 0x106DC0C0 (the destructor is 0x106DC0E0)
			AsyncCallback();
			~AsyncCallback();
			// 0x106DC0F0
			void SetStream(Stream* newStream);
			// 0x106DC100
			virtual void OnResult(int result);

			Stream* stream;
		};

		// 0x106DC1A0: a stream of that level; mode 0 compresses, 1 decompresses; the heap the compressor comes from
		Stream(int level, int mode, int heap);
		// 0x106DC230
		~Stream();
		// 0x106DBF20 / 0x106DBF40
		static void* operator new(unsigned int size, int heap);
		static void operator delete(void* block);
		// 0x106DC040 / 0x106DC050: the compressors a mode asks for (compressing is not available)
		ICompressor* CreateCompressor(int level, int heap);
		ICompressor* CreateDecompressor(int level, int heap);
		// 0x106DC080: stores the outcome of a step, wakes the waiting thread
		void SetResult(const StepResult* newResult);
		// 0x106DBFE0: runs a step of the compressor on a worker thread; 0x106DC120: on the calling thread
		void Submit(const void* input, unsigned int inputSize, void* output, unsigned int outputSize, bool last);
		void Run(const void* input, unsigned int inputSize, void* output, unsigned int outputSize, bool last);
		// 0x106DBF50 / 0x106DBF60: the level and the mode
		int GetLevel();
		int GetMode();
		// 0x106DBF70 / 0x106DBFA0 / 0x106DBFC0: the status and the used amounts of the last step, read under the lock
		int GetStatus();
		int GetUsedInput();
		int GetUsedOutput();
		// 0x106DBF90: waits for the event the finished step signals
		void Wait();

		AsyncCallback callback;
		int status;
		int usedInput;
		int usedOutput;
		int level;
		int mode;
		ICompressor* compressor;
		unsigned char lock[0x18];
		unsigned char event[8];
	};

	// 0x106DBF00 / 0x106DBF10: registers the worker thread's step with the task system and removes it
	void Startup();
	void Shutdown();
}

#endif
