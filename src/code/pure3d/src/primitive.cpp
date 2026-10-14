// The primitive unit of pure3d (0x106F2D00 - 0x106F4400; file name guessed): primitive states, the render state
// backup and pure3d::PrimStream. Names are guesses.
#include "code/pure3d/pddi.h"
#include "code/pure3d/primstream.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x106F31D0
	void RenderStateBackup::Restore()
	{
		if (groups & 1)
		{
			context->SetCullMode(cullMode);
			context->SetFillMode(fillMode);
			context->SetColourWrite(colourWrite[0], colourWrite[1], colourWrite[2], colourWrite[3]);
			context->EnableAlphaTest(alphaTest);
			context->SetBlendMode(blend[0], blend[1], blend[2], blend[3]);
			context->EnableFog(fog);
			context->SetFogRange(fogNear, fogFar);
			context->SetAlphaRef(alphaRef);
		}
		if (groups & 2)
		{
			context->SetViewUnknown4(view4);
			context->SetViewUnknown8(view8);
			context->SetViewUnknownC(viewC);
			context->SetViewUnknown10(view10);
			context->SetViewUnknown14(view14[0], view14[1], view14[2], view14[3]);
			context->SetViewUnknown24(view24[0], view24[1], view24[2], view24[3], view24[4], view24[5]);
		}
		if (groups & 4)
		{
			context->EnableZBuffer(zBuffer);
			context->SetZCompare(zCompare);
			context->EnableZWrite(zWrite);
			context->SetZBias(zBias, zSlope);
		}
		if (groups & 8)
		{
			context->EnableStencilBuffer(stencil);
			context->SetStencilCompare(stencilCompare);
			context->SetStencilMask(stencilMask);
			context->SetStencilWriteMask(stencilWriteMask);
			context->SetStencilOp(stencilFail, stencilZFail, stencilZPass);
		}
	}

	// FUNCTION: ENGINE 0x106F3630
	void PrimStream::End()
	{
		buffer->buffer->Unlock();
		if (written)
		{
			PrimBuffer* buffers = buffer->buffer;
			PrimDrawDesc desc(buffer->owner->format, 0, 1, &buffers, 0, count, type, 1);
			pddi->DrawPrimitive(&name, &desc, &parameters);
		}
		buffer->owner->Release();
		buffer->owner = 0;
		buffer = 0;
		written = false;
	}

	// FUNCTION: ENGINE 0x106F4100
	bool PrimStream::Begin(Shader* shader, int type, int format, int count,
		const core::Name<core::CaseInsensitiveKey32>& name, const PrimStreamParameters* parameters)
	{
		bool opened = Open(shader, type, format, count);
		if (opened)
		{
			this->name = name;
			if (parameters)
			{
				this->parameters = *parameters;
			}
		}
		return opened;
	}
}
