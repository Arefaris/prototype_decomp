// pure3d::pddiBaseShaderProgram and pure3d::dxProgram (RTTI names): a vertex or a pixel shader program of the
// Direct3D 9 back end, and the cache of the programs the device has set. Member names are guesses.
#ifndef PURE3D_PDDI_DX9_DXPROGRAM_H
#define PURE3D_PDDI_DX9_DXPROGRAM_H

#include "code/pure3d/pddi/dx9/d3d9.h"

namespace pure3d
{
	// One register binding of a program (12 bytes; the meanings are unknown)
	struct dxProgramBinding
	{
		unsigned int name;
		unsigned int flags;
		int kind;
	};

	// The program interface (RTTI name, two slots)
	class pddiBaseShaderProgram
	{
	public:
		// 0x10625860: 1 is a vertex program, 0 a pixel program
		pddiBaseShaderProgram(int newKind);
		// 0x10625890 (the destructor), 0x106258B0 (the deleting form)
		virtual ~pddiBaseShaderProgram();
		// 0x10625880: the name of the kind of program ("unknown" for the base)
		virtual const char* GetKindName();

		// 1 for a vertex program, 0 for a pixel program
		int kind;
		// The register bindings the program was loaded with (a new[] block)
		dxProgramBinding* bindings;
		int unknownC;
	};

	// The text a program's name is kept in (8 bytes, made by 0x1061AFA0; names are guesses)
	class dxProgramName
	{
	public:
		// 0x1061AFA0: room for at least that many characters
		dxProgramName(unsigned int capacity);
		// 0x1061AFD0
		~dxProgramName();
		// 0x1061B000
		void Assign(const char* text);

		char* text;
		unsigned int capacity;
	};

	// A vertex or pixel shader program of a technique (RTTI name, base pddiBaseShaderProgram, two slots)
	class dxProgram : public pddiBaseShaderProgram
	{
	public:
		// 0x10627CC0: the program of that name (loaded from the shader files when asked to)
		dxProgram(const char* name, int newKind, bool load);
		// 0x10626BC0: lets go of the Direct3D shaders; 0x10626DE0 is the deleting form
		virtual ~dxProgram();
		// 0x10627480: reads the program's code and its register bindings
		bool Load(const char* name);
		// 0x10626C10: makes the Direct3D shader out of the program's code (once)
		int Create(const void* function);
		// 0x10626C60
		int GetUnknown14();

		int unknown10;
		int unknown14;
		// Set once the Direct3D shader exists
		bool created;
		dxProgramName name;
		// 0x24 / 0x28: the Direct3D shader of a pixel program and of a vertex program
		IDirect3DShader9* pixelShader;
		IDirect3DShader9* vertexShader;
	};

	// What the context remembers of the programs it has set (the object at 0x11276DEC; name guess)
	struct dxProgramCache
	{
		// 0x10626A20
		dxProgramCache();
		// 0x10626A40: takes the programs off the device
		~dxProgramCache();

		dxProgram* vertex;
		dxProgram* pixel;
		dxProgram* saved;
		int unknownC;
		bool frozen;
		bool restricted;
		unsigned char unknown12[2];
		int vertexSets;
		int pixelSets;
		// 0x1C: the zfillnotex vertex program once it has been loaded
		dxProgram* zFill;
	};

	// 0x11276DEC
	extern dxProgramCache* gProgramCache;

	// 0x10626B60 / 0x10626B90: make a Direct3D vertex and pixel shader out of the compiled code (names are guesses)
	IDirect3DShader9* CreateVertexShader(const void* function);
	IDirect3DShader9* CreatePixelShader(const void* function);
	// The accessors of the cache (names are guesses): 0x10626A00 / 0x10626A10 the program loaded last, 0x10626A90
	// whether programs are only set when the cache is not frozen, 0x10626AA0 whether it is frozen, 0x10626AC0 /
	// 0x10626AE0 / 0x10626AF0 the counts of the programs set, 0x10626B00 takes every program off the device,
	// 0x10627000 deletes the cache
	dxProgram* GetZFillProgram();
	void SetZFillProgram(dxProgram* program);
	void SetProgramsRestricted(bool restricted);
	bool AreProgramsFrozen();
	void ResetProgramCounts();
	int GetVertexProgramSets();
	int GetPixelProgramSets();
	void ClearPrograms();
	void DestroyProgramCache();
}

#endif
