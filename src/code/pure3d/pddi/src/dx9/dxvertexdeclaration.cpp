// The Direct3D 9 vertex declaration of the pddi layer (unit around 0x10625A00 - 0x1062B800; the name comes from the
// assert path of 0x1062B170 and 0x1062B710). Only the constructor and the manager's statistics dump are
// reconstructed; the declaration's own dump (0x1062B170) is not.
#include "code/pure3d/pddi/vertexdeclaration.h"

#include "code/core/report.h"

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

	// 0x1062B170: dumps one entry of the manager's table (not reconstructed)
	void DumpVertexDeclaration(int index);

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
