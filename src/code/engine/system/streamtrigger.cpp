#include "code/engine/system/streamtrigger.h"
#include "code/content/stringmetatype.h"
#include "code/engine/system/enginememory.h"

namespace engine
{
	// GLOBAL: ENGINE 0x1130DE90
	int StreamTrigger::sUnknown;

	// FUNCTION: ENGINE 0x108352B0
	content::ClassInfo* StreamTrigger::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::StreamTrigger";
		sInfo.code = "pnr";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x108352F0
	void StreamTrigger::Slot3(int value)
	{
		sUnknown = value;
	}

	// FUNCTION: ENGINE 0x10835300
	bool StreamTrigger::Slot5()
	{
		RegisterStreamTrigger(this);
		return true;
	}

	// FUNCTION: ENGINE 0x10835310
	const char* StreamTrigger::GetNeighbours()
	{
		if (neighbours == 0)
		{
			return "";
		}
		return neighbours->Data();
	}

	// FUNCTION: ENGINE 0x10835330
	const char* StreamTrigger::GetPackages()
	{
		if (packages == 0)
		{
			return "";
		}
		return packages->Data();
	}

	// FUNCTION: ENGINE 0x10835350
	void StreamTrigger::SetTags(const char* text)
	{
		tags.FromString(text);
	}

	// FUNCTION: ENGINE 0x10835360
	const char* StreamTrigger::GetTags()
	{
		return tags.ToString();
	}

