#include "code/engine/actorspawner.h"
#include "code/engine/controller/inputsystem.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/system/poimanager.hpp"
#include <new>

namespace engine
{
#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define ENGINE_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)
#define ENGINE_STRING_BASE(type) ((type*)content::gStringMemberBase)

	// FUNCTION: ENGINE 0x10905BC0
	content::ClassInfo* ActorSpawner::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ActorSpawner";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10905C00
	content::ClassInfo* ActorCrowdSpawner::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::ActorCrowdSpawner";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10905C40
	bool ActorSpawner::Slot5()
	{
		int index = playerIndex;
		if (index >= 0)
		{
			if (controller::InputSystem::Get()->slots[index].id == 0xffffffff)
			{
				return false;
			}
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10905C60
	void ActorSpawner::Slot3(int unused)
	{
		handle = SpawnActor((content::LoadInventory*)unused);
	}

	// FUNCTION: ENGINE 0x10905C80
	void ActorCrowdSpawner::Slot3(int unused)
	{
		SpawnGrid((content::LoadInventory*)unused);
	}

	// FUNCTION: ENGINE 0x10905C90
	bool ActorCrowdSpawner::IsGridSizeValid() const
	{
		if (numAlongX <= 99 && numAlongZ <= 99)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10905DE0
	ActorSpawner::ActorSpawner() : playerIndex(-1)
	{
	}

	// FUNCTION: ENGINE 0x10905FE0
	content::MemberList* ActorSpawner::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<GameObjectSpawner>();
		static content::BaseClassCasterImpl<GameObjectSpawner, ActorSpawner> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<ActorSpawner>(true, true, "pn"), ENGINE_NAME_OFFSET(ActorSpawner, objectName),
				"objectName" },
			{ content::GetMemberPrimitiveMetaType<ActorSpawner, int, 0>("pn"), ENGINE_OFFSET(ActorSpawner, playerIndex),
				"playerIndex" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x109060B0
	content::MemberList* ActorCrowdSpawner::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<GameObjectSpawner>();
		static content::BaseClassCasterImpl<GameObjectSpawner, ActorCrowdSpawner> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberStringMetaType<0>(&ENGINE_STRING_BASE(ActorCrowdSpawner)->baseName, "pn"),
				content::StringBufferOffset(&ENGINE_STRING_BASE(ActorCrowdSpawner)->baseName)
				+ (int)&((ActorCrowdSpawner*)0)->baseName, "baseName" },
			{ content::GetMatrixMetaType<ActorCrowdSpawner>(false, false, "pn"),
				content::MemberOffset(&((ActorCrowdSpawner*)0)->baseTransform,
				(int)&((ActorCrowdSpawner*)0)->baseTransform), "baseTransform" },
			{ content::GetMemberPrimitiveMetaType<ActorCrowdSpawner, unsigned int, 0>("pn"),
				ENGINE_OFFSET(ActorCrowdSpawner, numAlongX), "numAlongX" },
			{ content::GetMemberPrimitiveMetaType<ActorCrowdSpawner, unsigned int, 1>("pn"),
				ENGINE_OFFSET(ActorCrowdSpawner, numAlongZ), "numAlongZ" },
			{ content::GetMemberPrimitiveMetaType<ActorCrowdSpawner, float, 0>("pn"),
				ENGINE_OFFSET(ActorCrowdSpawner, gridSpacingX), "mGridSpacingX" },
			{ content::GetMemberPrimitiveMetaType<ActorCrowdSpawner, float, 1>("pn"),
				ENGINE_OFFSET(ActorCrowdSpawner, gridSpacingZ), "mGridSpacingZ" }
		};
		sList.members = sMembers;
		sList.count = 6;
		return &sList;
	}

	// FUNCTION: ENGINE 0x109062B0
	bool ActorSpawner::IsReady()
	{
		bool ready = true;
		if (handle.Get() != 0)
		{
			GameObject* object = handle.Get();
			object->SetActive(false);
			if (object->behaviours.IsActive())
			{
				InvalidateHandle(&handle, true);
				ready = false;
			}
		}
		return ready;
	}

	// FUNCTION: ENGINE 0x10906330
	GameObjectHandle ActorSpawner::SpawnActor(content::LoadInventory* inventory)
	{
		GameObjectHandle result = GameObjectSpawner::Spawn(inventory, objectName);
		if (playerIndex >= 0)
		{
			POIManager& poi = POIManager::Get(playerIndex);
			GameObjectHandle previous = poi.GetControlled();
			if (previous.Get() != 0)
			{
				poi.Pop(previous);
			}
			poi.Push(result);
		}
		return result;
	}

	// FUNCTION: ENGINE 0x109063C0
	// NONMATCHING: the engine looks the handle up twice (a word load of each half, the table and the serial test are
	// repeated for the object), ours shares the first lookup, 35 %
#ifdef NONMATCHING
	bool ActorCrowdSpawner::IsReady()
	{
		bool ready = true;
		GameObjectHandle* last = handles.end;
		for (GameObjectHandle* item = handles.begin; item != last; item++)
		{
			GameObjectHandle current = *item;
			if (current.IsValid())
			{
				GameObject* object = current.Get();
				object->SetActive(false);
				if (object->behaviours.IsActive())
				{
					InvalidateHandle(item, true);
					ready = false;
				}
			}
		}
		return ready;
	}
#endif

