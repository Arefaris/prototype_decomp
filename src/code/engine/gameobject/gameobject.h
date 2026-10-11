// engine::GameObject (RTTI: 7 vftable slots, bases content::MetaLoadObject / LoadObject / core::IRefCount; 0x60
// bytes), gameobject.cpp (unit 0x107E05A0 - 0x107E1D20, no assert path; the file name is a guess): named attributes
// (the transform among them), a dynamic attribute list, the behaviour controller and the master table index.
#ifndef ENGINE_GAMEOBJECT_GAMEOBJECT_H
#define ENGINE_GAMEOBJECT_GAMEOBJECT_H

#include "code/container/arraydynamic.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/math/matrix.h"

namespace engine
{
	class Message;

	// The dynamic attribute list heap and length (gameobjectsystem.cpp's InitGameObjectSystem sets them)
	extern int gAttributeListHeap;
	extern unsigned int gAttributeListLength;

	// engine::BaseAttribute / engine::Attribute<T> (RTTI names; the GameObject's transform is an
	// Attribute<math::Matrix> found through dynamic_cast)
	class BaseAttribute
	{
	public:
		// 0x1086C900 / 0x1086C940 (the attribute unit)
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		virtual ~BaseAttribute();
	};

	template<class T> class Attribute : public BaseAttribute
	{
	public:
		// Out of line in the attribute's unit (Attribute<math::Matrix>: 0x1028AB90, starts at the identity)
		Attribute();

		virtual T& Get();

		T value;
	};

	// The construction helpers (gameobject.cpp): the heap a game object is being created in and the object being
	// constructed, kept in thread-local slots (names guessed)
	int GetConstructionHeap();
	void SetConstructionHeap(int heap);
	GameObject* GetConstructingObject();
	void SetConstructingObject(GameObject* object);

	class GameObject : public content::MetaLoadObject
	{
	public:
		// An attribute kept under a name (16 bytes; the copy keeps the last word)
		struct AttributeEntry
		{
			static content::ClassInfo* GetClassInfo();

			static content::MemberList* GetMembers();

			AttributeEntry()
				: key(0, 1)
			{
				attribute = 0;
			}
			AttributeEntry(content::ObjectName newKey, BaseAttribute* newAttribute)
				: key(newKey)
			{
				attribute = newAttribute;
			}
			AttributeEntry(const AttributeEntry& other)
				: key(other.key)
			{
				attribute = other.attribute;
			}
			AttributeEntry& operator=(const AttributeEntry& other)
			{
				key = other.key;
				attribute = other.attribute;
				return *this;
			}

			// The reflected members are "key" and "attribute"
			content::ObjectName key;
			BaseAttribute* attribute;
			int unknownC;
		};

		typedef container::ArrayDynamicHeap<AttributeEntry> AttributeList;

		// The attributes added at run time (allocated from the dynamic attribute heap)
		struct DynamicAttributeList : AttributeList
		{
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			DynamicAttributeList()
				: AttributeList(gAttributeListLength, container::AllocatorCoreAligned<16>(gAttributeListHeap))
			{
			}
		};

		GameObject();
		static void* operator new(unsigned int size);

		// The reflection data (the class name is plain "GameObject"; members "attributes", "dynamicAttributes" and
		// "behaviourController")
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// The vftable (RTTI: 7 slots; slot 2 is the deleting destructor, slot 6 MetaLoadObject's)
		virtual void AddRef();
		virtual void Release();
		virtual ~GameObject();
		// Registers the object in the master table and starts its behaviours (name guessed)
		virtual void Slot3(int unused);
		// True when the object may be released: its behaviours are stopped and it is unregistered (guessed)
		virtual bool IsReady();
		virtual bool Slot5();

		bool IsRegistered() const
		{
			return index != 0xffff;
		}
		bool TestUpdateMask(unsigned short mask) const
		{
			return (behaviours.updateMask & mask) != 0;
		}

		// Delivers the message when a behaviour listens for its type (through the controller's slot 6 / 5)
		bool SendMessage(Message* message);
		bool PostMessage(Message* message);
		void SetTransform(const math::Matrix& matrix);
		void SetPosition(const math::Vector& position);
		void Unknown107E0940(int value);
		void Slot8(int a, int b);
		void Slot9(int a);
		BaseAttribute* FindAttribute(const content::ObjectName& name);
		void SetActive(bool active);
		void AddAttribute(content::ObjectName name, BaseAttribute* attribute);
		bool AddDynamicAttribute(content::ObjectName name, BaseAttribute* attribute);
		void RemoveDynamicAttribute(const content::ObjectName& name);

		AttributeList attributes;
		DynamicAttributeList* dynamicAttributes;
		Attribute<math::Matrix>* transform;
		BehaviourController behaviours;
		// The master table index, 0xFFFF while unregistered
		unsigned short index;
		// 0: updated in the first pass; n: in the n-th deferred pass (after the objects it depends on; guessed)
		unsigned char updatePass;
		unsigned char unknown5B;
		int unknown5C;
	};
}

#endif
