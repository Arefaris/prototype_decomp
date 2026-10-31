// pure3d::LightGroup (RTTI name; bases pure3d::Entity, RefCounted, core::IRefCount): a fixed list of lights that are
// switched together (the scene's lights of one name). The list keeps a reference to each light. Names are guesses.
#ifndef PURE3D_LIGHTGROUP_H
#define PURE3D_LIGHTGROUP_H

#include "code/pure3d/context.h"
#include "code/pure3d/entity.h"
#include "code/pure3d/light.h"

namespace engine
{
	namespace render
	{
		// The unit's copies of the reference helpers the light lists go through (the lights are held as plain pointers):
		// releases the object and clears the pointer (0x107B2F40), and takes a reference to a new object and releases the
		// old one (0x107AC0F0)
		void ReleaseControllerObject(void*& object);
		void AssignControllerObject(void*& pointer, pure3d::Light* object);
	}
}

namespace pure3d
{
	// The room of a light list: begin and end of an array made with operator new[] (0x107AC290 makes it, once)
	struct LightPointers
	{
		LightPointers()
		{
			begin = 0;
			end = 0;
		}
		bool Allocate(unsigned int newCount, Light* const& fill);

		Light** begin;
		Light** end;
	};

	class LightGroup : public Entity
	{
	public:
		// 0x107AC2F0 / 0x107AC310 (room for that many lights, all empty)
		LightGroup();
		explicit LightGroup(unsigned int newCapacity);
		// Slot 2 (the body is 0x107AC350, the deleting destructor 0x107AC3E0)
		virtual ~LightGroup();

		// 0x107AC130: puts the light into the slot
		void SetLight(int index, Light* light);
		// 0x107AC150: adds the light to the list; with unique the same light is not added twice (false then, and false
		// when the list is full)
		bool AddLight(Light* light, bool unique);
		// 0x107AC1B0: takes the light out (the last one takes its place); false when it was not in the list
		bool RemoveLight(Light* light);
		// 0x107AC3B0: sets how many lights are in the list (and makes the room for them when there is none)
		void SetCount(unsigned int newCount);

		unsigned int capacity;       // +0x10
		unsigned int count;          // +0x14
		LightPointers lights;        // +0x18
	};
}

#endif
