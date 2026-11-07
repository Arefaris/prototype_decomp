// The patch of the mgraph library (RTTI: mgraph::Patch, an entity that wraps a dynamic object): the name of the graph
// that the audio and music code plays, and the properties of the object that the graph's trigger data describes.
#ifndef MGRAPH_PATCH_H
#define MGRAPH_PATCH_H

#include "code/om/dynamicobjectentity.h"

namespace mgraph
{
	class Patch : public om::DynamicObjectEntity
	{
	public:
		// 0x105B9540
		explicit Patch(const om::ClassName& newName);
		// Slot 0 (0x105B9380 is the body, the deleting destructor 0x105B9570)
		virtual ~Patch();
		// Slots 3, 4, 6, 7 and 8 (0x105BA0E0, 0x105B9860, 0x105BA370, 0x105B9CD0, 0x105B9D70): read and write the patch as
		// text and in binary form, and the last finds the graph of the name
		virtual bool Slot3(void* argument);
		virtual void Slot4(void* argument);
		virtual bool Slot6(void* argument);
		virtual bool Slot7(void* argument);
		virtual bool Slot8(void* argument);
		// Slot 9 (0x105B9820)
		virtual om::EntityTypeBase* GetEntityType();
		OM_ENTITY_ALLOCATION(Patch)

		// 0x105B93B0 / 0x105B93C0 / 0x105B93D0
		const om::ClassName& GetGraphName() const;
		bool GetIsSingleton() const;
		void SetIsSingleton(bool newIsSingleton);

		om::ClassName graphName;  // 0x48
		bool isSingleton;  // 0x50
	};
}

#endif
