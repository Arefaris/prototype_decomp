// proto::WebNodeLocator (RTTI and reflection names; a load object): where a node of the web of intrigue is placed in
// the world, with the index of the node it belongs to. Unit 0x1055B000 - 0x1055B770 (no assert path; the file name is
// a guess).
#ifndef PROTO_WEBOFINTRIGUE_WEBNODELOCATOR_H
#define PROTO_WEBOFINTRIGUE_WEBNODELOCATOR_H

#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/math/matrix.h"

namespace proto
{
	class WebNodeLocator : public content::MetaLoadObject
	{
	public:
		// 0x1055B3C0
		WebNodeLocator();
		// 0x1055B220 (the deleting destructor is 0x1055B4F0)
		virtual ~WebNodeLocator();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 3 (0x1055B230) and 4 (0x1055B250): the manager learns the node's transform when the locator has
		// loaded, and that it is ready
		virtual void Slot3(int unused);
		virtual bool IsReady();

		math::Matrix transform;  // +8
		int nodeID;  // +0x48
	};
}

#endif
