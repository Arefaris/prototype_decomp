// The vertex and pixel shader programs of the Direct3D 9 back end and the cache of the programs the device has set
// (unit around 0x10625860 - 0x10627CC0; the file name is guessed, no assert path survives).
#include <new>

#include "code/pure3d/pddi/dx9/dxprogram.h"

namespace pure3d
{
	// The kind of program the base class names itself after (a pointer the engine keeps to the string "unknown")
	extern const char* gProgramKindName;

	// FUNCTION: ENGINE 0x10625860
	pddiBaseShaderProgram::pddiBaseShaderProgram(int newKind) : kind(newKind), bindings(0), unknownC(0)
	{
	}

	// FUNCTION: ENGINE 0x10625890
	pddiBaseShaderProgram::~pddiBaseShaderProgram()
	{
		if (bindings != 0)
		{
			delete[] bindings;
		}
	}

	// FUNCTION: ENGINE 0x106258B0 is the compiler's scalar deleting destructor of the base class (slot 0)

	// FUNCTION: ENGINE 0x10625880
	const char* pddiBaseShaderProgram::GetKindName()
	{
		return gProgramKindName;
	}

	// FUNCTION: ENGINE 0x10626B60
	IDirect3DShader9* CreateVertexShader(const void* function)
	{
		IDirect3DShader9* shader = 0;
		gD3DDevice->lpVtbl->CreateVertexShader(gD3DDevice, function, (void**)&shader);
		return shader;
	}

	// FUNCTION: ENGINE 0x10626B90
	IDirect3DShader9* CreatePixelShader(const void* function)
	{
		IDirect3DShader9* shader = 0;
		gD3DDevice->lpVtbl->CreatePixelShader(gD3DDevice, function, (void**)&shader);
		return shader;
	}

	// FUNCTION: ENGINE 0x10626A20
	dxProgramCache::dxProgramCache()
	{
		vertex = 0;
		pixel = 0;
		saved = 0;
		zFill = 0;
		frozen = false;
		restricted = true;
		vertexSets = 0;
		pixelSets = 0;
	}

	// FUNCTION: ENGINE 0x10626A40
	dxProgramCache::~dxProgramCache()
	{
		gD3DDevice->lpVtbl->SetVertexShader(gD3DDevice, 0);
		gD3DDevice->lpVtbl->SetPixelShader(gD3DDevice, 0);
		vertex = 0;
		pixel = 0;
		saved = 0;
		frozen = false;
		restricted = true;
	}

	// FUNCTION: ENGINE 0x10626DA0 is the compiler's scalar deleting destructor of the cache

	// FUNCTION: ENGINE 0x10626A00
	dxProgram* GetZFillProgram()
	{
		return gProgramCache->zFill;
	}

	// FUNCTION: ENGINE 0x10626A10
	void SetZFillProgram(dxProgram* program)
	{
		gProgramCache->zFill = program;
	}

	// FUNCTION: ENGINE 0x10626A90
	void SetProgramsRestricted(bool restricted)
	{
		gProgramCache->restricted = restricted;
	}

	// FUNCTION: ENGINE 0x10626AA0
	bool AreProgramsFrozen()
	{
		return gProgramCache->frozen;
	}

	// FUNCTION: ENGINE 0x10626AC0
	void ResetProgramCounts()
	{
		gProgramCache->pixelSets = 0;
		gProgramCache->vertexSets = 0;
	}

	// FUNCTION: ENGINE 0x10626AE0
	int GetVertexProgramSets()
	{
		return gProgramCache->vertexSets;
	}

	// FUNCTION: ENGINE 0x10626AF0
	int GetPixelProgramSets()
	{
		return gProgramCache->pixelSets;
	}

	// FUNCTION: ENGINE 0x10626B00
	void ClearPrograms()
	{
		gD3DDevice->lpVtbl->SetVertexShader(gD3DDevice, 0);
		gD3DDevice->lpVtbl->SetPixelShader(gD3DDevice, 0);
		gProgramCache->frozen = false;
		gProgramCache->saved = 0;
		gProgramCache->pixel = 0;
		gProgramCache->vertex = 0;
	}

	// FUNCTION: ENGINE 0x10627000
	void DestroyProgramCache()
	{
		dxProgramCache* cache = gProgramCache;
		if (gProgramCache != 0)
		{
			delete cache;
			gProgramCache = 0;
		}
	}

	// FUNCTION: ENGINE 0x10627CC0
	dxProgram::dxProgram(const char* programName, int newKind, bool load) : pddiBaseShaderProgram(newKind),
		unknown14(0), created(false), name(0x100), pixelShader(0), vertexShader(0)
	{
		name.Assign(programName);
		if (load)
		{
			Load(programName);
		}
	}

	// FUNCTION: ENGINE 0x10626BC0
	dxProgram::~dxProgram()
	{
		if (this == gProgramCache->zFill)
		{
			gProgramCache->zFill = 0;
		}
		if (pixelShader != 0)
		{
			pixelShader->Release();
		}
		if (vertexShader != 0)
		{
			vertexShader->Release();
		}
	}

	// FUNCTION: ENGINE 0x10626DE0 is the compiler's scalar deleting destructor of this class (slot 0)

	// FUNCTION: ENGINE 0x10626C10
	int dxProgram::Create(const void* function)
	{
		if (!created)
		{
			if (kind == 0)
			{
				pixelShader = CreatePixelShader(function);
				created = true;
				return 1;
			}
			vertexShader = CreateVertexShader(function);
		}
		created = true;
		return 1;
	}

	// FUNCTION: ENGINE 0x10626C60
	int dxProgram::GetUnknown14()
	{
		return unknown14;
	}
}
