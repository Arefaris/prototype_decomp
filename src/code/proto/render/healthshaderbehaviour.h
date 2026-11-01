// proto::HealthShaderBehaviour (RTTI and reflection names; base engine::Behaviour): feeds the object's drawable the
// share of its health that is left, as the shader input "health_percent". Unit 0x102EF190 - 0x102EF600 (no assert
// path; the file name is a guess). Nothing is reflected beyond the base class.
#ifndef PROTO_RENDER_HEALTHSHADERBEHAVIOUR_H
#define PROTO_RENDER_HEALTHSHADERBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"

namespace proto
{
	class HealthShaderBehaviour : public engine::Behaviour
	{
	public:
		// 0x102EF1D0
		explicit HealthShaderBehaviour(engine::GameObject* newOwner);
		// 0x102EF230 (the deleting destructor is 0x102EF330)
		virtual ~HealthShaderBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 4 (0x102EF5E0): refreshes the shader input when the health changed
		virtual void Update(float dt, unsigned short mask);
		// vftable slot 6 (0x102EF240)
		virtual void OnMessage(engine::Message* message);

		// 0x102EF360: gives the drawable the share of health that is left (name guess)
		void UpdateShader();

		bool dirty;  // +0xC
		int heap;  // +0x10
	};
}

#endif
