// pure3d::dxContext, the Direct3D 9 device of the pddi layer: only the buffer and texture factories the neighbouring
// dx9 units call (unit around 0x1061B550; the file name is guessed, no assert path survives).
#include "code/pure3d/pddi/dx9/dxcontext.h"
#include "code/pure3d/pddi/vertexdeclaration.h"
#include "code/pure3d/shaderconstants.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x1061B530
	int dxContext::GetUnknown8()
	{
		return unknown8;
	}

	// FUNCTION: ENGINE 0x1061B540
	IDirect3DDevice9* dxContext::GetUnknownC()
	{
		return unknownC;
	}

	// FUNCTION: ENGINE 0x1061B550
	dxTexture* dxContext::NewTexture(const TextureDescription* description)
	{
		dxTexture* texture = new dxTexture(unknownC);
		if (!texture->Create(description))
		{
			delete texture;
			return 0;
		}
		return texture;
	}

	// FUNCTION: ENGINE 0x1061B5A0
	dxTexture* dxContext::NewTexture(const TextureDescription* description, const dxTexture* image)
	{
		dxTexture* texture = new dxTexture(unknownC);
		if (!texture->Create(description, image))
		{
			delete texture;
			return 0;
		}
		return texture;
	}

	// FUNCTION: ENGINE 0x1061B600
	dxVertexBuffer* dxContext::NewVertexBuffer(const VertexBufferDescription* description)
	{
		dxVertexBuffer* buffer = new dxVertexBuffer();
		buffer->Create(description);
		return buffer;
	}

	// FUNCTION: ENGINE 0x1061B660
	dxIndexBuffer* dxContext::NewIndexBuffer(const IndexBufferDescription* description)
	{
		dxIndexBuffer* buffer = new dxIndexBuffer();
		buffer->Create(description);
		return buffer;
	}

	// FUNCTION: ENGINE 0x1061BBC0
	dxContext* Unknown1061BBC0()
	{
		Unknown10627FB0();
		if (gDevice == 0)
		{
			gDevice = new dxDevice(Direct3DCreate9(D3D_SDK_VERSION));
		}
		// The callers keep the driver object as a dxContext (see dxDevice)
		return (dxContext*)gDevice;
	}

	// The vertex declaration a draw needs: its number goes to `declaration` (0x1062B7B0; name guess)
	void Unknown1062B7B0(int format, int* declaration, int* unknown);

	// FUNCTION: ENGINE 0x10620270 is SelectVertexDeclaration (vertexdeclaration.h), which the compiler keeps a copy of

	// FUNCTION: ENGINE 0x10620A20
	dxDrawTracker* dxContext::Unknown10620A20(dxShader* shader, int a, int b, int count,
		const core::Name<core::CaseInsensitiveKey32>* name, const void* parameters)
	{
		if (shader == 0)
		{
			shader = defaultShader;
		}
		int technique = shader->GetTechniques()->Find(name);
		int declaration;
		int unknown;
		Unknown1062B7B0(b, &declaration, &unknown);
		SelectVertexDeclaration(declaration);
		shader->Draw(technique, constants, parameters);
		batchDraws += 1.0f;
		// Added through a reference: the store then stays ahead of the load of the tracker
		float& primitives = batchedPrimitives;
		primitives += (float)count;
		tracker->Unknown1062A8F0(a, b, count);
		return tracker;
	}

	// FUNCTION: ENGINE 0x10620B00
	dxDrawTracker* dxContext::Unknown10620B00(dxShader* shader, int a, int b, int count, int unused)
	{
		if (shader == 0)
		{
			shader = defaultShader;
		}
		int technique = shader->GetTechniques()->Find(&gShaderLit);
		int declaration;
		int unknown;
		Unknown1062B7B0(b, &declaration, &unknown);
		SelectVertexDeclaration(declaration);
		shader->Draw(technique, constants, 0);
		batchDraws += 1.0f;
		// Added through a reference: the store then stays ahead of the load of the tracker
		float& primitives = batchedPrimitives;
		primitives += (float)count;
		tracker->Unknown1062A8F0(a, b, count);
		return tracker;
	}

	// FUNCTION: ENGINE 0x1061F150
	int PrimitiveCount(int type, int vertices, int indices)
	{
		int count = indices != 0 ? indices : vertices;
		switch (type)
		{
		case 0:
			return count / 3;
		case 1:
			return count - 2;
		case 2:
			return count / 2;
		case 3:
			return count - 1;
		case 4:
			return count;
		}
		return -1;
	}

	// FUNCTION: ENGINE 0x1061FB40
	void dxContext::DrawPrimitive(const core::Name<core::CaseInsensitiveKey32>* shaderName, const void* descPointer,
		const void* parameters)
	{
		const PrimDrawDesc* desc = (const PrimDrawDesc*)descPointer;
		if (desc->world != 0)
		{
			SetWorldMatrix(desc->world);
		}
		dxShader* shader = (dxShader*)desc->format;
		if (shader == 0)
		{
			shader = defaultShader;
		}
		int technique = shader->GetTechniques()->Find(shaderName);
		if (technique == -1)
		{
			shader = defaultShader;
			technique = shader->GetTechniques()->Find(&gShaderFallback);
			parameters = 0;
		}
		gDrawing = true;
		Unknown10626030(desc);
		dxIndexBuffer* indices = desc->indices;
		if (indices != 0 && indices != gCurrentIndices)
		{
			gD3DDevice->lpVtbl->SetIndices(gD3DDevice, indices->buffer);
			gCurrentIndices = indices;
		}
		shader->Draw(technique, constants, parameters);
		gDrawing = false;
		int d3dType = gD3DPrimitiveTypes[desc->primitiveType];
		int indexCount = 0;
		int vertices;
		if (desc->indices != 0)
		{
			vertices = desc->streams[0]->GetUnknown14() - desc->baseVertex;
			if (desc->count != 0)
			{
				indexCount = desc->count;
			}
			else
			{
				indexCount = desc->indices->GetUnknown1C();
			}
		}
		else
		{
			vertices = desc->count;
			if (vertices == 0)
			{
				vertices = desc->streams[0]->GetUnknown14();
			}
		}
		dxTechniques* techniques = shader->GetTechniques();
		techniques->Get(technique);
		if (desc->indices != 0)
		{
			IDirect3DDevice9* device = gD3DDevice;
			device->lpVtbl->DrawIndexedPrimitive(device, d3dType, desc->baseVertex, 0, vertices,
				desc->startIndex, PrimitiveCount(desc->primitiveType, 0, indexCount));
		}
		else
		{
			IDirect3DDevice9* device = gD3DDevice;
			int primitives;
			switch (desc->primitiveType)
			{
			case 0:
				primitives = vertices / 3;
				break;
			case 1:
				primitives = vertices - 2;
				break;
			case 2:
				primitives = vertices / 2;
				break;
			case 3:
				primitives = vertices - 1;
				break;
			case 4:
				primitives = vertices;
				break;
			default:
				primitives = -1;
			}
			device->lpVtbl->DrawPrimitive(device, d3dType, 0, primitives);
		}
		int primitives = PrimitiveCount(desc->primitiveType, vertices, indexCount);
		if (desc->indices != 0)
		{
			drawnIndexedPrimitives += (float)(unsigned int)primitives;
			drawnIndexedVertices += (float)(unsigned int)vertices;
		}
		else
		{
			drawnPrimitives += (float)(unsigned int)primitives;
			drawnVertices += (float)(unsigned int)vertices;
		}
		drawCalls += 1.0f;
	}

	// FUNCTION: ENGINE 0x10623250
	// EQUIVALENT: register allocation (28.7 %, 89.4 % when the shifted lines are aligned): the source is shaped like
	// DrawPrimitive's (0x1061FB40), but the engine keeps the technique in ebp and the index buffer in a stack slot,
	// this compiler the other way round; every call and every value is the same.
	// A local for the shader's technique table, a conditional for the vertex count and the device taken inside each
	// draw branch together give the technique ebp (64.5 %), but then the engine's order of the first two calls
	// (the name pushed before the table is asked for) and the device's table loaded once before the branch are lost;
	// that variant is not used.
	// The vertex count kept in a second variable, the technique table taken inline and the index buffer read into a
	// local for the index count compile as before; so do the index buffer's test as nested ifs or without a local
	// (the parameters take ebp then), the technique declared first or unsigned, and a barrier after any statement
	// (the engine's size with one inside a draw branch, 51 %). The orders of the statements between the Draw and the
	// primitive count that keep the engine's call order compile as before.
	void dxContext::Unknown2(const core::Name<core::CaseInsensitiveKey32>* shaderName, const void* descPointer,
		const void* parameters)
	{
		const PrimDrawDesc* desc = (const PrimDrawDesc*)descPointer;
		dxShader* shader = (dxShader*)desc->format;
		if (shader == 0)
		{
			shader = defaultShader;
		}
		int technique = shader->GetTechniques()->Find(shaderName);
		if (technique == -1)
		{
			shader = defaultShader;
			technique = shader->GetTechniques()->Find(&gShaderFallback);
			parameters = 0;
		}
		gDrawing = true;
		Unknown10626030(desc);
		dxIndexBuffer* indices = desc->indices;
		if (indices != 0 && indices != gCurrentIndices)
		{
			gD3DDevice->lpVtbl->SetIndices(gD3DDevice, indices->buffer);
			gCurrentIndices = indices;
		}
		shader->Draw(technique, constants, parameters);
		gDrawing = false;
		Unknown106229B0(((const PrimDrawDescGpuSkin*)desc)->unknown4C, ((const PrimDrawDescGpuSkin*)desc)->unknown50);
		int d3dType = gD3DPrimitiveTypes[desc->primitiveType];
		unsigned int vertices = desc->count;
		if (vertices == 0)
		{
			vertices = desc->streams[0]->GetUnknown14();
		}
		unsigned int indexCount = 0;
		dxTechniques* techniques = shader->GetTechniques();
		techniques->Get(technique);
		if (desc->indices != 0)
		{
			indexCount = desc->count;
			if (indexCount == 0)
			{
				indexCount = desc->indices->GetUnknown1C();
			}
		}
		int primitives = PrimitiveCount(desc->primitiveType, vertices, indexCount);
		IDirect3DDevice9* device = gD3DDevice;
		if (desc->indices != 0)
		{
			device->lpVtbl->DrawIndexedPrimitive(device, d3dType, desc->baseVertex, 0, vertices, desc->startIndex,
				primitives);
		}
		else
		{
			device->lpVtbl->DrawPrimitive(device, d3dType, desc->baseVertex, primitives);
		}
		if (desc->indices != 0)
		{
			drawnIndexedPrimitives += (float)primitives;
			drawnIndexedVertices += (float)vertices;
		}
		else
		{
			drawnPrimitives += (float)primitives;
			drawnVertices += (float)vertices;
		}
		drawCalls += 1.0f;
	}

	// Sets a program on the device unless the context has it set already (the cache counts what it sets)
	__forceinline void SetProgram(dxProgram* program)
	{
		dxProgramCache* cache = gProgramCache;
		if (program->kind == 0)
		{
			if (!cache->restricted)
			{
				if (cache->pixel != 0)
				{
					cache->pixel = 0;
					gD3DDevice->lpVtbl->SetPixelShader(gD3DDevice, 0);
					gProgramCache->pixelSets++;
				}
			}
			else if (!cache->frozen)
			{
				if (cache->pixel != program)
				{
					cache->pixel = program;
					gProgramCache->pixelSets++;
					gD3DDevice->lpVtbl->SetPixelShader(gD3DDevice, program->pixelShader);
				}
			}
			else
			{
				cache->saved = program;
				gProgramCache->pixel = 0;
			}
		}
		else if (cache->vertex != program)
		{
			cache->vertex = program;
			gProgramCache->vertexSets++;
			gD3DDevice->lpVtbl->SetVertexShader(gD3DDevice, program->vertexShader);
		}
	}

	// FUNCTION: ENGINE 0x10621060
	void dxContext::DrawBatches(const void* const* batches, int count)
	{
		if (count == 0)
		{
			return;
		}
		static dxProgram* vertexProgram = defaultShader->GetTechniques()->Unknown106283E0();
		static dxProgram* pixelProgram = defaultShader->GetTechniques()->Unknown10628400();
		SetProgram(vertexProgram);
		SetProgram(pixelProgram);
		Unknown10625A80();
		Unknown106268F0();
		for (unsigned int i = 0; i < (unsigned int)count; i++)
		{
			const dxDrawBatch* batch = (const dxDrawBatch*)batches[i];
			Unknown10626180(batch);
			gD3DDevice->lpVtbl->SetIndices(gD3DDevice, batch->indices->buffer);
			math::Matrix transform = batch->world;
			transform.Multiply(transform, *GetUnknown10614840());
			transform.Multiply(transform, *GetUnknown10614870());
			gD3DDevice->lpVtbl->SetVertexShaderConstantF(gD3DDevice, 0, &transform.m[0][0], 4);
			int d3dType = gD3DPrimitiveTypes[batch->primitiveType];
			int vertices = batch->streams[0]->GetUnknown14();
			int indexCount = batch->indexCount != 0 ? batch->indexCount : batch->indices->GetUnknown1C();
			int primitives;
			switch (batch->primitiveType)
			{
			case 0:
				primitives = indexCount / 3;
				break;
			case 1:
				primitives = indexCount - 2;
				break;
			case 2:
				primitives = indexCount / 2;
				break;
			case 3:
				primitives = indexCount - 1;
				break;
			case 4:
				primitives = indexCount;
				break;
			default:
				primitives = -1;
			}
			gD3DDevice->lpVtbl->DrawIndexedPrimitive(gD3DDevice, d3dType, 0, 0, vertices, batch->startIndex,
				primitives);
		}
		gD3DDevice->lpVtbl->SetIndices(gD3DDevice, 0);
		for (unsigned int stream = 0; stream < 8; stream++)
		{
			gD3DDevice->lpVtbl->SetStreamSource(gD3DDevice, stream, 0, 0, 0);
		}
		Unknown10625A80();
		Unknown106268F0();
	}

	// Passes a render state on to the device when it differs from the one the device is in
	__forceinline void SetRenderStateOn(IDirect3DDevice9* device, dxRenderStateCache* cache, int state, int value)
	{
		if (value != cache->renderStates[state])
		{
			cache->renderStates[state] = value;
			device->lpVtbl->SetRenderState(device, state, value);
		}
	}
