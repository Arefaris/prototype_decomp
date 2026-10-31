#include "code/engine/propspawner.h"
#include "code/content/stringmetatype.h"
#include "code/core/refptr.h"
#include "code/core/strings.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/gameobject/gameobjectmessages.h"
#include "code/math/mathconstants.h"
#include <new>
#include <string.h>

// The reallocation of the state array (0x10842A50): the engine calls its own copy of the template member from the
// constructor of the initial states
// FUNCTION: ENGINE 0x10842A50
template<> void container::ArrayDynamic<engine::TreeState, container::AllocatorNew>::Reserve(int count)
{
	int size = end - begin;
	if (count != capacity - begin)
	{
		int keep = count < size ? count : size;
		engine::TreeState* storage = (engine::TreeState*)operator new[](count * sizeof(engine::TreeState));
		if (storage == 0)
		{
			keep = 0;
			count = 0;
		}
		else
		{
			for (int i = 0; i < keep; i++)
			{
				ConstructCopyAt(storage + i, begin[i]);
			}
		}
		if (begin != 0)
		{
			Destroy(begin, end);
			operator delete[](begin);
		}
		end = storage + keep;
		begin = storage;
		capacity = storage + count;
	}
}

namespace engine
{
	// The attribute names (0x11283538 holds the spawner, 0x11283520 the scale; names guessed)
	extern content::ObjectName gPropSpawnerName;
	extern content::ObjectName gScaleName;

#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10842010
	content::ClassInfo* PropSpawner::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::PropSpawner";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10842260
	PropSpawner::PropSpawner() : scale(1.0f, 1.0f, 1.0f), initialState(0)
	{
	}

	// FUNCTION: ENGINE 0x108422E0
	// FUNCTION: ENGINE 0x108424D0
	PropSpawner::~PropSpawner()
	{
		core::SafeRelease(initialState);
		IsReady();
	}

	// FUNCTION: ENGINE 0x10842050
	bool PropSpawner::IsReady()
	{
		Refresh();
		return GameObjectSpawner::IsReady();
	}

	// FUNCTION: ENGINE 0x10842070
	const content::ObjectName* PropSpawner::GetName()
	{
		return &name;
	}

	// FUNCTION: ENGINE 0x10842310
	void PropSpawner::SetName(const content::ObjectName& newName)
	{
		name = newName;
	}