	// Appends a handle when the array has room
	static inline void PushHandle(ActorCrowdSpawner::HandleArray* array, const GameObjectHandle& value)
	{
		if (array->end < array->capacity)
		{
			GameObjectHandle* slot = array->end++;
			if (slot != 0)
			{
				*slot = value;
			}
		}
	}

	// FUNCTION: ENGINE 0x10906450
	// EQUIVALENT: the same reads and writes in the same order; the engine keeps both loop counters one word lower in
	// the frame, loads the grid spacing before the matrix component it adds to and reads the pushed handle through
	// the returned pointer, 96.6 %
	void ActorCrowdSpawner::SpawnGrid(content::LoadInventory* inventory)
	{
		if (objectTemplate != 0 && IsGridSizeValid())
		{
			HandleArray* array = &handles;
			unsigned int total = numAlongZ * numAlongX;
			array->Allocate(total);
			container::StringC<38> text;
			math::Matrix matrix;
			matrix.m[0][0] = baseTransform.m[0][0];
			matrix.m[0][1] = baseTransform.m[0][1];
			matrix.m[0][2] = baseTransform.m[0][2];
			matrix.m[0][3] = baseTransform.m[0][3];
			matrix.m[1][0] = baseTransform.m[1][0];
			matrix.m[1][1] = baseTransform.m[1][1];
			matrix.m[1][2] = baseTransform.m[1][2];
			matrix.m[1][3] = baseTransform.m[1][3];
			matrix.m[2][0] = baseTransform.m[2][0];
			matrix.m[2][1] = baseTransform.m[2][1];
			matrix.m[2][2] = baseTransform.m[2][2];
			matrix.m[2][3] = baseTransform.m[2][3];
			matrix.m[3][0] = baseTransform.m[3][0];
			matrix.m[3][1] = baseTransform.m[3][1];
			matrix.m[3][2] = baseTransform.m[3][2];
			matrix.m[3][3] = baseTransform.m[3][3];
			for (unsigned int x = 0; x < numAlongX; x++)
			{
				for (unsigned int z = 0; z < numAlongZ; z++)
				{
					text.Format("%s_%2d_%2d", baseName.Data(), x, z);
					content::ObjectName name(text.buffer, 1);
					GameObject* object = CreateObject(name, inventory);
					object->SetTransform(matrix);
					matrix.m[3][2] = gridSpacingZ + matrix.m[3][2];
					PushHandle(array, GetHandle(object));
				}
				matrix.m[3][0] = gridSpacingX + matrix.m[3][0];
				matrix.m[3][2] = baseTransform.m[3][2];
			}
		}
	}

	// FUNCTION: ENGINE 0x10906270
	ActorSpawner::~ActorSpawner()
	{
		if (handle.Get() != 0)
		{
			handle.DeferUpdate(false);
		}
	}

	// FUNCTION: ENGINE 0x109066D0
	ActorCrowdSpawner::ActorCrowdSpawner() : numAlongX(1), numAlongZ(1), gridSpacingX(1.0f), gridSpacingZ(1.0f)
	{
		baseTransform.Identity();
	}

	// FUNCTION: ENGINE 0x10906740
	ActorCrowdSpawner::~ActorCrowdSpawner()
	{
		GameObjectHandle* last = handles.end;
		for (GameObjectHandle* item = handles.begin; item != last; item++)
		{
			if (item->Get() != 0)
			{
				item->DeferUpdate(false);
			}
		}
		handles.end = handles.begin;
		if (handles.begin != 0)
		{
			delete[] handles.begin;
		}
	}
}

namespace container
{
	template class ArrayDynamic<engine::GameObjectHandle, AllocatorNew>;
}



// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10905CB0
// FUNCTION: ENGINE 0x10905CC0
// FUNCTION: ENGINE 0x10905CD0
// FUNCTION: ENGINE 0x10905CE0
// FUNCTION: ENGINE 0x10905CF0
// FUNCTION: ENGINE 0x10905D00
// FUNCTION: ENGINE 0x10905D20
// FUNCTION: ENGINE 0x10905D60
// FUNCTION: ENGINE 0x10905D90
// FUNCTION: ENGINE 0x10905E10
// FUNCTION: ENGINE 0x10905E20
// FUNCTION: ENGINE 0x10905E50
// FUNCTION: ENGINE 0x10905E60
// FUNCTION: ENGINE 0x10905E90
// FUNCTION: ENGINE 0x10905ED0
// FUNCTION: ENGINE 0x10905EE0
// FUNCTION: ENGINE 0x10905F20
// FUNCTION: ENGINE 0x10905F60
// FUNCTION: ENGINE 0x10905FA0
