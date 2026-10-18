// The Direct3D 9 vertex declaration of the pddi layer (unit around 0x10625A00 - 0x1062B800; the name comes from the
// assert path of 0x1062B170 and 0x1062B710). Only the constructor and the statistics dumps are reconstructed.
#include "code/pure3d/pddi/vertexdeclaration.h"

#include <string.h>

#include "code/core/report.h"
#include "code/core/strings.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10625AC0
	dxVertexDeclaration::dxVertexDeclaration() : unknown0(0), unknown4(0)
	{
		unknown108 = 0;
		unknown10C = 0;
		unknown110 = 0;
	}

	// The two report-once flags of DumpStats (0x110BC41E, 0x110BC41D; names are guesses)
	static bool sDumpHeaderEnabled = true;
	static bool sDumpCountEnabled = true;

	// FUNCTION: ENGINE 0x1062B5C0
	// EQUIVALENT: scheduling: the engine stores the new entry's user count before its element count, this compiler
	// the other way round (96.6 %)
	// Every store order, references, a constructor or an inline Set for the entry leave the order as it is.
	int FindVertexDeclaration(const D3DVERTEXELEMENT9* elements)
	{
		unsigned int count = 0;
		do
		{
			count++;
		} while (elements[count - 1].Type != 0x11);
		D3DVERTEXELEMENT9 known[0x100];
		unsigned int knownCount = 0x100;
		for (dxVertexDeclarationEntry* entry = gVertexDeclarationManager->entries.begin;
			entry != gVertexDeclarationManager->entries.end; entry++)
		{
			knownCount = 0x100;
			if (entry->elementCount == count)
			{
				entry->declaration->lpVtbl->GetDeclaration(entry->declaration, known, &knownCount);
				if (knownCount == count)
				{
					bool same = true;
					for (unsigned int i = 0; i < knownCount; i++)
					{
						if (known[i].Stream != elements[i].Stream || known[i].Type != elements[i].Type ||
							known[i].Usage != elements[i].Usage)
						{
							same = false;
							break;
						}
					}
					if (same)
					{
						entry->users++;
						return entry->id;
					}
				}
			}
		}
		dxVertexDeclarationEntry made;
		made.users = 1;
		made.elementCount = count;
		made.id = gVertexDeclarationManager->count;
		gD3DDevice->lpVtbl->CreateVertexDeclaration(gD3DDevice, elements, &made.declaration);
		gVertexDeclarationManager->entries.PushBack(made);
		gVertexDeclarationManager->count++;
		return made.id;
	}

	// The name of a declaration type (D3DDECLTYPE_FLOAT1 ... D3DDECLTYPE_UNUSED)
	const char* GetDeclarationTypeName(int type);

	// One line of the dump: the usage, its index, the stream and the type of an element
	#define DUMP_ELEMENT(format) 		core::SNPrintf(line, 0x100, format, elements[i].UsageIndex, elements[i].Stream, GetDeclarationTypeName(elements[i].Type))

	// FUNCTION: ENGINE 0x1062B170
	void DumpVertexDeclaration(int index)
	{
		unsigned int count;
		char line[0x100];
		D3DVERTEXELEMENT9 elements[0x100];
		char usage[0x400];
		memset(usage, 0, 0x400);
		count = 0x100;
		memset(elements, 0, 0x800);
		IDirect3DVertexDeclaration9* declaration = gVertexDeclarationManager->entries.begin[index].declaration;
		declaration->lpVtbl->GetDeclaration(declaration, elements, &count);
		for (unsigned int i = 0; i < count; i++)
		{
			memset(line, 0, 0x100);
			if (elements[i].Type == 0x11)
			{
				break;
			}
			switch (elements[i].Usage)
			{
			case 0:
				DUMP_ELEMENT(" Position %d Stream(%d) Type(%s) |");
				break;
			case 1:
				DUMP_ELEMENT(" BlendWeights %d Stream(%d) Type(%s) |");
				break;
			case 2:
				DUMP_ELEMENT(" BlendIndices %d Stream(%d) Type(%s) |");
			case 3:
				DUMP_ELEMENT(" Normal %d Stream(%d) Type(%s) |");
				break;
			case 4:
				DUMP_ELEMENT(" PSize %d Stream(%d) Type(%s) |");
				break;
			case 5:
				DUMP_ELEMENT(" TexCoord %d Stream(%d) Type(%s) |");
				break;
			case 6:
				DUMP_ELEMENT(" Tangent %d Stream(%d) Type(%s) |");
				break;
			case 7:
				DUMP_ELEMENT(" BiNormal %d Stream(%d) Type(%s) |");
				break;
			case 8:
				DUMP_ELEMENT(" TessFactor %d Stream(%d) Type(%s) |");
				break;
			case 10:
				DUMP_ELEMENT(" Colour %d Stream(%d) Type(%s) |");
				break;
			case 11:
				DUMP_ELEMENT(" Fog %d Stream(%d) Type(%s) |");
				break;
			case 12:
				DUMP_ELEMENT(" Depth %d Stream(%d) Type(%s) |");
				break;
			case 13:
				DUMP_ELEMENT(" Sample %d Stream(%d) Type(%s) |");
				break;
			}
			core::StrCat(usage, line);
		}
		static bool sUsageEnabled = true;
		if (sUsageEnabled)
		{
			if (core::Report(0, 0, "..\\..\\..\\code\\pure3d\\pddi\\src\\dx9\\dxvertexdeclaration.cpp", 0x173, 0,
					"Usage %s\n", usage, 0) == 3)
			{
				sUsageEnabled = false;
			}
		}
	}

	// FUNCTION: ENGINE 0x1062B710
	void DumpVertexDeclarations()
	{
		if (sDumpHeaderEnabled)
		{
			if (core::Report(0, 0, "..\\..\\..\\code\\pure3d\\pddi\\src\\dx9\\dxvertexdeclaration.cpp", 0x112, 0,
					"**** dxVertexDeclarationManager::DumpStats() ****\n", 0) == 3)
			{
				sDumpHeaderEnabled = false;
			}
		}
		if (sDumpCountEnabled)
		{
			if (core::Report(0, 0, "..\\..\\..\\code\\pure3d\\pddi\\src\\dx9\\dxvertexdeclaration.cpp", 0x113, 0,
					"%d Declarations\n", gVertexDeclarationManager->count, 0) == 3)
			{
				sDumpCountEnabled = false;
			}
		}
		for (int i = 0; i < gVertexDeclarationManager->count; i++)
		{
			DumpVertexDeclaration(i);
		}
	}
}
