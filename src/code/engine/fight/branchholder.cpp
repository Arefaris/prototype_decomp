// The reference a fight node holds to a branch of the tree (see trackfactory.h; part of the unit 0x105A2440 - 0x105B3680).
#include "code/core/strings.h"
#include "code/engine/fight/reader.h"
#include "code/engine/fight/trackfactory.h"
#include "code/engine/system/streampackage.h"
#include <new>
#include <string.h>

namespace fight
{
	// FUNCTION: ENGINE 0x105A7590
	void BranchHolder::SetPath(const char* text)
	{
		if (path != text)
		{
			delete[] path;
			if (text != 0)
			{
				int length = (int)strlen(text);
				if (length > 0)
				{
					path = new char[length + 1];
					core::StrCpy(path, text);
					return;
				}
			}
			path = 0;
		}
	}

	// FUNCTION: ENGINE 0x105A75F0
	void BranchHolder::SetBase(Branch* newBase)
	{
		base = newBase;
	}

	// FUNCTION: ENGINE 0x105A7600
	BranchHolder::BranchHolder(const char* newKind)
		: target(0), path(0), index(-1), base(0), kind(newKind), context(0), unknown20(0)
	{
	}

	// FUNCTION: ENGINE 0x105A7630
	void BranchHolder::Assign(Branch* unused, Branch* newBranch)
	{
		if (newBranch != target.branch)
		{
			if (target.branch != 0)
			{
				target.branch->Unregister(&target);
			}
			target.branch = newBranch;
			if (newBranch != 0)
			{
				newBranch->Register(&target);
			}
		}
	}

	// FUNCTION: ENGINE 0x105A7660
	bool BranchHolder::SetPathAndClear(const char* text)
	{
		if (path != text)
		{
			SetPath(text);
			Assign(0, 0);
		}
		return true;
	}

	// FUNCTION: ENGINE 0x105A7690
	bool BranchHolder::Load(const Name& key, int context, Reader* reader)
	{
		char text[1024] = { 0 };
		reader->ReadString(key, text, 1024);
		SetPathAndClear(text);
		if (reader->HasValue())
		{
			index = -1;
			reader->ReadInt(key, &index);
		}
		SetBase((Branch*)context);
		return true;
	}

	// FUNCTION: ENGINE 0x105A7720
	BranchHolder::~BranchHolder()
	{
		if (context != 0)
		{
			context->RemoveHolder(this);
		}
		Assign(0, 0);
		delete[] path;
	}

	// FUNCTION: ENGINE 0x105A7760
	BranchHolder& BranchHolder::operator=(const BranchHolder& other)
	{
		SetPathAndClear(other.path);
		Assign(0, other.target.branch);
		index = other.index;
		kind = other.kind;
		if (context != 0)
		{
			context->RemoveHolder(this);
		}
		context = other.context;
		if (context != 0)
		{
			context->AddHolder(this);
		}
		return *this;
	}

	// FUNCTION: ENGINE 0x105A77C0
	bool BranchHolder::IsUnresolved() const
	{
		return target.branch == 0 && (path != 0 || index >= 0);
	}

	// FUNCTION: ENGINE 0x105A77E0
	// EQUIVALENT: register allocation (the engine keeps the path in eax and the kind in edx, ours ecx and eax) and the alignment padding of the loop; 78.2 %
	bool BranchHolder::Resolve(Branch* start)
	{
		if (target.branch != 0)
		{
			return true;
		}
		if (start == 0 && kind == 0)
		{
			return false;
		}
		if (path != 0)
		{
			if (kind == 0)
			{
				Assign(start, start->FindByPath(path));
			}
			else
			{
				if (context == 0)
				{
					if (engine::gLoadListeners == 0)
					{
						return false;
					}
					TrackRegistry* found = engine::gLoadListeners->FindContextByName(kind);
					if (found == 0)
					{
						char buffer[256];
						start->GetPath(buffer, 256, 0);
						return false;
					}
					context = found;
					found->AddHolder(this);
				}
				Assign(start, context->branches->FindInTree(path));
			}
		}
		else if (index >= 0)
		{
			Branch* branch = start->GetFirstOfTree();
			if (branch == 0)
			{
				return false;
			}
			int remaining = index;
			while (remaining > 0)
			{
				branch = branch->GetNextOfTree();
				remaining = remaining - 1;
				if (branch == 0)
				{
					break;
				}
			}
			Assign(start, branch);
		}
		return !IsUnresolved();
	}

	// FUNCTION: ENGINE 0x105A78E0
	bool BranchHolder::Clear(Branch* unused)
	{
		if (target.branch != 0)
		{
			Assign(unused, 0);
		}
		return true;
	}

	// FUNCTION: ENGINE 0x105A7900
	void BranchHolder::Reset()
	{
		Clear(0);
		context = 0;
		unknown20 = 0;
	}

	// FUNCTION: ENGINE 0x105A7920
	BranchHolder::BranchHolder(const BranchHolder& other)
		: target(0), path(0), base(0), kind(0), context(0), unknown20(0)
	{
		index = -1;
		*this = other;
	}

	// FUNCTION: ENGINE 0x105A7960
	Branch* BranchHolder::GetBranch()
	{
		if (target.branch == 0)
		{
			Resolve(base);
		}
		return target.branch;
	}

	// FUNCTION: ENGINE 0x105A7980
	bool BranchHolder::CopyPath(char* buffer, unsigned int size)
	{
		if (target.branch == 0)
		{
			Resolve(base);
			if (target.branch == 0 && path != 0)
			{
				core::StrNCpy(buffer, path, size);
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105A79C0
	bool BranchHolder::CopyPath(int unused, char* buffer, unsigned int size)
	{
		if (target.branch == 0)
		{
			Resolve(base);
			if (target.branch == 0 && path != 0)
			{
				core::StrNCpy(buffer, path, size);
				return true;
			}
		}
		return false;
	}
}
