// pure3d::Pass and the render passes built on it (directory from the tree's pure3d/pass/src, file name guessed).
// The destructor, Run and RunChildren are reconstructed here; the rest of the unit is declared in
// code/pure3d/pass.h.
#include "code/pure3d/pass.h"
#include "code/pure3d/pddi.h"
#include "code/pure3d/primstream.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10754AE0
	Pass::~Pass()
	{
	}

	// FUNCTION: ENGINE 0x10754AF0
	void Pass::Run(PassContext* context)
	{
		if (!(flags24 & 1))
		{
			BeginOnce();
		}
		if (flags20 & 1)
		{
			RenderStateBackup backup(pddi, stateGroups, 1);
			backup.Save();
			Render(context);
			backup.Restore();
		}
	}

	// FUNCTION: ENGINE 0x10754B60
	void Pass::RunChildren(PassContext* context)
	{
		for (Pass* child = firstChild; child != 0; child = child->nextSibling)
		{
			child->Run(context);
		}
	}
}
