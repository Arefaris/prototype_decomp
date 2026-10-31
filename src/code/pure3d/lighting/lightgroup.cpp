// pure3d::LightGroup (unit around 0x107AC0F0 - 0x107AC3F0; the file name is guessed from the class). Names are guesses.
#include "code/pure3d/lightgroup.h"

namespace engine
{
	namespace render
	{
		// FUNCTION: ENGINE 0x107AC0F0
		void AssignControllerObject(void*& pointer, pure3d::Light* object)
		{
			if (object != 0)
			{
				object->AddRef();
			}
			if (pointer != 0)
			{
				((pure3d::RefCounted*)pointer)->Release();
			}
			pointer = object;
		}

		// FUNCTION: ENGINE 0x107B2F40
		void ReleaseControllerObject(void*& object)
		{
			if (object != 0)
			{
				((pure3d::RefCounted*)object)->Release();
				object = 0;
			}
		}
	}
}

namespace pure3d
{
	// FUNCTION: ENGINE 0x107AC290
	bool LightPointers::Allocate(unsigned int newCount, Light* const& fill)
	{
		if (begin != 0)
		{
			return false;
		}
		if (newCount > 0)
		{
			begin = (Light**)operator new[](newCount * sizeof(Light*));
			if (begin != 0)
			{
				end = begin + newCount;
				FillCopies(begin, newCount, fill);
				return true;
			}
		}
		begin = 0;
		end = 0;
		return false;
	}

	// FUNCTION: ENGINE 0x107AC130
	void LightGroup::SetLight(int index, Light* light)
	{
		engine::render::AssignControllerObject((void*&)lights.begin[index], light);
	}

	// FUNCTION: ENGINE 0x107AC150
	bool LightGroup::AddLight(Light* light, bool unique)
	{
		if (unique)
		{
			for (unsigned int i = 0; i < count; i++)
			{
				if (lights.begin[i] == light)
				{
					return false;
				}
			}
		}
		bool added = false;
		if (count < capacity)
		{
			count++;
			engine::render::AssignControllerObject((void*&)lights.begin[count - 1], light);
			added = true;
		}
		return added;
	}

	// FUNCTION: ENGINE 0x107AC1B0
	bool LightGroup::RemoveLight(Light* light)
	{
		bool removed = false;
		for (unsigned int i = 0; i < count; i++)
		{
			if (lights.begin[i] == light)
			{
				engine::render::AssignControllerObject((void*&)lights.begin[i], lights.begin[count - 1]);
				engine::render::AssignControllerObject((void*&)lights.begin[count - 1], 0);
				count--;
				removed = true;
				break;
			}
		}
		return removed;
	}

	// FUNCTION: ENGINE 0x107AC2F0
	LightGroup::LightGroup() : capacity(0), count(0)
	{
	}

	// FUNCTION: ENGINE 0x107AC310
	LightGroup::LightGroup(unsigned int newCapacity) : count(0), capacity(newCapacity)
	{
		lights.Allocate(newCapacity, (Light*)0);
	}

	// FUNCTION: ENGINE 0x107AC350
	LightGroup::~LightGroup()
	{
		for (unsigned int i = 0; i < capacity; i++)
		{
			if (lights.begin[i] != 0)
			{
				lights.begin[i]->Release();
				lights.begin[i] = 0;
			}
		}
		capacity = 0;
		count = 0;
		_ReadWriteBarrier();
		if (lights.begin != 0)
		{
			operator delete[](lights.begin);
		}
	}

	// FUNCTION: ENGINE 0x107AC3B0
	void LightGroup::SetCount(unsigned int newCount)
	{
		count = newCount;
		if (capacity == 0)
		{
			capacity = newCount;
			lights.Allocate(newCount, (Light*)0);
		}
	}
}
