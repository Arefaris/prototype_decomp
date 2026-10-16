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

	// The vertex declaration a draw needs: its number goes to `declaration` (0x1062B7B0; name guess)
	void Unknown1062B7B0(int format, int* declaration, int* unknown);

	// FUNCTION: ENGINE 0x10620A20
	// EQUIVALENT: scheduling and register allocation (27.3 %): the engine pushes the shader name before the call that
	// hands out the techniques, keeps the vertex declaration's number in the slot of the shader argument and saves
	// ebp around the device call; every call and every value is the same
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
		if (gVertexDeclarationManager->current != declaration)
		{
			gVertexDeclarationManager->current = declaration;
			gD3DDevice->lpVtbl->SetVertexDeclaration(gD3DDevice,
				gVertexDeclarationManager->entries.begin[declaration].declaration);
		}
		shader->Draw(technique, constants, parameters);
		batchDraws += 1.0f;
		batchedPrimitives += (float)count;
		tracker->Unknown1062A8F0(a, b, count);
		return tracker;
	}

	// FUNCTION: ENGINE 0x10620B00
	// EQUIVALENT: scheduling and register allocation, the same as 0x10620A20 (26.1 %)
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
		if (gVertexDeclarationManager->current != declaration)
		{
			gVertexDeclarationManager->current = declaration;
			gD3DDevice->lpVtbl->SetVertexDeclaration(gD3DDevice,
				gVertexDeclarationManager->entries.begin[declaration].declaration);
		}
		shader->Draw(technique, constants, 0);
		batchDraws += 1.0f;
		batchedPrimitives += (float)count;
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
	// EQUIVALENT: scheduling and register allocation (22.0 %): the engine reads the indexed draw's counts in another order
	// and keeps the state in different registers; every call and every value is the same
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
		if (desc->indices != 0 && desc->indices != gCurrentIndices)
		{
			gD3DDevice->lpVtbl->SetIndices(gD3DDevice, desc->indices->buffer);
			gCurrentIndices = desc->indices;
		}
		shader->Draw(technique, constants, parameters);
		gDrawing = false;
		int d3dType = gD3DPrimitiveTypes[desc->primitiveType];
		int indexCount = 0;
		int vertices;
		if (desc->indices == 0)
		{
			vertices = desc->count;
			if (vertices == 0)
			{
				vertices = desc->vertices->GetUnknown14();
			}
		}
		else
		{
			vertices = desc->vertices->GetUnknown14() - desc->baseVertex;
			indexCount = desc->count;
			if (indexCount == 0)
			{
				indexCount = desc->indices->GetUnknown1C();
			}
		}
		shader->GetTechniques()->Get(technique);
		if (desc->indices == 0)
		{
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
			gD3DDevice->lpVtbl->DrawPrimitive(gD3DDevice, d3dType, 0, primitives);
		}
		else
		{
			gD3DDevice->lpVtbl->DrawIndexedPrimitive(gD3DDevice, d3dType, desc->baseVertex, 0, vertices,
				desc->startIndex, PrimitiveCount(desc->primitiveType, 0, indexCount));
		}
		int primitives = PrimitiveCount(desc->primitiveType, vertices, indexCount);
		if (desc->indices == 0)
		{
			drawnPrimitives += (float)(unsigned int)primitives;
			drawnVertices += (float)(unsigned int)vertices;
		}
		else
		{
			drawnIndexedPrimitives += (float)(unsigned int)primitives;
			drawnIndexedVertices += (float)(unsigned int)vertices;
		}
		drawCalls += 1.0f;
	}

	// FUNCTION: ENGINE 0x10623250
	// EQUIVALENT: scheduling and register allocation (32.4 %), the same as 0x1061FB40
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
		if (desc->indices != 0 && desc->indices != gCurrentIndices)
		{
			gD3DDevice->lpVtbl->SetIndices(gD3DDevice, desc->indices->buffer);
			gCurrentIndices = desc->indices;
		}
		shader->Draw(technique, constants, parameters);
		gDrawing = false;
		Unknown106229B0(((const PrimDrawDescGpuSkin*)desc)->unknown4C, ((const PrimDrawDescGpuSkin*)desc)->unknown50);
		int d3dType = gD3DPrimitiveTypes[desc->primitiveType];
		unsigned int vertices = desc->count;
		if (vertices == 0)
		{
			vertices = desc->vertices->GetUnknown14();
		}
		unsigned int indexCount = 0;
		shader->GetTechniques()->Get(technique);
		if (desc->indices != 0)
		{
			indexCount = desc->count;
			if (indexCount == 0)
			{
				indexCount = desc->indices->GetUnknown1C();
			}
		}
		int primitives = PrimitiveCount(desc->primitiveType, vertices, indexCount);
		if (desc->indices == 0)
		{
			gD3DDevice->lpVtbl->DrawPrimitive(gD3DDevice, d3dType, desc->baseVertex, primitives);
		}
		else
		{
			gD3DDevice->lpVtbl->DrawIndexedPrimitive(gD3DDevice, d3dType, desc->baseVertex, 0, vertices,
				desc->startIndex, primitives);
		}
		if (desc->indices == 0)
		{
			drawnPrimitives += (float)(unsigned int)primitives;
			drawnVertices += (float)vertices;
		}
		else
		{
			drawnIndexedPrimitives += (float)(unsigned int)primitives;
			drawnIndexedVertices += (float)vertices;
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
			int vertices = batch->vertices->GetUnknown14();
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
}
