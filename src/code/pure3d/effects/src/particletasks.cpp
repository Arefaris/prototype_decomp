// The task functions of the particle update (unit around 0x1073B8F0 - 0x1073CC70; the file name is a guess, the unit
// also holds the particle task manager): each walks the chain of batches the manager built for one combination of the
// system's features and runs that combination's kernel on every batch, then reports the chain's result. The names
// are guesses.
#include "code/core/asynctask.h"
#include "code/pure3d/effects/particles.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x1073C1C0
	void RunUpdateKernel00(ParticleKernelBatch* batch, core::AsyncTaskCallback* callback)
	{
		ParticleKernelBatch* first = batch;
		for (; batch != 0; batch = batch->next)
		{
			UpdateKernel00(batch->dt, batch->count, batch->unknown50, batch->buffers[0], batch->buffers[1]);
		}
		callback->SetResult(first->result);
	}

	// FUNCTION: ENGINE 0x1073C210
	void RunUpdateKernel01(ParticleKernelBatch* batch, core::AsyncTaskCallback* callback)
	{
		ParticleKernelBatch* first = batch;
		for (; batch != 0; batch = batch->next)
		{
			UpdateKernel01(batch->dt, batch->count, batch->unknown50, batch->buffers[0], batch->buffers[1],
				batch->buffers[2], batch->buffers[3], batch->buffers[4]);
		}
		callback->SetResult(first->result);
	}

	// FUNCTION: ENGINE 0x1073C270
	void RunUpdateKernel02(ParticleKernelBatch* batch, core::AsyncTaskCallback* callback)
	{
		ParticleKernelBatch* first = batch;
		for (; batch != 0; batch = batch->next)
		{
			UpdateKernel02(batch->dt, batch->count, batch->unknown50, batch->buffers[0], batch->buffers[1]);
		}
		callback->SetResult(first->result);
	}

	// FUNCTION: ENGINE 0x1073C2C0
	void RunUpdateKernel03(ParticleKernelBatch* batch, core::AsyncTaskCallback* callback)
	{
		ParticleKernelBatch* first = batch;
		for (; batch != 0; batch = batch->next)
		{
			UpdateKernel03(batch->dt, batch->count, batch->unknown50, batch->buffers[0], batch->buffers[1],
				batch->buffers[2], batch->buffers[3], batch->buffers[5]);
		}
		callback->SetResult(first->result);
	}

	// FUNCTION: ENGINE 0x1073C320
	void RunUpdateKernel04(ParticleKernelBatch* batch, core::AsyncTaskCallback* callback)
	{
		ParticleKernelBatch* first = batch;
		for (; batch != 0; batch = batch->next)
		{
			UpdateKernel04(batch->dt, batch->count, batch->unknown50, batch->buffers[0], batch->buffers[1],
				batch->buffers[3]);
		}
		callback->SetResult(first->result);
	}

	// FUNCTION: ENGINE 0x1073C370
	void RunUpdateKernel05(ParticleKernelBatch* batch, core::AsyncTaskCallback* callback)
	{
		ParticleKernelBatch* first = batch;
		for (; batch != 0; batch = batch->next)
		{
			UpdateKernel05(batch->dt, batch->count, batch->unknown50, batch->buffers[0], batch->buffers[1],
				batch->buffers[2], batch->buffers[3], batch->buffers[4]);
		}
		callback->SetResult(first->result);
	}

	// FUNCTION: ENGINE 0x1073C3D0
	void RunUpdateKernel06(ParticleKernelBatch* batch, core::AsyncTaskCallback* callback)
	{
		ParticleKernelBatch* first = batch;
		for (; batch != 0; batch = batch->next)
		{
			UpdateKernel06(batch->dt, batch->count, batch->unknown50, batch->buffers[0], batch->buffers[1],
				batch->buffers[2], batch->buffers[3], batch->buffers[4], batch->buffers[5]);
		}
		callback->SetResult(first->result);
	}

	// FUNCTION: ENGINE 0x1073C430
	void RunUpdateFrameBlend(ParticleKernelBatch* batch, core::AsyncTaskCallback* callback)
	{
		ParticleKernelBatch* first = batch;
		for (; batch != 0; batch = batch->next)
		{
			UpdateFrameBlend(batch->dt, batch->count, batch->unknown50, (ParticleFrameBlend*)batch->buffers[0],
				(const float*)batch->buffers[1], batch->buffers[2], (float*)batch->buffers[3],
				(const float*)batch->buffers[4]);
		}
		callback->SetResult(first->result);
	}

	// FUNCTION: ENGINE 0x1073C490
	void RunUpdateKernel08(ParticleKernelBatch* batch, core::AsyncTaskCallback* callback)
	{
		ParticleKernelBatch* first = batch;
		for (; batch != 0; batch = batch->next)
		{
			UpdateKernel08(batch->dt, batch->count, batch->unknown50, batch->buffers[0], batch->buffers[1],
				batch->buffers[2], batch->buffers[3], batch->buffers[4], batch->buffers[5]);
		}
		callback->SetResult(first->result);
	}

	// FUNCTION: ENGINE 0x1073C4F0
	void RunUpdateKernel09(ParticleKernelBatch* batch, core::AsyncTaskCallback* callback)
	{
		ParticleKernelBatch* first = batch;
		for (; batch != 0; batch = batch->next)
		{
			UpdateKernel09(batch->dt, batch->count, batch->unknown50, batch->buffers[0], batch->buffers[1],
				batch->buffers[2], batch->buffers[3], batch->buffers[4], batch->buffers[5]);
		}
		callback->SetResult(first->result);
	}

	// FUNCTION: ENGINE 0x1073C550
	void RunUpdateKernel10(ParticleKernelBatch* batch, core::AsyncTaskCallback* callback)
	{
		ParticleKernelBatch* first = batch;
		for (; batch != 0; batch = batch->next)
		{
			UpdateKernel10(batch->dt, batch->count, batch->unknown50, batch->buffers[0], batch->buffers[1],
				batch->buffers[2], batch->buffers[3], batch->buffers[4], batch->buffers[5]);
		}
		callback->SetResult(first->result);
	}

	// FUNCTION: ENGINE 0x1073C5B0
	void RunUpdateKernel11(ParticleKernelBatch* batch, core::AsyncTaskCallback* callback)
	{
		ParticleKernelBatch* first = batch;
		for (; batch != 0; batch = batch->next)
		{
			UpdateKernel11(batch->dt, batch->count, batch->unknown50, batch->buffers[0], batch->buffers[1],
				batch->buffers[2], batch->buffers[3], batch->buffers[4], batch->buffers[5], batch->buffers[6],
				batch->buffers[7], batch->buffers[8], batch->buffers[9], batch->buffers[10], batch->buffers[11]);
		}
		callback->SetResult(first->result);
	}

	// FUNCTION: ENGINE 0x1073C620
	void RunUpdateKernel12(ParticleKernelBatch* batch, core::AsyncTaskCallback* callback)
	{
		ParticleKernelBatch* first = batch;
		for (; batch != 0; batch = batch->next)
		{
			UpdateKernel12(batch->dt, batch->count, batch->unknown50, batch->buffers[0], batch->buffers[1],
				batch->buffers[2], batch->buffers[3], batch->buffers[4], batch->buffers[5], batch->buffers[6],
				batch->buffers[7], batch->buffers[8], batch->buffers[9], batch->buffers[10], batch->buffers[11],
				batch->buffers[12], batch->buffers[13]);
		}
		callback->SetResult(first->result);
	}

	// FUNCTION: ENGINE 0x1073C6A0
	void RunUpdateKernel13(ParticleKernelBatch* batch, core::AsyncTaskCallback* callback)
	{
		ParticleKernelBatch* first = batch;
		for (; batch != 0; batch = batch->next)
		{
			UpdateKernel13(batch->dt, batch->count, batch->unknown50, batch->buffers[0], batch->buffers[1],
				batch->buffers[2], batch->buffers[3], batch->buffers[4], batch->buffers[5], batch->buffers[6],
				batch->buffers[7], batch->buffers[8], batch->buffers[9], batch->buffers[10], batch->buffers[11],
				batch->buffers[12], batch->buffers[13], batch->buffers[14], batch->buffers[15]);
		}
		callback->SetResult(first->result);
	}

	// FUNCTION: ENGINE 0x1073C720
	void RunUpdateKernel14(ParticleKernelBatch* batch, core::AsyncTaskCallback* callback)
	{
		ParticleKernelBatch* first = batch;
		for (; batch != 0; batch = batch->next)
		{
			UpdateKernel14(batch->dt, batch->count, batch->unknown50, batch->buffers[0], batch->buffers[1],
				batch->buffers[2], batch->buffers[3], batch->buffers[4], batch->buffers[5], batch->buffers[6],
				batch->buffers[7], batch->buffers[8], batch->buffers[9], batch->buffers[10], batch->buffers[11],
				batch->buffers[12], batch->buffers[13], batch->buffers[14], batch->buffers[15], batch->buffers[16]);
		}
		callback->SetResult(first->result);
	}

	// FUNCTION: ENGINE 0x1073C7B0
	void RunUpdateKernel15(ParticleKernelBatch* batch, core::AsyncTaskCallback* callback)
	{
		ParticleKernelBatch* first = batch;
		for (; batch != 0; batch = batch->next)
		{
			UpdateKernel15(batch->dt, batch->count, batch->unknown50, batch->buffers[0], batch->buffers[1],
				batch->buffers[2], batch->buffers[3], batch->buffers[4], batch->buffers[5], batch->buffers[6],
				batch->buffers[7], batch->buffers[8], batch->buffers[9], batch->buffers[10], batch->buffers[11],
				batch->buffers[12], batch->buffers[13], batch->buffers[14], batch->buffers[15], batch->buffers[16]);
		}
		callback->SetResult(first->result);
	}

	// FUNCTION: ENGINE 0x1073C840
	void RunUpdateKernel16(ParticleKernelBatch* batch, core::AsyncTaskCallback* callback)
	{
		ParticleKernelBatch* first = batch;
		for (; batch != 0; batch = batch->next)
		{
			UpdateKernel16(batch->dt, batch->count, batch->unknown50, batch->buffers[0], batch->buffers[1],
				batch->buffers[2], batch->buffers[3], batch->buffers[4], batch->buffers[5], batch->buffers[6],
				batch->buffers[7], batch->buffers[8], batch->buffers[9], batch->buffers[10], batch->buffers[11],
				batch->buffers[12], batch->buffers[13], batch->buffers[14], batch->buffers[15], batch->buffers[16]);
		}
		callback->SetResult(first->result);
	}

	// FUNCTION: ENGINE 0x1073C8D0
	void RunUpdateKernel21(ParticleKernelBatch* batch, core::AsyncTaskCallback* callback)
	{
		ParticleKernelBatch* first = batch;
		for (; batch != 0; batch = batch->next)
		{
			UpdateKernel21(batch->dt, batch->count, batch->unknown50, batch->buffers[0], batch->buffers[1]);
		}
		callback->SetResult(first->result);
	}

	// FUNCTION: ENGINE 0x1073C920
	void RunUpdateKernel22(ParticleKernelBatch* batch, core::AsyncTaskCallback* callback)
	{
		ParticleKernelBatch* first = batch;
		for (; batch != 0; batch = batch->next)
		{
			UpdateKernel22(batch->dt, batch->count, batch->unknown50, batch->buffers[0], batch->buffers[1],
				batch->buffers[2], batch->buffers[3], batch->buffers[4], batch->buffers[5], batch->buffers[6],
				batch->buffers[7], batch->buffers[8]);
		}
		callback->SetResult(first->result);
	}

	// FUNCTION: ENGINE 0x1073C990
	void RunUpdateKernel17(ParticleKernelBatch* batch, core::AsyncTaskCallback* callback)
	{
		ParticleKernelBatch* first = batch;
		for (; batch != 0; batch = batch->next)
		{
			UpdateKernel17(batch->dt, batch->count, batch->unknown50, batch->buffers[0], batch->buffers[1],
				batch->buffers[2], batch->buffers[3], batch->buffers[4]);
		}
		callback->SetResult(first->result);
	}

	// FUNCTION: ENGINE 0x1073C9F0
	void RunUpdateKernel23(ParticleKernelBatch* batch, core::AsyncTaskCallback* callback)
	{
		ParticleKernelBatch* first = batch;
		for (; batch != 0; batch = batch->next)
		{
			UpdateKernel23(batch->dt, batch->count, batch->unknown50, batch->buffers[0], batch->buffers[1],
				batch->buffers[2]);
		}
		callback->SetResult(first->result);
	}

	// FUNCTION: ENGINE 0x1073CA40
	void RunUpdateKernel24(ParticleKernelBatch* batch, core::AsyncTaskCallback* callback)
	{
		ParticleKernelBatch* first = batch;
		for (; batch != 0; batch = batch->next)
		{
			UpdateKernel24(batch->dt, batch->count, batch->unknown50, batch->buffers[0], batch->buffers[1]);
		}
		callback->SetResult(first->result);
	}

	// FUNCTION: ENGINE 0x1073CA90
	void RunUpdateKernel25(ParticleKernelBatch* batch, core::AsyncTaskCallback* callback)
	{
		ParticleKernelBatch* first = batch;
		for (; batch != 0; batch = batch->next)
		{
			UpdateKernel25(batch->dt, batch->count, batch->unknown50, batch->buffers[0], batch->buffers[1]);
		}
		callback->SetResult(first->result);
	}

	// FUNCTION: ENGINE 0x1073CAE0
	void RunUpdateNothing(ParticleKernelBatch* batch, core::AsyncTaskCallback* callback)
	{
		ParticleKernelBatch* first = batch;
		for (; batch != 0; batch = batch->next)
		{
			UpdateNothing(batch->dt, batch->count, batch->unknown50, batch->buffers[0], batch->buffers[1],
				batch->buffers[2], batch->buffers[3]);
		}
		callback->SetResult(first->result);
	}

	// FUNCTION: ENGINE 0x1073CB30
	void RunUpdateKernel26(ParticleKernelBatch* batch, core::AsyncTaskCallback* callback)
	{
		ParticleKernelBatch* first = batch;
		for (; batch != 0; batch = batch->next)
		{
			UpdateKernel26(batch->dt, batch->count, batch->unknown50, batch->buffers[0], batch->buffers[1],
				batch->buffers[2], batch->buffers[3], batch->buffers[4], batch->buffers[5]);
		}
		callback->SetResult(first->result);
	}

	// FUNCTION: ENGINE 0x1073CB90
	void RunUpdateKernel19(ParticleKernelBatch* batch, core::AsyncTaskCallback* callback)
	{
		ParticleKernelBatch* first = batch;
		for (; batch != 0; batch = batch->next)
		{
			UpdateKernel19(batch->dt, batch->count, batch->unknown50, batch->buffers[0], batch->buffers[1],
				batch->buffers[2], batch->buffers[3], batch->buffers[4], batch->buffers[5], batch->buffers[6],
				batch->buffers[7], batch->buffers[8], batch->buffers[9], batch->buffers[10], batch->buffers[11],
				batch->buffers[12], batch->buffers[13], batch->buffers[14], batch->buffers[15]);
		}
		callback->SetResult(first->result);
	}

	// FUNCTION: ENGINE 0x1073CC10
	void RunUpdateKernel20(ParticleKernelBatch* batch, core::AsyncTaskCallback* callback)
	{
		ParticleKernelBatch* first = batch;
		for (; batch != 0; batch = batch->next)
		{
			UpdateKernel20(batch->dt, batch->count, batch->unknown50, batch->buffers[0], batch->buffers[1],
				batch->buffers[2], batch->buffers[3], batch->buffers[4], batch->buffers[5], batch->buffers[6],
				batch->buffers[7]);
		}
		callback->SetResult(first->result);
	}
}
