// engine::AdvertisementMapping (RTTI and reflection names): the part of a model an advertisement is shown on, named by
// the primitive group and index of its drawable, the shader input that takes the picture, the polygon of up to four
// points the picture is cut to and the slot it belongs to. The elements of the "mappings" array of
// engine::AdvertisementBehaviour (unit 0x10917A30 - 0x10919F50; no assert path, the file name is a guess). The reflected
// member names are original; the rest is guessed.
#ifndef ENGINE_ADVERTISEMENTBEHAVIOUR_H
#define ENGINE_ADVERTISEMENTBEHAVIOUR_H

#include "code/container/arraycdynamic.h"
#include "code/container/arraydynamicallocatornew.h"
#include "code/container/string.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/math/vector.h"

namespace engine
{
	class BaseAttribute;

	// One mapping (0xB0 bytes)
	struct AdvertisementMapping
	{
		// 0x10919780
		AdvertisementMapping();
		// 0x10919690
		AdvertisementMapping(const AdvertisementMapping& other);
		// 0x10919230
		AdvertisementMapping& operator=(const AdvertisementMapping& other);

		// 0x109179F0 / 0x10919300
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		core::Name<core::CaseSensitiveKey> primitiveGroup;  // +0
		int primitiveIndex;  // +8
		container::StringC<64> shaderInput;  // +0xC
		container::ArrayCDynamic<math::Vector, 4> adPoly;  // +0x50
		__declspec(align(8)) core::Name<core::CaseSensitiveKey> slot;  // +0x88
		int unknown90;
		int unknown94;
		int unknown98;
		int unknown9C;
		int unknownA0;
		bool unknownA4;
		bool unknownA5;
		int unknownA8;
		int unknownAC;
	};

	typedef container::ArrayDynamic<AdvertisementMapping, container::AllocatorNew> AdvertisementMappingArray;

	// The interface a behaviour that puts advertisements on a model implements (RTTI name; one vftable slot)
	struct OnlineAdvertElementCallback
	{
		// 0x10917A80 (a copy of the inline constructor)
		OnlineAdvertElementCallback()
		{
		}
		virtual void Slot0(int unused1, int unused2) = 0;
	};

	// Puts the pictures of the online advertisements onto the mappings of its object's model (RTTI and reflection names;
	// 0x28 bytes). The secondary base sits at +0xC.
	class AdvertisementBehaviour : public Behaviour, public OnlineAdvertElementCallback
	{
	public:
		// 0x10919D70
		explicit AdvertisementBehaviour(GameObject* newOwner);
		// 0x10919DD0 (deleting destructor 0x10919F20)
		virtual ~AdvertisementBehaviour();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x10917D40, left to the engine)
		virtual void Slot1();
		// vftable slot 4 (0x10917E60, left to the engine)
		virtual void Update(float dt, unsigned short mask);
		// vftable slot 6 (0x10918B50, left to the engine)
		virtual void OnMessage(Message* message);
		// the callback's slot (0x10919060, left to the engine)
		virtual void Slot0(int unused1, int unused2);

		AdvertisementMappingArray mappings;  // +0x10
		// The word behind the array (the arrays of this kind are followed by one; never touched here)
		int unknown1C;
		bool registered;  // +0x20
		BaseAttribute* scale;  // +0x24
	};
}

namespace content
{
	// The insertion and the removal of the helpers are left to the engine (it keeps the default element in a function of
	// its own, and expands the removal in the helper)
	template<> void ArrayDynamicHelper<engine::AdvertisementMappingArray>::Insert(void* array, int index, int unused);
	template<> void ArrayDynamicHelper<engine::AdvertisementMappingArray>::Erase(void* array, int index, int unused);
	template<> void ArrayCDynamicHelper<container::ArrayCDynamic<math::Vector, 4> >::Insert(void* array, int index,
		int unused);
	template<> void ArrayCDynamicHelper<container::ArrayCDynamic<math::Vector, 4> >::Erase(void* array, int index,
		int unused);
}

#endif
