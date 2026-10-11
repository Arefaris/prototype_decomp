#include "code/container/string.h"
#include "code/core/heap.h"
#include "code/core/memory/segmentpoolallocator.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectspawner.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/gameobject/messagerouter.h"

namespace engine
{
	// The attribute names (another unit's statics; names guessed): the template an object was built from, the
	// stream package an object belongs to
	extern content::ObjectName gMetaObjectTemplateName;
	extern content::ObjectName gPackageNameName;
	extern content::ObjectName gGameObjectsName;

	// GLOBAL: ENGINE 0x11283830
	int GameObjectSpawner::sNameCount;

	// FUNCTION: ENGINE 0x107F22C0
	content::ClassInfo* GameObjectSpawner::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "GameObjectSpawner";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x107F2300
	int GameObjectSpawner::GetNameCount()
	{
		return sNameCount;
	}

	// FUNCTION: ENGINE 0x107F2310
	bool GameObjectSpawner::IsReady()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x107F2320
	void GameObjectSpawner::SetTemplate(content::MetaObjectTemplate* newTemplate)
	{
		objectTemplate = newTemplate;
	}

	// FUNCTION: ENGINE 0x107F2370
	GameObjectSpawner::~GameObjectSpawner()
	{
		core::SafeRelease(objectTemplate);
	}

	// FUNCTION: ENGINE 0x107F2390
	GameObjectHandle GameObjectSpawner::Spawn(content::LoadInventory* inventory, content::ObjectName name)
	{
		GameObject* object;
		if (name.IsEmpty())
		{
			container::StringC<128> text;
			text.Format("gameobject%d", sNameCount++);
			content::ObjectName generated(text.buffer, 1);
			object = CreateObject(generated, inventory);
		}
		else
		{
			object = CreateObject(name, inventory);
		}
		if (object == 0)
		{
			return GameObjectHandle();
		}
		object->SetTransform(transform);
		return GetHandle(object);
	}

	// FUNCTION: ENGINE 0x107F2470
	// EQUIVALENT: the engine computes the transform's address after the reference count store, ours before it
	GameObjectSpawner::GameObjectSpawner() : objectTemplate(0)
	{
		transform.Identity();
	}

	// FUNCTION: ENGINE 0x107F2510
	content::MemberList* GameObjectSpawner::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMatrixMetaType<GameObjectSpawner>(false, false, "pn"),
				content::MemberOffset(&((GameObjectSpawner*)0)->transform, (int)&((GameObjectSpawner*)0)->transform),
				"transform" },
			{ content::GetReferenceMetaType<GameObjectSpawner, content::MetaObjectTemplate>("p"),
				content::MemberOffset(&((GameObjectSpawner*)0)->objectTemplate,
				(int)&((GameObjectSpawner*)0)->objectTemplate), "template" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x107F25C0
	// EQUIVALENT: stack slots: the engine shares one slot between the heap statistic, the attribute lookup and the
	// handle and puts the attribute writer at +8; ours keeps the statistic apart (everything else is identical)
	GameObject* GameObjectSpawner::Create(content::MetaObjectTemplate* tmpl, const content::ObjectName& name, int heap,
		content::LoadInventory* inventory, content::LoadInventory* target, bool flag)
	{
		if (!IsGameObjectSystemReady())
		{
			return 0;
		}
		if (tmpl == 0)
		{
			return 0;
		}
		core::SegmentPoolAllocator* pool = 0;
		int value;
		if (core::GetHeapAllocator(heap)->GetStat(0xb, &value))
		{
			SetGameObjectHeap();
			pool = static_cast<core::SegmentPoolAllocator*>(core::GetHeapAllocator(heap));
			if (!pool->HasSegment())
			{
				return 0;
			}
			pool->PushCounter();
			pool->Open();
		}
		if (inventory == 0)
		{
			inventory = content::gRootInventory;
		}
		GameObject* object = tmpl->Create(heap, inventory, name, flag);
		if (object == 0)
		{
			return 0;
		}
		if (pool != 0)
		{
			pool->PopCounter();
		}
		if (target == 0)
		{
			target = content::gRootInventory->Find<content::LoadInventory>(gGameObjectsName);
		}
		target->Add(name, object);
		AttributeWriter<content::ObjectName> templateName =
			object->GetAttributeWriter<content::ObjectName>(gMetaObjectTemplateName);
		if (templateName.value != 0)
		{
			*templateName.value = tmpl->name;
		}
		if (flag)
		{
			const content::ObjectName* packageName = object->GetAttributeValue<content::ObjectName>(gPackageNameName);
			if (packageName != 0)
			{
				GameObjectHandle handle = GetHandle(object);
				handle.RouterRemove(*static_cast<const MessageListeners*>(packageName));
			}
		}
		return object;
	}

	// FUNCTION: ENGINE 0x107F2710
	GameObject* GameObjectSpawner::Create(content::MetaObjectTemplate* tmpl, const content::ObjectName& name,
		content::LoadInventory* inventory, content::LoadInventory* target, bool flag)
	{
		return Create(tmpl, name, core::GetCurrentHeap(), inventory, target, flag);
	}

	// FUNCTION: ENGINE 0x107F2740
	GameObject* GameObjectSpawner::Create(content::MetaObjectTemplate* tmpl, content::LoadInventory* inventory)
	{
		container::StringC<128> text;
		text.Format("gameobject%d", sNameCount++);
		content::ObjectName name(text.buffer, 1);
		return Create(tmpl, name, inventory, 0, true);
	}

	// FUNCTION: ENGINE 0x107F27B0
	GameObject* GameObjectSpawner::CreateObject(const content::ObjectName& name, content::LoadInventory* inventory)
	{
		return Create(objectTemplate, name, inventory, 0, true);
	}

	// Kept copies: the meta type getters, the scalar deleting destructor
	// FUNCTION: ENGINE 0x107F2330
	// FUNCTION: ENGINE 0x107F24A0
	// FUNCTION: ENGINE 0x107F24C0
}
