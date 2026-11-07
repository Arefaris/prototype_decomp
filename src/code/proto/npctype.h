// proto::NPCRender and proto::NPCType (RTTI and reflection names; base content::MetaLoadObject, NPCType derives from
// NPCRender): what a pedestrian is shown with. NPCRender names the drawables of the lower levels of detail and the shader
// palette, NPCType adds the drawable of the character itself, its gender and voice, the template of the game object
// and the pool of instances it draws from. Unit 0x1047AFE0 - 0x1047B9B0 (no assert path; the file name is a guess).
// The reflected names are original, the rest is guessed; the reflection, the construction and the destruction are
// reconstructed.
#ifndef PROTO_NPCTYPE_H
#define PROTO_NPCTYPE_H

#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/gameobjectspawner.h"
#include "code/engine/render/drawablearchetype.h"
#include "code/proto/npcanimation.h"
#include "code/proto/npcinstancepool.h"
#include "code/proto/shaders/shaderpalette.h"

namespace proto
{
	// The drawables of the lower levels of detail of a pedestrian (RTTI proto::NPCRender; 0x14 bytes)
	class NPCRender : public content::MetaLoadObject
	{
	public:
		// 0x1047B190
		NPCRender();
		// 0x1047B200 (the deleting destructor is 0x1047B380)
		virtual ~NPCRender();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// 0x1047B060: the drawable of a level of detail (0 the medium one, 1 the low one)
		NPCDrawable* GetLod(int level) const;

		NPCDrawable* lods[2];  // +8: "lod_Medium", "lod_Low"
		ShaderPalette* shaderPalette;  // +0x10
	};

	// The kind of pedestrian (RTTI proto::NPCType; 0x38 bytes)
	class NPCType : public NPCRender
	{
	public:
		// 0x1047B250
		NPCType();
		// 0x1047B2B0 (the deleting destructor is 0x1047B3B0)
		virtual ~NPCType();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 3 (0x1047B070) and 4 (0x1047B090): left to the engine
		virtual void Slot3(int unused);
		virtual bool IsReady();

		// vftable slot 6 (0x1047B2F0): keeps the name the type is known by
		virtual void SetName(const content::ObjectName& newName);

		engine::render::DrawableArchetype* lodCharacter;  // +0x14: "lod_Character"
		core::Name<core::CaseSensitiveKey> gender;  // +0x18
		content::MetaObjectTemplate* characterTemplate;  // +0x20
		NPCInstancePool* instancePool;  // +0x24
		core::Name<core::CaseSensitiveKey> name;  // +0x28
		core::Name<core::CaseSensitiveKey> voice;  // +0x30
	};
}

#endif