	// FUNCTION: ENGINE 0x10835480
	bool StreamTrigger::Contains(const math::Vector& point, float margin)
	{
		if (hulls.IsEmpty())
		{
			math::Vector high(boundingBox.max.x + margin, boundingBox.max.y + margin, boundingBox.max.z + margin);
			math::Vector low(boundingBox.min.x - margin, boundingBox.min.y - margin, boundingBox.min.z - margin);
			if (point.x >= low.x && high.x >= point.x && point.y >= low.y && high.y >= point.y && point.z >= low.z
				&& high.z >= point.z)
			{
				return true;
			}
			return false;
		}
		for (unsigned int i = hulls.Size(); i != 0;)
		{
			i--;
			if (hulls[i].Contains(point))
			{
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10835550
	StreamPackage* StreamTrigger::FindPackage(const TagSet& tags)
	{
		if (packageList != 0)
		{
			StreamPackage** package = packageList->begin;
			StreamPackage** last = packageList->end;
			for (; package != last; package++)
			{
				StreamPackage* candidate = *package;
				if (tags.Intersects(candidate->tags))
				{
					return candidate;
				}
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10835800
	void StreamTrigger::SetNeighbours(const char* text)
	{
		if (text != 0 && *text != 0)
		{
			Allocator allocator;
			neighbours = new (0xc) String(text, allocator);
		}
	}

	// FUNCTION: ENGINE 0x10835840
	void StreamTrigger::SetNeighbourTriggers(StreamTrigger** list, unsigned int count)
	{
		neighbourTriggers = new (0xc) container::ArrayDynamic<StreamTrigger*, Allocator>(count);
		for (unsigned int i = 0; i < count; i++)
		{
			neighbourTriggers->PushBack(list[i]);
		}
	}

	// FUNCTION: ENGINE 0x108358A0
	void StreamTrigger::SetPackages(const char* text)
	{
		if (text != 0 && *text != 0)
		{
			Allocator allocator;
			packages = new (0xc) String(text, allocator);
		}
	}

	// FUNCTION: ENGINE 0x10835950
	// Adds the trigger the token names to the neighbours of context (a StreamTrigger)
	void AddNeighbour(const char* token, void* context)
	{
		core::Name<core::CaseSensitiveKey> name(token, 1);
		StreamTrigger* trigger = FindStreamTrigger(name);
		if (trigger != 0)
		{
			((StreamTrigger*)context)->neighbourTriggers->PushBack(trigger);
		}
	}

	// FUNCTION: ENGINE 0x108359A0
	// Adds the package the token names to the packages of context (a StreamTrigger)
	void AddPackage(const char* token, void* context)
	{
		core::Name<core::CaseSensitiveKey> name(token, 1);
		StreamPackage* package = FindStreamPackage(name);
		if (package != 0)
		{
			((StreamTrigger*)context)->packageList->PushBack(package);
		}
	}

	// FUNCTION: ENGINE 0x10835CE0
	content::MemberList* StreamTrigger::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetStringMemberMetaType<StreamTrigger, 0>(&StreamTrigger::GetNeighbours,
				&StreamTrigger::SetNeighbours, "pnr"), 0, "neighbours" },
			{ content::GetStringMemberMetaType<StreamTrigger, 1>(&StreamTrigger::GetPackages,
				&StreamTrigger::SetPackages, "pnr"), 0, "packages" },
			{ content::GetArrayDynamicMetaType<StreamTrigger,
				container::ArrayDynamic<StreamTriggerHull, Allocator> >(
				content::GetClassMetaType<StreamTriggerHull>(), "pnr"),
				content::MemberOffset(&((StreamTrigger*)0)->hulls, (int)&((StreamTrigger*)0)->hulls), "hulls" },
			{ content::GetClassMetaType<math::AABB>(),
				content::MemberOffset(&((StreamTrigger*)0)->boundingBox, (int)&((StreamTrigger*)0)->boundingBox),
				"boundingBox" },
			{ content::GetStringMemberMetaType<StreamTrigger, 2>(&StreamTrigger::GetTags, &StreamTrigger::SetTags,
				"pnr"), 0, "tags" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10835E10
	void StreamTrigger::ResolveLinks()
	{
		if (neighbours != 0)
		{
			neighbourTriggers = new (0xc) container::ArrayDynamic<StreamTrigger*, Allocator>(
				neighbours->Count(';') + 1);
			neighbours->ForEachToken(';', AddNeighbour, this);
		}
		if (packages != 0)
		{
			packageList = new (0xc) container::ArrayDynamic<StreamPackage*, Allocator>(packages->Count(';') + 1);
			packages->ForEachToken(';', AddPackage, this);
		}
	}

	// FUNCTION: ENGINE 0x10835F00
	bool StreamTrigger::IsReady()
	{
		UnregisterStreamTrigger(this);
		if (neighbours != 0 && neighbourTriggers != 0)
		{
			delete neighbourTriggers;
			neighbourTriggers = 0;
		}
		if (packages != 0 && packageList != 0)
		{
			delete packageList;
			packageList = 0;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x108363D0
	// EQUIVALENT: the engine computes the name's address after clearing the reference count, ours before
	StreamTrigger::StreamTrigger()
		: neighbours(0), neighbourTriggers(0), packages(0), packageList(0)
	{
		boundingBox.min.x = 1e12f;
		boundingBox.min.y = 1e12f;
		boundingBox.min.z = 1e12f;
		boundingBox.max.x = -1e12f;
		boundingBox.max.y = -1e12f;
		boundingBox.max.z = -1e12f;
	}

	// FUNCTION: ENGINE 0x10836440
	void StreamTrigger::SetName(const content::ObjectName& newName)
	{
		name = newName;
	}

	// FUNCTION: ENGINE 0x10836450
	// EQUIVALENT: the engine computes the name's address after clearing the reference count, ours before
	StreamTrigger::StreamTrigger(const content::ObjectName& newName)
		: name(newName), neighbours(0), neighbourTriggers(0), packages(0), packageList(0)
	{
		boundingBox.min.x = 1e12f;
		boundingBox.min.y = 1e12f;
		boundingBox.min.z = 1e12f;
		boundingBox.max.x = -1e12f;
		boundingBox.max.y = -1e12f;
		boundingBox.max.z = -1e12f;
	}

	// FUNCTION: ENGINE 0x108364D0
	StreamTrigger::~StreamTrigger()
	{
		IsReady();
		delete neighbours;
		delete neighbourTriggers;
		delete packages;
		delete packageList;
	}

	// Kept copies: the explicitly instantiated members of the hull and plane arrays, the hull array's meta type
	// helper, the string member getter / setters and meta type getters, the default constructors of AABB and Vector
	// FUNCTION: ENGINE 0x10835370
	// FUNCTION: ENGINE 0x10835380
	// FUNCTION: ENGINE 0x10835390
	// FUNCTION: ENGINE 0x108353A0
	// FUNCTION: ENGINE 0x108353F0
	// FUNCTION: ENGINE 0x10835440
	// FUNCTION: ENGINE 0x10835450
	// FUNCTION: ENGINE 0x10835460
	// FUNCTION: ENGINE 0x10835470
	// FUNCTION: ENGINE 0x108355A0
	// FUNCTION: ENGINE 0x108355B0
	// FUNCTION: ENGINE 0x108355C0
	// FUNCTION: ENGINE 0x108355D0
	// FUNCTION: ENGINE 0x10835620
	// FUNCTION: ENGINE 0x10835630
	// FUNCTION: ENGINE 0x10835640
	// FUNCTION: ENGINE 0x10835650
	// FUNCTION: ENGINE 0x10835660
	// FUNCTION: ENGINE 0x108356B0
	// FUNCTION: ENGINE 0x108356C0
	// FUNCTION: ENGINE 0x108356D0
	// FUNCTION: ENGINE 0x108356E0
	// FUNCTION: ENGINE 0x108356F0
	// FUNCTION: ENGINE 0x10835700
	// FUNCTION: ENGINE 0x10835720
	// FUNCTION: ENGINE 0x10835730
	// FUNCTION: ENGINE 0x10835750
	// FUNCTION: ENGINE 0x10835760
	// FUNCTION: ENGINE 0x10835770
	// FUNCTION: ENGINE 0x10835780
	// FUNCTION: ENGINE 0x108359F0
	// FUNCTION: ENGINE 0x10835A60
	// FUNCTION: ENGINE 0x10835AD0
	// FUNCTION: ENGINE 0x10835B20
	// FUNCTION: ENGINE 0x10835B90
	// FUNCTION: ENGINE 0x10835BA0
	// FUNCTION: ENGINE 0x10835C10
	// FUNCTION: ENGINE 0x10835EA0
	// FUNCTION: ENGINE 0x10835EC0
	// FUNCTION: ENGINE 0x10835EE0
	// FUNCTION: ENGINE 0x10835F80
	// FUNCTION: ENGINE 0x10835FA0
	// FUNCTION: ENGINE 0x10835FC0
	// FUNCTION: ENGINE 0x10836000
	// FUNCTION: ENGINE 0x10836040
	// FUNCTION: ENGINE 0x10836070
	// FUNCTION: ENGINE 0x10836090
	// FUNCTION: ENGINE 0x108360C0
	// FUNCTION: ENGINE 0x10836100
	// FUNCTION: ENGINE 0x10836130
	// FUNCTION: ENGINE 0x108361C0
	// FUNCTION: ENGINE 0x108361E0
	// FUNCTION: ENGINE 0x10836330
	// FUNCTION: ENGINE 0x10836360
}

namespace container
{
	template class ArrayDynamic<engine::StreamTriggerHull, AllocatorCoreStatic<12, 16> >;
	template class ArrayDynamic<math::Plane, AllocatorCoreStatic<12, 16> >;
}

// the default element the reflection helper's Insert used; kept as the engine kept it
template engine::StreamTriggerHull&
	content::ArrayDynamicHelper<container::ArrayDynamic<engine::StreamTriggerHull, container::AllocatorCoreStatic<12, 16> > >::Default();
