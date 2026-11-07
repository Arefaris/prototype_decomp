// proto::ProtoColourVariationBehaviour (RTTI and reflection names; base engine::Behaviour): gives the drawable of its
// object the colours of one entry of a shader palette (shaderPalette), picked at random unless a message names one, and
// patches the shader inputs of a drawable that is created later (createPatchForNewDrawable). Unit 0x102DE4C0 -
// 0x102DEB50 (no assert path; the file name is a guess). The reflected names are original, the rest is guessed; the
// construction and the reflection are reconstructed.
#ifndef PROTO_RENDER_PROTOCOLOURVARIATIONBEHAVIOUR_H
#define PROTO_RENDER_PROTOCOLOURVARIATIONBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"
#include "code/proto/shaders/shaderpalette.h"

namespace proto
{
	class ProtoColourVariationBehaviour : public engine::Behaviour
	{
	public:
		// 0x102DE540
		explicit ProtoColourVariationBehaviour(engine::GameObject* newOwner);
		// 0x102DE610 (the deleting destructor is 0x102DE870)
		virtual ~ProtoColourVariationBehaviour();
		// 0x102DE500
		static content::ClassInfo* GetClassInfo();
		// 0x102DEA40
		static content::MemberList* GetMembers();

		// vftable slot 6 (0x102DE8A0)
		virtual void OnMessage(engine::Message* message);

		ShaderPalette* shaderPalette;  // +0xC
		unsigned int paletteIndex;  // +0x10
		bool createPatchForNewDrawable;  // +0x14
	};
}

#endif
