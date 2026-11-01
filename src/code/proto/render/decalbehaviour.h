// proto::DecalBehaviour (RTTI and reflection names; base engine::Behaviour): the decals stuck on an object (bullet
// holes, scorch marks): a growable array of the effect drawables that were put on it, each fading after its time.
// Reflected: "maxDecals" and "fadeTime". Unit 0x102EE7D0 - 0x102EF240 (no assert path; the file name is a guess). The
// reflected names are original, the rest is guessed; the decal creation and Update are reconstructed from the code.
#ifndef PROTO_RENDER_DECALBEHAVIOUR_H
#define PROTO_RENDER_DECALBEHAVIOUR_H

#include "code/container/arraydynamicnew.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"
#include "code/engine/render/async/drawable.h"
#include "code/math/vector.h"
#include "code/proto/render/deformshaderbehaviour.h"

namespace engine
{
	namespace driving
	{
		extern const float gOne;
	}
}

namespace proto
{
	// RTTI proto::AddDecalMessage (base ProtoRenderMsg, id 0x11): asks the object to put a decal on itself
	struct AddDecalMessage : public ProtoRenderMsg
	{
		AddDecalMessage() : ProtoRenderMsg(0x11)
		{
		}
		virtual ~AddDecalMessage()
		{
		}

		const core::Name<core::CaseSensitiveKey>* effect;  // +0xC
		const math::Vector* position;  // +0x10
		const math::Vector* direction;  // +0x14
		const float* size;  // +0x18
		float unknown1C;
		float unknown20;
		float unknown24;
		float lifetime;  // +0x28
	};

	class DecalBehaviour : public engine::Behaviour
	{
	public:
		// One decal of the array (0xC bytes): its drawable, the time before it starts to fade (negative once it
		// has) and the fade left
		struct Decal
		{
			engine::render::Drawable drawable;
			float timeLeft;
			float fade;
		};

		// 0x102EF000
		explicit DecalBehaviour(engine::GameObject* newOwner);
		// 0x102EF080 (the deleting destructor is 0x102EF110)
		virtual ~DecalBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x102EEC20): makes room for the decals
		virtual void Slot1();
		// vftable slot 4 (0x102EEC80): ages the decals and lets them fade
		virtual void Update(float dt, unsigned short mask);
		// vftable slot 6 (0x102EF0C0)
		virtual void OnMessage(engine::Message* message);

		// 0x102EED90: destroys every decal
		void Clear();
		// 0x102EEDE0: puts a decal on the object when there is room
		void AddDecal(AddDecalMessage* message);

		unsigned int maxDecals;  // +0xC
		container::ArrayDynamicNew<Decal> decals;  // +0x10
		unsigned char unknown1C[4];
		float fadeTime;  // +0x20
	};
}

#endif