#define SetRenderState(state, value) SetRenderStateOn(gD3DDevice, gRenderStateCache, state, value)

	// FUNCTION: ENGINE 0x10620BE0
	void dxContext::SetPerspective(float nearZ, float farZ, float fov, float aspect)
	{
		math::Matrix projection;
		projection.PerspectiveFovLH(fov * 57.295776f, aspect, nearZ, farZ);
		SetProjectionMatrix(&projection);
	}

	// FUNCTION: ENGINE 0x10620C30
	void dxContext::SetOrthographic(float left, float right, float bottom, float top, float nearZ, float farZ)
	{
		math::Matrix projection;
		projection.OrthoOffCenterLH(left, right, bottom, top, nearZ, farZ);
		SetProjectionMatrix(&projection);
	}

	// FUNCTION: ENGINE 0x10620110
	pddiQuery* dxContext::Unknown24(int flags)
	{
		switch (flags)
		{
		case 0x102:
			return queryUnknown660;
		case 0x400001:
			return queryUnknown65C;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10620140
	bool dxContext::Unknown25(int flags)
	{
		bool result = flags == 0x400001;
		return result;
	}

	// FUNCTION: ENGINE 0x10621440
	void dxContext::SetCullMode(int mode)
	{
		pddiBaseContext::SetCullMode(mode);
		if (mode == 0)
		{
			SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		}
		else
		{
			SetRenderState(D3DRS_CULLMODE, mode == 1 ? D3DCULL_CCW : D3DCULL_CW);
		}
	}

	// FUNCTION: ENGINE 0x10621520
	void dxContext::EnableZBuffer(bool enable)
	{
		pddiBaseContext::EnableZBuffer(enable);
		SetRenderState(D3DRS_ZENABLE, enable);
	}

	// FUNCTION: ENGINE 0x10621560
	void dxContext::SetZCompare(int compare)
	{
		pddiBaseContext::SetZCompare(compare);
		SetRenderState(D3DRS_ZFUNC, gD3DZCompares[compare]);
	}

	// FUNCTION: ENGINE 0x106215A0
	void dxContext::EnableZWrite(bool enable)
	{
		pddiBaseContext::EnableZWrite(enable);
		SetRenderState(D3DRS_ZWRITEENABLE, enable);
	}

	// FUNCTION: ENGINE 0x106215E0
	void dxContext::EnableStencilBuffer(bool enable)
	{
		pddiBaseContext::EnableStencilBuffer(enable);
		SetRenderState(D3DRS_STENCILENABLE, enable ? 1 : 0);
	}

	// FUNCTION: ENGINE 0x10621620
	void dxContext::SetStencilCompare(int compare)
	{
		pddiBaseContext::SetStencilCompare(compare);
		SetRenderState(D3DRS_STENCILFUNC, gD3DStencilCompares[compare]);
	}

	// FUNCTION: ENGINE 0x10621660
	void dxContext::SetStencilRef(int ref)
	{
		pddiBaseContext::SetStencilRef(ref);
		SetRenderState(D3DRS_STENCILREF, ref);
	}

	// FUNCTION: ENGINE 0x106216A0
	void dxContext::SetStencilMask(int mask)
	{
		pddiBaseContext::SetStencilMask(mask);
		SetRenderState(D3DRS_STENCILMASK, mask);
	}

	// FUNCTION: ENGINE 0x106216E0
	void dxContext::SetStencilWriteMask(int mask)
	{
		pddiBaseContext::SetStencilWriteMask(mask);
		SetRenderState(D3DRS_STENCILWRITEMASK, mask);
	}

	// FUNCTION: ENGINE 0x10621720
	void dxContext::SetStencilOp(int fail, int zFail, int zPass)
	{
		pddiBaseContext::SetStencilOp(fail, zFail, zPass);
		SetRenderState(D3DRS_STENCILFAIL, gD3DStencilOps[fail]);
		SetRenderState(D3DRS_STENCILZFAIL, gD3DStencilOps[zFail]);
		SetRenderState(D3DRS_STENCILPASS, gD3DStencilOps[zPass]);
	}

	// FUNCTION: ENGINE 0x106217E0
	void dxContext::Unknown51(bool enable)
	{
		pddiBaseContext::Unknown51(enable);
		SetRenderState(D3DRS_TWOSIDEDSTENCILMODE, enable ? 1 : 0);
	}

	// FUNCTION: ENGINE 0x10621830
	void dxContext::Unknown52(int compare)
	{
		pddiBaseContext::Unknown52(compare);
		SetRenderState(D3DRS_CCW_STENCILFUNC, gD3DStencilCompares[compare]);
	}

	// FUNCTION: ENGINE 0x10621880
	void dxContext::Unknown53(int fail, int zFail, int zPass)
	{
		pddiBaseContext::Unknown53(fail, zFail, zPass);
		SetRenderState(D3DRS_CCW_STENCILFAIL, gD3DStencilOps[fail]);
		SetRenderState(D3DRS_CCW_STENCILZFAIL, gD3DStencilOps[zFail]);
		SetRenderState(D3DRS_CCW_STENCILPASS, gD3DStencilOps[zPass]);
	}

	// FUNCTION: ENGINE 0x10621B50
	void dxContext::SetFillMode(int mode)
	{
		pddiBaseContext::SetFillMode(mode);
		SetRenderState(D3DRS_FILLMODE, gD3DFillModes[mode]);
	}

	// FUNCTION: ENGINE 0x106219C0
	void dxContext::EnableAlphaTest(bool enable)
	{
		pddiBaseContext::EnableAlphaTest(enable);
		SetRenderState(D3DRS_SCISSORTESTENABLE, enable);
	}

	// FUNCTION: ENGINE 0x10621940
	void dxContext::SetColourWrite(bool red, bool green, bool blue, bool alpha)
	{
		pddiBaseContext::SetColourWrite(red, green, blue, alpha);
		unsigned int mask = 0;
		if (red)
		{
			mask = 1;
		}
		if (green)
		{
			mask |= 2;
		}
		if (blue)
		{
			mask |= 4;
		}
		if (alpha)
		{
			mask |= 8;
		}
		colourWriteMask = mask;
		SetRenderState(D3DRS_COLORWRITEENABLE, mask);
	}

	// FUNCTION: ENGINE 0x10621A00
	void dxContext::SetFogRange(float nearZ, float farZ)
	{
		depthBiasSlope = nearZ;
		depthBias = farZ;
		SetRenderState(D3DRS_SLOPESCALEDEPTHBIAS, *(int*)&nearZ);
		SetRenderState(D3DRS_DEPTHBIAS, *(int*)&farZ);
	}

	// FUNCTION: ENGINE 0x10621A80
	// NONMATCHING: the engine loads the device before either branch and uses that load for the first state of both, this
	// compiler loads it after the first comparison (best 68.0 %); the code is the same
#ifdef NONMATCHING
	void dxContext::EnableFog(bool enable)
	{
		if (!enable)
		{
			SetRenderState(D3DRS_SLOPESCALEDEPTHBIAS, 0);
			SetRenderState(D3DRS_DEPTHBIAS, 0);
		}
		else
		{
			SetRenderStateOn(gD3DDevice, gRenderStateCache, D3DRS_SLOPESCALEDEPTHBIAS, gDepthBiasSlopeOn);
			SetRenderState(D3DRS_DEPTHBIAS, gDepthBiasOn);
		}
	}
#endif
}
