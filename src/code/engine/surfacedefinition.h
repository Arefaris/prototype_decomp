// SurfaceDefinition (RTTI and reflection names; the class is in the global namespace): a content library object that
// describes a surface material: the physics object the surface refers to and the names of the decal and of the sound
// effect it uses. Unit 0x10911500 - 0x10911880 (no assert path; the directory and file name are guesses). The
// reflected member names are original; the rest is guessed.
#ifndef ENGINE_SURFACEDEFINITION_H
#define ENGINE_SURFACEDEFINITION_H

#include "code/container/string.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/content/stringmetatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/gameobjecthandle.h"

namespace content
{
	// The meta type of a string member of a StringC<N>: one instance per member (Id tells them apart), in the unit of
	// the class that reflects it. The argument only selects the template
	template<int Id, int N> inline StringMetaType* GetMemberStringMetaType(container::StringC<N>* member, const char* code)
	{
		static StringMetaType sType(N, code);
		return &sType;
	}

	// Where the characters of a StringC<N> start (after the vftable); every string member's offset is this plus the
	// member's. The engine passes the address of the member in an object at gStringMemberBase (0x11276934)
	template<class S> int StringBufferOffset(S* member)
	{
		return 4;
	}

	extern unsigned char gStringMemberBase[];
}

class SurfaceDefinition : public content::MetaLoadObject
{
public:
	typedef container::StringC<260> Text;

	// 0x109117B0
	SurfaceDefinition();
	// 0x10911800 (deleting destructor 0x10911860)
	virtual ~SurfaceDefinition();

	// The class's reflection
	static content::ClassInfo* GetClassInfo();
	static content::MemberList* GetMembers();

	// vftable slot 3 (0x10911550): nothing to do once loaded
	virtual void Slot3(int unused)
	{
	}

	engine::GameObjectHandle handle;  // +0x08
	int unknownC;
	core::Name<core::CaseSensitiveKey> name;  // +0x10
	Text physicsObjectReference;  // +0x18
	Text soundEffectName;  // +0x120
	Text decalName;  // +0x228
};

#endif
