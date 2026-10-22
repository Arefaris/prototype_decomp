// engine::StreamDriverBehaviour: see the header. The file name is a guess.
#include "code/engine/system/streamdriverbehaviour.h"

#include "code/content/stringmetatype.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/system/enginememory.h"
#include "code/engine/system/streampackage.h"
#include "code/engine/system/streamtrigger.h"
#include <algorithm>

namespace engine
{
	// 0x11283510 (the name of the transform attribute) and 0x1130D3A0 (what the stream driver tells its object: a tag;
	// both are another unit's)
	extern core::Name<core::CaseSensitiveKey> gTransformName;
	class MessageListeners;
	extern MessageListeners gStreamListeners;

	// Sorts a range with a predicate (0x10899750; not inline, so the callers jump to it)
	template<class Iterator, class Predicate> void SortRange(Iterator first, Iterator last, Predicate predicate)
	{
		std::sort(first, last, predicate);
	}

	// FUNCTION: ENGINE 0x10898420
	content::ClassInfo* StreamDriverBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::StreamDriverBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10898480
	void StreamDriverBehaviour::SetTriggerTags(const char* text)
	{
		tags.FromString(text);
	}

	// FUNCTION: ENGINE 0x10898490
	const char* StreamDriverBehaviour::GetTriggerTags()
	{
		return tags.ToString();
	}

#define ENGINE_OFFSET(type, member) 	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10898AB0
	content::MemberList* StreamDriverBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Behaviour>();
		static content::BaseClassCasterImpl<Behaviour, StreamDriverBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<StreamDriverBehaviour, unsigned int, 0>("pn"),
				ENGINE_OFFSET(StreamDriverBehaviour, maxPackagesPerTransition), "maxPackagesPerTransition" },
			{ content::GetMemberPrimitiveMetaType<StreamDriverBehaviour, unsigned int, 1>("pn"),
				ENGINE_OFFSET(StreamDriverBehaviour, maxFilteredTriggers), "maxFilteredTriggers" },
			{ content::GetStringMemberMetaType<StreamDriverBehaviour, 0>(&StreamDriverBehaviour::GetTriggerTags,
				&StreamDriverBehaviour::SetTriggerTags, "pn"),
				0, "triggerTags" },
			{ content::GetMemberPrimitiveMetaType<StreamDriverBehaviour, bool, 2>("p"),
				ENGINE_OFFSET(StreamDriverBehaviour, restricted), "lockWhenStreaming" }
		};
		sList.members = sMembers;
		sList.count = 4;
		return &sList;
	}

	// FUNCTION: ENGINE 0x108984A0
	void StreamDriverBehaviour::SetRestricted(bool value)
	{
		restricted = value;
	}

	// FUNCTION: ENGINE 0x10899030
	void StreamDriverBehaviour::RefreshTriggers()
	{
		triggers->end = triggers->begin;
		CollectTriggers(triggers, tags);
		if (last != 0)
		{
			const math::Matrix& m = owner->transform->value;
			math::Vector position;
			position.Set(m.m[3][0], m.m[3][1], m.m[3][2]);
			StreamTrigger* found = 0;
			for (unsigned int i = triggers->end - triggers->begin; i != 0;)
			{
				i--;
				StreamTrigger* trigger = triggers->begin[i];
				if (trigger->Contains(position, 0.0f))
				{
					found = trigger;
					break;
				}
			}
			if (found != 0)
			{
				AddTriggerPackages(wanted, found, tags, 0, 1);
			}
			else
			{
				wanted->end = wanted->begin;
			}
			Unknown1082D1F0(&wanted, &current);
			last = found;
		}
	}

	// FUNCTION: ENGINE 0x10899110
	void StreamDriverBehaviour::SetWantedPackages(StreamPackage** packages, int count)
	{
		last = 0;
		wanted->end = wanted->begin;
		for (int i = 0; i < count; i++)
		{
			wanted->PushBack(packages[i]);
		}
		Unknown1082D1F0(&wanted, &current);
	}

	// FUNCTION: ENGINE 0x10898FB0
	void StreamDriverBehaviour::OnActiveChanged(bool active)
	{
		Behaviour::OnActiveChanged(active);
		if (!active)
		{
			wanted->end = wanted->begin;
			Unknown1082D1F0(&wanted, &current);
			current->end = current->begin;
			if (unknown50)
			{
				unknown51 = true;
			}
			last = 0;
			if (transitioning)
			{
				transitioning = false;
				Unknown1082BF40();
			}
		}
	}

	// FUNCTION: ENGINE 0x108991C0
	StreamDriverBehaviour::StreamDriverBehaviour(GameObject* newOwner) : Behaviour(newOwner)
	{
		current = 0;
		wanted = 0;
		triggers = 0;
		last = 0;
		maxPackagesPerTransition = 0x20;
		maxFilteredTriggers = 0x400;
		unknown4C = false;
		unknown4D = false;
		restricted = false;
		transitioning = false;
		unknown50 = false;
		unknown51 = false;
		Listen(0x18, true);
		Listen(0x17, true);
		Listen2(4, true);
		this->owner->SetAttributeAndGet<math::Matrix>(gTransformName, math::Matrix::IDENTITY, false);
	}

	// FUNCTION: ENGINE 0x10899560
	StreamDriverBehaviour::~StreamDriverBehaviour()
	{
		delete current;
		delete wanted;
		delete triggers;
		if (transitioning)
		{
			transitioning = false;
			Unknown1082BF40();
		}
	}

	// FUNCTION: ENGINE 0x108992B0
	void StreamDriverBehaviour::Slot1()
	{
		current = new (0xc) StreamPackageArray(maxPackagesPerTransition);
		wanted = new (0xc) StreamPackageArray(maxPackagesPerTransition);
		triggers = new (0xc) StreamTriggerArray(maxFilteredTriggers);
		CollectTriggers(triggers, tags);
		tagsCopy = tags;
		GameObjectHandle handle = GetHandle(owner);
		handle.RouterRemove(gStreamListeners);
	}

	// FUNCTION: ENGINE 0x10898460
	// Orders the packages by the distance Unknown10899770 stores
	int ComparePackageDistances(StreamPackage* a, StreamPackage* b)
	{
		return a->unknown58 < b->unknown58;
	}

	// FUNCTION: ENGINE 0x10899770
	// EQUIVALENT: the engine keeps the x difference in xmm1 and the y difference in xmm2, ours the other way round
	// (register allocation only), 95.2 %
	void StreamDriverBehaviour::Unknown10899770(StreamPackageArray* packages, const math::Vector* position,
		StreamPackage* package)
	{
		for (unsigned int i = 0; i < (unsigned int)(packages->end - packages->begin); i++)
		{
			StreamPackage* item = packages->begin[i];
			float distance;
			if (item == package)
			{
				distance = -1.0f;
			}
			else if (item->instance != 0 && item->instance->unknown98)
			{
				distance = 0.0f;
			}
			else
			{
				float dy = item->unknown4C.y - position->y;
				float dx = item->unknown4C.x - position->x;
				float dz = item->unknown4C.z - position->z;
				distance = dz * dz + dx * dx + dy * dy;
			}
			item->unknown58 = distance;
		}
		SortRange(packages->begin, packages->end, ComparePackageDistances);
	}

	// FUNCTION: ENGINE 0x10899830
	void StreamDriverBehaviour::Update(float dt, unsigned short mask)
	{
		if (unknown4D)
		{
			if (transitioning)
			{
				transitioning = false;
				Unknown1082BF40();
			}
			return;
		}
		const math::Matrix& m = owner->transform->value;
		math::Vector position;
		position.Set(m.m[3][0], m.m[3][1], m.m[3][2]);
		StreamTrigger* found = 0;
		if (last != 0)
		{
			if (last->Contains(position, 0.0f))
			{
				unknown4C = false;
				found = last;
			}
			else
			{
				StreamTriggerArray* neighbours = last->neighbourTriggers;
				if (neighbours != 0)
				{
					for (unsigned int i = neighbours->end - neighbours->begin; i != 0;)
					{
						i--;
						StreamTrigger* trigger = neighbours->begin[i];
						if (trigger->Contains(position, 0.0f))
						{
							found = trigger;
							break;
						}
					}
				}
			}
		}
		if (found == 0)
		{
			for (unsigned int i = triggers->end - triggers->begin; i != 0;)
			{
				i--;
				StreamTrigger* trigger = triggers->begin[i];
				if (trigger->Contains(position, 0.0f))
				{
					found = trigger;
					break;
				}
			}
		}
		if (found != 0)
		{
			AddTriggerPackages(wanted, found, tags, 0, 1);
		}
		else
		{
			wanted->end = wanted->begin;
		}
		StreamPackage* package = 0;
		if (found != 0)
		{
			package = found->FindPackage(tags);
			if (unknown50)
			{
				if (!package->IsLoaded() && !unknown51)
				{
					Unknown104B1860(true);
					unknown51 = true;
				}
				else if (package->IsLoaded() && unknown51)
				{
					Unknown104B1860(false);
					unknown51 = false;
				}
			}
		}
		Unknown10899770(current, &position, package);
		Unknown10899770(wanted, &position, package);
		UpdateStreamTransition(&wanted, &current, &transitioning, restricted);
		last = found;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108984C0
// FUNCTION: ENGINE 0x108984D0
// FUNCTION: ENGINE 0x108984F0
// FUNCTION: ENGINE 0x10898500
// FUNCTION: ENGINE 0x10898510
// FUNCTION: ENGINE 0x10898530
// FUNCTION: ENGINE 0x10898540
// FUNCTION: ENGINE 0x108985A0
// FUNCTION: ENGINE 0x10898640
// FUNCTION: ENGINE 0x10898650
// FUNCTION: ENGINE 0x10898680
// FUNCTION: ENGINE 0x108986C0
// FUNCTION: ENGINE 0x10898700
// FUNCTION: ENGINE 0x10898740
// FUNCTION: ENGINE 0x10898760
// FUNCTION: ENGINE 0x10898770
// FUNCTION: ENGINE 0x10898790
// FUNCTION: ENGINE 0x108987A0
// FUNCTION: ENGINE 0x108987C0
// FUNCTION: ENGINE 0x10898820
// FUNCTION: ENGINE 0x108988A0
// FUNCTION: ENGINE 0x108988C0
// FUNCTION: ENGINE 0x108988F0
// FUNCTION: ENGINE 0x10898960
// FUNCTION: ENGINE 0x10898A10
// FUNCTION: ENGINE 0x10898A50
// FUNCTION: ENGINE 0x10898A80
// FUNCTION: ENGINE 0x10898BE0
// FUNCTION: ENGINE 0x10898CD0
// FUNCTION: ENGINE 0x10898E70
// FUNCTION: ENGINE 0x10898EA0
// FUNCTION: ENGINE 0x10898F50
// FUNCTION: ENGINE 0x10898F90
// FUNCTION: ENGINE 0x10899010
// FUNCTION: ENGINE 0x10899170
// FUNCTION: ENGINE 0x10899250
// FUNCTION: ENGINE 0x10899620
// FUNCTION: ENGINE 0x10899730
// FUNCTION: ENGINE 0x10899750
