// pure3d::pddiBaseContext, the base of the render device (unit 0x10614640 - 0x10616xxx; file pddi/src/base/
// basecontext.cpp): the state accessors over the four state stacks, the clocks and the frame counter. Names of
// the states' words are guesses.
#include "code/core/debug.h"
#include "code/core/time.h"
#include "code/pure3d/pddi.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10614AB0
	unsigned __int64 pddiBaseContext::GetTimeUnknown600()
	{
		return timeUnknown600.value;
	}

	// FUNCTION: ENGINE 0x10614AC0
	void pddiBaseContext::SetTimeUnknown600(unsigned __int64 time)
	{
		timeUnknown600.value = time;
	}

	// FUNCTION: ENGINE 0x10614AE0
	void pddiBaseContext::ReadTimeUnknown608()
	{
		timeUnknown608.value = core::GetElapsedMicroseconds();
	}

	// FUNCTION: ENGINE 0x10614B00
	void pddiBaseContext::ReadTimeUnknown610()
	{
		timeUnknown610.value = core::GetElapsedMicroseconds();
		timeUnknown620.value = timeUnknown610.value - timeUnknown608.value - GetTimeUnknown600();
	}

	// FUNCTION: ENGINE 0x10614B50
	void pddiBaseContext::SetTimeUnknown618(unsigned __int64 time)
	{
		timeUnknown618.value = time;
	}

	// FUNCTION: ENGINE 0x10614B70
	unsigned __int64 pddiBaseContext::GetTimeUnknown618()
	{
		return timeUnknown618.value;
	}

	// FUNCTION: ENGINE 0x10614B80
	unsigned __int64 pddiBaseContext::GetTimeUnknown620()
	{
		return timeUnknown620.value;
	}

	// FUNCTION: ENGINE 0x10614B90
	// EQUIVALENT: the unsigned frame number is loaded into a register before it is converted, 74.3%
	void pddiBaseContext::Unknown27()
	{
		OLD_ASSERT_AT("..\\..\\..\\code\\pure3d\\pddi\\src\\base\\basecontext.cpp", 0x179, initialized, "mInitialized",
			"pddiBaseContext: Not initialized.  Call Init().");
		frameNumber += 1;
		frameActive = 1;
		clocks[0] = (float)frameNumber;
	}

	// FUNCTION: ENGINE 0x10614C00
	void pddiBaseContext::Unknown28()
	{
		frameActive = 0;
	}

	// FUNCTION: ENGINE 0x10614C10
	void pddiBaseContext::Unknown26()
	{
	}

	// FUNCTION: ENGINE 0x10614C20
	bool pddiBaseContext::IsUnknown14Set()
	{
		return frameActive > 0;
	}

	// FUNCTION: ENGINE 0x10614C30
	void pddiBaseContext::SetViewUnknown4(int value)
	{
		viewState->unknown4 = value;
	}

	// FUNCTION: ENGINE 0x10614C40
	// EQUIVALENT: the output pointer sits in edx, 86.7%
	void pddiBaseContext::GetViewUnknown4(int* value)
	{
		pddiViewStateData* state = viewState;
		int current = state->unknown4;
		*value = current;
	}

	// FUNCTION: ENGINE 0x10614C50
	void pddiBaseContext::SetViewUnknown8(float value)
	{
		viewState->unknown8 = value;
	}

	// FUNCTION: ENGINE 0x10614C70
	float pddiBaseContext::GetViewUnknown8()
	{
		return viewState->unknown8;
	}

	// FUNCTION: ENGINE 0x10614C80
	void pddiBaseContext::SetViewUnknownC(int value)
	{
		viewState->unknownC = value;
	}

	// FUNCTION: ENGINE 0x10614C90
	int pddiBaseContext::GetViewUnknownC()
	{
		return viewState->unknownC;
	}

	// FUNCTION: ENGINE 0x10614CA0
	void pddiBaseContext::SetViewUnknown10(int value)
	{
		viewState->unknown10 = value;
		Unknown67();
	}

	// FUNCTION: ENGINE 0x10614CC0
	int pddiBaseContext::GetViewUnknown10()
	{
		return viewState->unknown10;
	}

	// FUNCTION: ENGINE 0x10614D10
	void pddiBaseContext::GetViewUnknown14(float* a, float* b, float* c, float* d)
	{
		pddiViewStateData* state = viewState;
		*a = state->unknown14[0];
		*b = state->unknown14[1];
		*c = state->unknown14[2];
		*d = state->unknown14[3];
	}

	// FUNCTION: ENGINE 0x10614D40
	void pddiBaseContext::GetViewUnknown24(float* a, float* b, float* c, float* d)
	{
		pddiViewStateData* state = viewState;
		*a = state->unknown24[0];
		*b = state->unknown24[1];
		*c = state->unknown24[2];
		*d = state->unknown24[3];
	}

	// FUNCTION: ENGINE 0x10614D70
	void pddiBaseContext::GetViewUnknown34(float* a, float* b)
	{
		pddiViewStateData* state = viewState;
		*a = state->unknown24[4];
		*b = state->unknown24[5];
	}

	// FUNCTION: ENGINE 0x10614D90
	void pddiBaseContext::SetCullMode(int mode)
	{
		renderState->cullMode = mode;
	}

	// FUNCTION: ENGINE 0x10614DA0
	int pddiBaseContext::GetCullMode()
	{
		return renderState->cullMode;
	}

	// FUNCTION: ENGINE 0x10614DB0
	void pddiBaseContext::SetColourWrite(bool red, bool green, bool blue, bool alpha)
	{
		renderState->colourWrite[0] = red;
		renderState->colourWrite[1] = green;
		renderState->colourWrite[2] = blue;
		renderState->colourWrite[3] = alpha;
	}

	// FUNCTION: ENGINE 0x10614DE0
	void pddiBaseContext::GetColourWrite(bool* red, bool* green, bool* blue, bool* alpha)
	{
		*red = renderState->colourWrite[0];
		*green = renderState->colourWrite[1];
		*blue = renderState->colourWrite[2];
		*alpha = renderState->colourWrite[3];
	}

	// FUNCTION: ENGINE 0x10614E20
	void pddiBaseContext::EnableZBuffer(bool enable)
	{
		zState->zBuffer = enable;
	}

	// FUNCTION: ENGINE 0x10614E30
	bool pddiBaseContext::IsZBufferEnabled()
	{
		return zState->zBuffer;
	}

	// FUNCTION: ENGINE 0x10614E40
	void pddiBaseContext::SetZCompare(int compare)
	{
		zState->zCompare = compare;
	}

	// FUNCTION: ENGINE 0x10614E50
	int pddiBaseContext::GetZCompare()
	{
		return zState->zCompare;
	}

	// FUNCTION: ENGINE 0x10614E60
	void pddiBaseContext::EnableZWrite(bool enable)
	{
		zState->zWrite = enable;
	}

	// FUNCTION: ENGINE 0x10614E70
	bool pddiBaseContext::IsZWriteEnabled()
	{
		return zState->zWrite;
	}

	// FUNCTION: ENGINE 0x10614E80
	void pddiBaseContext::SetZBias(float bias, float slope)
	{
		zState->zBias = bias;
		zState->zSlope = slope;
	}

	// FUNCTION: ENGINE 0x10614EA0
	void pddiBaseContext::GetZBias(float* bias, float* slope)
	{
		pddiZStateData* state = zState;
		*bias = state->zBias;
		*slope = state->zSlope;
	}

	// FUNCTION: ENGINE 0x10614EC0
	void pddiBaseContext::EnableStencilBuffer(bool enable)
	{
		stencilState->enabled = enable;
	}

	// FUNCTION: ENGINE 0x10614ED0
	bool pddiBaseContext::IsStencilBufferEnabled()
	{
		return stencilState->enabled;
	}

	// FUNCTION: ENGINE 0x10614EE0
	void pddiBaseContext::SetStencilCompare(int compare)
	{
		stencilState->compare = compare;
	}

	// FUNCTION: ENGINE 0x10614EF0
	int pddiBaseContext::GetStencilCompare()
	{
		return stencilState->compare;
	}

	// FUNCTION: ENGINE 0x10614F00
	void pddiBaseContext::SetStencilRef(int ref)
	{
		stencilState->ref = ref;
	}

	// FUNCTION: ENGINE 0x10614F10
	int pddiBaseContext::GetStencilRef()
	{
		return stencilState->ref;
	}

	// FUNCTION: ENGINE 0x10614F20
	void pddiBaseContext::SetStencilMask(int mask)
	{
		stencilState->mask = mask;
	}

	// FUNCTION: ENGINE 0x10614F30
	int pddiBaseContext::GetStencilMask()
	{
		return stencilState->mask;
	}

	// FUNCTION: ENGINE 0x10614F40
	void pddiBaseContext::SetStencilWriteMask(int mask)
	{
		stencilState->writeMask = mask;
	}

	// FUNCTION: ENGINE 0x10614F50
	int pddiBaseContext::GetStencilWriteMask()
	{
		return stencilState->writeMask;
	}

	// FUNCTION: ENGINE 0x10614F60
	void pddiBaseContext::SetStencilOp(int fail, int zFail, int zPass)
	{
		stencilState->fail = fail;
		stencilState->zFail = zFail;
		stencilState->zPass = zPass;
	}

	// FUNCTION: ENGINE 0x10614F90
	void pddiBaseContext::GetStencilOp(int* fail, int* zFail, int* zPass)
	{
		*fail = stencilState->fail;
		*zFail = stencilState->zFail;
		*zPass = stencilState->zPass;
	}

	// FUNCTION: ENGINE 0x10614FC0
	void pddiBaseContext::Unknown51(bool enable)
	{
		stencilState->unknown24 = enable;
	}

	// FUNCTION: ENGINE 0x10614FD0
	void pddiBaseContext::Unknown52(int compare)
	{
		stencilState->unknown28 = compare;
	}

	// FUNCTION: ENGINE 0x10614FE0
	void pddiBaseContext::Unknown53(int fail, int zFail, int zPass)
	{
		stencilState->unknown2C = fail;
		stencilState->unknown30 = zFail;
		stencilState->unknown34 = zPass;
	}

	// FUNCTION: ENGINE 0x10615010
	void pddiBaseContext::SetRenderUnknown38(bool value)
	{
		renderState->unknown38 = value;
	}

	// FUNCTION: ENGINE 0x10615020
	void pddiBaseContext::SetFillMode(int mode)
	{
		renderState->fillMode = mode;
	}

	// FUNCTION: ENGINE 0x10615030
	int pddiBaseContext::GetFillMode()
	{
		return renderState->fillMode;
	}

	// FUNCTION: ENGINE 0x10615040
	void pddiBaseContext::SetRenderUnknownC(int value)
	{
		renderState->unknownC = value;
	}

	// FUNCTION: ENGINE 0x10615050
	int pddiBaseContext::GetRenderUnknownC()
	{
		return renderState->unknownC;
	}

	// FUNCTION: ENGINE 0x10615060
	void pddiBaseContext::EnableAlphaTest(bool enable)
	{
		renderState->alphaTest = enable;
	}

	// FUNCTION: ENGINE 0x10615070
	bool pddiBaseContext::IsAlphaTestEnabled()
	{
		return renderState->alphaTest;
	}

	// FUNCTION: ENGINE 0x10615080
	void pddiBaseContext::SetBlendMode(int source, int destination, int sourceAlpha, int destinationAlpha)
	{
		renderState->blend[0] = source;
		renderState->blend[1] = destination;
		renderState->blend[2] = sourceAlpha;
		renderState->blend[3] = destinationAlpha;
	}

	// FUNCTION: ENGINE 0x106150F0
	void pddiBaseContext::EnableFog(bool enable)
	{
		renderState->fog = enable;
	}

	// FUNCTION: ENGINE 0x10615100
	bool pddiBaseContext::IsFogEnabled()
	{
		return renderState->fog;
	}

	// FUNCTION: ENGINE 0x10615110
	void pddiBaseContext::SetFogRange(float nearZ, float farZ)
	{
		renderState->fogNear = nearZ;
		renderState->fogFar = farZ;
	}

	// FUNCTION: ENGINE 0x10615130
	void pddiBaseContext::GetFogRange(float* nearZ, float* farZ)
	{
		pddiRenderStateData* state = renderState;
		*nearZ = state->fogNear;
		*farZ = state->fogFar;
	}

	// FUNCTION: ENGINE 0x10615150
	void pddiBaseContext::SetAlphaRef(float ref)
	{
		renderState->alphaRef = ref;
	}

	// FUNCTION: ENGINE 0x10615170
	float pddiBaseContext::GetAlphaRef()
	{
		return renderState->alphaRef;
	}

	// FUNCTION: ENGINE 0x10615180
	int pddiBaseContext::GetFrameCount(int index)
	{
		return (int)clocks[index];
	}

	// FUNCTION: ENGINE 0x10615190
	float pddiBaseContext::GetFrameTimeUnknown(int index)
	{
		return clocks[index];
	}

	// FUNCTION: ENGINE 0x10615DA0
	void pddiBaseContext::Unknown8(int a)
	{
	}

	// FUNCTION: ENGINE 0x10615DB0
	void pddiBaseContext::Unknown9()
	{
	}

	// FUNCTION: ENGINE 0x10615DC0
	IDirect3DQuery9* pddiBaseContext::Unknown10()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10615DD0
	void pddiBaseContext::Unknown11(IDirect3DQuery9* query)
	{
	}

	// FUNCTION: ENGINE 0x10615DE0
	bool pddiBaseContext::Unknown12(IDirect3DQuery9* query)
	{
		return false;
	}

	// FUNCTION: ENGINE 0x10615DF0
	IDirect3DQuery9* pddiBaseContext::Unknown18()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10615E00
	void pddiBaseContext::Unknown19(IDirect3DQuery9* query)
	{
	}

	// FUNCTION: ENGINE 0x10615E10
	void pddiBaseContext::Unknown20(IDirect3DQuery9* query)
	{
	}

	// FUNCTION: ENGINE 0x10615E20
	void pddiBaseContext::Unknown21(IDirect3DQuery9* query)
	{
	}

	// FUNCTION: ENGINE 0x10615E30
	void pddiBaseContext::Unknown54(int a)
	{
	}

	// FUNCTION: ENGINE 0x10615E40
	void pddiBaseContext::Unknown55(int a)
	{
	}

	// FUNCTION: ENGINE 0x10615E50
	void pddiBaseContext::Unknown56(int a, int b)
	{
	}

	// FUNCTION: ENGINE 0x10615E60
	void pddiBaseContext::Unknown57(int a)
	{
	}
}
