// proto::BlobShadowBehaviour (RTTI and reflection names; base engine::Behaviour): a dark blob drawn under an object. It
// holds the blob's texture (a reflected reference, "blobTexture"), the radius ("radius"), the shader that draws it
// and a drawable. Unit 0x102EDD50 - 0x102EE680 (no assert path; the file name is a guess). The reflected names are
// original, the rest is guessed; Update (slot 4) is left to the engine.
#ifndef PROTO_RENDER_BLOBSHADOWBEHAVIOUR_H
#define PROTO_RENDER_BLOBSHADOWBEHAVIOUR_H

#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"
#include "code/engine/render/async/drawable.h"
#include "code/math/vector.h"
#include "code/pure3d/primitive.h"
#include "code/pure3d/shader.h"

namespace engine
{
	namespace driving
	{
		extern const float gOne;
	}
}

namespace proto
{
	class BlobShadowBehaviour : public engine::Behaviour
	{
	public:
		// 0x102EDD90
		explicit BlobShadowBehaviour(engine::GameObject* newOwner);
		// 0x102EDF00 (the deleting destructor is 0x102EE200)
		virtual ~BlobShadowBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x102EDF60): listens to the update messages and makes the shader the blob is drawn with
		virtual void Slot1();
		// vftable slot 3 (0x102EDE40)
		virtual void OnActiveChanged(bool active);
		// vftable slot 4 (0x102EE230)
		virtual void Update(float dt, unsigned short mask);
		// vftable slot 6 (0x102EDE80)
		virtual void OnMessage(engine::Message* message);

		// 0x102EDDF0: destroys the drawable if there is one (name guess)
		void DestroyDrawable();
		// 0x102EE010: tells the drawable where the blob lies (name guess)
		void UpdateBindings();

		engine::render::Drawable drawable;  // +0xC
		math::Vector position;  // +0x10
		pure3d::Texture* blobTexture;  // +0x1C
		pure3d::Shader* shader;  // +0x20
		float radius;  // +0x24
	};
}

#endif
