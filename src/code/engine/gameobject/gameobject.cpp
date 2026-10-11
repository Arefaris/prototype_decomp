#include "code/core/heap.h"
#include "code/core/memory/imemoryallocator.h"
#include "code/core/memory/segmentpoolallocator.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/message.h"
#include "code/engine/system/enginememory.h"

namespace core
{
	// 0x10646CC0 / 0x10646CA0: the calling thread's value of a thread-local slot (false when the thread has none)
	bool GetThreadValue(int slot, int* value);
	bool SetThreadValue(int slot, int value);
}

namespace engine
{
	// The thread-local slots InitGameObjectSystem allocates (gameobjectsystem.cpp)
	extern int gThreadSlotA;
	extern int gThreadSlotB;
	// The dynamic attribute heap (gameobjectsystem.cpp)
	extern int gAttributeHeap;
	// The shared identity transform (gameobjectsystem.cpp)
	extern Attribute<math::Matrix>* gIdentityTransform;
	// The name of the transform attribute (0x11283510) and a name the engine tests after creating an object
	// (0x11276940; meaning unknown)
	extern content::ObjectName gTransformName;
	extern content::ObjectName gUnknownName11276940;

	// engine::TransformAttributeUpdatedMessage (RTTI): type 0x1A, sent when the transform is set
	class TransformAttributeUpdatedMessage : public Message
	{
	public:
		TransformAttributeUpdatedMessage() : Message(0x1a, 0)
		{
		}
		virtual ~TransformAttributeUpdatedMessage()
		{
		}
	};

	// FUNCTION: ENGINE 0x107E0710
	void GameObject::Slot3(int unused)
	{
		core::IMemoryAllocator* allocator = core::GetHeapAllocator(core::GetCurrentHeap());
		int value;
		if (allocator->GetStat(0xb, &value))
		{
			static_cast<core::SegmentPoolAllocator*>(allocator)->Select((unsigned int)this);
		}
		RegisterGameObject(this);
		behaviours.Slot1();
		if (allocator->GetStat(0xb, &value))
		{
			static_cast<core::SegmentPoolAllocator*>(allocator)->Next();
		}
	}

	// FUNCTION: ENGINE 0x107E0790
	int GetConstructionHeap()
	{
		int heap;
		core::GetThreadValue(gThreadSlotB, &heap);
		return heap;
	}

	// FUNCTION: ENGINE 0x107E07B0
	void SetConstructionHeap(int heap)
	{
		core::SetThreadValue(gThreadSlotB, heap);
	}

	// FUNCTION: ENGINE 0x107E07D0
	GameObject* GetConstructingObject()
	{
		int object;
		core::GetThreadValue(gThreadSlotA, &object);
		return (GameObject*)object;
	}

	// FUNCTION: ENGINE 0x107E07F0
	void SetConstructingObject(GameObject* object)
	{
		core::SetThreadValue(gThreadSlotA, (int)object);
	}

