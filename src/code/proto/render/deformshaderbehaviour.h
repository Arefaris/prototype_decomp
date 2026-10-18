// proto::DeformShaderBehaviour (RTTI; vftable 0x10DEA3CC, base engine::Behaviour): the behaviour that dents a vehicle's
// deformation shader. It keeps the last four dents in a small ring at +0x10, fades each one in and hands them to a
// DeformShaderModifier (vtable 0x10DEA3C0) that writes them into the drawable's shader parameters on the render
// thread. The unit has no assert path, so the file name, the class layout and the member names are guesses.
#ifndef PROTO_RENDER_DEFORMSHADERBEHAVIOUR_H
#define PROTO_RENDER_DEFORMSHADERBEHAVIOUR_H

#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"
#include "code/engine/render/async/drawable.h"
#include "code/engine/render/async/private/drawableimpl.h"
#include "code/math/vector.h"

namespace engine
{
	namespace render
	{
		// 0x10817A50 / 0x10817AD0 (renderglobals.cpp): the memory the modifiers of the render events live in
		void* AllocRenderEvent(unsigned int size);
		void FreeRenderEvent(void* memory);
	}
}

namespace proto
{
	// One dent: where it is, and two values that grow from 0 to a target while the dent fades in. The record the
	// shader reads is {+0x0C target, +0x10 value, +0x14 time left, +0x18 target, +0x1C value}.
	struct Dent
	{
		Dent()
		{
		}
		// The engine's copy of a dent runs component by component through the x87 unit (fld / fstp)
		Dent& operator=(const Dent& dent)
		{
			position.x = dent.position.x;
			position.y = dent.position.y;
			position.z = dent.position.z;
			unknownC = dent.unknownC;
			unknown10 = dent.unknown10;
			unknown14 = dent.unknown14;
			unknown18 = dent.unknown18;
			unknown1C = dent.unknown1C;
			return *this;
		}

		math::Vector position;   // +0x00
		float unknownC;          // +0x0C
		float unknown10;         // +0x10
		float unknown14;         // +0x14
		float unknown18;         // +0x18
		float unknown1C;         // +0x1C
	};

	// The four dents the shader keeps: the buffer runs from the object's own address and end points just past the
	// dent added last (0x84 bytes)
	class DentBuffer
	{
	public:
		// 0x102D41C0 (another function of the same unit): appends dent, false when the four slots are taken
		bool Push(const Dent& dent);
		// 0x102D43F0: replaces the dents with another buffer's
		DentBuffer& operator=(const DentBuffer& other);

		Dent dents[4];
		Dent* end;
	};

	// The message type of the render behaviours' messages (RTTI proto::ProtoRenderMsg, base IntrusiveMessage)
	struct ProtoRenderMsg : public engine::IntrusiveMessage
	{
	public:
		explicit ProtoRenderMsg(short newId) : engine::IntrusiveMessage(0x3D, newId)
		{
		}
		virtual ~ProtoRenderMsg()
		{
		}
	};

	// Tells the behaviour of the object how strongly the level of detail is biased (vftable 0x10DEA384)
	struct SetLODBiasMessage : public ProtoRenderMsg
	{
	public:
		explicit SetLODBiasMessage(float newBias) : ProtoRenderMsg(2)
		{
			bias = newBias;
		}
		virtual ~SetLODBiasMessage()
		{
		}

		float bias;
	};

	class DeformShaderBehaviour : public engine::Behaviour
	{
	public:
		// The modifier the render thread applies (vtable 0x10DEA3C0, 0x8C bytes): the dents at +4, the bias at +0x88
		class DeformShaderModifier : public engine::render::DrawableModifier
		{
		public:
			// 0x102D4810: no dents yet
			DeformShaderModifier();
			// 0x102D4C50: writes the dents into the drawable's shader parameters and deletes itself
			virtual void Apply(engine::render::DrawableImpl* drawable);
			// 0x102D4350: stores one more dent
			bool AddDent(const math::Vector& position, float unknownC, float unknown14, float unknown18);

			static void* operator new(unsigned int size)
			{
				return engine::render::AllocRenderEvent(size);
			}
			static void operator delete(void* memory)
			{
				engine::render::FreeRenderEvent(memory);
			}

			DentBuffer dents;
			// The bias is copied as raw bits
			unsigned int bias;
		};

		// The vftable (0x10DEA3CC): slots 2 and 3 are the base's, the last one is the scalar deleting destructor
		virtual void Slot0();
		virtual void Slot1();
		virtual void Update(float dt, unsigned short mask);
		virtual void OnPostedMessage(engine::Message* message);
		virtual void OnMessage(engine::Message* message);
		virtual ~DeformShaderBehaviour();

		// 0x102D3FA0: the drawable of the object (asks it with a GetHighLODMessage)
		engine::render::Drawable GetDrawable();

		unsigned char unknownC[4];
		// +0x10: the dents, advanced by Update
		DentBuffer dents;
		// +0x94: the bias handed to the modifier, +0x98 how many dents are live
		unsigned int bias;
		int count;
		// +0x9C: the dents changed and the modifier has to run again
		bool dirty;
		// +0x9D: the LOD bias message was sent
		bool biasSent;
	};
}

#endif