	// FUNCTION: ENGINE 0x10842080
	const char* PropSpawner::GetInitialState()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x10842320
	int PropSpawner::GetStateCount()
	{
		if (initialState != 0)
		{
			return initialState->Size();
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x108424F0
	void PropSpawner::Refresh()
	{
		if (spawned.Get() != 0)
		{
			spawned.DeferUpdate(false);
		}
	}

	// The writer of the spawner attribute of an object (0x10842600; the pointer to the value is behind the vftable
	// of the attribute)
	template<> AttributeWriter<PropSpawner*> GameObject::GetAttributeWriter<PropSpawner*>(const content::ObjectName& name)
	{
		Attribute<PropSpawner*>* attribute = (Attribute<PropSpawner*>*)FindAttribute(name);
		if (attribute != 0)
		{
			return AttributeWriter<PropSpawner*>(&attribute->value, name, this);
		}
		return AttributeWriter<PropSpawner*>();
	}

	// FUNCTION: ENGINE 0x108426F0
	void PropSpawner::Slot3(int inventory)
	{
		if (name.IsEmpty())
		{
			spawned = Spawn((content::LoadInventory*)inventory, content::ObjectName("", 1));
		}
		else
		{
			GameObject* object = CreateObject(name, (content::LoadInventory*)inventory);
			if (object != 0)
			{
				spawned = GetHandle(object);
			}
		}
		if (spawned.IsValid())
		{
			AttributeWriter<PropSpawner*> writer = spawned.Get()->GetAttributeWriter<PropSpawner*>(gPropSpawnerName);
			if (writer.value != 0)
			{
				*writer.value = this;
			}
			Apply();
		}
	}

	// FUNCTION: ENGINE 0x108427E0
	// NONMATCHING: the engine builds the scale attribute's writer in each branch of a lookup it expands in place and
	// stores through the pointer it holds in a register, while ours reloads the pointer from the writer after every
	// store; the registers of the object and the value are swapped as well, 69.4 %
#ifdef NONMATCHING
	// The writer of the scale attribute (the body of GetAttributeWriter, expanded in place)
	static __forceinline AttributeWriter<math::Vector> GetScaleWriter(GameObject* object)
	{
		BaseAttribute* attribute = object->FindAttribute(gScaleName);
		if (attribute != 0)
		{
			math::Vector* value = &((Attribute<math::Vector>*)attribute)->Get();
			return AttributeWriter<math::Vector>(value, gScaleName, object);
		}
		return AttributeWriter<math::Vector>();
	}

	void PropSpawner::Apply()
	{
		spawned.Get()->SetTransform(transform);
		GameObject* object = spawned.Get();
		{
			AttributeWriter<math::Vector> writer = GetScaleWriter(object);
			if (writer.value != 0)
			{
				writer.value->x = scale.x;
				writer.value->y = scale.y;
				writer.value->z = scale.z;
			}
		}
		int count = GetStateCount();
		for (int i = 0; i < count; i++)
		{
			SetPropLogicStateMessage message((*initialState)[i].prefix, (*initialState)[i].state);
			spawned.Get()->SendMessage(&message);
		}
	}
#endif

	// FUNCTION: ENGINE 0x10842D80
	void PropSpawner::SetInitialState(const char* packed, content::LoadInventory* inventory)
	{
		if (inventory != 0)
		{
			UnpackedInitialState* state = inventory->Find<UnpackedInitialState>(content::ObjectName(packed, 0));
			if (state == 0)
			{
				state = new UnpackedInitialState(packed);
				inventory->Add(content::ObjectName(packed, 1), state);
				core::RefAssign(initialState, state);
			}
			else if (state != initialState)
			{
				core::RefAssign(initialState, state);
			}
		}
	}

	// FUNCTION: ENGINE 0x10842B20
	// EQUIVALENT: the engine writes an unused byte of its frame before the reference count is cleared, ours (kept
	// alive as a volatile local) writes it after the array's pointer is set; same calls, reads and writes otherwise,
	// 92.7 %
	UnpackedInitialState::UnpackedInitialState(const char* packed)
	{
		volatile bool marker = false;
		char text[0x100];
		char part[0x100];
		Clear();
		core::StrCpy(text, packed);
		for (char* token = core::StrTok(text, ","); token != 0; token = core::StrTok(0, ","))
		{
			TreeState state;
			char* colon = strchr(token, ':');
			if (colon != 0)
			{
				core::StrNCpy(part, token, strlen(token) - strlen(colon) + 1);
				content::ObjectName prefix(part, 1);
				state.prefix = prefix;
				core::StrNCpy(part, colon + 1, strlen(colon));
				content::ObjectName name(part, 1);
				state.state = name;
			}
			else
			{
				state.prefix = content::ObjectName();
				content::ObjectName name(token, 1);
				state.state = name;
			}
			if (Size() == Capacity())
			{
				Reserve(Capacity() + 1);
			}
			PushBack(state);
		}
		source = content::ObjectName(packed, 1);
	}

	// FUNCTION: ENGINE 0x10842E30
	content::MemberList* PropSpawner::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<GameObjectSpawner>();
		static content::BaseClassCasterImpl<GameObjectSpawner, PropSpawner> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<PropSpawner, 0>("pn"), 0x58, "scale" },
			{ content::GetStringMemberWithResolverMetaType<PropSpawner, 0>(&PropSpawner::GetInitialState,
				&PropSpawner::SetInitialState, "pn"), 0, "initialState" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}
}

// The array's members the engine keeps out of line copies of (the constructor expands the others in place)
template bool container::ArrayDynamic<engine::TreeState, container::AllocatorNew>::Create(unsigned int);
template engine::TreeState& container::ArrayDynamic<engine::TreeState, container::AllocatorNew>::operator[](int);
template void container::ArrayDynamic<engine::TreeState, container::AllocatorNew>::Free();

// Kept copies (inline functions and template instances of this unit):
// FUNCTION: ENGINE 0x10842090
// FUNCTION: ENGINE 0x10842190
// FUNCTION: ENGINE 0x108421B0
// FUNCTION: ENGINE 0x108421E0
// FUNCTION: ENGINE 0x10842200
// FUNCTION: ENGINE 0x10842230
// FUNCTION: ENGINE 0x10842340
// FUNCTION: ENGINE 0x10842370
// FUNCTION: ENGINE 0x10842380
// FUNCTION: ENGINE 0x108423E0
// FUNCTION: ENGINE 0x108423F0
// FUNCTION: ENGINE 0x10842410
// FUNCTION: ENGINE 0x10842430
// FUNCTION: ENGINE 0x10842460
// FUNCTION: ENGINE 0x10842480
// FUNCTION: ENGINE 0x10842490
// FUNCTION: ENGINE 0x10842530
// FUNCTION: ENGINE 0x10842590
// FUNCTION: ENGINE 0x10842600
// FUNCTION: ENGINE 0x108429F0
// FUNCTION: ENGINE 0x10842A30
// FUNCTION: ENGINE 0x10842110
// FUNCTION: ENGINE 0x10842160
// FUNCTION: ENGINE 0x10842180
// FUNCTION: ENGINE 0x10842360
// FUNCTION: ENGINE 0x108422B0
// FUNCTION: ENGINE 0x108429E0
// FUNCTION: ENGINE 0x10842A00

// The lookup of a prop spawner by name (the filter the inventory is handed)
// FUNCTION: ENGINE 0x108423C0
template class content::LoadInventory::DynamicCaster<engine::PropSpawner>;
