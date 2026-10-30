// pure3d::Pass and the render passes built on it (directory from the tree's pure3d/pass/src, file name guessed).
// The destructor, Run and RunChildren are reconstructed here; the rest of the unit is declared in
// code/pure3d/pass.h.
#include "code/pure3d/pass.h"
#include "code/pure3d/context.h"
#include "code/pure3d/lighting.h"
#include "code/pure3d/pass/rendertargetmanager.h"
#include "code/pure3d/pddi.h"
#include "code/pure3d/primstream.h"
#include "code/pure3d/scene.h"

namespace pure3d
{
	// The lighting inputs and the part list the passes share (0x11282AB0 / 0x11282AB4; names guessed)
	LightingInputs* gPassLightingInputs;
	PartList* gPassParts;

	// FUNCTION: ENGINE 0x10754540
	bool Pass::IsBegun()
	{
		return begun;
	}

	// FUNCTION: ENGINE 0x10754550
	void Pass::SetEntriesWord(unsigned int value)
	{
		entries.unknown0 = value;
	}

	// FUNCTION: ENGINE 0x10754560
	ContextRenderSettings::ContextRenderSettings()
	{
		unknown0 = 0;
		unknown4 = -1;
	}

	// FUNCTION: ENGINE 0x10754590
	void Pass::Visit(void* context)
	{
		VisitChildren(context);
	}

	// FUNCTION: ENGINE 0x107545A0
	void Pass::BeginView(View* view, CameraData* camera)
	{
		view->SetCamera(camera);
		view->clearFlags = 0;
		view->Apply();
	}

	// FUNCTION: ENGINE 0x107545D0
	void Pass::EndView(View* view)
	{
		view->End();
	}

	// FUNCTION: ENGINE 0x107545E0
	int Pass::IsActive(bool withParents)
	{
		if (withParents && parent != 0)
		{
			if (enabled)
			{
				if ((char)parent->IsActive(true))
				{
					return 1;
				}
			}
			return 0;
		}
		return enabled;
	}

	// FUNCTION: ENGINE 0x10754620
	Pass* Pass::GetNextSibling()
	{
		return nextSibling;
	}

	// FUNCTION: ENGINE 0x10754630
	const Pass* Pass::GetNextSibling() const
	{
		return nextSibling;
	}

	// FUNCTION: ENGINE 0x10754640
	Pass* Pass::GetFirstChild()
	{
		return firstChild;
	}

	// FUNCTION: ENGINE 0x10754650
	const Pass* Pass::GetFirstChild() const
	{
		return firstChild;
	}

	// FUNCTION: ENGINE 0x10754660
	Pass* Pass::GetParent()
	{
		return parent;
	}

	// FUNCTION: ENGINE 0x10754670
	const Pass* Pass::GetParent() const
	{
		return parent;
	}

	// FUNCTION: ENGINE 0x10754690
	void Pass::VisitChildren(void* context)
	{
		for (Pass* child = firstChild; child != 0; child = child->nextSibling)
		{
			child->Visit(context);
		}
	}

	// FUNCTION: ENGINE 0x107546C0
	void Pass::AddChild(Pass* child, Pass* before)
	{
		child->nextSibling = 0;
		child->parent = this;
		Pass* node = firstChild;
		if (node == 0)
		{
			firstChild = child;
			return;
		}
		if (before == 0)
		{
			while (node->nextSibling != 0)
			{
				node = node->nextSibling;
			}
			node->nextSibling = child;
			return;
		}
		Pass* previous = 0;
		while (node != before)
		{
			if (node == 0)
			{
				return;
			}
			previous = node;
			node = node->nextSibling;
		}
		if (node != 0)
		{
			child->nextSibling = node;
			if (previous != 0)
			{
				previous->nextSibling = child;
			}
		}
	}

	// FUNCTION: ENGINE 0x10754730
	bool Pass::CallIsVisible()
	{
		return IsVisible();
	}

	// FUNCTION: ENGINE 0x10754740
	bool Pass::IsVisible()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x10754750
	bool Pass::GetUnknown24Bit1()
	{
		return unknown24Bit1;
	}

	// FUNCTION: ENGINE 0x10754760
	void Pass::SetEnabled(bool value)
	{
		IsVisible();
		enabled = value;
	}

	// FUNCTION: ENGINE 0x107547B0
	PartList* Pass::GetParts(Scene* scene)
	{
		scene->SelectParts(gPassParts, &entries);
		return gPassParts;
	}

	// FUNCTION: ENGINE 0x10754810
	LightingInputs* Pass::GetLightingInputs()
	{
		return gPassLightingInputs;
	}

	// FUNCTION: ENGINE 0x10754820
	void Pass::BeginOnce()
	{
		RenderTargetManager::sSingleton->Unknown1073B450();
		Begin();
		begun = 1;
	}

	// FUNCTION: ENGINE 0x10754840
	void Pass::EndOnce()
	{
		End();
		begun = 0;
	}

	// FUNCTION: ENGINE 0x10754AC0
	// NONMATCHING: the engine clears eax (the slot returns an int), a bool clears only al (66.7 %)
#ifdef NONMATCHING
	bool Pass::IsEnabled()
	{
		return false;
	}
#endif

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

	// FUNCTION: ENGINE 0x10754B90
	void Pass::Begin()
	{
		for (Pass* child = firstChild; child != 0; child = child->nextSibling)
		{
			child->BeginOnce();
		}
	}

	// FUNCTION: ENGINE 0x10754BB0
	void Pass::End()
	{
		for (Pass* child = firstChild; child != 0; child = child->nextSibling)
		{
			child->EndOnce();
		}
	}
}