	// FUNCTION: ENGINE 0x107E0810
	bool GameObject::SendMessage(Message* message)
	{
		if (behaviours.IsListening(message->type))
		{
			behaviours.OnMessage(message);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107E0850
	bool GameObject::PostMessage(Message* message)
	{
		if (behaviours.IsListening(message->type))
		{
			behaviours.OnPostedMessage(message);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107E0890
	void GameObject::SetTransform(const math::Matrix& matrix)
	{
		transform->Get() = matrix;
		TransformAttributeUpdatedMessage message;
		SendMessage(&message);
	}

	// FUNCTION: ENGINE 0x107E08E0
	void GameObject::SetPosition(const math::Vector& position)
	{
		float* translation = transform->Get().m[3];
		translation[0] = position.x;
		translation[1] = position.y;
		translation[2] = position.z;
		TransformAttributeUpdatedMessage message;
		SendMessage(&message);
	}

	// FUNCTION: ENGINE 0x107E0940
	void GameObject::Unknown107E0940(int value)
	{
		behaviours.Unknown10839D80(value);
	}

	// FUNCTION: ENGINE 0x107E0950
	void GameObject::Slot8(int a, int b)
	{
		behaviours.Slot8(a, b);
	}

	// FUNCTION: ENGINE 0x107E0960
	void GameObject::Slot9(int a)
	{
		behaviours.Slot9(a);
	}

	// FUNCTION: ENGINE 0x107E0BE0
	void* GameObject::operator new(unsigned int size)
	{
		SetConstructionHeap(core::GetCurrentHeap());
		return ::operator new[](size);
	}

	// FUNCTION: ENGINE 0x107E0C00
	BaseAttribute* GameObject::FindAttribute(const content::ObjectName& name)
	{
		AttributeEntry* entry = attributes.begin;
		for (AttributeEntry* end = attributes.end; entry < end; entry++)
		{
			if (entry->name == name)
			{
				return entry->attribute;
			}
		}
		DynamicAttributeList* list = dynamicAttributes;
		if (list != 0)
		{
			entry = list->begin;
			for (AttributeEntry* listEnd = list->end; entry < listEnd; entry++)
			{
				if (entry->name == name)
				{
					return entry->attribute;
				}
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x107E0C60
	void GameObject::SetActive(bool active)
	{
		bool wasActive = behaviours.IsActive();
		if (active)
		{
			if (!wasActive)
			{
				behaviours.OnActiveChanged(true);
			}
		}
		else if (wasActive)
		{
			behaviours.OnActiveChanged(false);
		}
	}

	// FUNCTION: ENGINE 0x107E0F40
	bool GameObject::IsReady()
	{
		if (behaviours.IsActive())
		{
			SetActive(false);
			if (behaviours.IsActive())
			{
				return false;
			}
		}
		if (IsRegistered())
		{
			UnregisterGameObject(this);
		}
		return behaviours.Slot2();
	}

	// FUNCTION: ENGINE 0x107E1670
	GameObject::GameObject()
		: dynamicAttributes(0), transform(0), behaviours(this)
	{
		index = 0xffff;
		updatePass = 0;
		SetConstructingObject(this);
	}

	// FUNCTION: ENGINE 0x107E16C0
	void GameObject::AddRef()
	{
		LoadObject::AddRef();
	}

	// FUNCTION: ENGINE 0x107E16D0
	void GameObject::Release()
	{
		LoadObject::Release();
	}

	// FUNCTION: ENGINE 0x107E1700
	void GameObject::AddAttribute(content::ObjectName name, BaseAttribute* attribute)
	{
		int capacity = attributes.Capacity();
		if (attributes.Size() == capacity)
		{
			attributes.Reserve(capacity + 8);
		}
		new (attributes.Grow()) AttributeEntry(name, attribute);
	}

	// FUNCTION: ENGINE 0x107E1770
	bool GameObject::AddDynamicAttribute(content::ObjectName name, BaseAttribute* attribute)
	{
		if (dynamicAttributes == 0)
		{
			dynamicAttributes = new (gAttributeHeap) DynamicAttributeList;
		}
		if (dynamicAttributes->Size() < gAttributeListLength)
		{
			new (dynamicAttributes->Grow()) AttributeEntry(name, attribute);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107E1A00
	bool GameObject::Slot5()
	{
		int heap = GetConstructionHeap();
		behaviours.Slot0();
		BaseAttribute* attribute = FindAttribute(gTransformName);
		if (attribute == 0)
		{
			AddAttribute(gTransformName, gIdentityTransform);
			transform = gIdentityTransform;
		}
		else
		{
			transform = dynamic_cast<Attribute<math::Matrix>*>(attribute);
		}
		container::Compact(attributes, heap);
		core::IMemoryAllocator* allocator = core::GetHeapAllocator(heap);
		int value;
		if (allocator->GetStat(0xb, &value))
		{
			static_cast<core::SegmentPoolAllocator*>(allocator)->Next();
		}
		SetConstructingObject(0);
		SetConstructionHeap(-1);
		return gUnknownName11276940.IsEmpty() ? false : true;
	}

	// FUNCTION: ENGINE 0x107E1AC0
	// EQUIVALENT: the engine saves esi / edi before testing for the list; our build tests first
	void GameObject::RemoveDynamicAttribute(const content::ObjectName& name)
	{
		if (dynamicAttributes != 0)
		{
			for (AttributeEntry* entry = dynamicAttributes->begin; entry < dynamicAttributes->end; entry++)
			{
				if (entry->name == name)
				{
					delete entry->attribute;
					dynamicAttributes->EraseFast(entry);
					if (dynamicAttributes->IsEmpty())
					{
						delete dynamicAttributes;
						dynamicAttributes = 0;
					}
					return;
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x107E1BA0
	GameObject::~GameObject()
	{
		int heap = GetConstructionHeap();
		if (GetConstructingObject() == this)
		{
			core::IMemoryAllocator* allocator = core::GetHeapAllocator(heap);
			int value;
			if (allocator->GetStat(0xb, &value))
			{
				static_cast<core::SegmentPoolAllocator*>(allocator)->Next();
			}
		}
		behaviours.Slot10();
		if (GetConstructingObject() == this)
		{
			SetConstructingObject(0);
			SetConstructionHeap(-1);
		}
		if (dynamicAttributes != 0)
		{
			for (AttributeEntry* entry = dynamicAttributes->begin; entry < dynamicAttributes->end; entry++)
			{
				delete entry->attribute;
			}
			delete dynamicAttributes;
		}
		for (AttributeEntry* entry = attributes.begin; entry < attributes.end; entry++)
		{
			if (entry->attribute != gIdentityTransform)
			{
				delete entry->attribute;
			}
		}
		attributes.Reset();
	}
}
